#include "graphics/box.h"
#include "box/instance.h"
#include "math/vector3.h"
#include "schema/box_pos.h"
#include "schema/box_type.h"
#include "schema/data.h"
#include "schema/sku.h"

#include <raylib.h>

namespace janowski::paczki_cpp::graphics {

void drawBox(const box::Instance &box) {
  using janowski::paczki_cpp::math::rayvec;
  auto size = box.sizeRotated() * kSizeMultiplier;
  auto position = box.positionCenter() * kSizeMultiplier;
  DrawCube(rayvec(position), size.x, size.y, size.z,
           {box.color().x, box.color().y, box.color().z, 255u});
}
void drawBox(const schema::Data &data, const schema::BoxPos &box_pos,
             const math::Vector3<unsigned char> &color, uint8_t transparency) {
  using janowski::paczki_cpp::math::rayvec;
  const auto &box_def = data.box_types().at(box_pos.box_type_id());

  auto size = getSize(box_pos, box_def);
  auto position = getPosition(box_pos) + (size * 0.5f);
  size *= kSizeMultiplier;
  position *= kSizeMultiplier;
  DrawCube(rayvec(position), size.x, size.y, size.z,
           Color{color.x, color.y, color.z, transparency});
}

void drawBoxItems(const schema::Data &data, const schema::BoxPos &box_pos,
                  const schema::BoxType &box_type,
                  const math::Vector3<unsigned char> &color,
                  uint8_t transparency) {
  using janowski::paczki_cpp::math::rayvec;
  // drawBox(data, box_pos, color, transparency);
  for (auto &item : box_type.items()) {
    auto &sku = data.skus().at(item.sku_id);
    auto size = getItemSize(box_pos, item, sku);
    auto position = getItemPosition(box_pos, item) + (size * 0.5f);
    size *= kSizeMultiplier;
    position *= kSizeMultiplier;
    size += -0.05f;
    DrawCubeWires(rayvec(position), size.x, size.y, size.z,
                  Color{static_cast<uint8_t>(255u - color.x),
                        static_cast<uint8_t>(255u - color.y),
                        static_cast<uint8_t>(255u - color.z), 255u});
  }
}

void drawBoxOutline(const box::Instance &box) {
  using janowski::paczki_cpp::math::rayvec;
  math::Vector3<float> size = box.sizeRotated() * graphics::kSizeMultiplier;
  size += 0.05f;
  DrawCubeWires(rayvec(box.positionCenter() * graphics::kSizeMultiplier),
                size.x, size.y, size.z,
                {static_cast<uint8_t>(255u - box.color().x),
                 static_cast<uint8_t>(255u - box.color().y),
                 static_cast<uint8_t>(255u - box.color().z), 255u});
}
void drawBoxOutline(const schema::Data &data, const schema::BoxPos &box_pos,
                    const math::Vector3<unsigned char> &color) {
  using janowski::paczki_cpp::math::rayvec;
  const auto &box_def = data.box_types().at(box_pos.box_type_id());

  auto size = getSize(box_pos, box_def);
  auto position = getPosition(box_pos) + (size * 0.5f);
  size *= kSizeMultiplier;
  position *= kSizeMultiplier;
  size += 0.05f;
  DrawCubeWires(rayvec(position), size.x, size.y, size.z,
                Color{static_cast<uint8_t>(255u - color.x),
                      static_cast<uint8_t>(255u - color.y),
                      static_cast<uint8_t>(255u - color.z), 255u});
}

math::Vector3<float> getSize(const schema::BoxPos &box_pos,
                             const schema::BoxType &box_type) {
  const auto &rotated = box_pos.rotated();
  return math::Vector3<float>(!rotated ? box_type.size_x() : box_type.size_y(),
                              box_type.size_z(),
                              !rotated ? box_type.size_y() : box_type.size_x());
}

math::Vector3<float> getPosition(const schema::BoxPos &box_pos) {
  return math::Vector3<float>(box_pos.x(), box_pos.z(), box_pos.y());
}

math::Vector3<float> getItemSize(const schema::BoxPos &box_pos,
                                 const schema::BoxType::Item &item,
                                 const schema::Sku &sku) {
  const auto &rotated = item.rotated;
  auto item_size =
      math::Vector3<float>(!rotated ? sku.size_x() : sku.size_y(), sku.size_z(),
                           !rotated ? sku.size_y() : sku.size_x());
  if (box_pos.rotated()) {
    std::swap(item_size.x, item_size.z);
  }
  return item_size;
}

math::Vector3<float> getItemPosition(const schema::BoxPos &box_pos,
                                     const schema::BoxType::Item &item) {
  auto box_position =
      math::Vector3<float>(box_pos.x(), box_pos.z(), box_pos.y());
  auto item_position = math::Vector3<float>(item.x, item.z, item.y);
  if (box_pos.rotated()) {
    std::swap(item_position.x, item_position.z);
  }
  return box_position + item_position;
}

} // namespace janowski::paczki_cpp::graphics