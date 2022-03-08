// System headers
#include <cstdint>
#include <cstdlib>

// Other libraries headers
#include "utils/log/Log.h"

// Own components headers
#include "shape/config/ShapeConfigLoader.h"
#include "shape/ShapeApplication.h"


int32_t main([[maybe_unused]]int32_t argc, [[maybe_unused]]char *args[]) {
  ShapeApplication app;
  const auto cfg = ShapeConfigLoader::loadConfig();
  const auto err = app.run(cfg);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("ShapeApplication::run() failed");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

