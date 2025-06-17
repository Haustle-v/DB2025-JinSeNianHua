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

#include <optional>
#include <vector>

#include "common/common.h"
#include "transaction/transaction.h"
#include "transaction/transaction_manager.h"

// sqb base_tuple代表当前元组 logs是经过检查需要应用的undo 6.16
auto ReconstructTuple(const TabMeta *schema, const RmRecord &base_tuple, const TupleMeta &base_meta,
                      const std::vector<UndoLog> &undo_logs) -> std::optional<RmRecord> {
  // 从当前版本回退得到目标版本的元组 sqb
  // 注意undo log代表之前的状态

  RmRecord current_tuple(base_tuple);
  TupleMeta current_meta(base_meta);

  //   应用所有undo 由调用者负责传入哪些log,由时间戳决定
  auto &cols_meta = schema->cols;
  for (auto &log : undo_logs) {
    // delete的undo仅需改动标识
    current_meta.is_deleted_ = log.is_deleted_;

    // 修改或插入的 undo
    if (!log.is_deleted_) {
      int col_num = log.modified_fields_.size();
      for (size_t i = 0; i < col_num; ++i) {
        if (log.modified_fields_[i]) {
          // 当前列有修改 应用undo
          memcpy(current_tuple.data + cols_meta[i].offset, log.tuple_[i].raw->data, cols_meta[i].len);
        }
      }
    }
  }

  if (current_meta.is_deleted_) {
    return std::nullopt;
  }
  return current_tuple;
}

auto IsWriteWriteConflict(timestamp_t tuple_ts, Transaction *txn) -> bool;

//----------------------------------sqb 参考15445添加下面的辅助函数 6.17----------------------------------

// 给定事务读取时间戳 获取重建元组所需的undo logs
auto CollectUndoLogs(Rid rid, const TupleMeta &base_meta, const RmRecord &base_tuple, std::optional<UndoLink> undo_link,
                     Transaction *txn, TransactionManager *txn_mgr) -> std::vector<UndoLog> {
  // 检索该元组的所有撤销日志 直到事务读取时间戳

  std::vector<UndoLog> ret;
  timestamp_t read_ts = txn->get_read_ts();
  // 1. 元组比读取时间戳新 无需undo 返回空
  if (base_meta.ts_ < read_ts && read_ts < TXN_START_ID) {
    return ret;
  }
  // 2. 元组包含当前事务修改，该事务正在读自己改过的元组 同样无需undo
  if (read_ts == txn->get_temp_ts()) {
    return ret;
  }
  // 3. 元组被另一未提交事务修改、或比读取时间戳更新 ，需迭代收集undo logs
  UndoLink link;
  if (undo_link.has_value()) {
    link = undo_link.value();
  }
  while (link.IsValid()) {
    UndoLog log = txn_mgr->GetUndoLog(link);
    // 代表临时时间戳与大于read_ts的
    if (log.ts_ >= read_ts) {
      ret.emplace_back(log);
    } else {
      break;
    }
    link = log.prev_version_;
  }

  return ret;
}

auto GenerateNewUndoLog(const TabMeta *schema, const RmRecord *base_tuple, const RmRecord *target_tuple, timestamp_t ts,
                        UndoLink prev_version) -> UndoLog;

auto GenerateUpdatedUndoLog(const TabMeta *schema, const RmRecord *base_tuple, const RmRecord *target_tuple,
                            const UndoLog &log) -> UndoLog;

// auto GetTupleAndUndoLink()