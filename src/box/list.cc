#include "box/list.h"

#include "json_utils.h"
#include "math/vector3.h"

namespace janowski::paczki_cpp::box {
using namespace janowski::paczki_cpp::math;

void List::addDefinition(unsigned long long id, Definition definition) {
  definitions_.emplace(id, std::make_shared<Definition>(std::move(definition)));
}
void List::addInstance(unsigned long long defId, Instance instance) {
  instances_.emplace_back(definitions_.at(defId), instance.position(),
                          instance.rotated());
}

List::List(const nlohmann::json &data) {
  auto definitions = getDefinitions(data);
  auto instances = getInstances(data);
  for (const auto &[id, definition] : definitions) {
    addDefinition(id, std::move(definition));
  }
  for (const auto &[defId, instance] : instances) {
    addInstance(defId, std::move(instance));
  }
  x_min_ = y_min_ = z_min_ = std::numeric_limits<float>::max();
  x_max_ = y_max_ = z_max_ = std::numeric_limits<float>::min();
  for (auto &box : instances_) {
    auto lower = box.position();
    auto upper = box.position() + box.size();
    if (lower.x < x_min_) {
      x_min_ = lower.x;
    }
    if (lower.y < y_min_) {
      y_min_ = lower.y;
    }
    if (lower.z < z_min_) {
      z_min_ = lower.z;
    }
    if (upper.x > x_max_) {
      x_max_ = upper.x;
    }
    if (upper.y > y_max_) {
      y_max_ = upper.y;
    }
    if (upper.z > z_max_) {
      z_max_ = upper.z;
    }
  }
}

} // namespace janowski::paczki_cpp::box