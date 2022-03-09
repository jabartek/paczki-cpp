#pragma once

#include "lib/raylib_clean.h"

#include <memory>

#include "rendering/mode_3d.h"

namespace janowski::paczki_cpp::schema {
class Data;
}

namespace janowski::paczki_cpp::pallet_viewer {
class State;
}

namespace janowski::paczki_cpp::ui {
class PalletView {
 public:
  void set_data(std::shared_ptr<schema::Data> data, std::shared_ptr<pallet_viewer::State> state);
  schema::Data* data();

  void draw(rendering::Mode3D& frame);

  bool handleClick(const Vector2& pos);

 private:
  void drawStandard(rendering::Mode3D& frame);
  void drawExploded(rendering::Mode3D& frame); // debug
  void drawSelected(rendering::Mode3D& frame);

  std::shared_ptr<schema::Data> data_;
  std::shared_ptr<pallet_viewer::State> state_;
};
}  // namespace janowski::paczki_cpp::ui