/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include <assert.h>

#include <memory>
#include <mutex>
#include <optional>
#include <shared_mutex>
#include <tuple>

#include "bitmap.h"
#include "common/context.h"
#include "rm_defs.h"

class RmManager;
struct TabMeta;  // sqb

/* 对表数据文件中的页面进行封装 */
struct RmPageHandle {
  const RmFileHdr *file_hdr;  // 当前页面所在文件的文件头指针
  Page *page;                 // 页面的实际数据，包括页面存储的数据、元信息等
  RmPageHdr *page_hdr;        // page->data的第一部分，存储页面元信息，指针指向首地址，长度为sizeof(RmPageHdr)
  char *bitmap;               // page->data的第二部分，存储页面的bitmap，指针指向首地址，长度为file_hdr->bitmap_size
  char *slots;  // page->data的第三部分，存储表的记录，指针指向首地址，每个slot的长度为file_hdr->record_size

  RmPageHandle(const RmFileHdr *fhdr_, Page *page_) : file_hdr(fhdr_), page(page_) {
    page_hdr = reinterpret_cast<RmPageHdr *>(page->get_data() + page->OFFSET_PAGE_HDR);
    bitmap = page->get_data() + sizeof(RmPageHdr) + page->OFFSET_PAGE_HDR;
    slots = bitmap + file_hdr->bitmap_size;
  }

  //   // 返回指定slot_no的slot存储收地址
  //   char *get_slot(int slot_no) const {
  //     return slots + slot_no * file_hdr->record_size;  // slots的首地址 +
  //     slot个数 *
  //                                                      //
  //                                                      每个slot的大小(每个record的大小)
  //   }

  // sqb 重要改动 为所有record头部添加了tuple meta 6.17
  char *get_slot_record(int slot_no) const {
    return slots + slot_no * (file_hdr->record_size + sizeof(TupleMeta)) + sizeof(TupleMeta);
  }

  // sqb 重要改动 为所有record头部添加了tuple meta 6.17
  char *get_slot_meta(int slot_no) const { return slots + slot_no * (file_hdr->record_size + sizeof(TupleMeta)); }
};

/* 每个RmFileHandle对应一个表的数据文件，里面有多个page，每个page的数据封装在RmPageHandle中
 */
class RmFileHandle {
  friend class RmScan;
  friend class RmManager;

 private:
  DiskManager *disk_manager_;
  BufferPoolManager *buffer_pool_manager_;
  int fd_;  // 打开文件后产生的文件句柄

  //   mutable std::shared_mutex latch_;  // sqb 加锁保证线程安全 6.17

  std::mutex undo_latch_;  // 用于保护undo_log,undo_link的相关操作 sqb 7.7

  std::mutex fhdr_latch_;  // 用于保护file_hdr sqb  7.7

  std::string tab_name_;  // 事务记录时的表名

 public:
  RmFileHdr file_hdr_;  // 文件头，维护当前表文件的元数据
  RmFileHandle(DiskManager *disk_manager, BufferPoolManager *buffer_pool_manager, int fd)
      : disk_manager_(disk_manager), buffer_pool_manager_(buffer_pool_manager), fd_(fd) {
    // 注意：这里从磁盘中读出文件描述符为fd的文件的file_hdr，读到内存中
    // 这里实际就是初始化file_hdr，只不过是从磁盘中读出进行初始化
    // init file_hdr_
    disk_manager_->read_page(fd, RM_FILE_HDR_PAGE, (char *)&file_hdr_, sizeof(file_hdr_));
    // disk_manager管理的fd对应的文件中，设置从file_hdr_.num_pages开始分配page_no
    disk_manager_->set_fd2pageno(fd, file_hdr_.num_pages);

    tab_name_ = disk_manager_->get_file_name(fd_);
  }

  RmFileHdr get_file_hdr() { return file_hdr_; }
  int GetFd() { return fd_; }

  /* 判断指定位置上是否已经存在一条记录，通过Bitmap来判断 */
  bool is_record(const Rid &rid) const {
    RmPageHandle page_handle = fetch_page_handle(rid.page_no);
    return Bitmap::is_set(page_handle.bitmap,
                          rid.slot_no);  // page的slot_no位置上是否有record
  }

  std::unique_ptr<RmRecord> get_record(const Rid &rid, Context *context) const;

  // sqb 再次修改增删改接口 让undo link同时更新
  Rid insert_record(char *buf, Context *context, const TabMeta *schema = nullptr, TupleMeta *old_meta = nullptr);

  void insert_record(const Rid &rid, char *buf);

  // sqb 6.4更改 delete update 接口 便于封装事务与日志
  void delete_record(const Rid &rid, Context *context, RmRecord *old_rec = nullptr, const TabMeta *schema = nullptr,
                     TupleMeta *old_meta = nullptr);

  void update_record(const Rid &rid, char *buf, Context *context, RmRecord *old_rec = nullptr,
                     const TabMeta *schema = nullptr, TupleMeta *old_meta = nullptr);

  RmPageHandle create_new_page_handle();

  RmPageHandle fetch_page_handle(int page_no) const;

  // sqb 故障恢复指定插入用
  void allocate_pages(const Rid &rid);
  // sqb 6.16
  int get_page_num() { return file_hdr_.num_pages; }

  // sqb 6.17 关于tuple meta undolink的操作
  auto get_tuple_and_undoLink(const Rid &rid, Context *context)
      -> std::tuple<TupleMeta, RmRecord, std::optional<UndoLink>>;

  // sqb 6.20 获取对应版本的tuple
  auto get_reconstructed_tuple(const Rid &rid, Context *context, TabMeta &tab) -> std::unique_ptr<RmRecord>;

  // sqb 事务提交更新所有时间戳 事务回滚时用来
  void set_meta(const Rid &rid, timestamp_t ts, bool is_delete);

  // sqb 用于改动rmscan
  TupleMeta get_meta(const Rid &rid);

  // sqb 获取表中记录的数量
  size_t get_record_num() {
    // std::shared_lock<std::shared_mutex> lock(latch_);
    std::scoped_lock<std::mutex> fhdr_lock(fhdr_latch_);
    return file_hdr_.record_num;
  }

 private:
  RmPageHandle create_page_handle();

  //   void release_page_handle(RmPageHandle &page_handle);

  int find_free_slot_no(RmPageHandle &page_hdl, Context *context);
};