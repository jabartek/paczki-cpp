#include "schema/sku.h"

namespace janowski::paczki_cpp::schema {

Sku::Sku(std::string id, double size_x, double size_y, double size_z,
         double weight, double load_capacity, double max_overhang,
         double max_overhang_x, double max_overhang_y, bool fragile_top,
         bool uneven_bottom)
    : id_{std::move(id)}, size_x_{size_x}, size_y_{size_y}, size_z_{size_z},
      weight_{weight}, load_capacity_{load_capacity},
      max_overhang_{max_overhang}, max_overhang_x_{max_overhang_x},
      max_overhang_y_{max_overhang_y}, fragile_top_{fragile_top},
      uneven_bottom_{uneven_bottom} {}

Sku::Sku(nlohmann::json &json)
    : id_{json["Id"].get<std::string>()}, size_x_{json["SizeX"].get<double>()},
      size_y_{json["SizeY"].get<double>()},
      size_z_{json["SizeZ"].get<double>()},
      weight_{json["Weight"].get<double>()},
      load_capacity_{json["LoadCapacity"].get<double>()},
      max_overhang_{json["MaxOverhang"].get<double>()},
      max_overhang_x_{json["MaxOverhangX"].get<double>()},
      max_overhang_y_{json["MaxOverhangY"].get<double>()},
      fragile_top_{json["FragileTop"].get<bool>()},
      uneven_bottom_{json["UnevenBootom"].get<bool>()} {}

} // namespace janowski::paczki_cpp::schema
