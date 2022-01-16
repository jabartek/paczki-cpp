#pragma once
#include <raylib.h>

#include <memory>

namespace janowski::paczki_cpp::box {
class Definition;

class Instance {
public:
  const BoundingBox bounding_box() const;
  const Color &color() const;

  const Vector3 &position() const;
  const Vector3 positionCenter() const;
  const Vector3 &size() const;
  const Vector3 sizeRotated() const;
  bool rotated() const { return rotated_; }

  Instance(std::shared_ptr<Definition> definition_ptr, Vector3 position,
           bool rotated);

private:
  Vector3 position_;
  bool rotated_;
  std::weak_ptr<Definition> definition_;

  static const Vector3 zero_vec_;
};
} // namespace janowski::paczki_cpp::box