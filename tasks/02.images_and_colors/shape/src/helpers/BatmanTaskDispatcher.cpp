// Corresponding header
#include "shape/helpers/BatmanTaskDispatcher.h"

// System headers
#include <thread>

// Other libraries headers

// Own components headers
#include "shape/geometry/BatmanGeometry.h"

namespace {
int32_t getMaxSupportedThreadsCount() {
  const auto maxThreads = std::thread::hardware_concurrency();
  if (0 == maxThreads) {
    return 1; //hint failed
  }
  return static_cast<int32_t>(maxThreads);
}

//Embracingly parallel task - no locks needed
void calculateGeometryChunk(const BatmanShapeConfig &cfg,
                            int32_t rowsToCalculate, int32_t startRowIdx,
                            int32_t rowWidth, Color24 *outPixels) {
  Point2f target;
  int32_t relativePixelId = 0;
  for (int32_t row = 0; row < rowsToCalculate; ++row) {
    target.y = static_cast<float>(row + startRowIdx);
    for (int32_t col = 0; col < rowWidth; ++col) {
      target.x = static_cast<float>(col);
      if (!BatmanGeometry::inOval(target, cfg.origin, cfg.ovalRadius)) {
        ++relativePixelId;
        continue;
      }

      if (BatmanGeometry::inBatman(target, cfg.origin, cfg.scale)) {
        outPixels[relativePixelId] = Colors24::BLACK;
      }

      ++relativePixelId;
    }
  }
}
}

std::vector<Color24> BatmanTaskDispatcher::calculateGeometry(
    const BatmanShapeConfig &cfg, int32_t imageWidth, int32_t imageHeight) {
  std::vector<Color24> pixels(imageWidth * imageHeight, Colors24::YELLOW);
  const auto maxThreads = getMaxSupportedThreadsCount();
  const auto additionalThreads = maxThreads - 1; //leave work for main thread
  const auto pixelRowsPerThread = imageHeight / maxThreads;

  std::vector<std::thread> threadPool;
  threadPool.reserve(additionalThreads);
  auto offset = 0;
  auto startRowIdx = 0;
  for (auto threadId = 0; threadId < additionalThreads; ++threadId) {

    threadPool.emplace_back(calculateGeometryChunk, std::ref(cfg),
        pixelRowsPerThread, startRowIdx, imageWidth, &pixels[offset]);

    startRowIdx += pixelRowsPerThread;
    offset += (pixelRowsPerThread * imageWidth);
  }

  //utilize main thread
  calculateGeometryChunk(cfg, pixelRowsPerThread, startRowIdx, imageWidth,
      &pixels[offset]);

  for (auto &thread : threadPool) {
    thread.join();
  }

  return pixels;
}
