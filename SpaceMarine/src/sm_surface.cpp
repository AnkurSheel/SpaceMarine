#include "includes.h"
#include "sm_surface.h"
#include "SDL_image.h"

using namespace Utilities;
using namespace Base;

// *****************************************************************************
SMSurface::SMSurface()
{

}

// *****************************************************************************
SMSurface::~SMSurface()
{

}

// *****************************************************************************
SDL_Surface * SMSurface::OnLoad(const Base::cString & FilePath)
{
	SDL_Surface * pSurfaceTemp = IMG_Load(FilePath.GetData());
	
	if (pSurfaceTemp == NULL)
	{
		Log_Write(ILogger::LT_WARNING, 1, cString("Could not load file: ") + FilePath);
		return NULL;
	}
	
	SDL_Surface * pSurfaceReturn = SDL_DisplayFormatAlpha(pSurfaceTemp);
	SDL_FreeSurface(pSurfaceTemp);
	return pSurfaceReturn;
}

// *****************************************************************************
bool SMSurface::OnDraw(SDL_Surface * pDestinationSurface,
	SDL_Surface * pSourceSurface, const int XDestPos, const int YDestPos)
{
	SDL_Rect DestR;
	DestR.x = XDestPos;
	DestR.y = YDestPos;

	return InternalDraw(pDestinationSurface, NULL, pSourceSurface, &DestR);
}

// *****************************************************************************
bool SMSurface::OnDraw(SDL_Surface * pDestinationSurface,
	SDL_Surface * pSourceSurface, const int XDestPos, int YDestPos,
	const int XSrcPos, int YSrcPos, const int Width, const int Height)
{
	SDL_Rect DestR;
	DestR.x = XDestPos;
	DestR.y = YDestPos;

	SDL_Rect SrcR;
	SrcR.x = XSrcPos;
	SrcR.y = YSrcPos;
	SrcR.w = Width;
	SrcR.h = Height;

	return InternalDraw(pDestinationSurface, &SrcR, pSourceSurface, &DestR);
}

// *****************************************************************************
bool SMSurface::InternalDraw(SDL_Surface * pDestinationSurface, SDL_Rect * pSrcR,
	SDL_Surface * pSourceSurface, SDL_Rect * pDestR)
{
	if (pDestinationSurface == NULL)
	{
		Log_Write(ILogger::LT_WARNING, 2, "Destination Surface is NUll");
		return false;
	}
	if (pSourceSurface == NULL)
	{
		Log_Write(ILogger::LT_WARNING, 2 , "Source Surface is Null");
		return false;
	}
	
	SDL_BlitSurface(pSourceSurface, pSrcR, pDestinationSurface, pDestR);
	return true;
}
