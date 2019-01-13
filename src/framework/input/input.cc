//
//  Ruvi - @ruvi-framework.git
//

// includes
#include "input.hh"

// declarations
input_data id;

void input::on_paint( ) {

	std::copy( id.keys, id.keys + 255, id.old_keys );

	// handler
	for ( int x = 0; x < 255; x++ )
		id.keys[ x ] = csgo::input_system->is_button_down( e_button_code( x ) );

	// get the cursor position
	csgo::vgui_surface->surface_get_cursor_pos( id.cursor.x, id.cursor.y );
	
	// makes us able to click again, after we let go of mouse 1
	if (!get_key_press(ButtonCode_t::MOUSE_LEFT))
		id.can_click = true;
}

bool input::can_click() { // if mouse1 should be registered by the window

	return id.can_click;
}

bool input::get_key_state( e_button_code key ) { // if the key is being held

	return id.keys[ key ];
}

bool input::get_key_press( e_button_code key ) { // if the key is pressed (1 time check)

	if ( id.keys[ key ] == true && id.old_keys[ key ] == false )
		return true;
	else
		return false;
}

bool input::in_bounds( int x, int y, int x2, int y2, int width, int height ) {
	return ( x > x2 && y > y2 && x < x2 + width && y < y2 + height );
}

bool input::is_mouse_in_region( int x, int y, int width, int height ) {

	int m_cur_x, m_cur_y;
	csgo::vgui_surface->surface_get_cursor_pos( m_cur_x, m_cur_y );

	return input::in_bounds( m_cur_x, m_cur_y, x, y, width, height );
}
