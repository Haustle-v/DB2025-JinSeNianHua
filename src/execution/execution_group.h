#pragma once
#include "execution_defs.h"
#include "execution_manager.h"
#include "executor_abstract.h"
#include <unordered_map>
#include <variant>
#include "parser/ast.h"

class AggPlanExecutor : public AbstractExecutor {
    private:

        // 用于存储聚合值的结构体
        struct AggValue {
            std::variant<int32_t, float> value;  // 存储聚合结果
            ColType type;                        // 值的类型
            ast::AggFuncType agg_type;                    // 聚合函数类型
            
            AggValue(ColType t, ast::AggFuncType at) : type(t), agg_type(at) {
                // 初始化value
                switch(agg_type) {
                    case ast::AggFuncType::AGG_COUNT:
                        value = int32_t(0); // 明确指定类型
                        break;
                    case ast::AggFuncType::AGG_MIN:
                        if (type == TYPE_INT) {
                            value = INT32_MAX;
                        } else {
                            value = std::numeric_limits<float>::max();
                        }
                        break;
                    case ast::AggFuncType::AGG_MAX:
                        if (type == TYPE_INT) {
                            value = INT32_MIN;
                        } else {
                            value = std::numeric_limits<float>::lowest();
                        }
                        break;
                    case ast::AggFuncType::AGG_AVG:
                        if (type == TYPE_INT) {
                            value = 0;
                        } else {
                            value = 0.0f;
                        }
                        break;
                    default:
                        value = 0;
                        break;
                }
            }
        };

        std::unique_ptr<AbstractExecutor> prev_;
        std::vector<TabCol> sel_cols_;      // 选择的列（包含聚合函数的列）
        std::vector<TabCol> group_by_cols_; // group by的列
        bool is_first_;                     // 是否是第一次调用
        std::vector<ColMeta> cols_;         // 输出的列元数据
        size_t len_;                        // 输出记录的长度
        
        // 用于存储分组结果的数据结构
        struct GroupKey {
            std::string key;
            bool operator==(const GroupKey& other) const {
                return key == other.key;
            }
        };
        
        struct GroupKeyHash {
            size_t operator()(const GroupKey& key) const {
                return std::hash<std::string>()(key.key);
            }
        };

        // 存储分组的中间结果, 第二个int64_t用于存储计数
        std::unordered_map<GroupKey, std::pair<std::unique_ptr<RmRecord>, int64_t>, GroupKeyHash> group_results_;
        std::unordered_map<GroupKey, std::pair<std::unique_ptr<RmRecord>, int64_t>, GroupKeyHash>::iterator current_group_;

    public:
        AggPlanExecutor(std::unique_ptr<AbstractExecutor> prev, std::vector<TabCol> group_by_cols, std::vector<TabCol> sel_cols) {
            prev_ = std::move(prev);
            group_by_cols_ = group_by_cols;
            sel_cols_ = sel_cols;
            is_first_ = true;
            
            // 设置输出列的元数据和聚合类型
            size_t curr_offset = 0;
            auto &prev_cols = prev_->cols();
            
            // 添加group by的列
            for (const auto &group_col : group_by_cols_) {
                auto pos = get_col(prev_cols, group_col);
                auto col = *pos;
                col.offset = curr_offset;
                curr_offset += col.len;
                cols_.push_back(col);
            }
            
            // 添加聚合列
            for (const auto &sel_col : sel_cols_) {
                // 如果聚合函数是COUNT，则将类型设置为INT
                if (sel_col.aggFuncType == ast::AggFuncType::AGG_COUNT) {
                    ColMeta col_meta = {
                        .tab_name = sel_col.tab_name,
                        .name = sel_col.col_name,
                        .type = TYPE_INT,
                        .len = sizeof(int32_t),
                        .offset = curr_offset,
                        .index = false,
                    };
                    cols_.push_back(col_meta);
                    curr_offset += col_meta.len;
                    continue;
                }
                auto pos = get_col(prev_cols, sel_col);
                auto col = *pos;
                col.offset = curr_offset;
                curr_offset += col.len;
                cols_.push_back(col);
            }
            
            len_ = curr_offset;
        }

        void beginTuple() override {
            if (is_first_) {
                computeAggregation();
                is_first_ = false;
                current_group_ = group_results_.begin();
            }
        }

        void nextTuple() override {
            if (current_group_ != group_results_.end()) {
                ++current_group_;
            }
        }

        std::unique_ptr<RmRecord> Next() override {
            if (is_first_) {
                computeAggregation();
                is_first_ = false;
                current_group_ = group_results_.begin();
            }
            
            if (current_group_ == group_results_.end()) {
                return nullptr;
            }
            
            auto result = std::make_unique<RmRecord>(*current_group_->second.first);
            current_group_++;
            return result;
        }

        bool is_end() const override {
            return current_group_ == group_results_.end();
        }

        const std::vector<ColMeta> &cols() const override { return cols_; }
        
        size_t tupleLen() const override { return len_; }
        
        std::string getType() override { return "AggPlanExecutor"; }

        Rid &rid() override { return _abstract_rid; }

    private:
        void updateAggValue(AggValue& agg_value, const char* data, const ColMeta& col_meta) {
            if (agg_value.agg_type == ast::AggFuncType::AGG_COUNT) {
                std::get<int32_t>(agg_value.value)++;
                return;
            }

            // 根据不同的聚合类型和数据类型进行更新
            if (col_meta.type == TYPE_INT) {
                int32_t val = *(int32_t*)(data);
                switch(agg_value.agg_type) {
                    case ast::AggFuncType::AGG_SUM:
                    case ast::AggFuncType::AGG_AVG:
                        std::get<int32_t>(agg_value.value) += val;
                        break;
                    case ast::AggFuncType::AGG_MIN:
                        std::get<int32_t>(agg_value.value) = std::min(std::get<int32_t>(agg_value.value), val);
                        break;
                    case ast::AggFuncType::AGG_MAX:
                        std::get<int32_t>(agg_value.value) = std::max(std::get<int32_t>(agg_value.value), val);
                        break;
                    default:
                        break;
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
                    default:
                        break;
                }
            }
        }

        void computeAggregation() {
            // 遍历所有输入记录进行分组和聚合
            prev_->beginTuple();
            while (!prev_->is_end()) {
                auto record = prev_->Next(); // 获取当前行
                if (!record) continue;

                // 构建分组键
                GroupKey group_key;
                std::string key_str;
                for (const auto &group_col : group_by_cols_) {
                    auto col_meta = prev_->get_col_offset(group_col);
                    key_str += std::string(record->data + col_meta.offset, col_meta.len); // 将group by列的值拼接成字符串
                }
                group_key.key = key_str;

                // 如果是新的分组，创建新的结果记录
                if (group_results_.find(group_key) == group_results_.end()) {
                    auto new_record = std::make_unique<RmRecord>(len_);
                    
                    // 复制group by列的值
                    size_t curr_offset = 0;
                    size_t col_idx = 0;
                    for (const auto &group_col : group_by_cols_) {
                        auto col_meta = prev_->get_col_offset(group_col);
                        memcpy(new_record->data + curr_offset, 
                               record->data + col_meta.offset, 
                               col_meta.len);
                        curr_offset += col_meta.len;
                        col_idx++;
                    }
                    
                    // 初始化聚合列的值
                    for (size_t i = 0; i < sel_cols_.size(); i++) {
                        const auto &sel_col = sel_cols_[i];
                        auto col_meta = prev_->get_col_offset(sel_col);
                        AggValue agg_value(col_meta.type, sel_col.aggFuncType);
                        updateAggValue(agg_value, record->data + col_meta.offset, col_meta);

                        // 写入初始值
                        if (sel_col.aggFuncType == ast::AggFuncType::AGG_COUNT) {
                            *(int32_t*)(new_record->data + curr_offset) = std::get<int32_t>(agg_value.value);
                        } else if (col_meta.type == TYPE_INT) {
                            *(int32_t*)(new_record->data + curr_offset) = std::get<int32_t>(agg_value.value);
                        } else if (col_meta.type == TYPE_FLOAT) {
                            *(float*)(new_record->data + curr_offset) = std::get<float>(agg_value.value);
                        }
                        curr_offset += col_meta.len;
                    }
                    
                    group_results_[group_key] = std::make_pair(std::move(new_record), 1);
                } else {
                    // 更新已存在分组的聚合值
                    auto &existing_record = group_results_[group_key].first;
                    group_results_[group_key].second++;
                    size_t curr_offset = 0;
                    size_t col_idx = 0;
                    
                    // 跳过group by列
                    for (const auto &group_col : group_by_cols_) {
                        auto col_meta = prev_->get_col_offset(group_col);
                        curr_offset += col_meta.len;
                        col_idx++;
                    }
                    
                    // 更新聚合值
                    for (size_t i = 0; i < sel_cols_.size(); i++) {
                        const auto &sel_col = sel_cols_[i];
                        auto col_meta = prev_->get_col_offset(sel_col);
                        
                        // 读取当前聚合值
                        AggValue agg_value(col_meta.type, sel_col.aggFuncType);
                        if (sel_col.aggFuncType == ast::AggFuncType::AGG_COUNT) {
                            agg_value.value = *(int32_t*)(existing_record->data + curr_offset);
                        } else if (col_meta.type == TYPE_INT) {
                            agg_value.value = *(int32_t*)(existing_record->data + curr_offset);
                        } else if (col_meta.type == TYPE_FLOAT) {
                            agg_value.value = *(float*)(existing_record->data + curr_offset);
                        }
                        
                        // 更新聚合值
                        updateAggValue(agg_value, record->data + col_meta.offset, col_meta);
                        
                        // 写回更新后的值
                        if (sel_col.aggFuncType == ast::AggFuncType::AGG_COUNT) {
                            *(int32_t*)(existing_record->data + curr_offset) = std::get<int32_t>(agg_value.value);
                        } else if (col_meta.type == TYPE_INT) {
                            *(int32_t*)(existing_record->data + curr_offset) = std::get<int32_t>(agg_value.value);
                        } else if (col_meta.type == TYPE_FLOAT) {
                            *(float*)(existing_record->data + curr_offset) = std::get<float>(agg_value.value);
                        }
                        curr_offset += col_meta.len;
                    }
                }
                
                prev_->nextTuple();
            }

            // TODO: 对AVG类型进行最终的除法计算
            size_t curr_offset = 0;
            size_t col_idx = 0;
            for (const auto &group_col : group_by_cols_) {
                auto col_meta = prev_->get_col_offset(group_col);
                curr_offset += col_meta.len;
                col_idx++;
            }
            for (auto& group_pair : group_results_) {
                auto& record = group_pair.second.first;
                auto& count = group_pair.second.second;
                if (count > 0) {
                    size_t curr_offset2 = 0;
                    for (const auto &sel_col : sel_cols_) {
                        auto col_meta = prev_->get_col_offset(sel_col);
                        if (sel_col.aggFuncType == ast::AggFuncType::AGG_AVG) {
                            if (col_meta.type == TYPE_INT) {
                                *(int32_t*)(record->data + curr_offset + curr_offset2) /= count;
                            } else if (col_meta.type == TYPE_FLOAT) {
                                *(float*)(record->data + curr_offset + curr_offset2) /= count;
                            }
                        }
                        curr_offset2 += col_meta.len;
                    }
                }
            }
        }
};
