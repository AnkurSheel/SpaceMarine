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
	SMPlayer(const Base::cString & Name);
	~SMPlayer();
	bool VInitialize();
	void VUpdate(const float DeltaTime);
	void VRender(SDL_Surface * pDisplaySurface);
	void CheckCollisions(const Base::cVector2 & PredictedPos);

private:
	float	m_MaxSpeed;
};