#include "ui/pallet_view.h"

#include <iostream>  // debug
#include <limits>
#include <memory>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <variant>

#include "bind/stores.h"
#include "graphics/box.h"
#include "lib/raylib_clean.h"
#include "math/vector3.h"
#include "pallet_viewer/state.h"
#include "schema/box_pos.h"
#include "schema/data.h"
#include "ui/cursor_3d.h"
#include "ui/drawable.h"

#ifdef EMSCRIPTEN

#include "lib/emscripten_wrapper.h"

// EM_JS(void, update_color, (), { document.getElementById("kolorek").style.backgroundColor = Paczka["color"]; });

#endif

using namespace janowski::paczki_cpp::math;

namespace janowski::paczki_cpp::ui {
PalletView::PalletView(std::shared_ptr<schema::Data> data, std::shared_ptr<pallet_viewer::State> state)
    : Touchable(), cursor_(state_) {
  set_data(data, state);
#ifdef EMSCRIPTEN
  bind::registerFunction("removeBox", [this]() -> void { this->removeBox(); });
  bind::registerFunction("addBox", [this]() -> void { this->addBox(); });
  bind::registerFunction("resetBoxOrderPreview", [this]() -> void { this->clearLastVisible(); });
  bind::registerFunction("selectBoxTypeFromBoxPos", [this]() -> void { this->selectBoxTypeFromBoxPos(); });
  bind::registerFunction("takeBoxOff", [this]() -> void {
    try {
      std::string box_id = std::get<BoxPosSelection>(*selected_);
      unselectBoxPos();
      this->takeBoxOff(box_id);
    } catch (...) {
      // todo alert js
    }
  });
  bind::registerFunction("putBoxOn", [this](emscripten::val id_val) -> void {
    try {
      std::string box_id = id_val.as<std::string>();
      this->putBoxOn(box_id);
    } catch (...) {
      // todo alert js
    }
  });

  bind::subscribe("active_box_type", [this]() {
    auto id_val = bind::getFrom("active_box_type");
    if (!id_val.isString()) {
      this->unselectBoxType(true);
      return;
    }
    try {
      this->selectBoxType(id_val.as<std::string>(), true);
    } catch (...) {
      // todo alert
    }
  });
  bind::subscribe("selected_pallet", [this]() {
    auto id_val = bind::getFrom("selected_pallet");
    try {
      this->set_active_pallet(id_val.as<std::string>(), true);
    } catch (...) {
      // todo alert
    }
  });
  bind::subscribe("box_pos_order_it", [this]() {
    auto val = bind::getFrom("box_pos_order_it");
    try {
      auto it = val.as<int>();
      if (it < 0) {
        last_visible_.reset();
      } else {
        const int order_len = data_->box_order(*active_pallet_).size();
        last_visible_ = it >= order_len ? order_len - 1 : it;
      }
    } catch (...) {
      // todo alert
    }
  });
  bind::subscribe("color_by_box_pos", [this]() {
    auto val = bind::getFrom("color_by_box_pos");
    try {
      state_->set_color_scheme(val.as<bool>() ? StateBase::ColorScheme::kByBoxPos : StateBase::ColorScheme::kByBoxType);
    } catch (...) {
      std::cout << "bind::subscribe(\"color_by_box_pos\")\n";
    }
  });
#endif
}
void PalletView::set_data(std::shared_ptr<schema::Data> data, std::shared_ptr<pallet_viewer::State> state) {
  data_ = data;
  state_ = state;
  if (!data_->pallets().empty()) {
    set_active_pallet(data_->pallets().front());
  }
  updatePalletIdList();
}

schema::Data* PalletView::data() { return data_.get(); }

void PalletView::draw() {
  if (!state_) return;
  if (!selected_ && !last_visible_) {
    drawStandard();
    // drawExploded(frame);  // debug
  } else if (selected_) {
    drawSelected();
  } else {
    drawVisible();
  }
  if (selected_box_pos()) {
    cursor_.draw();
  }
}

void PalletView::drawStandard() {
  if (!data_ || !state_ || !active_pallet_) return;
  for (const auto& [id, cube] : data_->box_positions(*active_pallet_)) {
    auto color = state_->color_scheme() == pallet_viewer::State::ColorScheme::kByBoxPos
                     ? cube.color()
                     : data_->box_types().at(cube.box_type_id()).color();
    if (hover_box_pos_ && id == *hover_box_pos_) {
      graphics::drawBoxItems(*data_, cube, data_->box_types().at(cube.box_type_id()),
                             Color{color.r, color.g, color.b, 100u});
    } else {
      graphics::drawBox(*data_, cube, data_->box_types().at(cube.box_type_id()), color);
    }
  }
}

void PalletView::drawVisible() {
  if (!data_ || !state_ || !active_pallet_ || !last_visible_) return;
  const auto& box_order = data_->box_order(*active_pallet_);
  for (std::size_t i = 0; i <= *last_visible_ && i < box_order.size(); ++i) {
    const auto& id = box_order[i];
    const auto& cube = data_->box_positions(*active_pallet_).at(id);
    auto color = state_->color_scheme() == pallet_viewer::State::ColorScheme::kByBoxPos
                     ? cube.color()
                     : data_->box_types().at(cube.box_type_id()).color();
    if (hover_box_pos_ && id == *hover_box_pos_) {
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
    auto color = state_->color_scheme() == pallet_viewer::State::ColorScheme::kByBoxPos
                     ? cube.color()
                     : data_->box_types().at(cube.box_type_id()).color();
    if (hover_box_pos_ && id == *hover_box_pos_) {
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
    auto color = state_->color_scheme() == pallet_viewer::State::ColorScheme::kByBoxPos
                     ? cube.color()
                     : data_->box_types().at(cube.box_type_id()).color();
    if (auto selected_box_pos_v = selected_box_pos(), selected_box_type_v = selected_box_type();
        (selected_box_pos_v && *selected_box_pos_v == id) ||
        (selected_box_type_v && *selected_box_type_v == cube.box_type_id())) {
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
  auto selected_box_pos_v = selected_box_pos();
  if (!selected_box_pos_v) return;
  auto& box_postitions = state_->data->box_positions(*active_pallet_);

  auto& selected_box_pos = box_postitions.at(*selected_box_pos_v);
  if (!last_valid_pos_) {
    auto pre_cursor_pos = cursor_.position();
    std::swap(pre_cursor_pos.y, pre_cursor_pos.z);
    last_valid_pos_ = pre_cursor_pos;
  }
  cursor_.leftPress(pos);
  auto cursor_pos = cursor_.position();
  std::swap(cursor_pos.y, cursor_pos.z);

  const auto cursor_delta = (cursor_pos - *last_valid_pos_) * (1.f / graphics::kSizeMultiplier);

  selected_box_pos.tryMove(cursor_delta, *active_pallet_, last_valid_pos_);
}

void PalletView::leftRelease(const Vector2& pos) {
  auto selected_box_pos_v = selected_box_pos();
  if (!last_valid_pos_ || !selected_box_pos_v || !active_pallet_) return;
  last_valid_pos_ = std::nullopt;

  auto& box_pos = state_->data->box_positions(*active_pallet_).at(*selected_box_pos_v);
  auto& box_type = state_->data->box_types().at(box_pos.box_type_id());
  auto size = graphics::getSize(box_pos, box_type);
  ::Vector3 cursor_pos =
      (graphics::getPosition(box_pos) + size * 0.5f + ::Vector3{0.f, size.y, 0.f} * 0.5f) * graphics::kSizeMultiplier;
  cursor_.leftRelease(pos);
  cursor_ = ui::Cursor3D(state_, 1.5f, cursor_pos);
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
    cursor_ = ui::Cursor3D(state_, 1.5f, cursor_pos);
    // rem_std::cout << cursor_pos.x << "\t" << cursor_pos.y << "\t" << cursor_pos.z << "\n";
  }
}

void PalletView::rightClick(const Vector2& pos) {
  auto selected_box_pos_v = selected_box_pos();
  auto box_id = findBox(pos);
  if (box_id && selected_box_pos_v && *box_id == *selected_box_pos_v) {
    unselectBoxPos();
  }
}

std::optional<std::string> PalletView::selected_box_pos() const {
  return (selected_ && std::holds_alternative<BoxPosSelection>(*selected_))
             ? std::make_optional(std::get<BoxPosSelection>(*selected_))
             : std::nullopt;
}
void PalletView::selectBoxPos(std::string id, bool from_callback) {
  if (!data_ || !active_pallet_) return;
  const auto& box_positions = data_->box_positions(*active_pallet_);
  if (box_positions.contains(id)) {
    unselectBoxType(from_callback);
    unselectSku(from_callback);
    selected_ = BoxPosSelection{id};
    if (!from_callback) bind::setValue("active_packet", nlohmann::json{id});
  }
}
void PalletView::unselectBoxPos(bool from_callback) {
  if (selected_ && std::holds_alternative<BoxPosSelection>(*selected_)) selected_ = std::nullopt;
  if (!from_callback) bind::setValue("active_packet", nlohmann::json{});
}

std::optional<std::string> PalletView::selected_box_type() const {
  return (selected_ && std::holds_alternative<BoxTypeSelection>(*selected_))
             ? std::make_optional(std::get<BoxTypeSelection>(*selected_))
             : std::nullopt;
}
void PalletView::selectBoxType(std::string id, bool from_callback) {
  if (!data_) return;
  const auto& box_types = data_->box_types();
  if (box_types.contains(id)) {
    unselectBoxPos(from_callback);
    unselectSku(from_callback);
    selected_ = BoxTypeSelection{id};
    if (!from_callback) bind::setValue("active_box_type", emscripten::val{id});
  } else {
    // rem_std::cout << "PalletView::selectBoxType: No box with id: " << id << "\n";
  }
}
void PalletView::unselectBoxType(bool from_callback) {
  if (selected_ && !std::holds_alternative<BoxTypeSelection>(*selected_)) selected_ = std::nullopt;
  if (!from_callback) bind::setValue("active_box_type", nlohmann::json{});
}

void PalletView::selectBoxTypeFromBoxPos() {
  if (selected_ && std::holds_alternative<BoxPosSelection>(*selected_)) {
    try {
      const auto box_type =
          data_->box_positions(*active_pallet_).at(std::get<BoxPosSelection>(*selected_)).box_type_id();
      selectBoxType(box_type);
    } catch (...) {
      // rem_std::cout << "Could not select BoxType from BoxPos!\n";
    }
  }
}

std::optional<std::string> PalletView::selected_sku() const {
  return (selected_ && std::holds_alternative<SkuSelection>(*selected_))
             ? std::make_optional(std::get<SkuSelection>(*selected_))
             : std::nullopt;
}
void PalletView::selectSku(std::string id, bool from_callback) {
  if (!data_) return;
  const auto& skus = data_->skus();
  if (skus.contains(id)) {
    unselectBoxPos(from_callback);
    unselectBoxType(from_callback);
    selected_ = SkuSelection{id};
    if (!from_callback) bind::setValue("active_sku", nlohmann::json{id});
  }
}
void PalletView::unselectSku(bool from_callback) {
  if (selected_ && !std::holds_alternative<SkuSelection>(*selected_)) selected_ = std::nullopt;
  if (!from_callback) bind::setValue("active_sku", nlohmann::json{});
}

std::optional<std::string> PalletView::active_pallet() const { return active_pallet_; }

void PalletView::set_active_pallet(const std::string& id, bool from_callback) {
  if (!data_) return;
  const auto& pallet_ids = data_->pallets();
  if (std::find(pallet_ids.begin(), pallet_ids.end(), id) == pallet_ids.end()) {
    throw std::runtime_error("`Data::set_active_pallet` - Invalid pallet id: " + id);
  }
  if (!from_callback) bind::setValue("selected_pallet", emscripten::val(id));
  selected_.reset();
  clearLastVisible();
#ifdef EMSCRIPTEN
  bind::setValue("active_packet", emscripten::val::null());
  bind::setValue("active_box_type", emscripten::val::null());
  bind::setValue("active_sku", emscripten::val::null());
  const auto j = nlohmann::json{data_->box_order(id)};
  // rem_std::cout << "\n1\n2\n3\n5\nBoxOrder"<< j << "\n1\n2\n3";
  bind::setValue("box_pos_order", j);
#endif
  active_pallet_ = id;
}

void PalletView::set_active_pallet(std::size_t idx, bool from_callback) {
  if (!data_) return;
  const auto& pallet_ids = data_->pallets();
  set_active_pallet(*std::next(pallet_ids.begin(), idx), from_callback);
}

void PalletView::advancePallet() {
  if (!data_) return;
  const auto& pallet_ids = data_->pallets();
  auto it = std::find(pallet_ids.begin(), pallet_ids.end(), active_pallet_);
  std::size_t idx = std::distance(pallet_ids.begin(), it);
  idx++;
  set_active_pallet(*std::next(pallet_ids.begin(), idx >= pallet_ids.size() ? 0 : idx));
  prepareLastVisible();
}

void PalletView::prepareLastVisible() {
  if (!active_pallet_) {
    return;
  }

  const auto& order = data_->box_order(*active_pallet_);
  if (order.empty()) {
    return;
  }
  last_visible_ = data_->box_order(*active_pallet_).size() - 1;
}

void PalletView::clearLastVisible() {
  last_visible_.reset();
  bind::setValue("box_pos_order_it", emscripten::val{-1});
}

void PalletView::addBox() {
  if (!last_visible_) {
    prepareLastVisible();
  }
  if (last_visible_ && *last_visible_ < data_->box_order(*active_pallet_).size() - 1) {
    (*last_visible_)++;
  }
}

void PalletView::removeBox() {
  if (!last_visible_) {
    prepareLastVisible();
  }
  if (last_visible_ && *last_visible_ > 0) {
    (*last_visible_)--;
  }
}

void PalletView::takeBoxOff(const std::string& box_pos_id) {
  if (!active_pallet_ || !data_) return;
  data_->takeBoxOff(*active_pallet_, box_pos_id);
  bind::setValue("box_clipboard", nlohmann::json{data_->box_pos_clipboard()});
  const auto j = nlohmann::json{data_->box_order(*active_pallet_)};
  bind::setValue("box_pos_order", j);
  updatePalletIdList();
}
void PalletView::putBoxOn(const std::string& box_pos_id) {
  if (!active_pallet_) return;
  data_->putBoxOn(*active_pallet_, box_pos_id);
  bind::setValue("box_clipboard", nlohmann::json{data_->box_pos_clipboard()});
  const auto j = nlohmann::json{data_->box_order(*active_pallet_)};
  bind::setValue("box_pos_order", j);
  updatePalletIdList();
}

void PalletView::updatePalletIdList() {
  if (!data_) return;
  auto pallets = data_->pallets();
  std::vector<std::pair<std::string, std::unordered_map<std::string, std::size_t>>> pallets_s;

  for (const auto& pal : pallets) {
    decltype(pallets_s)::value_type val;
    val.first = pal;
    const auto& box_pos_local = data_->box_positions(pal);
    for (const auto& pos : box_pos_local) {
      val.second[pos.second.box_type_id()]++;
    }
    pallets_s.emplace_back(std::move(val));
  }

  auto pallet_id_list = nlohmann::json(pallets_s);
  bind::setValue("pallet_id_list", pallet_id_list);
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
