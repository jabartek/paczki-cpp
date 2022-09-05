#include "bind/stores.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <optional>
#include <stdexcept>

#include "nlohmann/json.hpp"

namespace janowski::paczki_cpp::bind {

#ifdef EMSCRIPTEN
std::unordered_map<std::string, emscripten::val> stores = {};
std::unordered_map<std::string, std::function<void(emscripten::val)>> bindings = {};
std::unordered_map<std::string, std::list<std::function<void()>>> callbacks = {};
std::optional<emscripten::val> store_get = std::nullopt;

void addStore(std::string name, emscripten::val store) {
  stores.emplace(std::make_pair(std::move(name), std::move(store)));
}

void setGet(emscripten::val get) { store_get.emplace(std::move(get)); }

emscripten::val getFrom(const std::string& name) {
  if (!stores.contains(name)) {
    throw std::runtime_error("(getFrom) No store named \"" + name + "\"!");
  }
  if (!store_get) {
    throw std::runtime_error("(getFrom) No getter set!");
  }
  return (*store_get)(stores.at(name));
}

void setValue(const std::string& name, emscripten::val value) {
  if (!stores.contains(name)) {
    return;
    // throw std::runtime_error("(setValue) No store named \"" + name + "\"!");
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

std::size_t subscribe(const std::string& store_name, std::function<void()> callback) {
  auto& callback_list2 = callbacks[store_name];
  callback_list2.push_back(std::move(callback));
  auto& callback_list = callbacks[store_name];

  //<< &callbacks << " " << &callback_list << " " << std::hash<std::string>{}(store_name) << "\n";
  return callback_list.size();
}

void callUpdate(const std::string& store_name) {
  auto& callback_list = callbacks[store_name];

  // &callbacks
  // << " " << &(callback_list) << " " << std::hash<std::string>{}(store_name) << "\n";
  std::for_each(callback_list.begin(), callback_list.end(), [](auto& f) { f(); });
}

void registerFunction(const std::string& function_name, std::function<void(emscripten::val)> function) {
  bindings[function_name] = function;
}

void registerFunction(const std::string& function_name, std::function<void()> function) {
  registerFunction(function_name, [function](emscripten::val) { function(); });
}

void call(std::string function_name, emscripten::val arg) {
  if (!bindings.contains(function_name)) {
    throw std::runtime_error("(call) No function named \"" + function_name + "\"!");
  }

  bindings.at(function_name)(arg);
}

#else

std::unordered_map<std::string, emscripten::val> stores = {};
void addStore(std::string, emscripten::val) {}

emscripten::val getFrom(const std::string& name) {
  if (!stores.contains(name)) {
    throw std::runtime_error("(getFrom) No store named \"" + name + "\"!");
  }
  return stores.at(name);
}

void setValue(const std::string&, emscripten::val) {}

void setValue(const std::string&, nlohmann::json) {}

std::size_t subscribe(const std::string& store_name, std::function<void()> callback) { return 0; }

void callUpdate(const std::string& store_name) {}

#endif
}  // namespace janowski::paczki_cpp::bind