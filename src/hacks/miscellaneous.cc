//
// ruvi base
//

#include "miscellaneous.hh"
#include "menu/menu.hh"

void features::miscellaneous::on_create_move(c_user_cmd *cmd) {

  if (!cmd)
    return;

  // run thinkers
  movement(cmd);
  other(cmd);
}

//
// thinkers
//
void features::miscellaneous::movement(c_user_cmd *cmd) {

  // local player pointer
  entity_t *local_player =
      reinterpret_cast<entity_t *>(csgo::entity_list->get_client_entity(
          csgo::engine_client->get_local_player()));

  if (!cmd || local_player->m_iHealth() == 0)
    return;

  // hit perfect jumps
  features::miscellaneous::bunny_hop(local_player, cmd);
  
  // strafe according to viewangles
  features::miscellaneous::auto_strafe(local_player, cmd);
}

void features::miscellaneous::other(c_user_cmd *cmd) {

  // local player pointer
  entity_t *local_player =
      reinterpret_cast<entity_t *>(csgo::entity_list->get_client_entity(
          csgo::engine_client->get_local_player()));
  
  if (!cmd)
    return;

  // reveal players ranks
  features::miscellaneous::rank_revealer(local_player, cmd);
}

//
// features
//
void features::miscellaneous::bunny_hop(entity_t* local_player, c_user_cmd *cmd) {

  if (!vars::checkbox["#bunny_hop"]->get_bool())
    return;

  // for later additions 
  static bool last_jumped = false;
  static bool should_fake = false;
  static int actual_hop = 0;

  if (!last_jumped && should_fake) {

    should_fake = false;
    cmd->buttons |= IN_JUMP;
  }

  else if (cmd->buttons & IN_JUMP) {
    if (local_player->m_fFlags() & ON_GROUND) {

      actual_hop++;
      last_jumped = true;
      should_fake = true;
    } else {

      cmd->buttons &= ~IN_JUMP;
      last_jumped = false;
    }
  } else {

    actual_hop = 0;
    last_jumped = false;
    should_fake = false;
  }
}

void features::miscellaneous::auto_strafe(entity_t* local_player, c_user_cmd *cmd) {

  if (!vars::checkbox["#auto_strafe"]->get_bool())
    return;

  if (cmd->buttons & cmd_buttons_t::IN_FORWARD || cmd->buttons & cmd_buttons_t::IN_BACK ||
      cmd->buttons & cmd_buttons_t::IN_MOVELEFT || cmd->buttons & cmd_buttons_t::IN_MOVERIGHT)
    return;

  if (cmd->mouse_dx <= 1 && cmd->mouse_dx >= -1)
    return;

  if (local_player->m_fFlags() & entity_flag_t::ON_GROUND)
    return;

  cmd->side_move = cmd->mouse_dx < 0 ? -450.0f : 450.0f;
}

void features::miscellaneous::rank_revealer(entity_t* local_player, c_user_cmd *cmd) {

  if (!vars::checkbox["#rank_revealer"]->get_bool())
    return;

  if (cmd->buttons & cmd_buttons_t::IN_SCORE)
    csgo::base_client->dispatch_user_message(CS_UM_ServerRankRevealAll, 0, 0,
                                             nullptr);
}
