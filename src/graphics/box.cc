#include "graphics/box.h"

namespace janowski::paczki_cpp::graphics {
void drawBox(const box::Instance& box) {
  using janowski::paczki_cpp::math::rayvec;
  DrawCube(rayvec(box.position() + (box.size() * 0.5f)), box.size().x(),
           box.size().y(), box.size().z(),
           {box.color().x(), box.color().y(), box.color().z(), 255u});
}
}  // namespace janowski::paczki_cpp::graphics