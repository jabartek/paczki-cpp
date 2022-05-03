#pragma once

#include "emscripten_wrapper.h"

#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

namespace janowski::paczki_cpp::bind {

extern std::unordered_map<std::string, emscripten::val> stores;

void addStore(std::string name, emscripten::val store);

emscripten::val& getFrom(const std::string& name);
void setValue(const std::string& name, emscripten::val value);
void setValue(const std::string& name, nlohmann::json json);

}  // namespace janowski::paczki_cpp::bind