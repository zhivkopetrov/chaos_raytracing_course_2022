// Corresponding header
#include "crt/defines/CrtDefines.h"

// System headers

// Other libraries headers
#include "utils/log/Log.h"

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

  LOGERR("Error, received unsupported CrtStrategy identifier: %s. "
         "Falling back to CrtStrategy::SINGLE_THREAD", identifier.c_str());
  return CrtStrategy::SINGLE_THREAD;
}
