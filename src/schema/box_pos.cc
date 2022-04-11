#include "schema/box_pos.h"

#include "schema/box_type.h"
#include "schema/data.h"
#include "schema/sku.h"

namespace janowski::paczki_cpp::schema {

BoxPos::BoxPos(std::string id, std::string box_type_id, double x, double y, double z, bool rotated, Data* schema) {
  id_ = std::move(id);
  box_type_id_ = std::move(box_type_id);
  x_ = x;
  y_ = y;
  z_ = z;
  rotated_ = rotated;
  schema_ = schema;
}

BoxPos::BoxPos(nlohmann::json& json) {
  id_ = json["$id"].get<std::string>();
  box_type_id_ = json["Item1"].value("$ref", "default");
  x_ = json["Item2"]["X"].get<double>();
  y_ = json["Item2"]["Y"].get<double>();
  z_ = json["Item2"]["Z"].get<double>();
  rotated_ = json["Item2"]["Rotated"].get<bool>();
}

BoxPos::BoxPos(nlohmann::json& json, Data* schema) : BoxPos(json) { schema_ = schema; }

const BoxType* BoxPos::box_type() const {
  if (schema_) {
    if (auto it = schema_->box_types().find(box_type_id_); it != schema_->box_types().end()) {
      return &it->second;
    }
  }
  return nullptr;
}

const Sku* BoxPos::sku() const {
  if (auto box_type_ptr = box_type(); box_type_ptr) {
    return box_type_ptr->sku();
  }
  return nullptr;
}

nlohmann::json BoxPos::json() const {
  nlohmann::json data;
  data["coordinates"] = {};
  auto& coordinates = data["coordinates"];
  coordinates["x"] = x_;
  coordinates["y"] = y_;
  coordinates["z"] = z_;
  if (!schema_) {
    return data;
  }
  data["size"] = {};
  auto& size = data["size"];
  const auto box_type = schema_->box_types().find(box_type_id_);
  if (box_type != schema_->box_types().end()) {
    size["x"] = box_type->second.size_x();
    size["y"] = box_type->second.size_y();
    size["z"] = box_type->second.size_z();
  }
  return data;
}

}  // namespace janowski::paczki_cpp::schema
