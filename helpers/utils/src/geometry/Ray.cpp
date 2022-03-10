// Corresponding header
#include "utils/geometry/Ray.h"

// System headers

// Other libraries headers

// Own components headers

Ray::Ray(const Point3f &origin, const Vec3f &direction)
    : _orig(origin), _dir(direction) {
}

Point3f Ray::origin() const {
  return _orig;
}

Vec3f Ray::direction() const {
  return _dir;
}

Color24 Ray::color24() const {
  const auto unitDir = unitVector(_dir);
  constexpr auto maxColorComponent = 255.999f;
  const auto r = ((1.0f + unitDir.x()) / 2.0f) * maxColorComponent;
  const auto g = ((1.0f + unitDir.y()) / 2.0f) * maxColorComponent;
  const auto b = ((1.0f + unitDir.z()) / 2.0f) * maxColorComponent;

  return Color24(r, g, b);
}
