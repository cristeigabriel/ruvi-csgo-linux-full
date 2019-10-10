//
//  ruvi base
//

#pragma once

// includes
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

  float *operator[](std::size_t index) { return matrix_value[index]; }

  const float *operator[](std::size_t index) const {
    return matrix_value[index];
  }

  float matrix_value[3][4];
};