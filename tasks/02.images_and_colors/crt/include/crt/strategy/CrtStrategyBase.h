#ifndef CRT_CRTSTRATEGYBASE_H_
#define CRT_CRTSTRATEGYBASE_H_

// System headers
#include <vector>

// Other libraries headers
#include "utils/rendering/color/Color24.h"

// Own components headers
#include "crt/config/CrtConfig.h"

// Forward declarations

class CrtStrategyBase {
public:
  virtual ~CrtStrategyBase() noexcept = default;

  //return value optimization should kick in
  virtual std::vector<Color24> generatePixelRegions(
      const ImageConfig &imageCfg, const PixelRegionConfig &pixelRegionCfg) = 0;
};

#endif /* CRT_CRTSTRATEGYBASE_H_ */
