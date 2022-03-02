#ifndef UTILS_COLOR32_H_
#define UTILS_COLOR32_H_

// System headers
#include <cstdint>
#include <iosfwd>

// Other libraries headers

// Own components headers

struct RGBA {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  uint8_t a = 255;
};

class Color32 {
public:
  // forbid default constructor
  Color32() = delete;

  /** Warning: if you use this constructor be sure to provide proper
   *           32bit RGBA color.
   *
   *           24bit RGB colors will be misinterpreted. If you have
   *           24bit RGB color hex that you want to use simply add
   *           two trailing FF's at the end of your 24bit hex value.
   *
   *  Example: 24bit RGB hex: 0xF100A3   should be transformed to
   *                          0xF100A3FF
   *           before passed to this constructor
   * */
  explicit Color32(uint32_t inputRgba);

  explicit Color32(uint8_t red, uint8_t green, uint8_t blue,
                   uint8_t alpha = 255);

  bool operator==(const Color32 &other) const;
  bool operator!=(const Color32 &other) const;

  uint32_t get32BitRgbaPalette() const;

  RGBA rgba;
};

namespace Colors32 {
extern const Color32 RED;
extern const Color32 GREEN;
extern const Color32 BLUE;
extern const Color32 BLACK;
extern const Color32 WHITE;
extern const Color32 CYAN;
extern const Color32 MAGENTA;
extern const Color32 YELLOW;
extern const Color32 ORANGE;
extern const Color32 PURPLE;
extern const Color32 FULL_TRANSPARENT;
} // namespace Colors32

#endif /* UTILS_COLOR32_H_ */
