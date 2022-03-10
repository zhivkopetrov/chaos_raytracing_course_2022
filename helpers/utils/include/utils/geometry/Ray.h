#ifndef UTILS_RAY_H_
#define UTILS_RAY_H_

// System headers

// Other libraries headers

// Own components headers
#include "utils/geometry/Vec3f.h"

// Forward declarations

class Ray {
public:
  Ray() = default;
  Ray(const Point3f &origin, const Point3f &direction);

  Point3f origin() const;
  Vec3f direction() const;

private:
  Point3f _orig;
  Vec3f _dir;
};
#endif /* UTILS_RAY_H_ */
