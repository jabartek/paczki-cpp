
#include "graphics/box.h"
#include "raylib.h"
#include "schema/box_pos.h"
#ifdef EMSCRIPTEN

#include <chrono>
#include <iostream>
#include <memory>

#include "bind/stores.h"
#include "lib/emscripten_wrapper.h"
#include "lib/raylib_clean.h"
#include "nlohmann/json.hpp"
#include "packet_viewer/state.h"

using namespace janowski::paczki_cpp;
std::shared_ptr<packet_viewer::State> state;

EMSCRIPTEN_BINDINGS(packet_viewer_addStore) { emscripten::function("addStore", &bind::addStore); };
EMSCRIPTEN_BINDINGS(packet_viewer_callUpdate) { emscripten::function("callUpdate", &bind::callUpdate); };
EMSCRIPTEN_BINDINGS(packet_viewer_call) { emscripten::function("call", &bind::call); };
EMSCRIPTEN_BINDINGS(packet_viewer_setGet) { emscripten::function("setGet", &bind::setGet); };

decltype(std::chrono::system_clock::now()) tp;
bool setCb = false;
void mainLoop() {
  state->handleObjects();
  BeginDrawing();
  ClearBackground(RAYWHITE);
  if (auto t = std::chrono::system_clock::now(); t - tp > std::chrono::seconds(1)) {
    if (!setCb) {
      setCb = true;
      state->subscribeAll();
    }
    tp = t;
    for (const auto& [id, sku] : state->data().skus()) {
      // rem_std::cout << sku.id() << ", ";
    }
    // rem_std::cout << std::endl;
  }
  BeginMode3D(state->camera->get());
  DrawGrid(1000, 2.0f);

  if (auto selected = state->selected_box_type(); selected) {
    try {
      graphics::drawBoxItems(state->data(), schema::BoxPos::null(), state->data().box_types().at(*selected),
                             Color{128, 128, 128, 255});
    } catch (...) {
      // rem_std::cout << "Selected: " << *selected << "\nKeys";
      for (const auto& [k, v] : state->data().box_types()) {
        // rem_std::cout << k << ", ";
      }
      // rem_std::cout << "\n";
    }
  }
  EndMode3D();
  state->drawObjects();

  EndDrawing();
}

int main() {
  state = std::make_shared<packet_viewer::State>();
  tp = std::chrono::system_clock::now();
  state->window_width = 1200;
  state->window_height = 800;
  state->camera.emplace(::Vector3{0.f, 0.f, 0.f}, 50.f, 0.f, atanf(1), 45.f);
  state->createObjects();
  SetConfigFlags(FLAG_VSYNC_HINT bitor FLAG_MSAA_4X_HINT);
  InitWindow(state->window_width, state->window_height, "Packet Viewer");

  emscripten_set_main_loop(mainLoop, 0, 1);

  RLCloseWindow();
  return 0;
}

#else
static_assert(false, "This should only be compiled for Emscripten!");
#endif