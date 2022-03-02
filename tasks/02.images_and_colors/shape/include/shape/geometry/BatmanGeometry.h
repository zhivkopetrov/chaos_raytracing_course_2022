#ifndef SHAPE_BATMANGEOMETRY_H_
#define SHAPE_BATMANGEOMETRY_H_

// System headers

// Other libraries headers
#include "utils/geometry/Point2f.h"

// Own components headers

// Forward declarations

class BatmanGeometry {
public:
  BatmanGeometry() = delete;

  static bool inOval(const Point2f &target, const Point2f &origin,
                     const Point2f &ovalRadius);

  static bool inBatman(const Point2f &target, const Point2f &origin,
                       double scale);
};

#endif /* SHAPE_BATMANGEOMETRY_H_ */
