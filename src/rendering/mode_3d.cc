#include "rendering/mode_3d.h"

#include "rendering/camera.h"

namespace janowski::paczki_cpp::rendering {
void Mode3D::Begin() {
  BeginMode3D(camera_->get());
  active_ = true;
}
void Mode3D::End() {
  EndMode3D();
  active_ = false;
}
}  // namespace janowski::paczki_cpp::rendering