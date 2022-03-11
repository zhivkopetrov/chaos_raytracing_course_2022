// Corresponding header
#include "utils/geometry/Vec3f.h"

// System headers
#include <cmath>
#include <ostream>

// Other libraries headers

// Own components headers

Vec3f::Vec3f(float x, float y, float z)
    : _x(x), _y(y), _z(z) {
}

void Vec3f::setX(float x) {
  _x = x;
  _dirty = true;
}

void Vec3f::setY(float y) {
  _y = y;
  _dirty = true;
}

void Vec3f::setZ(float z) {
  _z = z;
  _dirty = true;
}

float Vec3f::x() const {
  return _x;
}

float Vec3f::y() const {
  return _y;
}

float Vec3f::z() const {
  return _z;
}

Vec3f Vec3f::operator-() const {
  return Vec3f(-_x, -_y, -_z);
}

Vec3f& Vec3f::operator+=(const Vec3f &other) {
  _x += other._x;
  _y += other._y;
  _z += other._z;
  _dirty = true;
  return *this;
}

Vec3f& Vec3f::operator*=(float scalar) {
  _x *= scalar;
  _y *= scalar;
  _z *= scalar;
  _dirty = true;
  return *this;
}

Vec3f& Vec3f::operator/=(float scalar) {
  _dirty = true;
  return *this *= (1.0f / scalar);
}

float Vec3f::length() const {
  if (!_dirty) {
    return _lengthCache;
  }

  _dirty = false;
  _lengthCache = sqrtf(lengthSquared());
  return _lengthCache;
}

float Vec3f::lengthSquared() const {
  return (_x * _x) + (_y * _y) + (_z * _z);
}

void Vec3f::normalize() {
  *this /= length();
}

void Vec3f::writeInt32SpacedData(std::ostream &out) const {
  out << static_cast<int32_t>(_x) << ' ' << static_cast<int32_t>(_y) << ' '
      << static_cast<int32_t>(_z);
}

void Vec3f::writeCharData(std::ostream &out) const {
  const char data[3] {
    static_cast<char>(_x), static_cast<char>(_y), static_cast<char>(_z)
  };

  out << data;
}

Vec3f operator+(const Vec3f &left, const Vec3f &right) {
  return Vec3f(left._x + right._x, left._y + right._y, left._z + right._z);
}

Vec3f operator-(const Vec3f &left, const Vec3f &right) {
  return Vec3f(left._x - right._x, left._y - right._y, left._z - right._z);
}

Vec3f operator*(const Vec3f &left, const Vec3f &right) {
  return Vec3f(left._x * right._x, left._y * right._y, left._z * right._z);
}

Vec3f operator*(float scalar, const Vec3f &right) {
  return Vec3f(scalar * right._x, scalar * right._y, scalar * right._z);
}

Vec3f operator*(const Vec3f &vec, float scalar) {
  return scalar * vec;
}

Vec3f operator/(const Vec3f &v, float scalar) {
  return (1.0f / scalar) * v;
}

float dot(const Vec3f &left, const Vec3f &right) {
  return left._x * right._x + left._y * right._y + left._z * right._z;
}

Vec3f cross(const Vec3f &left, const Vec3f &right) {
  return Vec3f(left._y * right._z - left._z * right._y,
      left._z * right._x - left._x * right._z,
      left._x * right._y - left._y * right._x);
}

Vec3f unitVector(const Vec3f &vec) {
  return vec / vec.length();
}

std::ostream& operator<<(std::ostream &out, const Vec3f &right) {
  return out << right._x << ' ' << right._y << ' ' << right._z;
}

