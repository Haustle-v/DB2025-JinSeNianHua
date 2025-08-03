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
inline auto ReconstructTuple(const TabMeta *schema, const RmRecord &base_tuple, const TupleMeta &base_meta,
                             const std::vector<UndoLog> &undo_logs) -> std::optional<RmRecord> {
  // 从当前版本回退得到目标版本的元组 sqb
  // 注意undo log代表之前的状态

  RmRecord current_tuple(base_tuple);
  TupleMeta current_meta(base_meta);

  //   应用所有undo 由调用者负责传入哪些log,由时间戳决定
  auto &cols_meta = schema->cols;
  for (auto &log : undo_logs) {
    // insert的undo仅需改动标识
    current_meta.is_deleted_ = log.is_deleted_;

    // 修改或删除的 undo
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

inline auto IsWriteWriteConflict(timestamp_t tuple_ts, Transaction *txn) -> bool {
  // 自己写自己
  if (tuple_ts == txn->get_temp_ts()) {
    return false;
  }
  //   其它事务在写
  if (tuple_ts > TXN_START_ID) {
    return true;
  }
  // 当前元组版本已经更新
  if (tuple_ts > txn->get_read_ts()) {
    return true;
  }
  //   安全！
  return false;
}

//----------------------------------sqb 参考15445添加下面的辅助函数 6.17----------------------------------

// 给定事务读取时间戳 获取重建元组所需的undo logs
inline auto CollectUndoLogs(const TupleMeta &base_meta, std::optional<UndoLink> undo_link, Transaction *txn,
                            TransactionManager *txn_mgr) -> std::vector<UndoLog> {
  // 检索该元组的所有撤销日志 直到事务读取时间戳

  std::vector<UndoLog> ret;
  timestamp_t read_ts = txn->get_read_ts();

  // 1. 元组比读取时间戳新 无需undo 返回空
  if (base_meta.ts_ <= read_ts && base_meta.ts_ < TXN_START_ID) {
    return ret;
  }
  // 2. 元组包含当前事务修改，该事务正在读自己改过的元组 同样无需undo
  if (base_meta.ts_ == txn->get_temp_ts()) {
    return ret;
  }
  // 3. 元组被另一未提交事务修改、或比读取时间戳更新 ，需迭代收集undo logs
  UndoLink link;
  if (undo_link.has_value()) {
    link = undo_link.value();
  }
  while (link.IsValid()) {
    UndoLog log = txn_mgr->GetUndoLog(link);

    // 由于目前的回滚直接回复 所以版本链检查需跳过abort事务
    if (txn_mgr->CheckIsAbort(link.prev_txn_)) {
      link = log.prev_version_;
      continue;
    }

    // 代表临时时间戳与大于read_ts的
    if (log.ts_ > read_ts) {
      ret.emplace_back(log);
    } else {
      break;
    }
    link = log.prev_version_;
  }

  return ret;
}

inline Value GetValueFromRecord(const TabMeta *schema, const RmRecord *tuple, size_t i) {
  auto &col_meta = schema->cols[i];
  Value val;
  switch (col_meta.type) {
    case TYPE_INT: {
      int ii = *(int *)(tuple->data + col_meta.offset);
      val.set_int(ii);
    } break;
    case TYPE_FLOAT: {
      float ff = *(float *)(tuple->data + col_meta.offset);
      val.set_float(ff);
    } break;
    case TYPE_STRING: {
      std::string ss(tuple->data + col_meta.offset, col_meta.len);
      val.set_str(ss);
    } break;
  }
  val.init_raw(col_meta.len);
  return val;
}

inline auto GenerateNewUndoLog(const TabMeta *schema, const RmRecord *base_tuple, const RmRecord *target_tuple,
                               timestamp_t ts, UndoLink prev_version) -> UndoLog {
  UndoLog log;
  size_t col_num = schema->cols.size();
  //   删除
  if (target_tuple == nullptr) {
    log.is_deleted_ = false;
    log.modified_fields_.resize(col_num, true);
    for (size_t i = 0; i < col_num; ++i) {
      log.tuple_.emplace_back(GetValueFromRecord(schema, base_tuple, i));
    }
  } else if (base_tuple == nullptr) {
    // 插入
    log.is_deleted_ = true;
    log.modified_fields_.resize(col_num, false);
    log.tuple_.resize(col_num, {});
  } else {
    // 更新
    log.is_deleted_ = false;
    log.modified_fields_.resize(col_num, false);

    auto &cols_meta = schema->cols;
    for (size_t i = 0; i < col_num; ++i) {
      char *base_val = base_tuple->data + cols_meta[i].offset;
      char *target_val = target_tuple->data + cols_meta[i].offset;
      if (memcmp(base_val, target_val, cols_meta[i].len) != 0) {
        log.modified_fields_[i] = true;
        log.tuple_.emplace_back(GetValueFromRecord(schema, base_tuple, i));
      } else {
        log.tuple_.emplace_back();
      }
    }
  }
  log.ts_ = ts;
  log.prev_version_ = prev_version;
  log.tuple_test_ = nullptr;
  return log;
}

// 将新修改加入undo log时，应该只有更新或添加，不能有删除！
inline auto GenerateUpdatedUndoLog(const TabMeta *schema, const RmRecord *base_tuple, const RmRecord *target_tuple,
                                   const UndoLog &old_log) -> UndoLog {
  UndoLog updated_log = old_log;
  size_t col_num = schema->cols.size();

  //   新的删除操作 在此之前只可能是插入或更新
  // 插入前的元组必为delete 对应字段皆为空或者说不处理
  // update的undo已保存值修改
  if (target_tuple == nullptr) {
    // 前一操作为插入
    if (old_log.is_deleted_) {
      updated_log.is_deleted_ = true;
      //   updated_log.modified_fields_.clear();
      //   updated_log.tuple_.clear();
    }
    // 前一操作为update
    else {
      updated_log.is_deleted_ = false;
    }
  }
  // 新的更新操作 更新前只能是插入或更新
  else if (base_tuple != nullptr) {
    // 前一操作是插入 让对应字段为空
    if (old_log.is_deleted_ == true) {
      //   updated_log.modified_fields_.clear();
      //   updated_log.tuple_.clear();
    } else {
      // 前一操作是更新 更新需考虑是否修改比较undo log中字段与目标元组的修改
      auto &cols_meta = schema->cols;
      for (size_t i = 0; i < col_num; ++i) {
        if (old_log.modified_fields_[i]) {
          if (old_log.tuple_[i] != GetValueFromRecord(schema, target_tuple, i)) {
            updated_log.modified_fields_[i] = true;
          } else {
            updated_log.modified_fields_[i] = false;
          }
        } else {
          char *base_val = base_tuple->data + cols_meta[i].offset;
          char *target_val = target_tuple->data + cols_meta[i].offset;
          if (memcmp(base_val, target_val, cols_meta[i].len) != 0) {
            updated_log.modified_fields_[i] = true;
            updated_log.tuple_[i] = GetValueFromRecord(schema, base_tuple, i);
          }
        }
      }
    }
  } else {
    // 按理对应插入 插入之前只能是删除 删除的对应字段保留
    updated_log.is_deleted_ = false;
  }
  return updated_log;
}

// 在版本链中找到对应事务的版本链，否则返回版本链最后一个有效链
inline std::optional<UndoLink> WalkLinkToTxnLink(int fd, const Rid &rid, TransactionManager *txn_mgr,
                                                 const txn_id_t txn_id) {
  std::optional<UndoLink> op_undo_link = txn_mgr->GetUndoLink(fd, rid);
  if (!op_undo_link.has_value()) {
    return std::nullopt;
  }
  UndoLink link = op_undo_link.value();
  while (true) {
    if (link.prev_txn_ == txn_id) {
      return link;
    }
    UndoLog log = txn_mgr->GetUndoLog(link);
    if (!log.prev_version_.IsValid()) {
      break;
    }
    link = log.prev_version_;
  }
  return op_undo_link;
}

inline std::tuple<UndoLog, UndoLink> generateUndoLogAndLink(int fd, const Rid &rid, const RmRecord *old_rec,
                                                            const RmRecord *new_rec, const Context *context,
                                                            const TabMeta *schema) {
  UndoLog undo_log;
  UndoLink undo_link;
  txn_id_t txn_id = context->txn_->get_transaction_id();
  std::optional<UndoLink> op_undo_link = WalkLinkToTxnLink(fd, rid, context->txn_mgr_, txn_id);
  if (op_undo_link.has_value() && (*op_undo_link).prev_txn_ == txn_id) {
    // 找到事务对应undo log，进行更改
    UndoLog old_log = context->txn_mgr_->GetUndoLog(*op_undo_link);
    undo_log = GenerateUpdatedUndoLog(schema, old_rec, new_rec, old_log);
    undo_link = *op_undo_link;
  } else {
    // 版本链尾需维护版本链 没有值插入默认无效值
    UndoLink pre_link;
    if (op_undo_link.has_value() && (*op_undo_link).prev_txn_ != txn_id) {
      pre_link = *op_undo_link;
    }
    undo_log = GenerateNewUndoLog(schema, old_rec, new_rec, context->txn_->get_temp_ts(), pre_link);
  }
  return std::make_tuple(undo_log, undo_link);
}