#ifndef SHAPE_BATMANTASKDISPATCHER_H_
#define SHAPE_BATMANTASKDISPATCHER_H_

// System headers
#include <vector>

// Other libraries headers
#include "utils/geometry/Point2f.h"
#include "utils/geometry/Vec3f.h"

// Own components headers
#include "shape/geometry/config/BatmanShapeConfig.h"

// Forward declarations

class BatmanTaskDispatcher {
public:
  BatmanTaskDispatcher() = delete;

  //return value optimization should kick in
  static std::vector<Color24> calculateGeometry(const BatmanShapeConfig &cfg,
                                                int32_t imageWidth,
                                                int32_t imageHeight);
};

#endif /* SHAPE_BATMANTASKDISPATCHER_H_ */
