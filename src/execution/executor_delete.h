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

class DeleteExecutor : public AbstractExecutor {
 private:
  TabMeta tab_;                   // 表的元数据
  std::vector<Condition> conds_;  // delete的条件
  RmFileHandle *fh_;              // 表的数据文件句柄
  std::vector<Rid> rids_;         // 需要删除的记录的位置
  std::string tab_name_;          // 表名称
  SmManager *sm_manager_;

 public:
  DeleteExecutor(SmManager *sm_manager, const std::string &tab_name, std::vector<Condition> conds,
                 std::vector<Rid> rids, Context *context) {
    sm_manager_ = sm_manager;
    tab_name_ = tab_name;
    tab_ = sm_manager_->db_.get_table(tab_name);
    fh_ = sm_manager_->fhs_.at(tab_name).get();
    conds_ = conds;
    rids_ = rids;
    context_ = context;
  }

  //   sqb: 这里与update类似 rids就是包含了所有待删除记录 顺序处理即可
  //  处理记录与索引 5.29
  std::unique_ptr<RmRecord> Next() override {
    IxManager *ix_manager_ptr = sm_manager_->get_ix_manager();

    for (auto &rid : rids_) {
      std::unique_ptr<RmRecord> rec_ptr = fh_->get_record(rid, context_);

      //   删除索引
      for (auto &index_meta : tab_.indexes) {
        std::string index_name = ix_manager_ptr->get_index_name(tab_name_, index_meta.cols);
        auto ix_hdl_ptr = sm_manager_->ihs_[index_name].get();
        char key_buffer[index_meta.col_tot_len];
        int offset = 0;
        for (auto &col_meta : index_meta.cols) {
          memcpy(key_buffer + offset, rec_ptr->data + col_meta.offset, col_meta.len);
          offset += col_meta.len;
        }
        ix_hdl_ptr->delete_entry(key_buffer, context_->txn_);
      }

      //   补充版本链 sqb 6.19
      UndoLog undo_log;
      UndoLink undo_link;
      txn_id_t txn_id = context_->txn_->get_transaction_id();
      std::optional<UndoLink> op_undo_link = WalkLinkToTxnLink(rid, context_->txn_mgr_, txn_id);
      if (op_undo_link.has_value() && (*op_undo_link).prev_txn_ == txn_id) {
        // 找到事务对应undo log，进行更改
        UndoLog old_log = context_->txn_mgr_->GetUndoLog(*op_undo_link);
        undo_log = GenerateUpdatedUndoLog(&tab_, rec_ptr.get(), nullptr, old_log);
        undo_link = *op_undo_link;
      } else {
        // 版本链尾需维护版本链 没有值插入默认无效值
        UndoLink pre_link;
        if (op_undo_link.has_value() && (*op_undo_link).prev_txn_ != txn_id) {
          pre_link = *op_undo_link;
        }
        undo_log = GenerateNewUndoLog(&tab_, rec_ptr.get(), nullptr, context_->txn_->get_temp_ts(), pre_link);
      }

      //   删除记录
      fh_->delete_record(rid, context_, rec_ptr.get(), undo_log, undo_link);
    }
    return nullptr;
  }

  Rid &rid() override { return _abstract_rid; }

  std::string getType() override { return "DeleteExecutor"; };
};