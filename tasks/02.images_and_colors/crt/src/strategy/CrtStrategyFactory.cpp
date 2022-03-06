// Corresponding header
#include "crt/strategy/CrtStrategyFactory.h"

// System headers
#include <iostream>

// Other libraries headers
#include "utils/data_type/EnumClassUtils.h"

// Own components headers
#include "crt/strategy/CrtSingleThread.h"
#include "crt/strategy/CrtMultipleProducers.h"

std::unique_ptr<CrtStrategyBase> CrtStrategyFactory::createStrategy(
    const StrategyConfig &cfg) {
  switch (cfg.strategy) {
  case CrtStrategy::SINGLE_THREAD:
    return std::make_unique<CrtSingleThread>();

  case CrtStrategy::MULTIPLE_PRODUCERS:
    return std::make_unique<CrtMultipleProducers>(cfg.workerThreadsHint);

  case CrtStrategy::MULTIPLE_PRODUCERS_SINGLE_ASYNC_CONSUMER:
    std::cout << "Strategy is not implemented yet. "
        "Falling back to MULTIPLE_PRODUCERS\n";
    return std::make_unique<CrtMultipleProducers>(cfg.workerThreadsHint);

  default:
    std::cerr << "Error, received unsupported CrtStrategy: "
              << getEnumValue(cfg.strategy) << std::endl;
    return nullptr;
  }
}
