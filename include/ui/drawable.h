#pragma once

#include <memory>
#include <utility>

#include "lib/raylib_clean.h"

namespace janowski::paczki_cpp::ui {
class Drawable {
 public:
  virtual void draw() = 0;
  virtual ~Drawable() = default;
};

class Touchable : public Drawable {
 public:
  virtual bool isOver(const Vector2& pos) const = 0;
  virtual void leftPress(const Vector2& /*pos*/){};
  virtual void rightPress(const Vector2& /*pos*/){};
  virtual void leftClick(const Vector2& /*pos*/){};
  virtual void rightClick(const Vector2& /*pos*/){};
  virtual void leftRelease(const Vector2& /*pos*/){};
  virtual void rightRelease(const Vector2& /*pos*/){};
  virtual void hover(const Vector2& /*pos*/){};
  virtual ~Touchable() = default;

 protected:
};
}  // namespace janowski::paczki_cpp::ui