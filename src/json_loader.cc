#include "json_loader.h"

#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>

namespace janowski::paczki_cpp {
nlohmann::json jsonFromFile(const std::string &json_file_path) {
  nlohmann::json data;
  std::ifstream file(json_file_path);
  file >> data;
  return data;
}
} // namespace janowski::paczki_cpp