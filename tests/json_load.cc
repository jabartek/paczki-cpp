#include <boost/ut.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>

#include "schema/box_type.h"
#include "schema/data.h"

#define kNoSkipTag "no_skip"
#define may_skip (*has_metadata ? tag(kNoSkipTag) : tag("skip"))

namespace ut = boost::ut;

namespace utils {
struct CerrPrinter : ut::printer {
  template <class T>
  auto& operator<<(T&& t) {
    std::cerr << std::forward<T>(t);
    return *this;
  }
};
}  // namespace utils

template <>
auto ut::cfg<ut::override> = ut::runner<ut::reporter<utils::CerrPrinter>>{};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  using namespace ut;
  using namespace ut::bdd;
  using namespace janowski::paczki_cpp;

  cfg<ut::override> = {.tag = {"no_skip"}};

  if (argc < 2) throw std::runtime_error("Please specify .json storage directory.");

  const std::filesystem::path assets_path{argv[1]};
  for (const auto& file : std::filesystem::directory_iterator(assets_path)) {
    if (!file.is_regular_file()) continue;
    const auto& path = file.path();
    if (path.extension() != ".json") continue;
    const auto& filename = path.filename().string();
    scenario("Basic load: " + filename) = [&] {
      std::ifstream json_file(path);
      expect(json_file.is_open()) << filename << " not opened!";
      nlohmann::json json;
      expect(nothrow([&] { json_file >> json; })) << "Could not load " << filename << "!";
      expect(nothrow([&] { auto schema = std::make_unique<schema::Data>(json); }))
          << "Could not load Schema from " << filename << "!";
    };
  }
  for (const auto& file : std::filesystem::directory_iterator(assets_path)) {
    if (!file.is_regular_file()) continue;
    const auto& path = file.path();
    if (path.extension() != ".json") continue;
    const auto& filename = path.filename().string();
    scenario("Advanced load: " + filename) = [&] {
      std::ifstream json_file;
      should("Open file") = [&] {
        json_file = std::ifstream{file};
        expect(json_file.is_open()) << filename << " not opened!";
      };

      nlohmann::json json;
      should("Load JSON") = [&] {
        expect(nothrow([&] { json_file >> json; })) << "Could not load " << filename << "!";
      };

      std::optional<bool> has_metadata{};
      given("Has metadata") = [&] {
        has_metadata = json.contains("test_results");
        expect(has_metadata.has_value());

        const auto tuple_str = [](const auto colour_tuple) {
          std::ostringstream ss;
          ss << "(" << static_cast<int>(std::get<0>(colour_tuple)) << "," << static_cast<int>(std::get<1>(colour_tuple))
             << "," << static_cast<int>(std::get<2>(colour_tuple)) << ")";
          return ss.str();
        };

        may_skip / then("Advanced tests") = [&] {
          std::unique_ptr<schema::Data> data;
          expect(nothrow([&] { data = std::make_unique<schema::Data>(json); }));
          const auto& results = json["test_results"];

          should("Correct colours") = [&] {
            const auto cases_boxes = results["colours_boxes"];
            for (const auto& test_case : cases_boxes) {
              const auto pallet = test_case[0].get<std::string>();
              const auto box_pos_id = test_case[1].get<std::string>();
              const auto exp_r = test_case[2][0].get<unsigned long long>();
              const auto exp_g = test_case[2][1].get<unsigned long long>();
              const auto exp_b = test_case[2][2].get<unsigned long long>();
              const auto exp_colour = std::make_tuple(exp_r, exp_g, exp_b);
              const auto& box_pos_colour = data->box_positions(pallet).at(box_pos_id).color();
              const auto colour = std::make_tuple(box_pos_colour.r, box_pos_colour.g, box_pos_colour.b);
              expect(colour == exp_colour) << "Incorrect box colour for box" << box_pos_id << "on pallet" << pallet
                                           << "! Expected:" << tuple_str(exp_colour) << ", got:" << tuple_str(colour);
            }
            const auto cases_boxtypes = results["colours_boxtypes"];
            for (const auto& test_case : cases_boxtypes) {
              const auto box_type_id = test_case[0].get<std::string>();
              const auto exp_r = test_case[1][0].get<unsigned long long>();
              const auto exp_g = test_case[1][1].get<unsigned long long>();
              const auto exp_b = test_case[1][2].get<unsigned long long>();
              const auto exp_colour = std::make_tuple(exp_r, exp_g, exp_b);
              const auto& box_pos_colour = data->box_types().at(box_type_id).color();
              const auto colour = std::make_tuple(box_pos_colour.r, box_pos_colour.g, box_pos_colour.b);
              expect(colour == exp_colour) << "Incorrect box colour for box type" << box_type_id
                                           << "! Expected:" << tuple_str(exp_colour) << ", got:" << tuple_str(colour);
            }
          };

          should("Correct pallet count") = [&] {
            const auto exp_pallet_count = results["pallet_count"].get<unsigned long long>();
            const auto pallet_count = data->pallets().size();
            expect(pallet_count == exp_pallet_count)
                << "Incorrect pallet count! Expected:" << exp_pallet_count << ", got:" << pallet_count;
          };

          should("Correct BoxPos count") = [&] {
            const auto cases = results["boxpos_counts"];
            for (const auto& test_case : cases) {
              const auto pallet_id = test_case[0].get<std::string>();
              const auto exp_box_pos_count = test_case[1].get<unsigned long long>();
              const auto& box_pos_count = data->box_positions(pallet_id).size();
              expect(box_pos_count == exp_box_pos_count)
                  << "Incorrect BoxPos count on pallet" << pallet_id << "! Expected:" << exp_box_pos_count
                  << ", got:" << box_pos_count;
            }
          };

          should("Correct BoxType count") = [&] {
            const auto exp_boxtype_count = results["boxtype_count"].get<unsigned long long>();
            const auto boxtype_count = data->box_types().size();
            expect(boxtype_count == exp_boxtype_count)
                << "Incorrect BoxType count! Expected:" << exp_boxtype_count << ", got:" << boxtype_count;
          };

          should("Correct BoxType params") = [&] {
            const auto cases_boxtype_params = results["boxtype_params"];
            for (const auto& test_case : cases_boxtype_params) {
              const auto box_type_id = test_case[0].get<std::string>();
              const auto& box_type = data->box_types().at(box_type_id);
              const auto box_type_json = box_type.json();
              expect(std::all_of(test_case[1].cbegin(), test_case[1].cend(),
                                 [&box_type_json](const nlohmann::json& case_pair) {
                                   return box_type_json[case_pair[0].get<std::string>()] == case_pair[1];
                                 }))
                  << "Incorrect parameters for BoxType" << box_type_id;
            }
          };

          should("Correct BoxType SKUs") = [&] {
            const auto cases_boxtypes = results["boxtype_skus"];
            for (const auto& test_case : cases_boxtypes) {
              const auto box_type_id = test_case[0].get<std::string>();
              const auto& box_type = data->box_types().at(box_type_id);
              std::unordered_map<std::string, std::size_t> item_counts;
              std::for_each(
                  box_type.items().cbegin(), box_type.items().cend(),
                  [&item_counts](const schema::BoxType::Item& box_type_item) { item_counts[box_type_item.sku_id]++; });
              expect(std::all_of(test_case[1].cbegin(), test_case[1].cend(),
                                 [&item_counts](const nlohmann::json& item_count) {
                                   return item_counts.at(item_count[0].get<std::string>()) ==
                                          item_count[1].get<std::size_t>();
                                 }))
                  << "Incorrect item count for BoxType" << box_type_id;
            }
          };

          should("Correct BoxPos coordinates") = [&] {
            const auto cases_boxpos_coordinates = results["boxpos_coordinates"];
            for (const auto& test_case : cases_boxpos_coordinates) {
              const auto pallet = test_case[0].get<std::string>();
              const auto box_pos_id = test_case[1].get<std::string>();
              const auto exp_min_x = test_case[2][0].get<double>();
              const auto exp_min_y = test_case[2][1].get<double>();
              const auto exp_min_z = test_case[2][2].get<double>();
              const auto exp_max_x = test_case[3][0].get<double>();
              const auto exp_max_y = test_case[3][1].get<double>();
              const auto exp_max_z = test_case[3][2].get<double>();
              const auto exp_min = std::make_tuple(exp_min_x, exp_min_y, exp_min_z);
              const auto exp_max = std::make_tuple(exp_max_x, exp_max_y, exp_max_z);

              const auto box_pos_bb = *(data->box_positions(pallet).at(box_pos_id).bounding_box());
              const auto& box_pos_min = std::make_tuple(box_pos_bb.min.x, box_pos_bb.min.y, box_pos_bb.min.z);
              const auto& box_pos_max = std::make_tuple(box_pos_bb.max.x, box_pos_bb.max.y, box_pos_bb.max.z);

              expect(exp_min == box_pos_min)
                  << "Incorrect min box position for box" << box_pos_id << "on pallet" << pallet
                  << "! Expected:" << tuple_str(exp_min) << ", got:" << tuple_str(box_pos_min);
              expect(exp_max == box_pos_max)
                  << "Incorrect max box position for box" << box_pos_id << "on pallet" << pallet
                  << "! Expected:" << tuple_str(exp_max) << ", got:" << tuple_str(box_pos_max);
            }
          };
        };
      };
    };
  }
}