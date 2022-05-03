#include "schema/data.h"

#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string_view>
#include <utility>

/**/
#include <iostream>
/**/

#include "math/color.h"

namespace janowski::paczki_cpp::schema {

class IncorrectDataException : public std::runtime_error {
 public:
  IncorrectDataException(std::string err = "") : std::runtime_error(err) {}
};

Data::Data(nlohmann::json& json) : raw_(json) {
  for (auto& sku : json["SKUList"]) {
    if (!sku.contains("$id")) {
      continue;
    }
    Sku new_sku{sku};
    skus_.emplace(new_sku.id(), std::move(new_sku));
  };

  for (auto& pallet_data : json["Pallets"]) {
    if (!pallet_data.contains("$id")) continue;
    const auto& id = pallet_ids_.emplace_back(pallet_data["$id"].get<std::string>());
    auto& pallet = pallets_[id];
    auto& order = box_orders_[id];
    for (auto& box_pos : pallet_data["BoxPos"]) {
      if (!box_pos.contains("$id")) continue;
      BoxPos new_box_pos{box_pos, this};
      auto id = new_box_pos.id();
      pallet.emplace(id, std::move(new_box_pos));
      order.emplace_back(id);
      srand(std::hash<std::string_view>{}(id));  // debug
      posToColorMap_.emplace(id, math::makeColor(rand(), rand(), rand()));
    };
    last_boxes_[id] = !order.empty() ? std::next(order.end(), -1) : order.end();
  }
  for (auto& box_type : json["BoxTypes"]) {
    if (!box_type.contains("$id")) {
      continue;
    }
    BoxType new_box_type{box_type};
    if (auto id = new_box_type.id(); id) {
      box_types_.emplace(*id, std::move(new_box_type));
      srand(std::hash<std::string>{}(*id));  // debug
      typeToColorMap_.emplace(*id, math::makeColor(rand(), rand(), rand()));
    }
  };

  if (pallet_ids_.empty()) {
    throw IncorrectDataException("Missing pallet data!");
  }
  std::cout << "Załadowano " << pallet_ids_.size() << " palet!" << std::endl;
}

Data::Data(Data&& o)
    : pallets_(std::move(o.pallets_)),
      box_types_(std::move(o.box_types_)),
      skus_(std::move(o.skus_)),
      raw_(std::move(o.raw_)) {
  for (auto& [id, pallet] : pallets_) {
    for (auto& [id, box_pos] : pallet) {
      box_pos.set_schema(this);
    }
  }
}

Data& Data::operator=(Data&& rhs) {
  pallets_ = std::move(rhs.pallets_);
  box_types_ = std::move(rhs.box_types_);
  skus_ = std::move(rhs.skus_);
  raw_ = std::move(rhs.raw_);
  for (auto& [id, pallet] : pallets_) {
    for (auto& [id, box_pos] : pallet) {
      box_pos.set_schema(this);
    }
  }
  return *this;
}

Vector3 Data::dimensions() const {
  return {raw_["SizeX"].get<float>(), raw_["SizeZ"].get<float>(), raw_["SizeY"].get<float>()};
}

}  // namespace janowski::paczki_cpp::schema