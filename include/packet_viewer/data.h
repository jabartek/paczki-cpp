#pragma once

#include <iostream>
#include <optional>

#include "bind/stores.h"
#include "nlohmann/json.hpp"
#include "schema/box_type.h"
#include "schema/data.h"

namespace janowski::paczki_cpp::packet_viewer {
class Data : public schema::DataBase {
 public:
  using Skus = schema::DataBase::Skus;
  using BoxTypes = schema::DataBase::BoxTypes;

  inline Data() {}

  inline Data(nlohmann::json& json) { setSkus(json); }

  inline void setSkus(nlohmann::json& json) {
    skus_.clear();
    for (auto& sku : json) {
      if (!sku.contains("$id")) {
        continue;
      }
      schema::Sku new_sku{sku};
      skus_.emplace(new_sku.id(), std::move(new_sku));
    };
  }
  inline void setBoxTypeList(nlohmann::json& json) {
    box_type_store_.clear();
    for (auto& box_type : json) {
      if (!box_type.contains("$id")) {
        continue;
      }
      // rem_std::cout << box_type.dump() << "\n"; //todo debug
      schema::BoxType new_box_type{box_type, this};
      if (!new_box_type.ref()) continue;
      box_type_store_.emplace(*new_box_type.ref(), std::move(new_box_type));
    };
  }

  inline const Skus& skus() const override { return skus_; }
  inline const BoxTypes& box_types() const override { return box_type_store_; }

 private:
  Skus skus_;
  BoxTypes box_type_store_;
};
}  // namespace janowski::paczki_cpp::packet_viewer
