#include "graphics/box.h"

namespace janowski::paczki_cpp::graphics {
void drawBox(const box::Instance& box) {
  using janowski::paczki_cpp::math::rayvec;
  auto size = box.sizeRotated() * kSizeMultiplier;
  auto position = box.positionCenter() * kSizeMultiplier;
  DrawCube(rayvec(position), size.x, size.y, size.z,
           {box.color().x, box.color().y, box.color().z, 255u});
}
void drawBoxOutline(const box::Instance& box) {
  using janowski::paczki_cpp::math::rayvec;
  math::Vector3<float> size = box.sizeRotated() * graphics::kSizeMultiplier;
  size += 0.05f;
  DrawCubeWires(rayvec(box.positionCenter() * graphics::kSizeMultiplier),
                size.x, size.y, size.z,
                {static_cast<uint8_t>(255u - box.color().x),
                 static_cast<uint8_t>(255u - box.color().y),
                 static_cast<uint8_t>(255u - box.color().z), 255u});
}
}  // namespace janowski::paczki_cpp::graphics