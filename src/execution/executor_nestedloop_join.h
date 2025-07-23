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

class NestedLoopJoinExecutor : public AbstractExecutor {
 private:
  std::unique_ptr<AbstractExecutor> left_;   // 左儿子节点（需要join的表）
  std::unique_ptr<AbstractExecutor> right_;  // 右儿子节点（需要join的表）
  size_t len_;                               // join后获得的每条记录的长度
  std::vector<ColMeta> cols_;                // join后获得的记录的字段

  std::vector<Condition> fed_conds_;  // join条件
  bool isend;
  JoinType join_type_;

  //   sqb: 左右缓冲区 注意后期优化限制大小 5.24
  std::vector<std::unique_ptr<RmRecord>> Lbuffer;
  std::vector<std::unique_ptr<RmRecord>> Rbuffer;
  size_t Lpos{0}, Rpos{0};                 // 标记两个缓冲区扫描的位置
  std::unique_ptr<RmRecord> cur_rec_ptr_;  // 标记当前有效记录

  // 用于缓存 get_col_offset 结果的哈希表
  std::unordered_map<TabCol, ColMeta> col_meta_cache_;

 public:
  NestedLoopJoinExecutor(std::unique_ptr<AbstractExecutor> left,
                         std::unique_ptr<AbstractExecutor> right,
                         std::vector<Condition> conds,
                        JoinType join_type) {
    left_ = std::move(left);
    right_ = std::move(right);
    len_ = left_->tupleLen() + right_->tupleLen();
    cols_ = left_->cols();
    auto right_cols = right_->cols();
    for (auto &col : right_cols) {
      col.offset += left_->tupleLen();
    }

    cols_.insert(cols_.end(), right_cols.begin(), right_cols.end());
    isend = false;
    fed_conds_ = std::move(conds);
    join_type_ = std::move(join_type);
  }

  // sqb: 先实现一个最直接的嵌套循环连接 应该还有预读或者分块的做法
  // 目前这种不限制缓冲大小可能会爆内存 5.24
  void beginTuple() override {
    Lbuffer.clear();
    for (left_->beginTuple(); !left_->is_end(); left_->nextTuple()) {
      Lbuffer.emplace_back(left_->Next());
    }

    Rbuffer.clear();
    for (right_->beginTuple(); !right_->is_end(); right_->nextTuple()) {
      Rbuffer.emplace_back(right_->Next());
    }
    Lpos = Rpos = 0;
    nextTuple();
  }

  void nextTuple() override {
    size_t Lsize = Lbuffer.size();
    size_t Rsize = Rbuffer.size();
    bool is_find = false;

    // 只要在Rbuffer找到匹配就可以跳出右层循环了
    if (join_type_ == JoinType::SEMI_JOIN) {
      for (; Lpos < Lsize && !is_find; ++Lpos) {
        auto &lrec_ptr = Lbuffer[Lpos];
        for (; Rpos < Rsize && !is_find; ++Rpos) {
          auto &rrec_ptr = Rbuffer[Rpos];
          // 先拼成新元组后再检查
          cur_rec_ptr_ = std::make_unique<RmRecord>(left_->tupleLen());
          auto temp = std::make_unique<RmRecord>(len_);   //临时构造一个拼接记录，仅用于条件判断
          memcpy(temp->data, lrec_ptr->data, lrec_ptr->size);
          memcpy(temp->data + lrec_ptr->size, rrec_ptr->data,
                rrec_ptr->size);
          if (check_conds(cols_, fed_conds_, temp.get())) {
            // semi join 只保留左表记录
            memcpy(cur_rec_ptr_->data, lrec_ptr->data, lrec_ptr->size);
            is_find = true;
            break;    // 一旦匹配到，就直接break，不需要再遍历右表了
          }
        }
        //   注意外循环需迭代全部内表
        if (!is_find) {   // 如果没找到，Rpos归零，左表++Lpos继续找
          Rpos = 0;}
        else {         
          ++Lpos;   // 如果找到了，Rpos归零，左表++Lpos，跳出循环。注意这里要手动++，因为break就不会经过for的++Lpos
          break;
        }
      }

      // 注意没找到时要释放rec
      if (!is_find) {
        cur_rec_ptr_ = nullptr;
      }
    }else{

    for (; Lpos < Lsize && !is_find; ++Lpos) {
      auto &lrec_ptr = Lbuffer[Lpos];
      for (; Rpos < Rsize && !is_find; ++Rpos) {
        auto &rrec_ptr = Rbuffer[Rpos];
        // 先拼成新元组后再检查
        cur_rec_ptr_ = std::make_unique<RmRecord>(len_);
        memcpy(cur_rec_ptr_->data, lrec_ptr->data, lrec_ptr->size);
        memcpy(cur_rec_ptr_->data + lrec_ptr->size, rrec_ptr->data,
               rrec_ptr->size);
        if (check_conds(cols_, fed_conds_, cur_rec_ptr_.get())) {
          // 注意这里不是break 内循环会因find退出 但Rpos可以顺利自增
          // 同时外循环用break退出 避免Lpos变化（不执行++Lpos了）！保证下一次还是从这个Lpos寻找，而Rpos就从下一个位置
          is_find = true;
        }
      }
      //   注意外循环需迭代全部内表
      if (!is_find) {
        Rpos = 0;
      } else {
        break;
      }
    }

    // 注意没找到时要释放rec
    if (!is_find) {
      cur_rec_ptr_ = nullptr;
    }}
  }

  // sqb 5.24
  size_t tupleLen() const override { return len_; }
  // sqb 5.24
  bool is_end() const override { return cur_rec_ptr_ == nullptr; }

  //   sqb 5.24
  std::unique_ptr<RmRecord> Next() override { return std::move(cur_rec_ptr_); }

  Rid &rid() override { return _abstract_rid; }

  // sqb 5.24
  std::string getType() override { return "NestedLoopJoinExecutor"; }

  // sqb 5.24
  ColMeta get_col_offset(const TabCol &target) override {
    auto it = col_meta_cache_.find(target);
    if (it != col_meta_cache_.end()) {
      return it->second;
    }
    for (auto &col_meta : cols_) {
      if (col_meta.tab_name == target.tab_name &&
          col_meta.name == target.col_name) {
        col_meta_cache_[target] = col_meta;
        return col_meta;
      }
    }
    throw ColumnNotFoundError(target.col_name);
  }

  // sqb 5.24
  const std::vector<ColMeta> &cols() const override { return cols_; }
};