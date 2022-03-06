#ifndef CRT_CRTDEFINES_H_
#define CRT_CRTDEFINES_H_

// System headers

// Other libraries headers
#include <string>

// Own components headers

// Forward declarations

enum class PixelRegionType {
  RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN
};

enum class CrtStrategy {
  SINGLE_THREAD,
  MULTIPLE_PRODUCERS,
  MULTIPLE_PRODUCERS_SINGLE_ASYNC_CONSUMER,
};

CrtStrategy parseStrategy(const std::string& identifier);

#endif /* CRT_CRTDEFINES_H_ */
