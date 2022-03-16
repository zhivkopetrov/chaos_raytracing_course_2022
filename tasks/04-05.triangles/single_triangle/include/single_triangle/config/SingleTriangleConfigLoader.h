#ifndef SINGLE_TRIANGLE_SINGLETRIANGLECONFIGLOADER_H_
#define SINGLE_TRIANGLE_SINGLETRIANGLECONFIGLOADER_H_

// System headers
#include <cstdint>

// Other libraries headers
#include "utils/ErrorCode.h"

// Own components headers
#include "single_triangle/config/SingleTriangleConfig.h"

// Forward declarations

class SingleTriangleConfigLoader {
public:
  SingleTriangleConfigLoader() = delete;

  static ErrorCode loadConfig(SingleTriangleConfig& outCfg);
};

#endif /* SINGLE_TRIANGLE_SINGLETRIANGLECONFIGLOADER_H_ */
