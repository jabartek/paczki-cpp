#pragma once

#include <nlohmann/json.hpp>
#include <string>

#include "lib/raylib_clean.h"
#include "math/color.h"

namespace janowski::paczki_cpp::schema {
class Sku {
 public:
  Sku(std::string id, std::string ref, double size_x, double size_y, double size_z, double weight, double load_capacity,
      double max_overhang, double max_overhang_x, double max_overhang_y, bool fragile_top, bool uneven_bottom,
      unsigned char color_r, unsigned char color_g, unsigned char color_b);

  Sku(nlohmann::json& json);

  nlohmann::json json() const;

  inline std::string id() const { return id_; }
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

 private:
  std::string id_;
  std::string ref_;
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
};
}  // namespace janowski::paczki_cpp::schema
