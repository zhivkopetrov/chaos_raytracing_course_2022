#ifndef CRT_PIXELREGION_H_
#define CRT_PIXELREGION_H_

// System headers
#include <random>

// Other libraries headers
#include "utils/rendering/color/Color24.h"

// Own components headers
#include "crt/defines/CrtDefines.h"

// Forward declarations

class PixelRegion {
public:
  PixelRegion() = delete;

  static std::vector<Color24> produceRandomized(int32_t regionWidth,
                                                int32_t regionHeight,
                                                PixelRegionType type,
                                                std::mt19937 &generator);

  static void copy(int32_t regionWidth, int32_t regionHeight,
                   int32_t imageWidth, const std::vector<Color24> &srcPixels,
                   Color24 *destPixels);
};

#endif /* CRT_PIXELREGION_H_ */
