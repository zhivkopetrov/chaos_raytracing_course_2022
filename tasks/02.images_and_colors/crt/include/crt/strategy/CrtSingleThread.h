#ifndef CRT_CRTSINGLETHREAD_H_
#define CRT_CRTSINGLETHREAD_H_

// System headers

// Other libraries headers

// Own components headers
#include "crt/strategy/CrtStrategyBase.h"

// Forward declarations

class CrtSingleThread final : public CrtStrategyBase {
public:

private:
  std::vector<Color24> generatePixelRegions(
      const ImageConfig &imageCfg, const PixelRegionConfig &pixelRegionCfg)
          override;
};

#endif /* CRT_CRTSINGLETHREAD_H_ */
