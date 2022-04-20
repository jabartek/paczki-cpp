#include "ui/pallet_view.h"

#include <limits>
#include <memory>
#include <sstream>

#include "graphics/box.h"
#include "lib/raylib_clean.h"
#include "math/vector3.h"
#include "pallet_viewer/state.h"
#include "schema/box_pos.h"
#include "schema/data.h"
#include "ui/cursor_3d.h"
#include "ui/drawable.h"

#ifdef EMSCRIPTEN

#include <emscripten.h>
#include <emscripten/val.h>

// EM_JS(void, update_color, (), { document.getElementById("kolorek").style.backgroundColor = Paczka["color"]; });

#endif

using namespace janowski::paczki_cpp::math;

namespace janowski::paczki_cpp::ui {
PalletView::PalletView(std::shared_ptr<schema::Data> data, std::shared_ptr<pallet_viewer::State> state)
    : Touchable(), cursor_(state_) {
  set_data(data, state);
}
void PalletView::set_data(std::shared_ptr<schema::Data> data, std::shared_ptr<pallet_viewer::State> state) {
  data_ = data;
  state_ = state;
  if (!data_->pallets().empty()) {
    active_pallet_ = data_->pallets().front();
  }
}

schema::Data* PalletView::data() { return data_.get(); }

void PalletView::draw() {
  if (!state_) return;
  if (!selected_box_pos_ && !selected_box_type_) {
    drawStandard();
    // drawExploded(frame);  // debug
  } else {
    drawSelected();
  }
  if (selected_box_pos_) {
    cursor_.draw();
  }
}

void PalletView::drawStandard() {
  if (!data_ || !state_ || !active_pallet_) return;
  for (const auto& [id, cube] : data_->box_positions(*active_pallet_)) {
    auto color = state_->color_scheme == pallet_viewer::State::ColorScheme::kByBoxPos
                     ? data_->pos_to_color_map()[id]
                     : data_->type_to_color_map()[cube.box_type_id()];
    if (state_->hoverBoxPos && id == *state_->hoverBoxPos) {
      graphics::drawBoxItems(*data_, cube, data_->box_types().at(cube.box_type_id()),
                             Color{color.r, color.g, color.b, 100u});
    } else {
      graphics::drawBox(*data_, cube, data_->box_types().at(cube.box_type_id()), color);
    }
  }
}

void PalletView::drawExploded() {  // debug
  if (!data_ || !state_ || !active_pallet_) return;
  for (const auto& [id, cube] : data_->box_positions(*active_pallet_)) {
    auto color = state_->color_scheme == pallet_viewer::State::ColorScheme::kByBoxPos
                     ? data_->pos_to_color_map()[id]
                     : data_->type_to_color_map()[cube.box_type_id()];
    if (state_->hoverBoxPos && id == *state_->hoverBoxPos) {
      graphics::drawBoxItems(*data_, cube, data_->box_types().at(cube.box_type_id()),
                             Color{color.r, color.g, color.b, 100u});
    } else {
      graphics::drawBox(*data_, cube, data_->box_types().at(cube.box_type_id()), color);
    }
  }
}

void PalletView::drawSelected() {
  if (!data_ || !state_ || !active_pallet_) return;
  for (const auto& [id, cube] : data_->box_positions(*active_pallet_)) {
    auto color = state_->color_scheme == pallet_viewer::State::ColorScheme::kByBoxPos
                     ? data_->pos_to_color_map()[id]
                     : data_->type_to_color_map()[cube.box_type_id()];
    if ((selected_box_pos_ && *selected_box_pos_ == id) ||
        (selected_box_type_ && *selected_box_type_ == cube.box_type_id())) {
      graphics::drawBox(*data_, cube, data_->box_types().at(cube.box_type_id()), color);
    } else {
      graphics::drawBoxOutline(*data_, cube, color, false);
    }
  }
}

std::optional<std::string> PalletView::findBox(const Vector2& pos) {
  if (!state_ || !state_->camera || !active_pallet_) return std::nullopt;
  std::optional<std::string> box_id;
  auto ray = GetMouseRay(pos, state_->camera->get());
  RayCollision collision = {.distance = std::numeric_limits<float>::max()};

  for (auto& [id, box_pos] : state_->data->box_positions(*active_pallet_)) {
    auto& box_type = state_->data->box_types().at(box_pos.box_type_id());
    RayCollision cube_hit_info = GetRayCollisionBox(
        ray, {(graphics::getPosition(box_pos) * graphics::kSizeMultiplier),
              ((graphics::getPosition(box_pos) + graphics::getSize(box_pos, box_type)) * graphics::kSizeMultiplier)});
    if (cube_hit_info.hit && cube_hit_info.distance < collision.distance) {
      collision = cube_hit_info;
      box_id = box_pos.id();
    }
  }
  return box_id;
}

void PalletView::leftPress(const Vector2& pos) {
  if (!selected_box_pos_) return;
  auto& box_postitions = state_->data->box_positions(*active_pallet_);

  auto& selected_box_pos = box_postitions.at(*selected_box_pos_);
  if (!last_valid_pos_) {
    last_valid_pos_ = cursor_.position();
  }
  cursor_.leftPress(pos);
  auto cursor_delta = cursor_.position() - *last_valid_pos_;
  std::swap(cursor_delta.y, cursor_delta.z);
  cursor_delta = cursor_delta * (1.f / graphics::kSizeMultiplier);
  if (selected_box_pos.tryMove(cursor_delta, *active_pallet_)) {
    last_valid_pos_ = cursor_.position();
  }
}

void PalletView::leftRelease(const Vector2& pos) {
  if (!last_valid_pos_ || !selected_box_pos_ || !active_pallet_) return;
  last_valid_pos_ = std::nullopt;

  auto& box_pos = state_->data->box_positions(*active_pallet_).at(*selected_box_pos_);
  auto& box_type = state_->data->box_types().at(box_pos.box_type_id());
  auto size = graphics::getSize(box_pos, box_type);
  ::Vector3 cursor_pos =
      (graphics::getPosition(box_pos) + size * 0.5f + ::Vector3{0.f, size.y, 0.f} * 0.5f) * graphics::kSizeMultiplier;
  cursor_.leftRelease(pos);
  cursor_ = ui::Cursor3D(state_, 3.f, cursor_pos);
}

void PalletView::leftClick(const Vector2& pos) {
  auto box_id = findBox(pos);
  if (box_id) {
    selectBoxPos(*box_id);
    auto& box_pos = state_->data->box_positions(*active_pallet_).at(*box_id);
    auto& box_type = state_->data->box_types().at(box_pos.box_type_id());
    auto size = graphics::getSize(box_pos, box_type);
    ::Vector3 cursor_pos =
        (graphics::getPosition(box_pos) + size * 0.5f + ::Vector3{0.f, size.y, 0.f} * 0.5f) * graphics::kSizeMultiplier;
    cursor_ = ui::Cursor3D(state_, 3.f, cursor_pos);
    std::cout << cursor_pos.x << "\t" << cursor_pos.y << "\t" << cursor_pos.z << "\n";
  }
}

void PalletView::rightClick(const Vector2& pos) {
  auto box_id = findBox(pos);
  if (box_id && selected_box_pos_ && *box_id == *selected_box_pos_) {
    unselectBoxPos();
  }
}

std::optional<std::string> PalletView::selected_box_pos() const { return selected_box_pos_; }
void PalletView::selectBoxPos(std::string id) {
  if (!data_ || !active_pallet_) return;
  const auto& box_positions = data_->box_positions(*active_pallet_);
  if (box_positions.contains(id)) {
    selected_box_pos_ = id;
    bind::setValue("active_packet", {id});
  }
}
void PalletView::unselectBoxPos() {
  selected_box_pos_ = std::nullopt;
  bind::setValue("active_packet", nlohmann::json{});
}

std::optional<std::string> PalletView::selected_box_type() const { return selected_box_type_; }
void PalletView::selectBoxType(std::string id) {
  if (!data_ || !active_pallet_) return;
  const auto& box_types = data_->box_positions(*active_pallet_);
  if (box_types.contains(id)) {
    selected_box_type_ = id;
    bind::setValue("active_box_type", {id});
  }
}
void PalletView::unselectBoxType() {
  selected_box_pos_ = std::nullopt;
  bind::setValue("active_box_type", nlohmann::json{});
}

std::optional<std::string> PalletView::active_pallet() const { return active_pallet_; }

void PalletView::set_active_pallet(const std::string& id) {
  if (!data_) return;
  const auto& pallet_ids = data_->pallets();
  if (std::find(pallet_ids.begin(), pallet_ids.end(), id) == pallet_ids.end()) {
    throw std::runtime_error("`Data::set_active_pallet` - Invalid pallet id: " + id);
  }
  selected_box_pos_ = std::nullopt;
  active_pallet_ = id;
}

void PalletView::set_active_pallet(std::size_t idx) {
  if (!data_) return;
  const auto& pallet_ids = data_->pallets();
  set_active_pallet(*std::next(pallet_ids.begin(), idx));
}

void PalletView::advancePallet() {
  if (!data_) return;
  const auto& pallet_ids = data_->pallets();
  auto it = std::find(pallet_ids.begin(), pallet_ids.end(), active_pallet_);
  std::size_t idx = std::distance(pallet_ids.begin(), it);
  idx++;
  set_active_pallet(*std::next(pallet_ids.begin(), idx >= pallet_ids.size() ? 0 : idx));
}

}  // namespace janowski::paczki_cpp::ui

// The following does not belong here for now

/*
      std::stringstream color_ss;
      color_ss << "rgb(" << (int)color.r << "," << (int)color.g << "," << (int)color.g << ")";
#ifdef EMSCRIPTEN
      auto color_js = emscripten::val::global("setColor");
      auto color_result = color_js(color_ss.str());
      auto packet_js = emscripten::val::global("setActivePacket");
      auto packet_result = packet_js(cube.json().dump());
      update_color();
#endif
*/
