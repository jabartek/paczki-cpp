#include <raylib.h>
#include <raymath.h>

#include <algorithm>
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

using namespace janowski::paczki_cpp;
using json = nlohmann::json;
using JCamera = janowski::paczki_cpp::Camera;

int main() {
  box::List cubes;

  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Paczki C++");

  JCamera camera({0.f, 0.f, 0.f}, 50.f, 0.f, std::atanf(1), 45.f);

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

    // CubeCC *hitCube(nullptr);
    // std::list<CubeCC>::iterator hitCubeIt;
    // for (auto it = cubes.begin(); it != cubes.end(); ++it) {
    //   auto &cube = *it;
    //   RayCollision cubeHitInfo =
    //       GetRayCollisionBox(ray, {cube.pos, plus(cube.pos, cube.size)});
    //   if ((cubeHitInfo.hit) && (cubeHitInfo.distance < collision.distance)) {
    //     collision = cubeHitInfo;
    //     cursorColor = cube.color;
    //     hitObjectName = "Klocek";
    //     hitCube = &cube;
    //     hitCubeIt = it;
    //   }
    // }

    // if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && hitCube) {
    //   cubes.erase(hitCubeIt);
    // }

    if (IsFileDropped()) {
      int file_count{};
      auto file_names_ptr = GetDroppedFiles(&file_count);
      std::vector<std::string> file_names{};
      for (auto i = 0; i < file_count; ++i) {
        file_names.emplace_back(file_names_ptr[i]);
      }
      ClearDroppedFiles();
      cubes = box::List(loadJson(file_names.front()));
      // cubes = getCubes(file_names.front());
    }

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

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera.get());

    for (auto &cube : cubes.instances()) {
      DrawCube(rayvec((cube.position() + (cube.size() * 0.5f)) * 0.01f),
               cube.size().x() * 0.01f, cube.size().y() * 0.01f,
               cube.size().z() * 0.01f,
               {cube.color().x(), cube.color().y(), cube.color().z(), 255u});
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
    // if (hitObjectName == "Klocek") {
    //   DrawCubeWires(plus((*hitCube).pos, mul((*hitCube).size, 0.5f)),
    //                 (*hitCube).size.x, (*hitCube).size.y, (*hitCube).size.z,
    //                 {static_cast<uint8_t>(255u - (*hitCube).color.r),
    //                  static_cast<uint8_t>(255u - (*hitCube).color.g),
    //                  static_cast<uint8_t>(255u - (*hitCube).color.b),
    //                  (*hitCube).color.a});
    // }

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