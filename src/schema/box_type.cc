#include "schema/box_type.h"

#include <iostream>
#include <nlohmann/json.hpp>
#include <optional>

#include "colors.h"
#include "schema/data.h"
namespace janowski::paczki_cpp::schema {

// BoxType::BoxType(std::string id, std::string sku_id, double size_x, double size_y, double size_z, double weight,
//                  double load_capacity, double max_overhang, double max_overhang_x, double max_overhang_y,
//                  bool fragile_top, bool uneven_bottom, std::vector<Item> items, DataBase* schema) {
//   ref_ = std::move(id);
//   sku_id_ = std::move(sku_id);
//   size_x_ = size_x;
//   size_y_ = size_y;
//   size_z_ = size_z;
//   weight_ = weight;
//   load_capacity_ = load_capacity;
//   max_overhang_ = max_overhang;
//   max_overhang_x_ = max_overhang_x;
//   max_overhang_y_ = max_overhang_y;
//   fragile_top_ = fragile_top;
//   uneven_bottom_ = uneven_bottom;
//   items_ = std::move(items);
//   schema_ = schema;
// }

BoxType::BoxType(nlohmann::json& json, DataBase* schema) {
  ref_ = json["$id"].is_string() ? std::make_optional(json["$id"].get<std::string>()) : std::nullopt;
  id_ = json["Id"].get<std::string>();
  sku_id_ = json["SkuId"].is_string() ? std::make_optional(json["SkuId"].get<std::string>()) : std::nullopt;
  size_x_ = json["SizeX"].get<float>();
  size_y_ = json["SizeY"].get<float>();
  size_z_ = json["SizeZ"].get<float>();
  weight_ = json["Weight"].get<float>();
  load_capacity_ = json["LoadCapacity"].get<float>();
  max_overhang_ = json["MaxOverhang"].get<float>();
  max_overhang_x_ = json["MaxOverhangX"].get<float>();
  max_overhang_y_ = json["MaxOverhangY"].get<float>();
  fragile_top_ = json["FragileTop"].get<bool>();
  uneven_bottom_ = json["UnevenBottom"].get<bool>();
  if (json.contains("ColorR") && json.contains("ColorG") && json.contains("ColorB")) {
    color_r_ = json["ColorR"].get<unsigned char>();
    color_g_ = json["ColorG"].get<unsigned char>();
    color_b_ = json["ColorB"].get<unsigned char>();
  } else {
    const auto color_hash = std::hash<std::string>{}(id_);
    const auto color = colors::kColors.at(color_hash % colors::kColors.size());
    color_r_ = color.r;
    color_g_ = color.g;
    color_b_ = color.b;
  }
  schema_ = schema;
  self_ = json;  // debug

  items_.reserve(json["Num"].get<std::size_t>());
  for (auto& item : json["Items"]) {
    items_.emplace_back(item);
    items_native_ = true;
  }
  if (schema_ && sku_id_ && items_.empty() && schema->skus().contains(*sku_id_)) {
    // rem_std::cout << "Hello SKU: " << *sku_id_ << "\n";  // debug
    const auto& sku = schema->skus().at(*sku_id_);
    const bool rotated = !(size_x_ == sku.size_x() && size_y_ == sku.size_y() && size_z_ == sku.size_z());
    items_.emplace_back(*sku_id_, rotated);
  }
}
nlohmann::json BoxType::json() const {
  nlohmann::json val{};
  if (ref_) val["$id"] = *ref_;
  if (sku_id_) val["SkuId"] = *sku_id_;
  val["Id"] = id_;
  val["SizeX"] = size_x_;
  val["SizeY"] = size_y_;
  val["SizeZ"] = size_z_;
  val["Weight"] = weight_;
  val["LoadCapacity"] = load_capacity_;
  val["MaxOverhang"] = max_overhang_;
  val["MaxOverhangX"] = max_overhang_x_;
  val["MaxOverhangY"] = max_overhang_y_;
  val["FragileTop"] = fragile_top_;
  val["UnevenBottom"] = uneven_bottom_;
  val["ColorR"] = color_r_;
  val["ColorG"] = color_g_;
  val["ColorB"] = color_b_;
  if (items_native_) {
    val["Num"] = items_.size();
    val["Items"] = nlohmann::json(items_);
  } else {
    val["Num"] = items_.size();
    val["Items"] = nlohmann::json(items_);  // todo debug converted_sku
  }
  return val;
}

BoxType::Item::Item(nlohmann::json& json) {
  sku_id = json["Item1"].get<std::string>();
  x = json["Item2"]["X"].get<double>();
  y = json["Item2"]["Y"].get<double>();
  z = json["Item2"]["Z"].get<double>();
  rotated = json["Item2"]["Rotated"].get<bool>();
}

BoxType::Item::Item(std::string sku_id, bool rotated)
    : sku_id{std::move(sku_id)}, x{0.}, y{0.}, z{0.}, rotated{rotated} {}

const Sku* BoxType::sku() const {
  if (schema_ && sku_id_) {
    if (auto it = schema_->skus().find(*sku_id_); it != schema_->skus().end()) {
      return &it->second;
    }
  }
  return nullptr;
}

void to_json(nlohmann::json& j, const BoxType& box_type) { j = box_type.json(); }
void to_json(nlohmann::json& j, const BoxType::Item& item) {
  j = nlohmann::json{{"Item1", item.sku_id},
                     {"Item2", nlohmann::json{
                                   {"X", item.x},
                                   {"Y", item.y},
                                   {"Z", item.z},
                                   {"Rotated", item.rotated},
                               }}};
}

}  // namespace janowski::paczki_cpp::schema
