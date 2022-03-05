// Corresponding header
#include "crt/helpers/CrtWorkDispatcher.h"

// System headers

// Other libraries headers

// Own components headers
#include "crt/geometry/PixelRegion.h"

void copyRegionPixels(int32_t regionWidth, int32_t regionHeight,
                      int32_t imageWidth,
                      const std::vector<Color24> &regionPixels,
                      Color24 *outImagePixels) {
  int32_t offset = 0;
  int32_t regionPixelId = 0;
  for (int32_t row = 0; row < regionHeight; ++row) {
    for (int32_t col = 0; col < regionWidth; ++col) {
      outImagePixels[offset] = regionPixels[regionPixelId];
      ++offset;
      ++regionPixelId;
    }

    offset += imageWidth;
  }
}

std::vector<Color24> CrtWorkDispatcher::generatePixelRegions(
    const CrtConfig &cfg) {
  std::vector<Color24> imagePixels(cfg.imageCfg.width * cfg.imageCfg.height,
      Colors24::BLACK);

  const auto regionWidth = cfg.imageCfg.width
      / cfg.pixelRegionCfg.pixelRegionsPerRow;
  const auto regionHeight = cfg.imageCfg.height
      / cfg.pixelRegionCfg.pixelRegionsRows;

  std::random_device rd;
  std::mt19937 mt(rd());

  std::vector<Color24> regionPixels(regionWidth * regionHeight,
      Colors24::BLACK);
  for (int32_t row = 0; row < cfg.pixelRegionCfg.pixelRegionsRows; ++row) {
    for (int32_t col = 0; col < cfg.pixelRegionCfg.pixelRegionsPerRow; ++col) {
      PixelRegion::randomize(PixelRegionType::CYAN, mt, regionPixels);

      const int32_t imagePixelOffset = (row * regionHeight)
          + (col * regionWidth);
      copyRegionPixels(regionWidth, regionHeight, cfg.imageCfg.width,
          regionPixels, &imagePixels[imagePixelOffset]);
    }
  }

  return imagePixels;
}
