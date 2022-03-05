#ifndef SHAPE_SHAPECONFIG_H_
#define SHAPE_SHAPECONFIG_H_

// System headers
#include <cstdint>
#include <string>

// Other libraries headers
#include "utils/geometry/Point2f.h"

// Own components headers
#include "shape/geometry/config/BatmanShapeConfig.h"

// Forward declarations

struct ImageConfig {
  std::string name;
  int32_t width{};
  int32_t height{};
};

struct ShapeConfig {
  BatmanShapeConfig batmanShapeCfg;
  ImageConfig imageCfg;
};

#endif /* SHAPE_SHAPECONFIG_H_ */
