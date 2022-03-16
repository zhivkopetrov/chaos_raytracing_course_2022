// Corresponding header
#include "single_triangle/scene/SingleTriangleScene.h"

// System headers

// Other libraries headers
#include "utils/geometry/CoordinateTransform.h"

// Own components headers

void SingleTriangleScene::compose(const SingleTriangleSceneConfig &cfg) {
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

std::vector<Color24> SingleTriangleScene::produceImage() const {
  std::vector<Color24> pixels;
  pixels.reserve(_sceneRays.size());

  float rayToIntersectDist = 0.0f;
  for (const auto &ray : _sceneRays) {
    const bool intersects =
        _cfg.targetTriangle.intersects(ray, rayToIntersectDist);

    pixels.push_back(intersects ? Colors24::GRAY : Colors24::BLACK);
  }

  return pixels;
}
