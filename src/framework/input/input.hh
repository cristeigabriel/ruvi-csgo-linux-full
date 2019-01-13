//
//  Ruvi - @ruvi-framework.git
//

// includes
#include "utils/rendering.hh"
#include "interfaces/interfaces.hh"

// structs
struct input_data {

	bool keys[256];
	bool pressed_keys[256];
	bool old_keys[256];
	point cursor;
	bool can_click;
};

namespace input {

	void on_paint();

	bool get_key_state(e_button_code key);
	bool get_key_press(e_button_code key);
	bool in_bounds(int x, int y, int x2, int y2, int width, int height);
	bool is_mouse_in_region(int x, int y, int width, int height);
}
