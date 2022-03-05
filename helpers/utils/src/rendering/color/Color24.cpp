// Corresponding header
#include "utils/rendering/color/Color24.h"

// System headers
#include <ostream>

// Other libraries headers

// Own components headers

namespace Colors24 {
const Color24 RED(255, 0, 0);
const Color24 GREEN(0, 255, 0);
const Color24 BLUE(0, 0, 255);
const Color24 BLACK(0, 0, 0);
const Color24 WHITE(255, 255, 255);
const Color24 CYAN(0, 255, 255);
const Color24 MAGENTA(255, 0, 255);
const Color24 YELLOW(255, 255, 0);
const Color24 ORANGE(255, 128, 0);
} // namespace Colors24

Color24::Color24(uint32_t inputrgb) {
  rgb.r = static_cast<uint8_t>( (inputrgb & 0xFF000000) >> 24);
  rgb.g = static_cast<uint8_t>( (inputrgb & 0x00FF0000) >> 16);
  rgb.b = static_cast<uint8_t>( (inputrgb & 0x0000FF00) >> 8);
}

Color24::Color24(uint8_t red, uint8_t green, uint8_t blue) {
  rgb.r = red;
  rgb.g = green;
  rgb.b = blue;
}

bool Color24::operator==(const Color24 &other) const {
  return (rgb.r == other.rgb.r) && (rgb.g == other.rgb.g)
         && (rgb.b == other.rgb.b);
}

bool Color24::operator!=(const Color24 &other) const {
  return ! (*this == other);
}

uint32_t Color24::get24BitRgbPalette() const {
  return (rgb.r & 0xFF000000) | (rgb.g & 0x00FF0000) | (rgb.b & 0x0000FF00);
}

std::ostream& operator<<(std::ostream &out, const Color24 &color) {
  const auto &rgb = color.rgb;
  out << static_cast<int32_t>(rgb.r) << ' ' << static_cast<int32_t>(rgb.g)
      << ' ' << static_cast<int32_t>(rgb.b) << '\t';
  return out;
}

