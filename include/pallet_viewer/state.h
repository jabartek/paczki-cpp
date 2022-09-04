#pragma once

#include <chrono>
#include <memory>
#include <optional>
#include <string>

#include "rendering/camera.h"
#include "schema/data.h"
#include "state_base.h"
#include "ui/drawable.h"
#include "ui/handlers.h"
#include "ui/pallet_view.h"

namespace janowski::paczki_cpp::pallet_viewer {
struct Alert {
  std::string text;
  std::chrono::time_point<std::chrono::system_clock> timeout;
};

class State : public StateBase {
 public:
  std::shared_ptr<schema::Data> data;

  std::vector<std::unique_ptr<ui::Touchable>> touchables;
  std::optional<ui::PalletView> pallet_view;
  std::optional<Alert> alert;
  std::optional<std::string> file_to_load{};

  std::optional<std::chrono::time_point<std::chrono::system_clock>> left_button_start{};
  std::optional<std::chrono::time_point<std::chrono::system_clock>> right_button_start{};

  State();

  void set_color_scheme(ColorScheme color_scheme) override;

  void update();

  void offerDownload();
};
}  // namespace janowski::paczki_cpp::pallet_viewer