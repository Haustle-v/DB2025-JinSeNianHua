// alias_map.h
#ifndef ALIAS_MAP_H
#define ALIAS_MAP_H

#include <unordered_map>
#include <string>

// 声明一个全局变量 alias_map，类型是 std::unordered_map<std::string, std::string>
extern std::unordered_map<std::string, std::string> alias_map;  // 通过别名找表名
extern std::unordered_map<std::string, std::string> pam_saila;  // 通过表名找别名

#endif