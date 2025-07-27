#pragma once
#include "execution_defs.h"
#include "execution_manager.h"
#include "executor_abstract.h"
#include "index/ix.h"
#include "system/sm.h"
#include <vector>
#include <algorithm>
#include <functional> // For std::function

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
        if (!is_first_) {
            return;
        }

        // 定义统一的比较逻辑，这将被用于堆和全排序
        auto comparator = [this](const std::unique_ptr<RmRecord>& a, const std::unique_ptr<RmRecord>& b) {
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
                    // is_asc ? (a < b) : (a > b)
                    return is_asc_[i] ? cmp < 0 : cmp > 0;
                }
            }
            return false; // 如果所有列都相等，a 不“小于”b
        };

        // 优化：如果存在 limit，使用 Top-K 堆排序算法
        if (limit_ > 0) {
            std::vector<std::unique_ptr<RmRecord>> heap;
            heap.reserve(limit_);
            size_t k = static_cast<size_t>(limit_);

            prev_->beginTuple();
            while (!prev_->is_end()) {
                auto record = prev_->Next();
                if (record) {
                    if (heap.size() < k) {
                        heap.push_back(std::move(record));
                        // 当堆满时，立即将其构建成一个最大堆
                        if (heap.size() == k) {
                            std::make_heap(heap.begin(), heap.end(), comparator);
                        }
                    } else {
                        // 如果新记录比堆顶元素“小”，则替换堆顶元素
                        // comparator(record, heap.front()) 等价于 record < heap.front()
                        if (comparator(record, heap.front())) {
                            // std::pop_heap 将堆顶（最大元素）移动到容器末尾
                            std::pop_heap(heap.begin(), heap.end(), comparator);
                            // 用新记录替换掉原来的最大元素
                            heap.back() = std::move(record);
                            // std::push_heap 将末尾元素压入堆中并调整
                            std::push_heap(heap.begin(), heap.end(), comparator);
                        }
                    }
                }
                prev_->nextTuple();
            }

            // 循环结束后，heap 中包含了 Top-K 个元素，但处于堆序
            // 使用 sort_heap 将堆就地排序为有序序列（升序）
            std::sort_heap(heap.begin(), heap.end(), comparator);
            sorted_records_ = std::move(heap);
            
        } else {
            // 回退到原始逻辑：没有 limit，或者 limit 无效，进行全排序
            std::vector<std::unique_ptr<RmRecord>> records;
            prev_->beginTuple();
            while (!prev_->is_end()) {
                auto record = prev_->Next();
                if (record) {
                    records.push_back(std::move(record));
                }
                prev_->nextTuple();
            }

            // 对所有记录进行排序
            std::sort(records.begin(), records.end(), comparator);
            sorted_records_ = std::move(records);
        }

        current_pos_ = 0;
        is_first_ = false;
    }


    void nextTuple() override {
        if (is_first_) {
            beginTuple();
        }
        if (current_pos_ < sorted_records_.size()) {
            current_pos_++;
        }
    }

    std::unique_ptr<RmRecord> Next() override {
        if (is_first_) {
            beginTuple();
        }
        if (current_pos_ < sorted_records_.size()) {
            // 返回副本以保持 sorted_records_ 的内容不变
            return std::make_unique<RmRecord>(*sorted_records_[current_pos_]);
        }
        return nullptr;
    }

    bool is_end() const override {
        // 如果 Next() 尚未被调用，beginTuple() 也未执行，此时不应是结尾
        if (is_first_) {
            return false;
        }
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