#ifndef CRT_CRTCONFIGLOADER_H_
#define CRT_CRTCONFIGLOADER_H_

// System headers
#include <cstdint>

// Other libraries headers
#include "utils/ErrorCode.h"

// Own components headers
#include "crt/config/CrtConfig.h"

// Forward declarations

class CrtConfigLoader {
public:
  CrtConfigLoader() = delete;

  static ErrorCode loadConfig(CrtConfig& outCfg);
};

#endif /* CRT_CRTCONFIGLOADER_H_ */
