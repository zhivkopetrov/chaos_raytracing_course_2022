// Corresponding header
#include "crt/defines/CrtDefines.h"

// System headers
#include <iostream>

// Other libraries headers

// Own components headers

CrtStrategy parseStrategy(const std::string &identifier) {
  if (identifier == "single_thread") {
    return CrtStrategy::SINGLE_THREAD;
  }
  if (identifier == "multiple_producers") {
    return CrtStrategy::MULTIPLE_PRODUCERS;
  }
  if (identifier == "multiple_producers_single_async_consumer") {
    return CrtStrategy::MULTIPLE_PRODUCERS_SINGLE_ASYNC_CONSUMER;
  }

  std::cerr << "Error, received unsupported CrtStrategy identifier: "
            << identifier << ". Falling back to CrtStrategy::SINGLE_THREAD"
            << std::endl;
  return CrtStrategy::SINGLE_THREAD;
}
