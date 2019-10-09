///
///  ruvi base
///

// includes
#include "../core/interfaces/interfaces.hh"
#include "../sdk/utils/utilities.hh"

namespace features {

class visuals { // using classes for this might be a little bit overkill, but
                // IMO it's better for organization, and feature control.
public:
  void on_paint(); // main entity loop and other visuals
protected:
  void player(entity_t *entity); // player visuals (bounding box, name esp,
                                 // weapon esp, flags, etc)
  void world(entity_t *world); // non player visuals (dropped weapons, grenades
                               // esp, etc)
private:
  void bounding_box(const utilities::esp_box_t &box);
  void player_name(entity_t *entity, const utilities::esp_box_t &box);
  void nightmode(entity_t *entity, c_client_class *client_class);
  void engine_radar(entity_t *entity);
  void disable_post_processing();
  void low_health_warning(entity_t *local_player);
  void grenade_prediction();
  void disable_panorama_blur();
  void disable_smoke_effect(entity_t *entity, c_client_class *client_class);
};

} // namespace features

inline features::visuals visuals;