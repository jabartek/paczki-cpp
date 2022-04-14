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
  int c = 0;
  for (auto& box_type : json["BoxTypes"]) {
    c++;
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

  active_pallet_ = pallet_ids_.front();

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

void Data::set_active_pallet(const std::string& id) {
  if (std::find(pallet_ids_.begin(), pallet_ids_.end(), id) == pallet_ids_.end()) {
    throw std::runtime_error("`Data::set_active_pallet` - Invalid pallet id: " + id);
  }
  active_pallet_ = id;
}

void Data::set_active_pallet(std::size_t idx) { set_active_pallet(*std::next(pallet_ids_.begin(), idx)); }

void Data::advancePallet() {
  auto it = std::find(pallet_ids_.begin(), pallet_ids_.end(), active_pallet_);
  std::size_t idx = std::distance(pallet_ids_.begin(), it);
  idx++;
  active_pallet_ = *std::next(pallet_ids_.begin(), idx >= pallet_ids_.size() ? 0 : idx);
}

}  // namespace janowski::paczki_cpp::schema