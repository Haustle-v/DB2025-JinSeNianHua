/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "transaction/watermark.h"

// sqb 6.16
auto Watermark::AddTxn(timestamp_t read_ts) -> void {
  if (read_ts < commit_ts_) {
    throw InternalError("read ts < commit ts");
  }
  if (read_ts < watermark_) {
    watermark_ = read_ts;
  }
  current_reads_.insert(read_ts);
}

// sqb 6.16
auto Watermark::RemoveTxn(timestamp_t read_ts) -> void {
  auto iter = current_reads_.find(read_ts);
  if (iter != current_reads_.end()) {
    current_reads_.erase(iter);
  }
  if (current_reads_.empty()) {
    watermark_ = commit_ts_;
  } else {
    watermark_ = *current_reads_.begin();
  }
}