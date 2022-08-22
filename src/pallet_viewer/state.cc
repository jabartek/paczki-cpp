#include "pallet_viewer/state.h"

#include <chrono>

#include "bind/stores.h"

namespace janowski::paczki_cpp::pallet_viewer {
State::State() {
#ifdef EMSCRIPTEN
  bind::registerFunction("offerDownload", [this] { offerDownload(); });
  bind::registerFunction("loadFile", [this](emscripten::val path) { this->file_to_load = path.as<std::string>(); });
#endif
}

void State::set_color_scheme(ColorScheme color_scheme) {
  color_scheme_ = color_scheme;
  bind::setValue("color_by_box_pos", emscripten::val{color_scheme == ColorScheme::kByBoxPos});
}

void State::update() {
  if (alert && alert->timeout < std::chrono::system_clock::now()) {
    alert.reset();
  }
}

void State::offerDownload() {
  if (!data) return;
  const auto json_dump = data->dump();
  {
    std::ofstream o("data.json");
    o << json_dump;
  }
#if EMSCRIPTEN
  emscripten::val::global("window").call<void>("offerDownload", std::string("data.json"));
#endif
}
}  // namespace janowski::paczki_cpp::pallet_viewer