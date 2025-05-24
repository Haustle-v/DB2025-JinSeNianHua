/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include "common/common.h"
#include "execution_defs.h"
#include "index/ix.h"
#include "system/sm.h"

class AbstractExecutor {
 public:
  Rid _abstract_rid;

  Context *context_;

  virtual ~AbstractExecutor() = default;

  virtual size_t tupleLen() const { return 0; };

  virtual const std::vector<ColMeta> &cols() const {
    std::vector<ColMeta> *_cols = nullptr;
    return *_cols;
  };

  virtual std::string getType() { return "AbstractExecutor"; };

  virtual void beginTuple() {};

  virtual void nextTuple() {};

  virtual bool is_end() const { return true; };

  virtual Rid &rid() = 0;

  virtual std::unique_ptr<RmRecord> Next() = 0;

  virtual ColMeta get_col_offset(const TabCol &target) { return ColMeta(); };

  std::vector<ColMeta>::const_iterator get_col(
      const std::vector<ColMeta> &rec_cols, const TabCol &target) {
    auto pos =
        std::find_if(rec_cols.begin(), rec_cols.end(), [&](const ColMeta &col) {
          return col.tab_name == target.tab_name && col.name == target.col_name;
        });
    if (pos == rec_cols.end()) {
      throw ColumnNotFoundError(target.tab_name + '.' + target.col_name);
    }
    return pos;
  }

  //  sqb: 检查记录是否符合所有条件  5.24
  bool check_conds(std::vector<ColMeta> &rec_cols,
                   const std::vector<Condition> &conds,
                   const RmRecord *rec_ptr) {
    for (auto &single_cond : conds) {
      // 不满足单个条件 直接false
      if (!check_single_cond(rec_cols, single_cond, rec_ptr)) {
        return false;
      }
    }
    return true;
  }

  //  sqb: 检查记录是否符合单个条件 5.24
  bool check_single_cond(const std::vector<ColMeta> &rec_cols,
                         const Condition single_cond, const RmRecord *rec_ptr) {
    auto lhs_col = get_col(rec_cols, single_cond.lhs_col);
    char *lhs = rec_ptr->data + lhs_col->offset;
    char *rhs = nullptr;
    ColType rhs_type;
    if (single_cond.is_rhs_val) {
      rhs_type = single_cond.rhs_val.type;
      rhs = single_cond.rhs_val.raw->data;
    } else {
      auto rhs_col = get_col(rec_cols, single_cond.rhs_col);
      rhs_type = rhs_col->type;
      rhs = rec_ptr->data + rhs_col->offset;
    }
    assert(lhs_col->type == rhs_type && "check cond with different type");
    int cmp = ix_compare(lhs, rhs, rhs_type, lhs_col->len);
    switch (single_cond.op) {
      case OP_EQ: {
        return cmp == 0;
      }
      case OP_NE: {
        return cmp != 0;
      }
      case OP_LT: {
        return cmp < 0;
      }
      case OP_GT: {
        return cmp > 0;
      }
      case OP_LE: {
        return cmp <= 0;
      }
      case OP_GE: {
        return cmp >= 0;
      }
      default:
        throw InternalError("check cond on unsupport operand");
    }
    return true;
  }
};