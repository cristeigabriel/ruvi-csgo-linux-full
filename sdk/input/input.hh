//
//  ruvi base
//

#pragma once

// includes
#include <algorithm>
#include <array>

// framework includes
#include <FGUI/dependencies/aliases.hh>
#include <FGUI/dependencies/definitions.hh>

namespace input {

void on_entry_point();

fgui::state get_key_state(const fgui::key &key);
fgui::point get_mouse_position();
fgui::delta get_scroll_delta();
} // namespace input