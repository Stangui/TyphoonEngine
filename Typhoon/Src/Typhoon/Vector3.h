#pragma once

namespace TyphoonEngine
{

	template<typename T>
	struct Vector3
	{
		T x, y, z;

		Vector3() : x( 0 ), y( 0 ), z( 0 )
		{}

		Vector3( const T x, const T y, const T z )
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3( const Vector3<T>& v )
		{
			this->x = vec.x;
			this->y = vec.y;
			this->z = vec.z;
		}

		Vector3 &operator=( const Vector3<T> &v )
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			return *this;
		}
		
		bool operator==( const Vector3<T> &v ) const
		{
			return x == v.x && y == v.y && z == v.z;
		}

		bool operator!=( const Vector3<T> &v ) const
		{
			return !( *this == v );
		}

		Vector3 operator+( const Vector3<T> &v ) const
		{
			return vector2D<T>( x + v.x, y + v.y );
		}

		Vector3 operator-( const Vector3<T> &v ) const
		{
			return Vector3<T>( x - v.x, y - v.y );
		}

		//scaling
		Vector3 operator*( T v ) const
		{
			return Vector3<T>( x*v, y*v );
		}

		//scaling
		Vector3 operator/( T v ) const
		{
			return Vector3<T>( x / v, y / v, z / v );
		}

		//component-wise scaling
		Vector3 operator*( const Vector3<T> &v ) const
		{
			return Vector3<T>( x*v.x, y*v.y, z*v.z );
		}

		//component-wise scaling
		Vector3 operator/( const Vector3<T> &v ) const
		{
			return Vector3<T>( x / v.x, y / v.y, z / v.z );
		}

		Vector3 operator-() const
		{
			return ( Vector3( -x, -y, -z ) );
		}

		Vector3 operator+() const
		{
			return *this;
		}

		static T dotProduct( const Vector3<T> &a, const Vector3<T> &b )
		{
			return a.x*b.x + a.y*b.y + a.z*b.z;
		}

		T lengthSquared() const
		{
			return x * x + y * y + z * z;
		}

		T length() const
		{
			return (T)sqrt( lengthSquared() );
		}

		Vector3 normalize() const
		{
			return *this * ( 1 / length() );
		}

	};

	typedef Vector3<int> Vec3i;
	typedef Vector3<float> Vec3f;
	typedef Vector3<double> Vec3d;

}
