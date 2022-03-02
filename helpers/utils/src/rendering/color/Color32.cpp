// Corresponding header
#include "utils/rendering/color/Color32.h"

// System headers

// Other libraries headers

// Own components headers

namespace Colors32 {
const Color32 RED(255, 0, 0, 255);
const Color32 GREEN(0, 255, 0, 255);
const Color32 BLUE(0, 0, 255, 255);
const Color32 BLACK(0, 0, 0, 255);
const Color32 WHITE(255, 255, 255, 255);
const Color32 CYAN(0, 255, 255, 255);
const Color32 MAGENTA(255, 0, 255, 255);
const Color32 YELLOW(255, 255, 0, 255);
const Color32 ORANGE(255, 128, 0, 255);
const Color32 PURPLE(128, 0, 128, 255);
const Color32 FULL_TRANSPARENT(0, 0, 0, 0);
} // namespace Colors32

Color32::Color32(uint32_t inputRgba) {
  rgba.r = static_cast<uint8_t>( (inputRgba & 0xFF000000) >> 24);
  rgba.g = static_cast<uint8_t>( (inputRgba & 0x00FF0000) >> 16);
  rgba.b = static_cast<uint8_t>( (inputRgba & 0x0000FF00) >> 8);
  rgba.a = static_cast<uint8_t>( (inputRgba & 0x000000FF));
}

Color32::Color32(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
  rgba.r = red;
  rgba.g = green;
  rgba.b = blue;
  rgba.a = alpha;
}

bool Color32::operator==(const Color32 &other) const {
  return (rgba.r == other.rgba.r) && (rgba.g == other.rgba.g)
         && (rgba.b == other.rgba.b) && (rgba.a == other.rgba.a);
}

bool Color32::operator!=(const Color32 &other) const {
  return ! (*this == other);
}

uint32_t Color32::get32BitRgbaPalette() const {
  return (rgba.r & 0xFF000000) | (rgba.g & 0x00FF0000) | (rgba.b & 0x0000FF00)
         | (rgba.a & 0x000000FF);
}


