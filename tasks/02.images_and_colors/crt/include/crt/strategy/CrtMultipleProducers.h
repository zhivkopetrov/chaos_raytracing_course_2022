#ifndef CRT_CRTMULTIPLEPRODUCERS_H_
#define CRT_CRTMULTIPLEPRODUCERS_H_

// System headers

// Other libraries headers

// Own components headers
#include "crt/strategy/CrtStrategyBase.h"

// Forward declarations

class CrtMultipleProducers final : public CrtStrategyBase {
public:
  CrtMultipleProducers(int32_t workerThreadsHint);

private:
  struct WorkloadConfig {
    int32_t additionalThreads { };
    int32_t regionsPerThread { };
  };

  std::vector<Color24> generatePixelRegions(
      const ImageConfig &imageCfg, const PixelRegionConfig &pixelRegionCfg)
          override;

  void calculatePixelRegionChunk(const ImageConfig &imageCfg,
                                 const PixelRegionConfig &pixelRegionCfg,
                                 int32_t regionsToCalculate,
                                 int32_t startRegionId,
                                 std::vector<Color24> &outPixels);

  WorkloadConfig computeWorkloadConfig(const PixelRegionConfig &cfg) const;

  int32_t _workerThreadsHint;
};

#endif /* CRT_CRTMULTIPLEPRODUCERS_H_ */
