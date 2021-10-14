#pragma once

#include <raylib.h>
#include <raymath.h>

#include <cmath>
#include <memory>

namespace janowski::paczki_cpp {

namespace math {
auto plus(const ::Vector3 &vec1, const ::Vector3 &vec2) -> ::Vector3 {
  ::Vector3 vec;
  vec.x = vec1.x + vec2.x;
  vec.y = vec1.y + vec2.y;
  vec.z = vec1.z + vec2.z;
  return vec;
};
}  // namespace math

class Camera {
 public:
  Camera(::Vector3 target, float distance, float rotation_horizontal,
         float rotation_vertical, float fov)
      : camera_ptr_(std::make_shared<::Camera>()),
        target_(target),
        distance_(distance),
        rotation_horizontal_(rotation_horizontal),
        rotation_vertical_(rotation_vertical),
        fov_(fov) {
    auto &camera = *camera_ptr_;
    camera.up = {0.f, 1.f, 0.f};
    camera.fovy = fov_;
    camera.projection = ::CameraProjection::CAMERA_PERSPECTIVE;
    SetCameraMode(camera, ::CameraMode::CAMERA_CUSTOM);
    updateCamera();
  }

  void updateCamera() {
    const auto sin_horizontal = sinf(rotation_horizontal_);
    const auto cos_horizontal = cosf(rotation_horizontal_);
    const auto sin_vertical = sinf(rotation_vertical_);
    const auto cos_vertical = cosf(rotation_vertical_);
    const auto dist_horizontal = sin_vertical * distance_;

    const auto dist_x = sin_horizontal * dist_horizontal;
    const auto dist_y = cos_vertical * distance_;
    const auto dist_z = cos_horizontal * dist_horizontal;
    const ::Vector3 camera_offset{dist_x, dist_y, dist_z};

    auto &camera = *camera_ptr_;

    camera.position = math::plus(target_, camera_offset);
    camera.target = target_;
  }

  enum class Direction { UP, DOWN, LEFT, RIGHT, RESET };
  enum class Zoom { IN, OUT, RESET };

  void rotate(Direction direction, float angle) {
    switch (direction) {
      case Direction::UP:
        rotation_vertical_ += angle;
        break;
      case Direction::DOWN:
        rotation_vertical_ -= angle;
        break;
      case Direction::LEFT:
        rotation_horizontal_ -= angle;
        break;
      case Direction::RIGHT:
        rotation_horizontal_ += angle;
        break;
      default:
        rotation_horizontal_ = 0.f;
        rotation_vertical_ = 0.f;
    }
    updateCamera();
  }

  void zoom(Zoom zoom) {
    switch (zoom) {
      case Zoom::IN:
        distance_ *= 0.975f;
        break;
      case Zoom::OUT:
        distance_ /= 0.975f;
        break;
      default:
        break;
    }
    updateCamera();
  }

  ::Camera get() { return *camera_ptr_; }

  inline void set_target(::Vector3 target) { target_ = std::move(target); }

 private:
  std::shared_ptr<::Camera> camera_ptr_;
  ::Vector3 target_;
  float distance_;
  float rotation_horizontal_;
  float rotation_vertical_;
  float fov_;
};
}  // namespace janowski::paczki_cpp