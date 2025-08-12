/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "buffer_pool_object.h"

/**
 * @description: 从free_list或replacer中得到可淘汰帧页的 *frame_id
 * @return {bool} true: 可替换帧查找成功 , false: 可替换帧查找失败
 * @param {frame_id_t*} frame_id 帧页id指针,返回成功找到的可替换帧id
 */
bool BufferPoolObject::find_victim_page(frame_id_t *frame_id) {
  // Todo:
  // 1 使用BufferPoolManager::free_list_判断缓冲池是否已满需要淘汰页面
  // 1.1 未满获得frame
  // 1.2 已满使用lru_replacer中的方法选择淘汰页面

  //   该函数不用加锁 其它调用函数会加锁的
  frame_id_t target_frame_id = INVALID_FRAME_ID;
  if (!free_list_.empty()) {
    // 未满则直接分配
    target_frame_id = free_list_.front();
    free_list_.pop_front();
  } else {
    // 满了则替换 无论是否有成功 都会正确赋给tarfget
    replacer_->victim(&target_frame_id);
  }

  *frame_id = target_frame_id;

  if (target_frame_id != INVALID_FRAME_ID) {
    // std::cerr << "[DEBUG] bpm victim frame " << target_frame_id << std::endl;
    return true;
  }

  return false;
}

/**
 * @description: 更新页面数据,
 * 如果为脏页则需写入磁盘，再更新为新页面，更新page元数据(data, is_dirty,
 * page_id)和page table
 * @param {Page*} page 写回页指针
 * @param {PageId} new_page_id 新的page_id
 * @param {frame_id_t} new_frame_id 新的帧frame_id
 */
void BufferPoolObject::update_page(Page *page, PageId new_page_id, frame_id_t new_frame_id) {
  // Todo:
  // 1 如果是脏页，写回磁盘，并且把dirty置为false
  // 2 更新page table
  // 3 重置page的data，更新page id

  //   脏页判断
  if (page->is_dirty()) {
    // ++evictions_;
    disk_manager_->write_page(page->id_.fd, page->id_.page_no, page->get_data(), PAGE_SIZE);
    page->is_dirty_ = false;
  }

  //   数据页更新 不相等更新键值对 相等则修正
  if (!(page->id_ == new_page_id)) {
    page_table_.erase(page->id_);
    page_table_.emplace(new_page_id, new_frame_id);
  } else {
    page_table_[page->id_] = new_frame_id;
  }

  //   更新元数据
  page->id_ = new_page_id;
  page->reset_memory();
  page->set_page_lsn(INVALID_LSN);
}

/**
 * @description: 从buffer pool获取需要的页。
 *              如果页表中存在page_id（说明该page在缓冲池中），并且pin_count++。
 *              如果页表不存在page_id（说明该page在磁盘中），则找缓冲池victim
 * page，将其替换为磁盘中读取的page，pin_count置1。
 * @return {Page*} 若获得了需要的页则将其返回，否则返回nullptr
 * @param {PageId} page_id 需要获取的页的PageId
 */
Page *BufferPoolObject::fetch_page(PageId page_id) {
  // Todo:
  //  1.     从page_table_中搜寻目标页
  //  1.1 若目标页有被page_table_记录，则将其所在frame固定(pin)，并返回目标页。
  //  1.2 否则，尝试调用find_victim_page获得一个可用的frame，若失败则返回nullptr
  //  2.     若获得的可用frame存储的为dirty
  //  page，则须调用updata_page将page写回到磁盘
  //  3.     调用disk_manager_的read_page读取目标页到frame
  //  4.     固定目标页，更新pin_count_
  //  5.     返回目标页

  std::shared_lock<std::shared_mutex> lock(latch_);
  auto iter = page_table_.find(page_id);
  frame_id_t useable_frame_id = INVALID_FRAME_ID;
  if (iter != page_table_.end()) {
    // 缓存命中
    Page &target_page = pages_[iter->second];
    target_page.pin_count_++;
    replacer_->pin(iter->second);  // unpin会在外面被调用 这里必须加
    // std::cerr << "[DEBUG] bpm fetch_page cached hit! page "
    //           << page_id.toString() << std::endl;
    // ++hits_;
    return &target_page;
  }

  lock.unlock();
  return fetch_page_Wlock(page_id);
}

Page *BufferPoolObject::fetch_page_Wlock(PageId page_id) {
  std::unique_lock<std::shared_mutex> lock(latch_);
  auto iter = page_table_.find(page_id);
  frame_id_t useable_frame_id = INVALID_FRAME_ID;
  if (iter != page_table_.end()) {
    // 缓存命中 这里是二次检查
    Page &target_page = pages_[iter->second];
    target_page.pin_count_++;
    replacer_->pin(iter->second);  // unpin会在外面被调用 这里必须加
    // std::cerr << "[DEBUG] bpm fetch_page cached hit! page "
    //           << page_id.toString() << std::endl;
    // ++hits_;
    return &target_page;
  }

  //   ++misses_;
  // 缓存未命中 找可用页框
  // 无空闲页框
  if (!find_victim_page(&useable_frame_id)) {
    return nullptr;
  }

  // 找到可替换页 更新相关元数据
  update_page(&pages_[useable_frame_id], page_id, useable_frame_id);

  // 将目标页读入到给定页框
  disk_manager_->read_page(page_id.fd, page_id.page_no, pages_[useable_frame_id].get_data(), PAGE_SIZE);

  //    加载到内存时把它定住
  pages_[useable_frame_id].pin_count_ = 1;
  replacer_->pin(useable_frame_id);

  return pages_ + useable_frame_id;
}

/**
 * @description: 取消固定pin_count>0的在缓冲池中的page
 * @return {bool} 如果目标页的pin_count<=0则返回false，否则返回true
 * @param {PageId} page_id 目标page的page_id
 * @param {bool} is_dirty 若目标page应该被标记为dirty则为true，否则为false
 */
bool BufferPoolObject::unpin_page(PageId page_id, bool is_dirty) {
  // Todo:
  // 0. lock latch
  // 1. 尝试在page_table_中搜寻page_id对应的页P
  // 1.1 P在页表中不存在 return false
  // 1.2 P在页表中存在，获取其pin_count_
  // 2.1 若pin_count_已经等于0，则返回false
  // 2.2 若pin_count_大于0，则pin_count_自减一
  // 2.2.1 若自减后等于0，则调用replacer_的Unpin
  // 3 根据参数is_dirty，更改P的is_dirty_

  std::shared_lock<std::shared_mutex> lock(latch_);
  auto iter = page_table_.find(page_id);

  // std::cerr << "[DEBUG] bpm unpin page " << page_id.toString()
  //           << " try set dirty " << is_dirty << std::endl;

  if (iter == page_table_.end()) {
    // 不在缓存 直接false
    return false;
  }

  Page &target_page = pages_[iter->second];
  if (target_page.pin_count_ == 0) {
    return false;
  }

  //   pc大于0 自减后判断
  --target_page.pin_count_;
  if (target_page.pin_count_ == 0) {
    // std::cerr << "[DEBUG] will unpin frame " << iter->second << std::endl;
    replacer_->unpin(iter->second);
  }

  // 虽然它本来可能是脏的 但读时调用的unpin将会是false
  if (is_dirty) {
    target_page.is_dirty_ = is_dirty;
  }
  return true;
}

/**
 * @description: 将目标页写回磁盘，不考虑当前页面是否正在被使用
 * @return {bool} 成功则返回true，否则返回false(只有page_table_中没有目标页时)
 * @param {PageId} page_id 目标页的page_id，不能为INVALID_PAGE_ID
 */
bool BufferPoolObject::flush_page(PageId page_id) {
  // Todo:
  // 0. lock latch
  // 1. 查找页表,尝试获取目标页P
  // 1.1 目标页P没有被page_table_记录 ，返回false
  // 2. 无论P是否为脏都将其写回磁盘。
  // 3. 更新P的is_dirty_
  assert(page_id.page_no != INVALID_PAGE_ID && "bpm flush invalid page");
  std::unique_lock<std::shared_mutex> lock(latch_);
  auto iter = page_table_.find(page_id);
  if (iter == page_table_.end()) {
    // 不在缓存 直接false
    return false;
  }

  Page &target_page = pages_[iter->second];
  disk_manager_->write_page(target_page.id_.fd, target_page.id_.page_no, target_page.get_data(), PAGE_SIZE);
  target_page.is_dirty_ = false;
  return true;
}

/**
 * @description:
 * 创建一个新的page，即从磁盘中移动一个新建的空page到缓冲池某个位置。
 * @return {Page*} 返回新创建的page，若创建失败则返回nullptr
 * @param {PageId*} page_id 当成功创建一个新的page时存储其page_id
 */
Page *BufferPoolObject::new_page(PageId *page_id) {
  // 1.   获得一个可用的frame，若无法获得则返回nullptr
  // 2.   在fd对应的文件分配一个新的page_id
  // 3.   将frame的数据写回磁盘
  // 4.   固定frame，更新pin_count_
  // 5.   返回获得的page

  std::unique_lock<std::shared_mutex> lock(latch_);
  frame_id_t usable_frame_id = INVALID_FRAME_ID;

  //   找可用页框
  if (!find_victim_page(&usable_frame_id)) {
    return nullptr;
  }

  Page &target_page = pages_[usable_frame_id];

  *page_id = {page_id->fd, disk_manager_->allocate_page(page_id->fd)};
  //   刷盘与更新元数据
  update_page(&target_page, *page_id, usable_frame_id);

  replacer_->pin(usable_frame_id);
  target_page.pin_count_ = 1;

  // std::cerr << "[DEBUG] bpm new page " << page_id->toString() << " on frame "
  //           << usable_frame_id << std::endl;
  return &target_page;
}

/**
 * @description: 从buffer_pool删除目标页
 * @return {bool}
 * 如果目标页不存在于buffer_pool或者成功被删除则返回true，若其存在于buffer_pool但无法删除则返回false
 * @param {PageId} page_id 目标页
 */
bool BufferPoolObject::delete_page(PageId page_id) {
  // 1.   在page_table_中查找目标页，若不存在返回true
  // 2.   若目标页的pin_count不为0，则返回false
  // 3.
  // 将目标页数据写回磁盘，从页表中删除目标页，重置其元数据，将其加入free_list_，返回true

  std::unique_lock<std::shared_mutex> lock(latch_);
  auto iter = page_table_.find(page_id);
  if (iter == page_table_.end()) {
    return true;
  }
  // std::cerr << "[DEBUG] bpm will delete page " << page_id.toString()
  //           << " frame " << iter->second << std::endl;

  Page &target_page = pages_[iter->second];
  if (target_page.pin_count_ == 0) {
    // pc为0才能删
    disk_manager_->write_page(target_page.id_.fd, target_page.id_.page_no, target_page.get_data(), PAGE_SIZE);
    // 有问题！free加入了当前页框后面就会被替换 但是同时加入lru
    // 和free可能会被使用两次！
    // replacer_->pin(iter->second);
    page_table_.erase(page_id);
    free_list_.emplace_back(iter->second);
    target_page.id_.fd = -1;
    target_page.id_.page_no = INVALID_PAGE_ID;
    target_page.reset_memory();
    target_page.is_dirty_ = false;
    return true;
  }
  //   pc大于0返回false
  return false;
}

/**
 * @description: 将buffer_pool中的所有页写回到磁盘
 * @param {int} fd 文件句柄
 */
void BufferPoolObject::flush_all_pages(int fd) {
  std::unique_lock<std::shared_mutex> lock(latch_);
  page_id_t max_page_no = disk_manager_->get_fd2pageno(fd);
  PageId cur_page_id{fd, INVALID_PAGE_ID};
  //   仅查找和删除fd下的页
  // 简单调整一下 max_page_no可能比缓冲池大很多
  if (max_page_no > pool_size_) {
    for (page_id_t frame_no = 0; frame_no < pool_size_; ++frame_no) {
      const PageId &page_id = pages_[frame_no].get_page_id();
      if (page_id.fd == fd && page_id.page_no != INVALID_PAGE_ID) {
        disk_manager_->write_page(fd, page_id.page_no, pages_[frame_no].get_data(), PAGE_SIZE);
        pages_[frame_no].is_dirty_ = false;
      }
    }
  } else {
    for (page_id_t page_no = 0; page_no < max_page_no; ++page_no) {
      cur_page_id.page_no = page_no;
      auto iter = page_table_.find(cur_page_id);
      if (iter != page_table_.end()) {
        Page &target_page = pages_[iter->second];
        // 外部可以直接写page的data 所以dirty目前框架是有问题的 全部刷新！
        // if (target_page.is_dirty()) {
        disk_manager_->write_page(fd, page_no, target_page.get_data(), PAGE_SIZE);
        target_page.is_dirty_ = false;
        // }
      }
    }
  }
}