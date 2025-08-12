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

  // sqb 涉及mvcc 6.5
  txn_num_++;
  if (txn == nullptr) {
    txn = new Transaction(next_txn_id_.fetch_add(1));
    txn->set_start_ts(next_timestamp_.fetch_add(1));
    txn->set_read_ts(last_commit_ts_.load());
  }
  //   txn->set_state(TransactionState::GROWING);

  //   //   日志
  //   BeginLogRecord log_record{txn->get_transaction_id()};
  //   lsn_t begin_lsn = log_manager->add_log_to_buffer(&log_record);
  //   txn->set_prev_lsn(begin_lsn);

  // sqb 加水印 6.16
  std::unique_lock<std::shared_mutex> lock(txn_map_mutex_);
  txn_map.emplace(txn->get_transaction_id(), txn);
  //   running_txns_.AddTxn(txn->get_read_ts());

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

  // sqb 考虑mvcc 6.5
  // 直接进行写操作 所以不会存在未提交的写
  //   更新所有写操作的提交时间戳
  commit_num_++;
  std::scoped_lock<std::mutex> lck(commit_mutex_);
  timestamp_t commit_ts = next_timestamp_.fetch_add(1);
  auto write_set_ptr = txn->get_write_set();
  size_t idx = 0;  // 跟踪rid，因为一个rid仅在undo中出现一次，按顺序就是对应的undo_log顺序
  for (auto iter = write_set_ptr->begin(); iter != write_set_ptr->end(); ++iter) {
    Rid rid = (*iter)->GetRid();
    std::string &tab_name = (*iter)->GetTableName();
    auto fhdl_ptr = sm_manager_->fhs_.at(tab_name).get();
    fhdl_ptr->set_meta_ts(txn, idx++, rid, commit_ts);
  }
  // 更新undo log的时间戳
  //   txn->CommitAllUndoLogs(commit_ts);

  //  释放锁
  auto lock_set_ptr = txn->get_lock_set();
  for (auto &lock_id : *lock_set_ptr) {
    lock_manager_->unlock(txn, lock_id);
  }
  //   释放资源 感觉后面可以去掉
  lock_set_ptr->clear();
  txn->get_write_set()->clear();
  txn->get_write_tuples().clear();
  txn->get_index_deleted_page_set()->clear();
  txn->get_index_latch_page_set()->clear();

  //   //   日志与落盘
  //   CommitLogRecord log_record{txn->get_transaction_id()};
  //   log_record.prev_lsn_ = txn->get_prev_lsn();
  //   lsn_t commit_lsn = log_manager->add_log_to_buffer(&log_record);
  //   txn->set_prev_lsn(commit_lsn);
  //   log_manager->flush_log_to_disk();  // 待优化

  //   sqb 6.16 加水印
  std::unique_lock<std::shared_mutex> lock(txn_map_mutex_);
  txn->set_state(TransactionState::COMMITTED);
  txn->set_commit_ts(commit_ts);
  last_commit_ts_.store(commit_ts);
  //   running_txns_.UpdateCommitTs(commit_ts);
  //   running_txns_.RemoveTxn(txn->get_read_ts());
}

/**
 * @description: 事务的终止（回滚）方法
 * @param {Transaction *} txn 需要回滚的事务
 * @param {LogManager} *log_manager 日志管理器指针
 */
void TransactionManager::abort(Transaction *txn, LogManager *log_manager, TransactionManager *txn_mgr) {
  // Todo:
  // 1. 回滚所有写操作
  // 2. 释放所有锁
  // 3. 清空事务相关资源，eg.锁集
  // 4. 把事务日志刷入磁盘中
  // 5. 更新事务状态
  // 如果需要支持MVCC请在上述过程中添加代码

  // sqb 未考虑mvcc 6.5

  //   写操作回滚
  aborts_num_++;
  auto write_set_ptr = txn->get_write_set();
  for (auto iter = write_set_ptr->rbegin(); iter != write_set_ptr->rend(); ++iter) {
    auto &write_rec_ptr = *iter;
    // 给回滚操作加锁 加日志 6.12
    std::string &tab_name = write_rec_ptr->GetTableName();
    // lock_manager_->lock_exclusive_on_record(txn, write_rec_ptr->GetRid(), sm_manager_->fhs_.at(tab_name)->GetFd());

    // 现在全部都是update wrec 便于线下加故障恢复
    // auto old_rec = sm_manager_->fhs_[tab_name]->get_record(write_rec_ptr->GetRid(), nullptr);
    // UpdateLogRecord log_record{txn->get_transaction_id(), *old_rec, write_rec_ptr->GetRecord(),
    //                            write_rec_ptr->GetRid(), tab_name};
    // log_record.prev_lsn_ = txn->get_prev_lsn();
    // lsn_t undo_lsn = log_manager->add_log_to_buffer(&log_record);
    // txn->set_prev_lsn(undo_lsn);
    sm_manager_->rollback_update(tab_name, *write_rec_ptr, txn, txn_mgr);
  }

  //  释放锁
  auto lock_set_ptr = txn->get_lock_set();
  for (auto &lock_id : *lock_set_ptr) {
    lock_manager_->unlock(txn, lock_id);
  }
  //   释放资源 感觉后面可以去掉
  lock_set_ptr->clear();
  txn->get_write_set()->clear();
  txn->get_write_tuples().clear();
  txn->get_index_deleted_page_set()->clear();
  txn->get_index_latch_page_set()->clear();

  //   // 日志与落盘
  //   AbortLogRecord log_record{txn->get_transaction_id()};
  //   log_record.prev_lsn_ = txn->get_prev_lsn();
  //   lsn_t abort_lsn = log_manager->add_log_to_buffer(&log_record);
  //   txn->set_prev_lsn(abort_lsn);
  //   log_manager->flush_log_to_disk();  // 待优化

  //   sqb 6.16 加水印
  std::unique_lock<std::shared_mutex> lock(txn_map_mutex_);
  txn->set_state(TransactionState::ABORTED);
  //   running_txns_.RemoveTxn(txn->get_read_ts());
}

//------------------------关于MVCC部分的实现,参考15445,sqb---------------
/**
 * @brief 更新一个撤销链接，该链接将表堆元组与第一个撤销日志连接起来。
 * 在更新之前，将调用 `check` 函数以确保有效性。
 */
// 不确定
bool TransactionManager::UpdateUndoLink(int fd, Rid rid, std::optional<UndoLink> prev_link,
                                        std::function<bool(std::optional<UndoLink>)> &&check) {
  PageId page_id{fd, rid.page_no};
  std::unique_lock<std::shared_mutex> verion_table_lock(version_info_mutex_);
  std::shared_ptr<PageVersionInfo> pvi_ptr = nullptr;
  auto iter = version_info_.find(page_id);
  if (iter == version_info_.end()) {
    // 无则创建
    pvi_ptr = std::make_shared<PageVersionInfo>();
    version_info_[page_id] = pvi_ptr;
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
bool TransactionManager::UpdateVersionLink(int fd, Rid rid, std::optional<VersionUndoLink> prev_version,
                                           std::function<bool(std::optional<VersionUndoLink>)> &&check) {
  PageId page_id{fd, rid.page_no};
  std::unique_lock<std::shared_mutex> verion_table_lock(version_info_mutex_);
  std::shared_ptr<PageVersionInfo> pvi_ptr = nullptr;
  auto iter = version_info_.find(page_id);
  if (iter == version_info_.end()) {
    // 无则创建
    pvi_ptr = std::make_shared<PageVersionInfo>();
    version_info_[page_id] = pvi_ptr;
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
std::optional<UndoLink> TransactionManager::GetUndoLink(int fd, Rid rid) {
  PageId page_id{fd, rid.page_no};
  std::shared_lock<std::shared_mutex> version_table_lock(version_info_mutex_);
  auto iter = version_info_.find(page_id);
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
std::optional<VersionUndoLink> TransactionManager::GetVersionLink(int fd, Rid rid) {
  PageId page_id{fd, rid.page_no};
  std::shared_lock<std::shared_mutex> version_table_lock(version_info_mutex_);
  auto iter = version_info_.find(page_id);
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
