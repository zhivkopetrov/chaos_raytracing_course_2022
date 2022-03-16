#ifndef UTILS_VEC3F_H_
#define UTILS_VEC3F_H_

// System headers
#include <cstddef>
#include <iosfwd>

// Other libraries headers

// Own components headers

// Forward declarations

class Vec3f {
public:
  Vec3f() = default;
  Vec3f(float x, float y, float z);

  void setX(float x);
  void setY(float y);
  void setZ(float z);

  float x() const;
  float y() const;
  float z() const;

  Vec3f operator-() const;
  Vec3f& operator+=(const Vec3f &other);
  Vec3f& operator*=(float scalar);
  Vec3f& operator/=(float scalar);

  float length() const;
  float lengthSquared() const;

  void normalize();

  void writeInt32SpacedData(std::ostream &out) const;
  void writeCharData(std::ostream &out) const;

  //helper methods
  friend Vec3f operator+(const Vec3f &left, const Vec3f &right);
  friend Vec3f operator-(const Vec3f &left, const Vec3f &right);
  friend Vec3f operator*(const Vec3f &left, const Vec3f &right);
  friend Vec3f operator*(float scalar, const Vec3f &right);
  friend Vec3f operator*(const Vec3f &vec, float scalar);
  friend Vec3f operator/(const Vec3f& v, float scalar);
  friend float dot(const Vec3f &left, const Vec3f &right);
  friend Vec3f cross(const Vec3f &left, const Vec3f &right);
  friend Vec3f unitVector(const Vec3f &vec);

  // warning: quite slow, consider using Vec3f::writeInt32DataToStream
  friend std::ostream& operator<<(std::ostream &out, const Vec3f &right);

private:
  float _x { };
  float _y { };
  float _z { };

  mutable float _lengthCache{};
  mutable bool _dirty = true;
};

using Point3f = Vec3f;
using Color24 = Vec3f;

namespace Colors24 {
inline const Color24 RED(255, 0, 0);
inline const Color24 GREEN(0, 255, 0);
inline const Color24 BLUE(0, 0, 255);
inline const Color24 BLACK(0, 0, 0);
inline const Color24 WHITE(255, 255, 255);
inline const Color24 CYAN(0, 255, 255);
inline const Color24 MAGENTA(255, 0, 255);
inline const Color24 YELLOW(255, 255, 0);
inline const Color24 ORANGE(255, 128, 0);
inline const Color24 GRAY(192, 192, 0);
} //namespace Colors24

#endif /* UTILS_VEC3F_H_ */
