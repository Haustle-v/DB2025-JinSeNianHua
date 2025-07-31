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
#include "execution_common.h"  //sqb 6.19 用于支持MVCC
#include "execution_defs.h"
#include "execution_manager.h"
#include "executor_abstract.h"
#include "index/ix.h"
#include "system/sm.h"

class InsertExecutor : public AbstractExecutor {
 private:
  TabMeta tab_;                // 表的元数据
  std::vector<Value> values_;  // 需要插入的数据
  RmFileHandle *fh_;           // 表的数据文件句柄
  std::string tab_name_;       // 表名称
  Rid rid_;                    // 插入的位置，由于系统默认插入时不指定位置，因此当前rid_在插入后才赋值
  SmManager *sm_manager_;

 public:
  InsertExecutor(SmManager *sm_manager, const std::string &tab_name, std::vector<Value> values, Context *context) {
    sm_manager_ = sm_manager;
    tab_ = sm_manager_->db_.get_table(tab_name);
    values_ = values;
    tab_name_ = tab_name;
    if (values.size() != tab_.cols.size()) {
      throw InvalidValueCountError();
    }
    fh_ = sm_manager_->fhs_.at(tab_name).get();
    context_ = context;
  };

  std::unique_ptr<RmRecord> Next() override {
    // // sqb 事务并发控制 6.9
    // if (context_ != nullptr) {
    //   context_->lock_mgr_->lock_exclusive_on_table(context_->txn_, fh_->GetFd());
    // }
    // Make record buffer
    RmRecord rec(fh_->get_file_hdr().record_size);
    for (size_t i = 0; i < values_.size(); i++) {
      auto &col = tab_.cols[i];
      auto &val = values_[i];

      // 添加类型转换逻辑
      if (col.type != val.type) {
        if (col.type == TYPE_FLOAT && val.type == TYPE_INT) {
          // 将整数转换为浮点数
          val.type = TYPE_FLOAT;
          val.float_val = static_cast<float>(val.int_val);
        } else {
          throw IncompatibleTypeError(coltype2str(col.type), coltype2str(val.type));
        }
      }

      val.init_raw(col.len);
      memcpy(rec.data + col.offset, val.raw->data, col.len);
    }

    //     // 新增：遍历所有元组，判断是否有内容完全相同的元组
    // {
    //   RmScan scan(fh_);
    //   while (!scan.is_end()) {
    //     Rid cur_rid = scan.rid();
    //     std::unique_ptr<RmRecord> cur_tuple = fh_->get_reconstructed_tuple(cur_rid, context_, tab_);
    //     if (cur_tuple && *cur_tuple == rec) {
    //       // 有相同元组，直接abort
    //       throw TransactionAbortException(context_->txn_->get_transaction_id(), AbortReason::WRITE_CONFLICT);
    //     }
    //     scan.next();
    //   }
    // }

    // 一次性预读最大长度
    int max_index_len = 0;

    // sqb 添加索引唯一性检查 注意先检查所有索引再插入数据 不能边检查边插入
    bool reuse_key = false;
    IxManager *ix_manager_ptr = sm_manager_->get_ix_manager();
    for (auto &index_meta : tab_.indexes) {
      std::string index_name = ix_manager_ptr->get_index_name(tab_name_, index_meta.cols);
      auto ix_hdl_ptr = sm_manager_->ihs_[index_name].get();
      char key_buffer[index_meta.col_tot_len];
      int offset = 0;
      for (auto &index_col_meta : index_meta.cols) {
        memcpy(key_buffer + offset, rec.data + index_col_meta.offset, index_col_meta.len);
        offset += index_col_meta.len;
      }
      std::vector<Rid> tmp;
      if (ix_hdl_ptr->get_value(key_buffer, &tmp, context_->txn_)) {
        // throw InternalError("index unique constration error");
        // MVCC需对索引键值复用 只有键值不存在 才会先插入记录再插入索引
        for (auto &rid : tmp) {
          auto [meta, tuple, _] = fh_->get_tuple_and_undoLink(rid, context_);
          if (meta.is_deleted_ &&
              (meta.ts_ <= context_->txn_->get_read_ts() || meta.ts_ == context_->txn_->get_temp_ts())) {
            fh_->update_record(rid, rec.data, context_, &tuple, &tab_);
            reuse_key = true;
          } else {
            // throw TransactionAbortException(context_->txn_->get_transaction_id(), AbortReason::WRITE_CONFLICT);
            throw InternalError("index unique constration error");
          }
        }
      }
      max_index_len = index_meta.col_tot_len > max_index_len ? index_meta.col_tot_len : max_index_len;
    }

    // 复用现有键值 直接返回
    if (reuse_key) {
      return nullptr;
    }

    TupleMeta old_meta;  // 元组现在的tuple_meta，用于事务记录
    // mvcc 对应的插入
    rid_ = fh_->insert_record(rec.data, context_, &tab_, &old_meta);
    // 没有故障恢复的情况下，事务插入直接移出临界区
    if (context_ != nullptr) {
      auto insert_wrec = std::make_unique<WriteRecord>(WType::INSERT_TUPLE, tab_name_, rid_, old_meta);
      context_->txn_->append_write_record(std::move(insert_wrec));
    }

    // Insert into index
    char *key = new char[max_index_len];
    for (size_t i = 0; i < tab_.indexes.size(); ++i) {
      auto &index = tab_.indexes[i];
      auto ih = sm_manager_->ihs_.at(sm_manager_->get_ix_manager()->get_index_name(tab_name_, index.cols)).get();
      //   char *key = new char[index.col_tot_len];
      int offset = 0;
      for (size_t i = 0; i < index.col_num; ++i) {
        memcpy(key + offset, rec.data + index.cols[i].offset, index.cols[i].len);
        offset += index.cols[i].len;
      }
      ih->insert_entry(key, rid_, context_->txn_);
    }
    delete[] key;

    return nullptr;
  }
  Rid &rid() override { return rid_; }
};