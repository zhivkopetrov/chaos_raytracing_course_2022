#ifndef CRT_CRTSTRATEGYBASE_H_
#define CRT_CRTSTRATEGYBASE_H_

// System headers
#include <vector>
#include <array>

// Other libraries headers
#include "utils/geometry/Vec3f.h"

// Own components headers
#include "crt/defines/CrtDefines.h"
#include "crt/config/CrtConfig.h"

// Forward declarations

inline constexpr auto COLOR_PATTERN_SIZE = 6;
using ColorPattern = std::array<PixelRegionType, COLOR_PATTERN_SIZE>;

class CrtStrategyBase {
public:
  virtual ~CrtStrategyBase() noexcept = default;

  //return value optimization should kick in
  virtual std::vector<Color24> generatePixelRegions(
      const ImageConfig &imageCfg, const PixelRegionConfig &pixelRegionCfg) = 0;

protected:
  const ColorPattern _colorPattern { PixelRegionType::RED,
      PixelRegionType::GREEN, PixelRegionType::BLUE, PixelRegionType::YELLOW,
      PixelRegionType::MAGENTA, PixelRegionType::CYAN };
};

#endif /* CRT_CRTSTRATEGYBASE_H_ */
