#include "ui/pallet_view.h"

#include "lib/raylib_clean.h"

#include <memory>
#include <sstream>

#include "graphics/box.h"
#include "math/vector3.h"
#include "pallet_viewer/state.h"
#include "schema/box_pos.h"
#include "schema/data.h"
#include "ui/drawable.h"

#ifdef EMSCRIPTEN

#include <emscripten.h>
#include <emscripten/val.h>

// EM_JS(void, update_color, (), { document.getElementById("kolorek").style.backgroundColor = Paczka["color"]; });

#endif

using namespace janowski::paczki_cpp::math;

namespace janowski::paczki_cpp::ui {
PalletView::PalletView(std::shared_ptr<schema::Data> data, std::shared_ptr<pallet_viewer::State> state) : Touchable() {
  data_ = data;
  state_ = state;
}
void PalletView::set_data(std::shared_ptr<schema::Data> data, std::shared_ptr<pallet_viewer::State> state) {
  data_ = data;
  state_ = state;
}

schema::Data* PalletView::data() { return data_.get(); }

void PalletView::draw() {
  if (!state_) return;
  if (!state_->selectedBoxPos && !state_->selectedBoxType) {
    drawStandard();
    // drawExploded(frame);  // debug
  } else {
    drawSelected();
  }
}

void PalletView::drawStandard() {
  if (!data_ || !state_) return;
  for (const auto& [id, cube] : data_->box_positions()) {
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
  if (!data_ || !state_) return;
  for (const auto& [id, cube] : data_->box_positions()) {
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
  if (!data_ || !state_) return;
  for (const auto& [id, cube] : data_->box_positions()) {
    auto color = state_->color_scheme == pallet_viewer::State::ColorScheme::kByBoxPos
                     ? data_->pos_to_color_map()[id]
                     : data_->type_to_color_map()[cube.box_type_id()];
    if (*state_->selectedBoxPos == id || *state_->selectedBoxType == cube.box_type_id()) {
      graphics::drawBox(*data_, cube, data_->box_types().at(cube.box_type_id()), color);
    } else {
      graphics::drawBoxOutline(*data_, cube, color, false);
    }
  }
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