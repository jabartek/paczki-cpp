#include "schema/box_pos.h"

#include <string>

#include "nlohmann/json.hpp"

namespace janowski::paczki_cpp::schema {

BoxPos::BoxPos(std::string box_type_id, double x, double y, double z,
               bool rotated)
    : box_type_id_(std::move(box_type_id)),
      x_(x),
      y_(y),
      z_(z),
      rotated_(rotated) {}

BoxPos::BoxPos(nlohmann::json& json)
    : box_type_id_{json["Item1"]["$ref"].get<std::string>()},
      x_{json["Item2"]["X"].get<double>()},
      y_{json["Item2"]["Y"].get<double>()},
      z_{json["Item2"]["Z"].get<double>()},
      rotated_{json["Item2"]["Rotated"].get<bool>()} {}

}  // namespace janowski::paczki_cpp::schema
