#include "schema/box_type.h"

#include "schema/data.h"

#include <nlohmann/json.hpp>

namespace janowski::paczki_cpp::schema {

BoxType::BoxType(std::string id, std::string sku_id, double size_x,
                 double size_y, double size_z, double weight,
                 double load_capacity, double max_overhang,
                 double max_overhang_x, double max_overhang_y, bool fragile_top,
                 bool uneven_bottom, std::vector<Item> items, Data *schema)
    : id_{std::move(id)}, sku_id_{std::move(sku_id)}, size_x_{size_x},
      size_y_{size_y}, size_z_{size_z}, weight_{weight},
      load_capacity_{load_capacity}, max_overhang_{max_overhang},
      max_overhang_x_{max_overhang_x}, max_overhang_y_{max_overhang_y},
      fragile_top_{fragile_top},
      uneven_bottom_{uneven_bottom}, items_{std::move(items)}, schema_{schema} {
}

BoxType::BoxType(nlohmann::json &json, Data *schema)
    : id_{json["$id"].get<std::string>()},
      sku_id_{json["SkuId"].get<std::string>()},
      size_x_{json["SizeX"].get<float>()}, size_y_{json["SizeY"].get<float>()},
      size_z_{json["SizeZ"].get<float>()}, weight_{json["Weight"].get<float>()},
      load_capacity_{json["LoadCapacity"].get<float>()},
      max_overhang_{json["MaxOverhang"].get<float>()},
      max_overhang_x_{json["MaxOverhangX"].get<float>()},
      max_overhang_y_{json["MaxOverhangY"].get<float>()},
      fragile_top_{json["FragileTop"].get<bool>()},
      uneven_bottom_{json["UnevenBootom"].get<bool>()}, schema_{schema} {
  items_.reserve(json["Num"].get<std::size_t>());
  for (auto &item : json["Items"]) {
    items_.emplace_back(item);
  }
}

BoxType::Item::Item(nlohmann::json &json)
    : sku_id{json["Item1"].get<std::string>()},
      x{json["Item2"]["X"].get<double>()}, y{json["Item2"]["Y"].get<double>()},
      z{json["Item2"]["Z"].get<double>()},
      rotated{json["Item2"]["Rotated"].get<bool>()} {}

const Sku *BoxType::sku() const {
  if (schema_) {
    if (auto it = schema_->skus().find(sku_id_); it != schema_->skus().end()) {
      return &it->second;
    }
  }
  return nullptr;
}

} // namespace janowski::paczki_cpp::schema
