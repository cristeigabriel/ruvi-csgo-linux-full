//
//  ruvi base
//

// includes
#include "input.hh"
#include "core/interfaces/interfaces.hh"

void input::on_entry_point() {

  // initialize the input system
  fgui::input.get_key_state      = input::get_key_state;
  fgui::input.get_scroll_delta   = input::get_scroll_delta;
  fgui::input.get_mouse_position = input::get_mouse_position;
}

fgui::state input::get_key_state(const fgui::key &key) {

  return csgo::input_system->is_button_down(key);
}

fgui::delta input::get_scroll_delta() {

  return csgo::input_system->get_analog_delta(analog_code_t::MOUSE_WHEEL);
}

fgui::point input::get_mouse_position() {

  static fgui::point temporary_point = {0, 0};

  // get cursor position
  csgo::vgui_surface->surface_get_cursor_pos(temporary_point.x,
                                             temporary_point.y);

  return temporary_point;
}