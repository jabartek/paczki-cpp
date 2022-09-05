#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <exception>
#include <filesystem>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <nlohmann/json.hpp>
#include <optional>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "bind/bind.h"
#include "bind/stores.h"
#include "colors.h"
#include "graphics/box.h"
#include "json_utils.h"
#include "lib/raylib_clean.h"
#include "math/color.h"
#include "math/vector3.h"
#include "misc.h"
#include "pallet_viewer/state.h"
#include "raylib.h"
#include "rendering/camera.h"
#include "rendering/mode_3d.h"
#include "schema/data.h"
#include "ui/cursor_3d.h"
#include "ui/handlers.h"
#include "ui/pallet_view.h"
#include "ui/rotator.h"
#include "utils/png.h"

using namespace janowski::paczki_cpp;
using namespace janowski::paczki_cpp::math;
using namespace janowski::paczki_cpp::pallet_viewer;
using JCamera = janowski::paczki_cpp::rendering::Camera;

#ifdef EMSCRIPTEN

#include "lib/emscripten_wrapper.h"

#endif

std::shared_ptr<State> state_ptr{nullptr};

void alertMessage() {
  std::string text = "Alert!!";
  int ms_display = 10000;
  if (!state_ptr) return;
  state_ptr->alert = {text, std::chrono::system_clock::now() + std::chrono::milliseconds(ms_display)};
}

#ifdef EMSCRIPTEN
EMSCRIPTEN_BINDINGS(paczki_plusplus_alertMessage) { emscripten::function("alertMessage", &alertMessage); };

EMSCRIPTEN_BINDINGS(paczki_plusplus_addStore) { emscripten::function("addStore", &bind::addStore); };
EMSCRIPTEN_BINDINGS(paczki_plusplus_callUpdate) { emscripten::function("callUpdate", &bind::callUpdate); };
EMSCRIPTEN_BINDINGS(paczki_plusplus_call) { emscripten::function("call", &bind::call); };
EMSCRIPTEN_BINDINGS(paczki_plusplus_setGet) { emscripten::function("setGet", &bind::setGet); };
#endif

void mainLoop() {
  try {
    auto& state = *state_ptr;
    auto& handlers = state.handler_store;
    JCamera& camera = *state.camera;
    ::SetWindowSize(state.window_width, state.window_height);
    const auto time_now = std::chrono::system_clock::now();
    handlers->handleAll();

    const auto mouse_pos = GetMousePosition();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      if (!state.left_button_start) state.left_button_start = time_now;
      if (time_now - *state.left_button_start > ui::kMaxClickLength) {
        
        for (auto& touchable : state.touchables) {
          if (!touchable->isOver(mouse_pos)) continue;
          touchable->leftPress(mouse_pos);
        }

        if (state.pallet_view) {
          state.pallet_view->leftPress(mouse_pos);
        }
      }
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
      if (!state.right_button_start) state.right_button_start = time_now;
      if (time_now - *state.right_button_start > ui::kMaxClickLength) {
        
        for (auto& touchable : state.touchables) {
          if (!touchable->isOver(mouse_pos)) continue;
          touchable->rightPress(mouse_pos);
        }
      }
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      if (!state.left_button_start) state.left_button_start = time_now;
      if (time_now - *state.left_button_start <= ui::kMaxClickLength) {
        
        for (auto& touchable : state.touchables) {
          if (!touchable->isOver(mouse_pos)) continue;
          touchable->leftClick(mouse_pos);
        }

        if (state.pallet_view) {
          state.pallet_view->leftClick(mouse_pos);
        }
      } else {
        for (auto& touchable : state.touchables) {
          if (!touchable->isOver(mouse_pos)) continue;
          touchable->leftRelease(mouse_pos);
        }
        if (state.pallet_view) {
          state.pallet_view->leftRelease(mouse_pos);
        }
      }
      state.left_button_start.reset();
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
      if (!state.right_button_start) state.right_button_start = time_now;
      if (time_now - *state.right_button_start <= ui::kMaxClickLength) {
        
        for (auto& touchable : state.touchables) {
          if (!touchable->isOver(mouse_pos)) continue;
          touchable->rightClick(mouse_pos);
        }
        if (state.pallet_view) {
          state.pallet_view->rightClick(mouse_pos);
        }
      } else {
        for (auto& touchable : state.touchables) {
          if (!touchable->isOver(mouse_pos)) continue;
          touchable->rightRelease(mouse_pos);
        }
        if (state.pallet_view) {
          state.pallet_view->rightRelease(mouse_pos);
        }
      }
      state.right_button_start.reset();
    }
    for (auto& touchable : state.touchables) {
      if (!touchable->isOver(mouse_pos)) continue;
      touchable->hover(mouse_pos);
    }
    if (state.pallet_view) {
      state.pallet_view->hover(mouse_pos);
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    {
      rendering::Mode3D frame(&camera);

      if (state.pallet_view) state.pallet_view->draw();

      DrawGrid(1000, 2.0f);
    }

    for (auto& touchable : state.touchables) {
      touchable->draw();
    }
    if (state.alert) {
      state.update();
      DrawText(state.alert->text.c_str(), 20, 20, 20, colors::MAROON1_C);
    }

    EndDrawing();
  } catch (const std::exception& e) {
#ifdef EMSCRIPTEN
    emscripten::val::global("window").call<void>("showAlert", std::string(e.what()));
#else
    std::cerr << e.what() << std::endl;
#endif
  }
}

int main() {
  state_ptr = std::make_shared<State>();
  auto& state = *state_ptr;
  state.window_width = 1200;
  state.window_height = 800;
  SetConfigFlags(FLAG_VSYNC_HINT bitor FLAG_MSAA_4X_HINT);
  InitWindow(state.window_width, state.window_height, "Paczki C++");
  state_ptr->handler_store.emplace(state_ptr);
  state.camera.emplace(::Vector3{0.f, 0.f, 0.f}, 50.f, 0.f, atanf(1), 45.f);

  state.touchables.emplace_back(
      std::make_unique<ui::Rotator>(Vector2{.x = state.window_width - 70.f, .y = 70.f}, 50, state_ptr));
  // state.touchables.emplace_back(std::make_unique<ui::Cursor3D>(state_ptr));
#ifdef EMSCRIPTEN
  emscripten_set_main_loop(mainLoop, 0, 1);
#else
  while (!WindowShouldClose()) {
    mainLoop();
  }
#endif
  RLCloseWindow();

  return 0;
}