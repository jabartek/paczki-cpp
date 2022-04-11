#include "utils/png.h"

namespace janowski::paczki_cpp::utils {

constexpr std::array<char, 64> b64_map{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
    'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
    's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/',
};

std::string toPngBase64(const ::Image& image) {
  return toPngBase64(
      {reinterpret_cast<std::uint8_t*>(image.data), static_cast<std::size_t>(image.width * image.height)}, image.width,
      image.height);
}

std::string toPngBase64(std::span<std::uint8_t> image, std::size_t width, std::size_t height) {
  std::vector<unsigned char> png_image;
  png_image.resize(1000);
  lodepng::encode(png_image, reinterpret_cast<const unsigned char*>(image.data()), width, height);
  png_image.resize(((png_image.size() + 2) / 3) * 3, 0);

  auto b64_len = (png_image.size() / 3) * 4;
  std::string png_image_b64(b64_len, '=');
  for (size_t i = 0; i < png_image.size(); i += 3) {
    auto val = (png_image[i] << 16) + (png_image[i + 1] << 8) + (png_image[i + 2] << 0);
    constexpr auto m_a = 0b111111000000000000000000;
    constexpr auto m_b = 0b000000111111000000000000;
    constexpr auto m_c = 0b000000000000111111000000;
    constexpr auto m_d = 0b000000000000000000111111;
    const auto a = (val & m_a) >> 18;
    const auto b = (val & m_b) >> 12;
    const auto c = (val & m_c) >> 6;
    const auto d = (val & m_d) >> 0;
    auto s_i = i / 3 * 4;
    png_image_b64[s_i] = b64_map[a];
    png_image_b64[s_i + 1] = b64_map[b];
    png_image_b64[s_i + 2] = b64_map[c];
    png_image_b64[s_i + 3] = b64_map[d];
  }
  return png_image_b64;
}
}  // namespace janowski::paczki_cpp::utils
