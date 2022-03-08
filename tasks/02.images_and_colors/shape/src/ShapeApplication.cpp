// Corresponding header
#include "shape/ShapeApplication.h"

// System headers

// Other libraries headers
#include "utils/time/Time.h"
#include "utils/log/Log.h"

// Own components headers
#include "shape/helpers/BatmanTaskDispatcher.h"

ErrorCode ShapeApplication::run(const ShapeConfig &cfg) {
  Time time;
  const auto &imageCfg = cfg.imageCfg;
  const auto pixels = BatmanTaskDispatcher::calculateGeometry(
      cfg.batmanShapeCfg, imageCfg.width, imageCfg.height);

  const auto err = saveOutput(cfg.imageCfg, pixels);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("ShapeApplication::saveOutput() failed");
    return ErrorCode::FAILURE;
  }

  const auto elapsedMs = time.getElapsed().toMilliseconds();
  LOGG("Successfully generated [%s - %dx%d] in %lld ms",
       imageCfg.name.c_str(), imageCfg.width, imageCfg.height, elapsedMs);

  return ErrorCode::SUCCESS;
}

ErrorCode ShapeApplication::saveOutput(const ImageConfig &cfg,
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

