// *****************************************************************************
//  includes   version:  1.0   Ankur Sheel  date: 2013/04/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef includes_h__
#define includes_h__

#include <crtdbg.h>
#include "SDL.h"
#include "Logger.hxx"
#include "MyString.h"
#include "Macros.h"
#include "BaseUtilities.h"
#include "NonCopyable.h"

template <typename Interface>
inline void SafeFreeSurface(Interface **ppInterfaceToFree)
{
	if (*ppInterfaceToFree != NULL)
	{
		SDL_FreeSurface(*ppInterfaceToFree);
		(*ppInterfaceToFree) = NULL;
	}
}

#endif // includes_h__
