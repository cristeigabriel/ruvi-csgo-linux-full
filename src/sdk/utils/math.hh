//
//  ruvi base
//

#pragma once

// includes
#include "../vector/vector.hh"

namespace math {

inline void vector_angles(const vector3d &forward, qangle &angles) {

  if (forward[1] == 0.f && forward[0] == 0.f) {
    angles[0] = (forward[2] > 0.f) ? 270.f : 90.f; // pitch
    angles[1] = 0.f;                               // yaw
  } else {
    angles[0] = std::atan2(-forward[2], forward.length2d()) *
                (-180.f / static_cast<float>(M_PI));
    angles[1] =
        std::atan2(forward[1], forward[0]) * (180.f / static_cast<float>(M_PI));

    if (angles[1] > 90.f)
      angles[1] -= 180.f;

    else if (angles[1] < 90.f)
      angles[1] += 180.f;

    else if (angles[1] == 90.f)
      angles[1] = 0.f;
  }

  angles[2] = 0.f;
}

inline vector3d calculate_angle(const vector3d &src, const vector3d &dst) {

  qangle   angles = {0.f, 0.f, 0.f};
  vector3d delta  = (src - dst);

  math::vector_angles(delta, angles);

  delta.normalize();

  return angles;
}

inline vector3d angle_vector(vector3d to_convert) {

  float y_sin = std::sin(to_convert.y / 180.f * static_cast<float>(M_PI));
  float y_cos = std::cos(to_convert.y / 180.f * static_cast<float>(M_PI));

  float x_sin = std::sin(to_convert.x / 180.f * static_cast<float>(M_PI));
  float x_cos = std::cos(to_convert.x / 180.f * static_cast<float>(M_PI));

  return {(x_cos * y_cos), (x_cos * y_sin), -x_sin};
}

inline float distance_point_to_line(vector3d point, vector3d origin,
                                    vector3d direction) {

  vector3d delta = (point - origin);

  float temp = delta.dot_product(direction) /
               (direction.x * direction.x + direction.y * direction.y +
                direction.z * direction.z);

  if (temp < 0.000001f)
    return *reinterpret_cast<float *>(std::numeric_limits<float>::max);

  vector3d temp_vec = origin + (direction * temp);

  return (point - temp_vec).length();
}

inline vector3d vector_transform(vector3d &in, matrix3x4_t &matrix, vector3d &out) {

  for (std::size_t i = 0; i < 3; i++)
    out[i] = in.dot_product(matrix.matrix_value[i]) + matrix.matrix_value[i][3];

  return out;
}

} // namespace math