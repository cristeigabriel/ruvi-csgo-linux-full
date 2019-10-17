//
//  ruvi base
//

// includes
#include "legitbot.hh"
#include "../sdk/input/input.hh"
#include "../sdk/utils/globals.hh"
#include "../sdk/utils/math.hh"
#include "menu/menu.hh"

void features::legitbot::on_override_mouse_input(float *x, float *y) {

  // check if we have mouse movement
  if (!*x || !*y) return;

  // run thinkers
  legitbot::aim(x, y);
}

void features::legitbot::on_create_move(c_user_cmd *cmd) {

  // sanity checks
  if (!cmd || !cmd->command_number) return;

  // run thinkers
  legitbot::other(cmd);
}

void features::legitbot::on_paint() {

  // run thinkers
  legitbot::drawing();
}

//
// thinkers
//

void features::legitbot::aim(float *x, float *y) {

  // local player pointer
  entity_t *local_player =
      reinterpret_cast<entity_t *>(csgo::entity_list->get_client_entity(
          csgo::engine_client->get_local_player()));

  // sanity check
  if (local_player->m_iHealth() == 0) return;

  // local player active wapon
  weapon_t *active_weapon = reinterpret_cast<weapon_t *>(
      csgo::entity_list->get_client_entity_from_handle(
          local_player->m_hActiveWeapon()));

  // sanity check
  if (!active_weapon) return;

  // weapon class
  c_client_class *weapon_class =
      active_weapon->IClientNetworkable()->get_client_class();

  // sanity check
  if (!weapon_class) return;

  // aim assist
  legitbot::aim_assist(local_player, active_weapon, weapon_class, x, y);
}

void features::legitbot::other(c_user_cmd *cmd) {

  // local player pointer
  entity_t *local_player =
      reinterpret_cast<entity_t *>(csgo::entity_list->get_client_entity(
          csgo::engine_client->get_local_player()));

  // sanity check
  if (local_player->m_iHealth() == 0) return;

  // make enemies go back in time
  legitbot::backtrack(local_player, cmd);
}

void features::legitbot::drawing() {

  // local player pointer
  entity_t *local_player =
      reinterpret_cast<entity_t *>(csgo::entity_list->get_client_entity(
          csgo::engine_client->get_local_player()));

  // sanity check
  if (local_player->m_iHealth() == 0) return;

  // local player active wapon
  weapon_t *active_weapon = reinterpret_cast<weapon_t *>(
      csgo::entity_list->get_client_entity_from_handle(
          local_player->m_hActiveWeapon()));
  // sanity check
  if (!active_weapon) return;

  // draw a circle displaying the aimbot fov radius
  legitbot::fov_circle(local_player);
}

//
// features
//

void features::legitbot::aim_assist(entity_t *      local_player,
                                    weapon_t *      active_weapon,
                                    c_client_class *weapon_class, float *x,
                                    float *y) {

  if (!vars::checkbox["#aim_assist"]->get_bool()) return;

  //
  // change the value according to the active weapon group
  // move this to a struct later
  //
  static float aimbot_fov      = vars::slider["#field_of_view"]->get_value();
  static float strength_value  = vars::slider["#strength"]->get_value();
  static float smoothing_value = vars::slider["#smoothing"]->get_value();
  static float rcs_amount      = vars::slider["#recoil_control_system"]->get_value();
  static int   aim_hitbox      = 0;

  // sanity checks
  if (active_weapon->m_iClip1() == 0 ||
      (weapon_class->class_id == class_id_t::KNIFE ||
       weapon_class->class_id ==
           class_id_t::KNIFE_GOLDEN)) // TODO: reloading check and grenade check
    return;

  vector3d local_pos = local_player->get_eye_position();

  for (std::size_t i = 1; i <= csgo::entity_list->get_max_entities(); i++) {

    // target pointer
    entity_t *target =
        reinterpret_cast<entity_t *>(csgo::entity_list->get_client_entity(i));

    // sanity checks
    if (!target || target->m_iHealth() == 0 || target == local_player ||
        target->IClientNetworkable()->is_dormant() ||
        target->m_iTeamNum() == local_player->m_iTeamNum() ||
        target->m_bGunGameImmunity())
      continue;

    // aim while flashed
    // if (!vars::checkbox["#aim_while_flashed"]->get_bool() &&
    // local_player->m_flFlashDuration())
    //  continue;

    // scoped only
    // if (vars::checkbox["#scoped_only"]->get_bool() &&
    // active_weapon->is_sniper() && !local_player->m_bIsScoped())
    //  continue;

    // aimbot target
    vector3d hitbox_pos = utilities::get_hitbox_position(target, aim_hitbox);

    // calculate aim angle
    vector3d aim_angle = math::calculate_angle(local_pos, hitbox_pos);

    // recoil control system
    // aim_angle -= local_player->m_aimPunchAngle() * 2.f * rcs_amount;

    // conver pixel to angles
    vector3d move_ang = utilities::pixels_to_angle(vector3d(*x, *y, 0.f));

    // get local player view angles
    vector3d view_angle;
    csgo::engine_client->get_view_angles(&view_angle);

    vector3d view_delta = (aim_angle - view_angle).clamp();

    // aimbot strength
    move_ang *= strength_value;

    // aimbot smoothing
    move_ang /= smoothing_value;

    float delta_y = std::abs(move_ang.y);
    float delta_x = std::abs(move_ang.x);

    vector3d delta = {0.f, 0.f, 0.f};
    delta.x        = std::clamp(view_delta.x, -delta_x, delta_x);
    delta.y        = std::clamp(view_delta.y, -delta_y, delta_y);

    vector3d pixels = utilities::angle_to_pixels(delta);

    if (view_delta.length2d() <= aimbot_fov) {
      *x += pixels.x;
      *y += pixels.y;
    }
  }
}

void features::legitbot::fov_circle(entity_t *local_player) {

  if (!vars::checkbox["#fov_circle"]->get_bool()) return;

  // get screen size
  static int screen_width, screen_height;
  draw::get_screen_size(screen_width, screen_height);

  // get the middle of the screen
  screen_width /= 2;
  screen_height /= 2;

  // settings
  static float fov_value = vars::slider["#field_of_view"]->get_value();
  static float radius    = 6.25f;

  // draw fov circle
  draw::circle(screen_width + 1, screen_height + 1, (fov_value * radius) - 2,
               (fov_value * radius) - 2, fgui::color(25, 25, 25, 150));
  draw::circle(screen_width, screen_height, (fov_value * radius),
               (fov_value * radius), fgui::color(255, 75, 75));
}

void features::legitbot::backtrack(entity_t *local_player, c_user_cmd *cmd) {

  if (!vars::checkbox["#backtrack"]->get_bool()) return;

  int   best_target = -1;
  float best_fov    = 90.f;

  for (std::size_t i = 1; i <= csgo::entity_list->get_max_entities(); i++) {

    // entity pointer
    entity_t *entity =
        reinterpret_cast<entity_t *>(csgo::entity_list->get_client_entity(i));

    // sanity checks
    if (!entity || entity->m_iHealth() == 0 ||
        entity->IClientNetworkable()->is_dormant() ||
        entity->m_iTeamNum() == local_player->m_iTeamNum() ||
        entity == local_player)
      continue;

    m_backtrack[i][cmd->command_number % 14] = backtrack_settings_t{
        entity->m_flSimulationTime(), entity->get_bone_position(8)};

    // calculate view direction
    vector3d view_direction = math::angle_vector(cmd->view_angles);

    // distance point to line
    float fov = math::distance_point_to_line(entity->get_bone_position(8),
                                             local_player->get_bone_position(8),
                                             view_direction);

    // look for potential target
    if (best_fov > fov) {
      best_fov    = fov;
      best_target = i;
    }
  }

  float best_target_simulation_time = 0.f;

  // if we have a potential target
  if (best_target != -1) {

    float temp = std::numeric_limits<float>::max();

    // calculate view direction
    vector3d view_direction = math::angle_vector(cmd->view_angles);

    // loop through 'backtrackable' ticks
    for (std::size_t t = 0; t < vars::slider["#backtrack_ticks"]->get_value();
         ++t) {

      float fov = math::distance_point_to_line(
          m_backtrack[best_target][t].hitbox_position,
          local_player->get_bone_position(8), view_direction);

      // find a potential target in the backtrack range
      if (temp > fov && m_backtrack[best_target][t].simulation_time >
                            local_player->m_flSimulationTime() - 1.f) {
        temp = fov;
        best_target_simulation_time =
            m_backtrack[best_target][t].simulation_time;
      }
    }

    // backtrack target
    if (cmd->buttons & cmd_buttons_t::IN_ATTACK) {
      cmd->tick_count = static_cast<int>(
          0.5f + static_cast<float>(best_target_simulation_time) /
                     csgo::global_vars->interval_per_tick);
    }
  }
}