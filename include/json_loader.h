#pragma once

#include <nlohmann/json.hpp>

namespace janowski::paczki_cpp {
nlohmann::json jsonFromFile(const std::string &json_file_path);
} // namespace janowski::paczki_cpp
