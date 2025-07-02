/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "transaction_manager.h"
#include "record/rm_file_handle.h"
#include "system/sm_manager.h"

std::unordered_map<txn_id_t, Transaction *> TransactionManager::txn_map = {};

/**
 * @description: 事务的开始方法
 * @return {Transaction*} 开始事务的指针
 * @param {Transaction*} txn 事务指针，空指针代表需要创建新事务，否则开始已有事务
 * @param {LogManager*} log_manager 日志管理器指针
 */
Transaction *TransactionManager::begin(Transaction *txn, LogManager *log_manager) {
  // Todo:
  // 1. 判断传入事务参数是否为空指针
  // 2. 如果为空指针，创建新事务
  // 3. 把开始事务加入到全局事务表中
  // 4. 返回当前事务指针
  // 如果需要支持MVCC请在上述过程中添加代码

  // sqb 未涉及mvcc 未涉及日志6.4
  if (txn == nullptr) {
    txn = new Transaction(next_txn_id_++);
    txn->set_start_ts(next_timestamp_++);
  }
  {
    std::scoped_lock<std::mutex> lock(latch_);
    txn_map.emplace(txn->get_transaction_id(), txn);
  }

  return txn;
}

/**
 * @description: 事务的提交方法
 * @param {Transaction*} txn 需要提交的事务
 * @param {LogManager*} log_manager 日志管理器指针
 */
void TransactionManager::commit(Transaction *txn, LogManager *log_manager) {
  // Todo:
  // 1. 如果存在未提交的写操作，提交所有的写操作
  // 2. 释放所有锁
  // 3. 释放事务相关资源，eg.锁集
  // 4. 把事务日志刷入磁盘中
  // 5. 更新事务状态
  // 如果需要支持MVCC请在上述过程中添加代码

  // sqb 未考虑mvcc 未考虑日志 6.4
  // 直接进行写操作 所以不会存在未提交的写

  //  释放锁
  auto lock_set_ptr = txn->get_lock_set();
  for (auto &lock_id : *lock_set_ptr) {
    lock_manager_->unlock(txn, lock_id);
  }
  //   释放资源 感觉后面可以去掉
  lock_set_ptr->clear();
  txn->get_write_set()->clear();
  txn->get_index_deleted_page_set()->clear();
  txn->get_index_latch_page_set()->clear();

  txn->set_state(TransactionState::COMMITTED);
}

/**
 * @description: 事务的终止（回滚）方法
 * @param {Transaction *} txn 需要回滚的事务
 * @param {LogManager} *log_manager 日志管理器指针
 */
void TransactionManager::abort(Transaction *txn, LogManager *log_manager) {
  // Todo:
  // 1. 回滚所有写操作
  // 2. 释放所有锁
  // 3. 清空事务相关资源，eg.锁集
  // 4. 把事务日志刷入磁盘中
  // 5. 更新事务状态
  // 如果需要支持MVCC请在上述过程中添加代码

  // sqb 未考虑mvcc 未考虑日志 6.4

  //   写操作回滚
  auto write_set_ptr = txn->get_write_set();
  for (auto iter = write_set_ptr->rbegin(); iter != write_set_ptr->rend(); ++iter) {
    auto &write_rec_ptr = *iter;
    switch (write_rec_ptr->GetWriteType()) {
      case WType::INSERT_TUPLE: {
        rollback_insert(*write_rec_ptr);
        break;
      }
      case WType::DELETE_TUPLE: {
        rollback_delete(*write_rec_ptr);
        break;
      }
      case WType::UPDATE_TUPLE: {
        rollback_update(*write_rec_ptr);
        break;
      }
    }
  }
  //  释放锁
  auto lock_set_ptr = txn->get_lock_set();
  for (auto &lock_id : *lock_set_ptr) {
    lock_manager_->unlock(txn, lock_id);
  }
  //   释放资源 感觉后面可以去掉
  lock_set_ptr->clear();
  txn->get_write_set()->clear();
  txn->get_index_deleted_page_set()->clear();
  txn->get_index_latch_page_set()->clear();

  txn->set_state(TransactionState::ABORTED);
}

// sqb 回滚插入的记录  三种回滚基本都参照对应算子实现 回滚应该不需要再进行事务记录吧…… 6.4
void TransactionManager::rollback_insert(WriteRecord &write_rec) {
  // 插入回滚对应删除 先删索引再删记录
  std::string &tab_name = write_rec.GetTableName();
  Rid rid = write_rec.GetRid();
  IxManager *ix_manager_ptr = sm_manager_->get_ix_manager();

  TabMeta &tab_meta = sm_manager_->db_.get_table(tab_name);
  auto fhdl_ptr = sm_manager_->fhs_.at(tab_name).get();
  std::unique_ptr<RmRecord> rec_ptr = fhdl_ptr->get_record(rid, nullptr);

  //   删除索引
  for (auto &index_meta : tab_meta.indexes) {
    std::string index_name = ix_manager_ptr->get_index_name(tab_name, index_meta.cols);
    auto ix_hdl_ptr = sm_manager_->ihs_[index_name].get();
    char key_buffer[index_meta.col_tot_len];
    int offset = 0;
    for (auto &col_meta : index_meta.cols) {
      memcpy(key_buffer + offset, rec_ptr->data + col_meta.offset, col_meta.len);
      offset += col_meta.len;
    }
    ix_hdl_ptr->delete_entry(key_buffer, nullptr);
  }

  //   删除记录
  fhdl_ptr->delete_record(rid, nullptr);
}

// sqb 回滚插入的记录 6.4
void TransactionManager::rollback_delete(WriteRecord &write_rec) {
  // 删除回滚对应插入 先插入记录再插入索引 不同于删除的是 这里不指定位置
  std::string &tab_name = write_rec.GetTableName();
  RmRecord &rec = write_rec.GetRecord();
  IxManager *ix_manager_ptr = sm_manager_->get_ix_manager();

  TabMeta &tab_meta = sm_manager_->db_.get_table(tab_name);
  auto fhdl_ptr = sm_manager_->fhs_.at(tab_name).get();

  //   插入记录
  //   Rid rid = fhdl_ptr->insert_record(rec.data, nullptr);
  Rid rid = write_rec.GetRid();
  fhdl_ptr->allocate_pages(rid);
  fhdl_ptr->insert_record(rid, rec.data);

  //   插入索引
  for (auto &index_meta : tab_meta.indexes) {
    std::string index_name = ix_manager_ptr->get_index_name(tab_name, index_meta.cols);
    auto ix_hdl_ptr = sm_manager_->ihs_[index_name].get();
    char key_buffer[index_meta.col_tot_len];
    int offset = 0;
    for (auto &col_meta : index_meta.cols) {
      memcpy(key_buffer + offset, rec.data + col_meta.offset, col_meta.len);
      offset += col_meta.len;
    }
    ix_hdl_ptr->insert_entry(key_buffer, rid, nullptr);
  }
}

// sqb 回滚插入的记录 6.4
void TransactionManager::rollback_update(WriteRecord &write_rec) {
  // 更新回滚与自身行为一致  先删旧索引 插入新记录 插入新索引
  std::string &tab_name = write_rec.GetTableName();
  Rid rid = write_rec.GetRid();
  RmRecord &old_rec = write_rec.GetRecord();
  IxManager *ix_manager_ptr = sm_manager_->get_ix_manager();

  TabMeta &tab_meta = sm_manager_->db_.get_table(tab_name);
  auto fhdl_ptr = sm_manager_->fhs_.at(tab_name).get();

  std::unique_ptr<RmRecord> cur_rec_ptr = fhdl_ptr->get_record(rid, nullptr);

  // 删除旧索引
  for (auto &index_meta : tab_meta.indexes) {
    std::string index_name = ix_manager_ptr->get_index_name(tab_name, index_meta.cols);
    auto ix_hdl_ptr = sm_manager_->ihs_[index_name].get();
    char key_buffer[index_meta.col_tot_len];
    int offset = 0;
    for (auto &col_meta : index_meta.cols) {
      memcpy(key_buffer + offset, cur_rec_ptr->data + col_meta.offset, col_meta.len);
      offset += col_meta.len;
    }
    ix_hdl_ptr->delete_entry(key_buffer, nullptr);
  }

  //   插入记录
  fhdl_ptr->update_record(rid, old_rec.data, nullptr);

  //   插入新索引
  for (auto &index_meta : tab_meta.indexes) {
    std::string index_name = ix_manager_ptr->get_index_name(tab_name, index_meta.cols);
    auto ix_hdl_ptr = sm_manager_->ihs_[index_name].get();
    char key_buffer[index_meta.col_tot_len];
    int offset = 0;
    for (auto &col_meta : index_meta.cols) {
      memcpy(key_buffer + offset, old_rec.data + col_meta.offset, col_meta.len);
      offset += col_meta.len;
    }
    ix_hdl_ptr->insert_entry(key_buffer, rid, nullptr);
  }
}