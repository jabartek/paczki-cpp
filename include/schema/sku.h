#pragma once

namespace janowski::paczki_cpp::schema {
class Sku {
 public:
  Sku(long long id, double size_x, double size_y, double size_z, double weight,
      double load_capacity, double max_overhang, double max_overhang_x,
      double max_overhang_y, bool fragile_top, bool uneven_bottom);

 private:
  long long id_;
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
}  // namespace janowski::paczki_cpp::schema
