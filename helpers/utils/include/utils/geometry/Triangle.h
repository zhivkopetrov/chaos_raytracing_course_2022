#ifndef HELPERS_UTILS_INCLUDE_UTILS_GEOMETRY_TRIANGLE_H_
#define HELPERS_UTILS_INCLUDE_UTILS_GEOMETRY_TRIANGLE_H_

// System headers

// Other libraries headers

// Own components headers
#include "utils/geometry/Ray.h"

constexpr auto vertsInTriangle = 3;

// Forward declarations

class Triangle {
public:
  Triangle() = default;
  Triangle(const Vec3f &v0, const Vec3f &v1, const Vec3f &v2);

  bool intersects(const Ray &ray, float &outRayToIntersectDistance) const;

  Vec3f getNormal() const;

  bool isParallel(float normalDotRayDir) const;

private:
  Vec3f _verts[vertsInTriangle];
};

#endif /* HELPERS_UTILS_INCLUDE_UTILS_GEOMETRY_TRIANGLE_H_ */
