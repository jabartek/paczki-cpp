#pragma once
#include "box/definition.h"
#include "box/instance.h"

#include <nlohmann/json.hpp>

#include <unordered_map>
#include <utility>
#include <vector>

namespace janowski::paczki_cpp {
nlohmann::json loadJson(const std::string &json_file_path);
std::unordered_map<long long, box::Definition>
getDefinitions(const nlohmann::json &data);
std::vector<std::pair<long long, box::Instance>>
getInstances(const nlohmann::json &data);
} // namespace janowski::paczki_cpp
