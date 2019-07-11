#pragma once

namespace TyphoonEngine
{

	template <typename T>
	class Vector2
	{

	public:

		T x, y;

		Vector2() : x( 0 ), y( 0 )
		{
		}

		Vector2( T x, T y )
		{
			this->x = x;
			this->y = y;
		}

		Vector2( const Vector2<T> &v )
		{
			this->x = v.x;
			this->y = v.y;
		}

		Vector2 &operator=( const Vector2<T> &v )
		{
			this->x = v.x;
			this->y = v.y;
			return *this;
		}
		T& operator[]( int i ) const
		{
			return i == 0 ? x : y;
		}

		T& operator()( int i ) const
		{
			return ( *this )[i];
		}
		
		Vector2<T> operator()() const
		{
			return normalize();
		}

		bool operator==( const Vector2<T> &v ) const
		{
			return x == v.x && y == v.y;
		}

		bool operator!=( const Vector2<T> &v ) const
		{
			return !( *this == v );
		}

		Vector2 operator+( const Vector2<T> &v ) const
		{
			return Vector2<T>( x + v.x, y + v.y );
		}

		Vector2 operator-( const Vector2<T> &v ) const
		{
			return Vector2<T>( x - v.x, y - v.y );
		}

		//scaling
		Vector2 operator*( T v ) const
		{
			return Vector2<T>( x*v, y*v );
		}

		//scaling
		Vector2 operator/( T v ) const
		{
			return Vector2<T>( x / v, y / v );
		}

		//component-wise scaling
		Vector2 operator*( const Vector2<T> &v ) const
		{
			return Vector2<T>( x*v.x, y*v.y );
		}

		//component-wise scaling
		Vector2 operator/( const Vector2<T> &v ) const
		{
			return Vector2<T>( x / v.x, y / v.y );
		}

		Vector2 operator-() const
		{
			return ( Vector2( -x, -y ) );
		}

		Vector2 operator+() const
		{
			return *this;
		}

		T lengthSquared() const
		{
			return x * x + y * y;
		}

		T length() const
		{
			return (T)sqrt( length2() );
		}

		Vector2 normalize() const
		{
			return *this * ( 1 / length() );
		}

		Vector2 rotate( T angle ) const
		{
			T s = sin( angle ), c = cos( angle );
			return Vector2( x * c - y * s, y * c + x * s );
		}

		static T dotProduct( const Vector2<T> &a, const Vector2<T> &b )
		{
			return a.x*b.x + a.y*b.y;
		}

	};

	typedef Vector2<int> Vec2i;
	typedef Vector2<float> Vec2f;
	typedef Vector2<double> Vec2d;
}