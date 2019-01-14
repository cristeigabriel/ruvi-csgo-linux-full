//
//  Ruvi - @ruvi-framework.git
//

#pragma once

// includes
#include <string>
#include <iostream>
#include "utils/color.hh"
#include "vector/vector.hh"
#include "valve/isurface.hh"

// enums
enum e_gradient_type {

	vertical = 1,
	horizontal
};

// structs
typedef struct s_rect {
	int left;
	int top;
	int right;
	int bottom;
} rect;

typedef struct s_point {
	int x;
	int y;
} point;

namespace fonts {

	extern n_vgui::h_font watermark;
	extern n_vgui::h_font menu;
};

namespace draw {
	void on_entry_point( );

	void clear( int x, int y, int w, int h, Color color );
	void gradient( int x, int y, int w, int h, size_t alpha1, size_t alpha2, bool horizontal, Color color );
	void color_gradient( int x, int y, int w, int h, Color color1, Color color2, int gradient_type = 1 );
	void outline( int x, int y, int w, int h, Color color );
	void line( int x, int y, int x2, int y2, Color color );
	void poly_line( int* x, int* y, int points, Color color );
	void polygon( int count, vertex_t* vertex, Color color );
	void circle( int x, int y, int radius, int segments, Color color );
	void filled_circle( int x, int y, int radius, int segments, Color color );
	void rounded_clear( int x, int y, int w, int h, int radius, Color color );
	void image( unsigned char* image, int x, int y, unsigned int w, unsigned int h, float scale = 1.0f );
	void text( int x, int y, Color color, unsigned int font, const wchar_t* text, ... );
	void text( int x, int y, Color color, unsigned int font, std::string text, ... );
	void pixel_clear( int x, int y, int w, int h, Color color );
	bool world_to_screen( vector &origin, vector &screen );
	rect get_viewport( );
	vector2d get_text_size( unsigned int font, std::string text, ... );
	void progress_circle(int x, int y, int size, float percentage, Color color);
	void multi_color_gradient(int x, int y, int w, int h, Color color1, Color color2, Color color3, Color color4);
};