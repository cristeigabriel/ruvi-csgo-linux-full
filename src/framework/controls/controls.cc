//
//  Ruvi - @ruvi-framework.git
//

// includes
#include "controls.hh"
#include "utils/rendering.hh"

void ruvi::groupbox(int x, int y, int width, int height, std::string name) {

    auto title_size = draw::get_text_size(fonts::menu, name);

    draw::line( x - 1, y - 1, ( x - 1 ) + 14, y + 2, Color( 25, 25, 25 ) );
    draw::line( x, y, x + 10, y, Color( 60, 60, 60 ) );
    draw::line( ( x - 1 ) + 15 + title_size.x + 5, y - 1, ( x - 1 ) + width + 2, y - 1, Color( 25, 25, 25 ) );
    draw::line( x + 15 + title_size.x + 5, y, x + width, y, Color( 60, 60, 60 ) );
    draw::line( x - 1, y - 1, x - 1, ( y - 1 ) + height + 2, Color( 25, 25, 25 ) );
    draw::line( x, y, x, y + height, Color( 50, 50, 50 ) );
    draw::line( ( x - 1 ), ( y + 1 ) + height, ( x - 1 ) + width + 2, ( y + 1 ) + height, Color( 25, 25, 25 ) );
    draw::line( x, y + height, x + width, y + height, Color( 60, 60, 60 ) );
    draw::line( ( x - 1 ) + width + 2, y + 1, ( x - 1 ) + width + 2, ( y + 1 ) + height, Color( 25, 25, 25 ) );
    draw::line( x + width, y, x + width, y + height, Color( 60, 60, 60 ) );
    draw::clear( x + 1, y + 1, width - 1, height - 1, Color( 15, 15, 15 ) );
    draw::text( x + 15, y - 10 + ( title_size.y / 2 ), Color( 200, 200, 200 ), fonts::menu, name );
}

bool ruvi::checkbox(std::string name, bool *var, int x, int y) {
	auto title_size = draw::get_text_size(fonts::menu, name);
	auto box_size = Vector2D(CHECKBOX_BOX_X, CHECKBOX_BOX_Y);
	auto clickiable_area = rect{ x, y, x + (int)box_size.x + (int)title_size.x + CHECKBOX_TEXT_SPACING, y + (int)box_size.y };
	bool is_hovered = input::is_mouse_in_region(clickiable_area.left, clickiable_area.top, clickiable_area.right - clickiable_area.left, clickiable_area.bottom - clickiable_area.top);

	draw::clear(x, y, box_size.x, box_size.y, Color(100, 100, 100, 100));
	if (*var) draw::clear(x + 1, y + 1, box_size.x - 2, box_size.y - 2, Color(255, 0, 0, 255)); // assign a checkbox color to this later
	draw::text(x + box_size.x + CHECKBOX_TEXT_SPACING, y + box_size.y / 2 - title_size.y / 2, Color(200, 200, 200, 255), fonts::menu, name);

	if (is_hovered && input::get_key_press(ButtonCode_t::MOUSE_LEFT) && input::get_can_click()) {
		*var = !*var;	
		input::set_can_click(false);
	}

	return *var;
}
