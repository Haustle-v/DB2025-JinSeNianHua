/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "buffer_pool_manager.h"

/**
 * @description: 从free_list或replacer中得到可淘汰帧页的 *frame_id
 * @return {bool} true: 可替换帧查找成功 , false: 可替换帧查找失败
 * @param {frame_id_t*} frame_id 帧页id指针,返回成功找到的可替换帧id
 */
bool BufferPoolManager::find_victim_page(frame_id_t *frame_id) {
  // Todo:
  // 1 使用BufferPoolManager::free_list_判断缓冲池是否已满需要淘汰页面
  // 1.1 未满获得frame
  // 1.2 已满使用lru_replacer中的方法选择淘汰页面

  // 先在空闲队列中找
  {
    std::scoped_lock<std::mutex> lck(free_list_mutex_);
    if (!free_list_.empty()) {
      // 未满则直接分配
      *frame_id = free_list_.front();
      free_list_.pop_front();
      return true;
    }
  }

  //   没有空闲页则替换
  frame_id_t target_frame_id = INVALID_FRAME_ID;
  // 满了则替换 无论是否有成功 都会正确赋给tarfget
  replacer_->victim(&target_frame_id);
  *frame_id = target_frame_id;

  if (target_frame_id != INVALID_FRAME_ID) {
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
void BufferPoolManager::update_page(Page *page, PageId new_page_id, frame_id_t new_frame_id) {
  // 不再使用这个函数
  //   // Todo:
  //   // 1 如果是脏页，写回磁盘，并且把dirty置为false
  //   // 2 更新page table
  //   // 3 重置page的data，更新page id

  //   //   脏页判断
  //   if (page->is_dirty()) {
  //     disk_manager_->write_page(page->id_.fd, page->id_.page_no, page->get_data(), PAGE_SIZE);
  //     page->is_dirty_ = false;
  //   }

  //   //   数据页更新 不相等更新键值对 相等则修正
  //   if (!(page->id_ == new_page_id)) {
  //     page_table_.erase(page->id_);
  //     page_table_.emplace(new_page_id, new_frame_id);
  //   } else {
  //     page_table_[page->id_] = new_frame_id;
  //   }

  //   //   更新元数据
  //   page->id_ = new_page_id;
  //   //   page->reset_memory();  创建新页的时候强制刷盘
  //   //   page->set_page_lsn(INVALID_LSN);
}

/**
 * @description: 从buffer pool获取需要的页。
 *              如果页表中存在page_id（说明该page在缓冲池中），并且pin_count++。
 *              如果页表不存在page_id（说明该page在磁盘中），则找缓冲池victim
 * page，将其替换为磁盘中读取的page，pin_count置1。
 * @return {Page*} 若获得了需要的页则将其返回，否则返回nullptr
 * @param {PageId} page_id 需要获取的页的PageId
 */
Page *BufferPoolManager::fetch_page(PageId page_id) {
  // Todo:
  //  1.     从page_table_中搜寻目标页
  //  1.1 若目标页有被page_table_记录，则将其所在frame固定(pin)，并返回目标页。
  //  1.2 否则，尝试调用find_victim_page获得一个可用的frame，若失败则返回nullptr
  //  2.     若获得的可用frame存储的为dirty
  //  page，则须调用updata_page将page写回到磁盘
  //  3.     调用disk_manager_的read_page读取目标页到frame
  //  4.     固定目标页，更新pin_count_
  //  5.     返回目标页

  //   并发查找
  PageTableSegment &seg = get_seg(page_id);
  {
    std::shared_lock<std::shared_mutex> read_lock(seg.mutex);
    auto iter = seg.page_table.find(page_id);
    if (iter != seg.page_table.end()) {
      // 缓存命中
      Page &target_page = pages_[iter->second];
      std::scoped_lock<std::mutex> page_lock(target_page.frame_latch_);
      //   双重检查，避免修改
      if (target_page.id_ == page_id) {
        ++target_page.pin_count_;
        replacer_->pin(iter->second);  // unpin会在外面被调用 这里必须加
        return &target_page;
      }
      //   id不匹配，说明被其它线程修改了
      return fetch_page(page_id);
    }
  }

  // 缓存未命中 找可用页框
  frame_id_t useable_frame_id = INVALID_FRAME_ID;
  if (!find_victim_page(&useable_frame_id)) {
    return nullptr;  // 无空闲页框
  }

  Page &victim_page = pages_[useable_frame_id];
  PageId old_page_id;
  {
    std::unique_lock<std::mutex> page_lock(victim_page.frame_latch_);
    old_page_id = victim_page.id_;
    page_lock.unlock();

    //   剔除旧映射
    PageTableSegment &old_seg = get_seg(old_page_id);
    std::unique_lock<std::shared_mutex> old_seg_lock(old_seg.mutex);
    page_lock.lock();

    // 检查页面是否被修改
    if (!(victim_page.id_ == old_page_id)) {
      // 页面被其它线程修改 重试
      return fetch_page(page_id);
    }

    // 取消旧映射
    old_seg.page_table.erase(old_page_id);

    //   脏页刷盘
    if (victim_page.is_dirty()) {
      disk_manager_->write_page(old_page_id.fd, old_page_id.page_no, victim_page.get_data(), PAGE_SIZE);
      victim_page.is_dirty_ = false;
    }
    // 将目标页读入到给定页框
    disk_manager_->read_page(page_id.fd, page_id.page_no, victim_page.get_data(), PAGE_SIZE);

    //   更新元数据
    victim_page.id_ = page_id;
    victim_page.is_dirty_ = false;
    victim_page.set_page_lsn(INVALID_LSN);
    //    加载到内存时把它定住
    victim_page.pin_count_ = 1;
    replacer_->pin(useable_frame_id);
  }

  //   新映射
  {
    std::unique_lock<std::shared_mutex> lck(seg.mutex);
    // 检查是否被其它线程加载
    if (seg.page_table.count(page_id) > 0) {
      frame_id_t existing_frame = seg.page_table[page_id];
      Page &exist_page = pages_[existing_frame];
      std::scoped_lock<std::mutex> exist_page_lock(exist_page.frame_latch_);
      //   双重检查确保一致
      if (exist_page.id_ == page_id) {
        ++exist_page.pin_count_;
        replacer_->pin(existing_frame);
      }

      //   将victim_page复原
      victim_page.pin_count_ = 0;
      {
        std::scoped_lock<std::mutex> free_lock(free_list_mutex_);
        free_list_.emplace_back(useable_frame_id);
      }
      return &exist_page;
    }
    seg.page_table[page_id] = useable_frame_id;
  }

  replacer_->pin(useable_frame_id);
  return &victim_page;
}

/**
 * @description: 取消固定pin_count>0的在缓冲池中的page
 * @return {bool} 如果目标页的pin_count<=0则返回false，否则返回true
 * @param {PageId} page_id 目标page的page_id
 * @param {bool} is_dirty 若目标page应该被标记为dirty则为true，否则为false
 */
bool BufferPoolManager::unpin_page(PageId page_id, bool is_dirty) {
  // Todo:
  // 0. lock latch
  // 1. 尝试在page_table_中搜寻page_id对应的页P
  // 1.1 P在页表中不存在 return false
  // 1.2 P在页表中存在，获取其pin_count_
  // 2.1 若pin_count_已经等于0，则返回false
  // 2.2 若pin_count_大于0，则pin_count_自减一
  // 2.2.1 若自减后等于0，则调用replacer_的Unpin
  // 3 根据参数is_dirty，更改P的is_dirty_

  //   std::scoped_lock<std::mutex> lock(latch_);
  PageTableSegment &seg = get_seg(page_id);
  frame_id_t target_frame_id = INVALID_FRAME_ID;
  {
    std::shared_lock<std::shared_mutex> read_lock(seg.mutex);
    auto iter = seg.page_table.find(page_id);

    if (iter == seg.page_table.end()) {
      // 不在缓存 直接false
      return false;
    }
    target_frame_id = iter->second;
  }

  Page &target_page = pages_[target_frame_id];
  std::scoped_lock<std::mutex> page_lck(target_page.frame_latch_);

  //   双重检查确保一致
  if (!(target_page.id_ == page_id)) {
    return false;  // 页面被其它线程修改
  }

  if (target_page.pin_count_ == 0) {
    return false;
  }

  //   pc大于0 自减后判断
  --target_page.pin_count_;
  if (target_page.pin_count_ == 0) {
    replacer_->unpin(target_frame_id);
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
bool BufferPoolManager::flush_page(PageId page_id) {
  // Todo:
  // 0. lock latch
  // 1. 查找页表,尝试获取目标页P
  // 1.1 目标页P没有被page_table_记录 ，返回false
  // 2. 无论P是否为脏都将其写回磁盘。
  // 3. 更新P的is_dirty_
  assert(page_id.page_no != INVALID_PAGE_ID && "bpm flush invalid page");
  //   std::scoped_lock<std::mutex> lock(latch_);
  PageTableSegment &seg = get_seg(page_id);
  frame_id_t target_frame_id = INVALID_FRAME_ID;
  {
    std::shared_lock<std::shared_mutex> read_lock(seg.mutex);
    auto iter = seg.page_table.find(page_id);
    if (iter == seg.page_table.end()) {
      // 不在缓存 直接false
      return false;
    }
    target_frame_id = iter->second;
  }

  Page &target_page = pages_[target_frame_id];
  std::scoped_lock<std::mutex> page_lck(target_page.frame_latch_);

  //   双重检查确保一致
  if (!(target_page.id_ == page_id)) {
    return false;  // 页面被其它线程修改
  }

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
Page *BufferPoolManager::new_page(PageId *page_id) {
  // 1.   获得一个可用的frame，若无法获得则返回nullptr
  // 2.   在fd对应的文件分配一个新的page_id
  // 3.   将frame的数据写回磁盘
  // 4.   固定frame，更新pin_count_
  // 5.   返回获得的page

  //   std::scoped_lock<std::mutex> lock(latch_);
  frame_id_t usable_frame_id = INVALID_FRAME_ID;

  //   找可用页框
  if (!find_victim_page(&usable_frame_id)) {
    return nullptr;
  }

  //   获取当前页id
  Page &target_page = pages_[usable_frame_id];
  PageId old_page_id;
  {
    std::scoped_lock<std::mutex> page_lck(target_page.frame_latch_);
    old_page_id = target_page.id_;
  }

  // 移除旧映射
  {
    PageTableSegment &old_seg = get_seg(old_page_id);
    std::unique_lock<std::shared_mutex> lck(old_seg.mutex);
    old_seg.page_table.erase(old_page_id);
  }

  {
    std::scoped_lock<std::mutex> page_lck(target_page.frame_latch_);
    // 检查页面是否被其它线程修改
    if (!(target_page.id_ == old_page_id)) {
      return new_page(page_id);  // 页面被其它线程修改 重试
    }

    if (target_page.is_dirty()) {
      disk_manager_->write_page(old_page_id.fd, old_page_id.page_no, target_page.get_data(), PAGE_SIZE);
      target_page.is_dirty_ = false;
    }

    //   更新元数据
    page_id->page_no = disk_manager_->allocate_page(page_id->fd);
    target_page.id_ = *page_id;
    target_page.reset_memory();
    target_page.set_page_lsn(INVALID_LSN);

    replacer_->pin(usable_frame_id);
    target_page.pin_count_ = 1;
  }

  //   插入page_table
  PageTableSegment &new_seg = get_seg(*page_id);
  {
    std::unique_lock<std::shared_mutex> lck(new_seg.mutex);
    new_seg.page_table.emplace(*page_id, usable_frame_id);
  }

  return &target_page;
}

/**
 * @description: 从buffer_pool删除目标页
 * @return {bool}
 * 如果目标页不存在于buffer_pool或者成功被删除则返回true，若其存在于buffer_pool但无法删除则返回false
 * @param {PageId} page_id 目标页
 */
bool BufferPoolManager::delete_page(PageId page_id) {
  // 1.   在page_table_中查找目标页，若不存在返回true
  // 2.   若目标页的pin_count不为0，则返回false
  // 3.
  // 将目标页数据写回磁盘，从页表中删除目标页，重置其元数据，将其加入free_list_，返回true

  //   std::scoped_lock<std::mutex> lock(latch_);
  PageTableSegment &seg = get_seg(page_id);
  frame_id_t target_frame_id = INVALID_FRAME_ID;

  {
    std::shared_lock<std::shared_mutex> lck(seg.mutex);
    auto iter = seg.page_table.find(page_id);
    if (iter == seg.page_table.end()) {
      return true;
    }
    target_frame_id = iter->second;
  }

  Page &target_page = pages_[target_frame_id];
  std::scoped_lock<std::mutex> page_lck(target_page.frame_latch_);
  // 检查页面是否被其它线程修改
  if (!(target_page.id_ == page_id)) {
    return true;  // 页面被其它线程修改 相当于删除成功
  }

  if (target_page.pin_count_ == 0) {
    // 移除映射

    std::unique_lock<std::shared_mutex> write_lock(seg.mutex);
    //   检查映射表决定删除
    auto iter = seg.page_table.find(page_id);
    if (iter != seg.page_table.end() && iter->second == target_frame_id) {
      seg.page_table.erase(page_id);
    }

    // pc为0才能删
    if (target_page.is_dirty_) {
      disk_manager_->write_page(target_page.id_.fd, target_page.id_.page_no, target_page.get_data(), PAGE_SIZE);
    }
    target_page.reset_memory();
    target_page.id_.fd = -1;
    target_page.id_.page_no = INVALID_PAGE_ID;
    target_page.is_dirty_ = false;

    {
      // 加入空闲队列
      std::scoped_lock<std::mutex> free_lk(free_list_mutex_);
      free_list_.emplace_back(target_frame_id);
    }
    return true;
  }

  //   pc大于0返回false
  return false;
}

/**
 * @description: 将buffer_pool中的所有页写回到磁盘
 * @param {int} fd 文件句柄
 */
void BufferPoolManager::flush_all_pages(int fd) {
  //   std::scoped_lock<std::mutex> lock(latch_);
  page_id_t max_page_no = disk_manager_->get_fd2pageno(fd);
  PageId cur_page_id{fd, INVALID_PAGE_ID};
  //   仅查找和删除fd下的页
  // 简单调整一下 max_page_no可能比缓冲池大很多
  if (max_page_no > pool_size_) {
    for (page_id_t frame_no = 0; frame_no < pool_size_; ++frame_no) {
      std::scoped_lock<std::mutex> page_lck(pages_[frame_no].frame_latch_);
      const PageId &page_id = pages_[frame_no].get_page_id();
      if (page_id.fd == fd && page_id.page_no != INVALID_PAGE_ID) {
        disk_manager_->write_page(fd, page_id.page_no, pages_[frame_no].get_data(), PAGE_SIZE);
        pages_[frame_no].is_dirty_ = false;
      }
    }
  } else {
    for (page_id_t page_no = 0; page_no < max_page_no; ++page_no) {
      cur_page_id.page_no = page_no;
      PageTableSegment &seg = get_seg(cur_page_id);
      frame_id_t target_frame_id = INVALID_FRAME_ID;
      {
        std::shared_lock<std::shared_mutex> read_lock(seg.mutex);
        auto iter = seg.page_table.find(cur_page_id);
        if (iter == seg.page_table.end()) continue;
        target_frame_id = iter->second;
      }

      Page &target_page = pages_[target_frame_id];
      std::scoped_lock<std::mutex> page_lck(target_page.frame_latch_);
      //   双重检查
      if (target_page.id_.fd == fd && target_page.id_.page_no == page_no) {
        // 外部可以直接写page的data 所以dirty目前框架是有问题的 全部刷新！
        disk_manager_->write_page(fd, page_no, target_page.get_data(), PAGE_SIZE);
        target_page.is_dirty_ = false;
      }
    }
  }
}