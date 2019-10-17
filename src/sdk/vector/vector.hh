//
//  ruvi base
//

#pragma once

// includes
#include <algorithm>
#include <cmath>
#include <math.h>

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

  // helpers
  inline vector normalize() {
    if (length() != 0.f)
      *this /= length();
    else
      x = y = z = 0.f;

    return *this;
  }

  inline vector clamp() {
    x = std::clamp(x, -89.f, 89.f);
    y = std::clamp(std::remainder(y, 360.f), -180.f, 180.f);
    z = std::clamp(z, -50.f, 50.f);

    return *this;
  }

  inline float length2d() const { return std::sqrt(x * x + y * y); }

  inline float length() const { return std::sqrt(x * x + y * y + z * z); }

  inline t dot_product(const vector &rhs) {
    return (x * rhs.x + y * rhs.y + z * rhs.z);
  }

  inline t dot_product(const float *rhs) {

    vector temp = *this;

    return (temp.x * rhs[0] + temp.y * rhs[1] + temp.z * rhs[2]);
  }

  // operators
  vector &operator+=(const vector &rhs) const {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  vector &operator-=(const vector &rhs) const {
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

  vector operator+(const vector &rhs) const {
    return vector(x + rhs.x, y + rhs.y, z + rhs.z);
  }

  vector operator-(const vector &rhs) const {
    return vector(x - rhs.x, y - rhs.y, z - rhs.z);
  }

  vector operator*(const t &rhs) const {
    return vector(x * rhs, y * rhs, z * rhs);
  }

  vector operator/(const t &rhs) const {
    return vector(x / rhs, y / rhs, z / rhs);
  }

  t &operator[](std::size_t index) const {
    return ((t *)this)[index]; // c-style casting REEE
  }
};

class vector_aligned : public vector<float> {
public:
  vector_aligned() {
    x = 0.f;
    y = 0.f;
    z = 0.f;
  }
  vector_aligned(const vector &_v) {
    x = _v.x;
    y = _v.y;
    z = _v.z;
  }

  float w;
};

using vector3d = vector<float>;
using qangle   = vector<float>;