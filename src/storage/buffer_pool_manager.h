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
#include <fcntl.h>
#include <unistd.h>

#include <cassert>
#include <list>
#include <unordered_map>
#include <vector>

#include "disk_manager.h"
#include "errors.h"
#include "page.h"
#include "replacer/lru_replacer.h"
#include "replacer/replacer.h"

// 用分段提高缓冲池并发度
struct PageTableSegment {
  std::shared_mutex mutex;
  std::unordered_map<PageId, frame_id_t, PageIdHash> page_table;

  // 显式定义移动操作
  PageTableSegment(PageTableSegment &&other) noexcept : page_table(std::move(other.page_table)) {
    // 注意：latch 不移动（互斥量不应被移动）
  }

  PageTableSegment &operator=(PageTableSegment &&other) noexcept {
    page_table = std::move(other.page_table);
    return *this;
  }

  // 禁止拷贝（保持与std::shared_mutex一致）
  PageTableSegment(const PageTableSegment &) = delete;
  PageTableSegment &operator=(const PageTableSegment &) = delete;

  PageTableSegment() = default;
};

class BufferPoolManager {
 private:
  size_t pool_size_;  // buffer_pool中可容纳页面的个数，即帧的个数
  Page *pages_;       // buffer_pool中的Page对象数组，在构造空间中申请内存空间，在析构函数中释放，大小为BUFFER_POOL_SIZE
                      //   std::unordered_map<PageId, frame_id_t, PageIdHash>
  //       page_table_;                   // 帧号和页面号的映射哈希表，用于根据页面的PageId定位该页面的帧编号
  std::list<frame_id_t> free_list_;  // 空闲帧编号的链表
  DiskManager *disk_manager_;
  Replacer *replacer_;  // buffer_pool的置换策略，当前赛题中为LRU置换策略
  std::mutex latch_;    // 用于共享数据结构的并发控制

  std::vector<PageTableSegment> page_table_segemets_;  // 以分段来拆大锁

  std::mutex free_list_mutex_;  // 保护空闲帧的锁
                                //   std::vector<std::mutex> frame_latches_;  // 保护所有帧的锁

 public:
  BufferPoolManager(size_t pool_size, DiskManager *disk_manager) : pool_size_(pool_size), disk_manager_(disk_manager) {
    // 为buffer pool分配一块连续的内存空间
    pages_ = new Page[pool_size_];
    // 可以被Replacer改变
    if (REPLACER_TYPE.compare("LRU"))
      replacer_ = new LRUReplacer(pool_size_);
    else if (REPLACER_TYPE.compare("CLOCK"))
      replacer_ = new LRUReplacer(pool_size_);
    else {
      replacer_ = new LRUReplacer(pool_size_);
    }
    // 初始化时，所有的page都在free_list_中
    for (size_t i = 0; i < pool_size_; ++i) {
      free_list_.emplace_back(static_cast<frame_id_t>(i));  // static_cast转换数据类型
    }

    page_table_segemets_.resize(PAGE_TABLE_SEGEMENTS);
    // 为哈希预分配
    size_t seg_size = (pool_size_ / PAGE_TABLE_SEGEMENTS) * 2 + 16;
    for (auto &seg : page_table_segemets_) seg.page_table.reserve(seg_size);

    // frame_latches_.resize(pool_size_);
  }

  ~BufferPoolManager() {
    delete[] pages_;
    delete replacer_;
  }

  /**
   * @description: 将目标页面标记为脏页
   * @param {Page*} page 脏页
   */
  static void mark_dirty(Page *page) { page->is_dirty_ = true; }

 public:
  Page *fetch_page(PageId page_id);

  bool unpin_page(PageId page_id, bool is_dirty);

  bool flush_page(PageId page_id);

  Page *new_page(PageId *page_id);

  bool delete_page(PageId page_id);

  void flush_all_pages(int fd);

 private:
  bool find_victim_page(frame_id_t *frame_id);

  void update_page(Page *page, PageId new_page_id, frame_id_t new_frame_id);

  inline PageTableSegment &get_seg(const PageId &page_id) {
    size_t idx = std::hash<int64_t>{}(page_id.fd ^ page_id.page_no);
    return page_table_segemets_[idx % PAGE_TABLE_SEGEMENTS];
  }
};