#pragma once

#include <cstdint>

#include "math/vector3.h"

namespace janowski::paczki_cpp::misc {
inline math::Vector3<std::uint8_t> generateColor() {
  return {static_cast<std::uint8_t>(rand()), static_cast<std::uint8_t>(rand()),
          static_cast<std::uint8_t>(rand())};
}
}  // namespace janowski::paczki_cpp::misc