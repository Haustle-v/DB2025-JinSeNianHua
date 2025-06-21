#pragma once
#include "execution_defs.h"
#include "execution_manager.h"
#include "executor_abstract.h"
#include "index/ix.h"
#include "system/sm.h"
#include <vector>
#include <algorithm>

class SortExecutor : public AbstractExecutor {
private:
    std::unique_ptr<AbstractExecutor> prev_;  // 前一个执行器
    std::vector<TabCol> order_by_cols_;       // 排序的列
    std::vector<bool> is_asc_;                // 是否升序排序
    std::vector<ColMeta> cols_;               // 输出的列元数据
    size_t len_;                              // 输出记录的长度
    bool is_first_;                           // 是否是第一次调用
    std::vector<std::unique_ptr<RmRecord>> sorted_records_;  // 排序后的记录
    size_t current_pos_;                      // 当前记录的位置
    int32_t limit_;

public:
    SortExecutor(std::unique_ptr<AbstractExecutor> prev, 
                std::vector<TabCol> order_by_cols,
                std::vector<bool> is_asc,
                int32_t limit) 
        : prev_(std::move(prev)), 
          order_by_cols_(std::move(order_by_cols)),
          is_asc_(std::move(is_asc)),
          is_first_(true),
          current_pos_(0),
          limit_(limit) {
        // 复制前一个执行器的列信息
        cols_ = prev_->cols();
        len_ = prev_->tupleLen();
    }

    void beginTuple() override {
        if (is_first_) {
            // 收集所有记录
            std::vector<std::unique_ptr<RmRecord>> records;
            prev_->beginTuple();
            while (!prev_->is_end()) {
                auto record = prev_->Next();
                if (record) {
                    records.push_back(std::move(record));
                }
                prev_->nextTuple();
            }

            // 对记录进行排序
            std::sort(records.begin(), records.end(), 
                [this](const std::unique_ptr<RmRecord>& a, const std::unique_ptr<RmRecord>& b) {
                    for (size_t i = 0; i < order_by_cols_.size(); i++) {
                        const auto& col = order_by_cols_[i];
                        auto col_meta = prev_->get_col_offset(col);
                        int cmp = ix_compare(
                            a->data + col_meta.offset,
                            b->data + col_meta.offset,
                            col_meta.type,
                            col_meta.len
                        );
                        if (cmp != 0) {
                            return is_asc_[i] ? cmp < 0 : cmp > 0;
                        }
                    }
                    return false;  // 如果所有列都相等，保持原有顺序
                });

            sorted_records_ = std::move(records);
            // 应用 limit 限制
            if (limit_ > 0 && sorted_records_.size() > static_cast<size_t>(limit_)) {
                sorted_records_.resize(limit_);
            }
            current_pos_ = 0;
            is_first_ = false;
        }
    }

    void nextTuple() override {
        if (current_pos_ < sorted_records_.size()) {
            current_pos_++;
        }
    }

    std::unique_ptr<RmRecord> Next() override {
        if (is_first_) {
            beginTuple();
        }
        if (current_pos_ < sorted_records_.size()) {
            return std::make_unique<RmRecord>(*sorted_records_[current_pos_]);
        }
        return nullptr;
    }

    bool is_end() const override {
        return current_pos_ >= sorted_records_.size();
    }

    ColMeta get_col_offset(const TabCol &target) override {
        return prev_->get_col_offset(target);
    }

    const std::vector<ColMeta> &cols() const override { 
        return cols_; 
    }
    
    size_t tupleLen() const override { 
        return len_; 
    }
    
    std::string getType() override { 
        return "SortExecutor"; 
    }

    Rid &rid() override { 
        return _abstract_rid; 
    }
};
