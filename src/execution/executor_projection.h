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

// 1. [新增] 定义一个结构体，用于缓存投影所需的核心信息
// 这样可以避免在Next()的循环中重复查找
struct ProjectionInfo {
    size_t src_offset;   // 列在源记录中的偏移量
    size_t dest_offset;  // 列在目标记录中的偏移量
    size_t len;          // 列的长度
    ProjectionInfo(size_t src, size_t dest, size_t l)
        : src_offset(src), dest_offset(dest), len(l) {}
};

class ProjectionExecutor : public AbstractExecutor {
 private:
  std::unique_ptr<AbstractExecutor> prev_;  // 投影节点的儿子节点
  std::vector<ColMeta> cols_;               // 投影后输出的字段元数据
  size_t len_;                              // 投影后输出的字段总长度
  std::vector<TabCol> sel_cols_;            // 需要投影的原始列信息
  
  // 2. [新增] 缓存投影信息的核心数据结构
  std::vector<ProjectionInfo> proj_info_;

 public:
  ProjectionExecutor(std::unique_ptr<AbstractExecutor> prev,
                     const std::vector<TabCol> &sel_cols) {
    prev_ = std::move(prev);
    sel_cols_ = sel_cols;

    size_t curr_offset = 0;
    
    // 3. [优化] 在构造函数中一次性计算好所有列的投影信息
    for (auto &sel_col : sel_cols) {
      // 从子节点获取一次原始列的元数据
      // 这里的get_col_offset仍然是O(N)查找，但整个构造函数只执行一次，开销可接受
      auto prev_col_meta = prev_->get_col_offset(sel_col);

      // 缓存投影信息到 proj_info_
      proj_info_.emplace_back(prev_col_meta.offset, curr_offset, prev_col_meta.len);

      // 构建投影后的新元数据
      auto new_col = prev_col_meta;
      new_col.offset = curr_offset;
      cols_.push_back(new_col);

      curr_offset += prev_col_meta.len;
    }
    len_ = curr_offset;
  }

  void beginTuple() override { prev_->beginTuple(); }

  void nextTuple() override { prev_->nextTuple(); }

  std::unique_ptr<RmRecord> Next() override {
    // 从子节点获取原始记录
    std::unique_ptr<RmRecord> pre_rec = prev_->Next();

    // 如果子节点没有更多记录，则返回nullptr
    if (pre_rec == nullptr) {
      return nullptr;
    }

    // 创建用于存放投影结果的记录
    auto proj_rec = std::make_unique<RmRecord>(len_);

    // 4. [优化] 直接使用缓存的proj_info_进行数据复制，无任何查找操作
    for (const auto &info : proj_info_) {
      memcpy(proj_rec->data + info.dest_offset, pre_rec->data + info.src_offset,
             info.len);
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