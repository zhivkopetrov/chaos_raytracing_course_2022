#ifndef SHAPE_SHAPECONFIGLOADER_H_
#define SHAPE_SHAPECONFIGLOADER_H_

// System headers
#include <cstdint>

// Other libraries headers
#include "utils/ErrorCode.h"

// Own components headers
#include "shape/config/ShapeConfig.h"

// Forward declarations

class ShapeConfigLoader {
public:
  ShapeConfigLoader() = delete;

  static ErrorCode loadConfig(ShapeConfig& outCfg);
};

#endif /* SHAPE_SHAPECONFIGLOADER_H_ */
