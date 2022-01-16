#pragma once

#include <raylib.h>

namespace janowski::paczki_cpp::math {

inline Vector3 operator+(Vector3 lhs, const Vector3 &rhs) {
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  lhs.z += rhs.z;
  return lhs;
}

inline Vector3 operator+(Vector3 lhs, const auto &rhs) {
  lhs.x += rhs;
  lhs.y += rhs;
  lhs.z += rhs;
  return lhs;
}

inline Vector3 operator-(const Vector3 &rhs) {
  return Vector3{-rhs.x, -rhs.y, -rhs.z};
}

inline Vector3 operator-(Vector3 lhs, const auto &rhs) { return lhs + -rhs; }

inline Vector3 operator*(Vector3 lhs, const auto &rhs) {
  lhs.x *= rhs;
  lhs.y *= rhs;
  lhs.z *= rhs;
  return lhs;
}

inline Vector3 makeVector3(auto x, auto y, auto z) {
  return Vector3{
      .x = static_cast<float>(x),
      .y = static_cast<float>(y),
      .z = static_cast<float>(z),
  };
}

} // namespace janowski::paczki_cpp::math