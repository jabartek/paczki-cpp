#include "schema/sku.h"

#include <iostream>
#include <nlohmann/json.hpp>

#include "colors.h"

namespace janowski::paczki_cpp::schema {
Sku::Sku(std::string id, std::string ref, double size_x, double size_y, double size_z, double weight,
         double load_capacity, double max_overhang, double max_overhang_x, double max_overhang_y, bool fragile_top,
         bool uneven_bottom, unsigned char color_r, unsigned char color_g, unsigned char color_b) {
  id_ = std::move(id);
  ref_ = std::move(ref);
  size_x_ = size_x;
  size_y_ = size_y;
  size_z_ = size_z;
  weight_ = weight;
  load_capacity_ = load_capacity;
  max_overhang_ = max_overhang;
  max_overhang_x_ = max_overhang_x;
  max_overhang_y_ = max_overhang_y;
  fragile_top_ = fragile_top;
  uneven_bottom_ = uneven_bottom;
  color_r_ = color_r;
  color_g_ = color_g;
  color_b_ = color_b;
}

Sku::Sku(nlohmann::json& json) {
  id_ = json["Id"].get<std::string>();
  ref_ = json["$id"].get<std::string>();
  size_x_ = json["SizeX"].get<double>();
  size_y_ = json["SizeY"].get<double>();
  size_z_ = json["SizeZ"].get<double>();
  weight_ = json["Weight"].get<double>();
  load_capacity_ = json["LoadCapacity"].get<double>();
  max_overhang_ = json["MaxOverhang"].get<double>();
  max_overhang_x_ = json["MaxOverhangX"].get<double>();
  max_overhang_y_ = json["MaxOverhangY"].get<double>();
  fragile_top_ = json["FragileTop"].get<bool>();
  uneven_bottom_ = json["UnevenBottom"].get<bool>();
  if (json.contains("ColorR") && json.contains("ColorG") && json.contains("ColorB")) {
    color_r_ = json["ColorR"].get<unsigned char>();
    color_g_ = json["ColorG"].get<unsigned char>();
    color_b_ = json["ColorB"].get<unsigned char>();
  } else {
    const auto color_hash = std::hash<std::string>{}(ref_);
    const auto color = colors::kColors.at(color_hash % colors::kColors.size());
    color_r_ = color.r;
    color_g_ = color.g;
    color_b_ = color.b;
  }
}

nlohmann::json Sku::json() const {
  nlohmann::json j;
  j["Id"] = id_;
  j["$id"] = ref_;
  j["SizeX"] = size_x_;
  j["SizeY"] = size_y_;
  j["SizeZ"] = size_z_;
  j["Weight"] = weight_;
  j["LoadCapacity"] = load_capacity_;
  j["MaxOverhang"] = max_overhang_;
  j["MaxOverhangX"] = max_overhang_x_;
  j["MaxOverhangY"] = max_overhang_y_;
  j["FragileTop"] = fragile_top_;
  j["UnevenBottom"] = uneven_bottom_;
  j["ColorR"] = color_r_;
  j["ColorG"] = color_g_;
  j["ColorB"] = color_b_;
  return j;
}

}  // namespace janowski::paczki_cpp::schema
