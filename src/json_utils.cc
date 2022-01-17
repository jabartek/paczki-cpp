#include "json_utils.h"

#include "misc.h"

#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>
#include <string>

namespace janowski::paczki_cpp {
nlohmann::json loadJson(const std::string &json_file_path) {
  nlohmann::json data;
  std::ifstream file(json_file_path);
  file >> data;
  return data;
}
} // namespace janowski::paczki_cpp