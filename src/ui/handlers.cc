#include "ui/handlers.h"

#include <bind/bind.h>
#include <raylib.h>
//
#include <algorithm>
#include <filesystem>
#include <optional>
#include <utility>
//
#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>

#include "bind/stores.h"
#include "colors.h"
#include "graphics/box.h"
#include "pallet_viewer/state.h"

#ifdef EMSCRIPTEN
#include "lib/emscripten_wrapper.h"
#endif

using namespace janowski::paczki_cpp::math;

namespace janowski::paczki_cpp::ui {

namespace {
void loadFile(const std::string& path, std::shared_ptr<pallet_viewer::State> state_ptr) {
  {
    std::ifstream file(path);
    nlohmann::json json;
    file >> json;
    state_ptr->data = std::make_shared<schema::Data>(json);
  }
  auto& data = state_ptr->data;
  state_ptr->pallet_view.emplace(data, state_ptr);
  if (auto& camera = state_ptr->camera) {
    camera->set_target(data->dimensions() * 0.5f * graphics::kSizeMultiplier);
    camera->updateCamera();
  }
#ifdef EMSCRIPTEN
  nlohmann::json sku_list;
  for (auto& sku : data->skus()) {
    sku_list[sku.first] = sku.second.json();
  }
  bind::setValue("sku_list", sku_list);

  nlohmann::json box_type_list;
  for (auto& box_type : data->box_types()) {
    box_type_list[box_type.first] = box_type.second.json();
  }
  bind::setValue("box_type_list", box_type_list);

  nlohmann::json box_pos_list;
  for (const auto& pallet : data->pallets()) {
    box_pos_list[pallet] = {};
    for (const auto& [id, position] : data->box_positions(pallet)) {
      box_pos_list[pallet][id] = position.json();
    }
  }
  bind::setValue("box_pos_list", box_pos_list);

  // auto set_box_type_list = emscripten::val::global("setBoxTypeList");
  // auto set_box_type_list_result = set_box_type_list(box_type_list.dump());
#endif
}
}  // namespace

HandlerStore::HandlerStore(std::shared_ptr<pallet_viewer::State> state) {
  state_ = state;
  handlers_.emplace_back(&DropHandler::pred, &DropHandler::func);
  handlers_.emplace_back(&KeyboardHandler::pred, &KeyboardHandler::func);
}

void HandlerStore::doRegister(Handler handler) { handlers_.emplace_back(std::move(handler)); }
void HandlerStore::handleAll() {
  for (auto& [pred, func] : handlers_) {
    if (pred(state_)) func(state_);
  }
}

bool DropHandler::pred(std::shared_ptr<pallet_viewer::State> state_ptr) {
  return ::IsFileDropped() || (state_ptr && state_ptr->file_to_load);
}
void DropHandler::func(std::shared_ptr<pallet_viewer::State> state_ptr) {
  if (!state_ptr) return;
  std::optional<std::string> file_to_load{};
  if (::IsFileDropped()) {
    int file_count{};
    auto file_names_ptr = GetDroppedFiles(&file_count);

    if (file_count > 0) file_to_load = file_names_ptr[0];
    ClearDroppedFiles();
  } else if (state_ptr->file_to_load) {
    file_to_load = state_ptr->file_to_load;
    state_ptr->file_to_load.reset();
  }
  if (file_to_load) {
    loadFile(*file_to_load, state_ptr);
  }
}

bool KeyboardHandler::pred(std::shared_ptr<pallet_viewer::State> /*state_ptr*/) { return true; }
void KeyboardHandler::func(std::shared_ptr<pallet_viewer::State> state_ptr) {
  using JCamera = janowski::paczki_cpp::rendering::Camera;
  if (!state_ptr->camera) {
    return;
  }
  auto& camera = *(state_ptr->camera);
  if (IsKeyDown(KeyboardKey::KEY_W)) {
    camera.rotate(JCamera::Direction::UP, 0.05f);
  }
  if (IsKeyDown(KeyboardKey::KEY_S)) {
    camera.rotate(JCamera::Direction::DOWN, 0.05f);
  }
  if (IsKeyDown(KeyboardKey::KEY_A)) {
    camera.rotate(JCamera::Direction::LEFT, 0.05f);
  }
  if (IsKeyDown(KeyboardKey::KEY_D)) {
    camera.rotate(JCamera::Direction::RIGHT, 0.05f);
  }
  if (IsKeyDown(KeyboardKey::KEY_UP)) {
    camera.zoom(JCamera::Zoom::IN);
  }
  if (IsKeyDown(KeyboardKey::KEY_DOWN)) {
    camera.zoom(JCamera::Zoom::OUT);
  }
  if (IsKeyReleased(KeyboardKey::KEY_Z)) {
    state_ptr->set_color_scheme(state_ptr->color_scheme() == pallet_viewer::State::ColorScheme::kByBoxPos
                                    ? pallet_viewer::State::ColorScheme::kByBoxType
                                    : pallet_viewer::State::ColorScheme::kByBoxPos);
  }
  if (IsKeyReleased(KeyboardKey::KEY_P)) {
    // rem_std::cout << "test.json opening" << std::endl;
    loadFile("test.json", state_ptr);
  }
  if (IsKeyReleased(KeyboardKey::KEY_K)) {
    if (state_ptr) state_ptr->offerDownload();
  }
  if (IsKeyReleased(KeyboardKey::KEY_F)) {
    if (!state_ptr->pallet_view) return;
    state_ptr->pallet_view->advancePallet();
  }

  if (IsKeyReleased(KeyboardKey::KEY_R)) {
    try {
      bind::setValue("active_packet", emscripten::val(rand()));
    } catch (...) {
    }
  }

  if (IsKeyReleased(KeyboardKey::KEY_T)) {
    try {
      bind::setValue("active_packet", nlohmann::json({"hello", "ello"}));
    } catch (...) {
    }
  }

  if (IsKeyReleased(KeyboardKey::KEY_X)) {
#ifdef EMSCRIPTEN
    emscripten::val::global("window").call<void>("showAlert", std::string("Aplikacja niespodziewanie zamknięta :("),
                                                 true);
#else
    std::exit(-1);
#endif
  }
}

}  // namespace janowski::paczki_cpp::ui