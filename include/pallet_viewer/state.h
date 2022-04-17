#pragma once

#include <chrono>
#include <memory>
#include <optional>
#include <string>

#include "rendering/camera.h"
#include "schema/data.h"
#include "ui/drawable.h"
#include "ui/pallet_view.h"

namespace janowski::paczki_cpp::pallet_viewer {
struct Alert {
  std::string text;
  std::chrono::time_point<std::chrono::system_clock> timeout;
};

class State {
 public:
  enum class ColorScheme { kByBoxPos, kByBoxType } color_scheme = ColorScheme::kByBoxPos;

  std::shared_ptr<schema::Data> data;
  std::optional<schema::Data::ColorMap> color_map;
  std::optional<std::string> selectedBoxPos;
  std::optional<std::string> selectedBoxType;
  std::optional<std::string> hoverBoxPos;

  std::vector<std::unique_ptr<ui::Touchable>> touchables;

  int window_width{};
  int window_height{};

  std::optional<rendering::Camera> camera;
  std::optional<ui::PalletView> pallet_view;

  std::optional<Alert> alert;

  void update();
};
}  // namespace janowski::paczki_cpp::pallet_viewer