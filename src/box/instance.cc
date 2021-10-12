#include "box/instance.h"

namespace janowski::paczki_cpp::box {

const math::BoundingBox<float> Instance::bounding_box() const {
  return math::BoundingBox<float>{position_,
                                  position_ + definition_.lock()->size()};
}

const math::Vector3<uint8_t>& Instance::color() const {
  return definition_.lock()->color();
}

const math::Vector3<float>& Instance::position() const { return position_; }

const math::Vector3<float> Instance::positionCenter() const {
  return position_ + sizeRotated() * 0.5f;
}

const math::Vector3<float>& Instance::size() const {
  if (definition_.expired()) {
    return {0.f, 0.f, 0.f};
  }
  return definition_.lock()->size();
}

const math::Vector3<float> Instance::sizeRotated() const {
  auto size = this->size();
  if (rotated_) {
    std::swap(size.x, size.z);
  }
  return size;
}

Instance::Instance(std::shared_ptr<Definition> definition_ptr,
                   math::Vector3<float> position, bool rotated)
    : position_(position), rotated_(rotated), definition_(definition_ptr) {}

}  // namespace janowski::paczki_cpp::box