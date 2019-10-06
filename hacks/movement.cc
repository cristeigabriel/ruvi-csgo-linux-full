//
// ruvi base
//

#include "movement.hh"
#include "menu/menu.hh"

void features::movement::on_create_move(c_user_cmd *cmd) {

  movement::bunny_hop(cmd);
  movement::auto_strafe(cmd);

}

void features::movement::bunny_hop(c_user_cmd *cmd) {

  if (!vars::checkbox["#bunny_hop"]->get_bool()) return;

  /*for later additions*/
  static bool b_last_jumped = false;
  static bool b_should_fake = false;
  static int  b_actual_hop  = 0;

  entity_t *local_player =
      reinterpret_cast<entity_t *>(csgo::entity_list->get_client_entity(
          csgo::engine_client->get_local_player()));

  if (!local_player || local_player->m_iHealth() == 0) return;

  if (!b_last_jumped && b_should_fake) {

    b_should_fake = false;
    cmd->buttons |= IN_JUMP;
  }

  else if (cmd->buttons & IN_JUMP) {
    if (local_player->m_fFlags() & ON_GROUND) {

      b_actual_hop++;
      b_last_jumped = true;
      b_should_fake = true;
    } else {

      cmd->buttons &= ~IN_JUMP;
      b_last_jumped = false;
    }
  } else {

    b_actual_hop  = 0;
    b_last_jumped = false;
    b_should_fake = false;
  }
}

void features::movement::auto_strafe(c_user_cmd *cmd) {

  if (!vars::checkbox["#auto_strafe"]->get_bool()) return;

  entity_t *local_player =
      reinterpret_cast<entity_t *>(csgo::entity_list->get_client_entity(
          csgo::engine_client->get_local_player()));

  if (!local_player || local_player->m_iHealth() == 0) return;

  if (cmd->buttons & IN_FORWARD || cmd->buttons & IN_BACK ||
      cmd->buttons & IN_MOVELEFT || cmd->buttons & IN_MOVERIGHT)
    return;

  if (cmd->mouse_dx <= 1 && cmd->mouse_dx >= -1) return;

  if (local_player->m_fFlags() & ON_GROUND) return;

  cmd->side_move = cmd->mouse_dx < 0 ? -450.0f : 450.0f;
}