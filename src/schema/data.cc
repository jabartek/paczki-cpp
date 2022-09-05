#include "schema/data.h"

#include <algorithm>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string_view>
#include <utility>

/**/
#include <iostream>
/**/

#include "graphics/box.h"
#include "math/color.h"
#include "math/vector3.h"
#include "schema/box_pos.h"

using namespace janowski::paczki_cpp::math;

namespace janowski::paczki_cpp::schema {

class IncorrectDataException : public std::runtime_error {
 public:
  IncorrectDataException(std::string err = "") : std::runtime_error(err) {}
};

Data::Data(nlohmann::json& json) {
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
    };
    last_boxes_[id] = !order.empty() ? std::next(order.end(), -1) : order.end();
  }
  for (auto& box_type : json["BoxTypes"]) {
    if (!box_type.contains("$id")) {
      continue;
    }
    BoxType new_box_type{box_type, this};
    if (auto ref = new_box_type.ref(); ref) {
      box_types_.emplace(*ref, std::move(new_box_type));
    }
  };

  dimensions_ = {json["SizeX"].get<float>(), json["SizeZ"].get<float>(), json["SizeY"].get<float>()};

  if (pallet_ids_.empty()) {
    throw IncorrectDataException("Missing pallet data!");
  }
  
}

Data::Data(Data&& o) : pallets_(std::move(o.pallets_)), box_types_(std::move(o.box_types_)), skus_(std::move(o.skus_)) {
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
  for (auto& [pallet_id, pallet] : pallets_) {
    for (auto& [box_pos_id, box_pos] : pallet) {
      box_pos.set_schema(this);
    }
  }
  return *this;
}
::Vector3 Data::palletEnd(const std::string& pallet_id) {
  auto& pallet = box_positions(pallet_id);
  ::Vector3 max{0.f, 0.f, 0.f};
  for (const auto& [id, pos] : pallet) {
    const auto box_end = graphics::getPosition(pos) + graphics::getSize(pos, *pos.box_type());
    if (const auto end_x = box_end.x; end_x > max.x) {
      max.x = end_x;
    }
    if (const auto end_y = box_end.x; end_y > max.y) {
      max.y = end_y;
    }
    if (const auto end_z = box_end.z; end_z > max.z) {
      max.z = end_z;
    }
  }
  return max;
}

void Data::takeBoxOff(const std::string& pallet_id, const std::string& box_pos_id) {
  auto& pallet = box_positions(pallet_id);
  auto box_pos = pallet.at(box_pos_id);
  pallet.erase(box_pos_id);
  box_orders_[pallet_id].erase(std::find(box_orders_[pallet_id].begin(), box_orders_[pallet_id].end(), box_pos_id));
  box_pos_clipboard_.emplace(std::make_pair(box_pos_id, std::move(box_pos)));
}

void Data::putBoxOn(const std::string& pallet_id, const std::string& box_pos_id) {
  auto& pallet = box_positions(pallet_id);
  auto box_pos = box_pos_clipboard_.at(box_pos_id);
  box_pos_clipboard_.erase(box_pos_id);
  const auto pallet_end = palletEnd(pallet_id);
  box_pos.set_z(pallet_end.z);
  pallet.emplace(std::make_pair(box_pos_id, std::move(box_pos)));
  box_orders_[pallet_id].push_back(box_pos_id);
}

// void Data::setClipboardBoxY(const std::string& box_pos_id, float y){
//     auto& box_pos = box_pos_clipboard_.at(box_pos_id);
//     box_pos.
// }

nlohmann::json Data::dump() {
  
  nlohmann::json j{};
  j["SKUList"] = {};
  for (const auto& [id, sku] : skus_) {
    j["SKUList"][id] = sku.json();
  }
  j["BoxTypes"] = nlohmann::json::array();
  for (const auto& [id, box_type] : box_types_) {
    j["BoxTypes"].emplace_back(box_type);
  }
  j["Pallets"] = nlohmann::json::array();
  for (const auto& [pallet_id, box_positions] : pallets_) {
    nlohmann::json pallet_json{};
    pallet_json["$id"] = pallet_id;
    pallet_json["BoxPos"] = nlohmann::json::array();
    for (const auto& position : box_positions) {
      nlohmann::json position_json = position;
      position_json = position_json[1];
      std::cout << position_json.dump(2) << std::endl;
      pallet_json["BoxPos"].emplace_back(std::move(position_json));
    }
    j["Pallets"].emplace_back(std::move(pallet_json));
  }
  j["SizeX"] = dimensions_.x;
  j["SizeY"] = dimensions_.y;
  j["SizeZ"] = dimensions_.z;
  return j;
}

Vector3 Data::dimensions() const { return dimensions_; }

}  // namespace janowski::paczki_cpp::schema