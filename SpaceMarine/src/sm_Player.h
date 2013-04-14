// *****************************************************************************
//  sm_Player   version:  1.0   Ankur Sheel  date: 2013/04/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "sm_entity.h"

class SMPlayer
	: public SMEntity
{
public:
	SMPlayer(const Base::cString & Name, const Base::cVector2 & LevelSize,
		const Base::cVector2 & ScreenSize);
	~SMPlayer();
	void VUpdate(const float DeltaTime);
	void VRender(SDL_Surface * pDisplaySurface);
	Base::cVector2 GetCameraCenter() const { return m_CameraCenter; }

private:
	Base::cVector2	m_LevelSize;
	Base::cVector2	m_ScreenSize;
	Base::cVector2	m_CameraCenter;
};