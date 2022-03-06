// Corresponding header
#include "crt/config/CrtConfigLoader.h"

// System headers

// Other libraries headers

// Own components headers
#include "crt/defines/CrtDefines.h"

namespace {
//TODO read values from a file
constexpr auto FILE_NAME = "crt.ppm";
constexpr auto IMAGE_WIDTH = 1920;
constexpr auto IMAGE_HEIGHT = 1080;
constexpr auto PIXEL_REGION_ROWS = 12;
constexpr auto PIXEL_REGIONS_PER_ROW = 8;

constexpr auto STRATEGY_IDENTIFIER = "multiple_producers";
constexpr auto WORKER_THREADS_HINT = 0;
}

CrtConfig CrtConfigLoader::loadConfig() {
  CrtConfig cfg;

  auto& imageCfg = cfg.imageCfg;
  imageCfg.name = FILE_NAME;
  imageCfg.width = IMAGE_WIDTH;
  imageCfg.height = IMAGE_HEIGHT;

  auto& pixelRegionCfg = cfg.pixelRegionCfg;
  pixelRegionCfg.pixelRegionsRows = PIXEL_REGION_ROWS;
  pixelRegionCfg.pixelRegionsPerRow = PIXEL_REGIONS_PER_ROW;

  auto& strategyCfg = cfg.strategyCfg;
  strategyCfg.strategy = parseStrategy(STRATEGY_IDENTIFIER);
  strategyCfg.workerThreadsHint = WORKER_THREADS_HINT;

  return cfg;
}
