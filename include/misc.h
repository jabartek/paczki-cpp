#pragma once
#include <cstdlib>

#include "math/color.h"

namespace janowski::paczki_cpp::misc {
inline Color generateColor() { return math::makeColor(rand(), rand(), rand()); }
}  // namespace janowski::paczki_cpp::misc