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
#include <unordered_map>
#include "log_manager.h"
#include "storage/disk_manager.h"
#include "system/sm_manager.h"

class RedoLogsInPage {
 public:
  RedoLogsInPage() { table_file_ = nullptr; }
  RmFileHandle *table_file_;
  std::vector<lsn_t> redo_logs_;  // 在该page上需要redo的操作的lsn
};

class RecoveryManager {
 public:
  RecoveryManager(DiskManager *disk_manager, BufferPoolManager *buffer_pool_manager, SmManager *sm_manager) {
    disk_manager_ = disk_manager;
    buffer_pool_manager_ = buffer_pool_manager;
    sm_manager_ = sm_manager;
  }

  void analyze();
  void redo();
  void undo();

  //   sqb 获取日志文件中最大的lsn 6.11
  lsn_t get_max_lsn() { return last_lsn_; }

 private:
  //   sqb 6.8 为了利用缓冲区提高磁盘读效率 将lsn映射到对应缓冲区位置 前32为做块号 后32位做偏移
  uint64_t encode_lsn_pos(int32_t block_id, int32_t offset) {
    return (static_cast<uint64_t>(block_id) << 32 | static_cast<uint32_t>(offset));
  }
  void decode_lsn_pos(uint64_t lsn_pos, int32_t &block_id, int32_t &offset) {
    block_id = static_cast<int32_t>(static_cast<uint32_t>(lsn_pos >> 32));
    offset = static_cast<int32_t>(static_cast<uint32_t>(lsn_pos & 0xFFFFFFFF));
  }

  LogBuffer buffer_;                        // 读入日志
  DiskManager *disk_manager_;               // 用来读写文件
  BufferPoolManager *buffer_pool_manager_;  // 对页面进行读写
  SmManager *sm_manager_;                   // 访问数据库元数据

  //   sqb 添加结构6.5
  std::unordered_map<txn_id_t, lsn_t> active_txns_;  // 活动事务表与其最后的lsn
  lsn_t first_lsn_{INT32_MAX};                       // 相当于不建立DPT 直接找最小lsn
  lsn_t last_lsn_{INVALID_LSN};                      // 用于恢复后重新设置global lsn
  std::unordered_map<lsn_t, uint64_t> lsn_to_pos_;   // lsn与对应位置，以log buffer做块大小，高32位表示块号 低32位做偏移
  int log_file_size_;
};