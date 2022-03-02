#ifndef UTILS_COLOR24_H_
#define UTILS_COLOR24_H_

// System headers
#include <cstdint>
#include <iosfwd>

// Other libraries headers

// Own components headers

struct RGB {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
};

class Color24 {
public:
  // forbid default constructor
  Color24() = delete;

  /** Warning: if you use this constructor be sure to provide proper
   *           24bit RGB color.
   *
   *           alpha channel for 32bit colors (if any) will be discarded
   * */
  explicit Color24(uint32_t inputRgb);

  explicit Color24(uint8_t red, uint8_t green, uint8_t blue);

  bool operator==(const Color24 &other) const;
  bool operator!=(const Color24 &other) const;

  uint32_t get24BitRgbPalette() const;

  RGB rgb;
};

std::ostream& operator<<(std::ostream &out, const Color24& color);

namespace Colors24 {
extern const Color24 RED;
extern const Color24 GREEN;
extern const Color24 BLUE;
extern const Color24 BLACK;
extern const Color24 WHITE;
extern const Color24 CYAN;
extern const Color24 MAGENTA;
extern const Color24 YELLOW;
extern const Color24 ORANGE;
extern const Color24 PURPLE;
} // namespace Colors24

#endif /* UTILS_COLOR24_H_ */
