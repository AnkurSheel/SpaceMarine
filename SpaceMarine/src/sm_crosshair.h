// *****************************************************************************
//  sm_crosshair   version:  1.0   Ankur Sheel  date: 2013/04/20
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_crosshair_h__
#define sm_crosshair_h__

#include <Vector2.h>

class SMCrosshair
	: public Base::cNonCopyable
{
public:
	SMCrosshair();
	~SMCrosshair();
	bool Initialize(const Base::cString & FilePath, const Base::cVector2 & Offset);
	void Render(SDL_Surface * pDisplaySurface);
	void UpdatePosition(const Base::cVector2 & ParentPosition, const float Angle);

private:
	SDL_Surface *	m_pSurface;
	Base::cVector2	m_Position;
	Base::cVector2	m_Offset;
};
#endif // sm_crosshair_h__