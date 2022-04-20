#include "ui/handlers.h"

#include <bind/bind.h>
#include <raylib.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>

#include "bind/stores.h"
#include "colors.h"
#include "graphics/box.h"
#include "pallet_viewer/state.h"

#ifdef EMSCRIPTEN
#include <emscripten/val.h>
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
  state_ptr->pallet_view.emplace(state_ptr->data, state_ptr);
  if (auto& camera = state_ptr->camera) {
    camera->set_target(state_ptr->data->dimensions() * 0.5f * graphics::kSizeMultiplier);
    camera->updateCamera();
  }
  state_ptr->color_map = schema::Data::ColorMap{};
  for (auto& pallet : state_ptr->data->pallets()) {
    for (auto& [id, box_pos] : state_ptr->data->box_positions(pallet)) {
      state_ptr->color_map->emplace(id, colors::kColors[rand() % colors::kColors.size()]);
    }
  }
  // #ifdef EMSCRIPTEN
  //   nlohmann::json sku_list;
  //   for (auto& sku : state_ptr->data->skus()) {
  //     sku_list[sku.first] = sku.second.json();
  //   }

  //   bind::call("setSkuList", sku_list);

  //   auto palletIdList = nlohmann::json(state_ptr->data->pallets());
  //   bind::call("setPalletIdList", palletIdList);

  //   nlohmann::json box_type_list;
  //   for (auto& box_type : state_ptr->data->box_types()) {
  //     box_type_list[box_type.first] = box_type.second.json();
  //   }
  //   auto set_box_type_list = emscripten::val::global("setBoxTypeList");
  //   auto set_box_type_list_result = set_box_type_list(box_type_list.dump());
  // #endif
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

bool DropHandler::pred(std::shared_ptr<pallet_viewer::State> /*state_ptr*/) { return ::IsFileDropped(); }
void DropHandler::func(std::shared_ptr<pallet_viewer::State> state_ptr) {
  std::cout << "File dropped" << std::endl;
  int file_count{};
  auto file_names_ptr = GetDroppedFiles(&file_count);
  std::vector<std::string> file_names{};
  for (auto i = 0; i < file_count; ++i) {
    file_names.emplace_back(file_names_ptr[i]);
  }
  ClearDroppedFiles();

  loadFile(file_names.front(), state_ptr);
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
    state_ptr->color_scheme = state_ptr->color_scheme == pallet_viewer::State::ColorScheme::kByBoxPos
                                  ? pallet_viewer::State::ColorScheme::kByBoxType
                                  : pallet_viewer::State::ColorScheme::kByBoxPos;
  }
  if (IsKeyReleased(KeyboardKey::KEY_P)) {
    std::cout << "test.json opening" << std::endl;
    loadFile("test.json", state_ptr);
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
}

}  // namespace janowski::paczki_cpp::ui