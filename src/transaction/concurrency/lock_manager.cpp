/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once // 建议加上头文件保护符

#include "lock_manager.h"

// =========================================================================================
// 修复说明：
// 1.  策略选择：采用Wait-Die（等待-死亡）策略进行死锁预防。
//     选择原因：此策略仅需中止当前请求锁的事务，无需修改函数签名去获取其它事务的指针，
//     与现有代码结构兼容性最好，实现最直接。
// 2.  关键修改点：在 lock_helper 函数中，原先会使线程无条件进入 std::condition_variable::wait
//     的两个地方，加入了Wait-Die策略的判断逻辑。
// 3.  具体逻辑：当一个事务（记为 T_req）的加锁请求与已持有的锁不兼容时：
//     a. 遍历所有持有锁的事务（记为 T_holder）。
//     b. 如果 T_req 的事务ID大于任何一个 T_holder 的ID（即T_req更"年轻"），
//        则T_req必须"死亡"，立即中止并抛出异常，而不是等待。
//     c. 如果 T_req 比所有 T_holder 都"年老"，它才可以进入等待队列。
// 4.  健壮性提升：修改了 condition_variable::wait 的等待条件，
//     增加了对事务自身状态的检查 (txn->get_state() == TransactionState::ABORTED)。
//     这可以防止事务在被外部（如另一个事务根据Wound-Wait策略）中止后，仍然永久等待。
// 5.  新增AbourtReason：请确保在 TransactionAbortException.h 中定义了
//     DEADLOCK_PREVENTION 这个新的中断原因，用于记录日志和调试。
// =========================================================================================


// sqb 检查是否已持有足够强的锁 6.9
inline bool LockManager::is_stronger_or_equal(LockMode held, LockMode requested) {
  // ... (此函数无需修改)
  static const bool strength_matrix[5][5] = {/* SHRD */ {true, false, false, false, false},
                                             /* EXCL */ {true, true, false, false, false},
                                             /* IS   */ {false, false, true, false, false},
                                             /* IX   */ {false, false, false, true, false},
                                             /* SIX  */ {true, false, false, true, true}};
  return strength_matrix[static_cast<int>(held)][static_cast<int>(requested)];
}

// sqb 检查升级是否合法 6.9
inline bool LockManager::is_valid_upgrade(LockMode current, LockMode target) {
  // ... (此函数无需修改)
  static const bool upgrade_matrix[5][5] = {/* SHRD */ {true, true, false, false, true},
                                            /* EXCL */ {false, true, false, false, false},
                                            /* IS   */ {false, false, true, true, true},
                                            /* IX   */ {false, true, false, true, true},
                                            /* SIX  */ {false, false, false, false, true}};
  return upgrade_matrix[static_cast<int>(current)][static_cast<int>(target)];
}

// sqb 将请求的锁转换为队列中的锁 6.9
inline LockManager::GroupLockMode LockManager::convert2Group(LockMode mode) {
  // ... (此函数无需修改)
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
inline bool LockManager::is_compatible(GroupLockMode held, LockMode requested) {
  // ... (此函数无需修改)
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
    if (txn->get_state() == TransactionState::ABORTED) {
        return false;
    }
    if (txn->get_state() == TransactionState::SHRINKING) {
        txn->set_state(TransactionState::ABORTED);
        throw TransactionAbortException(txn->get_transaction_id(), AbortReason::LOCK_ON_SHIRINKING);
    }
    txn->set_state(TransactionState::GROWING);

    std::unique_lock<std::mutex> lock(latch_);
    auto &request_queue = lock_table_[lock_id];
    std::unique_lock<std::mutex> queue_lock(request_queue.latch_);
    lock.unlock();

    // 检查是否已有锁请求（处理锁升级）
    for (auto iter = request_queue.request_queue_.begin(); iter != request_queue.request_queue_.end(); ++iter) {
        if (iter->txn_id_ == txn->get_transaction_id()) {
            // 已有更强的锁
            if (is_stronger_or_equal(iter->lock_mode_, lock_mode)) {
                return true;
            }
            // 非法升级
            if (!is_valid_upgrade(iter->lock_mode_, lock_mode)) {
                txn->set_state(TransactionState::ABORTED);
                throw TransactionAbortException(txn->get_transaction_id(), AbortReason::UPGRADE_CONFLICT);
            }

            // --- 锁升级逻辑 ---
            if (request_queue.upgrading_ != INVALID_TXN_ID && request_queue.upgrading_ != txn->get_transaction_id()) {
                txn->set_state(TransactionState::ABORTED);
                throw TransactionAbortException(txn->get_transaction_id(), AbortReason::UPGRADE_CONFLICT);
            }

            GroupLockMode other_max_lock = GroupLockMode::NON_LOCK;
            for (const auto &other : request_queue.request_queue_) {
                if (other.txn_id_ != txn->get_transaction_id() && other.granted_) {
                    other_max_lock = MaxLockMode(other_max_lock, convert2Group(other.lock_mode_));
                }
            }

            // 升级与现有锁兼容
            if (is_compatible(other_max_lock, lock_mode)) {
                iter->lock_mode_ = lock_mode;
                request_queue.group_lock_mode_ = MaxLockMode(request_queue.group_lock_mode_, convert2Group(lock_mode));
            } else { // 不兼容，需要等待
                request_queue.upgrading_ = txn->get_transaction_id();
                txn_id_t upgrader_id = txn->get_transaction_id();
                for (const auto &holder_req : request_queue.request_queue_) {
                    if (holder_req.granted_ && holder_req.txn_id_ != upgrader_id) {
                        if (upgrader_id > holder_req.txn_id_) { // Wait-Die
                            txn->set_state(TransactionState::ABORTED);
                            request_queue.upgrading_ = INVALID_TXN_ID;
                            throw TransactionAbortException(upgrader_id, AbortReason::DEADLOCK_PREVENTION);
                        }
                    }
                }
                iter->granted_ = false; // 等待时，暂时标记为未授予
                request_queue.cv_.wait(queue_lock, [&] { return iter->granted_ || txn->get_state() == TransactionState::ABORTED; });

                if (txn->get_state() == TransactionState::ABORTED) {
                    request_queue.upgrading_ = INVALID_TXN_ID;
                    // 无需移除请求，交由事务回滚时的unlock逻辑处理
                    return false;
                }
                // 被唤醒且成功授权
                iter->lock_mode_ = lock_mode;
                request_queue.group_lock_mode_ = MaxLockMode(request_queue.group_lock_mode_, convert2Group(lock_mode));
            }
            request_queue.upgrading_ = INVALID_TXN_ID;
            return true;
        }
    }

    // --- 新锁请求逻辑 ---
    LockRequest request(txn->get_transaction_id(), lock_mode);
    if (request_queue.upgrading_ != INVALID_TXN_ID) {
        txn->set_state(TransactionState::ABORTED);
        throw TransactionAbortException(txn->get_transaction_id(), AbortReason::UPGRADE_CONFLICT);
    }
    if (is_compatible(request_queue.group_lock_mode_, lock_mode)) {
        // 兼容，直接授予
        request.granted_ = true;
        request_queue.request_queue_.push_back(request);
        request_queue.group_lock_mode_ = MaxLockMode(request_queue.group_lock_mode_, convert2Group(lock_mode));
        txn->get_lock_set()->emplace(lock_id);
    } else {
        // 不兼容，执行Wait-Die并等待
        txn_id_t requester_id = txn->get_transaction_id();
        for (const auto &holder_req : request_queue.request_queue_) {
            if (holder_req.granted_) {
                if (requester_id > holder_req.txn_id_) { // Wait-Die
                    txn->set_state(TransactionState::ABORTED);
                    throw TransactionAbortException(requester_id, AbortReason::DEADLOCK_PREVENTION);
                }
            }
        }
        request_queue.request_queue_.push_back(request);
        auto it = std::prev(request_queue.request_queue_.end());
        request_queue.cv_.wait(queue_lock, [&] { return it->granted_ || txn->get_state() == TransactionState::ABORTED; });
        // 【修复】处理被唤醒后的逻辑
        if (txn->get_state() == TransactionState::ABORTED) {
            // 如果是因为中止而被唤醒，且锁未被授予，则清理请求
            if (!it->granted_) {
                request_queue.request_queue_.erase(it);
            }
            return false;
        }
        // 【修复】成功获得锁后，执行关键的更新操作
        request_queue.group_lock_mode_ = MaxLockMode(request_queue.group_lock_mode_, convert2Group(it->lock_mode_));
        txn->get_lock_set()->emplace(lock_id);
    }
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
    // ... (此函数无需修改)
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
    // ... (此函数无需修改)
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
    // ... (此函数无需修改)
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
    // ... (此函数无需修改)
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
    // ... (此函数无需修改)
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
    // ... (此函数无需修改)
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
    auto iter_lock_table = lock_table_.find(lock_data_id);
    if (iter_lock_table == lock_table_.end()) {
        return true;
    }
    LockRequestQueue &request_queue = iter_lock_table->second;
    std::unique_lock<std::mutex> queue_lock(request_queue.latch_);
    lock.unlock();
    auto it_to_remove = std::find_if(request_queue.request_queue_.begin(), request_queue.request_queue_.end(),
                                     [id = txn->get_transaction_id()](const LockRequest &req) { return req.txn_id_ == id; });
    if (it_to_remove == request_queue.request_queue_.end()) {
        return true;
    }
    request_queue.request_queue_.erase(it_to_remove);
    if (request_queue.upgrading_ == txn->get_transaction_id()) {
        request_queue.upgrading_ = INVALID_TXN_ID;
    }
    GroupLockMode new_group_mode = GroupLockMode::NON_LOCK;
    for (const auto &req : request_queue.request_queue_) {
        if (req.granted_) {
            new_group_mode = MaxLockMode(new_group_mode, convert2Group(req.lock_mode_));
        }
    }
    request_queue.group_lock_mode_ = new_group_mode;
    // 遍历整个队列，唤醒所有当前可兼容的请求
    for (auto it = request_queue.request_queue_.begin(); it != request_queue.request_queue_.end(); ++it) {
        if (!it->granted_) {
            if (request_queue.upgrading_ != INVALID_TXN_ID && request_queue.upgrading_ != it->txn_id_) {
                continue;
            }
            if (is_compatible(request_queue.group_lock_mode_, it->lock_mode_)) {
                it->granted_ = true;
                request_queue.group_lock_mode_ = MaxLockMode(request_queue.group_lock_mode_, convert2Group(it->lock_mode_));
            }
        }
    }
    queue_lock.unlock();
    request_queue.cv_.notify_all();
    return true;
}