#include "box/definition.h"

namespace janowski::paczki_cpp::box {
Definition::Definition(math::Vector3<float> size,
                       math::Vector3<std::uint8_t> color)
    : size_(size), color_(color) {}
    
}  // namespace janowski::paczki_cpp::box