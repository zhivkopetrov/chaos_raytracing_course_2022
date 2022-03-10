#ifndef RAYS_RAYSSCENE_H_
#define RAYS_RAYSSCENE_H_

// System headers
#include <vector>

// Other libraries headers
#include "utils/geometry/Vec3f.h"

// Own components headers

// Forward declarations

class RaysScene {
public:
  void compose(const Point3f &origin, float distanceFromCamera);
//  std::vector<Vec3f>

private:
  Point3f _origin;
  std::vector<Vec3f> _worldDirVectors;
};

#endif /* RAYS_RAYSSCENE_H_ */
