#pragma once

#include <raylib.h>

namespace janowski::paczki_cpp::box {
class Definition {
public:
  inline const Vector3 &size() const { return size_; }
  inline const Color &color() const { return color_; }
  inline Vector3 &size() { return size_; }
  inline Color &color() { return color_; }

  Definition(Vector3 size, Color color);

private:
  Vector3 size_;
  Color color_;
};
} // namespace janowski::paczki_cpp::box