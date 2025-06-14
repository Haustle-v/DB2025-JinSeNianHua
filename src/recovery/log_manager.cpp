/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "log_manager.h"
#include <cstring>

/**
 * @description: 添加日志记录到日志缓冲区中，并返回日志记录号
 * @param {LogRecord*} log_record 要写入缓冲区的日志记录
 * @return {lsn_t} 返回该日志的日志记录号
 */
lsn_t LogManager::add_log_to_buffer(LogRecord *log_record) {
  // sqb 6.5
  std::scoped_lock<std::mutex> lock(latch_);
  if (log_buffer_.is_full(log_record->log_tot_len_)) {
    flush_log2disk_helper();
  }
  // 未满则追加
  log_record->lsn_ = global_lsn_++;
  log_record->serialize(log_buffer_.buffer_ + log_buffer_.offset_);
  log_buffer_.offset_ += log_record->log_tot_len_;

  //   补充检查点位置
  if (auto ckpt = dynamic_cast<CkptLogRecord *>(log_record)) {
    int ckpt_offset = disk_manager_->get_file_size(LOG_FILE_NAME) + log_buffer_.offset_;
    checkpoint_pos_ = encode_lsn_pos(ckpt_offset / LOG_BUFFER_SIZE, ckpt_offset % LOG_BUFFER_SIZE);
  }

  return log_record->lsn_;
}

/**
 * @description: 把日志缓冲区的内容刷到磁盘中，由于目前只设置了一个缓冲区，因此需要阻塞其他日志操作
 */
void LogManager::flush_log_to_disk() {
  // sqb 6.5
  std::scoped_lock<std::mutex> lock(latch_);
  flush_log2disk_helper();
}

// sqb 6.5 主要是便于上面两个函数共用 省的处理锁
void LogManager::flush_log2disk_helper() {
  disk_manager_->write_log(log_buffer_.buffer_, log_buffer_.offset_);
  persist_lsn_ = global_lsn_ - 1;
  log_buffer_.offset_ = 0;

  //   补充检查点位置 6.11
  if (checkpoint_pos_ != 0) {
    std::ofstream ofs(LOG_CHECKPOINT_POS_FILE);
    ofs << checkpoint_pos_;
  }
}
