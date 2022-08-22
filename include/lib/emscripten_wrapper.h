#pragma once

#ifdef EMSCRIPTEN

#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

#else
namespace emscripten {
class val {
 public:
  val() {}
  inline val(auto...) {}
  template <typename T>
  inline T as() {
    return T{};
  }
};
}  // namespace emscripten
#endif