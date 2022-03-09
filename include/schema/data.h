#pragma once

#include "lib/raylib_clean.h"

#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

#include "schema/box_pos.h"
#include "schema/box_type.h"
#include "schema/sku.h"

namespace janowski::paczki_cpp::schema {
class Data {
 public:
  using BoxPositions = std::unordered_map<std::string, BoxPos>;
  using BoxTypes = std::unordered_map<std::string, BoxType>;
  using Skus = std::unordered_map<std::string, Sku>;
  using ColorMap = std::unordered_map<std::string, Color>;

  Data(nlohmann::json& json);

  inline const BoxPositions& box_positions() const { return box_positions_; }
  inline const BoxTypes& box_types() const { return box_types_; }
  inline const Skus& skus() const { return skus_; }

  inline BoxPositions& box_positions() { return box_positions_; }
  inline BoxTypes& box_types() { return box_types_; }
  inline Skus& skus() { return skus_; }

  inline ColorMap& type_to_color_map() { return typeToColorMap_; }
  inline ColorMap& pos_to_color_map() { return posToColorMap_; }

  Vector3 dimensions() const;

  Data(Data&& o);
  Data& operator=(Data&& rhs);

 private:
  BoxPositions box_positions_;
  BoxTypes box_types_;
  Skus skus_;
  nlohmann::json raw_;
  ColorMap typeToColorMap_;
  ColorMap posToColorMap_;
};

}  // namespace janowski::paczki_cpp::schema