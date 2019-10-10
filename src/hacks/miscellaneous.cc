//
// ruvi base
//

#include "menu/menu.hh"
#include "miscellaneous.hh"

void features::miscellaneous::on_create_move(c_user_cmd *cmd) {

  if (!cmd) return;

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

  // local player's active weapon
  weapon_t *active_weapon = reinterpret_cast<weapon_t *>(
      csgo::entity_list->get_client_entity_from_handle(
          local_player->m_hActiveWeapon()));

  if (!cmd || !active_weapon || local_player->m_iHealth() == 0) return;

  // hit perfect jumps
  miscellaneous::bunny_hop(local_player, cmd);

  // automatically strafes for you
  miscellaneous::auto_strafe(local_player, cmd);

  // disables stamina when crouching
  miscellaneous::crouch_exploit(cmd);

  // removes the 3 second delay when you tries to plant the c4 while walking
  miscellaneous::instant_bomb_plant(local_player, active_weapon, cmd);
}

void features::miscellaneous::other(c_user_cmd *cmd) {

  // local player pointer
  entity_t *local_player =
      reinterpret_cast<entity_t *>(csgo::entity_list->get_client_entity(
          csgo::engine_client->get_local_player()));

  if (!cmd) return;

  // reveal players ranks
  miscellaneous::rank_revealer(local_player, cmd);

  // force thirdperson camera while spectating other player
  miscellaneous::thirdperson_while_spectating(local_player);
}

//
// features
//
void features::miscellaneous::bunny_hop(entity_t *  local_player,
                                        c_user_cmd *cmd) {

  if (!vars::checkbox["#bunny_hop"]->get_bool()) return;

  // for later additions
  static bool last_jumped = false;
  static bool should_fake = false;
  static int  actual_hop  = 0;

  if (!last_jumped && should_fake) {

    should_fake = false;
    cmd->buttons |= cmd_buttons_t::IN_JUMP;
  }

  else if (cmd->buttons & cmd_buttons_t::IN_JUMP) {
    if (local_player->m_fFlags() & entity_flag_t::ON_GROUND) {

      actual_hop++;
      last_jumped = true;
      should_fake = true;
    } else {

      cmd->buttons &= ~cmd_buttons_t::IN_JUMP;
      last_jumped = false;
    }
  } else {

    actual_hop  = 0;
    last_jumped = false;
    should_fake = false;
  }
}

void features::miscellaneous::auto_strafe(entity_t *  local_player,
                                          c_user_cmd *cmd) {

  if (!vars::checkbox["#auto_strafe"]->get_bool()) return;

  if (cmd->buttons & cmd_buttons_t::IN_FORWARD ||
      cmd->buttons & cmd_buttons_t::IN_BACK ||
      cmd->buttons & cmd_buttons_t::IN_MOVELEFT ||
      cmd->buttons & cmd_buttons_t::IN_MOVERIGHT)
    return;

  if (cmd->mouse_dx <= 1 && cmd->mouse_dx >= -1) return;

  if (local_player->m_fFlags() & entity_flag_t::ON_GROUND) return;

  cmd->side_move = cmd->mouse_dx < 0 ? -450.0f : 450.0f;
}

void features::miscellaneous::rank_revealer(entity_t *  local_player,
                                            c_user_cmd *cmd) {

  if (!vars::checkbox["#rank_revealer"]->get_bool()) return;

  if (cmd->buttons & cmd_buttons_t::IN_SCORE)
    csgo::base_client->dispatch_user_message(CS_UM_ServerRankRevealAll, 0, 0,
                                             nullptr);
}

void features::miscellaneous::crouch_exploit(c_user_cmd *cmd) {

  if (!vars::checkbox["#crouch_exploit"]->get_bool()) return;

  cmd->buttons |= cmd_buttons_t::IN_BULLRUSH;
}

void features::miscellaneous::instant_bomb_plant(entity_t *  local_player,
                                                 weapon_t *  active_weapon,
                                                 c_user_cmd *cmd) {

  if (!vars::checkbox["#instant_bomb_plant"]->get_bool()) return;

  // check if the local player is holding a c4 and if he is on the bomb site
  if (active_weapon->m_iItemDefinitionIndex() !=
          item_definition_index_t::WEAPON_C4 ||
      (local_player->m_bInBombZone() &&
       local_player->m_fFlags() & entity_flag_t::ON_GROUND))
    return;

  if (!cmd->buttons & cmd_buttons_t::IN_USE &&
      !cmd->buttons & cmd_buttons_t::IN_ATTACK)
    return;

  // start planting the bomb as soon as the user hits the plant key (this will
  // remove the delay that happens when you try to plant the c4
  // while walking on the bomb site)
  cmd->buttons &= ~cmd_buttons_t::IN_USE;
  cmd->buttons &= ~cmd_buttons_t::IN_ATTACK;
}

void features::miscellaneous::thirdperson_while_spectating(entity_t* local_player) {

  if (!vars::checkbox["#thirdperson_while_spectating"]->get_bool()) return;

  // check if the local player is dead
  if (local_player->m_iHealth() == 0)
    *local_player->m_iObserverMode() = observer_mode_t::MODE_CHASE;
}