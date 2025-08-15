/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "execution_manager.h"

// #include "execution_merge_join.h"
#include "executor_delete.h"
#include "executor_index_scan.h"
#include "executor_insert.h"
#include "executor_nestedloop_join.h"
#include "executor_projection.h"
#include "executor_seq_scan.h"
#include "executor_update.h"
#include "index/ix.h"
#include "record_printer.h"

const char *help_info =
    "Supported SQL syntax:\n"
    "  command ;\n"
    "command:\n"
    "  CREATE TABLE table_name (column_name type [, column_name type ...])\n"
    "  DROP TABLE table_name\n"
    "  CREATE INDEX table_name (column_name)\n"
    "  DROP INDEX table_name (column_name)\n"
    "  INSERT INTO table_name VALUES (value [, value ...])\n"
    "  DELETE FROM table_name [WHERE where_clause]\n"
    "  UPDATE table_name SET column_name = value [, column_name = value ...] "
    "[WHERE where_clause]\n"
    "  SELECT selector FROM table_name [WHERE where_clause]\n"
    "type:\n"
    "  {INT | FLOAT | CHAR(n)}\n"
    "where_clause:\n"
    "  condition [AND condition ...]\n"
    "condition:\n"
    "  column op {column | value}\n"
    "column:\n"
    "  [table_name.]column_name\n"
    "op:\n"
    "  {= | <> | < | > | <= | >=}\n"
    "selector:\n"
    "  {* | column [, column ...]}\n";

// 主要负责执行DDL语句
void QlManager::run_mutli_query(std::shared_ptr<Plan> plan, Context *context) {
  if (auto x = std::dynamic_pointer_cast<DDLPlan>(plan)) {
    switch (x->tag) {
      case T_CreateTable: {
        sm_manager_->create_table(x->tab_name_, x->cols_, context);
        break;
      }
      case T_DropTable: {
        sm_manager_->drop_table(x->tab_name_, context);
        break;
      }
      case T_CreateIndex: {
        sm_manager_->create_index(x->tab_name_, x->tab_col_names_, context);
        break;
      }
      case T_DropIndex: {
        sm_manager_->drop_index(x->tab_name_, x->tab_col_names_, context);
        break;
      }
      default:
        throw InternalError("Unexpected field type");
        break;
    }
  }
}

// 执行help; show tables; desc table; begin; commit; abort;语句
// sqb show index 5.30
void QlManager::run_cmd_utility(std::shared_ptr<Plan> plan, txn_id_t *txn_id, Context *context) {
  if (auto x = std::dynamic_pointer_cast<OtherPlan>(plan)) {
    switch (x->tag) {
      case T_Help: {
        memcpy(context->data_send_ + *(context->offset_), help_info, strlen(help_info));
        *(context->offset_) = strlen(help_info);
        break;
      }
      case T_ShowTable: {
        sm_manager_->show_tables(context);
        break;
      }
      case T_DescTable: {
        sm_manager_->desc_table(x->tab_name_, context);
        break;
      }
      case T_ShowIndex: {
        // sqb show index 5.30
        sm_manager_->show_index(x->tab_name_, context);
        break;
      }
      case T_Transaction_begin: {
        // 显示开启一个事务
        context->txn_->set_txn_mode(true);
        break;
      }
      case T_Transaction_commit: {
        context->txn_ = txn_mgr_->get_transaction(*txn_id);
        txn_mgr_->commit(context->txn_, context->log_mgr_);
        break;
      }
      case T_Transaction_rollback: {
        context->txn_ = txn_mgr_->get_transaction(*txn_id);
        txn_mgr_->abort(context->txn_, context->log_mgr_, context->txn_mgr_);
        break;
      }
      case T_Transaction_abort: {
        context->txn_ = txn_mgr_->get_transaction(*txn_id);
        txn_mgr_->abort(context->txn_, context->log_mgr_, context->txn_mgr_);
        break;
      }
      case T_CreateCheckPoint: {
        create_checkpoint(context);
        break;
      }
      case T_Crash: {
        exit(1);
        break;
      }
      case T_LoadData: {
        sm_manager_->load_csv_data(x->file_name_, x->tab_name_);
        break;
      }
      case T_IoEnable: {
        sm_manager_->io_enabled_ = x->io_enable_;
        break;
      }

      default:
        throw InternalError("Unexpected field type");
        break;
    }

  } else if (auto x = std::dynamic_pointer_cast<SetKnobPlan>(plan)) {
    switch (x->set_knob_type_) {
      case ast::SetKnobType::EnableNestLoop: {
        planner_->set_enable_nestedloop_join(x->bool_value_);
        break;
      }
      case ast::SetKnobType::EnableSortMerge: {
        planner_->set_enable_sortmerge_join(x->bool_value_);
        break;
      }
      default: {
        throw RMDBError("Not implemented!\n");
        break;
      }
    }
  }
}

// 执行select语句，select语句的输出除了需要返回客户端外，还需要写入output.txt文件中
void QlManager::select_from(std::unique_ptr<AbstractExecutor> executorTreeRoot, std::vector<TabCol> sel_cols,
                            Context *context) {
  std::vector<std::string> captions;
  size_t sel_col_num = sel_cols.size();
  captions.reserve(sel_col_num);
  for (auto &sel_col : sel_cols) {
    if (sel_col.aggFuncType != ast::AGG_INVALID) {
      captions.emplace_back(std::move(sel_col.alias));
    } else {
      captions.emplace_back(std::move(sel_col.col_name));
    }
  }

  // Print header into buffer
  RecordPrinter rec_printer(sel_col_num);
  rec_printer.print_separator(context);
  rec_printer.print_record(captions, context);
  rec_printer.print_separator(context);
  // print header into file
  std::fstream outfile;
  if (sm_manager_->io_enabled_) {  // yfs 7.3
    outfile.open("output.txt", std::ios::out | std::ios::app);
    outfile << "|";
    // for (int i = 0; i < captions.size(); ++i) {
    for (int i = 0; i < sel_col_num; ++i) {
      outfile << " " << captions[i] << " |";
    }
    outfile << "\n";
  }

  // Print records
  size_t num_rec = 0;
  // 执行query_plan
  for (executorTreeRoot->beginTuple(); !executorTreeRoot->is_end(); executorTreeRoot->nextTuple()) {
    auto Tuple = executorTreeRoot->Next();
    std::vector<std::string> columns;
    for (auto &col : executorTreeRoot->cols()) {
      std::string col_str;
      char *rec_buf = Tuple->data + col.offset;
      if (col.type == TYPE_INT) {
        col_str = std::to_string(*(int *)rec_buf);
      } else if (col.type == TYPE_FLOAT) {
        col_str = std::to_string(*(float *)rec_buf);
      } else if (col.type == TYPE_STRING) {
        col_str = std::string((char *)rec_buf, col.len);
        col_str.resize(strlen(col_str.c_str()));
      }
      columns.emplace_back(std::move(col_str));
    }
    // print record into buffer
    rec_printer.print_record(columns, context);
    // print record into file
    if (sm_manager_->io_enabled_) {  // yfs 7.3
      outfile << "|";

      size_t cols_num = columns.size();
      for (int i = 0; i < cols_num; ++i) {
        outfile << " " << columns[i] << " |";
      }
      outfile << "\n";
    }
    num_rec++;
  }
  if (sm_manager_->io_enabled_) {
    outfile.close();
  }
  // Print footer into buffer
  rec_printer.print_separator(context);
  // Print record count into buffer
  RecordPrinter::print_record_count(num_rec, context);
}

// 执行DML语句
void QlManager::run_dml(std::unique_ptr<AbstractExecutor> exec) { exec->Next(); }

// 创建检查点
void QlManager::create_checkpoint(Context *context) {
  // sqb 6.11 单事务下创建检查点 没考虑多事务 没考虑索引
  // 添加检查点日志 日志刷盘
  CkptLogRecord log_record{context->txn_->get_transaction_id()};
  log_record.prev_lsn_ = context->txn_->get_prev_lsn();
  lsn_t checkpoint_lsn = context->log_mgr_->add_log_to_buffer(&log_record);
  context->txn_->set_prev_lsn(checkpoint_lsn);
  context->log_mgr_->flush_log_to_disk();
  // 缓冲区落盘
  auto bpm_ptr = sm_manager_->get_bpm();
  auto dm_ptr = sm_manager_->get_disk_manager();
  for (auto &entry : sm_manager_->fhs_) {
    auto fhdl_ptr = entry.second.get();
    RmFileHdr file_hdr = fhdl_ptr->get_file_hdr();
    dm_ptr->write_page(fhdl_ptr->GetFd(), RM_FILE_HDR_PAGE, (char *)(&(file_hdr)), sizeof(file_hdr));
    bpm_ptr->flush_all_pages(fhdl_ptr->GetFd());
  }
}

//   sqb 快速返回select count结果，仅单表
// 执行select语句，select语句的输出除了需要返回客户端外，还需要写入output.txt文件中
void QlManager::quick_count_table(std::string &tab_name, std::string &sel_col, Context *context) {
  auto &fhdl_ptr = sm_manager_->fhs_.at(tab_name);
  size_t record_num = fhdl_ptr->get_record_num();
  std::vector<std::string> captions;
  captions.emplace_back(sel_col);

  // Print header into buffer
  RecordPrinter rec_printer(1);
  rec_printer.print_separator(context);
  rec_printer.print_record(captions, context);
  rec_printer.print_separator(context);
  // print header into file
  std::fstream outfile;
  if (sm_manager_->io_enabled_) {  // yfs 7.3
    outfile.open("output.txt", std::ios::out | std::ios::app);
    outfile << "|";
    for (int i = 0; i < captions.size(); ++i) {
      outfile << " " << captions[i] << " |";
    }
    outfile << "\n";
  }

  // Print records
  size_t num_rec = 1;
  std::vector<std::string> columns;
  columns.emplace_back(std::to_string(record_num));
  // print record into buffer
  rec_printer.print_record(columns, context);
  // print record into file
  if (sm_manager_->io_enabled_) {  // yfs 7.3
    outfile << "|";
    for (int i = 0; i < columns.size(); ++i) {
      outfile << " " << columns[i] << " |";
    }
    outfile << "\n";
  }

  if (sm_manager_->io_enabled_) {
    outfile.close();
  }
  // Print footer into buffer
  rec_printer.print_separator(context);
  // Print record count into buffer
  RecordPrinter::print_record_count(num_rec, context);
}
