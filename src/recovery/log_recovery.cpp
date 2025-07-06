/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "log_recovery.h"
#include <queue>

/**
 * @description: analyze阶段，需要获得脏页表（DPT）和未完成的事务列表（ATT）
 */
void RecoveryManager::analyze() {
  // sqb 6.8
  log_file_size_ = disk_manager_->get_file_size(LOG_FILE_NAME);
  int block_num = (log_file_size_ + LOG_BUFFER_SIZE - 1) / LOG_BUFFER_SIZE;  // 向上取整
  char log_header[LOG_HEADER_SIZE];                                          // 为块边界备用
  char log_body[4 * RM_MAX_RECORD_SIZE];                                     // 为块边界备用

  // 利用检查点位置定位 sqb 6.11
  std::ifstream ifs(LOG_CHECKPOINT_POS_FILE);
  uint64_t checkpoint_pos{0};
  int cur_block_id, cur_offset;
  if (!ifs) {
    cur_block_id = cur_offset = 0;
  } else {
    ifs >> checkpoint_pos;
    decode_lsn_pos(checkpoint_pos, cur_block_id, cur_offset);
  }

  LogRecord *log_record = new LogRecord();
  for (; cur_block_id < block_num; ++cur_block_id, cur_offset -= LOG_BUFFER_SIZE) {
    // 将日志读入缓冲区
    if (cur_block_id == block_num - 1) {
      disk_manager_->read_log(buffer_.buffer_, log_file_size_ % LOG_BUFFER_SIZE, cur_block_id * LOG_BUFFER_SIZE);
    } else {
      disk_manager_->read_log(buffer_.buffer_, LOG_BUFFER_SIZE, cur_block_id * LOG_BUFFER_SIZE);
    }
    // 给redo和undo时用，减少io
    buffer_.block_id_ = cur_block_id;
    int boundary = cur_block_id == block_num - 1 ? log_file_size_ % LOG_BUFFER_SIZE : LOG_BUFFER_SIZE;

    // 验证日志 记录att，记录最小rec lsn，记录lsn对应偏移
    while (cur_offset < boundary) {
      //   读取并验证日志头
      if (cur_offset + LOG_HEADER_SIZE > boundary) {
        // 注意处于块末尾的特殊处理 直接从磁盘读 不完整的日志直接停止
        if (disk_manager_->read_log(log_header, LOG_HEADER_SIZE, cur_block_id * LOG_BUFFER_SIZE + cur_offset) !=
            LOG_HEADER_SIZE) {
          break;
        }
        log_record->deserialize(log_header);
      } else {
        log_record->deserialize(buffer_.buffer_ + cur_offset);
      }

      //   验证日志体的完整
      if (cur_offset + log_record->log_tot_len_ > boundary) {
        if (disk_manager_->read_log(log_body, log_record->log_tot_len_, cur_block_id * LOG_BUFFER_SIZE + cur_offset) !=
            log_record->log_tot_len_) {
          break;
        }
      }

      //   更新相关数据结构
      lsn_to_pos_.emplace(log_record->lsn_, encode_lsn_pos(cur_block_id, cur_offset));
      cur_offset += log_record->log_tot_len_;
      last_lsn_ = log_record->lsn_;
      switch (log_record->log_type_) {
        case LogType::begin:
          active_txns_.emplace(log_record->log_tid_, log_record->lsn_);
          break;
        case LogType::commit:
        case LogType::ABORT:
          active_txns_.erase(log_record->log_tid_);
          break;
        case LogType::INSERT:
        case LogType::DELETE:
        case LogType::UPDATE:
          first_lsn_ = std::min(first_lsn_, log_record->lsn_);
          active_txns_[log_record->log_tid_] = log_record->lsn_;
          break;
        case LogType::CHECKPOINT:
          //  sqb 出于保险加 目前单事务下检查点恢复 应该不会走到这 6.11
          // 暂时正确 6.24
          first_lsn_ = log_record->lsn_;
          break;
        default:
          throw InternalError("unsupport log type!");
          break;
      }
    }
  }
  delete log_record;
}

/**
 * @description: 重做所有未落盘的操作
 */
void RecoveryManager::redo() {
  // 如果此前有检查点让first_lsn_无效，那么无需redo
  if (first_lsn_ == INT32_MAX) return;

  // sqb 6.8
  int first_block_id, first_offset;
  decode_lsn_pos(lsn_to_pos_[first_lsn_], first_block_id, first_offset);
  int block_num = (log_file_size_ + LOG_BUFFER_SIZE - 1) / LOG_BUFFER_SIZE;
  char log_header[LOG_HEADER_SIZE];       // 为块边界备用
  char log_body[4 * RM_MAX_RECORD_SIZE];  // 为块边界备用

  //   顺序扫描进行redo
  for (int cur_block_id = first_block_id, cur_offset = first_offset; cur_block_id < block_num;
       ++cur_block_id, cur_offset -= LOG_BUFFER_SIZE) {
    // 将日志读入缓冲区
    if (cur_block_id != buffer_.block_id_) {
      if (cur_block_id == block_num - 1) {
        disk_manager_->read_log(buffer_.buffer_, log_file_size_ % LOG_BUFFER_SIZE, cur_block_id * LOG_BUFFER_SIZE);
      } else {
        disk_manager_->read_log(buffer_.buffer_, LOG_BUFFER_SIZE, cur_block_id * LOG_BUFFER_SIZE);
      }
    }
    buffer_.block_id_ = cur_block_id;

    int boundary = cur_block_id == block_num - 1 ? log_file_size_ % LOG_BUFFER_SIZE : LOG_BUFFER_SIZE;

    // 读取日志记录 redo写操作 这次无需验证
    while (cur_offset < boundary) {
      LogRecord log_record;
      //   读取日志头
      if (cur_offset + LOG_HEADER_SIZE > boundary) {
        // 注意处于块末尾的特殊处理
        disk_manager_->read_log(log_header, LOG_HEADER_SIZE, cur_block_id * LOG_BUFFER_SIZE + cur_offset);
        log_record.deserialize(log_header);
      } else {
        log_record.deserialize(buffer_.buffer_ + cur_offset);
      }

      // redo 只处理增删改
      switch (log_record.log_type_) {
        case LogType::INSERT: {
          InsertLogRecord insert_record;
          //   读取完整日志
          if (cur_offset + log_record.log_tot_len_ > boundary) {
            disk_manager_->read_log(log_body, log_record.log_tot_len_, cur_block_id * LOG_BUFFER_SIZE + cur_offset);
            insert_record.deserialize(log_body);
          } else {
            insert_record.deserialize(buffer_.buffer_ + cur_offset);
          }

          std::string tab_name(insert_record.table_name_, insert_record.table_name_size_);
          redo_insert(tab_name, insert_record.rid_, insert_record.insert_value_, insert_record.lsn_);
        } break;
        case LogType::DELETE: {
          DeleteLogRecord delete_record;
          //   读取完整日志
          if (cur_offset + log_record.log_tot_len_ > boundary) {
            disk_manager_->read_log(log_body, log_record.log_tot_len_, cur_block_id * LOG_BUFFER_SIZE + cur_offset);
            delete_record.deserialize(log_body);
          } else {
            delete_record.deserialize(buffer_.buffer_ + cur_offset);
          }

          std::string tab_name(delete_record.table_name_, delete_record.table_name_size_);
          redo_delete(tab_name, delete_record.rid_, delete_record.lsn_);
        } break;
        case LogType::UPDATE: {
          UpdateLogRecord update_record;
          //   读取完整日志
          if (cur_offset + log_record.log_tot_len_ > boundary) {
            disk_manager_->read_log(log_body, log_record.log_tot_len_, cur_block_id * LOG_BUFFER_SIZE + cur_offset);
            update_record.deserialize(log_body);
          } else {
            update_record.deserialize(buffer_.buffer_ + cur_offset);
          }

          std::string tab_name(update_record.table_name_, update_record.table_name_size_);
          redo_update(tab_name, update_record.rid_, update_record.new_value_, update_record.lsn_);
        } break;
        default:
          break;
      }
      cur_offset += log_record.log_tot_len_;
    }
  }
}

/**
 * @description: 回滚未完成的事务
 */
void RecoveryManager::undo() {
  // sqb 6.8
  int block_num = (log_file_size_ + LOG_BUFFER_SIZE - 1) / LOG_BUFFER_SIZE;
  char log_header[LOG_HEADER_SIZE];       // 为块边界备用
  char log_body[4 * RM_MAX_RECORD_SIZE];  // 为块边界备用
  std::priority_queue<lsn_t> att_lsns_;   // 大顶堆记录最后lsn
  for (auto &entry : active_txns_) {
    att_lsns_.emplace(entry.second);
  }

  //   if (!att_lsns_.empty()) {
  //     assert(0);
  //   }

  //  逐个 undo活动事务
  int boundary = -1;
  while (!att_lsns_.empty()) {
    lsn_t last_lsn = att_lsns_.top();
    att_lsns_.pop();

    // while (last_lsn != INVALID_LSN) {
    int cur_block_id, cur_offset;
    decode_lsn_pos(lsn_to_pos_[last_lsn], cur_block_id, cur_offset);
    //   日志读入缓冲区
    if (cur_block_id != buffer_.block_id_) {
      if (cur_block_id == block_num - 1) {
        disk_manager_->read_log(buffer_.buffer_, log_file_size_ % LOG_BUFFER_SIZE, cur_block_id * LOG_BUFFER_SIZE);
        boundary = log_file_size_ % LOG_BUFFER_SIZE;
      } else {
        disk_manager_->read_log(buffer_.buffer_, LOG_BUFFER_SIZE, cur_block_id * LOG_BUFFER_SIZE);
        boundary = LOG_BUFFER_SIZE;
      }
    }
    buffer_.block_id_ = cur_block_id;

    //   日志头
    LogRecord log_record;
    if (cur_offset + LOG_HEADER_SIZE > boundary) {
      disk_manager_->read_log(log_header, LOG_HEADER_SIZE, cur_block_id * LOG_BUFFER_SIZE + cur_offset);
      log_record.deserialize(log_header);
    } else {
      log_record.deserialize(buffer_.buffer_ + cur_offset);
    }
    //   根据类型undo
    switch (log_record.log_type_) {
      case LogType::INSERT: {
        InsertLogRecord insert_record;
        //   读取完整日志
        if (cur_offset + log_record.log_tot_len_ > boundary) {
          disk_manager_->read_log(log_body, log_record.log_tot_len_, cur_block_id * LOG_BUFFER_SIZE + cur_offset);
          insert_record.deserialize(log_body);
        } else {
          insert_record.deserialize(buffer_.buffer_ + cur_offset);
        }
        std::string tab_name(insert_record.table_name_, insert_record.table_name_size_);
        redo_delete(tab_name, insert_record.rid_, insert_record.lsn_);
      } break;
      case LogType::DELETE: {
        DeleteLogRecord delete_record;
        //   读取完整日志
        if (cur_offset + log_record.log_tot_len_ > boundary) {
          disk_manager_->read_log(log_body, log_record.log_tot_len_, cur_block_id * LOG_BUFFER_SIZE + cur_offset);
          delete_record.deserialize(log_body);
        } else {
          delete_record.deserialize(buffer_.buffer_ + cur_offset);
        }
        std::string tab_name(delete_record.table_name_, delete_record.table_name_size_);
        redo_insert(tab_name, delete_record.rid_, delete_record.delete_value_, delete_record.lsn_);
      } break;
      case LogType::UPDATE: {
        UpdateLogRecord update_record;
        //   读取完整日志
        if (cur_offset + log_record.log_tot_len_ > boundary) {
          disk_manager_->read_log(log_body, log_record.log_tot_len_, cur_block_id * LOG_BUFFER_SIZE + cur_offset);
          update_record.deserialize(log_body);
        } else {
          update_record.deserialize(buffer_.buffer_ + cur_offset);
        }
        std::string tab_name(update_record.table_name_, update_record.table_name_size_);
        redo_update(tab_name, update_record.rid_, update_record.old_value_, update_record.lsn_);
      } break;
      default:
        break;
    }
    //   last_lsn = log_record.prev_lsn_;
    if (log_record.prev_lsn_ != INVALID_LSN) {
      att_lsns_.emplace((log_record.prev_lsn_));
    }
    // }
  }

  // 重建索引
  std::vector<IndexMeta> all_indexes = sm_manager_->db_.get_all_indexes();
  for (auto &index : all_indexes) {
    if (sm_manager_->fhs_.find(index.tab_name) == sm_manager_->fhs_.end()) {
      continue;
    }
    std::vector<std::string> col_names;
    for (auto &col_meta : index.cols) {
      col_names.emplace_back(col_meta.name);
    }
    try {
      sm_manager_->drop_index(index.tab_name, col_names, nullptr);
      sm_manager_->create_index(index.tab_name, col_names, nullptr);
    } catch (RMDBError &e) {
    }
  }
}

// sqb redo 增删改重构 6.24
void RecoveryManager::redo_insert(const std::string &tab_name, const Rid &rid, const RmRecord &rec, const lsn_t lsn) {
  //   检查表是否存在 不存在则都不redo
  auto iter = sm_manager_->fhs_.find(tab_name);
  if (iter == sm_manager_->fhs_.end()) {
    return;
  }
  RmFileHandle *fhdl_ptr = iter->second.get();
  TabMeta &tab_meta = sm_manager_->db_.get_table(tab_name);
  PageId page_id{fhdl_ptr->GetFd(), rid.page_no};

  //   检查页是否存在，不存在先提前分配
  fhdl_ptr->allocate_pages(rid);
  Page *page_ptr = buffer_pool_manager_->fetch_page(page_id);

  //   根据lsn决定是否redo
  if (lsn > page_ptr->get_page_lsn()) {
    fhdl_ptr->insert_record(rid, rec.data);
    page_ptr->set_page_lsn(lsn);
    buffer_pool_manager_->unpin_page(page_id, true);
  } else {
    buffer_pool_manager_->unpin_page(page_id, false);
  }
}

void RecoveryManager::redo_delete(const std::string &tab_name, const Rid &rid, const lsn_t lsn) {
  //   检查表是否存在 不存在则都不redo
  auto iter = sm_manager_->fhs_.find(tab_name);
  if (iter == sm_manager_->fhs_.end()) {
    return;
  }
  RmFileHandle *fhdl_ptr = iter->second.get();
  TabMeta &tab_meta = sm_manager_->db_.get_table(tab_name);
  PageId page_id{fhdl_ptr->GetFd(), rid.page_no};

  //   检查页是否存在，不存在先提前分配
  fhdl_ptr->allocate_pages(rid);
  Page *page_ptr = buffer_pool_manager_->fetch_page(page_id);

  //   根据lsn决定是否redo
  if (lsn > page_ptr->get_page_lsn()) {
    fhdl_ptr->delete_record(rid, nullptr);
    page_ptr->set_page_lsn(lsn);
    buffer_pool_manager_->unpin_page(page_id, true);
  } else {
    buffer_pool_manager_->unpin_page(page_id, false);
  }
}

void RecoveryManager::redo_update(const std::string &tab_name, const Rid &rid, const RmRecord &new_rec,
                                  const lsn_t lsn) {
  //   检查表是否存在 不存在则都不redo
  auto iter = sm_manager_->fhs_.find(tab_name);
  if (iter == sm_manager_->fhs_.end()) {
    return;
  }
  RmFileHandle *fhdl_ptr = iter->second.get();
  TabMeta &tab_meta = sm_manager_->db_.get_table(tab_name);
  PageId page_id{fhdl_ptr->GetFd(), rid.page_no};

  //   检查页是否存在，不存在先提前分配
  fhdl_ptr->allocate_pages(rid);
  Page *page_ptr = buffer_pool_manager_->fetch_page(page_id);

  //   根据lsn决定是否redo
  if (lsn > page_ptr->get_page_lsn()) {
    fhdl_ptr->update_record(rid, new_rec.data, nullptr);
    page_ptr->set_page_lsn(lsn);
    buffer_pool_manager_->unpin_page(page_id, true);
  } else {
    buffer_pool_manager_->unpin_page(page_id, false);
  }
}