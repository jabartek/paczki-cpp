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

std::unordered_map<long long, box::Definition>
getDefinitions(const nlohmann::json &data) {
  std::unordered_map<long long, box::Definition> definitions;
  for (const auto &box_def : data["BoxTypes"]) {
    auto box_id = std::stoll(box_def["$id"].get<std::string>());
    // The following is due to JSON parameter ordering being off
    Vector3 size{
        box_def["SizeX"].get<float>(),
        box_def["SizeZ"].get<float>(),
        box_def["SizeY"].get<float>(),
    };
    box::Definition definition(std::move(size), misc::generateColor());
    definitions.insert(std::make_pair(box_id, definition));
  }
  return definitions;
}
std::vector<std::pair<long long, box::Instance>>
getInstances(const nlohmann::json &data) {
  std::vector<std::pair<long long, box::Instance>> instances;
  for (const auto &instance_def : data["Pallets"][0]["BoxPos"]) {
    auto reference =
        std::stoll(instance_def["Item1"]["$ref"].get<std::string>());
    const auto &position_data = instance_def["Item2"];

    // The following is due to JSON parameter ordering being off
    Vector3 position{position_data["X"].get<float>(),
                     position_data["Z"].get<float>(),
                     position_data["Y"].get<float>()};
    bool rotated = position_data["Rotated"].get<bool>();
    box::Instance instance(nullptr, std::move(position), rotated);
    instances.emplace_back(std::make_pair(reference, instance));
  }
  return instances;
}
} // namespace janowski::paczki_cpp