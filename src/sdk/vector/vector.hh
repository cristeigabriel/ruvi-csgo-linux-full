//
//  ruvi base
//

#pragma once

// includes
#include <cmath>

// helpers
inline double DEG2RAD(double degrees) {
  return degrees * 4.0 * atan(1.0) / 180.0;
}

template <typename t>
class vector {
public:
  t x, y, z;

  vector() = default;
  vector(t _x, t _y, t _z) : x(_x), y(_y), z(_z) {}
  vector(const vector &v) : x(v.x), y(v.y), z(v.z) {}

  inline t magnitude() { return std::sqrt(x * x + y * y + z * z); }

  inline vector normalize() {
    t r = 1 / magnitude();
    return vector(x * r, y * r, z * r);
  }

  inline t dot_product(const vector &rhs) {
    return (x * rhs.x + y * rhs.y + z * rhs.z);
  }

  // operators
  vector &operator+=(const vector &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  vector &operator-=(const vector &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  vector &operator*=(t rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
  }

  vector &operator/=(t rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
  }

  vector operator+(const vector &rhs) {
    return vector(x + rhs.x, y + rhs.y, z + rhs.z);
  }

  vector operator-(const vector &rhs) {
    return vector(x - rhs.x, y - rhs.y, z - rhs.z);
  }

  vector operator*(const t &rhs) { return vector(x * rhs, y * rhs, z * rhs); }

  vector operator/(const t &rhs) { return vector(x / rhs, y / rhs, z / rhs); }

  t &operator[](std::size_t index) {
    return *reinterpret_cast<t *>(this + index);
  }
};

typedef vector<float> vector3d;
typedef vector<float> qangle;