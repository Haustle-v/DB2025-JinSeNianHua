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

#include <map>
// #include <unordered_map>
#include <set>

#include "transaction/transaction.h"

/**
 * @brief 追踪所有的读时间戳
 *
 */
class Watermark {
 public:
  explicit Watermark(timestamp_t commit_ts) : commit_ts_(commit_ts), watermark_(commit_ts) {}

  void AddTxn(timestamp_t read_ts);

  void RemoveTxn(timestamp_t read_ts);

  /** 调用者应在从水印中移除事务之前更新提交时间戳，以便我们能够正确跟踪水印。 */
  // sqb 6.16
  void UpdateCommitTs(timestamp_t commit_ts) {
    std::unique_lock<std::shared_mutex> lock(latch_);
    commit_ts_ = commit_ts;
    if (current_reads_.empty()) {
      watermark_ = commit_ts_;
    }
  }

  timestamp_t GetWatermark() {
    std::shared_lock<std::shared_mutex> lock(latch_);
    return watermark_;
  }

  mutable timestamp_t commit_ts_;

  timestamp_t watermark_;

  //   std::map<timestamp_t, int> current_reads_;
  std::multiset<timestamp_t> current_reads_;  // sqb 换个高效的写法

  std::shared_mutex latch_;  // 支持并发
};