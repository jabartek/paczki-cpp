#pragma once

#include <raylib.h>

#include <concepts>
#include <utility>

namespace janowski::paczki_cpp::math {
template <std::convertible_to<float> T>
class Vector3 {
 public:
  inline Vector3& operator+=(const Vector3<T>& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }
  inline friend Vector3 operator+(Vector3<T> lhs, const Vector3<T>& rhs) {
    lhs += rhs;
    return lhs;
  }

  inline Vector3& operator+=(const T& rhs) {
    x += rhs;
    y += rhs;
    z += rhs;
    return *this;
  }
  inline friend Vector3 operator+(Vector3<T> lhs, const T& rhs) {
    lhs += rhs;
    return lhs;
  }

  inline Vector3& operator*=(const T& rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
  }
  inline friend Vector3 operator*(Vector3<T> lhs, const T& rhs) {
    lhs *= rhs;
    return lhs;
  }

  inline Vector3(T x, T y, T z)
      : x(std::move(x)), y(std::move(y)), z(std::move(z)){};

  inline explicit Vector3(T val) : x(val), y(val), z(val){};

 private:
 public:
  T x;
  T y;
  T z;
};

template <std::convertible_to<float> T>
inline const ::Vector3& rayvec(const Vector3<T>& vec) {
  return *(reinterpret_cast<const ::Vector3*>(&vec));
}
}  // namespace janowski::paczki_cpp::math