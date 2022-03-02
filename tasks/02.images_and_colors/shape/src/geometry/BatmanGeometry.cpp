// Corresponding header
#include "shape/geometry/BatmanGeometry.h"

// System headers
#include <cmath>

// Other libraries headers

// Own components headers

// Forward declarations

namespace {
constexpr double HASH_1 = (6 * sqrt(10)) / 7;
constexpr double HASH_2 = HASH_1 / 2;
constexpr double HASH_3 = ( (3 * sqrt(33)) - 7) / 112;
}

bool BatmanGeometry::inOval(const Point2f &target, const Point2f &origin,
                            const Point2f &ovalRadius) {
  const auto posX = target.x - origin.x;
  const auto posY = target.y - origin.y;
  const auto deltaX = posX / ovalRadius.x;
  const auto deltaY = posY / ovalRadius.y;

  return ( (deltaX * deltaX) + (deltaY * deltaY) <= 1.0f) ? true : false;
}

// values taken from
// https://www.wolframalpha.com/input/?i=batman+equation
bool BatmanGeometry::inBatman(const Point2f &target, const Point2f &origin,
                              double scale) {
  const double posX = static_cast<double>(target.x - origin.x) / scale;
  const double posY = static_cast<double>(target.y - origin.y) / scale;
  double tempX = 0.0;
  double tempY = 0.0;

  if (posY < 0.0) {
    /* left upper wing */
    if (posX <= -3) {
      tempX = (-7 * sqrt(1 - ( (posY * posY) / 9.0)));
      return posX >= tempX ? true : false;
    }

    /* left shoulder */
    if (posX > -3.0 && posX <= -1.0) {
      tempX = -posX;
      const double localHash = fabs(tempX) - 1;
      tempY = - (HASH_1 + (1.5 - 0.5 * tempX))
          + HASH_2 * sqrt(4.0 - (localHash * localHash));
      return posY > tempY ? true : false;
    }

    /* exterior left ear */
    if (posX > -1.0 && posX <= -0.75) {
      tempY = 9.0 + 8.0 * posX;
      return posY > -tempY ? true : false;
    }

    /* interior left ear */
    if (posX > -0.75 && posX <= -0.5) {
      tempY = -3 * posX + 0.75;
      return posY > -tempY ? true : false;
    }

    /* top of head */
    if (posX > -0.5 && posX <= 0.5) {
      tempY = 2.25;
      return posY > -tempY ? true : false;
    }

    /* interior right ear */
    if (posX > 0.5 && posX <= 0.75) {
      tempY = 3 * posX + 0.75;
      return posY > -tempY ? true : false;
    }

    /* exterior right ear */
    if (posX > 0.75 && posX <= 1.0) {
      tempY = 9.0 - 8 * posX;
      return posY > -tempY ? true : false;
    }

    /* right shoulder */
    if (posX <= 3.0 && posX > 1.0) {
      const double localHash = fabs(posX) - 1.0;
      tempY = - (HASH_1 + (1.5 - 0.5 * posX))
          + HASH_2 * sqrt(4.0 - (localHash * localHash));
      return posY > tempY ? true : false;
    }

    /* right upper wing */
    if (posX > 3.0) {
      tempX = (7.0 * sqrt(1 - ( (posY * posY) / 9.0)));
      return posX <= tempX ? true : false;
    }
  }
  if (posY >= 0) {
    /* bottom left wing */
    if (posX <= -4.0) {
      tempX = (-7 * sqrt(1 - ( (posY * posY) / 9.0)));
      return posX >= tempX ? true : false;
    }

    /* bottom wing */
    if (posX > -4.0 && posX <= 4.0) {
      const double localHash = fabs(fabs(posX) - 2.0) - 1.0;
      tempY = (fabs(posX / 2) - (HASH_3 * posX * posX) - 3.0)
          + sqrt(1 - (localHash * localHash));
      tempY *= -1.0;
      return posY < tempY ? true : false;
    }

    /* bottom right wing */
    if (posX >= 4.0) {
      tempX = (7.0 * sqrt(1 - ( (posY * posY) / 9.0)));
      return posX <= tempX ? true : false;
    }
  }

  return false;
}
