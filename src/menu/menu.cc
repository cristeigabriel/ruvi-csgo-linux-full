//
//  ruvi base
//

// includes
#include "menu.hh"

void menu::on_entry_point() {

  // default fonts
  fgui::element_font title_font = { "Verdana Bold", 11, fgui::external::font_flags::ANTIALIAS | fgui::external::font_flags::SHADOW, true };
  fgui::element_font element_font = { "Verdana", 11, fgui::external::font_flags::ANTIALIAS, false };

  // initialize notifications
  REGISTER_NOTIFICATIONS(title_font);

  // initialize the main window
  ADD_WINDOW(vars::container["#window"], 50, 50, "Ruvi", 575, 450, fgui::external::key_code::KEY_HOME, title_font);

  // initialize the input system
  REGISTER_CURSOR(fgui::cursor_type::ARROW, fgui::input_state::UNLOCKED);

  REGISTER_TAB(vars::tabs["#panel"], 7, 1, element_font, vars::container["#window"], -1);

  ADD_TAB(vars::tabs["#panel"], "Aimbot"); {

    ADD_GROUPBOX(vars::container["#groupbox"], 15, (25 + 15), "Groupbox", 280, 370, element_font, vars::container["#window"], 0, false, false, false) {
    ADD_CONTROLLER(vars::container["#groupbox"], vars::tabs["#panel"]);

    }
  }

  ADD_TAB(vars::tabs["#panel"], "Visuals"); {
  }

  ADD_TAB(vars::tabs["#panel"], "Misc"); {
  }

  ADD_TAB(vars::tabs["#panel"], "Colors"); {
  }

  ADD_TAB(vars::tabs["#panel"], "Settings"); {
  }

  //
  // see https://github.com/iFloody/fgui/wiki for more info about the framework
  //
}
