/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include <cassert>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "common/common.h"
#include "parser/parser.h"
#include "system/sm.h"

class Query {
 public:
  std::shared_ptr<ast::TreeNode> parse;
  // TODO jointree
  std::vector<Condition> join_conds;

  JoinType join_type_{JoinType::INNER_JOIN};
  // where条件
  std::vector<Condition> conds;
  // 投影列
  std::vector<TabCol> cols;
  // 表名
  std::vector<std::string> tables;
  // update 的set 值
  std::vector<SetClause> set_clauses;
  // insert 的values值
  std::vector<Value> values;
  // group by 条件
  std::vector<TabCol> group_by_cols;
  // having 条件
  std::vector<Condition> having_conds;
  // order by 条件
  OrderBys order_bys;

  // 是否全选，即*，用于EXPLAIN里打印*的情况（而不是把所有列都打印出来）
  bool select_all{false};

  // sqb explain 标识
  bool need_explain{false};

  Query() {}
};

class Analyze {
 private:
  SmManager *sm_manager_;

 public:
  Analyze(SmManager *sm_manager) : sm_manager_(sm_manager) {}
  ~Analyze() {}

  std::shared_ptr<Query> do_analyze(std::shared_ptr<ast::TreeNode> root);

 private:
  TabCol check_column(const std::vector<ColMeta> &all_cols, TabCol target);
  TabCol check_column4semi_join(const std::vector<ColMeta> &all_cols, TabCol target);
  void get_all_cols(const std::vector<std::string> &tab_names, std::vector<ColMeta> &all_cols);
  void get_all_cols_of_left_tab(const std::string &tab_name, std::vector<ColMeta> &all_cols);
  void get_clause(const std::vector<std::shared_ptr<ast::BinaryExpr>> &sv_conds, std::vector<Condition> &conds);
  void get_clause2(const std::vector<std::shared_ptr<ast::JoinExpr>> &sv_conds,
                   std::vector<Condition> &conds);  // 给jointree的cond
  void check_clause(const std::vector<std::string> &tab_names, std::vector<Condition> &conds);
  Value convert_sv_value(const std::shared_ptr<ast::Value> &sv_val);
  CompOp convert_sv_comp_op(ast::SvCompOp op);
  void get_having_clause(const std::vector<std::shared_ptr<ast::BinaryExpr>> &sv_conds, std::vector<Condition> &conds);
  void check_having_clause(const std::vector<std::string> &tab_names, std::vector<Condition> &conds,
                           const std::vector<TabCol> &group_by_cols);
};
