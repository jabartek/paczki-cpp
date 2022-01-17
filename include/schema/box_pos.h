#pragma once

#include <nlohmann/json.hpp>

#include <string>

namespace janowski::paczki_cpp::schema {

class BoxPos;
class BoxType;
class Sku;
class Data;

class BoxPos {
public:
  BoxPos(std::string id, std::string box_type_id, double x, double y, double z,
         bool rotated, Data *schema);
  BoxPos(nlohmann::json &json);
  BoxPos(nlohmann::json &json, Data *schema);

  nlohmann::json json() const;

  const BoxType *box_type() const;
  const Sku *sku() const;

  inline std::string id() const { return id_; }
  inline std::string box_type_id() const { return box_type_id_; }
  inline double x() const { return x_; }
  inline double y() const { return y_; }
  inline double z() const { return z_; }
  inline bool rotated() const { return rotated_; }

  inline void set_schema(Data *schema) { schema_ = schema; }

private:
  std::string id_;
  std::string box_type_id_;
  double x_;
  double y_;
  double z_;
  bool rotated_;
  Data *schema_;
};
} // namespace janowski::paczki_cpp::schema
