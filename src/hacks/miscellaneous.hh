///
///  ruvi base
///

// includes
#include "../core/interfaces/interfaces.hh"
#include "../sdk/utils/utilities.hh"

namespace features {

class miscellaneous { // using classes for this might be a little bit overkill,
                      // but
                      // IMO it's better for organization, and feature control.
public:
  void on_create_move(c_user_cmd *cmd);

protected:
  void movement(c_user_cmd *cmd); // movement related features (auto strafer,
                                  // bunny hop, etc)
  void
  other(c_user_cmd *cmd); // other features (rank revealer, name changer, etc)
private:
  void bunny_hop(entity_t *local_player, c_user_cmd *cmd);
  void auto_strafe(entity_t *local_player, c_user_cmd *cmd);
  void rank_revealer(entity_t *local_player, c_user_cmd *cmd);
  void crouch_exploit(c_user_cmd *cmd);
  void instant_bomb_plant(entity_t *local_player, weapon_t *active_weapon,
                          c_user_cmd *cmd);
  void thirdperson_while_spectating(entity_t *local_player);
};

} // namespace features

inline features::miscellaneous miscellaneous;