#pragma once

#include "math/vector3.h"
#include "schema/box_pos.h"
#include "schema/box_type.h"
#include "schema/sku.h"

#include <nlohmann/json.hpp>

#include <string>
#include <unordered_map>

namespace janowski::paczki_cpp::schema {
class Data {
public:
  using BoxPositions = std::unordered_map<std::string, BoxPos>;
  using BoxTypes = std::unordered_map<std::string, BoxType>;
  using Skus = std::unordered_map<std::string, Sku>;

  Data(nlohmann::json &json);

  inline const BoxPositions &box_positions() const { return box_postitions_; }
  inline const BoxTypes &box_types() const { return box_types_; }
  inline const Skus &skus() const { return skus_; }

  inline BoxPositions &box_positions() { return box_postitions_; }
  inline BoxTypes &box_types() { return box_types_; }
  inline Skus &skus() { return skus_; }

private:
  BoxPositions box_postitions_;
  BoxTypes box_types_;
  Skus skus_;
};

using ColorMap = std::unordered_map<std::string, math::Vector3<unsigned char>>;
} // namespace janowski::paczki_cpp::schema