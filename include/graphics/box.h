#pragma once

#include <cstdint>

#include "box/instance.h"
#include "schema/box_pos.h"
#include "schema/data.h"
#include "schema/sku.h"

namespace janowski::paczki_cpp::graphics {
constexpr float kSizeMultiplier = 0.01f;

void drawBox(const box::Instance &box);
void drawBox(const schema::Data &data, const schema::BoxPos &box_pos,
             const schema::BoxType &box_type,
             const math::Vector3<unsigned char> &color,
             uint8_t transparency = 255u);

void drawBoxItems(const schema::Data &data, const schema::BoxPos &box_pos,
                  const schema::BoxType &box_type,
                  const math::Vector3<unsigned char> &color,
                  uint8_t transparency);

void drawBoxOutline(const box::Instance &box);
void drawBoxOutline(const schema::Data &data, const schema::BoxPos &box_pos,
                    const math::Vector3<unsigned char> &color);

math::Vector3<float> getSize(const schema::BoxPos &box_pos,
                             const schema::BoxType &box_type);

math::Vector3<float> getPosition(const schema::BoxPos &box_pos);

math::Vector3<float> getItemSize(const schema::BoxPos &box_pos,
                                 const schema::BoxType::Item &item,
                                 const schema::Sku &sku);

math::Vector3<float> getItemPosition(const schema::BoxPos &box_pos,
                                     const schema::BoxType::Item &item);

}  // namespace janowski::paczki_cpp::graphics