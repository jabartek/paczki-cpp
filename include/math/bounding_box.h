#pragma once

// #include <concepts> // TODO: Find out why concepts don't work on Emscripten/Clang on Linux
// template <std::convertible_to<float> T>

#include "math/vector3.h"

namespace janowski::paczki_cpp::math {
template <class T>
struct BoundingBox {
  Vector3<T> lower;
  Vector3<T> upper;
};

}  // namespace janowski::paczki_cpp::math