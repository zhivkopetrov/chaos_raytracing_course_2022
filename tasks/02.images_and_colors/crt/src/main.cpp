// System headers
#include <cstdint>
#include <cstdlib>
#include <iostream>

// Other libraries headers

// Own components headers
#include "crt/config/CrtConfigLoader.h"
#include "crt/CrtApplication.h"


int32_t main([[maybe_unused]]int32_t argc, [[maybe_unused]]char *args[]) {
  CrtApplication app;
  const auto cfg = CrtConfigLoader::loadConfig();
  const auto err = app.run(cfg);
  if (ErrorCode::SUCCESS != err) {
    std::cerr << "CrtConfig::run() failed" << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

