#include "bind/bind.h"

#include <nlohmann/json.hpp>

#ifdef EMSCRIPTEN
#include <emscripten/val.h>
namespace janowski::paczki_cpp::bind {
[[maybe_unused]] bool call(const std::string& function,
                           std::optional<std::reference_wrapper<const nlohmann::json>> data) {
  auto function_obj = emscripten::val::global(function.c_str());
  auto function_result = function_obj(data ? data->get().dump() : "");
  return function_result.as<bool>();
}

nlohmann::json call_json(const std::string& function,
                         std::optional<std::reference_wrapper<const nlohmann::json>> data) {
  auto function_obj = emscripten::val::global(function.c_str());
  auto function_result = function_obj(data ? data->get().dump() : "");
  try {
    return {function_result.as<std::string>()};
  } catch (...) {
    return {"Data not parsable to JSON"};
  }
}

}  // namespace janowski::paczki_cpp::bind

#else
namespace janowski::paczki_cpp::bind {
[[maybe_unused]] bool call(const std::string& function,
                           std::optional<std::reference_wrapper<const nlohmann::json>> data) {
  return false;
}

nlohmann::json call_json(const std::string&, std::optional<std::reference_wrapper<const nlohmann::json>>) { return {}; }

}  // namespace janowski::paczki_cpp::bind
#endif