// Corresponding header
#include "utils/geometry/Triangle.h"

// System headers
#include <cmath>

// Other libraries headers
#include "utils/data_type/FloatingPoint.h"

// Own components headers

Triangle::Triangle(const Vec3f &v0, const Vec3f &v1, const Vec3f &v2)
    : _verts { v0, v1, v2 } {

}

bool Triangle::intersects(const Ray &ray,
                          float &outRayToIntersectDistance) const {
  // no need to normalize
  const Vec3f normal = getNormal();
  const Vec3f rayDir = ray.direction();
  const Vec3f rayOrigin = ray.origin();

  const float normalDotRayDir = dot(normal, rayDir);

  // they are parallel so they don't intersect !
  if (isParallel(normalDotRayDir)) {
    return false;
  }

  // compute d parameter using equation 2
  const float d = dot(-normal, _verts[0]);

  // compute t (equation 3)
  outRayToIntersectDistance =
      - ( (dot(normal, rayOrigin) + d) / normalDotRayDir);

  if (outRayToIntersectDistance < 0.0f) {
    return false; // the triangle is behind the ray
  }

  // compute the intersection point
  const Point3f intersectionPoint =
      rayOrigin + (outRayToIntersectDistance * rayDir);

  // Step 2: inside-outside test
  Vec3f c; // vector perpendicular to triangle's plane

  // edge 0
  const Vec3f edge01 = _verts[1] - _verts[0];
  const Vec3f vp0 = intersectionPoint - _verts[0];
  c = cross(edge01, vp0);
  if (dot(normal, c) < 0.0f) {
    return false; // intersection is on the right side
  }


  // edge 1
  const Vec3f edge12 = _verts[2] - _verts[1];
  const Vec3f vp1 = intersectionPoint - _verts[1];
  c = cross(edge12, vp1);
  if (dot(normal, c) < 0.0f)
    return false; // intersection is on the right side

  // edge 2
  const Vec3f edge20 = _verts[0] - _verts[2];
  const Vec3f vp2 = intersectionPoint - _verts[2];
  c = cross(edge20, vp2);
  if (dot(normal, c) < 0.0f) {
    return false; // intersection is on the right side;
  }

  return true; // this ray hits the triangle
}

Vec3f Triangle::getNormal() const {
  const auto edge01 = _verts[1] - _verts[0];
  const auto edge02 = _verts[2] - _verts[0];
  return cross(edge01, edge02);
}

bool Triangle::isParallel(float normalDotRayDir) const {
  const FloatingPoint<float> lhs(normalDotRayDir);
  const FloatingPoint<float> rhs(0.0f);
  return lhs.AlmostEquals(rhs) ? true : false;
}

