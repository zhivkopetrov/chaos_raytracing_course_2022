// System headers
#include <cstdint>
#include <cstdlib>

// Other libraries headers
#include "utils/log/Log.h"

// Own components headers
#include "single_triangle/config/SingleTriangleConfigLoader.h"
#include "single_triangle/SingleTriangleApplication.h"

int32_t main([[maybe_unused]]int32_t argc, [[maybe_unused]]char *args[]) {
  SingleTriangleConfig cfg;
  auto err = SingleTriangleConfigLoader::loadConfig(cfg);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("SingleTriangleConfigLoader::loadConfig() failed");
    return EXIT_FAILURE;
  }

  SingleTriangleApplication app;
  err = app.run(cfg);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("SingleTriangleApplication::run() failed");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

