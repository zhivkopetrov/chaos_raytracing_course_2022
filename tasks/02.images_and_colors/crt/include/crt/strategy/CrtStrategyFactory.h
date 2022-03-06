#ifndef CRT_CRTSTRATEGYFACTORY_H_
#define CRT_CRTSTRATEGYFACTORY_H_

// System headers
#include <memory>

// Other libraries headers

// Own components headers
#include "crt/strategy/CrtStrategyBase.h"

// Forward declarations

class CrtStrategyFactory {
public:
  CrtStrategyFactory() = delete;

  static std::unique_ptr<CrtStrategyBase> createStrategy(
      const StrategyConfig &cfg);
};

#endif /* CRT_CRTSTRATEGYFACTORY_H_ */
