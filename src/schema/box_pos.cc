#include "schema/box_pos.h"

#include <nlohmann/json.hpp>
#include <optional>
#include <string>

// debug
#include <iostream>
//

#include "schema/box_type.h"
#include "schema/data.h"

namespace janowski::paczki_cpp::schema {

BoxPos::BoxPos(std::string id, std::string box_type_id, double x, double y,
               double z, bool rotated, Data& schema)
    : id_(std::move(id)),
      box_type_id_(std::move(box_type_id)),
      x_(x),
      y_(y),
      z_(z),
      rotated_(rotated),
      schema_(schema) {}

BoxPos::BoxPos(nlohmann::json& json)
    : id_{json["$id"].get<std::string>()},
      box_type_id_{json["Item1"]["$ref"].get<std::string>()},
      x_{json["Item2"]["X"].get<double>()},
      y_{json["Item2"]["Y"].get<double>()},
      z_{json["Item2"]["Z"].get<double>()},
      rotated_{json["Item2"]["Rotated"].get<bool>()} {}

BoxPos::BoxPos(nlohmann::json& json, Data& schema) : BoxPos(json) {
  schema_ = schema;
}

std::optional<std::reference_wrapper<const BoxType>> BoxPos::box_type() const {
  if (!schema_) {
    return std::nullopt;
  }
  return schema_->get().box_types().at(box_type_id_);
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
  std::cout << &schema_ << std::endl;
  const auto box_type = schema_->get().box_types().find(box_type_id_);
  const auto box_types_end = schema_->get().box_types().end();
  std::cout << (box_type == box_types_end ? "YES" : "NO!") << std::endl;
  // size["x"] = box_type.size_x();
  // size["y"] = box_type.size_y();
  // size["z"] = box_type.size_z();
  return data;
}

}  // namespace janowski::paczki_cpp::schema
