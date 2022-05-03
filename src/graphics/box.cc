#include "graphics/box.h"

#include "lib/raylib_clean.h"

#include "math/color.h"
#include "math/vector3.h"
#include "schema/box_pos.h"
#include "schema/box_type.h"
#include "schema/data.h"
#include "schema/sku.h"

namespace janowski::paczki_cpp::graphics {
using namespace math;

void drawBox(const schema::Data& /*data*/, const schema::BoxPos& box_pos, const schema::BoxType& box_type,
             const Color& color) {
  auto size = getSize(box_pos, box_type);
  auto position = getPosition(box_pos) + (size * 0.5f);
  size = size * kSizeMultiplier;
  position = position * kSizeMultiplier;
  DrawCube(position, size.x, size.y, size.z, color);
}

void drawBoxExploded(const schema::Data& /*data*/, const schema::BoxPos& box_pos, const schema::BoxType& box_type,
                     const Color& color, const Vector3& center, float ratio) { //debug
  auto size = getSize(box_pos, box_type);
  auto position = getPosition(box_pos) + (size * 0.5f);
  auto offset = position - center;
  offset = offset * ratio;
  position = center + offset;
  size = size * kSizeMultiplier;
  position = position * kSizeMultiplier;
  DrawCube(position, size.x, size.y, size.z, color);
}

void drawBoxItems(const schema::Data& data, const schema::BoxPos& box_pos, const schema::BoxType& box_type,
                  const Color& color) {
  for (auto& item : box_type.items()) {
    auto& sku = data.skus().at(item.sku_id);
    auto size = getItemSize(box_pos, item, sku);
    auto position = getItemPosition(box_pos, item) + (size * 0.5f);
    size = size * kSizeMultiplier;
    position = position * kSizeMultiplier;
    size = size + -0.05f;
    DrawCubeWires(position, size.x, size.y, size.z, color);
  }
}

void drawBoxOutline(const schema::Data& data, const schema::BoxPos& box_pos, const Color& color,
                    bool invert /* = true */) {
  const auto& box_def = data.box_types().at(box_pos.box_type_id());

  auto size = getSize(box_pos, box_def);
  auto position = getPosition(box_pos) + (size * 0.5f);
  size = size * kSizeMultiplier;
  position = position * kSizeMultiplier;
  size = size + 0.05f;
  DrawCubeWires(position, size.x, size.y, size.z,
                invert ? makeColor((255u - color.r), (255u - color.g), (255u - color.b), 255u) : color);
}

Vector3 getSize(const schema::BoxPos& box_pos, const schema::BoxType& box_type) {
  const auto& rotated = box_pos.rotated();
  return makeVector3(!rotated ? box_type.size_x() : box_type.size_y(), box_type.size_z(),
                     !rotated ? box_type.size_y() : box_type.size_x());
}

Vector3 getPosition(const schema::BoxPos& box_pos) { return makeVector3(box_pos.x(), box_pos.z(), box_pos.y()); }

Vector3 getItemSize(const schema::BoxPos& box_pos, const schema::BoxType::Item& item, const schema::Sku& sku) {
  const auto& rotated = item.rotated;
  auto item_size =
      makeVector3(!rotated ? sku.size_x() : sku.size_y(), sku.size_z(), !rotated ? sku.size_y() : sku.size_x());
  if (box_pos.rotated()) {
    std::swap(item_size.x, item_size.z);
  }
  return item_size;
}

Vector3 getItemPosition(const schema::BoxPos& box_pos, const schema::BoxType::Item& item) {
  auto box_position = makeVector3(box_pos.x(), box_pos.z(), box_pos.y());
  auto item_position = makeVector3(item.x, item.z, item.y);
  if (box_pos.rotated()) {
    std::swap(item_position.x, item_position.z);
  }
  return box_position + item_position;
}

bool checkCollision(BoundingBox box1, BoundingBox box2)
{
    bool collision = true;

    if ((box1.max.x > box2.min.x) && (box1.min.x < box2.max.x))
    {
        if ((box1.max.y <= box2.min.y) || (box1.min.y >= box2.max.y)) collision = false;
        if ((box1.max.z <= box2.min.z) || (box1.min.z >= box2.max.z)) collision = false;
    }
    else collision = false;

    return collision;
}

}  // namespace janowski::paczki_cpp::graphics