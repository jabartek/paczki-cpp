#include "schema/box_pos.h"

#include <cmath>
#include <iostream>  // debug
#include <utility>

#include "colors.h"
#include "graphics/box.h"
#include "math/vector3.h"
#include "raylib.h"
#include "schema/box_type.h"
#include "schema/data.h"
#include "schema/sku.h"

using namespace janowski::paczki_cpp::graphics;
using namespace janowski::paczki_cpp::math;

namespace janowski::paczki_cpp::schema {

BoxPos::BoxPos(std::string id, std::string box_type_id, double x, double y, double z, bool rotated,
               unsigned char color_r, unsigned char color_g, unsigned char color_b, Data* schema) {
  ref_ = std::move(id);
  box_type_id_ = std::move(box_type_id);
  x_ = x;
  y_ = y;
  z_ = z;
  rotated_ = rotated;
  color_r_ = color_r;
  color_g_ = color_g;
  color_b_ = color_b;
  schema_ = schema;
}

BoxPos::BoxPos(nlohmann::json& json, Data* schema) : schema_{schema} {
  ref_ = json["$id"].get<std::string>();
  if (json["Item1"].contains("$ref")) {
    box_type_id_ = json["Item1"]["$ref"].get<std::string>();
  } else {
    BoxType box_type{json["Item1"], schema_};
    schema_->box_types().emplace(*box_type.ref(), box_type);
    box_type_id_ = json["Item1"]["$id"].get<std::string>();
  }
  x_ = json["Item2"]["X"].get<double>();
  y_ = json["Item2"]["Y"].get<double>();
  z_ = json["Item2"]["Z"].get<double>();
  rotated_ = json["Item2"]["Rotated"].get<bool>();
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

bool BoxPos::tryMove(::Vector3 delta, const std::string& pallet_id, std::optional<::Vector3>& last_valid_pos) {
  auto fun = [&]() {
    auto new_box_pos = *this;
    new_box_pos.x_ += delta.x;
    new_box_pos.y_ += delta.y;
    new_box_pos.z_ += delta.z;
    const Axis move_axis = delta.x != 0.f ? Axis::X : delta.y != 0.f ? Axis::Y : Axis::Z;
    auto& pallet = schema_->box_positions(pallet_id);

    auto new_box_bounding_box = new_box_pos.bounding_box();
    if (!new_box_bounding_box) return true;
    auto move = std::make_pair(0.f, 0.f);
    for (auto& [id, box] : pallet) {
      if (id == new_box_pos.id()) continue;
      auto box_bounding_box = box.bounding_box();
      if (!box_bounding_box) continue;
      if (auto needed_move = graphics::checkCollision(*box_bounding_box, *new_box_bounding_box, move_axis);
          needed_move != std::make_pair(0.f, 0.f)) {
        if (needed_move.first > needed_move.second) std::swap(needed_move.first, needed_move.second);
        if (std::fabs(needed_move.first) > std::fabs(move.first)) move.first = needed_move.first;
        if (std::fabs(needed_move.second) > std::fabs(move.second)) move.second = needed_move.second;
      }
    }

    constexpr auto sgn = [](const auto& v) { return v > 0; };

    float applied_move = 0.f;

    switch (move_axis) {
      case Axis::X:
        applied_move = sgn(delta.x) == sgn(move.first) ? move.second : move.first;
        if (std::fabs(applied_move) > std::fabs(delta.x)) return false;
        delta.x += applied_move;
        break;
      case Axis::Y:
        applied_move = sgn(delta.y) == sgn(move.first) ? move.second : move.first;
        if (std::fabs(applied_move) > std::fabs(delta.y)) return false;
        delta.y += applied_move;
        break;
      case Axis::Z:
        applied_move = sgn(delta.z) == sgn(move.first) ? move.second : move.first;
        if (std::fabs(applied_move) > std::fabs(delta.z)) return false;
        delta.z += applied_move;
        break;
      default:
        break;
    }

    x_ += delta.x;
    y_ += delta.y;
    z_ += delta.z;
    return true;
  };
  std::swap(delta.y, delta.z);
  if (fun() && last_valid_pos) {
    *last_valid_pos = *last_valid_pos + delta * kSizeMultiplier;
  }
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
