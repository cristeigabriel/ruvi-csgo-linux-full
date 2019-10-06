//
// ruvi base
//

#include "miscellaneous.hh"
#include "menu/menu.hh"

void features::miscellaneous::on_create_move(c_user_cmd *cmd) {

  miscellaneous::rank_revealer(cmd);
}

void features::miscellaneous::rank_revealer(c_user_cmd *cmd) {

  if (!vars::checkbox["#rank_revealer"]->get_bool()) return;

  entity_t *local_player =
      reinterpret_cast<entity_t *>(csgo::entity_list->get_client_entity(
          csgo::engine_client->get_local_player()));

  if (local_player->m_fFlags() & IN_SCORE)
    csgo::base_client->dispatch_user_message(CS_UM_ServerRankRevealAll, 0, 0, nullptr);
}