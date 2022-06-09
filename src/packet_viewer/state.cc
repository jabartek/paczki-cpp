#include "packet_viewer/state.h"

#include <memory>

#include "graphics/box.h"
#include "raylib.h"
#include "ui/rotator.h"

using namespace janowski::paczki_cpp::math;

namespace janowski::paczki_cpp::packet_viewer {
State::State() {}

void State::createObjects() {
  auto rotator_ptr =
      std::make_unique<ui::Rotator>(Vector2{.x = window_width - 70.f, .y = 70.f}, 50, shared_from_this());
  touchables_.emplace_back(std::move(rotator_ptr));
}

void State::drawObjects() {
  for (auto& touchable : touchables_) {
    touchable->draw();
  }
}

void State::handleObjects() {
  static int left_button_lenght{0};
  static int right_button_lenght{0};
  auto mouse_pos = GetMousePosition();
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    left_button_lenght++;
    if (left_button_lenght > ui::kMaxClickLength) {
      // rem_std::cout << "Left button pressed at " << mouse_pos.x << "," << mouse_pos.y << "\n";
      for (auto& touchable : touchables_) {
        if (!touchable->isOver(mouse_pos)) continue;
        touchable->leftPress(mouse_pos);
      }
    }
  }
  if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
    right_button_lenght++;
    if (right_button_lenght > ui::kMaxClickLength) {
      // rem_std::cout << "Right button pressed at " << mouse_pos.x << "," << mouse_pos.y << "\n";
      for (auto& touchable : touchables_) {
        if (!touchable->isOver(mouse_pos)) continue;
        touchable->rightPress(mouse_pos);
      }
    }
  }
  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
    if (left_button_lenght <= ui::kMaxClickLength) {
      // rem_std::cout << "Left button clicked at " << mouse_pos.x << "," << mouse_pos.y << "\n";
      for (auto& touchable : touchables_) {
        if (!touchable->isOver(mouse_pos)) continue;
        touchable->leftClick(mouse_pos);
      }
    } else {
      for (auto& touchable : touchables_) {
        if (!touchable->isOver(mouse_pos)) continue;
        touchable->leftRelease(mouse_pos);
      }
    }
    left_button_lenght = 0;
  }
  if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
    if (right_button_lenght <= ui::kMaxClickLength) {
      // rem_std::cout << "Right button clicked at " << mouse_pos.x << "," << mouse_pos.y << "\n";
      for (auto& touchable : touchables_) {
        if (!touchable->isOver(mouse_pos)) continue;
        touchable->rightClick(mouse_pos);
      }
    } else {
      for (auto& touchable : touchables_) {
        if (!touchable->isOver(mouse_pos)) continue;
        touchable->rightRelease(mouse_pos);
      }
    }
    right_button_lenght = 0;
  }
  for (auto& touchable : touchables_) {
    if (!touchable->isOver(mouse_pos)) continue;
    touchable->hover(mouse_pos);
  }
}

void State::subscribeAll() {
  bind::subscribe("sku_list", [this]() {
    auto em_val = bind::getFrom("sku_list");
    if (em_val.isNull()) {
      return;
    }
    auto parser = emscripten::val::global("JSON");
    auto json_stringified = parser.call<emscripten::val>("stringify", em_val);
    auto json = nlohmann::json::parse(json_stringified.as<std::string>());
    // rem_std::cout << json_stringified.as<std::string>() << "\n";
    this->data().setSkus(json);
  });
  bind::subscribe("box_type_list", [this]() {
    auto em_val = bind::getFrom("box_type_list");
    if (em_val.isNull()) {
      return;
    }
    auto parser = emscripten::val::global("JSON");
    auto json_stringified = parser.call<emscripten::val>("stringify", em_val);
    auto json = nlohmann::json::parse(json_stringified.as<std::string>());
    // rem_std::cout << json_stringified.as<std::string>() << "\n";
    this->data().setBoxTypeList(json);
  });
  bind::subscribe("active_box_type", [this]() {
    auto em_val = bind::getFrom("active_box_type");
    if (em_val.isNull()) {
      this->selected_box_type_.reset();
      return;
    }
    auto id = em_val.as<std::string>();
    // rem_std::cout << "New active box type! " << id << "\n";
    this->selected_box_type_ = id;
    try {
      const auto& box_type = this->data_.box_types().at(*this->selected_box_type_);
      ::Vector3 target = graphics::getSize(schema::BoxPos::null(), box_type) * 0.5f * graphics::kSizeMultiplier;
      this->camera->set_target(target);
      const auto distance = std::max({target.x, target.y, target.z}) * 3.5f;
      this->camera->set_distance(distance);
      this->camera->updateCamera();
    } catch (...) {
      // todo debug
    }
  });
}
std::optional<std::string> State::selected_box_type() { return selected_box_type_; }

}  // namespace janowski::paczki_cpp::packet_viewer
