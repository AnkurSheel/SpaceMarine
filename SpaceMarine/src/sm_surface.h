// *****************************************************************************
//  sm_surface   version:  1.0   Ankur Sheel  date: 2013/04/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_surface_h__
#define sm_surface_h__

#include <NonCopyable.h>

struct SDL_Surface;

class SMSurface
	: public Base::cNonCopyable
{
public:
	SMSurface();
	~SMSurface();

public:
	static SDL_Surface * OnLoad(const Base::cString & FilePath);
	static bool OnDraw(SDL_Surface * pDestinationSurface,
		SDL_Surface * pSourceSurface, const int XDestPos, const int YDestPos);
	static bool OnDraw(SDL_Surface * pDestinationSurface,
		SDL_Surface * pSourceSurface, const int XDestPos, int YDestPos,
		const int XSrcPos, int YSrcPos, const int Width, const int Height);

private:
	static bool InternalDraw(SDL_Surface * pDestinationSurface, SDL_Rect * pSrcR,
		SDL_Surface * pSourceSurface, SDL_Rect * pDestR);

};
#endif // sm_surface_h__