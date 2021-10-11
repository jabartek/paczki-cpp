#pragma once

#include <concepts>

#include "math/vector3.h"

namespace janowski::paczki_cpp::math {
template <std::convertible_to<float> T>
struct BoundingBox {
  Vector3<T> lower;
  Vector3<T> upper;
};

}  // namespace janowski::paczki_cpp::math