/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "rm_file_handle.h"

/**
 * @description: 获取当前表中记录号为rid的记录
 * @param {Rid&} rid 记录号，指定记录的位置
 * @param {Context*} context
 * @return {unique_ptr<RmRecord>} rid对应的记录对象指针
 */
std::unique_ptr<RmRecord> RmFileHandle::get_record(const Rid &rid, Context *context) const {
  // Todo:
  // 1. 获取指定记录所在的page handle
  // 2. 初始化一个指向RmRecord的指针（赋值其内部的data和size）

  // std::scoped_lock<std::mutex> lock(latch_);
  // sqb 事务并发控制 6.9
  //   if (context != nullptr) {
  //     context->lock_mgr_->lock_shared_on_record(context->txn_, rid, fd_);
  //   }
  RmPageHandle page_hdl = fetch_page_handle(rid.page_no);
  std::shared_lock<std::shared_mutex> lock(latch_);
  assert(Bitmap::is_set(page_hdl.bitmap, rid.slot_no));
  std::unique_ptr<RmRecord> record_ptr =
      std::make_unique<RmRecord>(file_hdr_.record_size, page_hdl.get_slot(rid.slot_no));

  //   这个bfm不是raii管理页 数据操作注意释放
  buffer_pool_manager_->unpin_page(page_hdl.page->get_page_id(), false);
  return record_ptr;
}

/**
 * @description: 在当前表中插入一条记录，不指定插入位置
 * @param {char*} buf 要插入的记录的数据
 * @param {Context*} context
 * @return {Rid} 插入的记录的记录号（位置）
 */
Rid RmFileHandle::insert_record(char *buf, Context *context) {
  // Todo:
  // 1. 获取当前未满的page handle
  // 2. 在page handle中找到空闲slot位置
  // 3. 将buf复制到空闲slot位置
  // 4. 更新page_handle.page_hdr中的数据结构
  // 注意考虑插入一条记录后页面已满的情况，需要更新file_hdr_.first_free_page_no

  std::unique_lock<std::shared_mutex> lock(latch_);
  RmPageHandle page_hdl = create_page_handle();

  // 找空闲位置
  int free_slot_no = Bitmap::next_bit(0, page_hdl.bitmap, file_hdr_.num_records_per_page, -1);
  Rid ret{page_hdl.page->get_page_id().page_no, free_slot_no};

  //   sqb 加入事务控制 日志 6.5
  if (context != nullptr && (context->txn_->get_state() == TransactionState::DEFAULT ||
                             context->txn_->get_state() == TransactionState::GROWING)) {
    // 事务并发控制 6.9
    // context->lock_mgr_->lock_exclusive_on_record(context->txn_, ret, fd_);

    // 事务记录
    RmRecord new_rec = RmRecord(file_hdr_.record_size, buf);
    std::string tab_name = disk_manager_->get_file_name(fd_);
    auto insert_wrec = std::make_unique<WriteRecord>(WType::INSERT_TUPLE, tab_name, ret);
    context->txn_->append_write_record(std::move(insert_wrec));

    // 日志记录
    InsertLogRecord log_record{context->txn_->get_transaction_id(), new_rec, ret, tab_name};
    log_record.prev_lsn_ = context->txn_->get_prev_lsn();
    lsn_t insert_lsn = context->log_mgr_->add_log_to_buffer(&log_record);
    context->txn_->set_prev_lsn(insert_lsn);

    // 当前页的日志
    page_hdl.page->set_page_lsn(insert_lsn);
  }

  memcpy(page_hdl.get_slot(free_slot_no), buf, file_hdr_.record_size);
  Bitmap::set(page_hdl.bitmap, free_slot_no);

  page_hdl.page_hdr->num_records++;
  if (page_hdl.page_hdr->num_records == file_hdr_.num_records_per_page) {
    file_hdr_.first_free_page_no = page_hdl.page_hdr->next_free_page_no;
  }

  //   当前数据为脏
  buffer_pool_manager_->unpin_page(page_hdl.page->get_page_id(), true);

  return ret;
}

/**
 * @description: 在当前表中的指定位置插入一条记录
 * @param {Rid&} rid 要插入记录的位置
 * @param {char*} buf 要插入记录的数据
 */
void RmFileHandle::insert_record(const Rid &rid, char *buf) {
  std::unique_lock<std::shared_mutex> lock(latch_);

  RmPageHandle page_hdl = fetch_page_handle(rid.page_no);
  memcpy(page_hdl.get_slot(rid.slot_no), buf, file_hdr_.record_size);

  //   新的插入就得更新
  if (!Bitmap::is_set(page_hdl.bitmap, rid.slot_no)) {
    page_hdl.page_hdr->num_records++;
    Bitmap::set(page_hdl.bitmap, rid.slot_no);
    if (page_hdl.page_hdr->num_records == file_hdr_.num_records_per_page) {
      file_hdr_.first_free_page_no = page_hdl.page_hdr->next_free_page_no;
    }
  }
  //   当前数据为脏
  buffer_pool_manager_->unpin_page(page_hdl.page->get_page_id(), true);
}

/**
 * @description: 删除记录文件中记录号为rid的记录
 * @param {Rid&} rid 要删除的记录的记录号（位置）
 * @param {Context*} context
 */
void RmFileHandle::delete_record(const Rid &rid, Context *context, RmRecord *old_rec) {
  // Todo:
  // 1. 获取指定记录所在的page handle
  // 2. 更新page_handle.page_hdr中的数据结构
  // 注意考虑删除一条记录后页面未满的情况，需要调用release_page_handle()

  //   还是只考虑rid存在的情况
  std::unique_lock<std::shared_mutex> lock(latch_);
  RmPageHandle page_hdl = fetch_page_handle(rid.page_no);

  // sqb添加事务控制语句 日志 6.5
  if (context != nullptr && (context->txn_->get_state() == TransactionState::DEFAULT ||
                             context->txn_->get_state() == TransactionState::GROWING)) {
    // 事务并发控制 6.9
    // context->lock_mgr_->lock_exclusive_on_record(context->txn_, rid, fd_);

    // 事务记录
    std::string tab_name = disk_manager_->get_file_name(fd_);
    auto delete_wrec = std::make_unique<WriteRecord>(WType::DELETE_TUPLE, tab_name, rid, *old_rec);
    context->txn_->append_write_record(std::move(delete_wrec));

    // 日志记录
    DeleteLogRecord log_record{context->txn_->get_transaction_id(), *old_rec, rid, tab_name};
    log_record.prev_lsn_ = context->txn_->get_prev_lsn();
    lsn_t delete_lsn = context->log_mgr_->add_log_to_buffer(&log_record);
    context->txn_->set_prev_lsn(delete_lsn);

    // 页日志
    page_hdl.page->set_page_lsn(delete_lsn);
  }

  //   删除先不动内存 因为get那里做了检查
  Bitmap ::reset(page_hdl.bitmap, rid.slot_no);
  //   考虑release
  --page_hdl.page_hdr->num_records;
  if (page_hdl.page_hdr->num_records == file_hdr_.num_records_per_page - 1) {
    release_page_handle(page_hdl);
  }
  //   当前数据为脏
  buffer_pool_manager_->unpin_page(page_hdl.page->get_page_id(), true);
}

/**
 * @description: 更新记录文件中记录号为rid的记录
 * @param {Rid&} rid 要更新的记录的记录号（位置）
 * @param {char*} buf 新记录的数据
 * @param {Context*} context
 */
void RmFileHandle::update_record(const Rid &rid, char *buf, Context *context, RmRecord *old_rec) {
  // Todo:
  // 1. 获取指定记录所在的page handle
  // 2. 更新记录

  //   暂时只考虑数据存在的情况
  std::unique_lock<std::shared_mutex> lock(latch_);

  RmPageHandle page_hdl = fetch_page_handle(rid.page_no);
  assert(Bitmap::is_set(page_hdl.bitmap, rid.slot_no));

  // sqb添加事务控制语句 日志 6.5
  if (context != nullptr && (context->txn_->get_state() == TransactionState::DEFAULT ||
                             context->txn_->get_state() == TransactionState::GROWING)) {
    // 事务并发控制 6.9
    // context->lock_mgr_->lock_exclusive_on_record(context->txn_, rid, fd_);

    // 事务记录
    std::string tab_name = disk_manager_->get_file_name(fd_);
    auto update_wrec = std::make_unique<WriteRecord>(WType::UPDATE_TUPLE, tab_name, rid, *old_rec);
    context->txn_->append_write_record(std::move(update_wrec));

    // 日志记录
    RmRecord new_rec = RmRecord(file_hdr_.record_size, buf);
    UpdateLogRecord log_record{context->txn_->get_transaction_id(), *old_rec, new_rec, rid, tab_name};
    log_record.prev_lsn_ = context->txn_->get_prev_lsn();
    lsn_t update_lsn = context->log_mgr_->add_log_to_buffer(&log_record);
    context->txn_->set_prev_lsn(update_lsn);

    // 页日志
    page_hdl.page->set_page_lsn(update_lsn);
  }

  memcpy(page_hdl.get_slot(rid.slot_no), buf, file_hdr_.record_size);
  // Bitmap::set(page_hdl.bitmap, rid.slot_no);  // 出于保险加上先

  //   当前数据为脏
  buffer_pool_manager_->unpin_page(page_hdl.page->get_page_id(), true);
}

/**
 * 以下函数为辅助函数，仅提供参考，可以选择完成如下函数，也可以删除如下函数，在单元测试中不涉及如下函数接口的直接调用
 */
/**
 * @description: 获取指定页面的页面句柄
 * @param {int} page_no 页面号
 * @return {RmPageHandle} 指定页面的句柄
 */
RmPageHandle RmFileHandle::fetch_page_handle(int page_no) const {
  // Todo:
  // 使用缓冲池获取指定页面，并生成page_handle返回给上层
  // if page_no is invalid, throw PageNotExistError exception
  if (page_no == INVALID_PAGE_ID) {
    throw PageNotExistError(disk_manager_->get_file_name(fd_), page_no);
  }
  PageId target_page_id{fd_, page_no};
  Page *target_page = buffer_pool_manager_->fetch_page(target_page_id);
  //   按理来说得抛异常 断言先试试
  assert(target_page != nullptr);
  return RmPageHandle(&file_hdr_, target_page);
}

/**
 * @description: 创建一个新的page handle
 * @return {RmPageHandle} 新的PageHandle
 */
RmPageHandle RmFileHandle::create_new_page_handle() {
  // Todo:
  // 1.使用缓冲池来创建一个新page
  // 2.更新page handle中的相关信息
  // 3.更新file_hdr_

  // 在磁盘上获得一个新的page
  PageId new_page_id{fd_, INVALID_PAGE_ID};
  Page *new_page = buffer_pool_manager_->new_page(&new_page_id);

  //   对空页框进行初始化
  RmPageHandle page_hdl{&file_hdr_, new_page};
  Bitmap::init(page_hdl.bitmap, file_hdr_.bitmap_size);
  page_hdl.page_hdr->next_free_page_no = file_hdr_.first_free_page_no;

  //   更新file_hdr_
  file_hdr_.num_pages++;
  file_hdr_.first_free_page_no = new_page_id.page_no;

  return page_hdl;
}

/**
 * @brief 创建或获取一个空闲的page handle
 *
 * @return RmPageHandle 返回生成的空闲page handle
 * @note pin the page, remember to unpin it outside!
 */
RmPageHandle RmFileHandle::create_page_handle() {
  // Todo:
  // 1. 判断file_hdr_中是否还有空闲页
  //     1.1
  //     没有空闲页：使用缓冲池来创建一个新page；可直接调用create_new_page_handle()
  //     1.2 有空闲页：直接获取第一个空闲页
  // 2. 生成page handle并返回给上层

  if (file_hdr_.first_free_page_no == INVALID_PAGE_ID) {
    // 没有空闲页
    return create_new_page_handle();
  }

  //   有空闲页
  return fetch_page_handle(file_hdr_.first_free_page_no);
}

/**
 * @description:
 * 当一个页面从没有空闲空间的状态变为有空闲空间状态时，更新文件头和页头中空闲页面相关的元数据
 */
void RmFileHandle::release_page_handle(RmPageHandle &page_handle) {
  // Todo:
  // 当page从已满变成未满，考虑如何更新：
  // 1. page_handle.page_hdr->next_free_page_no
  // 2. file_hdr_.first_free_page_no

  page_handle.page_hdr->next_free_page_no = file_hdr_.first_free_page_no;
  file_hdr_.first_free_page_no = page_handle.page->get_page_id().page_no;
}

// sqb 避免故障恢复时 访问不存在的页报错  6.11
void RmFileHandle::allocate_pages(const Rid &rid) {
  while (rid.page_no >= file_hdr_.num_pages) {
    RmPageHandle page_hdl = create_new_page_handle();
    buffer_pool_manager_->unpin_page(page_hdl.page->get_page_id(), false);
  }
}
