#pragma once

#include <raylib.h>

namespace janowski::paczki_cpp::math {

inline Vector2 operator+(Vector2 lhs, const Vector2 &rhs) {
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  return lhs;
}

inline Vector2 operator+(Vector2 lhs, const auto &rhs) {
  lhs.x += rhs;
  lhs.y += rhs;
  return lhs;
}

inline Vector2 operator-(const Vector2 &rhs) { return Vector2{-rhs.x, -rhs.y}; }

inline Vector2 operator-(Vector2 lhs, const auto &rhs) { return lhs + -rhs; }

inline Vector2 operator*(Vector2 lhs, const auto &rhs) {
  lhs.x *= rhs;
  lhs.y *= rhs;
  return lhs;
}

inline Vector2 makeVector2(auto x, auto y) {
  return Vector2{
      .x = static_cast<float>(x),
      .y = static_cast<float>(y),
  };
}
} // namespace janowski::paczki_cpp::math