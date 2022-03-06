#ifndef CRT_CRTCONFIG_H_
#define CRT_CRTCONFIG_H_

// System headers
#include <cstdint>
#include <string>

// Other libraries headers

// Own components headers
#include "crt/defines/CrtDefines.h"
#include "crt/geometry/config/PixelRegionConfig.h"
#include "crt/strategy/config/StrategyConfig.h"

// Forward declarations

struct ImageConfig {
  std::string name;
  int32_t width{};
  int32_t height{};
};

struct CrtConfig {
  ImageConfig imageCfg;
  PixelRegionConfig pixelRegionCfg;
  StrategyConfig strategyCfg;
};

#endif /* CRT_CRTCONFIG_H_ */
