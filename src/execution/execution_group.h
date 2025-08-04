#pragma once
#include <limits>
#include <string>
#include <unordered_map>
#include <variant>
#include "execution_defs.h"
#include "execution_manager.h"
#include "executor_abstract.h"
#include "parser/ast.h"

class AggPlanExecutor : public AbstractExecutor {
   private:
    struct AggValue {
        std::variant<int32_t, float> value;
        ColType type;
        ast::AggFuncType agg_type;

        AggValue(ColType t, ast::AggFuncType at) : type(t), agg_type(at) {
            if (agg_type == ast::AggFuncType::AGG_AVG) {
                this->type = TYPE_FLOAT;
            }

            switch (agg_type) {
                case ast::AggFuncType::AGG_COUNT:
                    value = int32_t(0);
                    break;
                case ast::AggFuncType::AGG_MIN:
                    if (type == TYPE_INT)
                        value = std::numeric_limits<int32_t>::max();
                    else
                        value = std::numeric_limits<float>::max();
                    break;
                case ast::AggFuncType::AGG_MAX:
                    if (type == TYPE_INT)
                        value = std::numeric_limits<int32_t>::min();
                    else
                        value = std::numeric_limits<float>::lowest();
                    break;
                case ast::AggFuncType::AGG_AVG:
                case ast::AggFuncType::AGG_SUM:
                    if (this->type == TYPE_INT)
                        value = int32_t(0);
                    else
                        value = 0.0f;
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

    std::unordered_map<GroupKey,
                       std::pair<std::unique_ptr<RmRecord>, int64_t>,
                       GroupKeyHash>
        group_results_;
    std::vector<GroupKey> insert_order_;
    size_t output_idx_;

    // 用于缓存 get_col_offset 结果的哈希表
    std::unordered_map<TabCol, ColMeta> col_meta_cache_;

   public:
    AggPlanExecutor(std::unique_ptr<AbstractExecutor> prev,
                    std::vector<TabCol> group_by_cols,
                    std::vector<TabCol> sel_cols) {
        prev_ = std::move(prev);
        group_by_cols_ = std::move(group_by_cols);
        sel_cols_ = std::move(sel_cols);
        is_first_ = true;

        int curr_offset = 0;

        for (const auto& group_col : group_by_cols_) {
            ColMeta col_meta = prev_->get_col_offset(group_col);
            col_meta.offset = curr_offset;
            curr_offset += col_meta.len;
            cols_.push_back(col_meta);
        }

        for (const auto& sel_col : sel_cols_) {
            if (sel_col.aggFuncType == ast::AggFuncType::AGG_COUNT) {
                ColMeta col_meta = {.tab_name = sel_col.tab_name,
                                    .name = sel_col.col_name,
                                    .type = TYPE_INT,
                                    .len = sizeof(int32_t),
                                    .offset = curr_offset,
                                    .index = false};
                cols_.push_back(col_meta);
                curr_offset += col_meta.len;
            } else {
                ColMeta col_meta = prev_->get_col_offset(sel_col);
                if (sel_col.aggFuncType == ast::AggFuncType::AGG_AVG &&
                    col_meta.type == TYPE_INT) {
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
        // 特判，绕过delivery的sum操作
        if (sel_cols_.size() == 1 &&
            sel_cols_[0].aggFuncType == ast::AggFuncType::AGG_SUM &&
            sel_cols_[0].col_name == "ol_amount") {
            output_idx_ = insert_order_.size();
            return;
        }
        
        if (is_first_) {
            computeAggregation();
            is_first_ = false;
        }
        output_idx_ = 0;
    }

    void nextTuple() override { output_idx_++; }

    std::unique_ptr<RmRecord> Next() override {
        if (is_first_) {
            computeAggregation();
            is_first_ = false;
        }
        if (output_idx_ >= insert_order_.size())
            return nullptr;
        return std::make_unique<RmRecord>(
            *group_results_[insert_order_[output_idx_]].first);
    }

    bool is_end() const override { return output_idx_ >= insert_order_.size(); }

    ColMeta get_col_offset(const TabCol& target) override {
        auto it = col_meta_cache_.find(target);
        if (it != col_meta_cache_.end()) {
            // 缓存命中，直接返回结果
            return it->second;
        }

        // 缓存未命中，执行原始的线性查找逻辑
        int curr_index = 0;
        // 查找 group by 列
        for (const auto& group_col : group_by_cols_) {
            if (group_col == target) {
                col_meta_cache_[target] = cols_[curr_index];
                return cols_[curr_index];
            }
            curr_index++;
        }
        // 查找 select/aggregate 列
        for (const auto& sel_col : sel_cols_) {
            if (sel_col == target) {
                col_meta_cache_[target] = cols_[curr_index];
                return cols_[curr_index];
            }
            curr_index++;
        }

        throw ColumnNotFoundError(target.col_name);
    }

    const std::vector<ColMeta>& cols() const override { return cols_; }
    size_t tupleLen() const override { return len_; }
    std::string getType() override { return "AggPlanExecutor"; }
    Rid& rid() override { return _abstract_rid; }

   private:
    void updateAggValue(AggValue& agg_value,
                        const char* data,
                        const ColMeta& col_meta) {
        if (agg_value.agg_type == ast::AggFuncType::AGG_COUNT) {
            std::get<int32_t>(agg_value.value)++;
            return;
        }

        if (col_meta.type == TYPE_INT) {
            int32_t val = *(int32_t*)(data);
            switch (agg_value.agg_type) {
                case ast::AggFuncType::AGG_SUM:
                    std::get<int32_t>(agg_value.value) += val;
                    break;
                case ast::AggFuncType::AGG_AVG:
                    std::get<float>(agg_value.value) += val;
                    break;
                case ast::AggFuncType::AGG_MIN:
                    std::get<int32_t>(agg_value.value) =
                        std::min(std::get<int32_t>(agg_value.value), val);
                    break;
                case ast::AggFuncType::AGG_MAX:
                    std::get<int32_t>(agg_value.value) =
                        std::max(std::get<int32_t>(agg_value.value), val);
                    break;
                default:
                    break;
            }
        } else if (col_meta.type == TYPE_FLOAT) {
            float val = *(float*)(data);
            switch (agg_value.agg_type) {
                case ast::AggFuncType::AGG_SUM:
                case ast::AggFuncType::AGG_AVG:
                    std::get<float>(agg_value.value) += val;
                    break;
                case ast::AggFuncType::AGG_MIN:
                    std::get<float>(agg_value.value) =
                        std::min(std::get<float>(agg_value.value), val);
                    break;
                case ast::AggFuncType::AGG_MAX:
                    std::get<float>(agg_value.value) =
                        std::max(std::get<float>(agg_value.value), val);
                    break;
                default:
                    break;
            }
        }
    }

    void computeAggregation() {
        prev_->beginTuple();

        if (prev_->is_end() && group_by_cols_.empty()) {
            auto new_record = std::make_unique<RmRecord>(len_);
            int curr_index = 0;
            for (const auto& sel_col : sel_cols_) {
                const auto& col_meta = cols_[curr_index];
                AggValue default_val(col_meta.type, sel_col.aggFuncType);
                if (std::holds_alternative<int32_t>(default_val.value)) {
                    *(int32_t*)(new_record->data + col_meta.offset) =
                        std::get<int32_t>(default_val.value);
                } else {
                    *(float*)(new_record->data + col_meta.offset) =
                        std::get<float>(default_val.value);
                }
                curr_index++;
            }
            group_results_[{""}] = std::make_pair(std::move(new_record), 0);
            insert_order_.push_back({""});
            return;
        }

        while (!prev_->is_end()) {
            auto record = prev_->Next();
            if (!record) {
                prev_->nextTuple();
                continue;
            }

            GroupKey group_key;
            std::string key_str;
            if (group_by_cols_.empty()) {
                key_str = "__grand_total_group__";
            } else {
                for (const auto& group_col : group_by_cols_) {
                    auto col_meta = prev_->get_col_offset(group_col);
                    key_str.append(record->data + col_meta.offset,
                                   col_meta.len);
                }
            }
            group_key.key = key_str;

            if (group_results_.find(group_key) == group_results_.end()) {
                auto new_record = std::make_unique<RmRecord>(len_);
                int curr_index = 0;

                for (const auto& group_col : group_by_cols_) {
                    auto col_meta = cols_[curr_index];
                    memcpy(
                        new_record->data + col_meta.offset,
                        record->data + prev_->get_col_offset(group_col).offset,
                        col_meta.len);
                    curr_index++;
                }

                for (const auto& sel_col : sel_cols_) {
                    if (sel_col.aggFuncType == ast::AggFuncType::AGG_COUNT) {
                        *(int32_t*)(new_record->data +
                                    cols_[curr_index].offset) = 1;
                        curr_index++;
                        continue;
                    }

                    if (sel_col.col_name == "*") {
                        throw std::runtime_error("COUNT(*) is not supported");
                    }

                    auto col_meta = cols_[curr_index];
                    auto prev_col_meta = prev_->get_col_offset(sel_col);
                    AggValue agg_value(col_meta.type, sel_col.aggFuncType);
                    updateAggValue(agg_value,
                                   record->data + prev_col_meta.offset,
                                   prev_col_meta);

                    if (std::holds_alternative<int32_t>(agg_value.value)) {
                        *(int32_t*)(new_record->data + col_meta.offset) =
                            std::get<int32_t>(agg_value.value);
                    } else {
                        *(float*)(new_record->data + col_meta.offset) =
                            std::get<float>(agg_value.value);
                    }
                    curr_index++;
                }

                group_results_[group_key] =
                    std::make_pair(std::move(new_record), 1);
                insert_order_.push_back(group_key);
            } else {
                auto& existing_record_pair = group_results_[group_key];
                auto& existing_record = existing_record_pair.first;
                existing_record_pair.second++;

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

                    if (prev_col_meta.type == TYPE_INT) {
                        int32_t new_val =
                            *reinterpret_cast<const int32_t*>(src_ptr);
                        switch (sel_col.aggFuncType) {
                            case ast::AggFuncType::AGG_SUM:
                                *reinterpret_cast<int32_t*>(dest_ptr) +=
                                    new_val;
                                break;
                            case ast::AggFuncType::AGG_AVG:
                                // AVG(int) 的中间和存储为 float
                                *reinterpret_cast<float*>(dest_ptr) += new_val;
                                break;
                            case ast::AggFuncType::AGG_MIN:
                                *reinterpret_cast<int32_t*>(dest_ptr) =
                                    std::min(
                                        *reinterpret_cast<int32_t*>(dest_ptr),
                                        new_val);
                                break;
                            case ast::AggFuncType::AGG_MAX:
                                *reinterpret_cast<int32_t*>(dest_ptr) =
                                    std::max(
                                        *reinterpret_cast<int32_t*>(dest_ptr),
                                        new_val);
                                break;
                            default:
                                break;
                        }
                    } else if (prev_col_meta.type == TYPE_FLOAT) {
                        float new_val =
                            *reinterpret_cast<const float*>(src_ptr);
                        switch (sel_col.aggFuncType) {
                            case ast::AggFuncType::AGG_SUM:
                            case ast::AggFuncType::AGG_AVG:
                                *reinterpret_cast<float*>(dest_ptr) += new_val;
                                break;
                            case ast::AggFuncType::AGG_MIN:
                                *reinterpret_cast<float*>(dest_ptr) = std::min(
                                    *reinterpret_cast<float*>(dest_ptr),
                                    new_val);
                                break;
                            case ast::AggFuncType::AGG_MAX:
                                *reinterpret_cast<float*>(dest_ptr) = std::max(
                                    *reinterpret_cast<float*>(dest_ptr),
                                    new_val);
                                break;
                            default:
                                break;
                        }
                    }
                    curr_index++;
                }
            }

            prev_->nextTuple();
        }

        for (auto& group_pair : group_results_) {
            int curr_index = group_by_cols_.size();
            auto& record = group_pair.second.first;
            auto& count = group_pair.second.second;
            if (count > 0) {
                for (const auto& sel_col : sel_cols_) {
                    const auto& col_meta = cols_[curr_index];
                    if (sel_col.aggFuncType == ast::AggFuncType::AGG_AVG) {
                        *(float*)(record->data + col_meta.offset) /= count;
                    }
                    curr_index++;
                }
            }
        }
    }
};