// Corresponding header
#include "crt/CrtApplication.h"

// System headers
#include <iostream>

// Other libraries headers
#include "utils/time/Time.h"

// Own components headers
#include "crt/strategy/CrtStrategyFactory.h"

ErrorCode CrtApplication::run(const CrtConfig &cfg) {
  Time time;
  auto strategy = CrtStrategyFactory::createStrategy(cfg.strategyCfg);
  if (!strategy) {
    std::cerr << "CrtStrategyFactory::createStrategy() failed" << std::endl;
    return ErrorCode::FAILURE;
  }

  const auto pixels = strategy->generatePixelRegions(cfg.imageCfg,
      cfg.pixelRegionCfg);

  const auto err = saveOutput(cfg.imageCfg, pixels);
  if (ErrorCode::SUCCESS != err) {
    std::cerr << "CrtApplication::saveOutput() failed" << std::endl;
    return ErrorCode::FAILURE;
  }

  const auto elapsedMs = time.getElapsed().toMilliseconds();
  const auto &imageCfg = cfg.imageCfg;
  std::cout << "Successfully generated [" << imageCfg.name << " - "
            << imageCfg.width << 'x' << imageCfg.height << "] in " << elapsedMs
            << "ms\n";

  return ErrorCode::SUCCESS;
}

ErrorCode CrtApplication::saveOutput(const ImageConfig &cfg,
                                     const std::vector<Color24> &pixels) {
  const PpmHeader header = { .version = PpmVersion::P3, .imageWidth = cfg.width,
      .imageHeight = cfg.height, .maxColorComponent = 255 };

  const auto err = _writter.writeFile(cfg.name, header, pixels);
  if (ErrorCode::SUCCESS != err) {
    std::cerr << "writter.writeFile() failed" << std::endl;
    return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}

