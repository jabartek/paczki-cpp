#include "box_def.h"
#include "camera.h"
#include "json_loader.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

#include <nlohmann/json.hpp>
#include <raylib.h>
#include <raymath.h>

using janowski::paczki_cpp::BoxDef;
using janowski::paczki_cpp::Camera;
using json = nlohmann::json;

struct CubeCC {
  Vector3 pos;
  Vector3 size;
  Color color;
};

std::list<CubeCC> getCubes(const std::string &json_file_path) {
  auto data = janowski::paczki_cpp::jsonFromFile(json_file_path);

  std::unordered_map<int, BoxDef> box_types;

  for (auto i : data["BoxTypes"]) {
    auto box_id = std::stoi(i["$id"].get<std::string>());
    box_types[box_id] = {
        box_id,
        i["SizeX"].get<float>() / 100.f,
        i["SizeZ"].get<float>() / 100.f,
        i["SizeY"].get<float>() / 100.f,
    };
  }

  for (auto &[key, value] : box_types) {
    std::cout << value.ref << "\t" << value.x_size << "\t" << value.y_size
              << "\t" << value.z_size << std::endl;
  }
  for (auto i = 0; i < 1000; ++i) {
    if (!box_types.contains(i))
      continue;
    std::cout << i << std::endl;
  }

  srand(static_cast<unsigned int>(time(nullptr)));

  std::list<CubeCC> cubes;
  for (auto i : data["Pallets"][0]["BoxPos"]) {
    auto item1 = i["Item1"];
    auto ref = std::stoi(item1["$ref"].get<std::string>());
    auto item2 = i["Item2"];
    std::cout << "Ref:\t" << ref << "\t"
              << "X: " << item2["X"].get<float>() << "\t"
              << "Y: " << item2["Y"].get<float>() << "\t"
              << "Z: " << item2["Z"].get<float>() << std::endl;
    CubeCC cube;
    cube.pos = {item2["X"].get<float>() / 100.f,
                item2["Z"].get<float>() / 100.f,
                item2["Y"].get<float>() / 100.f};
    if (item2["Rotated"].get<bool>()) {
      cube.size = {box_types[ref].z_size, box_types[ref].y_size,
                   box_types[ref].x_size};
    } else {
      cube.size = {box_types[ref].x_size, box_types[ref].y_size,
                   box_types[ref].z_size};
    }
    cube.color = {static_cast<uint8_t>(rand() % 256),
                  static_cast<uint8_t>(rand() % 256),
                  static_cast<uint8_t>(rand() % 256), 255};
    cubes.push_back(cube);
  }
  return cubes;
}

int main() {
  std::list<CubeCC> cubes;

  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Paczki C++");

  Camera camera({0.f, 0.f, 0.f}, 50.f, 0.f, std::atanf(1), 45.f);

  Ray ray = {0};

  Vector3 g0 = {-50.0f, 0.0f, -50.0f};
  Vector3 g1 = {-50.0f, 0.0f, 50.0f};
  Vector3 g2 = {50.0f, 0.0f, 50.0f};
  Vector3 g3 = {50.0f, 0.0f, -50.0f};

  SetTargetFPS(60);

  auto mul = [](const Vector3 &vecs, auto f) -> Vector3 {
    Vector3 vec;
    vec.x = vecs.x * f;
    vec.y = vecs.y * f;
    vec.z = vecs.z * f;
    return vec;
  };

  auto plus = [](const Vector3 &vec1, const Vector3 &vec2) -> Vector3 {
    Vector3 vec;
    vec.x = vec1.x + vec2.x;
    vec.y = vec1.y + vec2.y;
    vec.z = vec1.z + vec2.z;
    return vec;
  };

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

    CubeCC *hitCube(nullptr);
    std::list<CubeCC>::iterator hitCubeIt;
    for (auto it = cubes.begin(); it != cubes.end(); ++it) {
      auto &cube = *it;
      RayCollision cubeHitInfo =
          GetRayCollisionBox(ray, {cube.pos, plus(cube.pos, cube.size)});
      if ((cubeHitInfo.hit) && (cubeHitInfo.distance < collision.distance)) {
        collision = cubeHitInfo;
        cursorColor = cube.color;
        hitObjectName = "Klocek";
        hitCube = &cube;
        hitCubeIt = it;
      }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && hitCube) {
      cubes.erase(hitCubeIt);
    }

    if (IsFileDropped()) {
      int file_count{};
      auto file_names_ptr = GetDroppedFiles(&file_count);
      std::vector<std::string> file_names{};
      for (auto i = 0; i < file_count; ++i) {
        file_names.emplace_back(file_names_ptr[i]);
      }
      ClearDroppedFiles();
      cubes = getCubes(file_names.front());
    }

    if (IsKeyDown(KeyboardKey::KEY_W)) {
      camera.rotate(Camera::Direction::UP, 0.05f);
    }
    if (IsKeyDown(KeyboardKey::KEY_S)) {
      camera.rotate(Camera::Direction::DOWN, 0.05f);
    }
    if (IsKeyDown(KeyboardKey::KEY_A)) {
      camera.rotate(Camera::Direction::LEFT, 0.05f);
    }
    if (IsKeyDown(KeyboardKey::KEY_D)) {
      camera.rotate(Camera::Direction::RIGHT, 0.05f);
    }
    if (IsKeyDown(KeyboardKey::KEY_UP)) {
      camera.zoom(Camera::Zoom::IN);
    }
    if (IsKeyDown(KeyboardKey::KEY_DOWN)) {
      camera.zoom(Camera::Zoom::OUT);
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera.get());

    for (auto &cube : cubes) {
      DrawCube(plus(cube.pos, mul(cube.size, 0.5f)), cube.size.x, cube.size.y,
               cube.size.z, cube.color);
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
    if (hitObjectName == "Klocek") {
      DrawCubeWires(plus((*hitCube).pos, mul((*hitCube).size, 0.5f)),
                    (*hitCube).size.x, (*hitCube).size.y, (*hitCube).size.z,
                    {static_cast<uint8_t>(255u - (*hitCube).color.r),
                     static_cast<uint8_t>(255u - (*hitCube).color.g),
                     static_cast<uint8_t>(255u - (*hitCube).color.b),
                     (*hitCube).color.a});
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