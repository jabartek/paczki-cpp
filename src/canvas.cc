#include "camera.h"
#include "math/vector2.h"
#include "math/vector3.h"
#include "raymath.h"
#include "schema/box_pos.h"
#include "ui/keyboard.h"

#include <cmath>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <limits>
#include <string>

#include <nlohmann/json.hpp>
#include <raylib.h>

using json = nlohmann::json;
using JCamera = janowski::paczki_cpp::Camera;

#ifdef EMSCRIPTEN

#include <emscripten.h>
#include <emscripten/val.h>

extern "C" {
const char *DOM_CANVAS_ID_FULL = "#canvas_test";
}

EM_JS(char *, get_color, (), {
  let jsString = color();
  let lengthBytes = lengthBytesUTF8(jsString) + 1;
  let stringOnWasmHeap = _malloc(lengthBytes);
  stringToUTF8(jsString, stringOnWasmHeap, lengthBytes);
  return stringOnWasmHeap;
});

EM_JS(char *, get_active_packet, (), {
  let jsString = activePacket();
  let lengthBytes = lengthBytesUTF8(jsString) + 1;
  let stringOnWasmHeap = _malloc(lengthBytes);
  stringToUTF8(jsString, stringOnWasmHeap, lengthBytes);
  return stringOnWasmHeap;
});

#else

char *get_color() {
  auto color = reinterpret_cast<char *>(calloc(1, 1));
  return color;
}

char *get_active_packet() {
  auto color = reinterpret_cast<char *>(calloc(1, 1));
  return color;
}

#endif

using namespace janowski::paczki_cpp;
namespace janowski::paczki_cpp::canvas {

class Cube {
public:
  ::BoundingBox bounding_box() const {
    return {
        .min = position,
        .max = position + size,
    };
  }

  void draw() const {
    DrawCube(position + size * 0.5f, size.x, size.y, size.z, color);
  }

  ::Vector3 position;
  ::Vector3 size;
  ::Color color;
};
} // namespace janowski::paczki_cpp::canvas

int main() {
  std::optional<schema::BoxPos> box_opt;
  const int screenWidth = 800;
  const int screenHeight = 450;
  SetConfigFlags(FLAG_WINDOW_RESIZABLE bitor FLAG_VSYNC_HINT bitor
                 FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "Canvas Test");
  std::string last_box{"{}"};
  // Camera3D camera;
  // camera.up = {0.f, 1.f, 0.f};
  // camera.fovy = 45.f;
  // camera.projection = ::CameraProjection::CAMERA_PERSPECTIVE;
  // camera.target = ::Vector3{0.f, 0.f, 0.f};
  // camera.position = ::Vector3{50.f, 50.f, 50.f};
  // SetCameraMode(camera, ::CameraMode::CAMERA_CUSTOM);

  JCamera camera({0.f, 0.f, 0.f}, 50.f, 0.f, atanf(1), 45.f);

  ::Vector3 cursor_pos{0.f, 0.f, 0.f};

  bool is_cursor_dragged{false};
  enum class LastCube { X, Y, Z, None = -1 };
  LastCube last_cube = LastCube::None;
  while (!WindowShouldClose()) {
    ui::handleKeyboard(camera);
    BeginDrawing();
    ClearBackground(RAYWHITE);
    auto text = get_active_packet();
    DrawText(text, 200, 300, 20, RED);
    if (std::string json_text(text); json_text != last_box) {
      std::swap(last_box, json_text);
    }
    {
      auto packet_json = json::parse(last_box);
      auto coordinates = packet_json["coordinates"];
      auto size = packet_json["size"];
      if (!coordinates.empty() && !size.empty()) {
        DrawRectangle(
            coordinates["x"].get<int>() / 10, coordinates["y"].get<int>() / 10,
            size["x"].get<int>() / 10, size["y"].get<int>() / 10, RED);
      }
    }
    free(text);
    DrawFPS(100, 100);
    DrawFPS(150, 100);
    BeginMode3D(*camera);
    DrawGrid(10, 10.f);
    using janowski::paczki_cpp::canvas::Cube;
    Cube cube_zero{
        .position = cursor_pos + ::Vector3{-.1f, -.1f, -.1f},
        .size = ::Vector3{.7f, .7f, .7f},
        .color = WHITE,
    };
    Cube cube_x{
        .position = cursor_pos,
        .size = {3.f, .5f, .5f},
        .color = RED,
    };
    Cube cube_y{
        .position = cursor_pos,
        .size = {.5f, 3.f, .5f},
        .color = GREEN,
    };
    Cube cube_z{
        .position = cursor_pos,
        .size = {.5f, .5f, 3.f},
        .color = BLUE,
    };
    cube_x.draw();
    cube_y.draw();
    cube_z.draw();
    cube_zero.draw();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      auto ray = GetMouseRay(GetMousePosition(), *camera);
      Cube *hit_cube = nullptr;
      RayCollision collision =
          GetRayCollisionBox(ray, cube_zero.bounding_box());
      if (!collision.hit) {
        collision.distance = std::numeric_limits<float>::max();
      }
      {
        auto collision_x = GetRayCollisionBox(ray, cube_x.bounding_box());
        if (collision_x.hit) {
          std::cout << "Hit X!\n";
          if (collision_x.distance < collision.distance) {
            hit_cube = &cube_x;
            collision = collision_x;
          }
        }
      }
      {
        auto collision_y = GetRayCollisionBox(ray, cube_y.bounding_box());
        if (collision_y.hit) {
          std::cout << "Hit Y!\n";
          if (collision_y.distance < collision.distance) {
            hit_cube = &cube_y;
            collision = collision_y;
          }
        }
      }
      {
        auto collision_z = GetRayCollisionBox(ray, cube_z.bounding_box());
        if (collision_z.hit) {
          std::cout << "Hit Z!\n";
          if (collision_z.distance < collision.distance) {
            hit_cube = &cube_z;
            collision = collision_z;
          }
        }
      }
      if (hit_cube) {
        is_cursor_dragged = true;
      }
      if (is_cursor_dragged) {
        switch (last_cube) {
        case LastCube::X:
          hit_cube = &cube_x;
          break;
        case LastCube::Y:
          hit_cube = &cube_y;
          break;
        case LastCube::Z:
          hit_cube = &cube_z;
          break;
        default:
          break;
        }
      }
      if (is_cursor_dragged) {
        auto delta = GetMouseDelta();
        auto ray_before =
            GetMouseRay(GetMousePosition() + delta * -1.f, *camera);
        auto pos = ::Vector3{0.f, 0.f, 0.f};
        ::Vector3 p1 = pos + ::Vector3{-1000.f, -1000.f, 0.f};
        ::Vector3 p2 = pos + ::Vector3{-1000.f, 1000.f, 0.f};
        ::Vector3 p3 = pos + ::Vector3{1000.f, 1000.f, 0.f};
        ::Vector3 p4 = pos + ::Vector3{1000.f, -1000.f, 0.f};
        ::Vector3 p1z = pos + ::Vector3{-1000.f, 0.f, -1000.f};
        ::Vector3 p2z = pos + ::Vector3{-1000.f, 0.f, 1000.f};
        ::Vector3 p3z = pos + ::Vector3{1000.f, 0.f, 1000.f};
        ::Vector3 p4z = pos + ::Vector3{1000.f, 0.f, -1000.f};
        auto col = GetRayCollisionQuad(ray, cursor_pos + p1, cursor_pos + p2,
                                       cursor_pos + p3, cursor_pos + p4);
        auto col_before =
            GetRayCollisionQuad(ray_before, cursor_pos + p1, cursor_pos + p2,
                                cursor_pos + p3, cursor_pos + p4);
        auto col_z =
            GetRayCollisionQuad(ray, cursor_pos + p1z, cursor_pos + p2z,
                                cursor_pos + p3z, cursor_pos + p4z);
        auto col_before_z =
            GetRayCollisionQuad(ray_before, cursor_pos + p1z, cursor_pos + p2z,
                                cursor_pos + p3z, cursor_pos + p4z);
        if (hit_cube == &cube_x) {
          last_cube = LastCube::X;
          cursor_pos = cursor_pos + ::Vector3{
                                        col.point.x - col_before.point.x,
                                        0.f,
                                        0.f,
                                    };
        } else if (hit_cube == &cube_y) {
          last_cube = LastCube::Y;
          cursor_pos = cursor_pos + ::Vector3{
                                        0.f,
                                        col.point.y - col_before.point.y,
                                        0.f,
                                    };
        } else if (hit_cube == &cube_z) {
          last_cube = LastCube::Z;
          cursor_pos = cursor_pos + ::Vector3{
                                        0.f,
                                        0.f,
                                        col_z.point.z - col_before_z.point.z,
                                    };
          std::cout << "Col Z point:\t" << col_z.point.x << "\t"
                    << col_z.point.y << "\t" << col_z.point.z << "\t\n";
        }
      }
    } else {
      last_cube = LastCube::None;
      is_cursor_dragged = false;
    }
    EndMode3D();
    EndDrawing();
  }
  RLCloseWindow();
}