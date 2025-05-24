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

#include "execution_defs.h"
#include "execution_manager.h"
#include "executor_abstract.h"
#include "index/ix.h"
#include "system/sm.h"

class SeqScanExecutor : public AbstractExecutor {
 private:
  std::string tab_name_;              // 表的名称
  std::vector<Condition> conds_;      // scan的条件
  RmFileHandle *fh_;                  // 表的数据文件句柄
  std::vector<ColMeta> cols_;         // scan后生成的记录的字段
  size_t len_;                        // scan后生成的每条记录的长度
  std::vector<Condition> fed_conds_;  // 同conds_，两个字段相同

  Rid rid_;
  std::unique_ptr<RecScan> scan_;  // table_iterator

  SmManager *sm_manager_;

 public:
  SeqScanExecutor(SmManager *sm_manager, std::string tab_name,
                  std::vector<Condition> conds, Context *context) {
    sm_manager_ = sm_manager;
    tab_name_ = std::move(tab_name);
    conds_ = std::move(conds);
    TabMeta &tab = sm_manager_->db_.get_table(tab_name_);
    fh_ = sm_manager_->fhs_.at(tab_name_).get();
    cols_ = tab.cols;
    len_ = cols_.back().offset + cols_.back().len;

    context_ = context;

    fed_conds_ = conds_;
  }

  // sqb 5.23
  void beginTuple() override { nextTuple(); }

  // sqb 5.23
  void nextTuple() override {
    // 已存在时rid指向了一个有效元组 需扫描下一个记录 不存在时先创建 然后检查
    if (scan_) {
      scan_->next();
    } else {
      scan_ = std::make_unique<RmScan>(fh_);
    }

    // 需要顺序扫描 满足条件的记录 注意当前框架的记录就是元组
    for (; !scan_->is_end(); scan_->next()) {
      std::unique_ptr<RmRecord> rec_ptr =
          fh_->get_record(scan_->rid(), context_);
      if (check_conds(cols_, conds_, rec_ptr.get())) {
        break;
      }
    }
    // 条件符合或到达循环末尾会到这 都可以正常处理
    rid_ = scan_->rid();
  }

  // sqb 5.23
  bool is_end() const override { return scan_->is_end(); }

  // sqb 5.23
  std::unique_ptr<RmRecord> Next() override {
    // 会先调用begin tuple 和 next tuple  实际是取当前有效rid_
    if (rid_.page_no != INVALID_PAGE_ID) {
      // 有效则读 应该有RVO
      return fh_->get_record(rid_, context_);
    }
    return nullptr;
  }

  size_t tupleLen() const override { return len_; }

  // sqb 5.23
  Rid &rid() override { return rid_; }

  // sqb 5.23
  std::string getType() override { return "SeqScanExecutor"; }

  // sqb 5.23
  ColMeta get_col_offset(const TabCol &target) override {
    for (auto &col_meta : cols_) {
      if (col_meta.tab_name == target.tab_name &&
          col_meta.name == target.col_name) {
        return col_meta;
      }
    }
    throw ColumnNotFoundError(target.col_name);
  }

  // sqb 5.23
  const std::vector<ColMeta> &cols() const override { return cols_; }
};