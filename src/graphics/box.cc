#include "graphics/box.h"

#include <iostream>
#include <utility>

#include "lib/raylib_clean.h"
#include "math/color.h"
#include "math/vector3.h"
#include "raylib.h"
#include "schema/box_pos.h"
#include "schema/box_type.h"
#include "schema/data.h"
#include "schema/sku.h"

namespace janowski::paczki_cpp::graphics {
using namespace math;

void drawBox(const schema::DataBase& /*data*/, const schema::BoxPos& box_pos, const schema::BoxType& box_type,
             const Color& color) {
  auto size = getSize(box_pos, box_type);
  auto position = getPosition(box_pos) + (size * 0.5f);
  size = size * kSizeMultiplier;
  position = position * kSizeMultiplier;
  DrawCube(position, size.x, size.y, size.z, color);
}

void drawBoxExploded(const schema::DataBase& /*data*/, const schema::BoxPos& box_pos, const schema::BoxType& box_type,
                     const Color& color, const Vector3& center, float ratio) {  // debug
  auto size = getSize(box_pos, box_type);
  auto position = getPosition(box_pos) + (size * 0.5f);
  auto offset = position - center;
  offset = offset * ratio;
  position = center + offset;
  size = size * kSizeMultiplier;
  position = position * kSizeMultiplier;
  DrawCube(position, size.x, size.y, size.z, color);
}

void drawBoxItems(const schema::DataBase& data, const schema::BoxPos& box_pos, const schema::BoxType& box_type,
                  const Color& color) {
  for (auto& item : box_type.items()) {
    auto& sku = data.skus().at(item.sku_id);
    auto size = getItemSize(box_pos, item, sku);
    auto position = getItemPosition(box_pos, item) + (size * 0.5f);
    size = size * kSizeMultiplier;
    position = position * kSizeMultiplier;
    // size = size * .99f;
    DrawCube(position, size.x, size.y, size.z, Color{sku.color_r(), sku.color_g(), sku.color_b(), 255u});
    size = size * 1.01f;
    DrawCubeWires(position, size.x, size.y, size.z,
                  Color{(unsigned char)(255u - sku.color_r()), (unsigned char)(255u - sku.color_g()),
                        (unsigned char)(255u - sku.color_b()), 255u});
  }
}

// void drawBoxItems(const schema::DataBase& data, const schema::BoxPos& box_pos, const schema::BoxType& box_type,
//                   const Color& color) {
//   for (auto& item : box_type.items()) {
//     auto& sku = data.skus().at(item.sku_id);
//     auto size = getItemSize(box_pos, item, sku);
//     auto position = getItemPosition(box_pos, item) + (size * 0.5f);
//     size = size * kSizeMultiplier;
//     position = position * kSizeMultiplier;
//     size = size * 0.98f;
//     DrawCubeWires(position, size.x, size.y, size.z, color);
//   }
// }

void drawBoxOutline(const schema::DataBase& data, const schema::BoxPos& box_pos, const Color& color,
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

std::pair<float, float> checkCollision(BoundingBox box1, BoundingBox box2, Axis move_axis) {
  std::pair<float, float> move = std::make_pair(0.f, 0.f);

  if ((box1.max.x <= box2.min.x) || (box1.min.x >= box2.max.x)) return move;
  if ((box1.max.y <= box2.min.y) || (box1.min.y >= box2.max.y)) return move;
  if ((box1.max.z <= box2.min.z) || (box1.min.z >= box2.max.z)) return move;

  switch (move_axis) {
    case Axis::X:
      return std::make_pair(box1.min.x - box2.max.x, box1.max.x - box2.min.x);

    case Axis::Y:
      return std::make_pair(box1.min.y - box2.max.y, box1.max.y - box2.min.y);

    case Axis::Z:
      return std::make_pair(box1.min.z - box2.max.z, box1.max.z - box2.min.z);

    default:
      break;
  }

  return move;
}

}  // namespace janowski::paczki_cpp::graphics