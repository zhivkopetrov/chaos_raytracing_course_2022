#ifndef RAYS_RAYSSCENE_H_
#define RAYS_RAYSSCENE_H_

// System headers
#include <vector>

// Other libraries headers
#include "utils/geometry/Vec3f.h"
#include "utils/geometry/Ray.h"
#include "utils/geometry/Triangle.h"

// Own components headers

// Forward declarations

struct SingleTriangleSceneConfig {
  Triangle targetTriangle;
  Point3f origin;
  float distanceFromCamera{};
  int32_t imageWidth{};
  int32_t imageHeight{};
};

class SingleTriangleScene {
public:
  void compose(const SingleTriangleSceneConfig &cfg);
  std::vector<Color24> produceImage() const;

private:
  SingleTriangleSceneConfig _cfg;
  std::vector<Ray> _sceneRays;
  Triangle _triangle;
};

#endif /* RAYS_RAYSSCENE_H_ */
