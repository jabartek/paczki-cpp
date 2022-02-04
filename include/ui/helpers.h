#pragma once

#include <raylib.h>

namespace janowski::paczki_cpp::ui {
class Event {
 public:
  virtual ~Event() = default;

 protected:
 private:
};

enum class MouseButton {
  kLeft = MOUSE_BUTTON_LEFT,
  kRight = MOUSE_BUTTON_RIGHT,
  kMiddle = MOUSE_BUTTON_MIDDLE,
  kSide = MOUSE_BUTTON_SIDE,
  kExtra = MOUSE_BUTTON_EXTRA,
  kForward = MOUSE_BUTTON_FORWARD,
  kBack = MOUSE_BUTTON_BACK
};

class MouseEvent : public Event {
 public:
  virtual ~MouseEvent() = default;

  inline const Vector2& position() const { return position_; }
  inline MouseButton button() const { return button_; }

 protected:
  Vector2 position_;
  MouseButton button_;

 private:
};

class Clickable {
 public:
  bool isClicked(const MouseEvent& event) const;
  bool onClick(MouseEvent& event);
  virtual ~Clickable() = default;

 private:
};
}  // namespace janowski::paczki_cpp::ui