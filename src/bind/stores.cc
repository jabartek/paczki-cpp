#include "bind/stores.h"

#include <iostream>
#include <stdexcept>

#include "nlohmann/json.hpp"

namespace janowski::paczki_cpp::bind {
std::unordered_map<std::string, emscripten::val> stores = {};
void addStore(std::string name, emscripten::val store) {
  std::cout << "Hello stores " << name << "!\n";
  stores.emplace(std::make_pair(std::move(name), std::move(store)));
}

emscripten::val& getFrom(const std::string& name) {
  if (!stores.contains(name)) {
    throw std::runtime_error("(getFrom) No store named \"" + name + "\"!");
  }
  return stores.at(name);
}

void setValue(const std::string& name, emscripten::val value) {
  if (!stores.contains(name)) {
    throw std::runtime_error("(setValue) No store named \"" + name + "\"!");
  }
  stores.at(name).call<void>("set", value);
}

void setValue(const std::string& name, nlohmann::json json) {
  if (!stores.contains(name)) {
    throw std::runtime_error("(setValue) No store named \"" + name + "\"!");
  }
  auto parser = emscripten::val::global("JSON");
  auto json_parsed = parser.call<emscripten::val>("parse", json.dump());
  stores.at(name).call<void>("set", json_parsed);
}

EMSCRIPTEN_BINDINGS(paczki_plusplus) { emscripten::function("addStore", &addStore); };
}  // namespace janowski::paczki_cpp::bind