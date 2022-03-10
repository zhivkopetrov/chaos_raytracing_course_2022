// Corresponding header
#include "utils/geometry/Ray.h"

// System headers

// Other libraries headers

// Own components headers

Ray::Ray(const Point3f &origin, const Point3f &direction)
    : _orig(origin), _dir(direction) {
}

Point3f Ray::origin() const {
  return _orig;
}

Vec3f Ray::direction() const {
  return _dir;
}
