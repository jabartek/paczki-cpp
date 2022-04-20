#include "schema/box_pos.h"

#include <iostream>  // debug

#include "graphics/box.h"
#include "math/vector3.h"
#include "raylib.h"
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

bool BoxPos::tryMove(const ::Vector3& delta, const std::string& pallet_id) {
  auto new_box_pos = *this;
  new_box_pos.x_ += delta.x;
  new_box_pos.y_ += delta.y;
  new_box_pos.z_ += delta.z;
  auto& pallet = schema_->box_positions(pallet_id);

  auto new_box_bounding_box = new_box_pos.bounding_box();
  if (!new_box_bounding_box) return true;
  for (auto& [id, box] : pallet) {
    if (id == new_box_pos.id()) continue;
    auto box_bounding_box = box.bounding_box();
    if (!box_bounding_box) continue;
    if (graphics::checkCollision(*new_box_bounding_box, *box_bounding_box) ||
        graphics::checkCollision(*box_bounding_box, *new_box_bounding_box)) {
      std::cout << "BB1 min: " << new_box_bounding_box->min.x << ", " << new_box_bounding_box->min.y << ", "
                << new_box_bounding_box->min.z << "\n";
      std::cout << "BB1 max: " << new_box_bounding_box->max.x << ", " << new_box_bounding_box->max.y << ", "
                << new_box_bounding_box->max.z << "\n";
      std::cout << "BB2 min: " << box_bounding_box->min.x << ", " << box_bounding_box->min.y << ", "
                << box_bounding_box->min.z << "\n";
      std::cout << "BB2 max: " << box_bounding_box->max.x << ", " << box_bounding_box->max.y << ", "
                << box_bounding_box->max.z << "\n";
      std::cout << new_box_pos.id_ << " " << id << "\n";
      return false;
    }
  }

  x_ += delta.x;
  y_ += delta.y;
  z_ += delta.z;
  return true;
}

std::optional<BoundingBox> BoxPos::bounding_box() const {
  auto box_type_ptr = box_type();
  if (!box_type_ptr) return std::nullopt;
  using namespace math;

  auto position = graphics::getPosition(*this);
  auto size = graphics::getSize(*this, *box_type_ptr);
  return BoundingBox{position, position + size};
}

}  // namespace janowski::paczki_cpp::schema
