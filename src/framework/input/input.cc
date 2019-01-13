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

	// cursor position stuff
	point last_cursor_pos;// this is used for the cursor delta
	csgo::vgui_surface->surface_get_cursor_pos( id.cursor.x, id.cursor.y ); //gets current mouse pos
	// the point struct does not have a - operator and I am to lazy to add one rn, so it stays written like aids VVV
	id.cursor_delta.x = id.cursor.x - last_cursor_pos.x; // sets the delta for x
	id.cursor_delta.y = id.cursor.y - last_cursor_pos.y  // sets the delta for y
	last_cursor_pos = id.cursor; //sets this value last
}
point get_cursor_delta() {
	
	return id.cursor_delta;
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
