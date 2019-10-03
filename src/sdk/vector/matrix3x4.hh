//
//  ruvi base
//

// includes
#include "vector.hh"
#include <cstdint>

class matrix3x4_t {
public:
  matrix3x4_t() {}

  matrix3x4_t(float m00, float m01, float m02, float m03, float m10, float m11,
              float m12, float m13, float m20, float m21, float m22,
              float m23) {
    matrix_value[0][0] = m00;
    matrix_value[0][1] = m01;
    matrix_value[0][2] = m02;
    matrix_value[0][3] = m03;
    matrix_value[1][0] = m10;
    matrix_value[1][1] = m11;
    matrix_value[1][2] = m12;
    matrix_value[1][3] = m13;
    matrix_value[2][0] = m20;
    matrix_value[2][1] = m21;
    matrix_value[2][2] = m22;
    matrix_value[2][3] = m23;
  }

  void init(const vector3d &x_axis, const vector3d &y_axis,
            const vector3d &z_axis, const vector3d &origin) {
    matrix_value[0][0] = x_axis.x;
    matrix_value[0][1] = y_axis.x;
    matrix_value[0][2] = z_axis.x;
    matrix_value[0][3] = origin.x;
    matrix_value[1][0] = x_axis.y;
    matrix_value[1][1] = y_axis.y;
    matrix_value[1][2] = z_axis.y;
    matrix_value[1][3] = origin.y;
    matrix_value[2][0] = x_axis.z;
    matrix_value[2][1] = y_axis.z;
    matrix_value[2][2] = z_axis.z;
    matrix_value[2][3] = origin.z;
  }

  matrix3x4_t(const vector3d &x_axis, const vector3d &y_axis,
              const vector3d &z_axis, const vector3d &origin) {
    init(x_axis, y_axis, z_axis, origin);
  }

  float *operator[](std::size_t index) { return matrix_value[index]; }

  const float *operator[](std::size_t index) const {
    return matrix_value[index];
  }

  float matrix_value[3][4];
};