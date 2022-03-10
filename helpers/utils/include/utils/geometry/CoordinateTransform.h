#ifndef UTILS_COORDINATETRANSFORM_H_
#define UTILS_COORDINATETRANSFORM_H_

// System headers
#include <vector>

// Other libraries headers

// Own components headers
#include "utils/geometry/Point2f.h"
#include "utils/geometry/Vec3f.h"

// Forward declarations

class CoordinateTransform {
public:
  CoordinateTransform() = delete;

  static std::vector<Point2f> getMidPixelRaster(int32_t imageWidth,
                                                int32_t imageHeight);

  static std::vector<Point2f> rasterToNdc(const std::vector<Point2f> &raster,
                                          int32_t imageWidth,
                                          int32_t imageHeight);

  static std::vector<Point2f> ndcToScreen(const std::vector<Point2f> &ndc);

  static std::vector<Vec3f> getWorldDirVectors(
      const std::vector<Point2f> &raster, float zDistance, int32_t imageWidth,
      int32_t imageHeight, bool normalize);
};

#endif /* UTILS_COORDINATETRANSFORM_H_ */
