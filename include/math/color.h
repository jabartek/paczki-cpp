#pragma once

#include <raylib.h>

namespace janowski::paczki_cpp::math {

inline Color makeColor(auto r, auto g, auto b, auto a = 255u) {
  return Color{
      .r = static_cast<unsigned char>(r),
      .g = static_cast<unsigned char>(g),
      .b = static_cast<unsigned char>(b),
      .a = static_cast<unsigned char>(a),
  };
}

inline Color makeColor(auto r, auto g, auto b) { return makeColor(r, g, b, 255u); }

}  // namespace janowski::paczki_cpp::math