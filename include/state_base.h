#pragma once

#include <optional>

#include "rendering/camera.h"
#include "ui/handlers.h"

namespace janowski::paczki_cpp {

class StateBase {
 public:
  enum class ColorScheme { kByBoxPos, kByBoxType };
  ColorScheme color_scheme() const { return color_scheme_; }
  virtual void set_color_scheme(ColorScheme color_scheme) { color_scheme_ = color_scheme; }
  std::optional<ui::HandlerStore> handler_store;

  std::optional<rendering::Camera> camera;

  int window_width{};
  int window_height{};

 protected:
  ColorScheme color_scheme_ = ColorScheme::kByBoxPos;
};
}  // namespace janowski::paczki_cpp