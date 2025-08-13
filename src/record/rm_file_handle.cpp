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
#include "execution/execution_common.h"  //sqb

/**
 * @description: 获取当前表中记录号为rid的记录  sqb--MVCC下相当于获得最新的tuple
 * @param {Rid&} rid 记录号，指定记录的位置
 * @param {Context*} context
 * @return {unique_ptr<RmRecord>} rid对应的记录对象指针
 */
std::unique_ptr<RmRecord> RmFileHandle::get_record(const Rid &rid, Context *context) {
  // Todo:
  // 1. 获取指定记录所在的page handle
  // 2. 初始化一个指向RmRecord的指针（赋值其内部的data和size）

  //   std::shared_lock<std::shared_mutex> lock(latch_);
  std::unique_ptr<RmRecord> record_ptr = nullptr;
  RmPageHandle page_hdl = fetch_page_handle(rid.page_no);
  //   page_hdl.page->RLatch();
  assert(Bitmap::is_set(page_hdl.bitmap, rid.slot_no));
  {
    auto rec_latch_ptr = get_rec_latch(rid);
    std::shared_lock<std::shared_mutex> rec_lock(*rec_latch_ptr);
    record_ptr = std::make_unique<RmRecord>(file_hdr_.record_size, page_hdl.get_slot_record(rid.slot_no));
  }
  //   page_hdl.page->RUnlatch();
  //   这个bfm不是raii管理页 数据操作注意释放
  buffer_pool_manager_->unpin_page(page_hdl.page->get_page_id(), false);
  return record_ptr;
}

// sqb 6.17 关于tuple meta undo link的查询 为保证原子性才这么写
auto RmFileHandle::get_tuple_and_undoLink(const Rid &rid, Context *context)
    -> std::tuple<TupleMeta, RmRecord, std::optional<UndoLink>> {
  std::tuple<TupleMeta, RmRecord, std::optional<UndoLink>> ret;
  //   std::shared_lock<std::shared_mutex> lock(latch_);
  RmPageHandle page_hdl = fetch_page_handle(rid.page_no);
  //   page_hdl.page->RLatch();
  assert(Bitmap::is_set(page_hdl.bitmap, rid.slot_no));

  //   找行锁 加锁读数据
  {
    auto rec_latch_ptr = get_rec_latch(rid);
    std::shared_lock<std::shared_mutex> rec_lock(*rec_latch_ptr);
    TupleMeta tuple_meta = *(TupleMeta *)(page_hdl.get_slot_meta(rid.slot_no));
    RmRecord tuple(file_hdr_.record_size, page_hdl.get_slot_record(rid.slot_no));

    auto undo_link = context->txn_mgr_->GetUndoLink(fd_, rid);
    ret = std::make_tuple(tuple_meta, tuple, undo_link);
  }

  //   page_hdl.page->RUnlatch();
  buffer_pool_manager_->unpin_page(page_hdl.page->get_page_id(), false);
  return ret;
}

// sqb 6.17 事务commit时更新所有写操作的时间戳 undo_log的时间戳应该一起更改
void RmFileHandle::set_meta_ts(Transaction *txn, size_t log_idx, const Rid &rid, timestamp_t ts) {
  //   std::unique_lock<std::shared_mutex> lock(latch_);
  RmPageHandle page_hdl = fetch_page_handle(rid.page_no);
  //   page_hdl.page->WLatch();

  //   找行锁 加锁写数据
  {
    auto rec_latch_ptr = get_rec_latch(rid);
    std::unique_lock<std::shared_mutex> rec_lock(*rec_latch_ptr);
    TupleMeta &base_meta = *(TupleMeta *)(page_hdl.get_slot_meta(rid.slot_no));
    base_meta.ts_ = ts;
    //   base_meta.is_deleted_ = is_delete;
    txn->CommitUndoLog(log_idx, ts);
  }

  //   page_hdl.page->WUnlatch();
  buffer_pool_manager_->unpin_page(page_hdl.page->get_page_id(), true);
}

// 热点行的更新操作只需保证串行安全即可 所以commit时就落地更新
void RmFileHandle::set_hot_record(const Rid &rid, ColMeta &col_meta, float delta) {
  RmPageHandle page_hdl = fetch_page_handle(rid.page_no);

  //   找行锁 加锁写数据
  {
    auto rec_latch_ptr = get_rec_latch(rid);
    std::unique_lock<std::shared_mutex> rec_lock(*rec_latch_ptr);
    char *old_val = page_hdl.get_slot_record(rid.slot_no) + col_meta.offset;
    // 必为浮点数
    float new_val = *(float *)old_val + delta;
    memcpy(old_val, &new_val, col_meta.len);
  }

  buffer_pool_manager_->unpin_page(page_hdl.page->get_page_id(), true);
}

// sqb 用于改动rmscan
TupleMeta RmFileHandle::get_meta(const Rid &rid) {
  //   std::shared_lock<std::shared_mutex> lock(latch_);
  RmPageHandle page_hdl = fetch_page_handle(rid.page_no);
  //   page_hdl.page->RLatch();
  TupleMeta ret;
  {
    auto rec_latch_ptr = get_rec_latch(rid);
    std::shared_lock<std::shared_mutex> rec_lock(*rec_latch_ptr);
    ret = *(TupleMeta *)(page_hdl.get_slot_meta(rid.slot_no));
  }
  //   page_hdl.page->RUnlatch();
  buffer_pool_manager_->unpin_page(page_hdl.page->get_page_id(), false);
  return ret;
}

// sqb 6.20 获取对应版本的元组，也就是经过重建后的
auto RmFileHandle::get_reconstructed_tuple(const Rid &rid, Context *context, TabMeta &tab)
    -> std::unique_ptr<RmRecord> {
  auto [current_tuple_meta, current_tuple, undo_link] = get_tuple_and_undoLink(rid, context);
  std::vector<UndoLog> undo_logs = CollectUndoLogs(current_tuple_meta, undo_link, context->txn_, context->txn_mgr_);
  std::optional<RmRecord> tuple = ReconstructTuple(&tab, current_tuple, current_tuple_meta, undo_logs);
  if (tuple.has_value()) {
    return std::make_unique<RmRecord>(*tuple);
  }
  return nullptr;
}

/**
 * @description: 在当前表中插入一条记录，不指定插入位置
 * @param {char*} buf 要插入的记录的数据
 * @param {Context*} context
 * @return {Rid} 插入的记录的记录号（位置）
 */
Rid RmFileHandle::insert_record(char *buf, Context *context, RmRecord *old_rec, const TabMeta *schema,
                                TupleMeta *old_meta) {
  // Todo:
  // 1. 获取当前未满的page handle
  // 2. 在page handle中找到空闲slot位置
  // 3. 将buf复制到空闲slot位置
  // 4. 更新page_handle.page_hdr中的数据结构
  // 注意考虑插入一条记录后页面已满的情况，需要更新file_hdr_.first_free_page_no

  //   std::unique_lock<std::shared_mutex> lock(latch_);
  //   插入并不会产生写写冲突 所以先维护头部 即使有bitmap检查 相应的读操作也依赖行锁
  RmPageHandle page_hdl = create_page_handle();
  page_hdl.page->WLatch();

  // 找空闲位置
  int free_slot_no = find_free_slot_no(page_hdl, context);

  //   如果因为逻辑删除指向了一个无真实空闲槽的数据页，直接创建新页
  if (free_slot_no == file_hdr_.num_records_per_page) {
    page_hdl.page->WUnlatch();
    buffer_pool_manager_->unpin_page(page_hdl.page->get_page_id(), false);
    {
      std::scoped_lock<std::mutex> fhdr_lock(fhdr_latch_);
      page_hdl = create_new_page_handle();
    }
    page_hdl.page->WLatch();
    free_slot_no = find_free_slot_no(page_hdl, context);
  }

  //   维护头部结构
  assert(free_slot_no != file_hdr_.num_records_per_page);
  Bitmap::set(page_hdl.bitmap, free_slot_no);
  page_hdl.page_hdr->num_records++;
  {
    std::scoped_lock<std::mutex> fhdr_lock(fhdr_latch_);
    if (page_hdl.page_hdr->num_records == file_hdr_.num_records_per_page) {
      file_hdr_.first_free_page_no = page_hdl.page_hdr->next_free_page_no;
    }
    // 跟踪表记录数量
    ++file_hdr_.record_num;
  }
  page_hdl.page->WUnlatch();

  //   插入的undo_log特殊 无需在锁内构建
  Rid ret{page_hdl.page->get_page_id().page_no, free_slot_no};
  RmRecord new_rec = RmRecord(file_hdr_.record_size, buf);
  auto [undo_log, undo_link] = generateUndoLogAndLink(fd_, ret, nullptr, &new_rec, context, schema);

  {
    auto rec_latch_ptr = get_rec_latch(ret);
    std::unique_lock<std::shared_mutex> rec_lock(*rec_latch_ptr);
    TupleMeta &base_meta = *(TupleMeta *)(page_hdl.get_slot_meta(ret.slot_no));
    if (context != nullptr && (context->txn_->get_state() == TransactionState::DEFAULT ||
                               context->txn_->get_state() == TransactionState::GROWING)) {
      // 锁控制并发 6.9
      // context->lock_mgr_->lock_exclusive_on_record(context->txn_, ret, fd_);

      // RmRecord new_rec = RmRecord(file_hdr_.record_size, buf);

      // 用于事务记录
      old_meta->ts_ = base_meta.ts_;
      old_meta->is_deleted_ = true;
      old_rec->SetData(page_hdl.get_slot_record(free_slot_no));

      //   auto [undo_log, undo_link] = generateUndoLogAndLink(fd_, ret, nullptr, &new_rec, context, schema);
      // 元数据时间戳更新
      base_meta.ts_ = context->txn_->get_temp_ts();

      // 当前log是updated log 在事务缓冲区修改 此时无需改动版本链
      if (undo_link.prev_txn_ == context->txn_->get_transaction_id()) {
        context->txn_->ModifyUndoLog(undo_link.prev_log_idx_, undo_log);
      } else {
        // 当前log为新log 追加到事务缓冲区内 同时更新版本链
        undo_link = context->txn_->AppendUndoLog(undo_log);
        context->txn_mgr_->UpdateUndoLink(fd_, ret, undo_link);
      }
    }
    memcpy(page_hdl.get_slot_record(free_slot_no), buf, file_hdr_.record_size);
    base_meta.is_deleted_ = false;
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
  //   std::unique_lock<std::shared_mutex> lock(latch_);
  RmPageHandle page_hdl = fetch_page_handle(rid.page_no);
  //   page_hdl.page->WLatch();
  {
    auto rec_latch_ptr = get_rec_latch(rid);
    std::unique_lock<std::shared_mutex> rec_lock(*rec_latch_ptr);
    memcpy(page_hdl.get_slot_record(rid.slot_no), buf, file_hdr_.record_size);

    TupleMeta &base_meta = *(TupleMeta *)(page_hdl.get_slot_meta(rid.slot_no));
    base_meta.is_deleted_ = false;
  }

  //   新的插入就得更新
  // MVCC下bitmap必定有效
  page_hdl.page->WLatch();
  page_hdl.page_hdr->num_records++;
  {
    std::scoped_lock<std::mutex> fhdr_lock(fhdr_latch_);
    if (page_hdl.page_hdr->num_records == file_hdr_.num_records_per_page) {
      file_hdr_.first_free_page_no = page_hdl.page_hdr->next_free_page_no;
    }
    // 跟踪表记录数量
    ++file_hdr_.record_num;
  }
  page_hdl.page->WUnlatch();
  //   当前数据为脏
  buffer_pool_manager_->unpin_page(page_hdl.page->get_page_id(), true);
}

/**
 * @description: 删除记录文件中记录号为rid的记录
 * @param {Rid&} rid 要删除的记录的记录号（位置）
 * @param {Context*} context
 */
void RmFileHandle::delete_record(const Rid &rid, Context *context, RmRecord *old_rec, const TabMeta *schema,
                                 TupleMeta *old_meta) {
  // Todo:
  // 1. 获取指定记录所在的page handle
  // 2. 更新page_handle.page_hdr中的数据结构
  // 注意考虑删除一条记录后页面未满的情况，需要调用release_page_handle()

  //   还是只考虑rid存在的情况
  //   std::unique_lock<std::shared_mutex> lock(latch_);
  RmPageHandle page_hdl = fetch_page_handle(rid.page_no);

  {
    // 用行锁维护记录与版本链
    auto rec_latch_ptr = get_rec_latch(rid);
    std::unique_lock<std::shared_mutex> rec_lock(*rec_latch_ptr);
    TupleMeta &base_meta = *(TupleMeta *)(page_hdl.get_slot_meta(rid.slot_no));
    if (context != nullptr && (context->txn_->get_state() == TransactionState::DEFAULT ||
                               context->txn_->get_state() == TransactionState::GROWING)) {
      // 写写冲突检查 6.19
      if (IsWriteWriteConflict(base_meta.ts_, context->txn_)) {
        throw TransactionAbortException(context->txn_->get_transaction_id(), AbortReason::DELETE_CONFLICT, tab_name_);
      }

      // 事务写入记录
      old_meta->ts_ = base_meta.ts_;
      old_meta->is_deleted_ = false;
      old_rec->SetData(page_hdl.get_slot_record(rid.slot_no));

      auto [undo_log, undo_link] = generateUndoLogAndLink(fd_, rid, old_rec, nullptr, context, schema);
      // 元数据时间戳更新
      base_meta.ts_ = context->txn_->get_temp_ts();

      // 当前log是updated log 在事务缓冲区修改 此时无需改动版本链
      if (undo_link.prev_txn_ == context->txn_->get_transaction_id()) {
        context->txn_->ModifyUndoLog(undo_link.prev_log_idx_, undo_log);
      } else {
        // 当前log为新log 追加到事务缓冲区内 同时更新版本链
        undo_link = context->txn_->AppendUndoLog(undo_log);
        context->txn_mgr_->UpdateUndoLink(fd_, rid, undo_link);
      }
    }

    //   Bitmap ::reset(page_hdl.bitmap, rid.slot_no);
    // bitmap不会在将1设为0 相对的，必须设置对应的is_delete
    base_meta.is_deleted_ = true;
  }

  //   让页锁维护头部结构 行锁处理实际操作
  {
    page_hdl.page->WLatch();
    assert(Bitmap::is_set(page_hdl.bitmap, rid.slot_no));
    --page_hdl.page_hdr->num_records;

    {
      std::scoped_lock<std::mutex> fhdr_lock(fhdr_latch_);
      // if (page_hdl.page_hdr->num_records == file_hdr_.num_records_per_page - 1) {
      //   page_hdl.page_hdr->next_free_page_no = file_hdr_.first_free_page_no;
      //   file_hdr_.first_free_page_no = page_hdl.page->get_page_id().page_no;
      // }
      // 跟踪表记录数量
      --file_hdr_.record_num;
    }

    page_hdl.page->WUnlatch();
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
void RmFileHandle::update_record(const Rid &rid, char *buf, Context *context, RmRecord *old_rec, const TabMeta *schema,
                                 TupleMeta *old_meta) {
  // Todo:
  // 1. 获取指定记录所在的page handle
  // 2. 更新记录

  //   暂时只考虑数据存在的情况
  //   std::unique_lock<std::shared_mutex> lock(latch_);

  RmPageHandle page_hdl = fetch_page_handle(rid.page_no);

  {
    // 用行锁维护记录与版本链
    auto rec_latch_ptr = get_rec_latch(rid);
    std::unique_lock<std::shared_mutex> rec_lock(*rec_latch_ptr);
    TupleMeta &base_meta = *(TupleMeta *)(page_hdl.get_slot_meta(rid.slot_no));
    if (context != nullptr && (context->txn_->get_state() == TransactionState::DEFAULT ||
                               context->txn_->get_state() == TransactionState::GROWING)) {
      // 锁控制并发 6.9
      // context->lock_mgr_->lock_exclusive_on_record(context->txn_, rid, fd_);

      // 写写冲突检查 6.19
      if (IsWriteWriteConflict(base_meta.ts_, context->txn_)) {
        throw TransactionAbortException(context->txn_->get_transaction_id(), AbortReason::UPDATE_CONFLICT, tab_name_);
      }

      // 事务写入记录
      old_meta->ts_ = base_meta.ts_;
      old_meta->is_deleted_ = base_meta.is_deleted_;
      old_rec->SetData(page_hdl.get_slot_record(rid.slot_no));

      {
        //   补充版本链 sqb 6.19
        RmRecord new_rec(file_hdr_.record_size, buf);
        //   std::scoped_lock<std::mutex> undo_lock(undo_latch_);
        auto [undo_log, undo_link] = generateUndoLogAndLink(fd_, rid, old_rec, &new_rec, context, schema);
        // 元数据更新
        base_meta.ts_ = context->txn_->get_temp_ts();

        // 当前log是updated log 在事务缓冲区修改 此时无需改动版本链
        if (undo_link.prev_txn_ == context->txn_->get_transaction_id()) {
          context->txn_->ModifyUndoLog(undo_link.prev_log_idx_, undo_log);
        } else {
          // 当前log为新log 追加到事务缓冲区内 同时更新版本链
          undo_link = context->txn_->AppendUndoLog(undo_log);
          context->txn_mgr_->UpdateUndoLink(fd_, rid, undo_link);
        }
      }
    }
    memcpy(page_hdl.get_slot_record(rid.slot_no), buf, file_hdr_.record_size);
    // Bitmap::set(page_hdl.bitmap, rid.slot_no);  // 出于保险加上先
    base_meta.is_deleted_ = false;
  }

  //   页锁维护头部
  {
    page_hdl.page->WLatch();
    assert(Bitmap::is_set(page_hdl.bitmap, rid.slot_no));
    // 跟踪表记录数量 由于索引永驻 逻辑删除后重用相当于插入
    if (old_meta->is_deleted_) {
      ++page_hdl.page_hdr->num_records;
      std::scoped_lock<std::mutex> fhdr_lock(fhdr_latch_);
      if (page_hdl.page_hdr->num_records == file_hdr_.num_records_per_page) {
        file_hdr_.first_free_page_no = page_hdl.page_hdr->next_free_page_no;
      }
      ++file_hdr_.record_num;
    }
    page_hdl.page->WUnlatch();
  }
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
 * sqb 必须在加锁后调用 7.8
 */
RmPageHandle RmFileHandle::create_new_page_handle() {
  // Todo:
  // 1.使用缓冲池来创建一个新page
  // 2.更新page handle中的相关信息
  // 3.更新file_hdr_

  // 在磁盘上获得一个新的page
  PageId new_page_id{fd_, INVALID_PAGE_ID};
  Page *new_page = buffer_pool_manager_->new_page(&new_page_id);
  if (new_page == nullptr) {
    throw PageNotExistError(disk_manager_->get_file_name(fd_), new_page_id.page_no);
  }

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

  std::scoped_lock<std::mutex> fhdr_lock(fhdr_latch_);
  if (file_hdr_.first_free_page_no == INVALID_PAGE_ID) {
    // 没有空闲页
    return create_new_page_handle();
  }

  //   有空闲页
  return fetch_page_handle(file_hdr_.first_free_page_no);
}

// /**
//  * @description:
//  * 当一个页面从没有空闲空间的状态变为有空闲空间状态时，更新文件头和页头中空闲页面相关的元数据
//  */
// void RmFileHandle::release_page_handle(RmPageHandle &page_handle) {
//   // Todo:
//   // 当page从已满变成未满，考虑如何更新：
//   // 1. page_handle.page_hdr->next_free_page_no
//   // 2. file_hdr_.first_free_page_no
//   std::scoped_lock<std::mutex> fhdr_lock(fhdr_latch_);

//   page_handle.page_hdr->next_free_page_no = file_hdr_.first_free_page_no;
//   file_hdr_.first_free_page_no = page_handle.page->get_page_id().page_no;
// }

// sqb 避免故障恢复时 访问不存在的页报错 暂时只考虑申请一次 6.11
void RmFileHandle::allocate_pages(const Rid &rid) {
  //   std::unique_lock<std::shared_mutex> lock(latch_);
  std::scoped_lock<std::mutex> fhdr_lock(fhdr_latch_);
  if (rid.page_no >= file_hdr_.num_pages) {
    page_id_t old_fisrt_free_page = file_hdr_.first_free_page_no;
    // RmPageHandle page_hdl = create_page_handle();
    RmPageHandle page_hdl = create_new_page_handle();            // sqb 7.8不确定
    page_hdl.page_hdr->next_free_page_no = old_fisrt_free_page;  // 可能有问题，也可能压根没用
    buffer_pool_manager_->unpin_page(page_hdl.page->get_page_id(), true);
  }
}

int RmFileHandle::find_free_slot_no(RmPageHandle &page_hdl, Context *context) {
  int free_slot_no = file_hdr_.num_records_per_page;
  for (int i = 0; i < file_hdr_.num_records_per_page; ++i) {
    // bm=0 代表没有 bm=1 is_delete=true 代表逻辑删除 写写冲突检查将允许事务自己插入到为1的地方 其它事务将仍无法处理
    if (Bitmap::is_set(page_hdl.bitmap, i) == 0) {
      free_slot_no = i;
      break;
    }
    // else {
    //   TupleMeta &base_meta = *(TupleMeta *)(page_hdl.get_slot_meta(i));
    //   //   插入到逻辑删除的位置需要进行写写冲突检查 该函数不应出现写写冲突
    //   if (base_meta.is_deleted_ == true &&
    //       !(context != nullptr && IsWriteWriteConflict(base_meta.ts_, context->txn_))) {
    //     free_slot_no = i;
    //     break;
    //   }
    // }
  }
  return free_slot_no;
}

//   找到行锁 不存在则创建 如果后续爆内存 那么就用分块
std::shared_ptr<std::shared_mutex> RmFileHandle::get_rec_latch(const Rid &rid) {
  //   行锁查找
  std::shared_ptr<std::shared_mutex> ret = nullptr;
  {
    std::unique_lock<std::shared_mutex> map_lock(rid_map_latch_);
    auto iter = rid_latches_.find(rid);
    // 有则返回 无则创建
    if (iter != rid_latches_.end()) {
      ret = iter->second;
    } else {
      ret = std::make_shared<std::shared_mutex>();
      rid_latches_[rid] = ret;
    }
  }
  return ret;
}

//   为了重构回滚 支持MVCC的垃圾回收 加回滚时rec和meta原子回滚的函数
void RmFileHandle::rollback_update_helper(const Rid &rid, const RmRecord &old_rec, const TupleMeta &old_meta,
                                          Transaction *txn, TransactionManager *txn_mgr) {
  //   std::unique_lock<std::shared_mutex> lock(latch_);
  RmPageHandle page_hdl = fetch_page_handle(rid.page_no);
  //   page_hdl.page->WLatch();
  assert(Bitmap::is_set(page_hdl.bitmap, rid.slot_no));

  TupleMeta pre_meta;  // 记录回滚前最新meta
  {
    // 行锁
    auto rec_latch_ptr = get_rec_latch(rid);
    std::unique_lock<std::shared_mutex> rec_lock(*rec_latch_ptr);

    //   回滚事务的版本链必定有值，且必定为自己，并只有一个
    std::optional<UndoLink> op_link = txn_mgr->GetUndoLink(fd_, rid);
    assert(op_link.has_value() && (*op_link).prev_txn_ == txn->get_transaction_id());
    UndoLog log = txn->GetUndoLog((*op_link).prev_log_idx_);
    //   UndoLog log = txn_mgr->GetUndoLog(*op_link);
    UndoLink pre_link = log.prev_version_;  // 跳过当前版本
    txn_mgr->UpdateUndoLink(fd_, rid, pre_link);

    TupleMeta &base_meta = *(TupleMeta *)(page_hdl.get_slot_meta(rid.slot_no));
    pre_meta = base_meta;

    //   回滚原始值
    base_meta = old_meta;
    memcpy(page_hdl.get_slot_record(rid.slot_no), old_rec.data, file_hdr_.record_size);
  }

  //   因为这步压缩了事务对一个元组回滚的多步 根据旧值与目前最新值推测事务操作 跟踪表记录数量
  page_hdl.page->WLatch();
  if (pre_meta.is_deleted_ != old_meta.is_deleted_) {
    if (old_meta.is_deleted_) {
      // 相当于插入做回滚
      --page_hdl.page_hdr->num_records;
      std::scoped_lock<std::mutex> fhdr_lock(fhdr_latch_);
      //   if (page_hdl.page_hdr->num_records == file_hdr_.num_records_per_page - 1) {
      //     page_hdl.page_hdr->next_free_page_no = file_hdr_.first_free_page_no;
      //     file_hdr_.first_free_page_no = page_hdl.page->get_page_id().page_no;
      //   }
      --file_hdr_.record_num;
    } else {
      // 相当于删除做回滚
      ++page_hdl.page_hdr->num_records;
      {
        std::scoped_lock<std::mutex> fhdr_lock(fhdr_latch_);
        // if (page_hdl.page_hdr->num_records == file_hdr_.num_records_per_page) {
        //   file_hdr_.first_free_page_no = page_hdl.page_hdr->next_free_page_no;
        // }
        // 跟踪表记录数量
        ++file_hdr_.record_num;
      }
    }
  }
  page_hdl.page->WUnlatch();

  buffer_pool_manager_->unpin_page(page_hdl.page->get_page_id(), true);
}