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

#include <list>
#include <mutex>
#include <vector>

#include "common/config.h"
#include "replacer/replacer.h"
#include "unordered_map"

/*
LRUReplacer实现了LRU替换策略
*/
class LRUReplacer : public Replacer {
 public:
  /**
   * @description: 创建一个新的LRUReplacer
   * @param {size_t} num_pages LRUReplacer最多需要存储的page数量
   */
  explicit LRUReplacer(size_t num_pages);

  ~LRUReplacer();

  bool victim(frame_id_t *frame_id);

  void pin(frame_id_t frame_id);

  void unpin(frame_id_t frame_id);

  size_t Size();

 private:
  std::mutex latch_;               // 互斥锁
  std::list<frame_id_t> LRUlist_;  // 按加入的时间顺序存放unpinned pages的frame id，首部表示最近被访问
  std::unordered_map<frame_id_t, std::list<frame_id_t>::iterator> LRUhash_;  // frame_id_t -> unpinned pages的frame id
  size_t max_size_;                                                          // 最大容量（与缓冲池的容量相同）
};

// sqb 尝试用clock置换策略
class ClockReplacer : public Replacer {
 public:
  explicit ClockReplacer() {}

  ~ClockReplacer() = default;

  bool victim(frame_id_t *frame_id) override {
    int steps = 0;
    do {
      clock_hand_ = (clock_hand_ + 1) % BUFFER_POOL_SIZE;
      if (pin_count_[clock_hand_] == 0 && pined_[clock_hand_] == false) {
        *frame_id = clock_hand_;
        return true;
      }
      if (pin_count_[clock_hand_] == 0) {
        pined_[clock_hand_] = false;
      }
      ++steps;
    } while (steps < 2 * BUFFER_POOL_SIZE);
    return false;
  }

  void pin(frame_id_t frame_id) override {
    ++pin_count_[frame_id];
    if (pin_count_[frame_id] == 1) {
      pined_[frame_id] = true;
    }
  }

  void unpin(frame_id_t frame_id) override { --pin_count_[frame_id]; }

  size_t Size() override { return BUFFER_POOL_SIZE; }

 private:
  int pin_count_[BUFFER_POOL_SIZE];
  bool pined_[BUFFER_POOL_SIZE];
  size_t clock_hand_ = 0;  // 当前扫描位置（时钟指针）
  //   size_t unpinned_count_ = 0;  // 可被替换的帧数
  //   size_t max_size_ = 0;        // 最多管理的帧
};