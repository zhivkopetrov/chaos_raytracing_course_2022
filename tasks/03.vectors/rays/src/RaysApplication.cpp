// Corresponding header
#include "rays/RaysApplication.h"

// System headers

// Other libraries headers
#include "utils/time/Time.h"
#include "utils/log/Log.h"

// Own components headers

ErrorCode RaysApplication::run(const RaysConfig &cfg) {
  Time time;

  const RaysSceneConfig sceneCfg = { .origin = Point3f(0, 0, 0),
      .distanceFromCamera = -1.0f, .imageWidth = cfg.imageCfg.width,
      .imageHeight = cfg.imageCfg.height };
  _scene.compose(sceneCfg);
  const auto pixels = _scene.produceSceneGradient();

  const auto err = saveOutput(cfg.imageCfg, pixels);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("CrtApplication::saveOutput() failed");
    return ErrorCode::FAILURE;
  }

  const auto elapsedMs = time.getElapsed().toMilliseconds();
  const auto &imageCfg = cfg.imageCfg;
  LOGG("Successfully generated [%s - %dx%d] in %zu ms", imageCfg.name.c_str(),
      imageCfg.width, imageCfg.height, elapsedMs);

  return ErrorCode::SUCCESS;
}

ErrorCode RaysApplication::saveOutput(const ImageConfig &cfg,
                                      const std::vector<Color24> &pixels) {
  const PpmHeader header = { .version = PpmVersion::P6, .imageWidth = cfg.width,
      .imageHeight = cfg.height, .maxColorComponent = 255 };

  const auto err = _writter.writeFile(cfg.name, header, pixels);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("writter.writeFile() failed");
    return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}

