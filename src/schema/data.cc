#include "schema/data.h"

#include <nlohmann/json.hpp>

#include <utility>

namespace janowski::paczki_cpp::schema {
Data::Data(nlohmann::json &json) : raw_(json) {
  for (auto &sku : json["SKUList"]) {
    if (!sku.contains("$id")) {
      continue;
    }
    Sku new_sku{sku};
    skus_.emplace(new_sku.id(), std::move(new_sku));
  };

  for (auto &box_pos : json["Pallets"][0]["BoxPos"]) {
    if (!box_pos.contains("$id")) {
      continue;
    }
    BoxPos new_box_pos{box_pos, this};
    box_positions_.emplace(new_box_pos.id(), std::move(new_box_pos));
  };

  for (auto &box_type : json["BoxTypes"]) {
    if (!box_type.contains("$id")) {
      continue;
    }
    BoxType new_box_type{box_type};
    box_types_.emplace(new_box_type.id(), std::move(new_box_type));
  };
}

Data::Data(Data &&o)
    : box_positions_(std::move(o.box_positions_)),
      box_types_(std::move(o.box_types_)), skus_(std::move(o.skus_)),
      raw_(std::move(o.raw_)) {
  for (auto &[id, box_pos] : box_positions_) {
    box_pos.set_schema(this);
  }
}

Data &Data::operator=(Data &&rhs) {
  box_positions_ = std::move(rhs.box_positions_);
  box_types_ = std::move(rhs.box_types_);
  skus_ = std::move(rhs.skus_);
  raw_ = std::move(rhs.raw_);
  for (auto &[id, box_pos] : box_positions_) {
    box_pos.set_schema(this);
  }
  return *this;
}

Vector3 Data::dimensions() const {
  return {raw_["SizeX"].get<float>(), raw_["SizeZ"].get<float>(),
          raw_["SizeY"].get<float>()};
}

} // namespace janowski::paczki_cpp::schema