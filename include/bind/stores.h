#pragma once

#include <cstddef>
#include <functional>
#include <list>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

#include "lib/emscripten_wrapper.h"

namespace janowski::paczki_cpp::bind {

extern std::unordered_map<std::string, emscripten::val> stores;
extern std::unordered_map<std::string, std::function<void(emscripten::val)>> bindings;
extern std::unordered_map<std::string, std::list<std::function<void()>>> callbacks;
extern std::optional<emscripten::val> store_get;

void addStore(std::string name, emscripten::val store);
void setGet(emscripten::val get);

emscripten::val getFrom(const std::string& name);
void setValue(const std::string& name, emscripten::val value);
void setValue(const std::string& name, nlohmann::json json);

[[maybe_unused]] std::size_t subscribe(const std::string& store_name, std::function<void()> callback);
void callUpdate(const std::string& store_name);

void call(std::string function_name, emscripten::val arg);  // = emscripten::val::undefined());
void registerFunction(const std::string& function_name, std::function<void(emscripten::val)> function);
void registerFunction(const std::string& function_name, std::function<void()> function);

}  // namespace janowski::paczki_cpp::bind