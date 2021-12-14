
#include <raylib.h>
#include <raymath.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <nlohmann/json.hpp>
#include <optional>
#include <sstream>
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
#include "schema/data.h"
#include "ui/keyboard.h"

using namespace janowski::paczki_cpp;
using json = nlohmann::json;
using JCamera = janowski::paczki_cpp::Camera;

#ifdef EMSCRIPTEN

#include <emscripten.h>
#include <emscripten/val.h>

EM_JS(void, paczka_init, (), {
  Paczka = {};
  Paczka["color"] = "#ffffff";
  newDiv = document.createElement("div");
  newDiv.id = "kolorek";
  newDiv.style.width = "100px";
  newDiv.style.height = "100px";
  document.body.insertBefore(newDiv, document.getElementById("output"));
});

EM_JS(void, update_color, (), {
  document.getElementById("kolorek").style.backgroundColor = Paczka["color"];
});

#else

void paczka_init() {}
void update_color() {}

#endif  // EMSCRIPTEN

struct Main {
  std::optional<std::string> last_color;
  bool last_color_changed = false;
};

int main() {
  Main state;
  box::List cubes;
  std::optional<schema::Data> data;
  std::optional<schema::ColorMap> colors;

  const int screenWidth = 800;
  const int screenHeight = 450;
  SetConfigFlags(FLAG_WINDOW_RESIZABLE bitor FLAG_VSYNC_HINT bitor
                 FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "Paczki C++");

  JCamera camera({0.f, 0.f, 0.f}, 50.f, 0.f, atanf(1), 45.f);

  Ray ray{};

  Vector3 g0 = {-50.0f, 0.0f, -50.0f};
  Vector3 g1 = {-50.0f, 0.0f, 50.0f};
  Vector3 g2 = {50.0f, 0.0f, 50.0f};
  Vector3 g3 = {50.0f, 0.0f, -50.0f};

  SetTargetFPS(60);

  paczka_init();

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

    if (data) {
      for (auto &[id, box_pos] : data->box_positions()) {
        auto &box_type = data->box_types().at(box_pos.box_type_id());
        RayCollision cube_hit_info = GetRayCollisionBox(
            ray,
            {rayvec(graphics::getPosition(box_pos) * graphics::kSizeMultiplier),
             rayvec((graphics::getPosition(box_pos) +
                     graphics::getSize(box_pos, box_type)) *
                    graphics::kSizeMultiplier)});
        if (cube_hit_info.hit && cube_hit_info.distance < collision.distance) {
          collision = cube_hit_info;
          const auto &box_color =
              colors ? colors->at(box_pos.id())
                     : math::Vector3<unsigned char>{0u, 0u, 0u};
          cursorColor = {box_color.x, box_color.y, box_color.z, 255u};
          hitObjectName = box_pos.id();
          // hit_box = box;
        }
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

      std::ifstream file(file_names.front());
      nlohmann::json json;
      file >> json;
      data = *(new schema::Data(json)); // debug
      cubes = box::List(loadJson(file_names.front()));
      camera.set_target(
          {(cubes.x_min() + cubes.x_max()) / 2.f * graphics::kSizeMultiplier,
           (cubes.y_min() + cubes.y_max()) / 2.f * graphics::kSizeMultiplier,
           (cubes.z_min() + cubes.z_max()) / 2.f * graphics::kSizeMultiplier});
      camera.updateCamera();
      colors = schema::ColorMap{};
      for (auto &[id, box_pos] : data->box_positions()) {
        colors->emplace(id, math::Vector3<unsigned char>{
                                (unsigned char)rand(), (unsigned char)rand(),
                                (unsigned char)rand()});
      }
    }

    ui::handleKeyboard(camera);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera.get());

    if (data && colors) {
      for (const auto &[id, cube] : data->box_positions()) {
        auto color = colors->at(cube.id());
        if (id == hitObjectName) {
          graphics::drawBoxItems(*data, cube,
                                 data->box_types().at(cube.box_type_id()),
                                 color, 100u);
#ifdef EMSCRIPTEN
          auto paczka_js = emscripten::val::global("setColor");
#endif
          std::stringstream color_ss;
          color_ss << "rgb(" << (int)color.x << "," << (int)color.y << ","
                   << (int)color.z << ")";
          std::cout << color_ss.str() << std::endl;
#ifdef EMSCRIPTEN
          auto color_js = emscripten::val::global("setColor");
          auto color_result = color_js(color_ss.str());
#endif
          std::cout << cube.json() << std::endl;
          // auto color_s = color_result.as<int>();
          // std::cout << color_s << std::endl;

          // paczka_js(color_ss.str());
          update_color();
        } else {
          graphics::drawBox(*data, cube,
                            data->box_types().at(cube.box_type_id()), color);
        }
      }
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
    if (!(hitObjectName == "Ground" || hitObjectName == "None")) {
      graphics::drawBoxOutline(*data, data->box_positions().at(hitObjectName),
                               colors->at(hitObjectName));
    }

    DrawRay(ray, MAROON);

    DrawGrid(10, 10.0f);

    EndMode3D();

    DrawText(TextFormat("Hit Object: %s", hitObjectName.c_str()), 10, 50, 10,
             BLACK);

    if (collision.hit) {
      int ypos = 50;

      if (!(hitObjectName == "Ground" || hitObjectName == "None")) {
        DrawText(
            TextFormat(
                "Box Type: %d",
                std::stoi(
                    data->box_positions().at(hitObjectName).box_type_id())),
            10, ypos += 15, 10, BLACK);
        DrawText(
            TextFormat(
                "Items: %d",
                data->box_types()
                    .at(data->box_positions().at(hitObjectName).box_type_id())
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

    DrawFPS(10, 10);

    EndDrawing();
  }

  RLCloseWindow();

  return 0;
}