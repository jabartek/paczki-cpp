#pragma once

#include <raylib.h>

#include <memory>

namespace janowski::paczki_cpp::rendering {
class Camera;
class Mode3D {
 public:
  inline Mode3D(rendering::Camera* camera) : camera_(camera) { Begin(); }

  inline ~Mode3D() { End(); }

  inline Camera& camera() { return *camera_; }

  inline bool active() const { return active_; };

 private:
  void Begin();
  void End();

  bool active_{false};
  rendering::Camera* camera_;
};
}  // namespace janowski::paczki_cpp::rendering