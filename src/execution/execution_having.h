#pragma once
#include "execution_defs.h"
#include "execution_manager.h"
#include "executor_abstract.h"
#include "parser/ast.h"
#include <vector>
#include <memory>
#include <variant>   // 新增：用于处理不同类型的值
#include <string>    // 新增：用于支持字符串
#include <stdexcept> // 新增：用于抛出异常

class HavingPlanExecutor : public AbstractExecutor {
private:
    std::unique_ptr<AbstractExecutor> prev_;
    std::vector<Condition> having_conds_;
    std::vector<ColMeta> cols_;
    size_t len_;

    // --- 新增状态变量，用于实现正确的迭代器模型 ---
    bool is_done_; // 标记是否已迭代完成
    std::unique_ptr<RmRecord> current_record_; // 存储当前满足条件的记录

public:
    HavingPlanExecutor(std::unique_ptr<AbstractExecutor> prev, std::vector<Condition> having_expr) 
        : prev_(std::move(prev)), having_conds_(std::move(having_expr)) {
        cols_ = prev_->cols();
        len_ = prev_->tupleLen();
        is_done_ = true; // 初始状态为完成，在 beginTuple 中重置
        current_record_ = nullptr;
    }
    
    // --- 以下是重构后的迭代器核心函数 ---

    void beginTuple() override {
        prev_->beginTuple();
        is_done_ = false;
        current_record_ = nullptr;
        // 寻找第一个满足条件的记录
        advance();
    }

    void nextTuple() override {
        if (!is_done_) {
            // 寻找下一个满足条件的记录
            advance();
        }
    }

    std::unique_ptr<RmRecord> Next() override {
        // 只返回当前已找到的有效记录的副本，不移动迭代器
        if (is_done_ || !current_record_) {
            return nullptr;
        }
        // 如果记录大小完全匹配，可以考虑直接移动
        if (current_record_->size == len_) {
            return std::move(current_record_);
        }
        return std::make_unique<RmRecord>(*current_record_);
    }

    bool is_end() const override {
        // 一个廉价、无副作用的状态检查
        return is_done_;
    }

    // --- 以下函数保持不变或有小幅改动 ---

    ColMeta get_col_offset(const TabCol &target) override {
        return prev_->get_col_offset(target);
    }
    const std::vector<ColMeta> &cols() const override { return cols_; }
    size_t tupleLen() const override { return len_; }
    std::string getType() override { return "HavingPlanExecutor"; }
    Rid &rid() override { return _abstract_rid; }

private:
    // 定义一个通用的值类型，用于比较
    using ValueVariant = std::variant<int32_t, float, std::string>;

    /**
     * @brief 新的私有辅助函数，负责查找下一个满足条件的记录
     * 这是新迭代器模型的核心。
     */
    void advance() {
        current_record_ = nullptr;
        while (!prev_->is_end()) {
            auto record_candidate = prev_->Next();
            // 必须先移动子迭代器，再处理当前记录
            prev_->nextTuple(); 

            if (!record_candidate) {
                continue;
            }

            if (evaluateHavingConditions(record_candidate.get())) {
                // 找到了一个有效的记录，将其保存并返回
                current_record_ = std::move(record_candidate);
                is_done_ = false; // 确保 is_end() 返回 false
                return;
            }
        }
        // 如果循环结束还没有找到记录，说明迭代已完成
        is_done_ = true;
    }

    // 计算having条件表达式的值
    bool evaluateHavingConditions(RmRecord* record) const {
        for (const auto& cond : having_conds_) {
            if (!evaluateHavingCondition(&cond, record)) {
                return false;
            }
        }
        return true;
    }
    
    /**
     * @brief 从记录中获取列的值，已重写以支持字符串并增强鲁棒性
     */
    ValueVariant getValueFromRecord(const TabCol& col, RmRecord* record) const {
        auto col_meta = prev_->get_col_offset(col);
        const char* data_ptr = record->data + col_meta.offset;
            
        if (col_meta.type == TYPE_INT) {
            return *reinterpret_cast<const int32_t*>(data_ptr);
        } else if (col_meta.type == TYPE_FLOAT) {
            return *reinterpret_cast<const float*>(data_ptr);
        } else if (col_meta.type == TYPE_STRING) {
            return std::string(data_ptr, col_meta.len);
        }
        
        throw std::runtime_error("HavingPlanExecutor: Unsupported column type.");
    }

    /**
     * @brief 递归计算表达式的值，已重写以支持跨类型和字符串比较
     */
    bool evaluateHavingCondition(const Condition* cond, RmRecord* record) const {
        if (!cond) return true;

        ValueVariant left = getValueFromRecord(cond->lhs_col, record);

        ValueVariant right;
        if (cond->is_rhs_val) {
            if (cond->rhs_val.type == TYPE_INT) {
                right = cond->rhs_val.int_val;
            } else if (cond->rhs_val.type == TYPE_FLOAT) {
                right = cond->rhs_val.float_val;
            } else if (cond->rhs_val.type == TYPE_STRING) {
                // 假设 Condition 结构中的 Value 也有 .str_val 成员
                right = cond->rhs_val.str_val; 
            } else {
                 throw std::runtime_error("HavingPlanExecutor: Unsupported literal type.");
            }
        } else {
            right = getValueFromRecord(cond->rhs_col, record);
        }

        // 使用 std::visit 安全地处理不同类型组合的比较
        return std::visit([op = cond->op](auto&& lhs_val, auto&& rhs_val) -> bool {
            // 如果两个值都是数值类型 (int, float)
            if constexpr (std::is_arithmetic_v<std::decay_t<decltype(lhs_val)>> && 
                          std::is_arithmetic_v<std::decay_t<decltype(rhs_val)>>) {
                // 自动类型提升到公共类型（如double）进行比较
                using CommonType = std::common_type_t<decltype(lhs_val), decltype(rhs_val)>;
                CommonType c_lhs = lhs_val;
                CommonType c_rhs = rhs_val;
                switch (op) {
                    case OP_EQ: return c_lhs == c_rhs;
                    case OP_NE: return c_lhs != c_rhs;
                    case OP_LT: return c_lhs < c_rhs;
                    case OP_GT: return c_lhs > c_rhs;
                    case OP_LE: return c_lhs <= c_rhs;
                    case OP_GE: return c_lhs >= c_rhs;
                    default:    return false;
                }
            }
            // 如果两个值都是字符串类型
            else if constexpr (std::is_same_v<std::decay_t<decltype(lhs_val)>, std::string> &&
                               std::is_same_v<std::decay_t<decltype(rhs_val)>, std::string>) {
                switch (op) {
                    case OP_EQ: return lhs_val == rhs_val;
                    case OP_NE: return lhs_val != rhs_val;
                    case OP_LT: return lhs_val < rhs_val;
                    case OP_GT: return lhs_val > rhs_val;
                    case OP_LE: return lhs_val <= rhs_val;
                    case OP_GE: return lhs_val >= rhs_val;
                    default:    return false;
                }
            }
            // 其他所有类型组合（如 string 和 int 比较）都视为 false
            else {
                return false;
            }
        }, left, right);
    }
};