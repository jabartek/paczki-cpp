#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#include "nlohmann/json.hpp"
#include "schema/box_pos.h"
#include "schema/box_type.h"
#include "schema/data.h"
#include "schema/sku.h"

int main(int argc, char* argv[]) {
  
  if (argc < 2) {
    
    exit(1);
  }
  std::filesystem::path json_path(argv[1]);
  std::ifstream content{json_path};
  nlohmann::json json;
  auto start = std::chrono::high_resolution_clock::now();
  content >> json;
  auto end = std::chrono::high_resolution_clock::now();
  
            << std::endl;

  for (auto& sku : json["SKUList"]) {
    if (!sku.contains("$id")) {
      continue;
    }
    janowski::paczki_cpp::schema::Sku new_sku{sku};
    
  };

  

  for (auto& box_pos : json["Pallets"][0]["BoxPos"]) {
    if (!box_pos.contains("$id")) {
      continue;
    }
    janowski::paczki_cpp::schema::BoxPos new_box_pos{box_pos};
    
  };

  

  for (auto& box_type : json["BoxTypes"]) {
    if (!box_type.contains("$id")) {
      continue;
    }
    janowski::paczki_cpp::schema::BoxType new_box_type{box_type};
    
  };

  start = std::chrono::high_resolution_clock::now();
  janowski::paczki_cpp::schema::Data data{json};
  end = std::chrono::high_resolution_clock::now();

  
            << std::endl;

  for (auto& [id, box_pos] : data.box_positions()) {
    
    
  }
}