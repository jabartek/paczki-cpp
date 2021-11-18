#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#include "nlohmann/json.hpp"
#include "schema/box_pos.h"
#include "schema/box_type.h"
#include "schema/sku.h"

int main(int argc, char* argv[]) {
  std::cout << "Hello JSON!" << std::endl;
  if (argc < 2) {
    std::cout << "No JSON path giver!" << std::endl;
    exit(1);
  }
  std::filesystem::path json_path(argv[1]);
  std::ifstream content{json_path};
  nlohmann::json json;
  content >> json;
  for (auto& sku : json["SKUList"]) {
    if (!sku.contains("$id")) {
      continue;
    }
    janowski::paczki_cpp::schema::Sku new_sku{sku};
    std::cout << new_sku.id() << std::endl;
  };

  std::cout << std::endl;

  for (auto& box_pos : json["Pallets"][0]["BoxPos"]) {
    if (!box_pos.contains("$id")) {
      continue;
    }
    janowski::paczki_cpp::schema::BoxPos new_box_pos{box_pos};
    std::cout << new_box_pos.box_type_id() << std::endl;
  };

  std::cout << std::endl;

  for (auto& box_type : json["BoxTypes"]) {
    if (!box_type.contains("$id")) {
      continue;
    }
    janowski::paczki_cpp::schema::BoxType new_box_type{box_type};
    std::cout << new_box_type.id() << '\t' << new_box_type.items().size()
              << std::endl;
  };
}