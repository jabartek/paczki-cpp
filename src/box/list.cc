#pragma once

#include "box/list.h"

namespace janowski::paczki_cpp::box {

void List::addDefinition(unsigned long long id, Definition definition) {
  definitions_.emplace(id, std::make_shared<Definition>(std::move(definition)));
}
void List::addInstance(unsigned long long defId, Instance instance) {
  instances_.emplace_back(definitions_.at(defId), instance.position(),
                          instance.rotated());
}

List::List(const nlohmann::json& data) {
  auto definitions = getDefinitions(data);
  auto instances = getInstances(data);
  for (const auto& [id, definition] : definitions) {
    addDefinition(id, std::move(definition));
  }
  for (const auto& [defId, instance] : instances) {
    addInstance(defId, std::move(instance));
  }
}

}  // namespace janowski::paczki_cpp::box