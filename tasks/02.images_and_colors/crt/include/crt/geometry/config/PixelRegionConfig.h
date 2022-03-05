#ifndef CRT_PIXELREGIONCONFIG_H_
#define CRT_PIXELREGIONCONFIG_H_

// System headers
#include <cstdint>

// Other libraries headers

// Own components headers

// Forward declarations

struct PixelRegionConfig {
  int32_t pixelRegionsPerRow{};
  int32_t pixelRegionsRows{};
};

struct StrategyConfig {
  CrtStrategy strategy;
  int32_t workerThreadsHint{}; //0 means - use all hardware threads
};

#endif /* CRT_PIXELREGIONCONFIG_H_ */
