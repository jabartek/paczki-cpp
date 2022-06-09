#pragma once

#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "math/color.h"

namespace janowski::paczki_cpp::schema {

class DataBase;
class Sku;

class BoxType {
 public:
  struct Item {
    Item(nlohmann::json& json);
    Item(std::string sku_id, bool rotated);

    std::string sku_id;
    double x;
    double y;
    double z;
    bool rotated;
  };

  // BoxType(std::string id, std::string sku_id, double size_x, double size_y, double size_z, double weight,
  //         double load_capacity, double max_overhang, double max_overhang_x, double max_overhang_y, bool fragile_top,
  //         bool uneven_bottom, std::vector<Item> items, Data* schema = nullptr);

  BoxType(nlohmann::json& json, DataBase* schema);

  nlohmann::json json() const;

  const Sku* sku() const;

  inline std::optional<std::string> ref() const { return ref_; }

  inline std::optional<std::string> sku_id() const { return sku_id_; }
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
  inline unsigned char color_r() const { return color_r_; }
  inline unsigned char color_g() const { return color_g_; }
  inline unsigned char color_b() const { return color_b_; }
  inline ::Color color() const { return math::makeColor(color_r_, color_g_, color_b_); }
  inline const std::vector<Item>& items() const { return items_; }

 private:
  std::optional<std::string> ref_;
  std::string id_;
  std::optional<std::string> sku_id_;
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
  unsigned char color_r_;
  unsigned char color_g_;
  unsigned char color_b_;

  std::vector<Item> items_;

  bool items_native_{false};  // If items were stored as list in original JSON

  DataBase* schema_;

  nlohmann::json self_;  // DEBUG
};

void to_json(nlohmann::json& j, const BoxType& box_type);
void to_json(nlohmann::json& j, const BoxType::Item& item);

}  // namespace janowski::paczki_cpp::schema
