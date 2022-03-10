// Corresponding header
#include "utils/geometry/CoordinateTransform.h"

// System headers

// Other libraries headers

// Own components headers

std::vector<Point2f> CoordinateTransform::getMidPixelRaster(
    int32_t imageWidth, int32_t imageHeight) {
  std::vector<Point2f> coords(imageWidth * imageHeight);

  constexpr auto offset = 0.5f;
  int32_t idx = 0;
  for (int32_t row = 0; row < imageHeight; ++row) {
    const auto yValue = static_cast<float>(row) + offset;
    for (int32_t col = 0; col < imageWidth; ++col) {
      coords[idx].y = yValue;
      coords[idx].x = static_cast<float>(col) + offset;
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
    ndc[i].x = raster[i].x / width;
    ndc[i].y = raster[i].y / height;
  }

  return ndc;
}

std::vector<Point2f> CoordinateTransform::ndcToScreen(
    const std::vector<Point2f> &ndc) {
  const auto size = ndc.size();
  std::vector<Point2f> screen(size);

  for (size_t i = 0; i < size; ++i) {
    screen[i].x = ( (2.0f * ndc[i].x) - 1.0f);
    screen[i].y = 1.0f - (2.0f * ndc[i].y);
  }

  return screen;
}

std::vector<Vec3f> CoordinateTransform::getWorldDirVectors(
    const std::vector<Point2f> &raster, float zDistance, int32_t imageWidth,
    int32_t imageHeight, bool normalize) {
  std::vector<Vec3f> dirs;
  dirs.reserve(raster.size());

  const auto ndc = rasterToNdc(raster, imageWidth, imageHeight);
  const auto screen = ndcToScreen(ndc);
  const auto aspectRatio = static_cast<float>(imageWidth)
      / static_cast<float>(imageHeight);

  for (const auto &screenPixel : screen) {
    dirs.emplace_back(screenPixel.x * aspectRatio, screenPixel.y, zDistance);
  }

  if (normalize) {
    for (auto &dir : dirs) {
      dir.normalize();
    }
  }

  return dirs;
}

