/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "transaction_manager.h"
#include "record/rm_file_handle.h"
#include "system/sm_manager.h"

std::unordered_map<txn_id_t, Transaction *> TransactionManager::txn_map = {};

/**
 * @description: 事务的开始方法
 * @return {Transaction*} 开始事务的指针
 * @param {Transaction*} txn 事务指针，空指针代表需要创建新事务，否则开始已有事务
 * @param {LogManager*} log_manager 日志管理器指针
 */
Transaction *TransactionManager::begin(Transaction *txn, LogManager *log_manager) {
  // Todo:
  // 1. 判断传入事务参数是否为空指针
  // 2. 如果为空指针，创建新事务
  // 3. 把开始事务加入到全局事务表中
  // 4. 返回当前事务指针
  // 如果需要支持MVCC请在上述过程中添加代码

  // sqb 涉及mvcc 未涉及日志6.16
  if (txn == nullptr) {
    txn = new Transaction(next_txn_id_++);
    txn->set_start_ts(next_timestamp_++);
    txn->set_read_ts(last_commit_ts_);
  }

  // sqb 加水印 6.16
  std::unique_lock<std::shared_mutex> lock(txn_map_mutex_);
  txn_map.emplace(txn->get_transaction_id(), txn);
  running_txns_.AddTxn(txn->get_read_ts());

  return txn;
}

/**
 * @description: 事务的提交方法
 * @param {Transaction*} txn 需要提交的事务
 * @param {LogManager*} log_manager 日志管理器指针
 */
void TransactionManager::commit(Transaction *txn, LogManager *log_manager) {
  // Todo:
  // 1. 如果存在未提交的写操作，提交所有的写操作
  // 2. 释放所有锁
  // 3. 释放事务相关资源，eg.锁集
  // 4. 把事务日志刷入磁盘中
  // 5. 更新事务状态
  // 如果需要支持MVCC请在上述过程中添加代码

  // sqb 考虑mvcc 未考虑日志 6.16
  // 直接进行写操作 所以不会存在未提交的写
  //   更新所有写操作的提交时间戳
  std::scoped_lock<std::mutex> lck(commit_mutex_);
  timestamp_t commit_ts = next_timestamp_++;
  auto write_set_ptr = txn->get_write_set();
  std::unordered_set<Rid> reseted_rids;
  for (auto iter = write_set_ptr->rbegin(); iter != write_set_ptr->rend(); ++iter) {
    Rid rid = (*iter)->GetRid();
    if (reseted_rids.find(rid) != reseted_rids.end()) {
      continue;
    } else {
      reseted_rids.insert(rid);
    }
    std::string &tab_name = (*iter)->GetTableName();
    auto fhdl_ptr = sm_manager_->fhs_.at(tab_name).get();
    if (((*iter)->GetWriteType() == WType::UPDATE_TUPLE)) {
      fhdl_ptr->set_meta(rid, commit_ts, (*iter)->GetTupleMeta().is_deleted_);
    } else {
      fhdl_ptr->set_meta(rid, commit_ts, !((*iter)->GetTupleMeta().is_deleted_));
    }
  }
  // 更新undo log的时间戳
  txn->CommitAllUndoLogs(commit_ts);

  //  释放锁
  auto lock_set_ptr = txn->get_lock_set();
  for (auto &lock_id : *lock_set_ptr) {
    lock_manager_->unlock(txn, lock_id);
  }
  //   释放资源 感觉后面可以去掉
  lock_set_ptr->clear();
  txn->get_write_set()->clear();
  txn->get_index_deleted_page_set()->clear();
  txn->get_index_latch_page_set()->clear();

  //   sqb 6.16 加水印
  std::unique_lock<std::shared_mutex> lock(txn_map_mutex_);
  txn->set_state(TransactionState::COMMITTED);
  txn->set_commit_ts(commit_ts);
  last_commit_ts_ = commit_ts;
  running_txns_.UpdateCommitTs(commit_ts);
  running_txns_.RemoveTxn(txn->get_read_ts());
}

/**
 * @description: 事务的终止（回滚）方法
 * @param {Transaction *} txn 需要回滚的事务
 * @param {LogManager} *log_manager 日志管理器指针
 */
void TransactionManager::abort(Transaction *txn, LogManager *log_manager) {
  // Todo:
  // 1. 回滚所有写操作
  // 2. 释放所有锁
  // 3. 清空事务相关资源，eg.锁集
  // 4. 把事务日志刷入磁盘中
  // 5. 更新事务状态
  // 如果需要支持MVCC请在上述过程中添加代码

  // sqb 考虑mvcc 未考虑日志 6.16

  //   写操作回滚
  auto write_set_ptr = txn->get_write_set();
  for (auto iter = write_set_ptr->rbegin(); iter != write_set_ptr->rend(); ++iter) {
    auto &write_rec_ptr = *iter;
    switch (write_rec_ptr->GetWriteType()) {
      case WType::INSERT_TUPLE: {
        rollback_insert(*write_rec_ptr);
        break;
      }
      case WType::DELETE_TUPLE: {
        rollback_delete(*write_rec_ptr);
        break;
      }
      case WType::UPDATE_TUPLE: {
        rollback_update(*write_rec_ptr);
        break;
      }
    }
  }
  //  释放锁
  auto lock_set_ptr = txn->get_lock_set();
  for (auto &lock_id : *lock_set_ptr) {
    lock_manager_->unlock(txn, lock_id);
  }
  //   释放资源 感觉后面可以去掉
  lock_set_ptr->clear();
  txn->get_write_set()->clear();
  txn->get_index_deleted_page_set()->clear();
  txn->get_index_latch_page_set()->clear();

  //   sqb 6.16 加水印
  std::unique_lock<std::shared_mutex> lock(txn_map_mutex_);
  txn->set_state(TransactionState::ABORTED);
  running_txns_.RemoveTxn(txn->get_read_ts());
}

// sqb 回滚插入的记录  三种回滚基本都参照对应算子实现 回滚应该不需要再进行事务记录吧…… 6.4
void TransactionManager::rollback_insert(WriteRecord &write_rec) {
  // 插入回滚对应删除 先删索引再删记录
  std::string &tab_name = write_rec.GetTableName();
  Rid rid = write_rec.GetRid();
  IxManager *ix_manager_ptr = sm_manager_->get_ix_manager();

  TabMeta &tab_meta = sm_manager_->db_.get_table(tab_name);
  auto fhdl_ptr = sm_manager_->fhs_.at(tab_name).get();
  std::unique_ptr<RmRecord> rec_ptr = fhdl_ptr->get_record(rid, nullptr);

  //   删除索引
  for (auto &index_meta : tab_meta.indexes) {
    std::string index_name = ix_manager_ptr->get_index_name(tab_name, index_meta.cols);
    auto ix_hdl_ptr = sm_manager_->ihs_[index_name].get();
    char key_buffer[index_meta.col_tot_len];
    int offset = 0;
    for (auto &col_meta : index_meta.cols) {
      memcpy(key_buffer + offset, rec_ptr->data + col_meta.offset, col_meta.len);
      offset += col_meta.len;
    }
    ix_hdl_ptr->delete_entry(key_buffer, nullptr);
  }

  // 回滚元信息 6.19
  auto &base_meta = write_rec.GetTupleMeta();
  fhdl_ptr->set_meta(rid, base_meta.ts_, base_meta.is_deleted_);

  //   删除记录
  fhdl_ptr->delete_record(rid, nullptr);
}

// sqb 回滚插入的记录 6.4
void TransactionManager::rollback_delete(WriteRecord &write_rec) {
  // 删除回滚对应插入 先插入记录再插入索引 不同于删除的是 这里不指定位置
  std::string &tab_name = write_rec.GetTableName();
  RmRecord &rec = write_rec.GetRecord();
  IxManager *ix_manager_ptr = sm_manager_->get_ix_manager();

  TabMeta &tab_meta = sm_manager_->db_.get_table(tab_name);
  auto fhdl_ptr = sm_manager_->fhs_.at(tab_name).get();

  //   插入记录
  //   Rid rid = fhdl_ptr->insert_record(rec.data, nullptr);
  Rid rid = write_rec.GetRid();
  fhdl_ptr->allocate_pages(rid);
  fhdl_ptr->insert_record(rid, rec.data);

  // 回滚元信息 6.19
  auto &base_meta = write_rec.GetTupleMeta();
  fhdl_ptr->set_meta(rid, base_meta.ts_, base_meta.is_deleted_);

  //   插入索引
  for (auto &index_meta : tab_meta.indexes) {
    std::string index_name = ix_manager_ptr->get_index_name(tab_name, index_meta.cols);
    auto ix_hdl_ptr = sm_manager_->ihs_[index_name].get();
    char key_buffer[index_meta.col_tot_len];
    int offset = 0;
    for (auto &col_meta : index_meta.cols) {
      memcpy(key_buffer + offset, rec.data + col_meta.offset, col_meta.len);
      offset += col_meta.len;
    }
    ix_hdl_ptr->insert_entry(key_buffer, rid, nullptr);
  }
}

// sqb 回滚插入的记录 6.4
void TransactionManager::rollback_update(WriteRecord &write_rec) {
  // 更新回滚与自身行为一致  先删旧索引 插入新记录 插入新索引
  std::string &tab_name = write_rec.GetTableName();
  Rid rid = write_rec.GetRid();
  RmRecord &old_rec = write_rec.GetRecord();
  IxManager *ix_manager_ptr = sm_manager_->get_ix_manager();

  TabMeta &tab_meta = sm_manager_->db_.get_table(tab_name);
  auto fhdl_ptr = sm_manager_->fhs_.at(tab_name).get();

  std::unique_ptr<RmRecord> cur_rec_ptr = fhdl_ptr->get_record(rid, nullptr);

  // 删除旧索引
  for (auto &index_meta : tab_meta.indexes) {
    std::string index_name = ix_manager_ptr->get_index_name(tab_name, index_meta.cols);
    auto ix_hdl_ptr = sm_manager_->ihs_[index_name].get();
    char key_buffer[index_meta.col_tot_len];
    int offset = 0;
    for (auto &col_meta : index_meta.cols) {
      memcpy(key_buffer + offset, cur_rec_ptr->data + col_meta.offset, col_meta.len);
      offset += col_meta.len;
    }
    ix_hdl_ptr->delete_entry(key_buffer, nullptr);
  }

  //   插入记录
  fhdl_ptr->update_record(rid, old_rec.data, nullptr);

  // 回滚元信息 6.19
  auto &base_meta = write_rec.GetTupleMeta();
  fhdl_ptr->set_meta(rid, base_meta.ts_, base_meta.is_deleted_);

  //   插入新索引
  for (auto &index_meta : tab_meta.indexes) {
    std::string index_name = ix_manager_ptr->get_index_name(tab_name, index_meta.cols);
    auto ix_hdl_ptr = sm_manager_->ihs_[index_name].get();
    char key_buffer[index_meta.col_tot_len];
    int offset = 0;
    for (auto &col_meta : index_meta.cols) {
      memcpy(key_buffer + offset, old_rec.data + col_meta.offset, col_meta.len);
      offset += col_meta.len;
    }
    ix_hdl_ptr->insert_entry(key_buffer, rid, nullptr);
  }
}

//------------------------关于MVCC部分的实现,参考15445,sqb---------------
/**
 * @brief 更新一个撤销链接，该链接将表堆元组与第一个撤销日志连接起来。
 * 在更新之前，将调用 `check` 函数以确保有效性。
 */
// 不确定
bool TransactionManager::UpdateUndoLink(Rid rid, std::optional<UndoLink> prev_link,
                                        std::function<bool(std::optional<UndoLink>)> &&check) {
  std::unique_lock<std::shared_mutex> verion_table_lock(version_info_mutex_);
  std::shared_ptr<PageVersionInfo> pvi_ptr = nullptr;
  auto iter = version_info_.find(rid.page_no);
  if (iter == version_info_.end()) {
    // 无则创建
    pvi_ptr = std::make_shared<PageVersionInfo>();
    version_info_[rid.page_no] = pvi_ptr;
  } else {
    // 有则准备修改
    pvi_ptr = iter->second;
  }
  std::unique_lock<std::shared_mutex> pvi_lock(pvi_ptr->mutex_);
  verion_table_lock.unlock();
  auto it = pvi_ptr->prev_version_.find(rid.slot_no);
  if (it == pvi_ptr->prev_version_.end()) {
    if (check != nullptr && !check(std::nullopt)) {
      return false;
    }
  } else {
    if (check != nullptr && !check(it->second.prev_)) {
      return false;
    }
  }
  if (prev_link.has_value()) {
    pvi_ptr->prev_version_[rid.slot_no].prev_ = prev_link.value();
  } else {
    pvi_ptr->prev_version_.erase(rid.slot_no);
  }
  return true;
}

/**
 * @brief 更新一个撤销链接，该链接将表堆元组与第一个撤销日志连接起来。
 * 在更新之前，将调用 `check` 函数以确保有效性。
 */
bool TransactionManager::UpdateVersionLink(Rid rid, std::optional<VersionUndoLink> prev_version,
                                           std::function<bool(std::optional<VersionUndoLink>)> &&check) {
  std::unique_lock<std::shared_mutex> verion_table_lock(version_info_mutex_);
  std::shared_ptr<PageVersionInfo> pvi_ptr = nullptr;
  auto iter = version_info_.find(rid.page_no);
  if (iter == version_info_.end()) {
    // 无则创建
    pvi_ptr = std::make_shared<PageVersionInfo>();
    version_info_[rid.page_no] = pvi_ptr;
  } else {
    // 有则准备修改
    pvi_ptr = iter->second;
  }
  std::unique_lock<std::shared_mutex> pvi_lock(pvi_ptr->mutex_);
  verion_table_lock.unlock();
  auto it = pvi_ptr->prev_version_.find(rid.slot_no);
  if (it == pvi_ptr->prev_version_.end()) {
    if (check != nullptr && !check(std::nullopt)) {
      return false;
    }
  } else {
    if (check != nullptr && !check(it->second)) {
      return false;
    }
  }
  if (prev_version.has_value()) {
    pvi_ptr->prev_version_[rid.slot_no] = prev_version.value();
  } else {
    pvi_ptr->prev_version_.erase(rid.slot_no);
  }
  return true;
}

/** @brief 获取表堆元组的第一个撤销日志。 */
std::optional<UndoLink> TransactionManager::GetUndoLink(Rid rid) {
  std::shared_lock<std::shared_mutex> version_table_lock(version_info_mutex_);
  auto iter = version_info_.find(rid.page_no);
  if (iter == version_info_.end()) {
    return std::nullopt;
  }
  std::shared_ptr<PageVersionInfo> pvi_ptr = iter->second;
  std::unique_lock<std::shared_mutex> pvi_lock(pvi_ptr->mutex_);
  version_table_lock.unlock();
  auto it = pvi_ptr->prev_version_.find(rid.slot_no);
  if (it == pvi_ptr->prev_version_.end()) {
    return std::nullopt;
  }
  return std::make_optional(it->second.prev_);
}

/** @brief 获取表堆元组的第一个撤销日志。*/
std::optional<VersionUndoLink> TransactionManager::GetVersionLink(Rid rid) {
  std::shared_lock<std::shared_mutex> version_table_lock(version_info_mutex_);
  auto iter = version_info_.find(rid.page_no);
  if (iter == version_info_.end()) {
    return std::nullopt;
  }
  std::shared_ptr<PageVersionInfo> pvi_ptr = iter->second;
  std::unique_lock<std::shared_mutex> pvi_lock(pvi_ptr->mutex_);
  version_table_lock.unlock();
  auto it = pvi_ptr->prev_version_.find(rid.slot_no);
  if (it == pvi_ptr->prev_version_.end()) {
    return std::nullopt;
  }
  return std::make_optional(it->second);
}

/** @brief 访问事务撤销日志缓冲区并获取撤销日志。如果事务不存在，返回 nullopt。
 * 如果索引超出范围仍然会抛出异常。 */
std::optional<UndoLog> TransactionManager::GetUndoLogOptional(UndoLink link) {
  std::shared_lock<std::shared_mutex> lock(txn_map_mutex_);
  auto iter = txn_map.find(link.prev_txn_);
  if (iter == txn_map.end()) {
    return std::nullopt;
  }
  Transaction *txn = iter->second;
  lock.unlock();
  return txn->GetUndoLog(link.prev_log_idx_);
}

/** @brief 访问事务撤销日志缓冲区并获取撤销日志。除非访问当前事务缓冲区，
 * 否则应该始终调用此函数以获取撤销日志，而不是手动检索事务 shared_ptr 并访问缓冲区。 */
UndoLog TransactionManager::GetUndoLog(UndoLink link) {
  auto undo_log = GetUndoLogOptional(link);
  if (undo_log.has_value()) {
    return undo_log.value();
  }
  throw InternalError("txn try access invalid undo log");
}

/** @brief 垃圾回收。仅在所有事务都未访问时调用。 */
void TransactionManager::GarbageCollection() {}