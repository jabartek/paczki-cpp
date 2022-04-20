#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace janowski::paczki_cpp::pallet_viewer {
class State;
}

namespace janowski::paczki_cpp::ui {

constexpr int kMaxClickLength = 20; // todo: change to std::chrono::duration

struct Handler {
  Handler(std::function<bool(std::shared_ptr<pallet_viewer::State>)> pred,
          std::function<void(std::shared_ptr<pallet_viewer::State>)> func)
      : pred(pred), func(func) {}
  std::function<bool(std::shared_ptr<pallet_viewer::State>)> pred;
  std::function<void(std::shared_ptr<pallet_viewer::State>)> func;
};

class HandlerStore {
 public:
  HandlerStore(std::shared_ptr<pallet_viewer::State> state);
  void doRegister(Handler handler);
  void handleAll();

 private:
  std::shared_ptr<pallet_viewer::State> state_;
  std::vector<Handler> handlers_;
};

class DropHandler {
 public:
  static bool pred(std::shared_ptr<pallet_viewer::State> /*state_ptr*/);
  static void func(std::shared_ptr<pallet_viewer::State> state_ptr);
};

class KeyboardHandler {
 public:
  static bool pred(std::shared_ptr<pallet_viewer::State> /*state_ptr*/);
  static void func(std::shared_ptr<pallet_viewer::State> state_ptr);
};

}  // namespace janowski::paczki_cpp::ui