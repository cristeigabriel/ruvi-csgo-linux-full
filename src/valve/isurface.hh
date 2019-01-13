//
//  Ruvi - @ruvi-framework.git
//

#pragma once

// includes
#include <math.h>
#include <functional>
#include "utils/color.hh"
#include "utils/memory.hh"
#include "utils/vector2d.hh"

/* namespaces */
namespace n_vgui {
	typedef unsigned long h_font;
	typedef unsigned int v_panel;
};

/* structs */
struct vertex_t {

	vector2d position;

	vector2d text_coord;

	vertex_t( ) {
	}

	vertex_t( const vector2d &pos, const vector2d &coord = vector2d( 0, 0 ) ) {
		position = pos;
		text_coord = coord;
	}

	void init( const vector2d &pos, const vector2d &coord = vector2d( 0, 0 ) ) {
		position = pos;
		text_coord = coord;
	}
};

// enums
enum e_font_flags {

	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

enum e_font_draw_type: int {
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,
	FONT_DRAW_TYPE_COUNT = 2
};

// prototypes
typedef unsigned long h_font;

class i_surface {
public:
	void draw_set_color( Color color ) {
		return memory::vfunc<14, void>( this, color.r( ), color.g( ), color.b( ), color.a( ) );
	}

	void draw_set_color( int red, int green, int blue, int alpha ) {
		return memory::vfunc<14, void>( this, red, green, blue, alpha );
	}

	void draw_filled_rect( int x, int y, int width, int height ) {
		return memory::vfunc<16, void>( this, x, y, width, height );
	}

	void draw_outlined_rect( int x, int y, int width, int height ) {
		return memory::vfunc<18, void>( this, x, y, width, height );
	}

	void draw_line( int x1, int y1, int x2, int y2 ) {
		return memory::vfunc<19, void>( this, x1, y1, x2, y2 );
	}

	void draw_poly_line( int* x, int* y, int points ) {
		return memory::vfunc<20, void>( this, x, y, points );
	}

	void draw_set_text_font( h_font font ) {
		return memory::vfunc<23, void>( this, font );
	}

	void draw_set_text_color( Color color ) {
		return memory::vfunc<24, void>( this, color.r( ), color.g( ), color.g( ), color.a( ) );
	}

	void draw_set_text_color( int red, int green, int blue, int alpha ) {
		return memory::vfunc<24, void>( this, red, green, blue, alpha );
	}

	void draw_set_text_pos( int x, int y ) {
		return memory::vfunc<26, void>( this, x, y );
	}

	void draw_print_text( const wchar_t* text, int length, int draw_type = FONT_DRAW_NONADDITIVE ) {
		return memory::vfunc<28, void>( this, text, length, draw_type );
	}

	void draw_set_texture_rgba( int texture_id, unsigned char const* colors, int width, int height ) {
		return memory::vfunc<37, void>( this, texture_id, colors, width, height );
	}

	void draw_set_texture( int texture_id ) {
		return memory::vfunc<38, void>( this, texture_id );
	}

	void draw_textured_rect( int x, int y, int width, int height ) {
		return memory::vfunc<41, void>( this, x, y, width, height );
	}

	bool is_texture_id_valid( int texture_id ) {
		return memory::vfunc<42, bool>( this, texture_id );
	}

	int create_new_texture_id( bool is_procedural ) {
		return memory::vfunc<43, int>( this, is_procedural );
	}

	void unlock_cursor( ) {
		return memory::vfunc<66, void>( this );
	}

	h_font create_font( ) {
		return memory::vfunc<71, h_font>( this );
	}

	bool set_font_glyph_set( h_font font, const char* font_name, int tall, int weight, int blur, int scanlines, int flags, int min_range = 0, int max_range = 0 ) {
		return memory::vfunc<72, bool>( this, font, font_name, tall, weight, blur, scanlines, flags, min_range, max_range );
	}

	void get_text_size( unsigned long long font, const wchar_t* text, int &wide, int &tall ) {
		return memory::vfunc<79, void>( this, font, text, std::ref( wide ), std::ref( tall ) );
	}

	void play_sound( const char* file_name ) {
		return memory::vfunc<82, void>( this, file_name );
	}

	void surface_get_cursor_pos( int &x, int &y ) {
		return memory::vfunc<100, void>( this, std::ref( x ), std::ref( y ) );
	}

	void draw_outlined_circle( int x, int y, int radius, int segments ) {
		return memory::vfunc<103, void>( this, x, y, radius, segments );
	}

	void draw_textured_polygon( int vertex_count, vertex_t* vertex, bool clip_vertices = true ) {
		return memory::vfunc<106, void>( this, vertex_count, vertex, clip_vertices );
	}

	void draw_filled_rect_fade( int x, int y, int w, int h, size_t alpha0, size_t alpha1, bool is_horizontal ) {
		return memory::vfunc<123, void>( this, x, y, w, h, alpha0, alpha1, is_horizontal );
	}
};
