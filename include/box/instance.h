#pragma once
#include <memory>

#include "box/definition.h"
#include "math/bounding_box.h"
#include "math/vector3.h"

namespace janowski::paczki_cpp::box {
class Instance {
 public:
  const math::BoundingBox<float> bounding_box() const;
  const math::Vector3<uint8_t>& color() const;

  const math::Vector3<float>& position() const;
  const math::Vector3<float> positionCenter() const;
  const math::Vector3<float>& size() const;
  const math::Vector3<float> sizeRotated() const;
  bool rotated() const { return rotated_; }

  Instance(std::shared_ptr<Definition> definition_ptr,
           math::Vector3<float> position, bool rotated);

 private:
  math::Vector3<float> position_;
  bool rotated_;
  std::weak_ptr<Definition> definition_;

  static const math::Vector3<float> zero_vec_;
};
}  // namespace janowski::paczki_cpp::box