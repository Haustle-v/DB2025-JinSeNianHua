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
#include "./parser/alias_map.h"

/**
 * @description: 分析器，进行语义分析和查询重写，需要检查不符合语义规定的部分
 * @param {shared_ptr<ast::TreeNode>} parse parser生成的结果集
 * @return {shared_ptr<Query>} Query
 */
std::shared_ptr<Query> Analyze::do_analyze(std::shared_ptr<ast::TreeNode> parse) {
  std::shared_ptr<Query> query = std::make_shared<Query>();
  if (auto x = std::dynamic_pointer_cast<ast::SelectStmt>(parse)) {
    // 测试
    // if(nullptr == std::dynamic_pointer_cast<ast::AggCol>(x->cols[1])) {
    //   if(x->group_by_cols.size() == 1) {
    //   if(x->cols[1]->col_name != x->group_by_cols[0]->col_name) {
    //     throw RMDBError();
    //   }
    //   }
    // }
    // 处理表名
    query->tables = std::move(x->tabs);
    // 把ast的jointree传递给query
    if (!x->jointree.empty()) {
      query->join_type_ = x->jointree[0]->type;
    }
    // 把ast的need_explain传递给query
    query->need_explain = x->need_explain;

    /** TODO: 检查表是否存在 */
    // sqb: down! 5.24
    for (auto &tab_name : query->tables) {
      if (!sm_manager_->db_.is_table(tab_name)) {
        throw TableNotFoundError(tab_name);
      }
    }

    for (auto &sv_sel_col : x->cols) {
      // 如果 col 为 AggCol 类型
      if (auto agg_col = std::dynamic_pointer_cast<ast::AggCol>(sv_sel_col)) {
        TabCol tab_agg_col = {.tab_name = std::move(agg_col->tab_name),
                              .col_name = std::move(agg_col->col_name),
                              .alias = std::move(agg_col->alias),
                              .aggFuncType = static_cast<ast::AggFuncType>(agg_col->agg_type)};
        query->cols.emplace_back(std::move(tab_agg_col));
        x->has_agg = true;
      } else {
        TabCol sel_col = {.tab_name = std::move(sv_sel_col->tab_name),
                          .col_name = std::move(sv_sel_col->col_name),
                          .alias = "",
                          .aggFuncType = ast::AGG_INVALID};
        query->cols.emplace_back(std::move(sel_col));
      }
    }

    // 如果有GROUP BY子句，也要设置has_agg为true，因为GROUP BY本身就表示这是一个聚合查询
    if (!x->group_by_cols.empty()) {
      x->has_agg = true;
    }

    // 参考修改 减少拷贝
    // // 只在这里计算一次所有列的元数据
    // std::vector<ColMeta> all_cols;
    // get_all_cols(query->tables, all_cols);

    // 处理target list，再target list中添加上表名，例如 a.id
    if (query->join_type_ == JoinType::SEMI_JOIN ||
        query->join_type_ == JoinType::ANTI_JOIN) {  // 检查列名的选择是否符合半连接的定义
      std::vector<ColMeta> all_cols_of_left_tab;
      get_all_cols_of_left_tab(x->jointree[0]->left, all_cols_of_left_tab);

      if (query->cols.empty()) {  // select * 表示 select all
        query->select_all = true;
        // select all columns
        for (auto &col : all_cols_of_left_tab) {
          TabCol sel_col = {
              .tab_name = col.tab_name, .col_name = col.name, .alias = "", .aggFuncType = ast::AGG_INVALID};
          query->cols.push_back(std::move(sel_col));
        }
      } else {
        // infer table name from column name
        for (auto &sel_col : query->cols) {
          sel_col = check_column4semi_join(all_cols_of_left_tab, sel_col);  // 列元数据校验
        }
      }
    } else {
      if (query->cols.empty()) {
        query->select_all = true;
        // select all columns
        for (auto &table_name : query->tables) {
          const auto &table_cols = sm_manager_->db_.get_table(table_name).cols;
          for (auto &col : table_cols) {
            // 初始化这里做拷贝 不做移动
            TabCol sel_col = {
                .tab_name = col.tab_name, .col_name = col.name, .alias = "", .aggFuncType = ast::AGG_INVALID};
            query->cols.emplace_back(std::move(sel_col));
          }
        }
      } else {
        // infer table name from column name
        for (auto &sel_col : query->cols) {
          if (sel_col.col_name == "*") {
            continue;
          }
          check_column(query->tables, sel_col);  // 列元数据校验
        }
      }
    }

    // 处理group by条件
    for (auto &sv_group_col : x->group_by_cols) {
      TabCol group_col = {.tab_name = std::move(sv_group_col->tab_name),
                          .col_name = std::move(sv_group_col->col_name),
                          .alias = "",
                          .aggFuncType = ast::AGG_INVALID};
      check_column(query->tables, group_col);
      query->group_by_cols.emplace_back(std::move(group_col));
    }

    // SELECT 列表中不能出现没有在 GROUP BY 子句中的非聚集列
    if (x->has_agg) {
      for (auto &sel_col : query->cols) {
        if (sel_col.aggFuncType == ast::AGG_INVALID) {
          bool found = false;
          for (auto &group_col : query->group_by_cols) {
            if (sel_col.tab_name == group_col.tab_name && sel_col.col_name == group_col.col_name) {
              found = true;
              break;
            }
          }
          if (!found) {
            // debug test
            throw GroupByError(sel_col.col_name);
          }
        }
      }
    }

    // 处理having条件
    get_having_clause(x->having_conds, query->having_conds);
    check_having_clause(query->tables, query->having_conds, query->group_by_cols);

    // 处理order by条件
    if (x->has_sort) {
      for (auto &order_by : x->order_by) {
        TabCol order_col = {.tab_name = std::move(order_by->col->tab_name),
                            .col_name = std::move(order_by->col->col_name),
                            .alias = "",
                            .aggFuncType = ast::AGG_INVALID};
        check_column(query->tables, order_col);
        query->order_bys.cols.emplace_back(std::move(order_col));
        query->order_bys.is_asc.emplace_back(order_by->orderby_dir == ast::OrderBy_ASC);
      }
      query->order_bys.limit = x->limit;
    }

    // WHERE 子句中不能用聚集函数作为条件表达式
    for (auto &cond : x->conds) {
      if (auto agg_col = std::dynamic_pointer_cast<ast::AggCol>(cond->lhs)) {
        assert(false);
        throw GroupByError(agg_col->col_name);
      }
    }

    // 处理where条件
    get_clause(x->conds, query->conds);
    check_clause(query->tables, query->conds);

    // 性能测试没有semi join
    get_clause2(x->jointree, query->join_conds);
    check_clause(query->tables, query->join_conds);  // 检查列名是否存在，以及可能需要推断表名
  } else if (auto x = std::dynamic_pointer_cast<ast::UpdateStmt>(parse)) {
    /** TODO: */
    // sqb :初步处理update 语句 5.24

    // 检查表存在
    if (!sm_manager_->db_.is_table(x->tab_name)) {
      throw TableNotFoundError(x->tab_name);
    }

    // // 计算该表的所有列元数据
    // std::vector<ColMeta> all_cols;
    // get_all_cols({x->tab_name}, all_cols);

    //  考虑补充列存在检查 （不一定需要）
    // set原语转换
    for (auto &sv_set_clause : x->set_clauses) {
      SetClause set_clause{.lhs = {.tab_name = x->tab_name,
                                   .col_name = std::move(sv_set_clause->col_name),
                                   .alias = "",
                                   .aggFuncType = ast::AGG_INVALID},
                           .rhs = std::move(convert_sv_value(sv_set_clause->val)),
                           .is_expr_ = sv_set_clause->is_expr_};
      query->set_clauses.emplace_back(std::move(set_clause));
    }

    // where 条件
    get_clause(x->conds, query->conds);
    check_clause({x->tab_name}, query->conds);

  } else if (auto x = std::dynamic_pointer_cast<ast::DeleteStmt>(parse)) {
    // // 计算该表的所有列元数据
    // std::vector<ColMeta> all_cols;
    // get_all_cols({x->tab_name}, all_cols);

    // 处理where条件
    get_clause(x->conds, query->conds);
    check_clause({x->tab_name}, query->conds);
  } else if (auto x = std::dynamic_pointer_cast<ast::InsertStmt>(parse)) {
    // 处理insert 的values值
    for (auto &sv_val : x->vals) {
      query->values.emplace_back(std::move(convert_sv_value(sv_val)));
    }
  } else {
    // do nothing
  }
  query->parse = std::move(parse);
  return query;
}

void Analyze::check_column(const std::vector<std::string> &tables, TabCol &target) {
  if (target.tab_name.empty()) {
    // Table name not specified, infer table name from column name
    std::string tab_name;
    for (auto &table_name : tables) {
      const auto &table_cols = sm_manager_->db_.get_table(table_name).cols;
      for (auto &col : table_cols) {
        if (col.name == target.col_name) {
          if (!tab_name.empty()) {
            throw AmbiguousColumnError(target.col_name);
          }
          tab_name = col.tab_name;
        }
      }
    }
    if (tab_name.empty()) {
      throw ColumnNotFoundError(target.col_name);
    }
    target.tab_name = std::move(tab_name);
  } else {
    /** TODO: Make sure target column exists */
    // sqb: down! 5.24
    // yfs 6.11 在这里修改了get_table，如果是用别名找到的，则将别名替换成表
    if (!(sm_manager_->db_.get_table2(target.tab_name).is_col(target.col_name))) {
      throw ColumnNotFoundError(target.col_name);
    }
  }
}

// 列没有指定表明，搜索所有表的所有列来匹配
// 如果select的列为多个表所共有，就会报错AmbiguousColumnError
// 但是semi join应该忽略这种情况，因为列名都是join左边的表
// 为通过测试点4，如果发现cols是其他表的，则报错
TabCol Analyze::check_column4semi_join(const std::vector<ColMeta> &all_cols,  // 左表的所有列
                                       TabCol target) {  // select的某一列（这只是一列，对select的列的遍历在函数外）
  if (target.tab_name.empty()) {                         // 选择的列没有表名
    // 检查列是否都是左表的
    std::string tab_name;
    for (auto &col : all_cols) {
      if (col.name == target.col_name) {
        tab_name = col.tab_name;
      }
    }
    if (tab_name.empty()) {  // 在左表的所有列中没有匹配到select的列
      throw ChooseColumnOfOtherTableError(target.col_name);
      // std::cout << "failure" << std::endl;
    }
    target.tab_name = tab_name;  // 把表名附带上去了
  } else {
    /** TODO: Make sure target column exists */
    // sqb: down! 5.24
    if (!sm_manager_->db_.get_table(target.tab_name).is_col(target.col_name)) {
      throw ColumnNotFoundError(target.col_name);
    }
  }
  return target;
}

void Analyze::get_all_cols(const std::vector<std::string> &tab_names, std::vector<ColMeta> &all_cols) {
  for (auto &sel_tab_name : tab_names) {
    // 这里db_不能写成get_db(), 注意要传指针
    const auto &sel_tab_cols = sm_manager_->db_.get_table(sel_tab_name).cols;
    all_cols.insert(all_cols.end(), sel_tab_cols.begin(), sel_tab_cols.end());
  }
}

void Analyze::get_all_cols_of_left_tab(const std::string &tab_name, std::vector<ColMeta> &all_cols) {
  // 这里db_不能写成get_db(), 注意要传指针
  const auto &sel_tab_cols = sm_manager_->db_.get_table(tab_name).cols;
  all_cols.insert(all_cols.end(), sel_tab_cols.begin(), sel_tab_cols.end());
}

void Analyze::get_having_clause(const std::vector<std::shared_ptr<ast::BinaryExpr>> &sv_conds,
                                std::vector<Condition> &conds) {
  conds.clear();
  for (auto &expr : sv_conds) {
    Condition cond;
    if (auto agg_col = std::dynamic_pointer_cast<ast::AggCol>(expr->lhs)) {
      cond.lhs_col = {.tab_name = std::move(agg_col->tab_name),
                      .col_name = std::move(agg_col->col_name),
                      .alias = std::move(agg_col->alias),
                      .aggFuncType = agg_col->agg_type};
    } else {
      cond.lhs_col = {.tab_name = std::move(expr->lhs->tab_name), .col_name = std::move(expr->lhs->col_name)};
    }

    cond.op = convert_sv_comp_op(expr->op);
    if (auto rhs_val = std::dynamic_pointer_cast<ast::Value>(expr->rhs)) {
      cond.is_rhs_val = true;
      cond.rhs_val = std::move(convert_sv_value(rhs_val));
    } else {
      throw RMDBError("Unexpected sv value type");
    }
    conds.emplace_back(std::move(cond));
  }
}

void Analyze::get_clause(const std::vector<std::shared_ptr<ast::BinaryExpr>> &sv_conds, std::vector<Condition> &conds) {
  conds.clear();
  for (auto &expr : sv_conds) {
    Condition cond;
    cond.lhs_col = {.tab_name = std::move(expr->lhs->tab_name), .col_name = std::move(expr->lhs->col_name)};
    cond.op = convert_sv_comp_op(expr->op);
    if (auto rhs_val = std::dynamic_pointer_cast<ast::Value>(expr->rhs)) {
      cond.is_rhs_val = true;
      cond.rhs_val = std::move(convert_sv_value(rhs_val));
    } else if (auto rhs_col = std::dynamic_pointer_cast<ast::Col>(expr->rhs)) {
      cond.is_rhs_val = false;
      cond.rhs_col = {.tab_name = std::move(rhs_col->tab_name), .col_name = std::move(rhs_col->col_name)};
    }
    conds.emplace_back(std::move(cond));
  }
}

void Analyze::check_having_clause(const std::vector<std::string> &tables, std::vector<Condition> &conds,
                                  const std::vector<TabCol> &group_by_cols) {
  // 直接使用传入的 all_cols，避免重复计算
  // Get raw values in where clause
  for (auto &cond : conds) {
    if (cond.lhs_col.aggFuncType == ast::AGG_INVALID) {
      bool found_in_group_by = false;
      for (const auto &group_col : group_by_cols) {
        if (cond.lhs_col.col_name == group_col.col_name) {
          found_in_group_by = true;
          break;
        }
      }
      if (!found_in_group_by) {
        throw GroupByError(cond.lhs_col.col_name);
      }
    }
    // Infer table name from column name
    ColType lhs_type;
    int lhs_col_len;
    if (cond.lhs_col.col_name != "*") {
      check_column(tables, cond.lhs_col);
      TabMeta &lhs_tab = sm_manager_->db_.get_table(cond.lhs_col.tab_name);
      auto lhs_col = lhs_tab.get_col(cond.lhs_col.col_name);
      lhs_type = lhs_col->type;
      lhs_col_len = lhs_col->len;
    } else {
      if (cond.lhs_col.aggFuncType == ast::AGG_COUNT) {
        lhs_type = TYPE_INT;
        lhs_col_len = 4;
      } else {
        // 只有 COUNT 的 col 可以为 *
        throw AmbiguousColumnError(cond.lhs_col.col_name);
      }
    }

    if (!cond.is_rhs_val && cond.rhs_col.col_name != "*") {
      check_column(tables, cond.rhs_col);
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
        cond.rhs_val.float_val = (float)cond.rhs_val.int_val;
        *(float *)(cond.rhs_val.raw->data) = cond.rhs_val.float_val;
      } else {
        throw IncompatibleTypeError(coltype2str(lhs_type), coltype2str(rhs_type));
      }
    }
  }
}

void Analyze::check_clause(const std::vector<std::string> &tables, std::vector<Condition> &conds) {
  // 直接使用传入的 all_cols，避免重复计算
  // Get raw values in where clause
  for (auto &cond : conds) {
    // Infer table name from column name
    check_column(tables, cond.lhs_col);
    if (!cond.is_rhs_val) {
      check_column(tables, cond.rhs_col);
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
        cond.rhs_val.float_val = (float)cond.rhs_val.int_val;
        *(float *)(cond.rhs_val.raw->data) = cond.rhs_val.float_val;
        //         *(float *)(cond.rhs_val.raw->data) = (float)cond.rhs_val.int_val;
        // cond.rhs_val.type = TYPE_INT;   // yfs 6.10
        // 这里的rhs_val.type我在planner.cpp的value2String需要用到，所以不能变，我这里再改回来了
      } else {
        throw IncompatibleTypeError(coltype2str(lhs_type), coltype2str(rhs_type));
      }
    }
  }
}

void Analyze::get_clause2(const std::vector<std::shared_ptr<ast::JoinExpr>> &sv_join_exprs,
                          std::vector<Condition> &join_conds) {
  join_conds.clear();
  for (auto &sv_conds : sv_join_exprs) {  // 遍历JoinExpr的vector
    for (
        auto &expr :
        sv_conds
            ->conds) {  // 取出每个JoinExpr的cond，后面操作就和上面get_clause一样了。所以，问题在于，根本不需要使用到join的left和right咯
      Condition cond;
      cond.lhs_col = {.tab_name = expr->lhs->tab_name, .col_name = expr->lhs->col_name};
      cond.op = convert_sv_comp_op(expr->op);
      if (auto rhs_val = std::dynamic_pointer_cast<ast::Value>(expr->rhs)) {
        cond.is_rhs_val = true;
        cond.rhs_val = std::move(convert_sv_value(rhs_val));
      } else if (auto rhs_col = std::dynamic_pointer_cast<ast::Col>(expr->rhs)) {
        cond.is_rhs_val = false;
        cond.rhs_col = {.tab_name = rhs_col->tab_name, .col_name = rhs_col->col_name};
      }
      join_conds.emplace_back(std::move(cond));
    }
  }
}

Value Analyze::convert_sv_value(const std::shared_ptr<ast::Value> &sv_val) {
  Value val;
  if (auto int_lit = std::dynamic_pointer_cast<ast::IntLit>(sv_val)) {
    val.set_int(int_lit->val);
  } else if (auto float_lit = std::dynamic_pointer_cast<ast::FloatLit>(sv_val)) {
    val.set_float(float_lit->val);
  } else if (auto str_lit = std::dynamic_pointer_cast<ast::StringLit>(sv_val)) {
    val.set_str(str_lit->val);
  } else {
    throw InternalError("Unexpected sv value type");
  }
  return std::move(val);
}

CompOp Analyze::convert_sv_comp_op(ast::SvCompOp op) {
  static std::map<ast::SvCompOp, CompOp> m = {
      {ast::SV_OP_EQ, OP_EQ}, {ast::SV_OP_NE, OP_NE}, {ast::SV_OP_LT, OP_LT},
      {ast::SV_OP_GT, OP_GT}, {ast::SV_OP_LE, OP_LE}, {ast::SV_OP_GE, OP_GE},
  };
  return m.at(op);
}
