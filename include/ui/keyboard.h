#pragma once

#include "camera.h"

namespace janowski::paczki_cpp::ui {
void handleKeyboard(janowski::paczki_cpp::Camera& camera) {
  using JCamera = janowski::paczki_cpp::Camera;
  if (IsKeyDown(KeyboardKey::KEY_W)) {
    camera.rotate(JCamera::Direction::UP, 0.05f);
  }
  if (IsKeyDown(KeyboardKey::KEY_S)) {
    camera.rotate(JCamera::Direction::DOWN, 0.05f);
  }
  if (IsKeyDown(KeyboardKey::KEY_A)) {
    camera.rotate(JCamera::Direction::LEFT, 0.05f);
  }
  if (IsKeyDown(KeyboardKey::KEY_D)) {
    camera.rotate(JCamera::Direction::RIGHT, 0.05f);
  }
  if (IsKeyDown(KeyboardKey::KEY_UP)) {
    camera.zoom(JCamera::Zoom::IN);
  }
  if (IsKeyDown(KeyboardKey::KEY_DOWN)) {
    camera.zoom(JCamera::Zoom::OUT);
  }
}
}  // namespace janowski::paczki_cpp::ui