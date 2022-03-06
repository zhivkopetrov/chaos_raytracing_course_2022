#ifndef CRT_CRTWORKDISPATCHER_H_
#define CRT_CRTWORKDISPATCHER_H_

// System headers
#include <vector>

// Other libraries headers
#include "utils/rendering/color/Color24.h"

// Own components headers
#include "crt/config/CrtConfig.h"

// Forward declarations

class CrtWorkDispatcher {
public:
  CrtWorkDispatcher() = delete;

  //return value optimization should kick in
  static std::vector<Color24> generatePixelRegions(const CrtConfig& cfg);
};

#endif /* CRT_CRTWORKDISPATCHER_H_ */
