// Corresponding header
#include "crt/strategy/CrtSingleThread.h"

// System headers
#include <random>
#include <array>

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

  constexpr auto colorPatternSize = 6;
  constexpr std::array<PixelRegionType, colorPatternSize> colorPatterns {
      PixelRegionType::RED, PixelRegionType::GREEN, PixelRegionType::BLUE,
      PixelRegionType::YELLOW, PixelRegionType::MAGENTA, PixelRegionType::CYAN };

  auto patternId = 0;
  for (int32_t row = 0; row < regionRows; ++row) {
    for (int32_t col = 0; col < regionCols; ++col) {
      const auto regionPixels = PixelRegion::produceRandomized(regionWidth,
          regionHeight, colorPatterns[patternId], mt);

      const auto imgPixelOffset = (row * regionHeight * imageCfg.width)
          + (col * regionWidth);

      PixelRegion::copy(regionWidth, regionHeight, imageCfg.width, regionPixels,
          &imagePixels[imgPixelOffset]);

      ++patternId;
      if (colorPatternSize == patternId) {
        patternId = 0;
      }
    }
  }

  return imagePixels;
}

