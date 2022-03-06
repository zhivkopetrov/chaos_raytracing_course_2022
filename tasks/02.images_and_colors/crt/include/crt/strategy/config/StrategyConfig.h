#ifndef CRT_STRATEGYCONFIG_H_
#define CRT_STRATEGYCONFIG_H_

// System headers

// Other libraries headers

// Own components headers
#include "crt/defines/CrtDefines.h"

// Forward declarations

struct StrategyConfig {
  CrtStrategy strategy;
  int32_t workerThreadsHint{}; //0 means - use all hardware threads
};

#endif /* CRT_STRATEGYCONFIG_H_ */
