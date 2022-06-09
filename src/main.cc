#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
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
  auto& state = *state_ptr;
  if (state.skip_frame) return;
  auto& skip_frame = state.skip_frame;
  auto& handlers = state.handler_store;
  JCamera& camera = *state.camera;
  ::SetWindowSize(state.window_width, state.window_height);
  handlers->handleAll();
  skip_frame = false;
  // UpdateCamera(&camera);

  RayCollision collision{};
  std::string hitObjectName("None");
  collision.distance = std::numeric_limits<float>::max();
  collision.hit = false;
  Color cursorColor = WHITE;

  auto ray = GetMouseRay(GetMousePosition(), *camera);

  RayCollision groundHitInfo =
      GetRayCollisionQuad(ray, {.x = -50.f, .y = 0.f, .z = -50.f}, {.x = 50.f, .y = 0.f, .z = -50.f},
                          {.x = 50.f, .y = 0.f, .z = 50.f}, {.x = -50.f, .y = 0.f, .z = 50.f});

  if ((groundHitInfo.hit) && (groundHitInfo.distance < collision.distance)) {
    collision = groundHitInfo;
    cursorColor = GREEN;
    hitObjectName = "Ground";
  }

  if (auto& data = state_ptr->data; data && state.pallet_view && state.pallet_view->active_pallet()) {
    for (auto& [id, box_pos] : data->box_positions(*state.pallet_view->active_pallet())) {
      auto& box_type = data->box_types().at(box_pos.box_type_id());
      RayCollision cube_hit_info = GetRayCollisionBox(
          ray, {(graphics::getPosition(box_pos) * graphics::kSizeMultiplier),
                ((graphics::getPosition(box_pos) + graphics::getSize(box_pos, box_type)) * graphics::kSizeMultiplier)});
      if (cube_hit_info.hit && cube_hit_info.distance < collision.distance) {
        collision = cube_hit_info;
        const auto& box_color = box_pos.color();
        cursorColor = makeColor(box_color.r, box_color.g, box_color.b);
        hitObjectName = box_pos.id();
      }
    }
  }

  {
    static int left_button_lenght{0};
    static int right_button_lenght{0};
    auto mouse_pos = GetMousePosition();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      left_button_lenght++;
      if (left_button_lenght > ui::kMaxClickLength) {
        // rem_std::cout << "Left button pressed at " << mouse_pos.x << "," << mouse_pos.y << "\n";
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
      right_button_lenght++;
      if (right_button_lenght > ui::kMaxClickLength) {
        // rem_std::cout << "Right button pressed at " << mouse_pos.x << "," << mouse_pos.y << "\n";
        for (auto& touchable : state.touchables) {
          if (!touchable->isOver(mouse_pos)) continue;
          touchable->rightPress(mouse_pos);
        }
      }
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      if (left_button_lenght <= ui::kMaxClickLength) {
        // rem_std::cout << "Left button clicked at " << mouse_pos.x << "," << mouse_pos.y << "\n";
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
      left_button_lenght = 0;
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
      if (right_button_lenght <= ui::kMaxClickLength) {
        // rem_std::cout << "Right button clicked at " << mouse_pos.x << "," << mouse_pos.y << "\n";
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
      right_button_lenght = 0;
    }
    for (auto& touchable : state.touchables) {
      if (!touchable->isOver(mouse_pos)) continue;
      touchable->hover(mouse_pos);
    }
  }
  BeginDrawing();
  ClearBackground(RAYWHITE);
  {
    rendering::Mode3D frame(&camera);

    if (state.pallet_view) state.pallet_view->draw();

    if (collision.hit) {
      DrawCube(collision.point, 0.3f, 0.3f, 0.3f, cursorColor);
      DrawCubeWires(collision.point, 0.3f, 0.3f, 0.3f, RED);
      auto normalEnd = collision.point + collision.normal;
      DrawLine3D(collision.point, normalEnd, RED);
    }
    if (!(hitObjectName == "Ground" || hitObjectName == "None") && state.pallet_view &&
        state.pallet_view->active_pallet()) {
      const auto& box_pos = state_ptr->data->box_positions(*state.pallet_view->active_pallet()).at(hitObjectName);
      graphics::drawBoxOutline(*state_ptr->data, box_pos, box_pos.color());
    }

    DrawRay(ray, MAROON);

    DrawGrid(1000, 2.0f);

    for (auto& touchable : state.touchables) {
      touchable->draw();
    }  // TODO
  }

  // DrawText(TextFormat("Hit Object: %s", hitObjectName.c_str()), 10, 50, 10,
  // BLACK);

  if (collision.hit) {
    int ypos = 50;

    if (!(hitObjectName == "Ground" || hitObjectName == "None") && state.pallet_view &&
        state.pallet_view->active_pallet()) {
      const auto& box_pos = state_ptr->data->box_positions(*state.pallet_view->active_pallet()).at(hitObjectName);
      DrawText(TextFormat("Box Id: %d", std::stoi(box_pos.id())), 10, ypos += 15, 10, BLACK);
      DrawText(TextFormat("Box Type id: %s", box_pos.box_type_id().c_str()), 10, ypos += 15, 10, BLACK);
      DrawText(TextFormat("Items: %d", state_ptr->data->box_types().at(box_pos.box_type_id()).items().size()), 10,
               ypos += 15, 10, BLACK);
    }

    ypos += 150;

    DrawText(TextFormat("Distance: %3.2f", collision.distance), 10, ypos, 10, BLACK);

    DrawText(TextFormat("Hit Pos: %3.2f %3.2f %3.2f", collision.point.x, collision.point.y, collision.point.z), 10,
             ypos + 15, 10, BLACK);

    DrawText(TextFormat("Hit Norm: %3.2f %3.2f %3.2f", collision.normal.x, collision.normal.y, collision.normal.z), 10,
             ypos + 30, 10, BLACK);
  }

  // DrawFPS(10, 10);

  if (state.alert) {
    state.update();
    DrawText(state.alert->text.c_str(), 20, 20, 20, colors::MAROON1_C);
  }

  for (auto& touchable : state.touchables) {
    touchable->draw();
  }

  EndDrawing();
  static auto last_b = std::chrono::system_clock::now();
  auto now = std::chrono::system_clock::now();
  if (now - last_b > std::chrono::milliseconds(1000) && IsKeyDown(KEY_B)) {
    ::SetWindowSize(state.window_width, state.window_height);
    for (int i = 10; i < 210; i += 20) {
      DrawFPS(i, i);
      EndDrawing();
      auto screenshot = LoadImageFromScreen();
      auto image_png = utils::toPngBase64(screenshot);
      // rem_std::cout << image_png << "\n";

      UnloadImage(screenshot);
    }
    last_b = now;
    // skip_frame = true;
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - now);
    // rem_std::cout << "Total time: " << elapsed.count() << "ms\n";
  }
}

int main() {
  state_ptr = std::make_shared<State>();
  auto& state = *state_ptr;
  state.window_width = 1200;
  state.window_height = 800;
  InitWindow(state.window_width, state.window_height, "Paczki C++");
  SetConfigFlags(FLAG_VSYNC_HINT bitor FLAG_MSAA_4X_HINT);
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