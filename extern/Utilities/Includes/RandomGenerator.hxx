// *****************************************************************************
//  Random   version:  1.0   Ankur Sheel  date: 2011/04/16
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// adapted from Game Coding Complete 
// *****************************************************************************
#ifndef RandomGenerator_hxx__
#define RandomGenerator_hxx__

#include "UtilitiesDefines.h"

namespace Utilities
{
	class IRandomGenerator
	{
	public:
		virtual ~IRandomGenerator() {}
		virtual unsigned int Random(const unsigned int nMax) = 0;
		virtual int Random(const int nMin,	const int nMax) = 0;
		virtual float Random() = 0;
		virtual void SetRandomSeed(const unsigned int nSeed) = 0 ;
		virtual unsigned int GetRandomSeed() = 0;
		virtual void Randomize() = 0;
		UTILITIES_API static IRandomGenerator * CreateRandomGenerator();
	};
}
#endif // RandomGenerator_hxx__
