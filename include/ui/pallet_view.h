#pragma once

#include <memory>

#include "lib/raylib_clean.h"
#include "rendering/mode_3d.h"
#include "ui/drawable.h"

namespace janowski::paczki_cpp::schema {
class Data;
}

namespace janowski::paczki_cpp::pallet_viewer {
class State;
}

namespace janowski::paczki_cpp::ui {
class PalletView : public Touchable {
 public:
  PalletView(std::shared_ptr<schema::Data> data, std::shared_ptr<pallet_viewer::State> state);

  void set_data(std::shared_ptr<schema::Data> data, std::shared_ptr<pallet_viewer::State> state);
  schema::Data* data();

  void draw() override;
  bool isOver(const Vector2& /*position*/) const override { return true; };

  bool handleClick(const Vector2& pos);

 private:
  void drawStandard();
  void drawExploded();  // debug
  void drawSelected();

  std::shared_ptr<schema::Data> data_;
  std::shared_ptr<pallet_viewer::State> state_;
};
}  // namespace janowski::paczki_cpp::ui