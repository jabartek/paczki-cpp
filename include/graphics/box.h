#pragma once

#include "schema/box_pos.h"
#include "schema/data.h"
#include "schema/sku.h"

namespace janowski::paczki_cpp::graphics {
constexpr float kSizeMultiplier = 0.01f;
enum class Axis { X, Y, Z, None };

void drawBox(const schema::DataBase& data, const schema::BoxPos& box_pos, const schema::BoxType& box_type,
             const Color& color);

void drawBoxItems(const schema::DataBase& data, const schema::BoxPos& box_pos, const schema::BoxType& box_type,
                  const Color& color);

void drawBoxOutline(const schema::DataBase& data, const schema::BoxPos& box_pos, const Color& color,
                    bool invert = true);

void drawBoxExploded(const schema::DataBase& data, const schema::BoxPos& box_pos, const schema::BoxType& box_type,
                     const Color& color, const Vector3& center, float ratio);  // debug

Vector3 getSize(const schema::BoxPos& box_pos, const schema::BoxType& box_type);

Vector3 getPosition(const schema::BoxPos& box_pos);

Vector3 getItemSize(const schema::BoxPos& box_pos, const schema::BoxType::Item& item, const schema::Sku& sku);

Vector3 getItemPosition(const schema::BoxPos& box_pos, const schema::BoxType::Item& item);

// returns the value first box needs to be moved by in the Axis in order to not collide
std::pair<float, float> checkCollision(BoundingBox box1, BoundingBox box2, Axis move_axis);

}  // namespace janowski::paczki_cpp::graphics