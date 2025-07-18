#pragma once
#include "execution_defs.h"
#include "execution_manager.h"
#include "executor_abstract.h"
#include <unordered_map>
#include <variant>
#include "parser/ast.h"
#include <limits>
#include <string>
#include <string_view> // 引入 string_view

class AggPlanExecutor : public AbstractExecutor {
    private:
        // AggValue 结构体保持不变
        struct AggValue {
            std::variant<int32_t, float> value;
            ColType type;
            ast::AggFuncType agg_type;
            
            AggValue(ColType t, ast::AggFuncType at) : type(t), agg_type(at) {
                if (agg_type == ast::AggFuncType::AGG_AVG) {
                    this->type = TYPE_FLOAT;
                }
                
                switch(agg_type) {
                    case ast::AggFuncType::AGG_COUNT:
                        value = int32_t(0);
                        break;
                    case ast::AggFuncType::AGG_MIN:
                        if (type == TYPE_INT) value = std::numeric_limits<int32_t>::max();
                        else value = std::numeric_limits<float>::max();
                        break;
                    case ast::AggFuncType::AGG_MAX:
                        if (type == TYPE_INT) value = std::numeric_limits<int32_t>::min();
                        else value = std::numeric_limits<float>::lowest();
                        break;
                    case ast::AggFuncType::AGG_AVG:
                    case ast::AggFuncType::AGG_SUM:
                        if (this->type == TYPE_INT) value = int32_t(0);
                        else value = 0.0f;
                        break;
                    default:
                        value = int32_t(0);
                        break;
                }
            }
        };

        std::unique_ptr<AbstractExecutor> prev_;
        std::vector<TabCol> sel_cols_;
        std::vector<TabCol> group_by_cols_;
        bool is_first_;
        std::vector<ColMeta> cols_;
        size_t len_;

        
        // 哈希表，键为 string，值为聚合记录和计数的 pair
        std::unordered_map<std::string, std::pair<std::unique_ptr<RmRecord>, int64_t>> group_results_;
        
        // 用于保持插入顺序，以便按分组顺序输出
        std::vector<std::string> insert_order_; 
        
        size_t output_idx_;

        std::string key_buffer_;

    public:
        AggPlanExecutor(std::unique_ptr<AbstractExecutor> prev, std::vector<TabCol> group_by_cols, std::vector<TabCol> sel_cols) {
            prev_ = std::move(prev);
            group_by_cols_ = std::move(group_by_cols);
            sel_cols_ = std::move(sel_cols);
            is_first_ = true;
            
            int curr_offset = 0;
            
            for (const auto &group_col : group_by_cols_) {
                ColMeta col_meta = prev_->get_col_offset(group_col);
                col_meta.offset = curr_offset;
                curr_offset += col_meta.len;
                cols_.push_back(col_meta);
            }
            
            for (const auto &sel_col : sel_cols_) {
                if (sel_col.aggFuncType == ast::AggFuncType::AGG_COUNT) {
                    ColMeta col_meta = { .tab_name = sel_col.tab_name, .name = sel_col.col_name, .type = TYPE_INT, .len = sizeof(int32_t), .offset = curr_offset, .index = false };
                    cols_.push_back(col_meta);
                    curr_offset += col_meta.len;
                } else {
                    ColMeta col_meta = prev_->get_col_offset(sel_col);
                    if (sel_col.aggFuncType == ast::AggFuncType::AGG_AVG && col_meta.type == TYPE_INT) {
                        col_meta.type = TYPE_FLOAT;
                        col_meta.len = sizeof(float);
                    }
                    col_meta.offset = curr_offset;
                    curr_offset += col_meta.len;
                    cols_.push_back(col_meta);
                }
            }
            
            len_ = curr_offset;
        }

        void beginTuple() override {
            if (is_first_) {
                computeAggregation();
                is_first_ = false;
            }
            output_idx_ = 0;
        }

        void nextTuple() override {
            output_idx_++;
        }

        std::unique_ptr<RmRecord> Next() override {
            if (is_first_) {
                computeAggregation();
                is_first_ = false;
            }
            if (output_idx_ >= insert_order_.size()) return nullptr;
            // 通过 insert_order_ 中的 key 来查找结果
            return std::make_unique<RmRecord>(*group_results_[insert_order_[output_idx_]].first);
        }

        bool is_end() const override {
            return output_idx_ >= insert_order_.size();
        }

        ColMeta get_col_offset(const TabCol &target) override {
            int curr_index = 0;
            for (const auto& group_col : group_by_cols_) {
                if (group_col.col_name == target.col_name && group_col.tab_name == target.tab_name && group_col.aggFuncType == target.aggFuncType && group_col.alias == target.alias) {
                    return cols_[curr_index];
                }
                curr_index++;
            }
            for (const auto& sel_col : sel_cols_) {
                if (sel_col.col_name == target.col_name && sel_col.tab_name == target.tab_name && sel_col.aggFuncType == target.aggFuncType && sel_col.alias == target.alias) {
                    return cols_[curr_index];
                }
                curr_index++;
            }
            throw ColumnNotFoundError(target.col_name);
        }

        const std::vector<ColMeta> &cols() const override { return cols_; }
        size_t tupleLen() const override { return len_; }
        std::string getType() override { return "AggPlanExecutor"; }
        Rid &rid() override { return _abstract_rid; }


    private:
        // updateAggValue 保持不变
        void updateAggValue(AggValue& agg_value, const char* data, const ColMeta& col_meta) {
            if (agg_value.agg_type == ast::AggFuncType::AGG_COUNT) {
                std::get<int32_t>(agg_value.value)++;
                return;
            }

            if (col_meta.type == TYPE_INT) {
                int32_t val = *(int32_t*)(data);
                switch(agg_value.agg_type) {
                    case ast::AggFuncType::AGG_SUM:
                        std::get<int32_t>(agg_value.value) += val;
                        break;
                    case ast::AggFuncType::AGG_AVG:
                        std::get<float>(agg_value.value) += val;
                        break;
                    case ast::AggFuncType::AGG_MIN:
                        std::get<int32_t>(agg_value.value) = std::min(std::get<int32_t>(agg_value.value), val);
                        break;
                    case ast::AggFuncType::AGG_MAX:
                        std::get<int32_t>(agg_value.value) = std::max(std::get<int32_t>(agg_value.value), val);
                        break;
                    default: break;
                }
            } else if (col_meta.type == TYPE_FLOAT) {
                float val = *(float*)(data);
                switch(agg_value.agg_type) {
                    case ast::AggFuncType::AGG_SUM:
                    case ast::AggFuncType::AGG_AVG:
                        std::get<float>(agg_value.value) += val;
                        break;
                    case ast::AggFuncType::AGG_MIN:
                        std::get<float>(agg_value.value) = std::min(std::get<float>(agg_value.value), val);
                        break;
                    case ast::AggFuncType::AGG_MAX:
                        std::get<float>(agg_value.value) = std::max(std::get<float>(agg_value.value), val);
                        break;
                    default: break;
                }
            }
        }
        
        void computeAggregation() {
            prev_->beginTuple();
            
            // 处理上游没有数据且没有 group by 的特殊情况
            if (prev_->is_end() && group_by_cols_.empty()) {
                auto new_record = std::make_unique<RmRecord>(len_);
                int curr_index = 0;
                for (const auto& sel_col : sel_cols_) {
                    const auto& col_meta = cols_[curr_index];
                    AggValue default_val(col_meta.type, sel_col.aggFuncType);
                    if (std::holds_alternative<int32_t>(default_val.value)) {
                        *(int32_t*)(new_record->data + col_meta.offset) = std::get<int32_t>(default_val.value);
                    } else {
                        *(float*)(new_record->data + col_meta.offset) = std::get<float>(default_val.value);
                    }
                    curr_index++;
                }
                std::string key = "";
                group_results_[key] = std::make_pair(std::move(new_record), 0);
                insert_order_.push_back(key);
                return;
            }

            while (!prev_->is_end()) {
                auto record = prev_->Next();
                if (!record) { prev_->nextTuple(); continue; }

                // 使用可重用的 key_buffer_ 构建分组键
                key_buffer_.clear(); // 清空 buffer 以便重用
                if (group_by_cols_.empty()) {
                    // 对于没有 GROUP BY 的聚合（例如 SELECT SUM(a) FROM t），使用一个固定的内部键
                    key_buffer_ = "__grand_total_group__";
                } else {
                    for (const auto &group_col : group_by_cols_) {
                        auto col_meta = prev_->get_col_offset(group_col);
                        // append 直接从内存指针添加，避免创建临时对象
                        key_buffer_.append(record->data + col_meta.offset, col_meta.len);
                    }
                }

                // 使用 find + emplace/iterator 模式，避免二次查找
                auto it = group_results_.find(key_buffer_);

                if (it == group_results_.end()) {
                    // 分组键第一次出现，创建新记录
                    auto new_record = std::make_unique<RmRecord>(len_);
                    int curr_index = 0;
                    
                    // 1. 拷贝 group by 列的值
                    for (const auto& group_col : group_by_cols_) {
                        auto col_meta = cols_[curr_index];
                        memcpy(new_record->data + col_meta.offset, record->data + prev_->get_col_offset(group_col).offset, col_meta.len);
                        curr_index++;
                    }
                    
                    // 2. 初始化聚合列的值
                    for (const auto& sel_col : sel_cols_) {
                        if (sel_col.aggFuncType == ast::AggFuncType::AGG_COUNT) {
                            *(int32_t*)(new_record->data + cols_[curr_index].offset) = 1;
                            curr_index++;
                            continue;
                        }
                        
                        // 移除对 COUNT(*) 的显式错误抛出，以支持该功能
                        // if (sel_col.col_name == "*" ) { ... }

                        auto col_meta = cols_[curr_index];
                        auto prev_col_meta = prev_->get_col_offset(sel_col);
                        
                        // 使用 updateAggValue 进行初始化
                        AggValue agg_value(col_meta.type, sel_col.aggFuncType);
                        updateAggValue(agg_value, record->data + prev_col_meta.offset, prev_col_meta);

                        if (std::holds_alternative<int32_t>(agg_value.value)) {
                            *(int32_t*)(new_record->data + col_meta.offset) = std::get<int32_t>(agg_value.value);
                        } else {
                            *(float*)(new_record->data + col_meta.offset) = std::get<float>(agg_value.value);
                        }
                        curr_index++;
                    }
                    
                    // 将新记录插入哈希表，并记录插入顺序
                    // key_buffer_ 在此被拷贝一次存入哈希表，后续循环可安全覆盖 key_buffer_
                    group_results_[key_buffer_] = std::make_pair(std::move(new_record), 1);
                    insert_order_.push_back(key_buffer_);

                } else {
                    // 分组键已存在，直接更新
                    auto &existing_record_pair = it->second;
                    auto &existing_record = existing_record_pair.first;
                    existing_record_pair.second++; // 增加该组的计数

                    int curr_index = group_by_cols_.size();
                    for (const auto& sel_col : sel_cols_) {
                        const auto& col_meta = cols_[curr_index];
                        char* dest_ptr = existing_record->data + col_meta.offset;

                        if (sel_col.aggFuncType == ast::AggFuncType::AGG_COUNT) {
                            *(reinterpret_cast<int32_t*>(dest_ptr)) += 1;
                            curr_index++;
                            continue;
                        }

                        const auto& prev_col_meta = prev_->get_col_offset(sel_col);
                        const char* src_ptr = record->data + prev_col_meta.offset;

                        // 更新聚合值
                        if (prev_col_meta.type == TYPE_INT) {
                            int32_t new_val = *reinterpret_cast<const int32_t*>(src_ptr);
                            switch(sel_col.aggFuncType) {
                                case ast::AggFuncType::AGG_SUM: *reinterpret_cast<int32_t*>(dest_ptr) += new_val; break;
                                case ast::AggFuncType::AGG_AVG: *reinterpret_cast<float*>(dest_ptr) += new_val; break;
                                case ast::AggFuncType::AGG_MIN: *reinterpret_cast<int32_t*>(dest_ptr) = std::min(*reinterpret_cast<int32_t*>(dest_ptr), new_val); break;
                                case ast::AggFuncType::AGG_MAX: *reinterpret_cast<int32_t*>(dest_ptr) = std::max(*reinterpret_cast<int32_t*>(dest_ptr), new_val); break;
                                default: break;
                            }
                        } else if (prev_col_meta.type == TYPE_FLOAT) {
                            float new_val = *reinterpret_cast<const float*>(src_ptr);
                            switch(sel_col.aggFuncType) {
                                case ast::AggFuncType::AGG_SUM:
                                case ast::AggFuncType::AGG_AVG: *reinterpret_cast<float*>(dest_ptr) += new_val; break;
                                case ast::AggFuncType::AGG_MIN: *reinterpret_cast<float*>(dest_ptr) = std::min(*reinterpret_cast<float*>(dest_ptr), new_val); break;
                                case ast::AggFuncType::AGG_MAX: *reinterpret_cast<float*>(dest_ptr) = std::max(*reinterpret_cast<float*>(dest_ptr), new_val); break;
                                default: break;
                            }
                        }
                        curr_index++;
                    }
                }
                
                prev_->nextTuple();
            }

            // 所有元组处理完毕后，计算 AVG 的最终值
            for (auto& group_pair : group_results_) {
                int curr_index = group_by_cols_.size();
                auto& record = group_pair.second.first;
                auto& count = group_pair.second.second;
                if (count > 0) {
                    for (const auto& sel_col : sel_cols_) {
                        if (sel_col.aggFuncType == ast::AggFuncType::AGG_AVG) {
                            const auto &col_meta = cols_[curr_index];
                            *(float*)(record->data + col_meta.offset) /= count;
                        }
                        curr_index++;
                    }
                }
            }
        }
};