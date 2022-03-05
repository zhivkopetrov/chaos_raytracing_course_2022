// Corresponding header
#include "crt/geometry/PixelRegion.h"

// System headers
#include <iostream>

// Other libraries headers
#include "utils/data_type/EnumClassUtils.h"

// Own components headers

namespace {
void randomizeRedComponent(std::mt19937 &generator,
                           std::vector<Color24> &outPixels) {
  std::uniform_int_distribution<> distr(0, 255);
  for (auto &pixel : outPixels) {
    pixel.rgb.r = distr(generator);
  }
}

void randomizeGreenComponent(std::mt19937 &generator,
                             std::vector<Color24> &outPixels) {
  std::uniform_int_distribution<> distr(0, 255);
  for (auto &pixel : outPixels) {
    pixel.rgb.g = distr(generator);
  }
}

void randomizeBlueComponent(std::mt19937 &generator,
                            std::vector<Color24> &outPixels) {
  std::uniform_int_distribution<> distr(0, 255);
  for (auto &pixel : outPixels) {
    pixel.rgb.b = distr(generator);
  }
}
}
void PixelRegion::randomize(PixelRegionType type, std::mt19937 &generator,
                            std::vector<Color24> &outPixels) {
  switch (type) {
  case PixelRegionType::RED:
    randomizeRedComponent(generator, outPixels);
    break;
  case PixelRegionType::GREEN:
    randomizeGreenComponent(generator, outPixels);
    break;
  case PixelRegionType::BLUE:
    randomizeBlueComponent(generator, outPixels);
    break;
  case PixelRegionType::YELLOW:
    randomizeRedComponent(generator, outPixels);
    randomizeGreenComponent(generator, outPixels);
    break;
  case PixelRegionType::MAGENTA:
    randomizeRedComponent(generator, outPixels);
    randomizeBlueComponent(generator, outPixels);
    break;
  case PixelRegionType::CYAN:
    randomizeGreenComponent(generator, outPixels);
    randomizeBlueComponent(generator, outPixels);
    break;
  default:
    std::cerr << "Error, received unsupported PixelRegionType: "
              << getEnumValue(type)
              << ". Returrning result for PixelRegionType::RED" << std::endl;
    randomizeRedComponent(generator, outPixels);
    break;
  }
}
