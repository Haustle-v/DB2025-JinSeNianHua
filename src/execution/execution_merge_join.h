
#pragma once
#include "execution_defs.h"
#include "execution_manager.h"
#include "executor_abstract.h"
#include "index/ix.h"
#include "system/sm.h"

class MergeJoinExecutor : public AbstractExecutor {
 private:
  std::unique_ptr<AbstractExecutor> left_;   // 左儿子节点（需要join的表）
  std::unique_ptr<AbstractExecutor> right_;  // 右儿子节点（需要join的表）
  size_t len_;                               // join后获得的每条记录的长度
  std::vector<ColMeta> cols_;                // join后获得的记录的字段

  std::vector<Condition> fed_conds_;  // join条件
  bool isend;
  JoinType join_type_;

  std::vector<Condition> equal_conds_;      // 等值连接
  std::vector<Condition> non_equal_conds_;  // 非等值连接
  std::vector<ColMeta> LequalCols;          // 等值连接排序用
  std::vector<ColMeta> RequalCols;          // 等值连接排序用

  //   sqb: 左右缓冲区 注意后期优化限制大小 5.24
  std::vector<std::unique_ptr<RmRecord>> Lbuffer;
  std::vector<std::unique_ptr<RmRecord>> Rbuffer;
  size_t Lpos{0}, Rpos{0};                 // 标记两个缓冲区扫描的位置
  std::unique_ptr<RmRecord> cur_rec_ptr_;  // 标记当前有效记录

  size_t mark_pos_{0};  // 右表回溯标记

  // 用于缓存 get_col_offset 结果的哈希表
  std::unordered_map<TabCol, ColMeta> col_meta_cache_;

  //   目前merge join会先做两表排序，同时支持了非等值排序，需要后期在算子树上进行优化并调整
 public:
  MergeJoinExecutor(std::unique_ptr<AbstractExecutor> left, std::unique_ptr<AbstractExecutor> right,
                    std::vector<Condition> conds, JoinType join_type) {
    left_ = std::move(left);
    right_ = std::move(right);
    len_ = left_->tupleLen() + right_->tupleLen();
    cols_ = left_->cols();
    auto right_cols = right_->cols();

    // 区分等值与非等值条件
    for (auto &cond : conds) {
      if (cond.op == CompOp::OP_EQ) {
        equal_conds_.emplace_back(cond);
        LequalCols.emplace_back(*get_col(cols_, cond.lhs_col));
        RequalCols.emplace_back(*get_col(right_cols, cond.rhs_col));
      } else {
        non_equal_conds_.emplace_back(cond);
      }
    }

    for (auto &col : right_cols) {
      col.offset += left_->tupleLen();
    }

    cols_.insert(cols_.end(), right_cols.begin(), right_cols.end());
    isend = false;
    fed_conds_ = std::move(conds);
    join_type_ = std::move(join_type);
  }

  //   将基于等值的排序合并缝进来
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

    // 区分是否包含等值条件，有则根据等值连接的字段排序，目前是升序
    if (!equal_conds_.empty()) {
      //   左表先排序
      std::sort(Lbuffer.begin(), Lbuffer.end(),
                [this](const std::unique_ptr<RmRecord> &a, const std::unique_ptr<RmRecord> &b) {
                  for (auto &col_meta : LequalCols) {
                    int cmp =
                        ix_compare(a->data + col_meta.offset, b->data + col_meta.offset, col_meta.type, col_meta.len);
                    if (cmp != 0) {
                      return cmp < 0;
                    }
                  }
                  //   全列相等不动
                  return false;
                });

      // 右表排序
      std::sort(Rbuffer.begin(), Rbuffer.end(),
                [this](const std::unique_ptr<RmRecord> &a, const std::unique_ptr<RmRecord> &b) {
                  for (auto &col_meta : RequalCols) {
                    int cmp =
                        ix_compare(a->data + col_meta.offset, b->data + col_meta.offset, col_meta.type, col_meta.len);
                    if (cmp != 0) {
                      return cmp < 0;
                    }
                  }
                  //   全列相等不动
                  return false;
                });
    }

    nextTuple();
  }

  void nextTuple() override {
    size_t Lsize = Lbuffer.size();
    size_t Rsize = Rbuffer.size();
    size_t eq_cond_num = equal_conds_.size();
    size_t non_eq_cond_num = non_equal_conds_.size();
    bool is_find = false;

    // 有等值连接就先做排序合并在嵌套，没有等值就默认为嵌套
    if (!equal_conds_.empty()) {
      while (Lpos < Lsize && Rpos < Rsize) {
        bool has_backtrace = false;  // 控制回溯标记

        // 内部先做等值连接的排序合并，随后为非等值连接做嵌套连接
        auto &lrec_ptr = Lbuffer[Lpos];
        auto &rrec_ptr = Rbuffer[Rpos];
        int cmp = 0;
        for (size_t i = 0; i < eq_cond_num; ++i) {
          cmp = ix_compare(lrec_ptr->data + LequalCols[i].offset, rrec_ptr->data + RequalCols[i].offset,
                           LequalCols[i].type, LequalCols[i].len);
          if (cmp != 0) {
            break;
          }
        }

        if (cmp == 0) {
          // 检查其它非等值连接条件
          cur_rec_ptr_ = std::make_unique<RmRecord>(len_);
          memcpy(cur_rec_ptr_->data, lrec_ptr->data, lrec_ptr->size);
          memcpy(cur_rec_ptr_->data + lrec_ptr->size, rrec_ptr->data, rrec_ptr->size);
          if (non_eq_cond_num == 0 || check_conds(cols_, non_equal_conds_, cur_rec_ptr_.get())) {
            is_find = true;
          }
          ++Rpos;
          //   处理相同等值的回溯
          if (Rpos >= Rsize) {
            ++Lpos;
            has_backtrace = true;
            Rpos = mark_pos_;
          }
        } else if (cmp > 0) {
          ++Rpos;
        } else {
          ++Lpos;
          //   视情况回溯
          if (Lpos < Lsize) {
            bool all_equal = true;
            for (size_t i = 0; i < eq_cond_num; ++i) {
              if (ix_compare(Lbuffer[Lpos]->data + LequalCols[i].offset,
                             Rbuffer[mark_pos_]->data + RequalCols[i].offset, LequalCols[i].type,
                             LequalCols[i].len) != 0) {
                all_equal = false;
                break;
              }
            }
            if (all_equal) {
              has_backtrace = true;
              Rpos = mark_pos_;
            }
          }
        }

        // 未回溯时标记右侧表第一个不同值出现的位置
        if (!has_backtrace) {
          size_t tmp_pos = cmp >= 0 ? Rpos - 1 : Rpos;
          if (tmp_pos != mark_pos_) {
            for (size_t i = 0; i < eq_cond_num; ++i) {
              if (tmp_pos < Rsize && ix_compare(Rbuffer[tmp_pos]->data + RequalCols[i].offset,
                                                Rbuffer[mark_pos_]->data + RequalCols[i].offset, RequalCols[i].type,
                                                RequalCols[i].len) != 0) {
                mark_pos_ = tmp_pos;
                break;
              }
            }
          }
        }

        if (is_find) return;
      }
      //   执行到这里意味着没有匹配到
      cur_rec_ptr_ = nullptr;
    } else {
      // 原有的直接做嵌套连接部分
      for (; Lpos < Lsize && !is_find; ++Lpos) {
        auto &lrec_ptr = Lbuffer[Lpos];
        for (; Rpos < Rsize && !is_find; ++Rpos) {
          auto &rrec_ptr = Rbuffer[Rpos];
          // 先拼成新元组后再检查
          cur_rec_ptr_ = std::make_unique<RmRecord>(len_);
          memcpy(cur_rec_ptr_->data, lrec_ptr->data, lrec_ptr->size);
          memcpy(cur_rec_ptr_->data + lrec_ptr->size, rrec_ptr->data, rrec_ptr->size);
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
      }
    }
  }

  // sqb 5.24
  size_t tupleLen() const override { return len_; }
  // sqb 5.24
  bool is_end() const override { return cur_rec_ptr_ == nullptr; }

  //   sqb 5.24
  std::unique_ptr<RmRecord> Next() override { return std::move(cur_rec_ptr_); }

  Rid &rid() override { return _abstract_rid; }

  // sqb 5.24
  std::string getType() override { return "MergeJoinExecutor"; }

  // sqb 5.24
  ColMeta get_col_offset(const TabCol &target) override {
    auto it = col_meta_cache_.find(target);
    if (it != col_meta_cache_.end()) {
      return it->second;
    }
    for (auto &col_meta : cols_) {
      if (col_meta.tab_name == target.tab_name && col_meta.name == target.col_name) {
        col_meta_cache_[target] = col_meta;
        return col_meta;
      }
    }
    throw ColumnNotFoundError(target.col_name);
  }

  // sqb 5.24
  const std::vector<ColMeta> &cols() const override { return cols_; }
};