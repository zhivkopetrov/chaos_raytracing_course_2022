// Corresponding header
#include "crt/CrtApplication.h"

// System headers

// Other libraries headers
#include "utils/time/Time.h"
#include "utils/log/Log.h"

// Own components headers
#include "crt/strategy/CrtStrategyFactory.h"

ErrorCode CrtApplication::run(const CrtConfig &cfg) {
  Time time;
  auto strategy = CrtStrategyFactory::createStrategy(cfg.strategyCfg);
  if (!strategy) {
    LOGERR("CrtStrategyFactory::createStrategy() failed");
    return ErrorCode::FAILURE;
  }

  const auto pixels = strategy->generatePixelRegions(cfg.imageCfg,
      cfg.pixelRegionCfg);

  const auto err = saveOutput(cfg.imageCfg, pixels);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("CrtApplication::saveOutput() failed");
    return ErrorCode::FAILURE;
  }

  const auto elapsedMs = time.getElapsed().toMilliseconds();
  const auto &imageCfg = cfg.imageCfg;
  LOGG("Successfully generated [%s - %dx%d] in %zu ms",
       imageCfg.name.c_str(), imageCfg.width, imageCfg.height, elapsedMs);

  return ErrorCode::SUCCESS;
}

ErrorCode CrtApplication::saveOutput(const ImageConfig &cfg,
                                     const std::vector<Color24> &pixels) {
  const PpmHeader header = { .version = PpmVersion::P3, .imageWidth = cfg.width,
      .imageHeight = cfg.height, .maxColorComponent = 255 };

  const auto err = _writter.writeFile(cfg.name, header, pixels);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("writter.writeFile() failed");
    return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}

