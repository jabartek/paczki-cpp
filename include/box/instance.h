#pragma once
#include <memory>

#include "math/bounding_box.h"
#include "math/vector3.h"
#include "box/definition.h"

namespace janowski::paczki_cpp::box {
class Instance {
 public:
  const math::BoundingBox<float> bounding_box() const;
  const math::Vector3<uint8_t>& color() const;

  const math::Vector3<float>& position() const;
  const math::Vector3<float>& size() const;
  bool rotated() const { return rotated_; }

  Instance(std::shared_ptr<Definition> definition_ptr,
           math::Vector3<float> position, bool rotated);

 private:
  math::Vector3<float> position_;
  bool rotated_;
  std::weak_ptr<Definition> definition_;
};
}  // namespace janowski::paczki_cpp::box