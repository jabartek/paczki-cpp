#include <boost/ut.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>

#include "schema/data.h"

namespace ut = boost::ut;

namespace utils {
struct CerrPrinter : ut::printer {
  auto& operator<<(auto&& t) {
    std::cerr << t;
    return *this;
  }
};
}  // namespace utils

template <>
auto ut::cfg<ut::override> = ut::runner<ut::reporter<utils::CerrPrinter>>{};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  using namespace ut;
  using namespace janowski::paczki_cpp;

  if (argc < 2) throw std::runtime_error("Please specify .json storage directory.");

  const std::filesystem::path assets_path{argv[1]};
  for (auto file : std::filesystem::directory_iterator(assets_path)) {
    if (!file.is_regular_file()) continue;
    const auto& path = file.path();
    if (path.extension() != ".json") continue;
    const auto& filename = path.filename().string();
    test(filename) = [&] {
      std::ifstream json_file(path);
      expect(json_file.is_open()) << filename << " not opened!";
      nlohmann::json json;
      expect(nothrow([&] { json_file >> json; })) << "Could not load " << filename << "!";
      expect(nothrow([&] { auto schema = std::make_unique<schema::Data>(json); }))
          << "Could not load Schema from " << filename << "!";
    };
  }
}