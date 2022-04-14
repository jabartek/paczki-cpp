#pragma once

#include <list>
#include <nlohmann/json.hpp>
#include <string>
#include <string_view>
#include <unordered_map>

#include "lib/raylib_clean.h"
#include "schema/box_pos.h"
#include "schema/box_type.h"
#include "schema/sku.h"

namespace janowski::paczki_cpp::schema {

constexpr auto kDefaultPalletName = "0";
class Data {
 public:
  using BoxPositions = std::unordered_map<std::string, BoxPos>;
  using BoxOrder = std::list<std::string>;
  using BoxTypes = std::unordered_map<std::string, BoxType>;
  using Skus = std::unordered_map<std::string, Sku>;
  using ColorMap = std::unordered_map<std::string, Color>;
  using Pallets = std::list<std::string>;

  Data(nlohmann::json& json);

  inline const BoxPositions& box_positions() const { return box_positions(active_pallet_); }
  inline const BoxPositions& box_positions(const std::string& pallet) const { return pallets_.at(pallet); }
  inline const BoxTypes& box_types() const { return box_types_; }
  inline const Skus& skus() const { return skus_; }

  inline BoxPositions& box_positions() { return box_positions(active_pallet_); }
  inline BoxPositions& box_positions(const std::string& pallet) { return pallets_.at(pallet); }
  inline BoxTypes& box_types() { return box_types_; }
  inline Skus& skus() { return skus_; }

  inline ColorMap& type_to_color_map() { return typeToColorMap_; }
  inline ColorMap& pos_to_color_map() { return posToColorMap_; }

  inline const Pallets& pallets() const { return pallet_ids_; }

  void set_active_pallet(const std::string& id);
  void set_active_pallet(std::size_t idx);

  void advancePallet();

  Vector3 dimensions() const;

  Data(Data&& o);
  Data& operator=(Data&& rhs);

 private:
  Pallets pallet_ids_;
  std::map<std::string, BoxPositions> pallets_;
  std::map<std::string, BoxOrder> box_orders_;
  std::map<std::string, BoxOrder::iterator> last_boxes_;

  BoxTypes box_types_;
  Skus skus_;
  nlohmann::json raw_;
  ColorMap typeToColorMap_;
  ColorMap posToColorMap_;

  std::string active_pallet_;
};

}  // namespace janowski::paczki_cpp::schema