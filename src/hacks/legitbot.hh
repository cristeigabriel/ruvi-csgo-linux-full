//
//  ruvi base
//

#pragma once

// includes
#include "../core/interfaces/interfaces.hh"
#include "../menu/menu.hh"
#include "../sdk/utils/utilities.hh"

namespace features {

class legitbot {
public:
  void on_override_mouse_input(float *x, float *y);
  void on_create_move(c_user_cmd *cmd);
  void on_paint();

protected:
  void aim(float *x,
           float *y); // aim related (aim assist, angle manipulation, etc)
  void other(c_user_cmd *cmd); // other stuff related to aimbot (legit
                               // anti-aim, backtrack etc)
  void drawing();

private:
  void aim_assist(entity_t *local_player, weapon_t *active_weapon,
                  c_client_class *weapon_class, float *x, float *y);
  void fov_circle(entity_t *local_player);
  void backtrack(entity_t *local_player, c_user_cmd *cmd);

private:
  struct backtrack_settings_t {
    float       simulation_time;
    vector3d    hitbox_position;
    matrix3x4_t bone_matrix[128];
  };
  backtrack_settings_t m_backtrack[64][14];

  struct legitbot_settings_t {};
  legitbot_settings_t m_legitbot;
};
} // namespace features

inline features::legitbot legitbot;