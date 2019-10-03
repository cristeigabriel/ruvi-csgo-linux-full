//
//  ruvi base
//

#pragma once

// includes
#include "../../core/interfaces/interfaces.hh"
#include "../vector/vector.hh"
#include <cmath>

namespace utilities {

inline void move_fix_start(c_user_cmd *cmd, qangle old_angle,
                           float old_forward_move, float old_side_move) {

  old_angle = cmd->view_angles;
  old_forward_move = cmd->forward_move;
  old_side_move = cmd->side_move;
}

inline void move_fix_end(c_user_cmd *cmd, qangle old_angle,
                         float old_forward_move, float old_side_move) {

  float yaw_delta = cmd->view_angles.y - old_angle.y;
  float f1, f2;

  if (old_angle.y < 0.f)
    f1 = 360.0f + old_angle.y;
  else
    f1 = old_angle.y;

  if (cmd->view_angles.y < 0.0f)
    f2 = 360.0f + cmd->view_angles.y;
  else
    f2 = cmd->view_angles.y;

  if (f2 < f1)
    yaw_delta = std::abs(f2 - f1);
  else
    yaw_delta = 360.0f - std::abs(f1 - f2);

  yaw_delta = 360.0f - yaw_delta;

  cmd->forward_move = std::cos(DEG2RAD(yaw_delta)) * old_forward_move +
                      std::cos(DEG2RAD(yaw_delta + 90.f)) * old_side_move;
  cmd->side_move = std::sin(DEG2RAD(yaw_delta)) * old_forward_move +
                   std::sin(DEG2RAD(yaw_delta + 90.f)) * old_side_move;
}

inline vector3d rotate_point(vector3d point_to_rotate, int center_x,
                             int center_y, float angle) {

  // angle in radians
  float angle_in_radians = angle * (M_PI / 180.f);

  // sin and cos theta
  float sin_theta = std::sin(angle_in_radians);
  float cos_theta = std::cos(angle_in_radians);

  return {(cos_theta * (point_to_rotate.x - center_x) -
           sin_theta * (point_to_rotate.y - center_y) + center_x),
          (sin_theta * (point_to_rotate.x - center_x) +
           cos_theta * (point_to_rotate.y - center_y) + center_y),
          0.f};
}
} // namespace utilities