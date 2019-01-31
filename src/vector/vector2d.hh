//
//  Ruvi - @ruvi-framework.git
//

#pragma once

// includes
#include <math.h>
#include <float.h>
#include <assert.h>

// prototypes
typedef float vec_t;
typedef float vec2_t[2];
typedef float vec3_t[3];

class vector2d {
public:
	float x, y;

	vector2d( void );
	vector2d( vec_t X, vec_t Y );
	vector2d( const float* pFloat );
	bool is_valid( ) const;
	float operator[]( int i ) const;
	float &operator[]( int i );
	bool operator==( const vector2d &v ) const;
	bool operator!=( const vector2d &v ) const;
	vector2d &operator+=( const vector2d &v );
	vector2d &operator-=( const vector2d &v );
	vector2d &operator*=( const vector2d &v );
	vector2d &operator*=( float s );
	vector2d &operator/=( const vector2d &v );
	vector2d &operator/=( float s );
};

inline vec_t bits_to_float( unsigned long i ) {
	return *reinterpret_cast<vec_t*>(&i);
}

inline vector2d::vector2d( vec_t X, vec_t Y ) {
	x = X;
	y = Y;
	assert( this->is_valid( ) );
}

inline vector2d::vector2d( const float* p_float ) {
	assert( p_float );
	x = p_float[ 0 ];
	y = p_float[ 1 ];
	assert( this->is_valid( ) );
}

inline bool vector2d::is_valid( ) const {
	return isfinite( x ) && isfinite( y );
}
