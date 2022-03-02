// System headers
#include <cstdint>
#include <cstdlib>
#include <iostream>

// Other libraries headers
#include "utils/file/PpmFileWritter.h"

// Own components headers
#include "shape/geometry/BatmanGeometry.h"

int32_t main([[maybe_unused]]int32_t argc, [[maybe_unused]]char *args[]) {

  PpmFileWritter writter;
  const PpmHeader header = { .version = PpmVersion::P3, .imageWidth = 1920,
      .imageHeight = 1080, .maxColorComponent = 255 };
  std::vector<Color24> pixels(header.imageWidth * header.imageHeight,
      Colors24::YELLOW);

  const double xRadius = header.imageWidth / 2;
  const double yRadius = xRadius / 2;

  const auto origin = Point2f(header.imageWidth / 2, header.imageHeight / 2);
  const auto scale = 120.0f;
  const auto ovalRadius = Point2f(xRadius, yRadius);

  Point2f target;
  int32_t pixelId = 0;
  for (int32_t row = 0; row < header.imageHeight; ++row) {
    target.y = row;
    for (int32_t col = 0; col < header.imageWidth; ++col) {
      target.x = col;
      if (!BatmanGeometry::inOval(target, origin, ovalRadius)) {
        ++pixelId;
        continue;
      }

      if (BatmanGeometry::inBatman(target, origin, scale)) {
        pixels[pixelId] = Colors24::BLACK;
      }

      ++pixelId;
    }
  }

  const auto err = writter.writeFile("batman.ppm", header, pixels);
  if (ErrorCode::SUCCESS != err) {
    std::cerr << "writter.writeFile() failed" << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

