#pragma once

#include <memory>
#include <optional>
#include <string>

#include "schema/data.h"

namespace janowski::paczki_cpp::pallet_viewer {
class State {
 public:
  enum class ColorScheme { kByBoxPos, kByBoxType } color_scheme;
  std::shared_ptr<schema::Data> data;
  std::optional<schema::Data::ColorMap> color_map;
  std::optional<std::string> selectedBoxPos;
  std::optional<std::string> selectedBoxType;
  std::optional<std::string> hoverBoxPos;

  void update();
};
}  // namespace janowski::paczki_cpp::pallet_viewer