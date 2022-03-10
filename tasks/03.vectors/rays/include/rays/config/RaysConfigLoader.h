#ifndef RAYS_RAYSCONFIGLOADER_H_
#define RAYS_RAYSCONFIGLOADER_H_

// System headers
#include <cstdint>

// Other libraries headers
#include "utils/ErrorCode.h"

// Own components headers
#include "rays/config/RaysConfig.h"

// Forward declarations

class RaysConfigLoader {
public:
  RaysConfigLoader() = delete;

  static ErrorCode loadConfig(RaysConfig& outCfg);
};

#endif /* RAYS_RAYSCONFIGLOADER_H_ */
