/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "sm_manager.h"

#include <sys/stat.h>
#include <unistd.h>

#include <fstream>

#include "index/ix.h"
#include "record/rm.h"
#include "record_printer.h"

/**
 * @description: 判断是否为一个文件夹
 * @return {bool} 返回是否为一个文件夹
 * @param {string&} db_name 数据库文件名称，与文件夹同名
 */
bool SmManager::is_dir(const std::string &db_name) {
  struct stat st;
  return stat(db_name.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
}

/**
 * @description: 创建数据库，所有的数据库相关文件都放在数据库同名文件夹下
 * @param {string&} db_name 数据库名称
 */
void SmManager::create_db(const std::string &db_name) {
  if (is_dir(db_name)) {
    throw DatabaseExistsError(db_name);
  }
  // 为数据库创建一个子目录
  std::string cmd = "mkdir " + db_name;
  if (system(cmd.c_str()) < 0) {  // 创建一个名为db_name的目录
    throw UnixError();
  }
  if (chdir(db_name.c_str()) < 0) {  // 进入名为db_name的目录
    throw UnixError();
  }
  // 创建系统目录
  DbMeta *new_db = new DbMeta();
  new_db->name_ = db_name;

  // 注意，此处ofstream会在当前目录创建(如果没有此文件先创建)和打开一个名为DB_META_NAME的文件
  std::ofstream ofs(DB_META_NAME);

  // 将new_db中的信息，按照定义好的operator<<操作符，写入到ofs打开的DB_META_NAME文件中
  ofs << *new_db;  // 注意：此处重载了操作符<<

  delete new_db;

  // 创建日志文件
  disk_manager_->create_file(LOG_FILE_NAME);

  // 回到根目录
  if (chdir("..") < 0) {
    throw UnixError();
  }
}

/**
 * @description: 删除数据库，同时需要清空相关文件以及数据库同名文件夹
 * @param {string&} db_name 数据库名称，与文件夹同名
 */
void SmManager::drop_db(const std::string &db_name) {
  if (!is_dir(db_name)) {
    throw DatabaseNotFoundError(db_name);
  }
  std::string cmd = "rm -r " + db_name;
  if (system(cmd.c_str()) < 0) {
    throw UnixError();
  }
}

/**
 * @description:
 * 打开数据库，找到数据库对应的文件夹，并加载数据库元数据和相关文件
 * @param {string&} db_name 数据库名称，与文件夹同名
 */
void SmManager::open_db(const std::string &db_name) {
  // sqb :完成数据与索引 5.29

  // 找到目录 并进入
  if (!is_dir(db_name)) {
    throw DatabaseNotFoundError(db_name);
  }
  if (chdir(db_name.c_str()) < 0) {
    throw UnixError();
  }

  //   加载元数据
  std::ifstream ifs(DB_META_NAME);
  ifs >> db_;

  //   加载数据文件
  for (auto &table_and_meta : db_.tabs_) {
    fhs_.emplace(table_and_meta.first, rm_manager_->open_file(table_and_meta.first));
    // 加载表的索引文件
    for (auto &index_meta : table_and_meta.second.indexes) {
      std::string index_name = ix_manager_->get_index_name(table_and_meta.first, index_meta.cols);
      ihs_.emplace(index_name, ix_manager_->open_index(table_and_meta.first, index_meta.cols));
    }
  }
}

/**
 * @description: 把数据库相关的元数据刷入磁盘中
 */
void SmManager::flush_meta() {
  // 默认清空文件
  std::ofstream ofs(DB_META_NAME);
  ofs << db_;
}

/**
 * @description: 关闭数据库并把数据落盘
 */
void SmManager::close_db() {
  // sqb :完成数据与索引 5.29

  // 更新元数据
  flush_meta();
  // 更新数据
  for (auto &entry : fhs_) {
    rm_manager_->close_file(entry.second.get());
  }
  // 更新索引
  for (auto &entry : ihs_) {
    ix_manager_->close_index(entry.second.get());
  }

  //   打扫数据
  db_.name_.clear();
  db_.tabs_.clear();
  fhs_.clear();
  ihs_.clear();

  // 回到根目录
  if (chdir("..") < 0) {
    throw UnixError();
  }
}

/**
 * @description:
 * 显示所有的表,通过测试需要将其结果写入到output.txt,详情看题目文档
 * @param {Context*} context
 */
void SmManager::show_tables(Context *context) {
  std::fstream outfile;
  outfile.open("output.txt", std::ios::out | std::ios::app);
  outfile << "| Tables |\n";
  RecordPrinter printer(1);
  printer.print_separator(context);
  printer.print_record({"Tables"}, context);
  printer.print_separator(context);
  for (auto &entry : db_.tabs_) {
    auto &tab = entry.second;
    printer.print_record({tab.name}, context);
    outfile << "| " << tab.name << " |\n";
  }
  printer.print_separator(context);
  outfile.close();
}

/**
 * @description: 显示表的元数据
 * @param {string&} tab_name 表名称
 * @param {Context*} context
 */
void SmManager::desc_table(const std::string &tab_name, Context *context) {
  TabMeta &tab = db_.get_table(tab_name);

  std::vector<std::string> captions = {"Field", "Type", "Index"};
  RecordPrinter printer(captions.size());
  // Print header
  printer.print_separator(context);
  printer.print_record(captions, context);
  printer.print_separator(context);
  // Print fields
  for (auto &col : tab.cols) {
    std::vector<std::string> field_info = {col.name, coltype2str(col.type), col.index ? "YES" : "NO"};
    printer.print_record(field_info, context);
  }
  // Print footer
  printer.print_separator(context);
}

/**
 * @description: 创建表
 * @param {string&} tab_name 表的名称
 * @param {vector<ColDef>&} col_defs 表的字段
 * @param {Context*} context
 */
void SmManager::create_table(const std::string &tab_name, const std::vector<ColDef> &col_defs, Context *context) {
  if (db_.is_table(tab_name)) {
    throw TableExistsError(tab_name);
  }
  // Create table meta
  int curr_offset = 0;
  TabMeta tab;
  tab.name = tab_name;
  for (auto &col_def : col_defs) {
    ColMeta col = {.tab_name = tab_name,
                   .name = col_def.name,
                   .type = col_def.type,
                   .len = col_def.len,
                   .offset = curr_offset,
                   .index = false};
    curr_offset += col_def.len;
    tab.cols.push_back(col);
  }
  // Create & open record file
  int record_size = curr_offset;  // record_size就是col
                                  // meta所占的大小（表的元数据也是以记录的形式进行存储的）
  rm_manager_->create_file(tab_name, record_size);
  db_.tabs_[tab_name] = tab;
  // fhs_[tab_name] = rm_manager_->open_file(tab_name);
  fhs_.emplace(tab_name, rm_manager_->open_file(tab_name));

  flush_meta();
}

/**
 * @description: 删除表
 * @param {string&} tab_name 表的名称
 * @param {Context*} context
 */
void SmManager::drop_table(const std::string &tab_name, Context *context) {
  // sqb :完成数据与索引 5.29

  if (!db_.is_table(tab_name)) {
    throw TableNotFoundError(tab_name);
  }

  //   删除内存中相关表元数据
  rm_manager_->close_file(fhs_[tab_name].get());
  rm_manager_->destroy_file(tab_name);

  TabMeta &tab_meta = db_.tabs_[tab_name];
  for (auto &index_meta : tab_meta.indexes) {
    drop_index(tab_name, index_meta.cols, context);
  }

  fhs_.erase(tab_name);
  db_.tabs_.erase(tab_name);
  flush_meta();
}

/**
 * @description: 创建索引
 * @param {string&} tab_name 表的名称
 * @param {vector<string>&} col_names 索引包含的字段名称
 * @param {Context*} context
 */
void SmManager::create_index(const std::string &tab_name, const std::vector<std::string> &col_names, Context *context) {
  // sqb 5.29
  if (ix_manager_->exists(tab_name, col_names)) {
    throw IndexExistsError(tab_name, col_names);
  }

  //   创建索引元数据
  //   TabMeta &tab = db_.tabs_[tab_name];
  //   IndexMeta index = {.tab_name = tab_name, .col_num = (int)col_names.size()};
  //   int col_len = 0;
  //   for (auto &col_name : col_names) {
  //     auto col__meta_iter = tab.get_col(col_name);
  //     col_len += col__meta_iter->len;
  //     index.cols.emplace_back(*col__meta_iter);
  //   }
  //   index.col_tot_len = col_len;
  //   tab.indexes.emplace_back(index);

  //   //   创建索引 插入记录
  //   ix_manager_->create_index(tab_name, index.cols);
  //   auto ix_hdl_ptr = ix_manager_->open_index(tab_name, col_names);
  //   auto file_hdl_ptr = fhs_[tab_name].get();
  //   char key_buffer[col_len];
  //   //   for (RmScan scan(file_hdl_ptr); !scan.is_end(); scan.next()) {
  //   //     auto rec_ptr = file_hdl_ptr->get_record(scan.rid(), context);
  //   //     int curr_offset = 0;
  //   //     for (auto &col_meta : index.cols) {
  //   //       memcpy(key_buffer + curr_offset, rec_ptr->data + col_meta.offset, col_meta.len);
  //   //       curr_offset += col_meta.len;
  //   //     }
  //   //     ix_hdl_ptr->insert_entry(key_buffer, scan.rid(), context->txn_);
  //   //   }

  //   ihs_.emplace(ix_manager_->get_index_name(tab_name, col_names), std::move(ix_hdl_ptr));
  //   flush_meta();
}

/**
 * @description: 删除索引
 * @param {string&} tab_name 表名称
 * @param {vector<string>&} col_names 索引包含的字段名称
 * @param {Context*} context
 */
void SmManager::drop_index(const std::string &tab_name, const std::vector<std::string> &col_names, Context *context) {
  // sqb 5.29
  if (!ix_manager_->exists(tab_name, col_names)) {
    throw IndexNotFoundError(tab_name, col_names);
  }

  //   std::string index_name = ix_manager_->get_index_name(tab_name, col_names);
  //   IxIndexHandle *ix_hdl_ptr = ihs_[index_name].get();
  //   int index_page_num = ix_hdl_ptr->get_page_num();

  //   // 缓冲池要删除索引对应页 因为创建时索引写入磁盘绕过了缓冲池 后面创建可能会有虚假缓存命中
  //   // 0 1 作为file leaf hdr 直接绕过了缓冲区读写 不用管
  //   for (page_id_t page_no = 2; page_no < index_page_num; ++page_no) {
  //     buffer_pool_manager_->delete_page({ix_hdl_ptr->get_fd(), page_no});
  //   }

  //   //   删除索引文件
  //   ix_manager_->close_index(ix_hdl_ptr);
  //   ix_manager_->destroy_index(tab_name, col_names);

  //   TabMeta &tab = db_.tabs_[tab_name];
  //   tab.indexes.erase(tab.get_index_meta(col_names));
  //   ihs_.erase(index_name);
  //   flush_meta();
}

/**
 * @description: 删除索引
 * @param {string&} tab_name 表名称
 * @param {vector<ColMeta>&} 索引包含的字段元数据
 * @param {Context*} context
 */
void SmManager::drop_index(const std::string &tab_name, const std::vector<ColMeta> &cols, Context *context) {
  // sqb 5.29
  std::vector<std::string> col_names;
  for (auto &col_meta : cols) {
    col_names.emplace_back(col_meta.name);
  }
  drop_index(tab_name, col_names, context);
}

/**
 * @description:
 * sqb 显示表的索引,参考show tables;
 * @param {Context*} context
 */
void SmManager::show_index(const std::string &tab_name, Context *context) {
  //   std::fstream outfile;
  //   outfile.open("output.txt", std::ios::out | std::ios::app);
  //   RecordPrinter printer(1);

  //   TabMeta &tab_meta = db_.get_table(tab_name);
  //   for (auto &index_meta : tab_meta.indexes) {
  //     std::string output;  // 用于输出到终端
  //     outfile << "| " << tab_name << " | unique | (" << index_meta.cols[0].name;
  //     output += tab_name + " | unique | (" + index_meta.cols[0].name;
  //     for (size_t i = 1; i < index_meta.col_num; ++i) {
  //       outfile << "," << index_meta.cols[i].name;
  //       output += "," + index_meta.cols[i].name;
  //     }
  //     outfile << ") |\n";
  //     output += ")";  // 剩下的 | \n 在下个函数里
  //     printer.print_index({output}, context);
  //   }
  //   outfile.close();
}