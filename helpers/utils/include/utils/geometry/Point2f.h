#ifndef UTILS_POINT2F_H_
#define UTILS_POINT2F_H_

// System headers

// Other libraries headers

// Own components headers

// Forward declarations

struct Point2f {
  Point2f() = default;
  Point2f(float inputX, float inputY);

  bool operator==(const Point2f& other) const;
  bool operator!=(const Point2f& other) const;

  float x{};
  float y{};
};

#endif /* UTILS_POINT2F_H_ */
