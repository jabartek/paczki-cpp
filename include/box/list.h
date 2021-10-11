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
  inline const std::list<box::Instance>& instances() const {
    return instances_;
  }

  void addDefinition(unsigned long long id, Definition definition);
  void addInstance(unsigned long long defId, Instance instance);

  explicit List(const nlohmann::json& data);

  List() = default;

 private:
  std::unordered_map<unsigned long long, std::shared_ptr<Definition>>
      definitions_;
  std::list<box::Instance> instances_;
};
}  // namespace janowski::paczki_cpp::box