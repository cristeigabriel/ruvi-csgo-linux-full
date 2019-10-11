///
///  ruvi base
///

// includes
#include "core/hooks/hooks.hh"
#include "menu/menu.hh"
#include "visuals.hh"

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

  // disables the flashbang effect
  visuals::disable_flashbang_effect(local_player);
}

void features::visuals::on_override_view(c_view_setup *view_setup) {

  if (!view_setup) return;

  // local player pointer
  entity_t *local_player =
      reinterpret_cast<entity_t *>(csgo::entity_list->get_client_entity(
          csgo::engine_client->get_local_player()));

  // run thinker
  visuals::view(local_player, view_setup);
}

void features::visuals::on_draw_model_execute(
    i_mat_render_context *render_context, void *state,
    const model_render_info_t &model_info, matrix3x4_t *custom_bone_to_world) {

  // entity pointer
  entity_t *entity = reinterpret_cast<entity_t *>(
      csgo::entity_list->get_client_entity(model_info.entity_index));

  // model name
  const std::string_view model_name =
      csgo::model_info->get_model_name(model_info.model);

  static std::once_flag once_flag1, once_flag2;

  // create chams material
  std::call_once(once_flag1, utilities::create_materials);

  // grab original function from draw model execute
  std::call_once(once_flag2,
                 draw_model_execute_original.operator=(std::bind(
                     hooks::draw_model_execute::original, csgo::model_render,
                     render_context, state, model_info,
                     custom_bone_to_world))); // what the fuck is this lmao

  // run thinkers
  if (model_name.compare("models/player"))
    visuals::player_advanced(entity);
  else
    visuals::world_advanced(entity);
}

//
// thinkers
//
void features::visuals::player(entity_t *entity) {

  // local player pointer
  entity_t *local_player =
      reinterpret_cast<entity_t *>(csgo::entity_list->get_client_entity(
          csgo::engine_client->get_local_player()));

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

void features::visuals::view(entity_t *local_player, c_view_setup *view_setup) {

  // sanity checks
  if (!view_setup || local_player->m_iHealth() == 0) return;

  // force the thirdperson camera
  visuals::force_thirdperson(local_player);
}

void features::visuals::player_advanced(entity_t *entity) {

  // sanity checks
  if (!entity || entity->IClientNetworkable()->is_dormant() ||
      entity->m_iHealth() == 0)
    return;

  // change player textures color
  visuals::player_chams(entity);
}

void features::visuals::world_advanced(entity_t *entity) {

  // sanity checks
  if (!entity || entity->IClientNetworkable()->is_dormant() ||
      entity->m_iHealth() == 0)
    return;
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
        draw::get_text_size(fonts.at(FONT_TAHOMA), STR("[BOT]"));

    // bot name
    draw::text(box.x + (box.width / 2) - (text_size.width / 2),
               (box.y - text_size.height), fgui::color(200, 200, 200),
               fonts.at(FONT_TAHOMA), entity->get_entity_info().name);
    draw::text(box.x + (box.width / 2) - (text_size.width / 2) +
                   (text_size.width + 2),
               (box.y - text_size.height) - 1, fgui::color(150, 150, 150),
               fonts.at(FONT_TAHOMA), STR("[BOT]"));
  }

  else {

    // calculate player name text size
    fgui::dimension text_size = draw::get_text_size(
        fonts.at(FONT_TAHOMA), entity->get_entity_info().name);

    // wrapper
    const std::string &player_name = entity->get_entity_info().name;

    // safety check
    if (player_name.size() > 17) player_name.substr(0, 17) + STR("...");

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
  static convar *sv_skyname = csgo::cvar->find_var(STR("sv_skyname"));

  // 3d skybox convar
  static convar *r_3dsky = csgo::cvar->find_var(STR("r_3dsky"));

  // change skybox
  sv_skyname->set_value(STR(
      "sky_csgo_cloudy01")); // todo: find a proper way to restore sky boxes.

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
      csgo::cvar->spoof(csgo::cvar->find_var(STR("mat_postprocess_enable")),
                        STR("mat_postprocess_enable_spoofed"));
  static convar *mat_disable_bloom =
      csgo::cvar->spoof(csgo::cvar->find_var(STR("mat_disable_bloom")),
                        STR("mat_disable_bloom_spoofed"));
  static convar *mat_colorcorrection =
      csgo::cvar->spoof(csgo::cvar->find_var(STR("mat_colorcorrection")),
                        STR("mat_colorcorrection_spoofed"));

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
      csgo::cvar->find_var(STR("@panorama_disable_blur"));

  // disable blur
  panorama_disable_blur->set_value(
      vars::checkbox["#disable_panorama_blur"]->get_bool());
}

void features::visuals::grenade_prediction() {

  // sv cheats convar
  static convar *sv_cheats = csgo::cvar->spoof(
      csgo::cvar->find_var(STR("sv_cheats")), ("sv_cheats_spoofed"));

  // grenade preview convar
  static convar *cl_grenadepreview =
      csgo::cvar->spoof(csgo::cvar->find_var(STR("cl_grenadepreview")),
                        STR("cl_grenadepreview_spoofed"));

  // set spoofed sv cheats to true
  sv_cheats->set_value(vars::checkbox["#grenade_prediction"]->get_bool());

  // enable grenade preview
  cl_grenadepreview->set_value(
      vars::checkbox["#grenade_prediction"]->get_bool());
}

void features::visuals::disable_smoke_effect(entity_t *      entity,
                                             c_client_class *client_class) {

  if (!vars::checkbox["#disable_smoke_effect"]->get_bool()) return;

  if (client_class->class_id != class_id_t::SMOKE_GRENADE_PROJECTILE) return;

  // grenade projectile pointer
  smoke_grenade_projectile_t *smoke_grenade_projectile =
      reinterpret_cast<smoke_grenade_projectile_t *>(entity);

  // check if there's a grenade on the world first
  if (!smoke_grenade_projectile) return;

  // trick the game on thinking that the smoke effect was already applied
  *smoke_grenade_projectile->m_bDidSmokeEffect() = true;
  *smoke_grenade_projectile->m_nSmokeEffectTickBegin() =
      -999; // ghetto fix for preventing the smoke drawing on the local player's
            // position
}

void features::visuals::disable_flashbang_effect(entity_t *local_player) {

  if (!vars::checkbox["#disable_flashbang_effect"]->get_bool()) return;

  // set the flashbang effect alpha to 0
  *local_player->m_flFlashMaxAlpha() = 0.f;
}

void features::visuals::force_thirdperson(entity_t *local_player) {

  if (!vars::checkbox["#force_thirdperosn"]->get_bool()) {
    csgo::input->camera_in_third_person = false;
    return;
  }

  constexpr float camera_distance = 150.f; // TODO: make this dynamic

  // local player view angles
  static qangle view_angles = {0.f, 0.f, 0.f};
  csgo::engine_client->get_view_angles(&view_angles);

  // callback update visibility (this will fix the flickering on local servers)
  local_player->update_visibility_all_entities();

  if (local_player->m_iHealth() > 0) {
    csgo::input->camera_in_third_person = true;
    csgo::input->camera_offset          = {view_angles.x, view_angles.y,
                                  camera_distance};
  } else
    csgo::input->camera_in_third_person = false;
}

void features::visuals::player_chams(entity_t *entity) {

  if (!vars::checkbox["#player_chams"]->get_bool()) return;

  // chams materials
  i_material *normal_material =
      csgo::material_system->find_material("normal_material", "Other textures");
  i_material *ignorez_material = csgo::material_system->find_material(
      "ignorez_material", "Other textures");

  // check if materials are valid
  if (!normal_material || !ignorez_material) return;

  // normal color (r: 200, g: 100, b: 0)
  // ignorez color (r: 255, g: 255, b: 255)
  float normal_chams_color[3]  = {(255.f / 255.f), (75.f / 255.f),
                                 (75.f / 255.f)};
  float ignorez_chams_color[3] = {1.f, 1.f, 1.f};

  // change texture color (behind walls)
  csgo::render_view->set_color_modulation(ignorez_chams_color);

  // replace model texture with our own
  csgo::model_render->force_override_material(ignorez_material);

  draw_model_execute_original();

  // change texture color
  csgo::render_view->set_color_modulation(normal_chams_color);

  // replace model texture with our own
  csgo::model_render->force_override_material(normal_material);
}