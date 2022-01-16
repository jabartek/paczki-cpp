#pragma once
#include "math/color.h"

#include <cstdlib>

namespace janowski::paczki_cpp::misc {
inline Color generateColor() { return math::makeColor(rand(), rand(), rand()); }
} // namespace janowski::paczki_cpp::misc