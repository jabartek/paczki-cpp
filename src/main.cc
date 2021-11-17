#include <iterator>
#include <raylib.h>
#include <raymath.h>

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <list>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>

#include "box/definition.h"
#include "box/instance.h"
#include "box/list.h"
#include "camera.h"
#include "graphics/box.h"
#include "json_utils.h"
#include "math/vector3.h"
#include "ui/keyboard.h"


using namespace janowski::paczki_cpp;
using json = nlohmann::json;
using JCamera = janowski::paczki_cpp::Camera;

int main() {
  box::List cubes;

  const int screenWidth = 800;
  const int screenHeight = 450;
  SetConfigFlags(FLAG_WINDOW_RESIZABLE bitor FLAG_VSYNC_HINT bitor
                 FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "Paczki C++");

  JCamera camera({0.f, 0.f, 0.f}, 50.f, 0.f, atanf(1), 45.f);

  Ray ray = {0};

  Vector3 g0 = {-50.0f, 0.0f, -50.0f};
  Vector3 g1 = {-50.0f, 0.0f, 50.0f};
  Vector3 g2 = {50.0f, 0.0f, 50.0f};
  Vector3 g3 = {50.0f, 0.0f, -50.0f};

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // UpdateCamera(&camera);

    RayCollision collision{};
    std::string hitObjectName("None");
    collision.distance = std::numeric_limits<float>::max();
    collision.hit = false;
    Color cursorColor = WHITE;

    ray = GetMouseRay(GetMousePosition(), camera.get());

    RayCollision groundHitInfo = GetRayCollisionQuad(ray, g0, g1, g2, g3);

    if ((groundHitInfo.hit) && (groundHitInfo.distance < collision.distance)) {
      collision = groundHitInfo;
      cursorColor = GREEN;
      hitObjectName = "Ground";
    }

    std::optional<decltype(cubes.instances().begin())> hit_box{};

    for (auto box = cubes.instances().begin(); box != cubes.instances().end(); box++) {
      RayCollision cube_hit_info = GetRayCollisionBox(
          ray,
          {rayvec(box->position() * graphics::kSizeMultiplier),
           rayvec((box->position() + box->size()) * graphics::kSizeMultiplier)});
      if (cube_hit_info.hit && cube_hit_info.distance < collision.distance) {
        collision = cube_hit_info;
        const auto& box_color = box->color();
        cursorColor = {box_color.x, box_color.y, box_color.z, 255u};
        hitObjectName = "Paczka " + std::to_string(std::distance(cubes.instances().begin(), box));
        hit_box = box;
      }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && hit_box) {
       cubes.instances().erase(*hit_box);
    }

    if (IsFileDropped()) {
      int file_count{};
      auto file_names_ptr = GetDroppedFiles(&file_count);
      std::vector<std::string> file_names{};
      for (auto i = 0; i < file_count; ++i) {
        file_names.emplace_back(file_names_ptr[i]);
      }
      ClearDroppedFiles();
      cubes = box::List(loadJson(file_names.front()));
      camera.set_target(
          {(cubes.x_min() + cubes.x_max()) / 2.f * graphics::kSizeMultiplier,
           (cubes.y_min() + cubes.y_max()) / 2.f * graphics::kSizeMultiplier,
           (cubes.z_min() + cubes.z_max()) / 2.f * graphics::kSizeMultiplier});
      camera.updateCamera();
    }

    ui::handleKeyboard(camera);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera.get());

    for (auto& cube : cubes.instances()) {
      graphics::drawBox(cube);
    }

    if (collision.hit) {
      DrawCube(collision.point, 0.3f, 0.3f, 0.3f, cursorColor);
      DrawCubeWires(collision.point, 0.3f, 0.3f, 0.3f, RED);

      Vector3 normalEnd;
      normalEnd.x = collision.point.x + collision.normal.x;
      normalEnd.y = collision.point.y + collision.normal.y;
      normalEnd.z = collision.point.z + collision.normal.z;

      DrawLine3D(collision.point, normalEnd, RED);
    }
    if (hitObjectName.starts_with("Paczka") && hit_box) {
      graphics::drawBoxOutline(**hit_box);
    }

    DrawRay(ray, MAROON);

    DrawGrid(10, 10.0f);

    EndMode3D();

    DrawText(TextFormat("Hit Object: %s", hitObjectName.c_str()), 10, 50, 10,
             BLACK);

    if (collision.hit) {
      int ypos = 70;

      DrawText(TextFormat("Distance: %3.2f", collision.distance), 10, ypos, 10,
               BLACK);

      DrawText(TextFormat("Hit Pos: %3.2f %3.2f %3.2f", collision.point.x,
                          collision.point.y, collision.point.z),
               10, ypos + 15, 10, BLACK);

      DrawText(TextFormat("Hit Norm: %3.2f %3.2f %3.2f", collision.normal.x,
                          collision.normal.y, collision.normal.z),
               10, ypos + 30, 10, BLACK);
    }

    DrawFPS(10, 10);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}