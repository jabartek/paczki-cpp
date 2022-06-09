#pragma once

#include <optional>

#include "rendering/camera.h"
#include "ui/handlers.h"

namespace janowski::paczki_cpp {

class StateBase {
 public:
  enum class ColorScheme { kByBoxPos, kByBoxType };
  ColorScheme color_scheme = ColorScheme::kByBoxPos;
  std::optional<ui::HandlerStore> handler_store;

  std::optional<rendering::Camera> camera;

  int window_width{};
  int window_height{};
};
}  // namespace janowski::paczki_cpp