#pragma once

#include <cstdint>

#include "math/vector3.h"

namespace janowski::paczki_cpp::box {
class Definition {
 public:
  inline const math::Vector3<float>& size() const { return size_; }
  inline const math::Vector3<std::uint8_t>& color() const { return color_; }
  inline math::Vector3<float>& size() { return size_; }
  inline math::Vector3<std::uint8_t>& color() { return color_; }

  Definition(math::Vector3<float> size, math::Vector3<std::uint8_t> color);

 private:
  math::Vector3<float> size_;
  math::Vector3<std::uint8_t> color_;
};
}  // namespace janowski::paczki_cpp::box