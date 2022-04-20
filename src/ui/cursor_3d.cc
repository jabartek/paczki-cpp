#include "ui/cursor_3d.h"

#include "pallet_viewer/state.h"

using namespace janowski::paczki_cpp::math;

namespace janowski::paczki_cpp::ui {

::BoundingBox Cube::bounding_box() const {
  return {
      .min = position,
      .max = position + size,
  };
}

void Cube::draw() const { DrawCube(position + size * 0.5f, size.x, size.y, size.z, color); }

Cursor3D::Cursor3D(std::shared_ptr<pallet_viewer::State> state, float size, ::Vector3 pos)
    : Touchable(), state_(state), size_(size), pos_(pos) {
  updateCubes();
  std::cout << "Hello Cursor3D!\n";
}

void Cursor3D::draw() {
  cube_x_.draw();
  cube_y_.draw();
  cube_z_.draw();
  cube_c_.draw();
}

bool Cursor3D::isOver(const Vector2& /*pos*/) const { return true; }

void Cursor3D::leftPress(const Vector2& pos) {
  if (!state_ || !state_->camera) return;
  std::cout << "Cursor3D::leftPress\tx:\t" << pos.x << "\ty:\t" << pos.y << "\n";
  updateCubes();
  auto camera = state_->camera->get();
  auto ray = GetMouseRay(pos, camera);
  Cube* hit_cube = nullptr;
  RayCollision collision = GetRayCollisionBox(ray, cube_c_.bounding_box());
  if (!collision.hit) {
    collision.distance = std::numeric_limits<float>::max();
  }
  {
    auto collision_x = GetRayCollisionBox(ray, cube_x_.bounding_box());
    if (collision_x.hit) {
      std::cout << "Hit X!\n";
      if (collision_x.distance < collision.distance) {
        hit_cube = &cube_x_;
        collision = collision_x;
      }
    }
  }
  {
    auto collision_y = GetRayCollisionBox(ray, cube_y_.bounding_box());
    if (collision_y.hit) {
      std::cout << "Hit Y!\n";
      if (collision_y.distance < collision.distance) {
        hit_cube = &cube_y_;
        collision = collision_y;
      }
    }
  }
  {
    auto collision_z = GetRayCollisionBox(ray, cube_z_.bounding_box());
    if (collision_z.hit) {
      std::cout << "Hit Z!\n";
      if (collision_z.distance < collision.distance) {
        hit_cube = &cube_z_;
        collision = collision_z;
      }
    }
  }
  if (hit_cube) {
    is_cursor_dragged_ = true;
  }
  if (is_cursor_dragged_) {
    switch (last_cube_) {
      case LastCube::X:
        hit_cube = &cube_x_;
        break;
      case LastCube::Y:
        hit_cube = &cube_y_;
        break;
      case LastCube::Z:
        hit_cube = &cube_z_;
        break;
      default:
        break;
    }
  }
  if (is_cursor_dragged_) {
    auto delta = GetMouseDelta();
    auto ray_before = GetMouseRay(pos + delta * -1.f, camera);
    auto pos = ::Vector3{0.f, 0.f, 0.f};
    ::Vector3 p1 = pos + ::Vector3{-1000.f, -1000.f, 0.f};
    ::Vector3 p2 = pos + ::Vector3{-1000.f, 1000.f, 0.f};
    ::Vector3 p3 = pos + ::Vector3{1000.f, 1000.f, 0.f};
    ::Vector3 p4 = pos + ::Vector3{1000.f, -1000.f, 0.f};
    ::Vector3 p1z = pos + ::Vector3{-1000.f, 0.f, -1000.f};
    ::Vector3 p2z = pos + ::Vector3{-1000.f, 0.f, 1000.f};
    ::Vector3 p3z = pos + ::Vector3{1000.f, 0.f, 1000.f};
    ::Vector3 p4z = pos + ::Vector3{1000.f, 0.f, -1000.f};
    auto col = GetRayCollisionQuad(ray, pos_ + p1, pos_ + p2, pos_ + p3, pos_ + p4);
    auto col_before = GetRayCollisionQuad(ray_before, pos_ + p1, pos_ + p2, pos_ + p3, pos_ + p4);
    auto col_z = GetRayCollisionQuad(ray, pos_ + p1z, pos_ + p2z, pos_ + p3z, pos_ + p4z);
    auto col_before_z = GetRayCollisionQuad(ray_before, pos_ + p1z, pos_ + p2z, pos_ + p3z, pos_ + p4z);
    if (hit_cube == &cube_x_) {
      last_cube_ = LastCube::X;
      pos_ = pos_ + ::Vector3{
                        col.point.x - col_before.point.x,
                        0.f,
                        0.f,
                    };
    } else if (hit_cube == &cube_y_) {
      last_cube_ = LastCube::Y;
      pos_ = pos_ + ::Vector3{
                        0.f,
                        col.point.y - col_before.point.y,
                        0.f,
                    };
    } else if (hit_cube == &cube_z_) {
      last_cube_ = LastCube::Z;
      pos_ = pos_ + ::Vector3{
                        0.f,
                        0.f,
                        col_z.point.z - col_before_z.point.z,
                    };
      std::cout << "Col Z point:\t" << col_z.point.x << "\t" << col_z.point.y << "\t" << col_z.point.z << "\t\n";
    }
  }
}
void Cursor3D::leftRelease(const Vector2& /*pos*/) {
  last_cube_ = LastCube::None;
  is_cursor_dragged_ = false;
}

void Cursor3D::updateCubes() {
  float length = size_;
  float width = length * 0.16667f;
  float offset = length * 0.03333f;
  float center_cube_size = width + 2 * offset;
  cube_x_ = Cube{
      .position = pos_,
      .size = {length, width, width},
      .color = RED,
  };
  cube_y_ = Cube{
      .position = pos_,
      .size = {width, length, width},
      .color = GREEN,
  };
  cube_z_ = Cube{
      .position = pos_,
      .size = {width, width, length},
      .color = BLUE,
  };
  cube_c_ = Cube{
      .position = pos_ + ::Vector3{-offset, -offset, -offset},
      .size = ::Vector3{center_cube_size, center_cube_size, center_cube_size},
      .color = WHITE,
  };
}
}  // namespace janowski::paczki_cpp::ui