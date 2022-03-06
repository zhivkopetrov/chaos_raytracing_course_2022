// Corresponding header
#include "crt/strategy/CrtSingleThread.h"

// System headers
#include <random>

// Other libraries headers

// Own components headers
#include "crt/geometry/PixelRegion.h"

std::vector<Color24> CrtSingleThread::generatePixelRegions(
    const ImageConfig &imageCfg, const PixelRegionConfig &pixelRegionCfg) {
  std::vector<Color24> imagePixels(imageCfg.width * imageCfg.height,
      Colors24::BLACK);
  std::mt19937 mt(std::random_device { }());

  const auto regionRows = pixelRegionCfg.pixelRegionsRows;
  const auto regionCols = pixelRegionCfg.pixelRegionsPerRow;
  const auto regionWidth = imageCfg.width / regionCols;
  const auto regionHeight = imageCfg.height / regionRows;

  auto patternId = 0;
  for (int32_t row = 0; row < regionRows; ++row) {
    for (int32_t col = 0; col < regionCols; ++col) {
      const auto regionPixels = PixelRegion::produceRandomized(regionWidth,
          regionHeight, _colorPattern[patternId % COLOR_PATTERN_SIZE], mt);
      ++patternId;

      const auto imgPixelOffset = (row * regionHeight * imageCfg.width)
          + (col * regionWidth);

      PixelRegion::copy(regionWidth, regionHeight, imageCfg.width, regionPixels,
          &imagePixels[imgPixelOffset]);
    }
  }

  return imagePixels;
}

