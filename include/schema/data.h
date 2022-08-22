#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <nlohmann/json.hpp>
#include <string>
#include <string_view>
#include <unordered_map>

#include "bind/stores.h"
#include "lib/raylib_clean.h"
#include "schema/box_pos.h"
#include "schema/box_type.h"
#include "schema/sku.h"

namespace janowski::paczki_cpp::schema {
class DataBase {
 public:
  using Skus = std::unordered_map<std::string, Sku>;
  using BoxTypes = std::unordered_map<std::string, BoxType>;
  virtual const Skus& skus() const = 0;
  virtual const BoxTypes& box_types() const = 0;
  virtual ~DataBase() = default;
};

class Data : public DataBase {
 public:
  using BoxPositions = std::unordered_map<std::string, BoxPos>;
  using BoxOrder = std::vector<std::string>;
  using Skus = DataBase::Skus;
  using BoxTypes = DataBase::BoxTypes;
  using ColorMap = std::unordered_map<std::string, Color>;
  using Pallets = std::list<std::string>;

  Data(nlohmann::json& json);

  inline BoxPositions& box_positions(const std::string& pallet) { return pallets_.at(pallet); }
  inline const BoxPositions& box_positions(const std::string& pallet) const { return pallets_.at(pallet); }

  inline const BoxOrder& box_order(const std::string& pallet) const { return box_orders_.at(pallet); }

  inline BoxTypes& box_types() { return box_types_; }
  inline const BoxTypes& box_types() const override { return box_types_; }

  inline Skus& skus() { return skus_; }
  inline const Skus& skus() const override { return skus_; }

  inline const Pallets& pallets() const { return pallet_ids_; }

  ::Vector3 palletEnd(const std::string& pallet_id);
  void takeBoxOff(const std::string& pallet_id, const std::string& box_pos_id);
  void putBoxOn(const std::string& pallet_id, const std::string& box_pos_id);
  void setClipboardBoxY(const std::string& box_pos_id, float y);
  inline const BoxPositions box_pos_clipboard() const { return box_pos_clipboard_; }

  nlohmann::json dump();

  Vector3 dimensions() const;

  Data(Data&& o);
  Data& operator=(Data&& rhs);

 private:
  Pallets pallet_ids_;
  std::map<std::string, BoxPositions> pallets_;
  BoxPositions box_pos_clipboard_;
  std::map<std::string, BoxOrder> box_orders_;
  std::map<std::string, BoxOrder::iterator> last_boxes_;

  BoxTypes box_types_;
  Skus skus_;

  Vector3 dimensions_;
};  // namespace janowski::paczki_cpp::schema

}  // namespace janowski::paczki_cpp::schema