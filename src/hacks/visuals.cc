///
///  ruvi base
///

// includes
#include "visuals.hh"
#include "menu/menu.hh"

void features::visuals::on_paint() {

  // local player pointer
  entity_t *local_player =
      reinterpret_cast<entity_t *>(csgo::entity_list->get_client_entity(
          csgo::engine_client->get_local_player()));

  // main entity loop
  for (std::size_t i = 0; i < csgo::entity_list->get_highest_entity_index();
       i++) {

    // entity pointer
    entity_t *entity =
        reinterpret_cast<entity_t *>(csgo::entity_list->get_client_entity(i));

    if (!entity) continue;

    // client class pointer
    c_client_class *client_class =
        entity->IClientNetworkable()->get_client_class();

    if (!client_class) continue;

    // run thinkers
    if (client_class->class_id == class_id_t::PLAYER)
      player(entity);
    else
      world(entity);

    // makes the map look darker
    visuals::nightmode(entity, client_class);

    // spot entities on radar
    visuals::engine_radar(entity);

    // disable the smoke effect from smoke greandes
    visuals::disable_smoke_effect(entity, client_class);
  }

  // disable some post processing effects
  visuals::disable_post_processing();

  // draw a distorting effect when the local player health is low
  visuals::low_health_warning(local_player);

  // disables the blur on panorama panels
  visuals::disable_panorama_blur();

  // draw a line that predicts the grenade path (where it will land)
  visuals::grenade_prediction();
}

//
// thinkers
//
void features::visuals::player(entity_t *entity) {

  // sanity checks
  if (!entity || entity->IClientNetworkable()->is_dormant() ||
      entity->m_iHealth() == 0)
    return;

  utilities::esp_box_t box;
  if (utilities::create_box(entity, box)) {

    // draw bounding box around the player
    visuals::bounding_box(box);

    // draw the player/bot name above his head
    visuals::player_name(entity, box);
  }
}

void features::visuals::world(entity_t *entity) {

  // sanity checks
  if (!entity || entity->IClientNetworkable()->is_dormant() ||
      entity->m_iHealth() == 0)
    return;

  utilities::esp_box_t box;
  if (utilities::create_box(entity, box)) {}
}

//
// features
//
void features::visuals::bounding_box(const utilities::esp_box_t &box) {

  if (!vars::checkbox["#bounding_box"]->get_bool()) return;

  // draw box
  draw::outline(box.x, box.y, box.width, box.height,
                fgui::color(25, 25, 25, 150));
  draw::outline(box.x + 1, box.y + 1, box.width - 2, box.height - 2,
                fgui::color(200, 75, 75));
}

void features::visuals::player_name(entity_t *                  entity,
                                    const utilities::esp_box_t &box) {

  if (!vars::checkbox["#player_name"]->get_bool()) return;

  // if the entity is a bot
  if (entity->get_entity_info().is_fake_player) {

    // calculate bot name text size
    fgui::dimension text_size = draw::get_text_size(
        fonts.at(FONT_TAHOMA), entity->get_entity_info().name);
    fgui::dimension text_size_bot =
        draw::get_text_size(fonts.at(FONT_TAHOMA), "[BOT]");

    // bot name
    draw::text(box.x + (box.width / 2) - (text_size.width / 2),
               (box.y - text_size.height), fgui::color(200, 200, 200),
               fonts.at(FONT_TAHOMA), entity->get_entity_info().name);
    draw::text(box.x + (box.width / 2) - (text_size.width / 2) +
                   (text_size.width + 2),
               (box.y - text_size.height) - 1, fgui::color(150, 150, 150),
               fonts.at(FONT_TAHOMA), "[BOT]");
  }

  else {

    // calculate player name text size
    fgui::dimension text_size = draw::get_text_size(
        fonts.at(FONT_TAHOMA), entity->get_entity_info().name);

    // wrapper
    const std::string &player_name = entity->get_entity_info().name;

    // safety check
    if (player_name.size() > 17) player_name.substr(0, 17) + "...";

    // player name
    draw::text(box.x + (box.width / 2) - (text_size.width / 2),
               (box.y - text_size.height) - 1, fgui::color(200, 200, 200),
               fonts.at(FONT_TAHOMA), player_name);
  }
}

void features::visuals::nightmode(entity_t *      entity,
                                  c_client_class *client_class) {

  if (client_class->class_id !=
      class_id_t::ENV_TONEMAP_CONTROLLER) // The netvar manager is not
                                          // grabbing the handle to
                                          // m_hTonemapController for some
                                          // reason, so I had to use the class
                                          // id method.
    return;

  // tonemap controller pointer
  tonemap_controller_t *tonemap_controller =
      reinterpret_cast<tonemap_controller_t *>(entity);

  // this is needed because some maps doesn't have proper lightning set up
  if (!tonemap_controller) return;

  // get the skyname convar (is this convar checked?)
  static convar *sv_skyname = csgo::cvar->find_var("sv_skyname");

  // 3d skybox convar
  static convar *r_3dsky = csgo::cvar->find_var("r_3dsky");

  // change skybox
  sv_skyname->set_value(
      "sky_csgo_cloudy01"); // todo: find a proper way to restore sky boxes.

  // disable 3d skybox (newer maps)
  r_3dsky->set_value(!vars::checkbox["#nightmode"]->get_bool());

  // force the game to use a custom exposure value
  *tonemap_controller->m_bUseCustomAutoExposureMin() =
      vars::checkbox["#nightmode"]->get_bool();
  *tonemap_controller->m_bUseCustomAutoExposureMax() =
      vars::checkbox["#nightmode"]->get_bool();

  // set custom exposure value
  *tonemap_controller->m_flCustomAutoExposureMin() = 0.45f;
  *tonemap_controller->m_flCustomAutoExposureMax() = 0.45f;
}

void features::visuals::engine_radar(entity_t *entity) {

  if (!vars::checkbox["#engine_radar"]->get_bool()) return;

  *entity->m_bSpotted() = true;
}

void features::visuals::disable_post_processing() {

  // post process convar
  static convar *mat_postproccesing_enable =
      csgo::cvar->spoof(csgo::cvar->find_var("mat_postprocess_enable"),
                        "mat_postprocess_enable_spoofed");
  static convar *mat_disable_bloom = csgo::cvar->spoof(
      csgo::cvar->find_var("mat_disable_bloom"), "mat_disable_bloom_spoofed");
  static convar *mat_colorcorrection =
      csgo::cvar->spoof(csgo::cvar->find_var("mat_colorcorrection"),
                        "mat_colorcorrection_spoofed");

  // disable post processing effects
  mat_postproccesing_enable->set_value(
      !vars::checkbox["#disable_post_process"]->get_bool());
  mat_disable_bloom->set_value(
      vars::checkbox["#disable_post_process"]->get_bool());
  mat_colorcorrection->set_value(
      !vars::checkbox["#disable_post_process"]->get_bool());
}

void features::visuals::low_health_warning(entity_t *local_player) {

  if (!vars::checkbox["#low_health_warning"]->get_bool()) return;

  if (local_player->m_iHealth() <= 50)
    *local_player->m_flHealthShotBoostExpirationTime() =
        csgo::global_vars->cur_time +
        0.5f; // I'm going to use curtime on this one instead of justing typing
              // a large number. It also makes the effect less "strong" and easy
              // on the eyes.
}

void features::visuals::disable_panorama_blur() {

  // panorama blur convar
  static convar *panorama_disable_blur =
      csgo::cvar->find_var("@panorama_disable_blur");

  // disable blur
  panorama_disable_blur->set_value(
      vars::checkbox["#disable_panorama_blur"]->get_bool());
}

void features::visuals::grenade_prediction() {

  // sv cheats convar
  static convar *sv_cheats =
      csgo::cvar->spoof(csgo::cvar->find_var("sv_cheats"), "sv_cheats_spoofed");

  // grenade preview convar
  static convar *cl_grenadepreview = csgo::cvar->spoof(
      csgo::cvar->find_var("cl_grenadepreview"), "cl_grenadepreview_spoofed");

  // set spoofed sv cheats to true
  sv_cheats->set_value(vars::checkbox["#grenade_prediction"]->get_bool());

  // enable grenade preview
  cl_grenadepreview->set_value(
      vars::checkbox["#grenade_prediction"]->get_bool());
}

void features::visuals::disable_smoke_effect(entity_t *entity,
                                                 c_client_class *client_class) {

  if (!vars::checkbox["#disable_smoke_effect"]->get_bool())
    return;

  if (client_class->class_id != class_id_t::SMOKE_GRENADE_PROJECTILE)
    return;

  // grenade projectile pointer
  smoke_grenade_projectile_t *smoke_grenade_projectile =
      reinterpret_cast<smoke_grenade_projectile_t *>(entity);

  // check if there's a grenade on the world first
  if (!smoke_grenade_projectile)
    return;

  // trick the game on thinking that the smoke effect was already applied 
  *smoke_grenade_projectile->m_bDidSmokeEffect() = true;
  *smoke_grenade_projectile->m_nSmokeEffectTickBegin() = -999; // ghetto fix for preventing the smoke drawing on the local player's position
}