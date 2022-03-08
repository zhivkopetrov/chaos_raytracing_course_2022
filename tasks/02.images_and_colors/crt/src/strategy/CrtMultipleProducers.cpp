// Corresponding header
#include "crt/strategy/CrtMultipleProducers.h"

// System headers
#include <random>
#include <array>
#include <thread>

// Other libraries headers
#include "utils/log/Log.h"

// Own components headers
#include "crt/geometry/PixelRegion.h"

CrtMultipleProducers::CrtMultipleProducers(int32_t workerThreadsHint)
    : _workerThreadsHint(workerThreadsHint) {

}

std::vector<Color24> CrtMultipleProducers::generatePixelRegions(
    const ImageConfig &imageCfg, const PixelRegionConfig &pixelRegionCfg) {
  std::vector<Color24> imagePixels(imageCfg.width * imageCfg.height,
      Colors24::BLACK);

  const auto [additionalThreads, regionsPerThread] = computeWorkloadConfig(
      pixelRegionCfg);
  std::vector<std::thread> threadPool;
  threadPool.reserve(additionalThreads);

  auto startRegionIdx = 0;
  for (auto threadId = 0; threadId < additionalThreads; ++threadId) {

    threadPool.emplace_back(&CrtMultipleProducers::calculatePixelRegionChunk,
        this, std::ref(imageCfg), std::ref(pixelRegionCfg), regionsPerThread,
        startRegionIdx, std::ref(imagePixels));

    startRegionIdx += regionsPerThread;
  }

  //utilize main thread
  calculatePixelRegionChunk(imageCfg, pixelRegionCfg, regionsPerThread,
      startRegionIdx, imagePixels);

  for (auto &thread : threadPool) {
    thread.join();
  }

  return imagePixels;
}

void CrtMultipleProducers::calculatePixelRegionChunk(
    const ImageConfig &imageCfg, const PixelRegionConfig &pixelRegionCfg,
    int32_t regionsToCalculate, int32_t startRegionId,
    std::vector<Color24> &outPixels) {
  std::mt19937 mt(std::random_device { }());

  const auto regionRows = pixelRegionCfg.pixelRegionsRows;
  const auto regionCols = pixelRegionCfg.pixelRegionsPerRow;
  const auto regionWidth = imageCfg.width / regionCols;
  const auto regionHeight = imageCfg.height / regionRows;

  for (int32_t i = 0; i < regionsToCalculate; ++i) {
    const auto regionId = i + startRegionId;
    const auto regionColor = _colorPattern[regionId % COLOR_PATTERN_SIZE];

    const auto regionPixels = PixelRegion::produceRandomized(regionWidth,
        regionHeight, regionColor, mt);

    const auto regionRow = regionId / regionCols;
    const auto regionCol = regionId % regionCols;
    const auto absImagePixelOffset = (regionRow * regionHeight * imageCfg.width)
        + (regionCol * regionWidth);

    PixelRegion::copy(regionWidth, regionHeight, imageCfg.width, regionPixels,
        &outPixels[absImagePixelOffset]);
  }
}

CrtMultipleProducers::WorkloadConfig CrtMultipleProducers::computeWorkloadConfig(
    const PixelRegionConfig &cfg) const {
  WorkloadConfig workloadCfg;

  const auto hardwareThreads =
      static_cast<int32_t>(std::thread::hardware_concurrency());
  if (0 == hardwareThreads) { //hint failed
    LOGR("CrtMultipleProducers::getAdditionalThreadCount: unable to "
         "detect hardware threads. Falling back to single-threaded solution");
    workloadCfg.additionalThreads = 0;
    workloadCfg.regionsPerThread = 0;
    return workloadCfg;
  }

  const auto maxAdditionalThreads =
      (0 == _workerThreadsHint) ?
          hardwareThreads : std::min(_workerThreadsHint, hardwareThreads);

  const auto totalRegions = cfg.pixelRegionsPerRow * cfg.pixelRegionsRows;
  if (totalRegions <= maxAdditionalThreads) {
    //leave work for main thread
    workloadCfg.additionalThreads = totalRegions - 1;
    workloadCfg.regionsPerThread = 1;
    LOGR("Truncating worker threads down to: %d to achieve best performance",
         maxAdditionalThreads);
  } else {
    //leave work for main thread
    workloadCfg.additionalThreads = maxAdditionalThreads - 1;
    workloadCfg.regionsPerThread = totalRegions / maxAdditionalThreads;
  }

  return workloadCfg;
}

