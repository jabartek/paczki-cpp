#pragma once

#include <memory>
#include <optional>
#include <string>
#include <variant>

#include "lib/raylib_clean.h"
#include "rendering/mode_3d.h"
#include "ui/cursor_3d.h"
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

  void leftPress(const Vector2& pos) override;
  void leftRelease(const Vector2& pos) override;
  void leftClick(const Vector2& pos) override;
  void rightClick(const Vector2& pos) override;

  std::optional<std::string> selected_box_pos() const;
  void selectBoxPos(std::string id, bool from_callback = false);
  void unselectBoxPos(bool from_callback = false);

  std::optional<std::string> selected_box_type() const;
  void selectBoxType(std::string id, bool from_callback = false);
  void unselectBoxType(bool from_callback = false);

  void selectBoxTypeFromBoxPos();

  std::optional<std::string> selected_sku() const;
  void selectSku(std::string id, bool from_callback = false);
  void unselectSku(bool from_callback = false);

  std::optional<std::string> active_pallet() const;
  void set_active_pallet(const std::string& id, bool from_callback = false);
  void set_active_pallet(std::size_t idx, bool from_callback = false);

  void addBox();
  void removeBox();

  void advancePallet();

 private:
  void drawStandard();
  void drawExploded();  // debug
  void drawVisible();   // debug
  void drawSelected();

  void prepareLastVisible();
  void clearLastVisible();

  std::optional<std::string> findBox(const Vector2& pos);

  std::shared_ptr<schema::Data> data_;
  std::shared_ptr<pallet_viewer::State> state_;

  ui::Cursor3D cursor_;

  std::optional<std::string> active_pallet_;

  class BoxPosSelection : public std::string {};
  class BoxTypeSelection : public std::string {};
  class SkuSelection : public std::string {};
  std::optional<std::variant<BoxPosSelection, BoxTypeSelection, SkuSelection>> selected_;

  std::optional<std::size_t> last_visible_;

  std::optional<::Vector3> last_valid_pos_;
  std::optional<std::string> hover_box_pos_;
};
}  // namespace janowski::paczki_cpp::ui