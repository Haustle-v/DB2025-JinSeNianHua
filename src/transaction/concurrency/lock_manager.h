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

#include <condition_variable>
#include <mutex>
#include "transaction/transaction.h"

static const std::string GroupLockModeStr[10] = {"NON_LOCK", "IS", "IX", "S", "X", "SIX"};

class LockManager {
  /* 加锁类型，包括共享锁、排他锁、意向共享锁、意向排他锁、SIX（意向排他锁+共享锁） */
  enum class LockMode { SHARED, EXLUCSIVE, INTENTION_SHARED, INTENTION_EXCLUSIVE, S_IX };

  /* 用于标识加锁队列中排他性最强的锁类型，例如加锁队列中有SHARED和EXLUSIVE两个加锁操作，则该队列的锁模式为X */
  //   enum class GroupLockMode { NON_LOCK, IS, IX, S, X, SIX };
  enum class GroupLockMode { NON_LOCK, IS, IX, S, SIX, X };

  /* 事务的加锁申请 */
  class LockRequest {
   public:
    LockRequest(txn_id_t txn_id, LockMode lock_mode) : txn_id_(txn_id), lock_mode_(lock_mode), granted_(false) {}

    txn_id_t txn_id_;     // 申请加锁的事务ID
    LockMode lock_mode_;  // 事务申请加锁的类型
    bool granted_;        // 该事务是否已经被赋予锁
  };

  /* 数据项上的加锁队列 */
  class LockRequestQueue {
   public:
    std::list<LockRequest> request_queue_;  // 加锁队列
    std::condition_variable cv_;            // 条件变量，用于唤醒正在等待加锁的申请，在no-wait策略下无需使用
    GroupLockMode group_lock_mode_ = GroupLockMode::NON_LOCK;  // 加锁队列的锁模式
    std::mutex latch_;                                         // sqb 条件变量使用应该是结合锁的
    txn_id_t waiting_txn_{INVALID_TXN_ID};                     // 等待锁升级的事务
  };

 public:
  LockManager() {}

  ~LockManager() {}

  bool lock_shared_on_record(Transaction *txn, const Rid &rid, int tab_fd);

  bool lock_exclusive_on_record(Transaction *txn, const Rid &rid, int tab_fd);

  bool lock_shared_on_table(Transaction *txn, int tab_fd);

  bool lock_exclusive_on_table(Transaction *txn, int tab_fd);

  bool lock_IS_on_table(Transaction *txn, int tab_fd);

  bool lock_IX_on_table(Transaction *txn, int tab_fd);

  bool unlock(Transaction *txn, LockDataId lock_data_id);

 private:
  // sqb 6.8 添加几个私有的方法辅助加锁
  bool lock_helper(Transaction *txn, LockDataId &lock_id, LockMode lock_mode);

  inline bool is_stronger_or_equal(LockMode held, LockMode requested);

  inline bool is_valid_upgrade(LockMode current, LockMode target);

  inline GroupLockMode convert2Group(LockMode mode);

  inline bool is_compatible(GroupLockMode held, LockMode requested);

  inline GroupLockMode MaxLockMode(GroupLockMode x, GroupLockMode y) {
    return static_cast<GroupLockMode>(std::max(static_cast<std::underlying_type_t<GroupLockMode>>(x),
                                               static_cast<std::underlying_type_t<GroupLockMode>>(y)));
  }

  std::mutex latch_;                                             // 用于锁表的并发
  std::unordered_map<LockDataId, LockRequestQueue> lock_table_;  // 全局锁表
};
