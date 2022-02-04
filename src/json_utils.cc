#include "json_utils.h"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

#include "misc.h"

namespace janowski::paczki_cpp {
nlohmann::json loadJson(const std::string& json_file_path) {
  nlohmann::json data;
  std::ifstream file(json_file_path);
  file >> data;
  return data;
}
}  // namespace janowski::paczki_cpp