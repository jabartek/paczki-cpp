#pragma once

#include <raylib.h>

#include "box/instance.h"

namespace janowski::paczki_cpp::graphics {
constexpr float kSizeMultiplier = 0.01f;

void drawBox(const box::Instance& box);
void drawBoxOutline(const box::Instance& box);
}  // namespace janowski::paczki_cpp::graphics