#include "pallet_viewer/state.h"

#include <chrono>

namespace janowski::paczki_cpp::pallet_viewer {
void State::update() {
  if (alert && alert->timeout < std::chrono::system_clock::now()) {
    alert.reset();
  }
}
}  // namespace janowski::paczki_cpp::pallet_viewer