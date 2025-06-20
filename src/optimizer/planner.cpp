/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "planner.h"
#include "explain.h"

#include <memory>
#include <fstream>
#include <iostream>
#include <string>
#include "execution/executor_delete.h"
#include "execution/executor_index_scan.h"
#include "execution/executor_insert.h"
#include "execution/executor_nestedloop_join.h"
#include "execution/executor_projection.h"
#include "execution/executor_seq_scan.h"
#include "execution/executor_update.h"
#include "index/ix.h"
#include "record_printer.h"

// 目前的索引匹配规则为：完全匹配索引字段，且全部为单点查询，不会自动调整where条件的顺序
bool Planner::get_index_cols(std::string tab_name, std::vector<Condition> curr_conds, std::vector<std::string>& index_col_names) {
    index_col_names.clear();
    for(auto& cond: curr_conds) {
        if(cond.is_rhs_val && cond.op == OP_EQ && cond.lhs_col.tab_name.compare(tab_name) == 0)
            index_col_names.push_back(cond.lhs_col.col_name);
    }
    TabMeta& tab = sm_manager_->db_.get_table(tab_name);
    if(tab.is_index(index_col_names)) return true;
    return false;
}

/**
 * @brief 表算子条件谓词生成
 *
 * @param conds 条件
 * @param tab_names 表名
 * @return std::vector<Condition>
 */
std::vector<Condition> pop_conds(std::vector<Condition> &conds, std::string tab_names) {
    // auto has_tab = [&](const std::string &tab_name) {
    //     return std::find(tab_names.begin(), tab_names.end(), tab_name) != tab_names.end();
    // };
    std::vector<Condition> solved_conds;
    auto it = conds.begin();
    while (it != conds.end()) {
        if ((tab_names.compare(it->lhs_col.tab_name) == 0 && it->is_rhs_val) || (it->lhs_col.tab_name.compare(it->rhs_col.tab_name) == 0)) {
            solved_conds.emplace_back(std::move(*it));
            it = conds.erase(it);
        } else {
            it++;
        }
    }
    return solved_conds;
}

int push_conds(Condition *cond, std::shared_ptr<Plan> plan)
{
    if(auto x = std::dynamic_pointer_cast<ScanPlan>(plan))
    {
        if(x->tab_name_.compare(cond->lhs_col.tab_name) == 0) {
            return 1;
        } else if(x->tab_name_.compare(cond->rhs_col.tab_name) == 0){
            return 2;
        } else {
            return 0;
        }
    }
    else if(auto x = std::dynamic_pointer_cast<JoinPlan>(plan))
    {
        int left_res = push_conds(cond, x->left_);
        // 条件已经下推到左子节点
        if(left_res == 3){
            return 3;
        }
        int right_res = push_conds(cond, x->right_);
        // 条件已经下推到右子节点
        if(right_res == 3){
            return 3;
        }
        // 左子节点或右子节点有一个没有匹配到条件的列
        if(left_res == 0 || right_res == 0) {
            return left_res + right_res;
        }
        // 左子节点匹配到条件的右边
        if(left_res == 2) {
            // 需要将左右两边的条件变换位置
            std::map<CompOp, CompOp> swap_op = {
                {OP_EQ, OP_EQ}, {OP_NE, OP_NE}, {OP_LT, OP_GT}, {OP_GT, OP_LT}, {OP_LE, OP_GE}, {OP_GE, OP_LE},
            };
            std::swap(cond->lhs_col, cond->rhs_col);
            cond->op = swap_op.at(cond->op);
        }
        x->conds_.emplace_back(std::move(*cond));
        return 3;
    }
    return false;
}

std::shared_ptr<Plan> pop_scan(int *scantbl, std::string table, std::vector<std::string> &joined_tables, 
                std::vector<std::shared_ptr<Plan>> plans)
{
    for (size_t i = 0; i < plans.size(); i++) {
        auto x = std::dynamic_pointer_cast<ScanPlan>(plans[i]);
        if(x->tab_name_.compare(table) == 0)
        {
            scantbl[i] = 1;
            joined_tables.emplace_back(x->tab_name_);
            return plans[i];
        }
    }
    return nullptr;
}


std::shared_ptr<Query> Planner::logical_optimization(std::shared_ptr<Query> query, Context *context)
{
    
    //TODO 实现逻辑优化规则

    return query;
}

std::shared_ptr<Plan> Planner::physical_optimization(std::shared_ptr<Query> query, Context *context)
{
    std::shared_ptr<Plan> plan = make_one_rel(query);
    
    // 其他物理优化

    // 处理orderby
    plan = generate_sort_plan(query, std::move(plan)); 

    return plan;
}


Condition reverse_condition(const Condition& cond) {
    static const std::map<CompOp, CompOp> swap_op = {
        {OP_EQ, OP_EQ}, {OP_NE, OP_NE},
        {OP_LT, OP_GT}, {OP_GT, OP_LT},
        {OP_LE, OP_GE}, {OP_GE, OP_LE}};

    Condition reversed = cond;
    std::swap(reversed.lhs_col, reversed.rhs_col);
    reversed.op = swap_op.at(reversed.op);  // 安全使用 map 查表
    return reversed;
}

// 找到 需要新添加的(右)表 与 已经在(左)jointree中所有的表 相关的连接条件
std::vector<Condition> extract_join_conditions(std::vector<Condition>& joinconds,
                                               const std::vector<std::string>& tables,
                                               int index,         // index指的是目前处理到哪一张右表了
                                                bool& reversed){
    std::vector<Condition> result;
    auto it = joinconds.begin();
    while (it != joinconds.end()) {
        const std::string& cond_left_tab = it->lhs_col.tab_name;
        const std::string& cond_right_tab = it->rhs_col.tab_name;
        const std::string& curr_tab = tables[index];

        bool cond_left_tab_in_jointree = false;
        bool cond_right_tab_in_jointree = false;

        // 看条件的左表或右表是否在jointree的表中(tables[0~index-1])
        for (int i = 0; i <= index-1; ++i) {
            if (cond_left_tab == tables[i]) cond_left_tab_in_jointree = true;
            if (cond_right_tab == tables[i]) cond_right_tab_in_jointree = true;
        }

        // 如果条件的左表已经被添加到(左)jointree里了，并且条件的右表就为当前表，则刚好使我们需要的joincond
        if ((cond_left_tab_in_jointree && cond_right_tab == curr_tab)) {
            result.push_back(*it);
            it = joinconds.erase(it);
        } // 但如果反了，那到时候joincond的lhs(left-hand-side)和rhs肯定会报错，不仅相关的列找不到，连op也会弄反，所以需要reverse
        else if ((cond_right_tab_in_jointree && cond_left_tab == curr_tab)) {
            result.push_back(reverse_condition(*it));
            it = joinconds.erase(it);
            reversed = true;
        } else {
            ++it;
        }
    }  
    return result;
}



std::shared_ptr<Plan> Planner::make_one_rel(std::shared_ptr<Query> query)
{
    auto x = std::dynamic_pointer_cast<ast::SelectStmt>(query->parse);
    std::vector<std::string> tables = query->tables;
    // 直接原地对table按照大小升序排序
    std::sort(tables.begin(), tables.end(), [&](const std::string &a, const std::string &b) {
    return sm_manager_->db_.get_table(a).record_count < sm_manager_->db_.get_table(b).record_count;
    });
    // Scan table , 生成表算子列表tab_nodes
    std::vector<std::shared_ptr<Plan>> table_scan_executors(tables.size());
    // 处理where中的只涉及一个表的条件, 也就是Filter
    for (size_t i = 0; i < tables.size(); i++) {
        auto curr_conds = pop_conds(query->conds, tables[i]);   // curr_conds是只某个表本身的条件（比如a.col>10或者a.col1>a.col2)
        // int index_no = get_indexNo(tables[i], curr_conds);
        std::vector<std::string> index_col_names;       //??这个指的是啥？等于条件的左边的列？干啥用的
        bool index_exist = get_index_cols(tables[i], curr_conds, index_col_names);
        if (index_exist == false) {  // 该表没有索引
            index_col_names.clear();
            table_scan_executors[i] = 
                std::make_shared<ScanPlan>(T_SeqScan, sm_manager_, tables[i], curr_conds, index_col_names);
        } else {  // 存在索引
            table_scan_executors[i] =
                std::make_shared<ScanPlan>(T_IndexScan, sm_manager_, tables[i], curr_conds, index_col_names);
        }
    }
    // 只有一个表，不需要join。
    if(tables.size() == 1)
    {
        return table_scan_executors[0];
    }
    
    auto joinconds = std::move(query->join_conds);     // join的所有条件
    auto conds = std::move(query->conds);              // where条件中, 以防还有不是Filter的条件，比如select * from A join B on A.a=B.b where A.c>B.d
    joinconds.insert(joinconds.end(), conds.begin(), conds.end());

    // 现在思路不一样了：先找表，再找对应连接条件；而不是根据连接条件去找表

    // 第一层连接
    std::shared_ptr<Plan> left = table_scan_executors[0];
    std::shared_ptr<Plan> right =  table_scan_executors[1];
    bool reversed = false;
    std::shared_ptr<Plan> table_join_executors;
    table_join_executors = std::make_shared<JoinPlan>(T_NestLoop, std::move(left), std::move(right), 
                        extract_join_conditions(joinconds, tables, 1, reversed), reversed, query->join_type_);
    
    
    // 其余层连接
    for (int i=2; i<=tables.size()-1;i++){  // i是右表的index
        bool reversed = false;
        table_join_executors = std::make_shared<JoinPlan>(T_NestLoop, std::move(table_join_executors),  // 左深树, 把已连接节点放左边
            std::move(table_scan_executors[i]), extract_join_conditions(joinconds, tables, i, reversed), reversed);
    } 
    // 这里后需要处理！reverse的时候给jointree一个标记，因为赛题要求jointree输出的条件表达式左右顺序不变

    return table_join_executors;

}


std::shared_ptr<Plan> Planner::generate_sort_plan(std::shared_ptr<Query> query, std::shared_ptr<Plan> plan)
{
    auto x = std::dynamic_pointer_cast<ast::SelectStmt>(query->parse);
    if(!x->has_sort) {
        return plan;
    }
    std::vector<std::string> tables = query->tables;
    std::vector<ColMeta> all_cols;
    for (auto &sel_tab_name : tables) {
        // 这里db_不能写成get_db(), 注意要传指针
        const auto &sel_tab_cols = sm_manager_->db_.get_table(sel_tab_name).cols;
        all_cols.insert(all_cols.end(), sel_tab_cols.begin(), sel_tab_cols.end());
    }
    TabCol sel_col;
    for (auto &col : all_cols) {
        if(col.name.compare(x->order->cols->col_name) == 0 )
        sel_col = {.tab_name = col.tab_name, .col_name = col.name};
    }
    return std::make_shared<SortPlan>(T_Sort, std::move(plan), sel_col, 
                                    x->order->orderby_dir == ast::OrderBy_DESC);
}


// 投影下推需要保留的列：Select选择到的列; Scan的cond (也就是Filter条件涉及的列); Join的join_cond
void Planner::projection_pushdown(std::shared_ptr<Plan>& plan, std::vector<TabCol>& cols){
    if (auto proj_plan = std::dynamic_pointer_cast<ProjectionPlan>(plan)){
        size_t original_size = cols.size();
        cols.insert(cols.end(), (proj_plan->sel_cols_).begin(), (proj_plan->sel_cols_).end());
        projection_pushdown(proj_plan->subplan_, cols);
        // 相当于把这层涉及到的条件push出来，因为回到上一层就不需要这些条件了
        cols.resize(original_size);     
    }else if (auto join_plan = std::dynamic_pointer_cast<JoinPlan>(plan)){
        size_t original_size = cols.size();
        for (const auto& cond : join_plan->conds_) {
            cols.push_back(cond.lhs_col);
            cols.push_back(cond.rhs_col);
        }
        //如果左节点是Scan，就检查是否需要添加Proj
        if (auto scan_plan = std::dynamic_pointer_cast<ScanPlan>(join_plan->left_)){
            // 投影保留的列：cols中和当前Scan表相关的列
            std::vector<TabCol> proj_cols;  
            std::unordered_set<std::string> seen_col_names; // 要保证不重复
            for (const auto& col : cols) {
                if (col.tab_name == scan_plan->tab_name_) {
                    if (seen_col_names.insert(col.col_name).second){    // 如果该列没有被推入proj（防止重复）
                        proj_cols.push_back(col);
                    }
            }}
            // 按照测试说明文档的测试点3，哪怕需要选取的列就是这个表所有的列，也需要project，所以把if判断注释了
            // 只能说应该是官方没考虑到这个问题...
            // if (proj_cols.size()<sm_manager_->db_.get_table(scan_plan->tab_name_).cols.size()){
                std::shared_ptr<Plan> proj_scan_plan = std::make_shared<ProjectionPlan>(T_Projection, std::move(scan_plan), std::move(proj_cols));
                join_plan->left_ = std::move(proj_scan_plan);
            // }

        }else{
            projection_pushdown(join_plan->left_, cols);
        }
        // 右节点同理
        if (auto scan_plan = std::dynamic_pointer_cast<ScanPlan>(join_plan->right_)){
            std::vector<TabCol> proj_cols;
            std::unordered_set<std::string> seen_col_names; // 要保证不重复
            for (const auto& col : cols) {
                if (col.tab_name == scan_plan->tab_name_) {
                    if (seen_col_names.insert(col.col_name).second){    // 如果该列没有被推入proj
                        proj_cols.push_back(col);
                    }
            }}

            // if (proj_cols.size()<sm_manager_->db_.get_table(scan_plan->tab_name_).cols.size()){
                std::shared_ptr<Plan> proj_scan_plan = std::make_shared<ProjectionPlan>(T_Projection, std::move(scan_plan), std::move(proj_cols));
                join_plan->right_ = std::move(proj_scan_plan);
            // }
        }else{
            projection_pushdown(join_plan->right_, cols);
        }

        // 如果这一层递归结束要回到上一层了，要push出对应的col，因为肯定这一层需要的col在上一层丕定需要
        cols.resize(original_size);       
    }else{
        std::cout<<"ERROR"<<std::endl;
    }
}


/**
 * @brief select plan 生成
 *
 * @param sel_cols select plan 选取的列
 * @param tab_names select plan 目标的表
 * @param conds select plan 选取条件
 */
std::shared_ptr<Plan> Planner::generate_select_plan(std::shared_ptr<Query> query, Context *context) {
    //逻辑优化
    query = logical_optimization(std::move(query), context);

    //物理优化
    auto sel_cols = query->cols;
    std::shared_ptr<Plan> plannerRoot = physical_optimization(query, context);
    plannerRoot = std::make_shared<ProjectionPlan>(T_Projection, std::move(plannerRoot), 
                                                        std::move(sel_cols), query->select_all);
    std::vector<TabCol> cols_need_retain;
    if (!query->select_all){
        projection_pushdown(plannerRoot, cols_need_retain);
    }


    return plannerRoot;
}

// 生成DDL语句和DML语句的查询执行计划
std::shared_ptr<Plan> Planner::do_planner(std::shared_ptr<Query> query, Context *context)
{
    std::shared_ptr<Plan> plannerRoot;
    if (auto x = std::dynamic_pointer_cast<ast::CreateTable>(query->parse)) {
        // create table;
        std::vector<ColDef> col_defs;
        for (auto &field : x->fields) {
            if (auto sv_col_def = std::dynamic_pointer_cast<ast::ColDef>(field)) {
                ColDef col_def = {.name = sv_col_def->col_name,
                                  .type = interp_sv_type(sv_col_def->type_len->type),
                                  .len = sv_col_def->type_len->len};
                col_defs.push_back(col_def);
            } else {
                throw InternalError("Unexpected field type");
            }
        }
        plannerRoot = std::make_shared<DDLPlan>(T_CreateTable, x->tab_name, std::vector<std::string>(), col_defs);
    } else if (auto x = std::dynamic_pointer_cast<ast::DropTable>(query->parse)) {
        // drop table;
        plannerRoot = std::make_shared<DDLPlan>(T_DropTable, x->tab_name, std::vector<std::string>(), std::vector<ColDef>());
    } else if (auto x = std::dynamic_pointer_cast<ast::CreateIndex>(query->parse)) {
        // create index;
        plannerRoot = std::make_shared<DDLPlan>(T_CreateIndex, x->tab_name, x->col_names, std::vector<ColDef>());
    } else if (auto x = std::dynamic_pointer_cast<ast::DropIndex>(query->parse)) {
        // drop index
        plannerRoot = std::make_shared<DDLPlan>(T_DropIndex, x->tab_name, x->col_names, std::vector<ColDef>());
    } else if (auto x = std::dynamic_pointer_cast<ast::InsertStmt>(query->parse)) {
        // insert;
        plannerRoot = std::make_shared<DMLPlan>(T_Insert, std::shared_ptr<Plan>(),  x->tab_name,  
                                                    query->values, std::vector<Condition>(), std::vector<SetClause>());
    } else if (auto x = std::dynamic_pointer_cast<ast::DeleteStmt>(query->parse)) {
        // delete;
        // 生成表扫描方式
        std::shared_ptr<Plan> table_scan_executors;
        // 只有一张表，不需要进行物理优化了
        // int index_no = get_indexNo(x->tab_name, query->conds);
        std::vector<std::string> index_col_names;
        bool index_exist = get_index_cols(x->tab_name, query->conds, index_col_names);
        
        if (index_exist == false) {  // 该表没有索引
            index_col_names.clear();
            table_scan_executors = 
                std::make_shared<ScanPlan>(T_SeqScan, sm_manager_, x->tab_name, query->conds, index_col_names);
        } else {  // 存在索引
            table_scan_executors =
                std::make_shared<ScanPlan>(T_IndexScan, sm_manager_, x->tab_name, query->conds, index_col_names);
        }

        plannerRoot = std::make_shared<DMLPlan>(T_Delete, table_scan_executors, x->tab_name,  
                                                std::vector<Value>(), query->conds, std::vector<SetClause>());
    } else if (auto x = std::dynamic_pointer_cast<ast::UpdateStmt>(query->parse)) {
        // update;
        // 生成表扫描方式
        std::shared_ptr<Plan> table_scan_executors;
        // 只有一张表，不需要进行物理优化了
        // int index_no = get_indexNo(x->tab_name, query->conds);
        std::vector<std::string> index_col_names;
        bool index_exist = get_index_cols(x->tab_name, query->conds, index_col_names);

        if (index_exist == false) {  // 该表没有索引
        index_col_names.clear();
            table_scan_executors = 
                std::make_shared<ScanPlan>(T_SeqScan, sm_manager_, x->tab_name, query->conds, index_col_names);
        } else {  // 存在索引
            table_scan_executors =
                std::make_shared<ScanPlan>(T_IndexScan, sm_manager_, x->tab_name, query->conds, index_col_names);
        }
        plannerRoot = std::make_shared<DMLPlan>(T_Update, table_scan_executors, x->tab_name,
                                                     std::vector<Value>(), query->conds, 
                                                     query->set_clauses);
    } else if (auto x = std::dynamic_pointer_cast<ast::SelectStmt>(query->parse)) {
        bool need_explain = query->need_explain;
        std::shared_ptr<plannerInfo> root = std::make_shared<plannerInfo>(x);
        // 生成select语句的查询执行计划
        std::shared_ptr<Plan> projection = generate_select_plan(std::move(query), context);
        plannerRoot = std::make_shared<DMLPlan>(T_select, projection, std::string(), std::vector<Value>(),
                                                    std::vector<Condition>(), std::vector<SetClause>());
        // 如果需要解释，就do_explain，并且把tag设置为T_Explain，确保在portal中啥也不做
        if (need_explain){
            auto plannerRoot_dml = std::dynamic_pointer_cast<DMLPlan>(plannerRoot);
            do_explain(plannerRoot_dml, context); 
            plannerRoot->tag = T_Explain;
        }
    } else {
        throw InternalError("Unexpected AST root");
    }
    return plannerRoot;
}