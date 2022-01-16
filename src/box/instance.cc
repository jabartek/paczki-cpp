#include "box/instance.h"

#include "box/definition.h"
#include "math/vector3.h"

namespace janowski::paczki_cpp::box {
using namespace janowski::paczki_cpp::math;

const Vector3 Instance::zero_vec_ = {0.f, 0.f, 0.f};

const BoundingBox Instance::bounding_box() const {
  return BoundingBox{.min = position_,
                     .max = position_ + definition_.lock()->size()};
}

const Color &Instance::color() const { return definition_.lock()->color(); }

const Vector3 &Instance::position() const { return position_; }

const Vector3 Instance::positionCenter() const {
  return position_ + sizeRotated() * 0.5f;
}

const Vector3 &Instance::size() const {
  if (definition_.expired()) {
    return zero_vec_;
  }
  return definition_.lock()->size();
}

const Vector3 Instance::sizeRotated() const {
  auto size = this->size();
  if (rotated_) {
    std::swap(size.x, size.z);
  }
  return size;
}

Instance::Instance(std::shared_ptr<Definition> definition_ptr, Vector3 position,
                   bool rotated)
    : position_(position), rotated_(rotated), definition_(definition_ptr) {}

} // namespace janowski::paczki_cpp::box