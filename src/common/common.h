/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include <cassert>
#include <cstring>
#include <memory>
#include <string>
#include <vector>
#include "defs.h"
#include "parser/ast.h"
#include "record/rm_defs.h"

struct TabCol {
  std::string tab_name;
  std::string col_name;

  std::string alias;

  ast::AggFuncType aggFuncType;

  friend bool operator<(const TabCol &x, const TabCol &y) {
    return std::make_pair(x.tab_name, x.col_name) < std::make_pair(y.tab_name, y.col_name);
  }
};

// 为 TabCol 提供相等性比较运算符
inline bool operator==(const TabCol& lhs, const TabCol& rhs) {
    return lhs.tab_name == rhs.tab_name &&
           lhs.col_name == rhs.col_name &&
           lhs.alias == rhs.alias &&
           lhs.aggFuncType == rhs.aggFuncType;
}

// 为 TabCol 提供哈希函数
namespace std {
    template<>
    struct hash<TabCol> {
        size_t operator()(const TabCol& col) const noexcept {
            const size_t h1 = std::hash<std::string>{}(col.tab_name);
            const size_t h2 = std::hash<std::string>{}(col.col_name);
            const size_t h3 = std::hash<std::string>{}(col.alias);
            const size_t h4 = std::hash<int>{}(static_cast<int>(col.aggFuncType));
            size_t seed = 0;
            seed ^= h1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= h3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= h4 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        }
    };
}

struct Value {
  ColType type;  // type of value
  union {
    int int_val;      // int value
    float float_val;  // float value
  };
  std::string str_val;  // string value

  std::shared_ptr<RmRecord> raw;  // raw record buffer

  void set_int(int int_val_) {
    type = TYPE_INT;
    int_val = int_val_;
  }

  void set_float(float float_val_) {
    type = TYPE_FLOAT;
    float_val = float_val_;
  }

  void set_str(std::string str_val_) {
    type = TYPE_STRING;
    str_val = std::move(str_val_);
  }

  void init_raw(int len) {
    assert(raw == nullptr);
    raw = std::make_shared<RmRecord>(len);
    if (type == TYPE_INT) {
      assert(len == sizeof(int));
      *(int *)(raw->data) = int_val;
    } else if (type == TYPE_FLOAT) {
      assert(len == sizeof(float));
      *(float *)(raw->data) = float_val;
    } else if (type == TYPE_STRING) {
      if (len < (int)str_val.size()) {
        throw StringOverflowError();
      }
      memset(raw->data, 0, len);
      memcpy(raw->data, str_val.c_str(), str_val.size());
    }
  }

  // sqb 6.18 添加等号与不等号
  friend bool operator==(const Value &a, const Value &b) { return a.type == b.type && *(a.raw) == *(b.raw); }

  friend bool operator!=(const Value &a, const Value &b) { return !(a == b); }
};

enum CompOp { OP_EQ, OP_NE, OP_LT, OP_GT, OP_LE, OP_GE };

struct Condition {
  TabCol lhs_col;   // left-hand side column
  CompOp op;        // comparison operator
  bool is_rhs_val;  // true if right-hand side is a value (not a column)
  TabCol rhs_col;   // right-hand side column
  Value rhs_val;    // right-hand side value
};

struct SetClause {
  TabCol lhs;
  Value rhs;
  bool is_expr_{false};  // sqb 增加update set col=col+val支持 6.16
};

struct OrderBys {
  std::vector<TabCol> cols;
  std::vector<bool> is_asc;
  int limit;
};