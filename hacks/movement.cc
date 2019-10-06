//
// ruvi base
//

#include "movement.hh"
#include "menu/menu.hh"

void features::movement::on_move(c_user_cmd *cmd) { movement::bunny_hop(cmd); }

void features::movement::bunny_hop(c_user_cmd *cmd) {     /* spent a few of my minutes writing this */ 
                                                          /* and seeing how fuzion does it, no idea why*/
  if (!vars::checkbox["#bunny_hop"]->get_bool()) return;  /* it acts up and just doesn't work, will fix it later:TM:*/

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
    if (local_player->m_iFlags() & ON_GROUND) {

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
