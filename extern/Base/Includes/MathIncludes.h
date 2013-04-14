// *****************************************************************************
//  MathIncludes   version:  1.0   Ankur Sheel  date: 2013/01/24
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef MathIncludes_h__
#define MathIncludes_h__

namespace Base
{
	const int     MaxInt    = (std::numeric_limits<int>::max)();
	const int     MinInt    = (std::numeric_limits<int>::min)();
	const double  MaxDouble = (std::numeric_limits<double>::max)();
	const double  MinDouble = (std::numeric_limits<double>::min)();
	const double  EpsilonDouble = (std::numeric_limits<double>::epsilon)();
	const float   MaxFloat  = (std::numeric_limits<float>::max)();
	const float   MinFloat  = (std::numeric_limits<float>::min)();
	const float   EpsilonFloat = (std::numeric_limits<float>::epsilon)();

	const float   Pi        = 3.14159f;
	const float   TwoPi     = Pi * 2;
	const float   HalfPi    = Pi / 2;
	const float   QuarterPi = Pi / 4;

	inline bool isEqual(const float a, const float b)
	{
		if (fabs(a-b) < EpsilonFloat)
		{
			return true;
		}

		return false;
	}

	inline float DegtoRad(const float x)
	{
		return (x * Pi /180);
	}

	inline float RadtoDeg(const float x)
	{
		return (x * 180 /Pi);
	}

	inline float ClampToTwoPi(const float x)
	{
		float val = fmod(x, TwoPi);
		if (val < 0)
		{
			val = TwoPi + val;
		}
		return val;
	}

	inline int roundUp(int numToRound, int multiple)  
	{  
		if(multiple == 0)  
		{  
			return numToRound;  
		}  

		int remainder = numToRound % multiple; 
		if (remainder == 0)
		{
			return numToRound; 
		}

		return numToRound + multiple - remainder; 
	}  

	template <class T>
	inline short Sign(const T a)
	{
		return a >=0 ? 1 : -1;
	}

	template <class T>
	inline T Clamp(T & val, const T min, const T max)
	{
		if(val < min)
		{
			val = min;
		}
		else if (val > max)
		{
			val = max;
		}
		return val;
	}
}
#endif // MathIncludes_h__