#ifndef CRT_CRTCONFIGLOADER_H_
#define CRT_CRTCONFIGLOADER_H_

// System headers
#include <cstdint>

// Other libraries headers

// Own components headers
#include "crt/config/CrtConfig.h"

// Forward declarations

class CrtConfigLoader {
public:
  CrtConfigLoader() = delete;

  static CrtConfig loadConfig();
};

#endif /* CRT_CRTCONFIGLOADER_H_ */
