#pragma once

#include <nlohmann/json.hpp>

#include <string>

namespace janowski::paczki_cpp::schema {
class Sku {
public:
  Sku(std::string id, double size_x, double size_y, double size_z,
      double weight, double load_capacity, double max_overhang,
      double max_overhang_x, double max_overhang_y, bool fragile_top,
      bool uneven_bottom);

  Sku(nlohmann::json &json);

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

private:
  std::string id_;
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
};
} // namespace janowski::paczki_cpp::schema
