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
  bool skip_frame{false};

  void update();
};
}  // namespace janowski::paczki_cpp::pallet_viewer