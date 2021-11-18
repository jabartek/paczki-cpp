#include "schema/data.h"

#include <nlohmann/json.hpp>
#include <utility>

namespace janowski::paczki_cpp::schema {
Data::Data(nlohmann::json &json) {
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
    BoxPos new_box_pos{box_pos};
    box_postitions_.emplace(new_box_pos.id(), std::move(new_box_pos));
  };

  for (auto &box_type : json["BoxTypes"]) {
    if (!box_type.contains("$id")) {
      continue;
    }
    BoxType new_box_type{box_type};
    box_types_.emplace(new_box_type.id(), std::move(new_box_type));
  };
}
} // namespace janowski::paczki_cpp::schema