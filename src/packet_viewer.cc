#include <memory>

#include "lib/emscripten_wrapper.h"
#include "lib/raylib_clean.h"

#include "bind/stores.h"

struct PacketViewerState {
  int window_width{};
  int window_height{};
  ::Camera2D camera;
};

PacketViewerState state;

void mainLoop() {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawText("Hello world", 100, 100, 10, RED);
  EndDrawing();
}

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE bitor FLAG_VSYNC_HINT bitor FLAG_MSAA_4X_HINT);
  state.window_width = 800;
  state.window_height = 450;
  state.camera = ::Camera2D{.offset = {0.f, 0.f}, .target = {0.f, 0.f}, .rotation = 0.f, .zoom = 0.f};
  InitWindow(state.window_width, state.window_height, "Packet Viewer");

  emscripten_set_main_loop(mainLoop, 0, 1);
  RLCloseWindow();

  return 0;
}