#pragma once

#include <nlohmann/json.hpp>
#include <string>

#include "lib/raylib_clean.h"
#include "math/color.h"

namespace janowski::paczki_cpp::schema {

class BoxPos;
class BoxType;
class Sku;
class Data;

class BoxPos {
 public:
  BoxPos(std::string id, std::string box_type_id, double x, double y, double z, bool rotated, unsigned char color_r,
         unsigned char color_g, unsigned char color_b, Data* schema);
  BoxPos(nlohmann::json& json, Data* schema);

  static BoxPos null() { return BoxPos("", "", 0, 0, 0, false, 0u, 0u, 0u, nullptr); }

  nlohmann::json json() const;

  const BoxType* box_type() const;
  const Sku* sku() const;

  inline std::string id() const { return ref_; }
  inline std::string box_type_id() const { return box_type_id_; }
  inline double x() const { return x_; }
  inline double y() const { return y_; }
  inline double z() const { return z_; }
  inline void set_x(double x) { x_ = x; }
  inline void set_y(double y) { x_ = y; }
  inline void set_z(double z) { x_ = z; }
  inline ::Vector3 position() const { return {(float)x_, (float)y_, (float)z_}; }
  inline bool rotated() const { return rotated_; }
  inline unsigned char color_r() const { return color_r_; }
  inline unsigned char color_g() const { return color_g_; }
  inline unsigned char color_b() const { return color_b_; }
  inline ::Color color() const { return math::makeColor(color_r_, color_g_, color_b_); }

  void tryMove(::Vector3 delta, const std::string& pallet_id, std::optional<::Vector3>& last_valid_pos);

  inline void set_schema(Data* schema) { schema_ = schema; }

  std::optional<BoundingBox> bounding_box() const;

 private:
  std::string ref_;
  std::string box_type_id_;
  double x_;
  double y_;
  double z_;
  bool rotated_;
  unsigned char color_r_;
  unsigned char color_g_;
  unsigned char color_b_;
  Data* schema_;
};

void to_json(nlohmann::json& j, const BoxPos& box_pos);

}  // namespace janowski::paczki_cpp::schema
