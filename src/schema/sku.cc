#include "schema/sku.h"

namespace janowski::paczki_cpp::schema {

Sku::Sku(long long id, double size_x, double size_y, double size_z,
         double weight, double load_capacity, double max_overhang,
         double max_overhang_x, double max_overhang_y, bool fragile_top,
         bool uneven_bottom)
    : size_x_(size_x),
      size_y_(size_y),
      size_z_(size_z),
      weight_(weight),
      load_capacity_(load_capacity),
      max_overhang_(max_overhang),
      max_overhang_x_(max_overhang_x),
      max_overhang_y_(max_overhang_y),
      fragile_top_(fragile_top),
      uneven_bottom_(uneven_bottom) {}

}  // namespace janowski::paczki_cpp::schema
