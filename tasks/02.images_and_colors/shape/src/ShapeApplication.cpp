// Corresponding header
#include "shape/ShapeApplication.h"

// System headers
#include <iostream>

// Other libraries headers
#include "utils/time/Time.h"

// Own components headers
#include "shape/helpers/BatmanWorkDispatcher.h"

ErrorCode ShapeApplication::run(const ShapeConfig &cfg) {
  Time time;
  const auto &imageCfg = cfg.imageCfg;
  const auto pixels = BatmanWorkDispatcher::calculateGeometry(
      cfg.batmanShapeCfg, imageCfg.width, imageCfg.height);

  const auto err = saveOutput(cfg.imageCfg, pixels);
  if (ErrorCode::SUCCESS != err) {
    std::cerr << "ShapeApplication::saveOutput() failed" << std::endl;
    return ErrorCode::FAILURE;
  }

  const auto elapsedMs = time.getElapsed().toMilliseconds();
  std::cout << "Successfully generated [" << imageCfg.name << " - "
            << imageCfg.width << 'x' << imageCfg.height << "] in " << elapsedMs
            << "ms\n";

  return ErrorCode::SUCCESS;
}

ErrorCode ShapeApplication::saveOutput(const ImageConfig &cfg,
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

