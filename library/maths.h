
#pragma once

#include <cmath>

#ifndef M_PI
#define M_PI						3.141592654f
#endif

#define M_DEGRADCONV		57.2957795f

class Maths
{
	public:
		//static float Pi() { return M_PI; };

		static int Min( int a, int b )
		{
			return ( a <= b ? a : b );
		};
		static float Min( float a, float b )
		{
			return ( a <= b ? a : b );
		};

		static int Max( int a, int b )
		{
			return ( a >= b ? a : b );
		};
		static float Max( float a, float b )
		{
			return ( a >= b ? a : b );
		};

		static int Abs( int a )
		{
			return ( a < 0 ? a * -1 : a );
		};
		static float Abs( float a )
		{
			return ( a < 0.0 ? a * -1 : a );
		};
};
