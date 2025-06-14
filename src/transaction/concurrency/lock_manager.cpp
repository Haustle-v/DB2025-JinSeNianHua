/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "lock_manager.h"

// sqb 检查是否已持有足够强的锁 6.9
bool LockManager::is_stronger_or_equal(LockMode held, LockMode requested) {
  static const bool strength_matrix[5][5] = {/* SHRD */ {true, false, false, false, false},
                                             /* EXCL */ {true, true, false, false, false},
                                             /* IS   */ {false, false, true, false, false},
                                             /* IX   */ {false, false, false, true, false},
                                             /* SIX  */ {true, false, false, true, true}};
  return strength_matrix[static_cast<int>(held)][static_cast<int>(requested)];
}

// sqb 检查升级是否合法 6.9
bool LockManager::is_valid_upgrade(LockMode current, LockMode target) {
  static const bool upgrade_matrix[5][5] = {/* SHRD */ {true, true, false, false, true},
                                            /* EXCL */ {false, true, false, false, false},
                                            /* IS   */ {false, false, true, true, true},
                                            /* IX   */ {false, true, false, true, true},
                                            /* SIX  */ {false, false, false, false, true}};
  return upgrade_matrix[static_cast<int>(current)][static_cast<int>(target)];
}

// sqb 将请求的锁转换为队列中的锁 6.9
LockManager::GroupLockMode LockManager::convert2Group(LockMode mode) {
  switch (mode) {
    case LockMode::SHARED:
      return GroupLockMode::S;
    case LockMode::EXLUCSIVE:
      return GroupLockMode::X;
    case LockMode::INTENTION_EXCLUSIVE:
      return GroupLockMode::IX;
    case LockMode::INTENTION_SHARED:
      return GroupLockMode::IS;
    case LockMode::S_IX:
      return GroupLockMode::SIX;
    default:
      return GroupLockMode::NON_LOCK;
  }
}

// sqb 检查兼容性 6.9
bool LockManager::is_compatible(GroupLockMode held, LockMode requested) {
  GroupLockMode request_mode = convert2Group(requested);
  static const bool compatiable_matrix[6][6] = {/* NON_LOCK */ {true, true, true, true, true, true},
                                                /* IS   */ {true, true, true, true, true, false},
                                                /* IX   */ {true, true, true, false, false, false},
                                                /* SHRD */ {true, true, false, true, false, false},
                                                /* SIX  */ {true, true, false, false, false, false},
                                                /* EXCL */ {true, false, false, false, false, false}};
  return compatiable_matrix[static_cast<int>(held)][static_cast<int>(request_mode)];
}

// sqb 统一抽象，用于加锁 6.9
bool LockManager::lock_helper(Transaction *txn, LockDataId &lock_id, LockMode lock_mode) {
  // 检查事务状态
  if (txn->get_state() == TransactionState::ABORTED) {
    return false;
  } else if (txn->get_state() == TransactionState::SHRINKING) {
    txn->set_state(TransactionState::ABORTED);
    throw TransactionAbortException(txn->get_transaction_id(), AbortReason::LOCK_ON_SHIRINKING);
  }
  txn->set_state(TransactionState::GROWING);

  //   查找现有锁
  std::unique_lock<std::mutex> lock(latch_);
  auto &request_queue = lock_table_[lock_id];  // 有则取，无则创建
  lock.unlock();
  std::unique_lock<std::mutex> queue_lock(request_queue.latch_);
  auto iter = request_queue.request_queue_.begin();
  for (; iter != request_queue.request_queue_.end(); ++iter) {
    if (iter->txn_id_ == txn->get_transaction_id()) {
      break;
    }
  }

  // 事务已有该锁请求
  if (iter != request_queue.request_queue_.end()) {
    // 已申请更强的锁就直接返回
    if (is_stronger_or_equal(iter->lock_mode_, lock_mode)) {
      return true;
    }
    // 检查现有锁能否升级到对应锁
    if (is_valid_upgrade(iter->lock_mode_, lock_mode)) {
      // 其它事务正在等待获取锁
      if (request_queue.waiting_txn_ != INVALID_TXN_ID) {
        txn->set_state(TransactionState::ABORTED);
        throw TransactionAbortException(txn->get_transaction_id(), AbortReason::UPGRADE_CONFLICT);
        return false;
      }

      //   为当前锁升级
      request_queue.waiting_txn_ = txn->get_transaction_id();
      iter->lock_mode_ = lock_mode;
      if (is_compatible(request_queue.group_lock_mode_, lock_mode)) {
        // 兼容直接授予锁
        iter->granted_ = true;
      } else {
        // 不兼容需等待锁
        iter->granted_ = false;
        request_queue.cv_.wait(queue_lock, [&]() { return iter->granted_; });
      }
      //   锁升级后更新队列最强锁 直接返回
      request_queue.group_lock_mode_ = MaxLockMode(request_queue.group_lock_mode_, convert2Group(lock_mode));
      if (request_queue.waiting_txn_ == txn->get_transaction_id()) {
        request_queue.waiting_txn_ = INVALID_TXN_ID;
      }
      return true;

    } else {
      //   非法升级  不确定 先回滚吧
      txn->set_state(TransactionState::ABORTED);
      throw TransactionAbortException(txn->get_transaction_id(), AbortReason::UPGRADE_CONFLICT);
      //   return false;
    }
  }

  //   事务没有锁 应创建锁请求
  LockRequest request{txn->get_transaction_id(), lock_mode};
  //   空队列直接添加
  if (request_queue.request_queue_.empty()) {
    request.granted_ = true;
    request_queue.request_queue_.emplace_back(request);
  } else {
    // 非空队列需检查兼容性 兼容直接授予锁 不兼容需等待
    if (is_compatible(request_queue.group_lock_mode_, lock_mode)) {
      request.granted_ = true;
      request_queue.request_queue_.emplace_back(request);
    } else {
      request_queue.request_queue_.emplace_back(request);
      auto it = request_queue.request_queue_.rbegin();
      request_queue.cv_.wait(queue_lock, [&]() { return it->granted_; });
    }
  }
  request_queue.group_lock_mode_ = MaxLockMode(request_queue.group_lock_mode_, convert2Group(lock_mode));
  txn->get_lock_set()->emplace(lock_id);
  return true;
}

/**
 * @description: 申请行级共享锁
 * @return {bool} 加锁是否成功
 * @param {Transaction*} txn 要申请锁的事务对象指针
 * @param {Rid&} rid 加锁的目标记录ID 记录所在的表的fd
 * @param {int} tab_fd
 */
bool LockManager::lock_shared_on_record(Transaction *txn, const Rid &rid, int tab_fd) {
  // 为表先加意向锁
  // LockDataId table_lock{tab_fd, LockDataType::TABLE};
  // if (!lock_helper(txn, table_lock, LockMode::INTENTION_SHARED)) {
  //   return false;
  // }
  LockDataId lock_data_id{tab_fd, rid, LockDataType::RECORD};
  return lock_helper(txn, lock_data_id, LockMode::SHARED);
}

/**
 * @description: 申请行级排他锁
 * @return {bool} 加锁是否成功
 * @param {Transaction*} txn 要申请锁的事务对象指针
 * @param {Rid&} rid 加锁的目标记录ID
 * @param {int} tab_fd 记录所在的表的fd
 */
bool LockManager::lock_exclusive_on_record(Transaction *txn, const Rid &rid, int tab_fd) {
  // 为表先加意向锁
  // LockDataId table_lock{tab_fd, LockDataType::TABLE};
  // if (!lock_helper(txn, table_lock, LockMode::INTENTION_EXCLUSIVE)) {
  //   return false;
  // }
  LockDataId lock_data_id{tab_fd, rid, LockDataType::RECORD};
  return lock_helper(txn, lock_data_id, LockMode::EXLUCSIVE);
}

/**
 * @description: 申请表级读锁
 * @return {bool} 返回加锁是否成功
 * @param {Transaction*} txn 要申请锁的事务对象指针
 * @param {int} tab_fd 目标表的fd
 */
bool LockManager::lock_shared_on_table(Transaction *txn, int tab_fd) {
  LockDataId lock_data_id{tab_fd, LockDataType::TABLE};
  return lock_helper(txn, lock_data_id, LockMode::SHARED);
}

/**
 * @description: 申请表级写锁
 * @return {bool} 返回加锁是否成功
 * @param {Transaction*} txn 要申请锁的事务对象指针
 * @param {int} tab_fd 目标表的fd
 */
bool LockManager::lock_exclusive_on_table(Transaction *txn, int tab_fd) {
  LockDataId lock_data_id{tab_fd, LockDataType::TABLE};
  return lock_helper(txn, lock_data_id, LockMode::EXLUCSIVE);
}

/**
 * @description: 申请表级意向读锁
 * @return {bool} 返回加锁是否成功
 * @param {Transaction*} txn 要申请锁的事务对象指针
 * @param {int} tab_fd 目标表的fd
 */
bool LockManager::lock_IS_on_table(Transaction *txn, int tab_fd) {
  LockDataId lock_data_id{tab_fd, LockDataType::TABLE};
  return lock_helper(txn, lock_data_id, LockMode::INTENTION_SHARED);
}

/**
 * @description: 申请表级意向写锁
 * @return {bool} 返回加锁是否成功
 * @param {Transaction*} txn 要申请锁的事务对象指针
 * @param {int} tab_fd 目标表的fd
 */
bool LockManager::lock_IX_on_table(Transaction *txn, int tab_fd) {
  LockDataId lock_data_id{tab_fd, LockDataType::TABLE};
  return lock_helper(txn, lock_data_id, LockMode::INTENTION_EXCLUSIVE);
}

/**
 * @description: 释放锁
 * @return {bool} 返回解锁是否成功
 * @param {Transaction*} txn 要释放锁的事务对象指针
 * @param {LockDataId} lock_data_id 要释放的锁ID
 */
bool LockManager::unlock(Transaction *txn, LockDataId lock_data_id) {
  if (txn->get_state() == TransactionState::GROWING) {
    txn->set_state(TransactionState::SHRINKING);
  }
  std::unique_lock<std::mutex> lock(latch_);
  // 寻找锁对应的请求队列
  auto iter = lock_table_.find(lock_data_id);
  if (iter == lock_table_.end()) {
    return false;
  }
  LockRequestQueue &request_queue = iter->second;
  lock.unlock();
  std::unique_lock<std::mutex> queue_lock(request_queue.latch_);

  // 删除请求队列中该事务的请求
  bool found = false;
  txn_id_t cur_txn_id = txn->get_transaction_id();
  for (auto it = request_queue.request_queue_.begin(); it != request_queue.request_queue_.end();) {
    if (it->txn_id_ == cur_txn_id) {
      // 如果事务锁正在升级 移除标记
      if (request_queue.waiting_txn_ == cur_txn_id) {
        request_queue.waiting_txn_ = INVALID_TXN_ID;
      }
      it = request_queue.request_queue_.erase(it);
      found = true;
    } else {
      it++;
    }
  }
  if (!found) return false;

  //   重新计算gruop lock
  GroupLockMode max_group_mode = GroupLockMode::NON_LOCK;
  for (auto &request : request_queue.request_queue_) {
    if (request.granted_) {
      max_group_mode = MaxLockMode(max_group_mode, convert2Group(request.lock_mode_));
    }
  }
  request_queue.group_lock_mode_ = max_group_mode;

  //   等待队列无请求则删除
  if (request_queue.request_queue_.empty()) {
    std::unique_lock<std::mutex> lock(latch_);
    lock_table_.erase(iter);
  }
  // 为事务中等待队列重新赋予锁
  for (auto &request : request_queue.request_queue_) {
    if (request.granted_) continue;

    // 有正在锁升级的事务先处理 其它事务不能获取
    if (request_queue.waiting_txn_ != INVALID_TXN_ID && request.txn_id_ != request_queue.waiting_txn_) continue;

    if (is_compatible(request_queue.group_lock_mode_, request.lock_mode_)) {
      request.granted_ = true;
      request_queue.group_lock_mode_ = MaxLockMode(request_queue.group_lock_mode_, convert2Group(request.lock_mode_));
    }
  }
  //   queue_lock.unlock();
  request_queue.cv_.notify_all();

  return true;
}