#pragma once

#include "planner.h"
#include <string>
#include <vector>
#include <memory>


const char* compOp2String(CompOp op);
std::string value2String(const Value& val);
std::string sort_dict(std::vector<std::string>& strs);
void find_join_tables(std::vector<std::string>& joined_tables, std::shared_ptr<Plan> plan);
std::string get_pam_saila(const std::string& tab_name);

enum PlanTypeOrder {
    FILTER = 0,
    JOIN = 1,
    PROJECTION = 2,
    SCAN = 3,
    UNKNOWN = 4
};

PlanTypeOrder get_plan_type_order(const std::shared_ptr<Plan>& plan);
std::string get_sort_key(const std::shared_ptr<Plan>& plan);
bool is_left_preferred(const std::shared_ptr<Plan>& left, const std::shared_ptr<Plan>& right);
void explain(std::string& explain_output, std::shared_ptr<Plan> plan, const std::string& offset);
