/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "analyze.h"

/**
 * @description: 分析器，进行语义分析和查询重写，需要检查不符合语义规定的部分
 * @param {shared_ptr<ast::TreeNode>} parse parser生成的结果集
 * @return {shared_ptr<Query>} Query
 */
std::shared_ptr<Query> Analyze::do_analyze(
    std::shared_ptr<ast::TreeNode> parse) {
  std::shared_ptr<Query> query = std::make_shared<Query>();
  if (auto x = std::dynamic_pointer_cast<ast::SelectStmt>(parse)) {
    // 处理表名
    query->tables = std::move(x->tabs);
        if (!x->jointree.empty()) {
        query->join_type_ = x->jointree[0]->type;
    }
    /** TODO: 检查表是否存在 */
    // sqb: down! 5.24
    for (auto &tab_name : query->tables) {
      if (!sm_manager_->db_.is_table(tab_name)) {
        throw TableNotFoundError(tab_name);
      }
    }

    // 处理target list，再target list中添加上表名，例如 a.id
    for (auto &sv_sel_col : x->cols) {
      TabCol sel_col = {.tab_name = sv_sel_col->tab_name,
                        .col_name = sv_sel_col->col_name};
      query->cols.push_back(sel_col);
    }

    std::vector<ColMeta> all_cols;
    std::vector<ColMeta> all_cols_of_left_tab;
    get_all_cols(query->tables, all_cols);
    get_all_cols_of_left_tab(x->jointree[0]->left, all_cols_of_left_tab);

    // 检查列名的选择是否符合反连接的定义
    if (query->join_type_ == JoinType::ANTI_JOIN){
      // infer table name from column name
      for (auto &sel_col : query->cols) {
        sel_col = check_column4semi_join(all_cols_of_left_tab, sel_col);  // 列元数据校验
      }
    }else{
    if (query->cols.empty()) {
      // select all columns
      for (auto &col : all_cols) {
        TabCol sel_col = {.tab_name = col.tab_name, .col_name = col.name};
        query->cols.push_back(sel_col);
      }
    } else {
      // infer table name from column name
      for (auto &sel_col : query->cols) {
        sel_col = check_column(all_cols, sel_col);  // 列元数据校验
      }}
    }

    // 检查列名的选择是否符合半连接的定义
    if (query->join_type_ == JoinType::SEMI_JOIN){
      if (query->cols.empty()) {  // select * 表示 select all
        // select all columns
        for (auto &col : all_cols_of_left_tab) {
        TabCol sel_col = {.tab_name = col.tab_name, .col_name = col.name};
        query->cols.push_back(sel_col);
      }
      }else {
      // infer table name from column name
      for (auto &sel_col : query->cols) {
        sel_col = check_column4semi_join(all_cols_of_left_tab, sel_col);  // 列元数据校验
      }}
    }else{
    if (query->cols.empty()) {
      // select all columns
      for (auto &col : all_cols) {
        TabCol sel_col = {.tab_name = col.tab_name, .col_name = col.name};
        query->cols.push_back(sel_col);
      }
    } else {
      // infer table name from column name
      for (auto &sel_col : query->cols) {
        sel_col = check_column(all_cols, sel_col);  // 列元数据校验
      }}
    }
    // 处理where条件
    get_clause(x->conds, query->conds);
    check_clause(query->tables, query->conds);

    get_clause2(x->jointree, query->join_conds);
    check_clause(query->tables, query->join_conds);   // 检查列名是否存在，以及可能需要推断表名
  } else if (auto x = std::dynamic_pointer_cast<ast::UpdateStmt>(parse)) {
    /** TODO: */
    // sqb :初步处理update 语句 5.24

    // 检查表存在
    if (!sm_manager_->db_.is_table(x->tab_name)) {
      throw TableNotFoundError(x->tab_name);
    }

    //  考虑补充列存在检查 （不一定需要）
    // set原语转换
    for (auto &sv_set_clause : x->set_clauses) {
      SetClause set_clause{.lhs = {x->tab_name, sv_set_clause->col_name},
                           .rhs = convert_sv_value(sv_set_clause->val)};
      query->set_clauses.emplace_back(set_clause);
    }

    // where 条件
    get_clause(x->conds, query->conds);
    check_clause({x->tab_name}, query->conds);

  } else if (auto x = std::dynamic_pointer_cast<ast::DeleteStmt>(parse)) {
    // 处理where条件
    get_clause(x->conds, query->conds);
    check_clause({x->tab_name}, query->conds);
  } else if (auto x = std::dynamic_pointer_cast<ast::InsertStmt>(parse)) {
    // 处理insert 的values值
    for (auto &sv_val : x->vals) {
      query->values.push_back(convert_sv_value(sv_val));
    }
  } else {
    // do nothing
  }
  query->parse = std::move(parse);
  return query;
}

TabCol Analyze::check_column(const std::vector<ColMeta> &all_cols,
                             TabCol target) {
  if (target.tab_name.empty()) {
    // Table name not specified, infer table name from column name
    std::string tab_name;
    for (auto &col : all_cols) {
      if (col.name == target.col_name) {
        if (!tab_name.empty()) {
          throw AmbiguousColumnError(target.col_name);
        }
        tab_name = col.tab_name;
      }
    }
    if (tab_name.empty()) {
      throw ColumnNotFoundError(target.col_name);
    }
    target.tab_name = tab_name;
  } else {
    /** TODO: Make sure target column exists */
    // sqb: down! 5.24
    if (!sm_manager_->db_.get_table(target.tab_name).is_col(target.col_name)) {
      throw ColumnNotFoundError(target.col_name);
    }
  }
  return target;
}

// 列没有指定表明，搜索所有表的所有列来匹配
// 如果select的列为多个表所共有，就会报错AmbiguousColumnError
// 但是semi join应该忽略这种情况，因为列名都是join左边的表
// 为通过测试点4，如果发现cols是其他表的，则报错
TabCol Analyze::check_column4semi_join(const std::vector<ColMeta> &all_cols,  // 左表的所有列
                             TabCol target) {       // select的某一列（这只是一列，对select的列的遍历在函数外）
  if (target.tab_name.empty()) {  // 选择的列没有表名
    // 检查列是否都是左表的
    std::string tab_name;
    for (auto &col : all_cols) {
      if (col.name == target.col_name) {
        tab_name = col.tab_name;
      }
    }
    if (tab_name.empty()) {   // 在左表的所有列中没有匹配到select的列
      throw ChooseColumnOfOtherTableError(target.col_name);
      // std::cout << "failure" << std::endl;
    }
    target.tab_name = tab_name;   // 把表名附带上去了
  } else {
    /** TODO: Make sure target column exists */
    // sqb: down! 5.24
    if (!sm_manager_->db_.get_table(target.tab_name).is_col(target.col_name)) {
      throw ColumnNotFoundError(target.col_name);
    }
  }
  return target;
}

void Analyze::get_all_cols(const std::vector<std::string> &tab_names,
                           std::vector<ColMeta> &all_cols) {
  for (auto &sel_tab_name : tab_names) {
    // 这里db_不能写成get_db(), 注意要传指针
    const auto &sel_tab_cols = sm_manager_->db_.get_table(sel_tab_name).cols;
    all_cols.insert(all_cols.end(), sel_tab_cols.begin(), sel_tab_cols.end());
  }
}

void Analyze::get_all_cols_of_left_tab(const std::string &tab_name,
                           std::vector<ColMeta> &all_cols) {
  // 这里db_不能写成get_db(), 注意要传指针
  const auto &sel_tab_cols = sm_manager_->db_.get_table(tab_name).cols;
  all_cols.insert(all_cols.end(), sel_tab_cols.begin(), sel_tab_cols.end());
}

void Analyze::get_clause(
    const std::vector<std::shared_ptr<ast::BinaryExpr>> &sv_conds,
    std::vector<Condition> &conds) {
  conds.clear();
  for (auto &expr : sv_conds) {
    Condition cond;
    cond.lhs_col = {.tab_name = expr->lhs->tab_name,      // 这个是C++20的写法，但我现在C++17为啥没报错？
                    .col_name = expr->lhs->col_name};
    cond.op = convert_sv_comp_op(expr->op);
    if (auto rhs_val = std::dynamic_pointer_cast<ast::Value>(expr->rhs)) {
      cond.is_rhs_val = true;
      cond.rhs_val = convert_sv_value(rhs_val);
    } else if (auto rhs_col = std::dynamic_pointer_cast<ast::Col>(expr->rhs)) {
      cond.is_rhs_val = false;
      cond.rhs_col = {.tab_name = rhs_col->tab_name,
                      .col_name = rhs_col->col_name};
    }
    conds.push_back(cond);
  }
}

void Analyze::check_clause(const std::vector<std::string> &tab_names,
                           std::vector<Condition> &conds) {
  // auto all_cols = get_all_cols(tab_names);
  std::vector<ColMeta> all_cols;
  get_all_cols(tab_names, all_cols);
  // Get raw values in where clause
  for (auto &cond : conds) {
    // Infer table name from column name
    cond.lhs_col = check_column(all_cols, cond.lhs_col);
    if (!cond.is_rhs_val) {
      cond.rhs_col = check_column(all_cols, cond.rhs_col);
    }
    TabMeta &lhs_tab = sm_manager_->db_.get_table(cond.lhs_col.tab_name);
    auto lhs_col = lhs_tab.get_col(cond.lhs_col.col_name);
    ColType lhs_type = lhs_col->type;
    ColType rhs_type;
    if (cond.is_rhs_val) {
      cond.rhs_val.init_raw(lhs_col->len);
      rhs_type = cond.rhs_val.type;
    } else {
      TabMeta &rhs_tab = sm_manager_->db_.get_table(cond.rhs_col.tab_name);
      auto rhs_col = rhs_tab.get_col(cond.rhs_col.col_name);
      rhs_type = rhs_col->type;
    }

    // sqb: 在这里补充做类型兼容 5.24 注意暂时没考虑浮点数转换为整型
    if (lhs_type != rhs_type) {
      if (lhs_type == TYPE_FLOAT && rhs_type == TYPE_INT) {
        cond.rhs_val.type = TYPE_FLOAT;
        *(float *)(cond.rhs_val.raw->data) = (float)cond.rhs_val.int_val;
      } else {
        throw IncompatibleTypeError(coltype2str(lhs_type),
                                    coltype2str(rhs_type));
      }
    }
  }
}

void Analyze::get_clause2(
    const std::vector<std::shared_ptr<ast::JoinExpr>> &sv_join_exprs,
    std::vector<Condition> &join_conds) {
  join_conds.clear();
  for (auto &sv_conds : sv_join_exprs){     // 遍历JoinExpr的vector
    for (auto &expr : sv_conds->conds){    // 取出每个JoinExpr的cond，后面操作就和上面get_clause一样了。所以，问题在于，根本不需要使用到join的left和right咯
        Condition cond;
        cond.lhs_col = {.tab_name = expr->lhs->tab_name, 
                        .col_name = expr->lhs->col_name};
        cond.op = convert_sv_comp_op(expr->op);
        if (auto rhs_val = std::dynamic_pointer_cast<ast::Value>(expr->rhs)) {
          cond.is_rhs_val = true;
          cond.rhs_val = convert_sv_value(rhs_val);
        } else if (auto rhs_col = std::dynamic_pointer_cast<ast::Col>(expr->rhs)) {
          cond.is_rhs_val = false;
          cond.rhs_col = {.tab_name = rhs_col->tab_name,
                          .col_name = rhs_col->col_name};
        }
        join_conds.push_back(cond);
      }
  }
  
}

Value Analyze::convert_sv_value(const std::shared_ptr<ast::Value> &sv_val) {
  Value val;
  if (auto int_lit = std::dynamic_pointer_cast<ast::IntLit>(sv_val)) {
    val.set_int(int_lit->val);
  } else if (auto float_lit =
                 std::dynamic_pointer_cast<ast::FloatLit>(sv_val)) {
    val.set_float(float_lit->val);
  } else if (auto str_lit = std::dynamic_pointer_cast<ast::StringLit>(sv_val)) {
    val.set_str(str_lit->val);
  } else {
    throw InternalError("Unexpected sv value type");
  }
  return val;
}

CompOp Analyze::convert_sv_comp_op(ast::SvCompOp op) {
  std::map<ast::SvCompOp, CompOp> m = {
      {ast::SV_OP_EQ, OP_EQ}, {ast::SV_OP_NE, OP_NE}, {ast::SV_OP_LT, OP_LT},
      {ast::SV_OP_GT, OP_GT}, {ast::SV_OP_LE, OP_LE}, {ast::SV_OP_GE, OP_GE},
  };
  return m.at(op);
}
