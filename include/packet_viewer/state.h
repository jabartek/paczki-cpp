#pragma once

#include <memory>
#include <optional>

#include "lib/raylib_clean.h"
#include "packet_viewer/data.h"
#include "raylib.h"
#include "state_base.h"
#include "ui/drawable.h"

namespace janowski::paczki_cpp::packet_viewer {
class State : public StateBase, public std::enable_shared_from_this<State> {
 public:
  State();

  void createObjects();
  void handleObjects();
  void drawObjects();

  const Data& data() const { return data_; }
  Data& data() { return data_; }

  std::optional<std::string> selected_box_type();
  inline std::vector<std::unique_ptr<ui::Touchable>>& touchables() { return touchables_; }

  void subscribeAll();

 private:
  Data data_{};
  std::optional<std::string> selected_box_type_;
  std::vector<std::unique_ptr<ui::Touchable>> touchables_;
};

}  // namespace janowski::paczki_cpp::packet_viewer
