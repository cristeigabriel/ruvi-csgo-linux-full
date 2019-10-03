//
//  ruvi base
//

#pragma once

// includes
#include "../vector/vector.hh"

enum cmd_buttons_t {
  in_attack = (1 << 0),
  in_jump = (1 << 1),
  in_duck = (1 << 2),
  in_forward = (1 << 3),
  in_back = (1 << 4),
  in_use = (1 << 5),
  in_cancel = (1 << 6),
  in_left = (1 << 7),
  in_right = (1 << 8),
  in_moveleft = (1 << 9),
  in_moveright = (1 << 10),
  in_attack2 = (1 << 11),
  in_run = (1 << 12),
  in_reload = (1 << 13),
  in_alt1 = (1 << 14),
  in_alt2 = (1 << 15),
  in_score = (1 << 16),
  in_speed = (1 << 17),
  in_walk = (1 << 18),
  in_zoom = (1 << 19),
  in_weapon1 = (1 << 20),
  in_weapon2 = (1 << 21),
  in_bullrush = (1 << 22),
  in_grenade1 = (1 << 23),
  in_grenade2 = (1 << 24),
  in_attack3 = (1 << 25)
};

class c_user_cmd {
public:
  virtual ~c_user_cmd(){};

  int command_number;
  int tick_count;
  qangle view_angles;
  vector3d aim_direction;
  float forward_move;
  float side_move;
  float up_move;
  int buttons;
  unsigned char impulse;
  int weapon_select;
  int weapon_subtype;
  int random_seed;
  short mouse_dx;
  short mouse_dy;
  bool has_been_predicted;
  qangle head_angles;
  vector3d head_offset;
};