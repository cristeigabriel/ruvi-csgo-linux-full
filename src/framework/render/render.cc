//
//  Ruvi - @ruvi-framework.git
//

// includes
#include <vector>
#include <math.h>
#include "render.hh"
#include "interfaces/interfaces.hh"

// definitions
#define RAD2DEG( x ) ((float)(x) * (float)(180.f / (float)M_PI))
#define DEG2RAD( x ) ((float)(x) * (float)((float)M_PI / 180.f))

namespace fonts {

	n_vgui::h_font watermark;
	n_vgui::h_font menu;
};

auto draw::on_entry_point( ) -> void {

	fonts::watermark = csgo::vgui_surface->create_font();
	fonts::menu = csgo::vgui_surface->create_font();

	csgo::vgui_surface->set_font_glyph_set( fonts::watermark, "fs Tahoma 8px", 14, 0, 0, 0, FONTFLAG_NONE | FONTFLAG_DROPSHADOW );
	csgo::vgui_surface->set_font_glyph_set( fonts::menu, "fs Tahoma 8px", 14, 0, 0, 0, FONTFLAG_NONE | FONTFLAG_DROPSHADOW );
}

void draw::clear( int x, int y, int w, int h, Color color ) {

	csgo::vgui_surface->draw_set_color( color );
	csgo::vgui_surface->draw_filled_rect( x, y, x + w, y + h );
}

void draw::gradient( int x, int y, int w, int h, size_t alpha1, size_t alpha2, bool horizontal, Color color ) {

	csgo::vgui_surface->draw_set_color( color );
	csgo::vgui_surface->draw_filled_rect_fade( x, y, x + w, y + h, alpha1, alpha2, horizontal );
}

void draw::color_gradient( int x, int y, int w, int h, Color color1, Color color2, int gradient_type ) {

	if ( gradient_type == e_gradient_type::vertical ) {

		draw::clear( x, y, w, h, color1 );

		unsigned char first = color2.r( );
		unsigned char second = color2.g( );
		unsigned char third = color2.b( );

		for ( int i = 0; i < h; i++ ) {

			float fi = i, fh = h;
			float a = fi / fh;
			unsigned int ia = a * 255;
			draw::clear( x, y + i, w, 1, Color( first, second, third, ia ) );
		}
	}

	else if ( gradient_type == e_gradient_type::horizontal ) {

		draw::clear( x, y, w, h, color1 );

		unsigned char first = color2.r( );
		unsigned char second = color2.g( );
		unsigned char third = color2.b( );

		for ( int i = 0; i < w; i++ ) {
			float fi = i, fw = w;
			float a = fi / fw;
			unsigned int ia = a * 255;
			draw::clear( x + i, y, 1, h, Color( first, second, third, ia ) );
		}
	}
}

void draw::outline( int x, int y, int w, int h, Color color ) {

	csgo::vgui_surface->draw_set_color( color );
	csgo::vgui_surface->draw_outlined_rect( x, y, x + w, y + h );
}

void draw::line( int x, int y, int x2, int y2, Color color ) {

	csgo::vgui_surface->draw_set_color( color );
	csgo::vgui_surface->draw_line( x, y, x2, y2 );
}

void draw::text( int x, int y, Color color, unsigned int font, const wchar_t* text, ... ) {

	csgo::vgui_surface->draw_set_text_font( font );
	csgo::vgui_surface->draw_set_text_color( color.r( ), color.g( ), color.b( ), color.a( ) );
	csgo::vgui_surface->draw_set_text_pos( x, y );
	csgo::vgui_surface->draw_print_text( text, wcslen( text ) );
}

void draw::text( int x, int y, Color color, unsigned int font, std::string text, ... ) {

	std::wstring wtext = std::wstring( text.begin( ), text.end( ) );

	csgo::vgui_surface->draw_set_text_pos( x, y );
	csgo::vgui_surface->draw_set_text_font( font );
	csgo::vgui_surface->draw_set_text_color( color.r( ), color.g( ), color.b( ), color.a( ) );
	csgo::vgui_surface->draw_print_text( wtext.c_str( ), wcslen( wtext.c_str( ) ) );
}

vector2d draw::get_text_size( unsigned int font, std::string text, ... ) {

	int x, y;

	csgo::vgui_surface->get_text_size( font, std::wstring( text.begin( ), text.end( ) ).c_str( ), x, y );

	return vector2d( x, y );
}

rect draw::get_viewport( ) {

	s_rect viewport = { 0, 0, 0, 0 };

	// get the screen size
	int w, h;
	csgo::engine_client->get_screen_size( w, h );

	// apply the screen size to the viewport
	viewport.right = w;
	viewport.bottom = h;

	return viewport;
}

void draw::polygon( int count, vertex_t* vertex, Color color ) {

	static int texture = csgo::vgui_surface->create_new_texture_id( true );
	unsigned char buffer[4] = { 255, 255, 255, 255 };

	csgo::vgui_surface->draw_set_texture_rgba( texture, buffer, 1, 1 );
	csgo::vgui_surface->draw_set_color( color );
	csgo::vgui_surface->draw_set_texture( texture );

	csgo::vgui_surface->draw_textured_polygon( count, vertex );
}

void draw::circle( int x, int y, int radius, int segments, Color color ) {

	csgo::vgui_surface->draw_set_color( color );
	csgo::vgui_surface->draw_outlined_circle( x, y, radius, segments );
}

void draw::filled_circle( int x, int y, int radius, int segments, Color color ) {

	std::vector<vertex_t> vertices;
	float step = ( float )M_PI * 2.0f / segments;

	for ( float a = 0; a < ( M_PI * 2.0f ); a += step )
		vertices.push_back( vertex_t( vector2d( radius * cosf( a ) + x, radius * sinf( a ) + y ) ) );

	draw::polygon( ( int )segments, vertices.data( ), color );
}

void draw::rounded_clear( int x, int y, int w, int h, int radius, Color color ) {

	vertex_t round[64];

	for ( int i = 0; i < 4; i++ ) {

		int _x = x + ( ( i < 2 ) ? ( w - radius ) : radius );
		int _y = y + ( ( i % 3 ) ? ( h - radius ) : radius );

		float a = 90.f * i;

		for ( int j = 0; j < 16; j++ ) {

			float _a = DEG2RAD( a + j * 6.f );

			round[ ( i * 16 ) + j ] = vertex_t( vector2d( _x + radius * sin( _a ), _y - radius * cos( _a ) ) );
		}
	}

	draw::polygon( 64, round, color );
}

void draw::alpha_background(int x, int y, int w, int h) {

	for (int py = 0; py < h / 5; py++) {

		for (int px = 0; px < w / 5; px++) {

			int pixel_nr = roundf(px);
			int line_nr = roundf(py);
			bool start_with_light = line_nr % 2;
			bool is_brick_light = start_with_light ? pixel_nr % 2 : pixel_nr % 2 == 0;

			Color new_color = is_brick_light ? Color(60, 60, 60) : Color(40, 40, 40);

			draw::clear(x + px * 5, y + py * 5, 5, 5, new_color);
		}
	}
};