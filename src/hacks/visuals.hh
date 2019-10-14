///
///  ruvi base
///

// includes
#include "../core/interfaces/interfaces.hh"
#include "../sdk/utils/utilities.hh"
#include <array>
#include <functional>
#include <mutex>

namespace features {

class visuals { // using classes for this might be a little bit overkill, but
                // IMO it's better for organization, and feature control.
public:
  void on_paint(); // main entity loop and other visuals
  void on_override_view(c_view_setup *view_setup); // override view
  void on_draw_model_execute(
      i_mat_render_context *render_context, void *state,
      const model_render_info_t &model_info,
      matrix3x4_t *              custom_bone_to_world); // draw model execute
  void on_render_view(c_view_setup &view_setup, c_view_setup &hud_setup,
                      int clear_flags, int what_to_draw);

protected:
  void player(entity_t *entity); // player visuals (bounding box, name esp,
                                 // weapon esp, flags, etc)
  void world(entity_t *world); // non player visuals (dropped weapons, grenades
                               // esp, etc)

  void
  view(entity_t *    local_player,
       c_view_setup *view_setup); // everything that manipulates the screen or
                                  // camera (thirdperson, fov changer, etc)
  void view_advanced(entity_t *local_player, c_view_setup &view_setup,
                     i_mat_render_context *render_context);

  void player_advanced(
      entity_t *            entity,
      i_mat_render_context *render_context); // player advanced drawing (chams,
                                             // custom textures, glow, etc)
  void world_advanced(
      entity_t *entity,
      i_mat_render_context
          *render_context); // non player advanced drawing (weapon chams,
                            // weapon, glow, custom weapon skins, etc)
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
  void disable_flashbang_effect(entity_t *local_player);
  void force_thirdperson(entity_t *local_player);
  void player_chams();
  void mirror_cam(i_texture* texture, c_view_setup &        view_setup,
                   i_mat_render_context *render_context);

private:
  std::function<void()> draw_model_execute_original;
};

} // namespace features

inline features::visuals visuals;