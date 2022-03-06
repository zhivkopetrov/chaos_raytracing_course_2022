// Corresponding header
#include "crt/strategy/CrtStrategyFactory.h"

// System headers
#include <iostream>

// Other libraries headers
#include "utils/data_type/EnumClassUtils.h"

// Own components headers
#include "crt/strategy/CrtSingleThread.h"

std::unique_ptr<CrtStrategyBase> CrtStrategyFactory::createStrategy(
    const StrategyConfig &cfg) {
  switch (cfg.strategy) {
  case CrtStrategy::SINGLE_THREAD:
    return std::make_unique<CrtSingleThread>();
  case CrtStrategy::MULTIPLE_PRODUCERS:
    return std::make_unique<CrtSingleThread>();
  case CrtStrategy::MULTIPLE_PRODUCERS_SINGLE_ASYNC_CONSUMER:
    return std::make_unique<CrtSingleThread>();
  default:
    std::cerr << "Error, received unsupported CrtStrategy: "
              << getEnumValue(cfg.strategy) << std::endl;
    return nullptr;
  }
}
