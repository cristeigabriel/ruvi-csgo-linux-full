//
//  Ruvi - @ruvi-framework.git
//

#pragma once

// includes
#include <math.h>
#include <stdlib.h>
#include <limits>

// declarations
class vector;
class matrix3x4_t;

// prototypes
typedef float vec_t;
typedef float vec2_t[2];
typedef float vec3_t[3];

// definitions
#define Assert( _exp ) ((void)0)

typedef class vector {
public:
	vec_t x, y, z;

	vector( );
	vector( const float* clr );
	vector( float X, float Y, float Z );
	vector &operator=( const vector &v_other );
	void init( float ix, float iy, float iz );
	float dist_to(const vector& vec) const;
	inline float operator[]( int i ) const;
	inline void normalize( );
	inline float length_sqr( );
	inline float length( );
	inline float dot( const vector &other ) const;
	inline void clamp_angles( );
	inline bool is_zero( );
	inline vec_t length_2d( ) const;
	float &operator[]( int i ) {return ( ( float* )this )[ i ];}
	vector normalized( ) const {

		vector res = *this;
		float l = res.length( );

		if ( l != 0.0f )
			res /= l;
		else
			res.x = res.y = res.z = 0.0f;

		return res;
	}

	void normalize_in_place( ) {
		*this = normalized( );
	}

public:
	inline operator bool( ) const;
	inline bool operator!( ) const;
	inline vector operator-( );
	inline bool operator==( const vector &v );
	inline bool operator==( const vector &v ) const;
	inline bool operator!=( const vector &v );
	inline vector &operator-=( const vector &v );
	inline vector operator-( const vector &v ) const;
	inline vector operator+( const vector &v ) const;
	inline vector operator*( const float n );
	inline vector operator/( const float n );
	inline vector operator/( const vector &v );
	inline vector &operator+=( float fl );
	inline vector &operator+=( const vector &v );
	inline vector &operator/=( float fl );
	inline vector &operator-=( float fl );
	inline vector &operator*=( const vector &v );
	inline vector &operator*=( float s );
} q_angle;


inline vector::vector( ) {
	x = 0.f;
	y = 0.f;
	z = 0.f;
}

inline vector::vector( const float* clr ) {
	x = clr[ 0 ];
	y = clr[ 1 ];
	z = clr[ 2 ];
}

inline vector::vector( float X, float Y, float Z ) {
	x = X;
	y = Y;
	z = Z;
}

inline vector &vector::operator=( const vector &v_other ) {
	x = v_other.x;
	y = v_other.y;
	z = v_other.z;
	return *this;
}

inline void vector::init( float ix, float iy, float iz ) {
	x = ix;
	y = iy;
	z = iz;
}

inline float vector::operator[]( int i ) const {

	if ( i == 0 ) {
		return x;
	}

	if ( i == 1 ) {
		return y;
	}

	return z;
};

inline void vector::normalize( ) {

	float length = length_sqr( );

	if ( length ) {
		x = x / length;
		y = y / length;
		z = z / length;
	}
	else {
		x = y = 0.0f;
	}
	z = 1.0f;
}

inline float vector::dist_to(const vector& vec) const {
	return (*this - vec).length();
}

inline float vector::length_sqr( ) {
	return ( x * x + y * y + z * z );
}

inline float vector_length(const vector &v) {
	return (vec_t)sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline vec_t vector_normalize(vector& v) {

	vec_t l = v.length();

	if (l != 0.0f) {
		v /= l;
	}
	else {
		v.x = v.y = 0.0f; v.z = 1.0f;
	}

	return l;
}

inline vec_t vector::length_2d( ) const {
	return ( vec_t )::sqrtf( x * x + y * y );
}

inline float vector::length( ) {
	return ( float )sqrt( length_sqr( ) );
}

inline vec_t dot_product( const vector &a, const vector &b ) {
	return ( a.x * b.x + a.y * b.y + a.z * b.z );
}

inline float vector::dot( const vector &other ) const {
	return dot_product( *this, other );
}

inline vector &vector::operator+=( const vector &v ) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

inline void vector_add( const vector &a, const vector &b, vector &c ) {

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

inline void vector_subtract( const vector &a, const vector &b, vector &c ) {
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

inline void vector::clamp_angles( ) {

	if ( this->x < -89.0f )
		this->x = -89.0f;

	if ( this->x > 89.0f )
		this->x = 89.0f;

	while ( this->y < -180.0f )
		this->y += 360.0f;

	while ( this->y > 180.0f )
		this->y -= 360.0f;

	this->z = 0.0f;
}

inline bool vector::is_zero( ) {
	return ( x < 0.01f && x > -0.01f && y < 0.01f && y > -0.01f );
}

inline bool vector::operator!( ) const {
	return ( !x && !y && !z );
}

inline vector vector::operator-( ) {
	return vector( -x, -y, -z );
}

inline bool vector::operator==( const vector &v ) {
	return ( x == v.x ) && ( y == v.y ) && ( z == v.z );
}

inline bool vector::operator==( const vector &v ) const {
	return ( x == v.x ) && ( y == v.y ) && ( z == v.z );
}

inline bool vector::operator!=( const vector &v ) {
	return ( x != v.x ) || ( y != v.y ) || ( z != v.z );
}

inline vector &vector::operator*=( float fl ) {
	x *= fl;
	y *= fl;
	z *= fl;
	return *this;
}

inline vector &vector::operator*=( const vector &v ) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

inline vector &vector::operator/=( float fl ) {
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	return *this;
}

inline vector &vector::operator+=( float fl ) {
	x += fl;
	y += fl;
	z += fl;
	return *this;
}


inline vector &vector::operator-=( const vector &v ) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

inline vector &vector::operator-=( float fl ) {
	x -= fl;
	y -= fl;
	z -= fl;
	return *this;
}

inline vector vector::operator-( const vector &v ) const {
	return vector( x - v.x, y - v.y, z - v.z );
}

inline vector vector::operator+( const vector &v ) const {
	return vector( x + v.x, y + v.y, z + v.z );
}

inline vector vector::operator*( const float n ) {
	return vector( x * n, y * n, z * n );
}

inline vector vector::operator/( const float n ) {
	return vector( x / n, y / n, z / n );
}

inline vector vector::operator/( const vector &v ) {
	return vector( x / v.x, y / v.y, z / v.z );
}

class vector_aligned: public vector {
public:

	vector_aligned( ) {
		x = y = z = 0.0f;
	}

	vector_aligned( const vector &v ) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	float w;
};

/* structs */
class matrix3x4_t {
public:
	matrix3x4_t( ) {
	}

	matrix3x4_t( float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23 ) {
		m_flMatVal[ 0 ][ 0 ] = m00;
		m_flMatVal[ 0 ][ 1 ] = m01;
		m_flMatVal[ 0 ][ 2 ] = m02;
		m_flMatVal[ 0 ][ 3 ] = m03;
		m_flMatVal[ 1 ][ 0 ] = m10;
		m_flMatVal[ 1 ][ 1 ] = m11;
		m_flMatVal[ 1 ][ 2 ] = m12;
		m_flMatVal[ 1 ][ 3 ] = m13;
		m_flMatVal[ 2 ][ 0 ] = m20;
		m_flMatVal[ 2 ][ 1 ] = m21;
		m_flMatVal[ 2 ][ 2 ] = m22;
		m_flMatVal[ 2 ][ 3 ] = m23;
	}

	void Init( const vector &xAxis, const vector &yAxis, const vector &zAxis, const vector &vecOrigin ) {
		m_flMatVal[ 0 ][ 0 ] = xAxis.x;
		m_flMatVal[ 0 ][ 1 ] = yAxis.x;
		m_flMatVal[ 0 ][ 2 ] = zAxis.x;
		m_flMatVal[ 0 ][ 3 ] = vecOrigin.x;
		m_flMatVal[ 1 ][ 0 ] = xAxis.y;
		m_flMatVal[ 1 ][ 1 ] = yAxis.y;
		m_flMatVal[ 1 ][ 2 ] = zAxis.y;
		m_flMatVal[ 1 ][ 3 ] = vecOrigin.y;
		m_flMatVal[ 2 ][ 0 ] = xAxis.z;
		m_flMatVal[ 2 ][ 1 ] = yAxis.z;
		m_flMatVal[ 2 ][ 2 ] = zAxis.z;
		m_flMatVal[ 2 ][ 3 ] = vecOrigin.z;
	}

	matrix3x4_t( const vector &xAxis, const vector &yAxis, const vector &zAxis, const vector &vecOrigin ) {
		Init( xAxis, yAxis, zAxis, vecOrigin );
	}

	float* operator[]( int i ) {
		return m_flMatVal[ i ];
	}

	const float* operator[]( int i ) const {
		return m_flMatVal[ i ];
	}

	float* Base( ) {
		return &m_flMatVal[ 0 ][ 0 ];
	}

	const float* Base( ) const {
		return &m_flMatVal[ 0 ][ 0 ];
	}

	float m_flMatVal[3][4];
};
