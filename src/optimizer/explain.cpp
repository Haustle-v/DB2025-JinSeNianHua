#include "explain.h"
#include "planner.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <iomanip>
// yfs 6.10
const char* compOp2String(CompOp op) {
    switch (op) {
        case OP_EQ: return "=";
        case OP_NE: return "!=";
        case OP_LT: return "<";
        case OP_GT: return ">";
        case OP_LE: return "<=";
        case OP_GE: return ">=";
        default: return "UNKNOWN";
    }
}

// yfs 6.10
std::string value2String(const Value& val) {
    switch (val.type) {
        case ColType::TYPE_INT:
            return std::to_string(val.int_val);  // int -> string
        case TYPE_FLOAT:
            return std::to_string(val.float_val);  // float -> string
        case TYPE_STRING:
            return "'" + val.str_val + "'";  // string 直接返回(再加两个'')
        default:
            return "UNKNOWN_TYPE";
    }
}

// yfs 6.11 按照字典序排序
std::string sort_dict(std::vector<std::string> &strs) {
    std::string string_output = "" ;
    std::sort(strs.begin(), strs.end());
    bool first = true;
    for (const auto &str : strs) {
        if (!first) {string_output += ",";}
        string_output += str;
        first = false;
    }
    return string_output;
}


// 一直找到scan
void find_join_tables(std::vector<std::string>& joined_tables, std::shared_ptr<Plan> plan){ // 可能要用set防止重复
    if (auto proj_plan = std::dynamic_pointer_cast<ProjectionPlan>(plan)){
        find_join_tables(joined_tables, proj_plan->subplan_);
    }else if (auto join_plan = std::dynamic_pointer_cast<JoinPlan>(plan)){
        find_join_tables(joined_tables, join_plan->left_);
        find_join_tables(joined_tables, join_plan->right_);
    }else if (auto scan_plan = std::dynamic_pointer_cast<ScanPlan>(plan)){
        joined_tables.push_back(scan_plan->tab_name_);
    }else{
        std::cout<< "ERROR" <<std::endl;
    }
}

// yfs 6.12 因为EXPLAIN要求输出的时候有别名的全显示别名，所以这里简单判断一下
std::string get_pam_saila(const std::string& tab_name) {
    auto it = pam_saila.find(tab_name);
    if (it != pam_saila.end()) {    // 有别名则用别名
        return it->second;
    } else {
        return tab_name;            // 没有别名则就用表名
    }
}

// Join节点的左右子树如果不同，左子树应该是较靠前的（按Filter Join Project Scan顺序）
PlanTypeOrder get_plan_type_order(const std::shared_ptr<Plan>& plan) {
    if (auto scan_plan = std::dynamic_pointer_cast<ScanPlan>(plan)) {
        if (!scan_plan->conds_.empty()) {
            return FILTER; // 把带条件的 Scan 看成 Filter
        }
        return SCAN;
    } else if (std::dynamic_pointer_cast<JoinPlan>(plan)) {
        return JOIN;
    } else if (std::dynamic_pointer_cast<ProjectionPlan>(plan)) {
        return PROJECTION;
    }
    return UNKNOWN;
}

// 如果相同，按照Filter节点的condition 或 Join节点的tables 或 Project节点的columns 或 Scan节点的table 升序输出
std::string get_sort_key(const std::shared_ptr<Plan>& plan) {
    if (auto scan_plan = std::dynamic_pointer_cast<ScanPlan>(plan)) {
        if (!scan_plan->conds_.empty()){
            std::vector<std::string> temp;
            for (const auto& cond : scan_plan->conds_) {
                temp.push_back(get_pam_saila(cond.lhs_col.tab_name) + "." + cond.lhs_col.col_name + compOp2String(cond.op)
                                + value2String(cond.rhs_val));
            }
            return sort_dict(temp);
        }else{
            return scan_plan->tab_name_;
        }
    } else if (auto join_plan = std::dynamic_pointer_cast<JoinPlan>(plan)) {
        std::vector<std::string> joined_tables;
        find_join_tables(joined_tables, join_plan);
        return sort_dict(joined_tables);
    } else if (auto proj_plan = std::dynamic_pointer_cast<ProjectionPlan>(plan)) {
        std::vector<std::string> temp;
        for (const auto& sel_col : proj_plan->sel_cols_) {
            temp.push_back(get_pam_saila(sel_col.tab_name) + "." + sel_col.col_name);
        }
        return sort_dict(temp);
    }else{
        return "";
    }
}

bool is_left_preferred(const std::shared_ptr<Plan>& left, const std::shared_ptr<Plan>& right) {
    PlanTypeOrder left_type = get_plan_type_order(left);
    PlanTypeOrder right_type = get_plan_type_order(right);

    if (left_type != right_type) {
        return left_type < right_type;  // 较小的优先级更靠前
    }

    // 相同类型，按内容排序
    return get_sort_key(left) < get_sort_key(right);
}

// 要把翻转过的条件转回来，因为EXPLAIN打印需要原始顺序
Condition reverse_condition4explain(const Condition& cond) {
    static const std::map<CompOp, CompOp> swap_op = {
        {OP_EQ, OP_EQ}, {OP_NE, OP_NE},
        {OP_LT, OP_GT}, {OP_GT, OP_LT},
        {OP_LE, OP_GE}, {OP_GE, OP_LE}};

    Condition reversed = cond;
    std::swap(reversed.lhs_col, reversed.rhs_col);
    reversed.op = swap_op.at(reversed.op);  // 安全使用 map 查表
    return reversed;
}

// yfs 6.10
void explain(std::string& explain_output, std::shared_ptr<Plan> plan, const std::string& offset) {
    if (auto dml_plan = std::dynamic_pointer_cast<DMLPlan>(plan)) {
        explain(explain_output, dml_plan->subplan_, offset);

    }else if (auto proj_plan = std::dynamic_pointer_cast<ProjectionPlan>(plan)){    
        explain_output += offset + "Project(columns=[";
        if (proj_plan->select_all_) {   // 需要保留全部的列则输出Project(columns=[*])
            explain_output += "*])\n";
        }else{
            std::vector<std::string> temp;
            for (const auto& sel_col : proj_plan->sel_cols_) {
                temp.push_back(get_pam_saila(sel_col.tab_name) + "." + sel_col.col_name);
            }
            explain_output += sort_dict(temp);
            explain_output += "])\n";
        }

        explain(explain_output, proj_plan->subplan_, offset + "\t");

    }else if (auto join_plan = std::dynamic_pointer_cast<JoinPlan>(plan)){
        explain_output += offset + "Join(tables=[";
        std::vector<std::string> joined_tables;
        find_join_tables(joined_tables, join_plan);     // 找到这个连接下的所有表
        explain_output += sort_dict(joined_tables);
        explain_output += "],condition=[";
        std::vector<std::string> temp;
        for (const auto& cond : join_plan->conds_) {
            Condition cond2 = cond;       // 如果之前被翻转过，那么EXPLAIN的时候要打印原来的顺序
            if (join_plan->reversed_){
                cond2 = reverse_condition4explain(cond);
            }
            temp.push_back(get_pam_saila(cond2.lhs_col.tab_name) + "." + cond2.lhs_col.col_name + compOp2String(cond2.op) 
                        + get_pam_saila(cond2.rhs_col.tab_name) + "." + cond2.rhs_col.col_name);
        }
        explain_output += sort_dict(temp);
        explain_output += "])\n";

        // 要求：Join节点的左右子树如果不同，左子树应该是较靠前的（按Filter Join Project Scan顺序）
        // 其实这里Filter是有Filter的Scan，因为所有的Filter都被推到了最底层（仅高于Scan）
        // 如果相同，按照Scan节点的table，Join节点的tables，Filter节点的condition，Project节点的columns升序输出
        if (is_left_preferred(join_plan->left_, join_plan->right_)){
            explain(explain_output, join_plan->left_, offset + "\t");
            explain(explain_output, join_plan->right_, offset + "\t");
        }else{
            explain(explain_output, join_plan->right_, offset + "\t");
            explain(explain_output, join_plan->left_, offset + "\t");            
        }


    }else if (auto scan_plan = std::dynamic_pointer_cast<ScanPlan>(plan)){
        // 先考虑这个scan有没有Filter
        if (!scan_plan->conds_.empty()){    // 这是在make_one_rel里获取到的curr_cond，只与这个表本身相关，也就是Filter条件
            explain_output += offset + "Filter(condition[";
            std::vector<std::string> temp;
            for (const auto& cond : scan_plan->conds_) {
                temp.push_back(get_pam_saila(cond.lhs_col.tab_name) + "." + cond.lhs_col.col_name + compOp2String(cond.op)
                                + value2String(cond.rhs_val));
            }
            explain_output += sort_dict(temp);
            explain_output += "])\n";

            explain_output += offset + "\t" + "Scan(table=" + scan_plan->tab_name_ + ")\n";
        }else{
            explain_output += offset + "Scan(table=" + scan_plan->tab_name_ + ")\n";
        }
        return;

    }else{
        std::cout << "ERROR" << std::endl;
        return;
    }
}

// yfs 6.10
void Planner::do_explain(std::shared_ptr<DMLPlan> plan, Context *context){        // yfs 6.9
    std::string explain_output;
    explain(explain_output, plan, "");

    std::fstream outfile;
    outfile.open("output.txt", std::ios::out | std::ios::app);
    outfile << explain_output;
    outfile.close();

    std::cout << explain_output <<std::endl;
}