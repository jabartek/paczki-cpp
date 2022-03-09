#pragma once

#include <lodepng.h>

#include <array>
#include <cstdint>
#include <span>
#include <vector>

#include "lib/raylib_clean.h"

namespace janowski::paczki_cpp::utils {
std::string toPngBase64(const ::Image& image);
std::string toPngBase64(std::span<std::uint8_t> image, std::size_t width, std::size_t height);
}  // namespace janowski::paczki_cpp::utils
