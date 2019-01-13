//
//  Ruvi - @ruvi-framework.git
//

#pragma once

// includes
#include <algorithm>

// functions
class Color {
public:

	void set_color( int _r, int _g, int _b, int _a = 255 ) {

		_color[ 0 ] = ( unsigned char )_r;
		_color[ 1 ] = ( unsigned char )_g;
		_color[ 2 ] = ( unsigned char )_b;
		_color[ 3 ] = ( unsigned char )_a;
	}

	void get_color( int &_r, int &_g, int &_b, int &_a ) const {

		_r = _color[ 0 ];
		_g = _color[ 1 ];
		_b = _color[ 2 ];
		_a = _color[ 3 ];
	}

	Color( ) {
		*( ( int* )this ) = 0;
	}

	Color( int color32 ) {
		*( ( int* )this ) = color32;
	}

	Color( int _r, int _g, int _b ) {
		set_color( _r, _g, _b, 255 );
	}

	Color( int _r, int _g, int _b, int _a ) {
		set_color( _r, _g, _b, _a );
	}

	void set_raw_color( int color32 ) {
		*( ( int* )this ) = color32;
	}

	int get_raw_color( ) const {
		return *( ( int* )this );
	}

	inline int r( ) const {
		return _color[ 0 ];
	}

	inline int g( ) const {
		return _color[ 1 ];
	}

	inline int b( ) const {
		return _color[ 2 ];
	}

	inline int a( ) const {
		return _color[ 3 ];
	}

	inline float red_base( ) const {
		return _color[ 0 ] / 255.0f;
	}

	inline float green_base( ) const {
		return _color[ 1 ] / 255.0f;
	}

	inline float blue_base( ) const {
		return _color[ 2 ] / 255.0f;
	}

	inline float alpha_base( ) const {
		return _color[ 3 ] / 255.0f;
	}

	unsigned char &operator[]( int index ) {
		return _color[ index ];
	}

	const unsigned char &operator[]( int index ) const {
		return _color[ index ];
	}

	bool operator==( const Color &rhs ) const {
		return ( *( ( int* )this ) == *( ( int* )&rhs ) );
	}

	bool operator!=( const Color &rhs ) const {
		return !( operator==( rhs ) );
	}

	Color &operator=( const Color &rhs ) {
		set_raw_color( rhs.get_raw_color( ) );
		return *this;
	}

	static Color hsb_to_rgb(float hue, float saturation, float brightness, int alpha = 255) {

		hue = std::clamp(hue, 0.f, 1.f);
		saturation = std::clamp(saturation, 0.f, 1.f);
		brightness = std::clamp(brightness, 0.f, 1.f);

		float h = (hue == 1.f) ? 0.f : (hue * 6.f);
		float f = h - static_cast<int>(h);
		float p = brightness * (1.f - saturation);
		float q = brightness * (1.f - saturation * f);
		float t = brightness * (1.f - (saturation * (1.f - f)));

		if (h < 1.f)
			return Color(brightness * 255, t * 255, p * 255, alpha);

		else if (h < 2.f)
			return Color(q * 255, brightness * 255, p * 255, alpha);

		else if (h < 3.f)
			return Color(p * 255, brightness * 255, t * 255, alpha);

		else if (h < 4)
			return Color(p * 255, q * 255, brightness * 255, alpha);

		else if (h < 5)
			return Color(t * 255, p * 255, brightness * 255, alpha);

		else
			return Color(brightness * 255, p * 255, q * 255, alpha);

	}

	unsigned char _color[4];
};
