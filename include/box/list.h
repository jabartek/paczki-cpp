#pragma once

#include <list>
#include <memory>
#include <nlohmann/json.hpp>
#include <unordered_map>

#include "box/definition.h"
#include "box/instance.h"
#include "json_utils.h"

namespace janowski::paczki_cpp::box {
class List {
 public:
  using Key = unsigned long long;

  inline const std::list<box::Instance>& instances() const {
    return instances_;
  }

  inline const float x_min() const { return x_min_; }
  inline const float y_min() const { return y_min_; }
  inline const float z_min() const { return z_min_; }
  inline const float x_max() const { return x_max_; }
  inline const float y_max() const { return y_max_; }
  inline const float z_max() const { return z_max_; }

  void addDefinition(Key id, Definition definition);
  void addInstance(Key defId, Instance instance);

  explicit List(const nlohmann::json& data);

  List() = default;

 private:
  std::unordered_map<Key, std::shared_ptr<Definition>> definitions_;
  std::list<Instance> instances_;
  float x_min_, x_max_, y_min_, y_max_, z_min_, z_max_;
};
}  // namespace janowski::paczki_cpp::box