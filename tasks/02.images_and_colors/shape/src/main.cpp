// System headers
#include <cstdint>
#include <cstdlib>

// Other libraries headers
#include "utils/log/Log.h"

// Own components headers
#include "shape/config/ShapeConfigLoader.h"
#include "shape/ShapeApplication.h"


int32_t main([[maybe_unused]]int32_t argc, [[maybe_unused]]char *args[]) {
  ShapeConfig cfg;
  auto err = ShapeConfigLoader::loadConfig(cfg);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("ShapeConfigLoader::loadConfig() failed");
    return EXIT_FAILURE;
  }

  ShapeApplication app;
  err = app.run(cfg);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("ShapeApplication::run() failed");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

