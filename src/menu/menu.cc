//
//  ruvi base
//

// includes
#include "menu.hh"

#include "../core/interfaces/interfaces.hh"

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
             "Ruvi for Counter-Strike: Global Offensive", 560, 450,
             fgui::external::key_code::KEY_HOME, title_font);

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
      ADD_CHECKBOX(vars::checkbox["#player_chams"], 15, (40 + 25), "Player Chams",
                   "vars.player_chams", element_font,
                   vars::container["#player_esp_groupbox"], -1);
    }

    ADD_GROUPBOX(vars::container["#effects_groupbox"], (260 + 15) + 10,
                 (25 + 15), "Effects", 260, 150, title_font,
                 vars::container["#window"], 1, false, false, false) {
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