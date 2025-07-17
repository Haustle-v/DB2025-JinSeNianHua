/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "rm_scan.h"

#include "rm_file_handle.h"

/**
 * @brief 初始化file_handle和rid
 * @param file_handle
 */
RmScan::RmScan(const RmFileHandle *file_handle) : file_handle_(file_handle) {
  // Todo:
  // 初始化file_handle和rid（指向第一个存放了记录的位置）

  int max_page_num = file_handle_->file_hdr_.num_pages;
  int max_record_size = file_handle_->file_hdr_.num_records_per_page;
  PageId tmp_page_id{file_handle_->fd_, INVALID_PAGE_ID};

  for (page_id_t page_no = 1; page_no < max_page_num; ++page_no) {
    RmPageHandle page_hdl = file_handle_->fetch_page_handle(page_no);
    tmp_page_id.page_no = page_no;
    int slot_no = Bitmap::next_bit(1, page_hdl.bitmap, max_record_size, -1);
    if (slot_no != max_record_size) {
      rid_.page_no = page_no;
      rid_.slot_no = slot_no;
      file_handle_->buffer_pool_manager_->unpin_page(tmp_page_id, false);
      return;
    }
    file_handle_->buffer_pool_manager_->unpin_page(tmp_page_id, false);
  }
  //   如果全部遍历完了还没有 就设为无效
  rid_.page_no = INVALID_PAGE_ID;
  rid_.slot_no = -1;
}

/**
 * @brief 找到文件中下一个存放了记录的位置
 */
void RmScan::next() {
  // Todo:
  // 找到文件中下一个存放了记录的非空闲位置，用rid_来指向这个位置

  assert(rid_.page_no != INVALID_PAGE_ID && "rm scan next invalid!");

  int max_page_num = file_handle_->file_hdr_.num_pages;
  int max_record_size = file_handle_->file_hdr_.num_records_per_page;
  PageId tmp_page_id{file_handle_->fd_, INVALID_PAGE_ID};

  //   顺序扫描
  int start_slot_no = rid_.slot_no;
  for (page_id_t page_no = rid_.page_no; page_no < max_page_num; ++page_no) {
    RmPageHandle page_hdl = file_handle_->fetch_page_handle(page_no);
    tmp_page_id.page_no = page_no;
    int slot_no = Bitmap::next_bit(1, page_hdl.bitmap, max_record_size, start_slot_no);

    if (slot_no == max_record_size) {
      start_slot_no = -1;
    } else {
      // 找到了
      rid_.page_no = page_no;
      rid_.slot_no = slot_no;
      file_handle_->buffer_pool_manager_->unpin_page(tmp_page_id, false);
      return;
    }

    file_handle_->buffer_pool_manager_->unpin_page(tmp_page_id, false);
  }

  //   没找到 设为无效
  rid_.page_no = INVALID_PAGE_ID;
  rid_.slot_no = -1;
}

/**
 * @brief ​ 判断是否到达文件末尾
 */
bool RmScan::is_end() const {
  // Todo: 修改返回值

  return rid_.page_no == INVALID_PAGE_ID;
}

/**
 * @brief RmScan内部存放的rid
 */
Rid RmScan::rid() const { return rid_; }