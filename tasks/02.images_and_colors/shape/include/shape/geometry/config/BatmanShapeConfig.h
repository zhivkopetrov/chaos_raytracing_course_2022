#ifndef SHAPE_BATMANSHAPECONFIG_H_
#define SHAPE_BATMANSHAPECONFIG_H_

// System headers

// Other libraries headers
#include "utils/geometry/Point2f.h"

// Own components headers

// Forward declarations

struct BatmanShapeConfig {
  Point2f origin;
  Point2f ovalRadius;
  float scale{};
};

#endif /* SHAPE_BATMANSHAPECONFIG_H_ */
