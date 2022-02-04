#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace janowski::paczki_cpp::schema {

class Data;
class Sku;

class BoxType {
 public:
  class Item {
   public:
    Item(nlohmann::json& json);
    std::string sku_id;
    double x;
    double y;
    double z;
    bool rotated;
  };

  BoxType(std::string id, std::string sku_id, double size_x, double size_y, double size_z, double weight,
          double load_capacity, double max_overhang, double max_overhang_x, double max_overhang_y, bool fragile_top,
          bool uneven_bottom, std::vector<Item> items, Data* schema = nullptr);

  BoxType(nlohmann::json& json, Data* schema = nullptr);

  inline nlohmann::json json() const { return self_; } // debug

  const Sku* sku() const;

  inline const std::string& id() const { return id_; }
  inline const std::string& sku_id() const { return sku_id_; }
  inline double size_x() const { return size_x_; }
  inline double size_y() const { return size_y_; }
  inline double size_z() const { return size_z_; }
  inline double weight() const { return weight_; }
  inline double load_capacity() const { return load_capacity_; }
  inline double max_overhang() const { return max_overhang_; }
  inline double max_overhang_x() const { return max_overhang_x_; }
  inline double max_overhang_y() const { return max_overhang_y_; }
  inline bool fragile_top() const { return fragile_top_; }
  inline bool uneven_bottom() const { return uneven_bottom_; }
  inline const std::vector<Item>& items() const { return items_; }

 private:
  std::string id_;
  std::string sku_id_;
  double size_x_;
  double size_y_;
  double size_z_;
  double weight_;
  double load_capacity_;
  double max_overhang_;
  double max_overhang_x_;
  double max_overhang_y_;
  bool fragile_top_;
  bool uneven_bottom_;

  std::vector<Item> items_;

  Data* schema_;

  nlohmann::json self_;  // DEBUG
};
}  // namespace janowski::paczki_cpp::schema
