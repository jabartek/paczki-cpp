#pragma once

#include "schema/data.h"

namespace janowski::paczki_cpp::pallet_viewer {
class State {
public:
  std::optional<schema::Data> data;
  std::optional<schema::ColorMap> color_map;
};
} // namespace janowski::paczki_cpp::pallet_viewer