// Corresponding header
#include "rays/scene/RaysScene.h"

// System headers

// Other libraries headers
#include "utils/geometry/CoordinateTransform.h"

// Own components headers

void RaysScene::compose(const RaysSceneConfig &cfg) {
  _cfg = cfg;

  const auto raster = CoordinateTransform::getMidPixelRaster(_cfg.imageWidth,
      _cfg.imageHeight);
  const bool normalize = true;

  const auto worldDirVectors = CoordinateTransform::getWorldDirVectors(raster,
      _cfg.distanceFromCamera, _cfg.imageWidth, _cfg.imageHeight, normalize);

  _sceneRays.reserve(worldDirVectors.size());
  for (const auto &dirVector : worldDirVectors) {
    _sceneRays.emplace_back(_cfg.origin, dirVector);
  }
}

std::vector<Color24> RaysScene::produceSceneGradient() const {
  std::vector<Color24> pixels;
  pixels.reserve(_sceneRays.size());

  for (const auto &ray : _sceneRays) {
    pixels.push_back(ray.color24());
  }

  return pixels;
}
