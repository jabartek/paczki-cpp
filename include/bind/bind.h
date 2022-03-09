#pragma once

#include <functional>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

#ifdef EMSCRIPTEN

#endif

namespace janowski::paczki_cpp::bind {

[[maybe_unused]] bool call(const std::string& function,
                           std::optional<std::reference_wrapper<const nlohmann::json>> data = std::nullopt);
nlohmann::json call_json(const std::string& function,
                         std::optional<std::reference_wrapper<const nlohmann::json>> data = std::nullopt);

}  // namespace janowski::paczki_cpp::bind