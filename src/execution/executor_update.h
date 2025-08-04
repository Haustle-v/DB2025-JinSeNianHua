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
#include "execution_common.h"  //sqb 6.19 用于支持MVCC
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

  std::vector<std::unique_ptr<RmRecord>> old_recs;  // 减少一次读 sqb

 public:
  UpdateExecutor(SmManager *sm_manager, const std::string &tab_name, std::vector<SetClause> set_clauses,
                 std::vector<Condition> conds, std::vector<Rid> rids, std::vector<std::unique_ptr<RmRecord>> recs,
                 Context *context) {
    sm_manager_ = sm_manager;
    tab_name_ = tab_name;
    set_clauses_ = set_clauses;
    tab_ = sm_manager_->db_.get_table(tab_name);
    fh_ = sm_manager_->fhs_.at(tab_name).get();
    conds_ = conds;
    rids_ = rids;
    old_recs = std::move(recs);  // sqb add
    context_ = context;
  }

  // sqb: updata算子里的rids_是经过seq scan扫描得到的
  // 所以在这里更新全部就好 处理数据与索引 5.29
  std::unique_ptr<RmRecord> Next() override {
    // sqb 事务并发控制 6.9
    // if (context_ != nullptr) {
    //   context_->lock_mgr_->lock_exclusive_on_table(context_->txn_, fh_->GetFd());
    // }
    // 提前做类型兼容 并为set 子句的值分配空间 它的空间通过raii管理
    IxManager *ix_manager_ptr = sm_manager_->get_ix_manager();
    for (auto &single_set_clause : set_clauses_) {
      auto col_meta_iter = tab_.get_col(single_set_clause.lhs.col_name);

      if (col_meta_iter->type != single_set_clause.rhs.type) {
        if (col_meta_iter->type == TYPE_FLOAT && single_set_clause.rhs.type == TYPE_INT) {
          single_set_clause.rhs.type = TYPE_FLOAT;
          single_set_clause.rhs.float_val = single_set_clause.rhs.int_val;
        } else {
          throw IncompatibleTypeError(coltype2str(col_meta_iter->type), coltype2str(single_set_clause.rhs.type));
        }
      }
      // 分配空间 跟列保持一致
      single_set_clause.rhs.init_raw(col_meta_iter->len);
    }

    // for (auto &rid : rids_) {
    // std::unique_ptr<RmRecord> rec_ptr = fh_->get_record(rid, context_);
    TupleMeta old_meta;
    RmRecord *pre_rec = new RmRecord(fh_->get_file_hdr().record_size);  // 被update赋值 存当前表堆最新记录
    size_t rec_num = rids_.size();
    for (size_t i = 0; i < rec_num; ++i) {
      Rid &rid = rids_[i];
      std::unique_ptr<RmRecord> &rec_ptr = old_recs[i];  // 当前可见版本记录
      RmRecord old_rec = *rec_ptr;

      //   更新数据
      for (auto &single_set_clause : set_clauses_) {
        auto col_meta_iter = tab_.get_col(single_set_clause.lhs.col_name);
        // sqb 增加set语句是表达式的支持 6.16
        if (single_set_clause.is_expr_) {
          char *lhs_val = rec_ptr->data + col_meta_iter->offset;
          switch (col_meta_iter->type) {
            case TYPE_INT: {
              int ival = *(int *)lhs_val + single_set_clause.rhs.int_val;
              memcpy(lhs_val, &ival, col_meta_iter->len);
              break;
            }
            case TYPE_FLOAT: {
              float fval = *(float *)lhs_val + single_set_clause.rhs.float_val;
              memcpy(lhs_val, &fval, col_meta_iter->len);
              break;
            }
            default: {
              throw InternalError("Unexpected set type in update executor");
              break;
            }
          }
        } else {
          memcpy(rec_ptr->data + col_meta_iter->offset, single_set_clause.rhs.raw->data, col_meta_iter->len);
        }
      }

      // MVCC下，索引键只增加，不删除
      //    处理索引
      //   RmRecord new_rec = *rec_ptr;
      bool reuse_key = false;
      for (auto &index_meta : tab_.indexes) {
        char old_key[index_meta.col_tot_len], new_key[index_meta.col_tot_len];
        std::string index_name = ix_manager_ptr->get_index_name(tab_name_, index_meta.cols);
        auto ix_hdl_ptr = sm_manager_->ihs_[index_name].get();
        // 获取新旧键
        int offset = 0;
        for (auto &col_meta : index_meta.cols) {
          memcpy(old_key + offset, old_rec.data + col_meta.offset, col_meta.len);
          //   memcpy(new_key + offset, new_rec.data + col_meta.offset, col_meta.len);
          memcpy(new_key + offset, rec_ptr->data + col_meta.offset, col_meta.len);
          offset += col_meta.len;
        }
        // 检查键是否相同 相同无需更新 不相同要保证键的唯一性
        if (memcmp(old_key, new_key, index_meta.col_tot_len) != 0) {
          std::vector<Rid> tmp;
          if (ix_hdl_ptr->get_value(new_key, &tmp, context_->txn_)) {
            // throw InternalError("index unique constration error");
            // update情况下 MVCC也应考虑键值复用 这时的复用等价于删除和插入 便于后期加功能
            // 若对性能影响大，那么还是考虑原地更新
            for (auto &ix_rid : tmp) {
              TupleMeta meta = fh_->get_meta(ix_rid);
              if (meta.is_deleted_ &&
                  (meta.ts_ <= context_->txn_->get_read_ts() || meta.ts_ == context_->txn_->get_temp_ts())) {
                fh_->delete_record(ix_rid, context_, pre_rec, &tab_, &old_meta);
                if (context_ != nullptr && !context_->txn_->check_tuple_operated(fh_->GetFd(), ix_rid)) {
                  auto update_wrec =
                      std::make_unique<WriteRecord>(WType::UPDATE_TUPLE, tab_name_, ix_rid, *pre_rec, old_meta);
                  context_->txn_->append_write_record(std::move(update_wrec));
                  context_->txn_->append_write_tuple(fh_->GetFd(), ix_rid);
                }
                Rid new_rid = fh_->insert_record(rec_ptr->data, context_, pre_rec, &tab_, &old_meta);
                // 没有故障恢复的情况下，事务插入直接移出临界区
                if (context_ != nullptr && !context_->txn_->check_tuple_operated(fh_->GetFd(), new_rid)) {
                  auto update_wrec =
                      std::make_unique<WriteRecord>(WType::UPDATE_TUPLE, tab_name_, new_rid, *pre_rec, old_meta);
                  context_->txn_->append_write_record(std::move(update_wrec));
                  context_->txn_->append_write_tuple(fh_->GetFd(), new_rid);
                }

                reuse_key = true;
                ix_hdl_ptr->insert_entry(new_key, new_rid, context_->txn_);
              } else {
                // throw TransactionAbortException(context_->txn_->get_transaction_id(), AbortReason::WRITE_CONFLICT);
                throw InternalError("index unique constration error");
              }
            }
          }

          //   ix_hdl_ptr->delete_entry(old_key, context_->txn_);
          //   ix_hdl_ptr->insert_entry(new_key, rid, context_->txn_);
        }
      }

      //   涉及主键的更改在索引处完成 非主键的更改直接在原地完成
      if (reuse_key) continue;

      //   mvcc下的非主键的更新
      fh_->update_record(rid, rec_ptr->data, context_, pre_rec, &tab_, &old_meta);
      if (context_ != nullptr && !context_->txn_->check_tuple_operated(fh_->GetFd(), rid)) {
        auto update_wrec = std::make_unique<WriteRecord>(WType::UPDATE_TUPLE, tab_name_, rid, *pre_rec, old_meta);
        context_->txn_->append_write_record(std::move(update_wrec));
        context_->txn_->append_write_tuple(fh_->GetFd(), rid);
      }
    }
    delete pre_rec;

    return nullptr;
  }

  Rid &rid() override { return _abstract_rid; }

  std::string getType() override { return "UpdateExecutor"; };
};