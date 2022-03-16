// Corresponding header
#include "single_triangle/SingleTriangleApplication.h"

// System headers

// Other libraries headers
#include "utils/time/Time.h"
#include "utils/log/Log.h"

// Own components headers

ErrorCode SingleTriangleApplication::run(const SingleTriangleConfig &cfg) {
  Time time;

  _scene.compose(generateSceneConfig(cfg));
  const auto pixels = _scene.produceImage();

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

ErrorCode SingleTriangleApplication::saveOutput(
    const ImageConfig &cfg, const std::vector<Color24> &pixels) {
  const PpmHeader header = { .version = PpmVersion::P6, .imageWidth = cfg.width,
      .imageHeight = cfg.height, .maxColorComponent = 255 };

  const auto err = _writter.writeFile(cfg.name, header, pixels);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("writter.writeFile() failed");
    return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}

SingleTriangleSceneConfig SingleTriangleApplication::generateSceneConfig(
    const SingleTriangleConfig &cfg) const {
  SingleTriangleSceneConfig sceneCfg;
  sceneCfg.origin = Point3f(0, 0, 0);
  sceneCfg.distanceFromCamera = -1.0f;
  sceneCfg.imageWidth = cfg.imageCfg.width;
  sceneCfg.imageHeight = cfg.imageCfg.height;

  const Vec3f v0(-1.75f, -1.75f, -3.0f);
  const Vec3f v1(1.75f, -1.75f, -3.0f);
  const Vec3f v2(0.0f, 1.75f, -3.0f);
  sceneCfg.targetTriangle = Triangle(v0, v1, v2);

  return sceneCfg;
}

