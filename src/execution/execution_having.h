#pragma once
#include "execution_defs.h"
#include "execution_manager.h"
#include "executor_abstract.h"
#include "parser/ast.h"

class HavingPlanExecutor : public AbstractExecutor {
private:
    std::unique_ptr<AbstractExecutor> prev_;
    std::vector<Condition> having_conds_;  // having条件表达式
    bool is_first_;           // 是否是第一次调用
    std::vector<ColMeta> cols_;  // 输出的列元数据
    size_t len_;              // 输出记录的长度

public:
    HavingPlanExecutor(std::unique_ptr<AbstractExecutor> prev, std::vector<Condition> having_expr) 
        : prev_(std::move(prev)), having_conds_(std::move(having_expr)), is_first_(true) {
        // 复制前一个执行器的列信息
        cols_ = prev_->cols();
        len_ = prev_->tupleLen();
    }

    void beginTuple() override {
        if (is_first_) {
            prev_->beginTuple();
            is_first_ = false;

            while (!prev_->is_end()) {
                auto record = prev_->Next();
                if (!record) continue;

                if (evaluateHavingConditions(record.get())) {
                    break;
                }
                prev_->nextTuple();
            }
        }
    }

    void nextTuple() override {
        prev_->nextTuple();
    }

    std::unique_ptr<RmRecord> Next() override {
        return prev_->Next();
    }

    bool is_end() const override {
        while (!prev_->is_end()) {
            auto record = prev_->Next();
            if (!record) continue;

            if (evaluateHavingConditions(record.get())) {
                return false;
            }
            prev_->nextTuple();
        }
        return true;
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
        return "HavingPlanExecutor"; 
    }

    Rid &rid() override { 
        return _abstract_rid; 
    }

private:
    // 计算having条件表达式的值
    bool evaluateHavingConditions(RmRecord* record) const {
        for (auto& cond : having_conds_) {
            if (!evaluateHavingCondition(&cond, record)) {
                return false;
            }
        }
        return true;
    }

    // 递归计算表达式的值
    bool evaluateHavingCondition(const Condition* cond, RmRecord* record) const {
        if (!cond) return true;

        auto left = getValueFromRecord(cond->lhs_col, record);

        std::variant<int32_t, float> right;
        if (cond->is_rhs_val) {
            if (cond->rhs_val.type == TYPE_INT) {
                right = cond->rhs_val.int_val;
            } else if (cond->rhs_val.type == TYPE_FLOAT) {
                right = cond->rhs_val.float_val;
            }
        } else {
            right = getValueFromRecord(cond->rhs_col, record);
        }

        switch (cond->op) {
            case OP_EQ: {                
                return left == right;
            }
            case OP_NE: {                
                return left != right;
            }
            case OP_LT: {                
                return left < right;
            }
            case OP_GT: {                
                return left > right;
            }
            case OP_LE: {                
                return left <= right;
            }
            case OP_GE: {                
                return left >= right;
            }
            default:
                return false;
        }
    }

    // 从记录中获取值
    std::variant<int32_t, float> getValueFromRecord(const TabCol& col, RmRecord* record) const {
        auto col_meta = prev_->get_col_offset(col);
            
        if (col_meta.type == TYPE_INT) {
            return *(int32_t*)(record->data + col_meta.offset);
        } else if (col_meta.type == TYPE_FLOAT) {
            return *(float*)(record->data + col_meta.offset);
        }
        
        // 默认返回0
        return 0;
    }
        
};