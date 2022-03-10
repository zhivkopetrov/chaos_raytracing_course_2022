// System headers
#include <cstdint>
#include <cstdlib>

// Other libraries headers
#include "utils/log/Log.h"

// Own components headers
#include "rays/config/RaysConfigLoader.h"
#include "rays/RaysApplication.h"

int32_t main([[maybe_unused]]int32_t argc, [[maybe_unused]]char *args[]) {
  RaysConfig cfg;
  auto err = RaysConfigLoader::loadConfig(cfg);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("RaysConfigLoader::loadConfig() failed");
    return EXIT_FAILURE;
  }

  RaysApplication app;
  err = app.run(cfg);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("RaysApplication::run() failed");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

