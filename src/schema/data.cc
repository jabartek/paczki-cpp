#include "schema/data.h"

#include <nlohmann/json.hpp>
#include <stdexcept>
#include <utility>

/**/
#include <iostream>
/**/

#include "math/color.h"

namespace janowski::paczki_cpp::schema {
Data::Data(nlohmann::json& json) : raw_(json) {
  for (auto& sku : json["SKUList"]) {
    if (!sku.contains("$id")) {
      continue;
    }
    Sku new_sku{sku};
    skus_.emplace(new_sku.id(), std::move(new_sku));
  };
  pallet_ids_ = {kDefaultPalletName};
  pallets_[pallet_ids_[0]];
  box_orders_[pallet_ids_[0]];

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
      srand(std::stoi(id));  // debug
      posToColorMap_.emplace(id, math::makeColor(rand(), rand(), rand()));
    };
  }

  for (auto& box_type : json["BoxTypes"]) {
    if (!box_type.contains("$id")) {
      continue;
    }
    BoxType new_box_type{box_type};
    auto id = new_box_type.id();
    box_types_.emplace(id, std::move(new_box_type));
    srand(std::stoi(id));  // debug
    typeToColorMap_.emplace(id, math::makeColor(rand(), rand(), rand()));
  };

  active_pallet_ = pallet_ids_[pallet_ids_.size() > 1 ? 1 : 0];
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

void Data::set_active_pallet(const std::string& id) {
  if (std::find(pallet_ids_.begin(), pallet_ids_.end(), id) == pallet_ids_.end()) {
    throw std::runtime_error("`Data::set_active_pallet` - Invalid pallet id: " + id);
  }
  active_pallet_ = id;
}

void Data::set_active_pallet(std::size_t idx) { set_active_pallet(pallet_ids_.at(idx)); }

}  // namespace janowski::paczki_cpp::schema