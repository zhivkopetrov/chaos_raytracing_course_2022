// Corresponding header
#include "crt/geometry/PixelRegion.h"

// System headers

// Other libraries headers
#include "utils/data_type/EnumClassUtils.h"
#include "utils/log/Log.h"

// Own components headers

namespace {

void randomizeRedComponent(std::mt19937 &generator,
                           std::vector<Color24> &outPixels) {
  std::uniform_real_distribution<float> distr(0.0f, 255.999f);
  for (auto &pixel : outPixels) {
    pixel.setX(distr(generator));
  }
}

void randomizeGreenComponent(std::mt19937 &generator,
                             std::vector<Color24> &outPixels) {
  std::uniform_real_distribution<float> distr(0.0f, 255.999f);
  for (auto &pixel : outPixels) {
    pixel.setY(distr(generator));
  }
}

void randomizeBlueComponent(std::mt19937 &generator,
                            std::vector<Color24> &outPixels) {
  std::uniform_real_distribution<float> distr(0.0f, 255.999f);
  for (auto &pixel : outPixels) {
    pixel.setZ(distr(generator));
  }
}

} //end anonymous namespace

std::vector<Color24> PixelRegion::produceRandomized(int32_t regionWidth,
                                                    int32_t regionHeight,
                                                    PixelRegionType type,
                                                    std::mt19937 &generator) {
  std::vector<Color24> pixels(regionWidth * regionHeight, Colors24::BLACK);
  switch (type) {
  case PixelRegionType::RED:
    randomizeRedComponent(generator, pixels);
    break;
  case PixelRegionType::GREEN:
    randomizeGreenComponent(generator, pixels);
    break;
  case PixelRegionType::BLUE:
    randomizeBlueComponent(generator, pixels);
    break;
  case PixelRegionType::YELLOW:
    randomizeRedComponent(generator, pixels);
    randomizeGreenComponent(generator, pixels);
    break;
  case PixelRegionType::MAGENTA:
    randomizeRedComponent(generator, pixels);
    randomizeBlueComponent(generator, pixels);
    break;
  case PixelRegionType::CYAN:
    randomizeGreenComponent(generator, pixels);
    randomizeBlueComponent(generator, pixels);
    break;
  default:
    LOGERR("Error, received unsupported PixelRegionType: %d. "
           "Returning result for PixelRegionType::RED", getEnumValue(type));
    randomizeRedComponent(generator, pixels);
    break;
  }

  return pixels;
}

void PixelRegion::copy(int32_t regionWidth, int32_t regionHeight,
                       int32_t imageWidth,
                       const std::vector<Color24> &srcPixels,
                       Color24 *destPixels) {
  int32_t offset = 0;
  int32_t srcPixelId = 0;
  for (int32_t row = 0; row < regionHeight; ++row) {
    for (int32_t col = 0; col < regionWidth; ++col) {
      destPixels[offset] = srcPixels[srcPixelId];
      ++offset;
      ++srcPixelId;
    }

    //move to next image row
    offset += (imageWidth - regionWidth);
  }
}

