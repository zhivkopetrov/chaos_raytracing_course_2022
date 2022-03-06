#ifndef SHAPE_BATMANWORKDISPATCHER_H_
#define SHAPE_BATMANWORKDISPATCHER_H_

// System headers
#include <vector>

// Other libraries headers
#include "utils/geometry/Point2f.h"
#include "utils/rendering/color/Color24.h"

// Own components headers
#include "shape/geometry/config/BatmanShapeConfig.h"

// Forward declarations

class BatmanWorkDispatcher {
public:
  BatmanWorkDispatcher() = delete;

  //return value optimization should kick in
  static std::vector<Color24> calculateGeometry(const BatmanShapeConfig &cfg,
                                                int32_t imageWidth,
                                                int32_t imageHeight);
};

#endif /* SHAPE_BATMANWORKDISPATCHER_H_ */