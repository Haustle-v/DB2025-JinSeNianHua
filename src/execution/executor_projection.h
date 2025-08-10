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

class ProjectionExecutor : public AbstractExecutor {
 private:
  std::unique_ptr<AbstractExecutor> prev_;  // 投影节点的儿子节点
  std::vector<ColMeta> cols_;               // 需要投影的字段
  size_t len_;                              // 字段总长度
  std::vector<TabCol> sel_cols_;

 public:
  ProjectionExecutor(std::unique_ptr<AbstractExecutor> prev,
                     const std::vector<TabCol> &sel_cols) {
    prev_ = std::move(prev);

    sel_cols_ = sel_cols;

    size_t curr_offset = 0;
    auto &prev_cols = prev_->cols();
    for (auto &sel_col : sel_cols) {
      auto pos = get_col(prev_cols, sel_col);
      auto col = *pos;
      col.offset = curr_offset;
      curr_offset += col.len;
      cols_.push_back(col);
    }
    len_ = curr_offset;
  }
  // sqb :初步完成 未优化 5.24
  void beginTuple() override { prev_->beginTuple(); }

  void nextTuple() override { prev_->nextTuple(); }

  std::unique_ptr<RmRecord> Next() override {
    // 将顺序扫描到的记录投影
    std::unique_ptr<RmRecord> pre_rec = prev_->Next();
    if (!pre_rec) return nullptr;
    
    // 如果投影后记录完全一样，可以直接返回原记录
    if (len_ == pre_rec->size && sel_cols_.size() == prev_->cols().size()) {
        // 检查是否所有列都被选中且顺序相同
        bool all_columns_selected = true;
        for (size_t i = 0; i < sel_cols_.size(); ++i) {
            if (sel_cols_[i].col_name != prev_->cols()[i].name || 
                sel_cols_[i].tab_name != prev_->cols()[i].tab_name) {
                all_columns_selected = false;
                break;
            }
        }
        if (all_columns_selected) {
            return std::move(pre_rec);
        }
    }
    
    std::unique_ptr<RmRecord> proj_rec = std::make_unique<RmRecord>(len_);
    size_t proj_col_num = cols_.size();
    for (size_t proj_idx = 0; proj_idx < proj_col_num; ++proj_idx) {
      auto pre_col = prev_->get_col_offset(sel_cols_[proj_idx]);
      auto &proj_col = cols_[proj_idx];
      memcpy(proj_rec->data + proj_col.offset, pre_rec->data + pre_col.offset,
             proj_col.len);
    }
    return proj_rec;
  }

  Rid &rid() override { return prev_->rid(); }

  size_t tupleLen() const override { return len_; }

  const std::vector<ColMeta> &cols() const override { return cols_; }

  std::string getType() override { return "ProjectionExecutor"; }

  bool is_end() const override { return prev_->is_end(); }

  ColMeta get_col_offset(const TabCol &target) override {
    for (auto &col_meta : cols_) {
      if (col_meta.tab_name == target.tab_name &&
          col_meta.name == target.col_name) {
        return col_meta;
      }
    }
    throw ColumnNotFoundError(target.col_name);
  }
};