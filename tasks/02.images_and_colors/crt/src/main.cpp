// System headers
#include <cstdint>
#include <cstdlib>

// Other libraries headers
#include "utils/log/Log.h"

// Own components headers
#include "crt/config/CrtConfigLoader.h"
#include "crt/CrtApplication.h"

int32_t main([[maybe_unused]]int32_t argc, [[maybe_unused]]char *args[]) {
  CrtConfig cfg;
  auto err = CrtConfigLoader::loadConfig(cfg);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("CrtConfigLoader::loadConfig() failed");
    return EXIT_FAILURE;
  }

  CrtApplication app;
  err = app.run(cfg);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("CrtConfig::run() failed");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

