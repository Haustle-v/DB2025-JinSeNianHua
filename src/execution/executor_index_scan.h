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

class IndexScanExecutor : public AbstractExecutor {
 private:
  std::string tab_name_;              // 表名称
  TabMeta tab_;                       // 表的元数据
  std::vector<Condition> conds_;      // 扫描条件
  RmFileHandle *fh_;                  // 表的数据文件句柄
  std::vector<ColMeta> cols_;         // 需要读取的字段
  size_t len_;                        // 选取出来的一条记录的长度
  std::vector<Condition> fed_conds_;  // 扫描条件，和conds_字段相同

  std::vector<std::string> index_col_names_;  // index scan涉及到的索引包含的字段
  IndexMeta index_meta_;                      // index scan涉及到的索引元数据

  Rid rid_;
  std::unique_ptr<RecScan> scan_;

  SmManager *sm_manager_;

 public:
  IndexScanExecutor(SmManager *sm_manager, std::string tab_name, std::vector<Condition> conds,
                    std::vector<std::string> index_col_names, Context *context) {
    sm_manager_ = sm_manager;
    context_ = context;
    tab_name_ = std::move(tab_name);
    tab_ = sm_manager_->db_.get_table(tab_name_);
    conds_ = std::move(conds);
    // index_no_ = index_no;
    index_col_names_ = index_col_names;
    index_meta_ = *(tab_.get_index_meta(index_col_names_));
    fh_ = sm_manager_->fhs_.at(tab_name_).get();
    cols_ = tab_.cols;
    len_ = cols_.back().offset + cols_.back().len;
    std::map<CompOp, CompOp> swap_op = {
        {OP_EQ, OP_EQ}, {OP_NE, OP_NE}, {OP_LT, OP_GT}, {OP_GT, OP_LT}, {OP_LE, OP_GE}, {OP_GE, OP_LE},
    };

    for (auto &cond : conds_) {
      if (cond.lhs_col.tab_name != tab_name_) {
        // lhs is on other table, now rhs must be on this table
        assert(!cond.is_rhs_val && cond.rhs_col.tab_name == tab_name_);
        // swap lhs and rhs
        std::swap(cond.lhs_col, cond.rhs_col);
        cond.op = swap_op.at(cond.op);
      }
    }
    fed_conds_ = conds_;
  }

  //   sqb 为范围查询的另一侧赋最小值 5.30
  void fill_lowest(std::string &col_name, char *key, int offset, int len) {
    switch (tab_.get_col(col_name)->type) {
      case TYPE_INT:
        *(int *)(key + offset) = std::numeric_limits<int>::min();
        break;
      case TYPE_FLOAT:
        *(float *)(key + offset) = std::numeric_limits<float>::min();
        break;
      case TYPE_STRING:
        memset(key + offset, 0, len);
        break;
    }
  }

  //   sqb 为范围查询的另一侧赋最大值 5.30
  void fill_uppest(std::string &col_name, char *key, int offset, int len) {
    switch (tab_.get_col(col_name)->type) {
      case TYPE_INT:
        *(int *)(key + offset) = std::numeric_limits<int>::max();
        break;
      case TYPE_FLOAT:
        *(float *)(key + offset) = std::numeric_limits<float>::max();
        break;
      case TYPE_STRING:
        memset(key + offset, 0xFF, len);
        break;
    }
  }

  // sqb  检查cond中的条件语句中是否包含索引 true代表是等值查询 false为范围 5.30
  bool get_key(std::string &index_col_name, char *lower_key, char *upper_key, int offset, int len) {
    // 列要么是等值查询  给定下界的查询  给定上界的查询  同时给定上下界 暂时不考虑同时给多个下界的情况
    bool lower_inited = false;
    bool upper_inited = false;
    for (auto &cond : conds_) {
      // 仅考虑右侧为值 注意这里会检查所有条件 也就是支持一个索引的上下界检查
      if (cond.lhs_col.col_name == index_col_name && cond.is_rhs_val) {
        switch (cond.op) {
          case OP_EQ:
            memcpy(lower_key + offset, cond.rhs_val.raw->data, len);
            memcpy(upper_key + offset, cond.rhs_val.raw->data, len);
            return true;
          case OP_LT:
          case OP_LE:
            memcpy(upper_key + offset, cond.rhs_val.raw->data, len);
            upper_inited = true;
            break;
          case OP_GT:
          case OP_GE:
            memcpy(lower_key + offset, cond.rhs_val.raw->data, len);
            lower_inited = true;
            break;
          default:
            //   不处理不等号
            break;
        }
      }
    }
    if (!lower_inited) {
      fill_lowest(index_col_name, lower_key, offset, len);
    }
    if (!upper_inited) {
      fill_uppest(index_col_name, upper_key, offset, len);
    }
    return false;
  }

  //   sqb 索引匹配规则的修改在planner里  没有显式的修改cond的顺序
  // 最左匹配要根据索引进行 一直到第一个范围查询都可用（含）5.30
  void beginTuple() override {
    // sqb 加入事务并发语句 6.9
    // if (context_ != nullptr) {
    //   context_->lock_mgr_->lock_shared_on_table(context_->txn_, fh_->GetFd());
    // }
    IxManager *ix_manager_ptr = sm_manager_->get_ix_manager();
    std::string index_name = ix_manager_ptr->get_index_name(tab_name_, index_col_names_);
    auto ix_hdl_ptr = sm_manager_->ihs_[index_name].get();

    // 利用上下界限定b+树上下界  用来初始化scan
    char lower_key[index_meta_.col_tot_len];
    char upper_key[index_meta_.col_tot_len];
    memset(lower_key, 0, sizeof(lower_key));
    memset(upper_key, 0, sizeof(upper_key));
    int offset = 0;

    // 按照索引的顺序 检查cond中的条件语句是否能应用索引 若有 则得到对应键值 current_size代表等值查询数
    int current_size = 0;
    for (; current_size < index_meta_.col_num; ++current_size) {
      // 注意第一个范围查询可用索引 后续都不能使用索引
      auto &index_col_meta = index_meta_.cols[current_size];
      if (!get_key(index_col_meta.name, lower_key, upper_key, offset, index_col_meta.len)) {
        break;
      }
      offset += index_col_meta.len;
    }
    // 填充后续条件
    if (current_size != index_meta_.col_num) {
      offset += index_meta_.cols[current_size++].len;
      for (; current_size < index_meta_.col_num; ++current_size) {
        ColMeta &index_col_meta = index_meta_.cols[current_size];
        fill_lowest(index_col_meta.name, lower_key, offset, index_col_meta.len);
        fill_uppest(index_col_meta.name, upper_key, offset, index_col_meta.len);
        offset += index_col_meta.len;
      }
    }

    // 确保 lower < upper
    offset = 0;
    int tmp = 0;
    for (auto &col_meta : index_meta_.cols) {
      tmp = ix_compare(lower_key + offset, upper_key + offset, col_meta.type, col_meta.len);
      if (tmp != 0) {
        break;
      }
      offset += col_meta.len;
    }

    // 初始化scan
    if (tmp > 0) {
      // lower > upper
      scan_ =
          std::make_unique<IxScan>(ix_hdl_ptr, ix_hdl_ptr->leaf_end(), ix_hdl_ptr->leaf_end(), sm_manager_->get_index_bpm());
    } else {
      // lower <= upper
      scan_ = std::make_unique<IxScan>(ix_hdl_ptr, ix_hdl_ptr->lower_bound(lower_key),
                                       ix_hdl_ptr->upper_bound(upper_key), sm_manager_->get_index_bpm());
    }

    // 开始扫描！
    for (; !scan_->is_end(); scan_->next()) {
      rid_ = scan_->rid();
      std::unique_ptr<RmRecord> rec_ptr = fh_->get_record(rid_, context_);
      if (check_conds(cols_, conds_, rec_ptr.get())) {
        break;
      }
    }
  }

  void nextTuple() override {
    // 对scan的记录扫描检查既可
    scan_->next();
    for (; !scan_->is_end(); scan_->next()) {
      rid_ = scan_->rid();
      std::unique_ptr<RmRecord> rec_ptr = fh_->get_record(rid_, context_);
      if (check_conds(cols_, conds_, rec_ptr.get())) {
        break;
      }
    }
  }

  std::unique_ptr<RmRecord> Next() override {
    if (!scan_->is_end()) {
      return fh_->get_record(rid_, context_);
    }
    return nullptr;
  }

  // sqb 5.30
  bool is_end() const override { return scan_->is_end(); }

  Rid &rid() override { return rid_; }

  // sqb 5.30
  size_t tupleLen() const override { return len_; }

  // sqb 5.30
  std::string getType() override { return "IndexScanExecutor"; }

  // sqb 5.30
  ColMeta get_col_offset(const TabCol &target) override {
    for (auto &col_meta : cols_) {
      if (col_meta.tab_name == target.tab_name && col_meta.name == target.col_name) {
        return col_meta;
      }
    }
    throw ColumnNotFoundError(target.col_name);
  }

  // sqb 5.30
  const std::vector<ColMeta> &cols() const override { return cols_; }
};