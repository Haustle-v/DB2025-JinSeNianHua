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

#include "common/context.h"
#include "index/ix.h"
#include "record/rm_file_handle.h"
#include "sm_defs.h"
#include "sm_meta.h"

class Context;

struct ColDef {
  std::string name;  // Column name
  ColType type;      // Type of column
  int len;           // Length of column
};

/* 系统管理器，负责元数据管理和DDL语句的执行 */
class SmManager {
 public:
  DbMeta db_;  // 当前打开的数据库的元数据
  std::unordered_map<std::string, std::unique_ptr<RmFileHandle>>
      fhs_;  // file name -> record file handle, 当前数据库中每张表的数据文件
  std::unordered_map<std::string, std::unique_ptr<IxIndexHandle>>
      ihs_;  // file name -> index file handle, 当前数据库中每个索引的文件
 private:
  DiskManager *disk_manager_;
  BufferPoolManager *buffer_pool_manager_;
  RmManager *rm_manager_;
  IxManager *ix_manager_;

  //   sqb 把rollback和redo的共有代码提出来 参照对应算子实现 6.8
  void record_insert_helper(const std::string &tab_name, const Rid &rid, const RmRecord &rec,
                            const lsn_t lsn = INVALID_LSN);

  void record_delete_helper(const std::string &tab_name, const Rid &rid, const lsn_t lsn = INVALID_LSN);

  void record_update_helper(const std::string &tab_name, const Rid &rid, const RmRecord &new_rec,
                            const lsn_t lsn = INVALID_LSN);

 public:
  SmManager(DiskManager *disk_manager, BufferPoolManager *buffer_pool_manager, RmManager *rm_manager,
            IxManager *ix_manager)
      : disk_manager_(disk_manager),
        buffer_pool_manager_(buffer_pool_manager),
        rm_manager_(rm_manager),
        ix_manager_(ix_manager) {}

  ~SmManager() {}

  BufferPoolManager *get_bpm() { return buffer_pool_manager_; }

  RmManager *get_rm_manager() { return rm_manager_; }

  IxManager *get_ix_manager() { return ix_manager_; }

  DiskManager *get_disk_manager() { return disk_manager_; }

  bool is_dir(const std::string &db_name);

  void create_db(const std::string &db_name);

  void drop_db(const std::string &db_name);

  void open_db(const std::string &db_name);

  void close_db();

  void flush_meta();

  void show_tables(Context *context);

  void desc_table(const std::string &tab_name, Context *context);

  void create_table(const std::string &tab_name, const std::vector<ColDef> &col_defs, Context *context);

  void drop_table(const std::string &tab_name, Context *context);

  void create_index(const std::string &tab_name, const std::vector<std::string> &col_names, Context *context);

  void drop_index(const std::string &tab_name, const std::vector<std::string> &col_names, Context *context);

  void drop_index(const std::string &tab_name, const std::vector<ColMeta> &col_names, Context *context);

  // sqb : show index 5.30
  void show_index(const std::string &tab_name, Context *context);

  // sqb 回滚增删改 等价于undo 将进行相反操作 6.8
  void rollback_insert(const std::string &tab_name, const Rid &rid, const lsn_t lsn = INVALID_LSN) {
    record_delete_helper(tab_name, rid, lsn);
  }

  void rollback_delete(const std::string &tab_name, const Rid &rid, const RmRecord &rec,
                       const lsn_t lsn = INVALID_LSN) {
    record_insert_helper(tab_name, rid, rec, lsn);
  }

  void rollback_update(const std::string &tab_name, const Rid &rid, const RmRecord &old_rec,
                       const lsn_t lsn = INVALID_LSN) {
    record_update_helper(tab_name, rid, old_rec, lsn);
  }
};