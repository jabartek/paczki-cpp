#include "pallet_viewer/state.h"

#include <chrono>

#include "bind/stores.h"

namespace janowski::paczki_cpp::pallet_viewer {
void State::set_color_scheme(ColorScheme color_scheme) {
  color_scheme_ = color_scheme;
  bind::setValue("color_by_box_pos", emscripten::val{color_scheme == ColorScheme::kByBoxPos});
}

void State::update() {
  if (alert && alert->timeout < std::chrono::system_clock::now()) {
    alert.reset();
  }
}
}  // namespace janowski::paczki_cpp::pallet_viewer