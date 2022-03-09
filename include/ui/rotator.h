#pragma once

#include "lib/raylib_clean.h"

#include <cmath>
#include <utility>

#include "colors.h"
#include "math/vector2.h"
#include "rendering/camera.h"

using namespace janowski::paczki_cpp::math;

namespace janowski::paczki_cpp::ui {

constexpr float kInnerRadiusMultiplier = .6f;
constexpr float kRotatorZoomSpeed = .985f;
constexpr float kRotatorRotateSpeed = 1.f / 60.f;
constexpr unsigned kCircleSides = 36;

class Rotator {
 public:
  inline Rotator(Vector2 center, float radius)
      : center_(std::move(center)), radius_outer_(radius), radius_inner_(radius * kInnerRadiusMultiplier) {}
  inline void draw() {
    drawRotationTool();
    drawZoomTool();
  }

  inline bool isOver(const Vector2& pos) const { return Vector2Distance(pos, center_) <= radius_outer_; }

  inline bool handleClick(const Vector2& pos, janowski::paczki_cpp::rendering::Camera& camera) {
    if (!isOver(pos)) {
      return false;
    }
    if (Vector2Distance(pos, center_) <= radius_inner_) {
      handleZoomClick(pos, camera);
    } else {
      handleRotateClick(pos, camera);
    }
    return true;
  }

 private:
  inline void drawRotationTool() {
    DrawCircleSector(center_, radius_outer_, -45.f, 45.f, kCircleSides / 4, colors::GRAY55_C);
    DrawCircleSector(center_, radius_outer_, 90.f + -45.f, 90.f + 45.f, kCircleSides / 4, colors::GRAY65_C);
    DrawCircleSector(center_, radius_outer_, 180.f + -45.f, 180.f + 45.f, kCircleSides / 4, colors::GRAY55_C);
    DrawCircleSector(center_, radius_outer_, 270.f + -45.f, 270.f + 45.f, kCircleSides / 4, colors::GRAY65_C);
  };
  inline void drawZoomTool() {
    DrawCircleSector(center_, radius_inner_, -90.f, 90.f, kCircleSides / 2, colors::GRAY50_C);
    DrawCircleSector(center_, radius_inner_, 90.f, 270.f, kCircleSides / 2, colors::GRAY70_C);
  }

  inline void handleZoomClick(const Vector2& pos, janowski::paczki_cpp::rendering::Camera& camera) {
    if (pos.y > center_.y) {
      camera.zoom(janowski::paczki_cpp::rendering::Camera::Zoom::OUT, kRotatorZoomSpeed);
      return;
    }
    if (pos.y <= center_.y) {
      camera.zoom(janowski::paczki_cpp::rendering::Camera::Zoom::IN, kRotatorZoomSpeed);
      return;
    }
  }

  inline void handleRotateClick(const Vector2& pos, janowski::paczki_cpp::rendering::Camera& camera) {
    auto offset = pos - center_;
    if (offset.y > 0.f && std::fabs(offset.y) > std::fabs(offset.x)) {
      camera.rotate(janowski::paczki_cpp::rendering::Camera::Direction::UP, kRotatorRotateSpeed);
      return;
    }
    if (offset.y <= 0.f && std::fabs(offset.y) > std::fabs(offset.x)) {
      camera.rotate(janowski::paczki_cpp::rendering::Camera::Direction::DOWN, kRotatorRotateSpeed);
      return;
    }
    if (offset.x < 0.f) {
      camera.rotate(janowski::paczki_cpp::rendering::Camera::Direction::LEFT, kRotatorRotateSpeed);
      return;
    }
    if (offset.x >= 0.f) {
      camera.rotate(janowski::paczki_cpp::rendering::Camera::Direction::RIGHT, kRotatorRotateSpeed);
      return;
    }
  }
  Vector2 center_;
  float radius_outer_;
  float radius_inner_;
};
}  // namespace janowski::paczki_cpp::ui