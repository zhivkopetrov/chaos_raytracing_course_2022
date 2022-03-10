// Corresponding header
#include "utils/geometry/CoordinateTransform.h"

// System headers
#include <cassert>

// Other libraries headers

// Own components headers

std::vector<Point2f> CoordinateTransform::getMidPixelRaster(
    int32_t imageWidth, int32_t imageHeight) {
  std::vector<Point2f> coords(imageWidth * imageHeight);

  constexpr auto offset = 0.5f;
  int32_t idx = 0;
  for (int32_t row = 0; row < imageHeight; ++row) {
    const auto xValue = static_cast<float>(row) + offset;
    for (int32_t col = 0; col < imageWidth; ++col) {
      coords[idx].x = xValue;
      coords[idx].y = static_cast<float>(col) + offset;
      ++idx;
    }
  }

  return coords;
}

std::vector<Point2f> CoordinateTransform::rasterToNdc(
    const std::vector<Point2f> &raster, int32_t imageWidth,
    int32_t imageHeight) {
  const auto size = raster.size();
  std::vector<Point2f> ndc(size);

  const auto width = static_cast<float>(imageWidth);
  const auto height = static_cast<float>(imageHeight);

  for (size_t i = 0; i < size; ++i) {
    ndc[i].x = width * raster[i].x;
    ndc[i].y = height * raster[i].y;
  }

  return ndc;
}

std::vector<Point2f> CoordinateTransform::ndcToScreen(
    const std::vector<Point2f> &ndc, float aspectRatio) {
  const auto size = ndc.size();
  std::vector<Point2f> screen(size);

  for (size_t i = 0; i < size; ++i) {
    screen[i].x = ( (2.0f * ndc[i].x) - 1.0f) * aspectRatio;
    screen[i].y = 1.0f - (2.0f * ndc[i].y);
  }

  return screen;
}

std::vector<Vec3f> CoordinateTransform::getWorldDirVectors(
    const std::vector<Point2f> &raster, float zDistance, int32_t imageWidth,
    int32_t imageHeight, bool normalize) {
  const auto size = raster.size();
  std::vector<Vec3f> dirs;
  dirs.reserve(size);

  const auto aspectRatio = static_cast<float>(imageWidth)
      / static_cast<float>(imageHeight);
  const auto ndc = rasterToNdc(raster, imageWidth, imageHeight);
  const auto screen = ndcToScreen(ndc, aspectRatio);

  assert(size == screen.size());
  for (size_t i = 0; i < size; ++i) {
    dirs.emplace_back(screen[i].x, screen[i].y, zDistance);
  }

  if (normalize) {
    for (auto& dir : dirs) {
      dir.normalize();
    }
  }

  return dirs;
}

