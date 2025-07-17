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

#include "../defs.h"

// int yyparse();

// typedef struct yy_buffer_state *YY_BUFFER_STATE;

// YY_BUFFER_STATE yy_scan_string(const char *str);

// void yy_delete_buffer(YY_BUFFER_STATE buffer);

// 将词法分析改为多线程 sqb 7.9
typedef struct yy_buffer_state *YY_BUFFER_STATE;  // 词法分析器的缓冲池
typedef void *yyscan_t;                           // 词法分析器状态句柄

// 重入式解析函数声明 sqb
int yyparse(void *scanner);  // 需要与Yacc的%parse-param匹配

// 扫描给定字符串，创建一个词法分析器的缓冲区
YY_BUFFER_STATE yy_scan_string(const char *str, yyscan_t scanner);

// 释放给定词法分析器的缓冲区
void yy_delete_buffer(YY_BUFFER_STATE buffer, yyscan_t scanner);

// 初始化线程独立的词法分析器
void yylex_init(yyscan_t *scanner);

// 释放给定词法分析器的实例
void yylex_destroy(yyscan_t scanner);