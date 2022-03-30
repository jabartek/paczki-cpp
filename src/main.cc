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
#include <unordered_map>
#include <vector>

#include "bind/bind.h"
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

#include <emscripten.h>
#include <emscripten/val.h>

extern "C" {
const char* DOM_CANVAS_ID_FULL = "#paczki_view";
}

EM_JS(void, paczka_init, (), {
  Paczka = {};
  Paczka["color"] = "#ffffff";
  newDiv = document.createElement("div");
  newDiv.id = "kolorek";
  newDiv.style.width = "100px";
  newDiv.style.height = "100px";
  document.body.insertBefore(newDiv, document.getElementById("output"));
});

#else

void paczka_init() {}

#endif  // EMSCRIPTEN

struct Main {
  std::optional<std::string> last_color;
  bool last_color_changed = false;
};

int main() {
  auto state_ptr = std::make_shared<State>();
  ui::HandlerStore handlers(state_ptr);
  auto& state = *state_ptr;
  state.window_width = 800;
  state.window_height = 450;
  state.pallet_view.emplace();
  state.camera.emplace(::Vector3{0.f, 0.f, 0.f}, 50.f, 0.f, atanf(1), 45.f);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE bitor FLAG_VSYNC_HINT bitor
                 FLAG_MSAA_4X_HINT);
  InitWindow(state.window_width, state.window_height, "Paczki C++");

  ui::Rotator rotator(makeVector2(GetScreenWidth() - 70, 70), 50);
  JCamera& camera = *state.camera;


  Ray ray{};

  Vector3 g0 = {-50.0f, 0.0f, -50.0f};
  Vector3 g1 = {-50.0f, 0.0f, 50.0f};
  Vector3 g2 = {50.0f, 0.0f, 50.0f};
  Vector3 g3 = {50.0f, 0.0f, -50.0f};

  // SetTargetFPS(60);

  paczka_init();

  bool skip_frame{false};

  while (skip_frame || !WindowShouldClose()) {
    ::SetWindowSize(state.window_width, state.window_height);
    handlers.handleAll();
    skip_frame = false;
    // UpdateCamera(&camera);

    RayCollision collision{};
    std::string hitObjectName("None");
    collision.distance = std::numeric_limits<float>::max();
    collision.hit = false;
    Color cursorColor = WHITE;

    ray = GetMouseRay(GetMousePosition(), *camera);

    RayCollision groundHitInfo = GetRayCollisionQuad(ray, g0, g1, g2, g3);

    if ((groundHitInfo.hit) && (groundHitInfo.distance < collision.distance)) {
      collision = groundHitInfo;
      cursorColor = GREEN;
      hitObjectName = "Ground";
    }

    if (auto& data = state_ptr->data; data) {
      for (auto& [id, box_pos] : data->box_positions()) {
        auto& box_type = data->box_types().at(box_pos.box_type_id());
        RayCollision cube_hit_info = GetRayCollisionBox(
            ray, {(graphics::getPosition(box_pos) * graphics::kSizeMultiplier),
                  ((graphics::getPosition(box_pos) +
                    graphics::getSize(box_pos, box_type)) *
                   graphics::kSizeMultiplier)});
        if (cube_hit_info.hit && cube_hit_info.distance < collision.distance) {
          collision = cube_hit_info;
          const auto& box_color = state_ptr->color_map
                                      ? state_ptr->color_map->at(box_pos.id())
                                      : makeColor(0u, 0u, 0u);
          cursorColor = makeColor(box_color.r, box_color.g, box_color.b);
          hitObjectName = box_pos.id();
        }
      }
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      rotator.handleClick(GetMousePosition(), camera);
    }
    if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);
    {
      rendering::Mode3D frame(&camera);

      state.pallet_view->draw(frame);

      if (collision.hit) {
        DrawCube(collision.point, 0.3f, 0.3f, 0.3f, cursorColor);
        DrawCubeWires(collision.point, 0.3f, 0.3f, 0.3f, RED);
        auto normalEnd = collision.point + collision.normal;
        DrawLine3D(collision.point, normalEnd, RED);
      }
      if (!(hitObjectName == "Ground" || hitObjectName == "None")) {
        graphics::drawBoxOutline(
            *state_ptr->data,
            state_ptr->data->box_positions().at(hitObjectName),
            state_ptr->color_map->at(hitObjectName));
      }

      DrawRay(ray, MAROON);

      DrawGrid(1000, 5.0f);
    }

    // DrawText(TextFormat("Hit Object: %s", hitObjectName.c_str()), 10, 50, 10,
    // BLACK);

    if (collision.hit) {
      int ypos = 50;

      if (!(hitObjectName == "Ground" || hitObjectName == "None")) {
        DrawText(TextFormat("Box Type: %d",
                            std::stoi(state_ptr->data->box_positions()
                                          .at(hitObjectName)
                                          .box_type_id())),
                 10, ypos += 15, 10, BLACK);
        DrawText(
            TextFormat("Items: %d", state_ptr->data->box_types()
                                        .at(state_ptr->data->box_positions()
                                                .at(hitObjectName)
                                                .box_type_id())
                                        .items()
                                        .size()),
            10, ypos += 15, 10, BLACK);
      }

      ypos += 150;

      DrawText(TextFormat("Distance: %3.2f", collision.distance), 10, ypos, 10,
               BLACK);

      DrawText(TextFormat("Hit Pos: %3.2f %3.2f %3.2f", collision.point.x,
                          collision.point.y, collision.point.z),
               10, ypos + 15, 10, BLACK);

      DrawText(TextFormat("Hit Norm: %3.2f %3.2f %3.2f", collision.normal.x,
                          collision.normal.y, collision.normal.z),
               10, ypos + 30, 10, BLACK);
    }

    // DrawFPS(10, 10);
    rotator.draw();
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
        std::cout << image_png << "\n";

        UnloadImage(screenshot);
      }
      last_b = now;
      skip_frame = true;
      auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now() - now);
      std::cout << "Total time: " << elapsed.count() << "ms\n";
    }
  }

  RLCloseWindow();

  return 0;
}