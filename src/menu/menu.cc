//
//  ruvi base
//

// includes
#include "menu.hh"

// temporary
#include "../core/interfaces/interfaces.hh"
#include "../sdk/utils/globals.hh"

//
// move this to another place
//
void mirror_cam(std::shared_ptr<fgui::container> window) {

  if (csgo::engine_client->is_in_game()) {

    // window position
    fgui::point position = window->get_absolute_position();

    // window size
    fgui::dimension size = window->get_size();

    // render context pointer
    i_mat_render_context *render_context =
        csgo::material_system->get_render_context();

    if (!render_context) return;

    // mirror cam material
    static i_material *mirror_material = csgo::material_system->find_material(
        "mirrorcam_material", "Other textures");

    if (!mirror_material || !globals::mirror_texture)
      return;

    render_context->draw_screen_space_rectangle(
        mirror_material, position.x + 6, position.y + 26, size.width - 12,
        size.height - 31, 0, 0, float(size.width), float(size.height),
        globals::mirror_texture->get_actual_width(),
        globals::mirror_texture->get_actual_height(),
        nullptr, 1, 1);

    render_context->release();
  }
}

void menu::on_entry_point() {

  // default font
  fgui::element_font title_font   = {"Verdana Bold", 11,
                                   fgui::external::font_flags::ANTIALIAS, true};
  fgui::element_font element_font = {
      "Verdana", 11, fgui::external::font_flags::ANTIALIAS, false};

  // initialize notifications
  REGISTER_NOTIFICATIONS(title_font);

  // initialize the main window
  ADD_WINDOW(vars::container["#window"], 50, 50,
             "Ruvi", 560, 450,
             fgui::external::key_code::KEY_HOME, title_font);

  ADD_WINDOW(vars::container["#mirror_window"], 50, 50, "Mirror Cam", 350, 200,
             fgui::external::key_code::KEY_F1, title_font);
  ADD_FUNCTION(vars::container["#mirror_window"],
               std::bind(mirror_cam, vars::container["#mirror_window"]));

  // initialize the input system
  REGISTER_CURSOR(fgui::cursor_type::ARROW, fgui::input_state::UNLOCKED);

  REGISTER_TAB(vars::tabs["#tab_panel"], 7, 1, element_font,
               vars::container["#window"], -1);

  ADD_TAB(vars::tabs["#tab_panel"], "Aimbot");
  {}

  ADD_TAB(vars::tabs["#tab_panel"], "Visuals");
  {

    ADD_GROUPBOX(vars::container["#player_esp_groupbox"], 15, (25 + 15),
                 "Player ESP", 260, 370, title_font, vars::container["#window"],
                 1, false, false, false) {
      ADD_CONTROLLER(vars::container["#player_esp_groupbox"],
                     vars::tabs["#tab_panel"]);

      ADD_CHECKBOX(vars::checkbox["#bounding_box"], 15, 15, "Bounding Box",
                   "vars.bounding_box", element_font,
                   vars::container["#player_esp_groupbox"], -1);
      ADD_CHECKBOX(vars::checkbox["#player_name"], 15, (15 + 25), "Player Name",
                   "vars.player_name", element_font,
                   vars::container["#player_esp_groupbox"], -1);
      ADD_CHECKBOX(vars::checkbox["#player_chams"], 15, (40 + 25),
                   "Player Chams", "vars.player_chams", element_font,
                   vars::container["#player_esp_groupbox"], -1);
    }

    ADD_GROUPBOX(vars::container["#effects_groupbox"], (260 + 15) + 10,
                 (25 + 15), "Effects", 260, 150, title_font,
                 vars::container["#window"], 1, true, false, false) {
      ADD_CONTROLLER(vars::container["#effects_groupbox"],
                     vars::tabs["#tab_panel"]);

      ADD_CHECKBOX(vars::checkbox["#nightmode"], 15, 15, "Nightmode",
                   "vars.night_mode", element_font,
                   vars::container["#effects_groupbox"], -1);
      ADD_CHECKBOX(vars::checkbox["#disable_post_process"], 15, (15 + 25),
                   "Disable Post Processing", "vars.disable_post_process",
                   element_font, vars::container["#effects_groupbox"], -1);
      ADD_CHECKBOX(vars::checkbox["#low_health_warning"], 15, (40 + 25),
                   "Low Health Warning", "vars.low_health_warning",
                   element_font, vars::container["#effects_groupbox"], -1);
      ADD_CHECKBOX(vars::checkbox["#disable_panorama_blur"], 15, (65 + 25),
                   "Disable Panorama Blur", "vars.disable_panorama_blur",
                   element_font, vars::container["#effects_groupbox"], -1);
      ADD_CHECKBOX(vars::checkbox["#disable_smoke_effect"], 15, (90 + 25),
                   "Disable Smoke Effect", "vars.disable_smoke_effect",
                   element_font, vars::container["#effects_groupbox"], -1);
      ADD_CHECKBOX(vars::checkbox["#disable_flashbang_effect"], 15, (115 + 25),
                   "Disable Flashbang Effect", "vars.disable_flashbang_effect",
                   element_font, vars::container["#effects_groupbox"], -1);
    }

    ADD_GROUPBOX(vars::container["#other_visuals_groupbox"], (260 + 15) + 10,
                 (25 + 15) + 150 + 10, "Other", 260, 150, title_font,
                 vars::container["#window"], 1, false, false, false) {
      ADD_CONTROLLER(vars::container["#other_visuals_groupbox"],
                     vars::tabs["#tab_panel"]);

      ADD_CHECKBOX(vars::checkbox["#engine_radar"], 15, 15, "Engine Radar",
                   "vars.engine_radar", element_font,
                   vars::container["#other_visuals_groupbox"], -1);
      ADD_CHECKBOX(vars::checkbox["#grenade_prediction"], 15, (15 + 25),
                   "Grenade Prediction", "vars.grenade_prediction",
                   element_font, vars::container["#other_visuals_groupbox"],
                   -1);
      ADD_CHECKBOX(vars::checkbox["#force_thirdperosn"], 15, (40 + 25),
                   "Force Thirdperson Camera", "vars.force_thirdperosn",
                   element_font, vars::container["#other_visuals_groupbox"],
                   -1);
    }
  }

  ADD_TAB(vars::tabs["#tab_panel"], "Misc");
  {

    ADD_GROUPBOX(vars::container["#miscellaneous_groupbox"], 15, (25 + 15),
                 "Misc", 260, 370, title_font, vars::container["#window"], 2,
                 false, false, false) {
      ADD_CONTROLLER(vars::container["#miscellaneous_groupbox"],
                     vars::tabs["#tab_panel"]);

      ADD_CHECKBOX(vars::checkbox["#rank_revealer"], 15, 15, "Rank Revealer",
                   "vars.rank_revealer", element_font,
                   vars::container["#miscellaneous_groupbox"], -1);
      ADD_CHECKBOX(vars::checkbox["#bunny_hop"], 15, (15 + 25), "Bunny Hop",
                   "vars.bunny_hop", element_font,
                   vars::container["#miscellaneous_groupbox"], -1);
      ADD_CHECKBOX(vars::checkbox["#auto_strafe"], 15, (40 + 25), "Auto Strafe",
                   "vars.auto_strafe", element_font,
                   vars::container["#miscellaneous_groupbox"], -1);
      ADD_CHECKBOX(vars::checkbox["#crouch_exploit"], 15, (65 + 25),
                   "Crouch Exploit", "vars.crouch_exploit", element_font,
                   vars::container["#miscellaneous_groupbox"], -1);
      ADD_CHECKBOX(vars::checkbox["#instant_bomb_plant"], 15, (90 + 25),
                   "Instant Bomb Plant", "vars.instant_bomb_plant",
                   element_font, vars::container["#miscellaneous_groupbox"],
                   -1);
      ADD_CHECKBOX(vars::checkbox["#thirdperson_while_spectating"], 15,
                   (115 + 25), "Thirdperson while Spectating",
                   "vars.thirdperson_while_spectating", element_font,
                   vars::container["#miscellaneous_groupbox"], -1);
    }
  }

  ADD_TAB(vars::tabs["#tab_panel"], "Colors");
  {}

  ADD_TAB(vars::tabs["#tab_panel"], "Settings");
  {}

  //
  // see https://github.com/iFloody/fgui/wiki for more info about the framework
  //
}