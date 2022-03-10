#ifndef RAYS_RAYSSCENE_H_
#define RAYS_RAYSSCENE_H_

// System headers
#include <vector>

// Other libraries headers
#include "utils/geometry/Vec3f.h"
#include "utils/geometry/Ray.h"

// Own components headers

// Forward declarations

struct RaysSceneConfig {
  Point3f origin;
  float distanceFromCamera{};
  int32_t imageWidth{};
  int32_t imageHeight{};
};

class RaysScene {
public:
  void compose(const RaysSceneConfig &cfg);
  std::vector<Color24> produceSceneGradient() const;

private:
  RaysSceneConfig _cfg;
  std::vector<Ray> _sceneRays;
};

#endif /* RAYS_RAYSSCENE_H_ */
