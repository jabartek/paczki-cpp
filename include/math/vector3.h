#pragma once

#include <raylib.h>

#include <concepts>

namespace janowski::paczki_cpp::math {
template <std::convertible_to<float> T>
class Vector3 {
 public:
  inline Vector3& operator+=(const Vector3<T>& rhs) {
    x_ += rhs.x_;
    y_ += rhs.y_;
    z_ += rhs.z_;
    return *this;
  }
  inline friend Vector3 operator+(Vector3<T> lhs, const Vector3<T>& rhs) {
    lhs += rhs;
    return lhs;
  }

  inline Vector3& operator+=(const T& rhs) {
    x_ += rhs;
    y_ += rhs;
    z_ += rhs;
    return *this;
  }
  inline friend Vector3 operator+(Vector3<T> lhs, const T& rhs) {
    lhs += rhs;
    return lhs;
  }

  inline Vector3& operator*=(const T& rhs) {
    x_ *= rhs;
    y_ *= rhs;
    z_ *= rhs;
    return *this;
  }
  inline friend Vector3 operator*(Vector3<T> lhs, const T& rhs) {
    lhs *= rhs;
    return lhs;
  }

  inline const T& x() const { return x_; }
  inline const T& y() const { return y_; }
  inline const T& z() const { return z_; }
  inline T& x() { return x_; }
  inline T& y() { return y_; }
  inline T& z() { return z_; }

  inline Vector3(T x, T y, T z)
      : x_(std::move(x)), y_(std::move(y)), z_(std::move(z)){};
      
  inline explicit Vector3(T val) : x_(val), y_(val), z_(val){};

 private:
  T x_;
  T y_;
  T z_;
};

template <std::convertible_to<float> T>
inline const ::Vector3& rayvec(const Vector3<T>& vec) {
  return *(reinterpret_cast<const ::Vector3*>(&vec));
}
}  // namespace janowski::paczki_cpp::math