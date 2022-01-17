#pragma once
#include <nlohmann/json.hpp>

#include <unordered_map>
#include <utility>
#include <vector>

namespace janowski::paczki_cpp {
nlohmann::json loadJson(const std::string &json_file_path);
} // namespace janowski::paczki_cpp
