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
    /** TODO: 检查表是否存在 */
    // sqb: down! 5.24
    for (auto &tab_name : query->tables) {
      if (!sm_manager_->db_.is_table(tab_name)) {
        throw TableNotFoundError(tab_name);
      }
    }

    // 处理target list，再target list中添加上表名，例如 a.id
    for (auto &sv_sel_col : x->cols) {
      // 如果 col 为 AggCol 类型
      if (auto agg_col = std::dynamic_pointer_cast<ast::AggCol>(sv_sel_col)) {
        TabCol tab_agg_col = {.tab_name = agg_col->tab_name,
                                .col_name = agg_col->col_name,
                                .alias = agg_col->alias,
                                .aggFuncType = static_cast<ast::AggFuncType>(agg_col->agg_type)};
        query->cols.push_back(tab_agg_col);
        x->has_agg = true;
      } else {
        TabCol sel_col = {.tab_name = sv_sel_col->tab_name,
                        .col_name = sv_sel_col->col_name,
                        .alias = "",
                        .aggFuncType = ast::AGG_INVALID};
      query->cols.push_back(sel_col);
      }
    }

    std::vector<ColMeta> all_cols;
    get_all_cols(query->tables, all_cols);
    if (query->cols.empty()) {
      // select all columns
      for (auto &col : all_cols) {
        TabCol sel_col = {.tab_name = col.tab_name, .col_name = col.name};
        query->cols.push_back(sel_col);
      }
    } else {
      // infer table name from column name
      for (auto &sel_col : query->cols) {
        if (sel_col.col_name == "*") {
          continue;
        }
        sel_col = check_column(all_cols, sel_col);  // 列元数据校验
      }
    }

    // 处理group by条件
    for (auto &sv_group_col : x->group_by_cols) {
      TabCol group_col = {.tab_name = sv_group_col->tab_name,
                          .col_name = sv_group_col->col_name,
                          .alias = "",
                          .aggFuncType = ast::AGG_INVALID};
      group_col = check_column(all_cols, group_col);
      query->group_by_cols.push_back(group_col);
    }

    // 处理having条件
    get_having_clause(x->having_conds, query->having_conds);
    check_having_clause(query->tables, query->having_conds);

    // 处理where条件
    get_clause(x->conds, query->conds);
    check_clause(query->tables, query->conds);
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

void Analyze::get_all_cols(const std::vector<std::string> &tab_names,
                           std::vector<ColMeta> &all_cols) {
  for (auto &sel_tab_name : tab_names) {
    // 这里db_不能写成get_db(), 注意要传指针
    const auto &sel_tab_cols = sm_manager_->db_.get_table(sel_tab_name).cols;
    all_cols.insert(all_cols.end(), sel_tab_cols.begin(), sel_tab_cols.end());
  }
}

void Analyze::get_having_clause(
    const std::vector<std::shared_ptr<ast::BinaryExpr>> &sv_conds,
    std::vector<Condition> &conds) {
  conds.clear();
  for (auto &expr : sv_conds) {
    Condition cond;
    if (auto agg_col = std::dynamic_pointer_cast<ast::AggCol>(expr->lhs)) {
      cond.lhs_col = {.tab_name = agg_col->tab_name,
                      .col_name = agg_col->col_name,
                      .alias = agg_col->alias,
                      .aggFuncType = agg_col->agg_type};
    } else {
      cond.lhs_col = {.tab_name = expr->lhs->tab_name,
                    .col_name = expr->lhs->col_name};
    }
    
    cond.op = convert_sv_comp_op(expr->op);
    if (auto rhs_val = std::dynamic_pointer_cast<ast::Value>(expr->rhs)) {
      cond.is_rhs_val = true;
      cond.rhs_val = convert_sv_value(rhs_val);
    } else if (auto rhs_col = std::dynamic_pointer_cast<ast::Col>(expr->rhs)) {
      if (auto agg_col = std::dynamic_pointer_cast<ast::AggCol>(rhs_col)) {
        cond.rhs_col = {.tab_name = agg_col->tab_name,
                        .col_name = agg_col->col_name,
                        .alias = agg_col->alias,
                        .aggFuncType = agg_col->agg_type};
      } else {
        cond.rhs_col = {.tab_name = rhs_col->tab_name,
                        .col_name = rhs_col->col_name};
      }
    }
    conds.push_back(cond);
  }
}

void Analyze::get_clause(
    const std::vector<std::shared_ptr<ast::BinaryExpr>> &sv_conds,
    std::vector<Condition> &conds) {
  conds.clear();
  for (auto &expr : sv_conds) {
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
    conds.push_back(cond);
  }
}

void Analyze::check_having_clause(const std::vector<std::string> &tab_names,
                           std::vector<Condition> &conds) {
  // auto all_cols = get_all_cols(tab_names);
  std::vector<ColMeta> all_cols;
  get_all_cols(tab_names, all_cols);
  // Get raw values in where clause
  for (auto &cond : conds) {
    // Infer table name from column name
    ColType lhs_type;
    int lhs_col_len;
    if (cond.lhs_col.col_name != "*") {
      cond.lhs_col = check_column(all_cols, cond.lhs_col);
      TabMeta &lhs_tab = sm_manager_->db_.get_table(cond.lhs_col.tab_name);
      auto lhs_col = lhs_tab.get_col(cond.lhs_col.col_name);
      lhs_type = lhs_col->type;
      lhs_col_len = lhs_col->len;
    } else {
      if(cond.lhs_col.aggFuncType == ast::AGG_COUNT) {
        lhs_type = TYPE_INT;
        lhs_col_len = 4;
      } else {
        // 只有 COUNT 的 col 可以为 *
        throw AmbiguousColumnError(cond.lhs_col.col_name);
      }
    }
    
    if (!cond.is_rhs_val && cond.rhs_col.col_name != "*") {
      cond.rhs_col = check_column(all_cols, cond.rhs_col);
    }
    
    ColType rhs_type;
    if (cond.is_rhs_val) {
      cond.rhs_val.init_raw(lhs_col_len);
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
