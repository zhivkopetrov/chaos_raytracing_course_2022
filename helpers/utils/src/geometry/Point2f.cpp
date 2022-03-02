// Corresponding header
#include "utils/geometry/Point2f.h"

// System headers

// Other libraries headers
#include "utils/data_type/FloatingPoint.h"

// Own components headers

// Forward declarations

Point2f::Point2f(float inputX, float inputY)
    : x(inputX), y(inputY) {
}

bool Point2f::operator==(const Point2f& other) const {
  const FloatingPoint<float> lhsX(x);
  const FloatingPoint<float> rhsX(other.x);

  const FloatingPoint<float> lhsY(y);
  const FloatingPoint<float> rhsY(other.y);

  return lhsX.AlmostEquals(rhsX) && lhsY.AlmostEquals(rhsY);
}

bool Point2f::operator!=(const Point2f& other) const {
  return !(*this == other);
}
