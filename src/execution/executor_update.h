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
#include "execution_defs.h"
#include "execution_manager.h"
#include "executor_abstract.h"
#include "index/ix.h"
#include "system/sm.h"

class UpdateExecutor : public AbstractExecutor {
 private:
  TabMeta tab_;
  std::vector<Condition> conds_;
  RmFileHandle *fh_;
  std::vector<Rid> rids_;
  std::string tab_name_;
  std::vector<SetClause> set_clauses_;
  SmManager *sm_manager_;

 public:
  UpdateExecutor(SmManager *sm_manager, const std::string &tab_name,
                 std::vector<SetClause> set_clauses,
                 std::vector<Condition> conds, std::vector<Rid> rids,
                 Context *context) {
    sm_manager_ = sm_manager;
    tab_name_ = tab_name;
    set_clauses_ = set_clauses;
    tab_ = sm_manager_->db_.get_table(tab_name);
    fh_ = sm_manager_->fhs_.at(tab_name).get();
    conds_ = conds;
    rids_ = rids;
    context_ = context;
  }

  // sqb: updata算子里的rids_是经过seq scan扫描得到的
  // 所以在这里更新全部就好 5.24 注意这里后面还要考虑索引
  std::unique_ptr<RmRecord> Next() override {
    // 提前做类型兼容 并为set 子句的值分配空间 它的空间通过raii管理
    for (auto &single_set_clause : set_clauses_) {
      auto col_meta_iter = tab_.get_col(single_set_clause.lhs.col_name);

      if (col_meta_iter->type != single_set_clause.rhs.type) {
        if (col_meta_iter->type == TYPE_FLOAT &&
            single_set_clause.rhs.type == TYPE_INT) {
          single_set_clause.rhs.type = TYPE_FLOAT;
          single_set_clause.rhs.float_val = single_set_clause.rhs.int_val;
        } else {
          throw IncompatibleTypeError(coltype2str(col_meta_iter->type),
                                      coltype2str(single_set_clause.rhs.type));
        }
      }
      // 分配空间 跟列保持一致
      single_set_clause.rhs.init_raw(col_meta_iter->len);
    }

    for (auto &rid : rids_) {
      std::unique_ptr<RmRecord> rec_ptr = fh_->get_record(rid, context_);
      for (auto &single_set_clause : set_clauses_) {
        auto col_meta_iter = tab_.get_col(single_set_clause.lhs.col_name);
        // 更新
        memcpy(rec_ptr->data + col_meta_iter->offset,
               single_set_clause.rhs.raw->data, col_meta_iter->len);
      }
      fh_->update_record(rid, rec_ptr->data, context_);
    }

    return nullptr;
  }

  Rid &rid() override { return _abstract_rid; }

  std::string getType() override { return "UpdateExecutor"; };
};