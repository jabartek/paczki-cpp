#pragma once

#include <iostream>

#include "lib/raylib_clean.h"
#include "math/vector2.h"
#include "math/vector3.h"
#include "ui/drawable.h"
#include "ui/handlers.h"

using namespace janowski::paczki_cpp::math;

namespace janowski::paczki_cpp::pallet_viewer {
class State;
}

namespace janowski::paczki_cpp::ui {
class Cube {
 public:
  ::BoundingBox bounding_box() const;

  void draw() const;

  ::Vector3 position;
  ::Vector3 size;
  ::Color color;
};

class Cursor3D : public Touchable {
 public:
  Cursor3D(std::shared_ptr<pallet_viewer::State> state, float size = 3.f, ::Vector3 pos = {0.f, 0.f, 0.f});

  void draw() override;

  bool isOver(const Vector2& /*pos*/) const override;

  void leftPress(const Vector2& pos) override;
  void leftClick(const Vector2& /*pos*/) override;

 private:
  std::shared_ptr<pallet_viewer::State> state_;
  float size_;
  ::Vector3 pos_;
  Cube cube_x_;
  Cube cube_y_;
  Cube cube_z_;
  Cube cube_c_;

  enum class LastCube { X, Y, Z, None = -1 };
  LastCube last_cube_{LastCube::None};
  bool is_cursor_dragged_{false};

  void updateCubes();
};
}  // namespace janowski::paczki_cpp::ui