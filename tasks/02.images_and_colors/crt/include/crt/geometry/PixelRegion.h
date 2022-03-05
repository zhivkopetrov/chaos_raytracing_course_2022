#ifndef CRT_PIXELREGION_H_
#define CRT_PIXELREGION_H_

// System headers
#include <random>

// Other libraries headers
#include "utils/rendering/color/Color24.h"

// Own components headers

// Forward declarations

enum class PixelRegionType {
  RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN
};

class PixelRegion {
public:
  PixelRegion() = delete;

  static void randomize(PixelRegionType type, std::mt19937 &generator,
                        std::vector<Color24> &outPixels);

};

#endif /* CRT_PIXELREGION_H_ */
