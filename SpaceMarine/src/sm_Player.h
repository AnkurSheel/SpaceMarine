// *****************************************************************************
//  sm_Player   version:  1.0   Ankur Sheel  date: 2013/04/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_Player_h__
#define sm_Player_h__

#include "sm_entity.h"

class SMPlayer
	: public SMEntity
{
public:
	SMPlayer(const Base::cString & Type, const Base::cString & Name);
	~SMPlayer();
	bool VInitialize();
	void VUpdate(const float DeltaTime);
	void CheckCollisions(const Base::cVector2 & PredictedPos);
};

#endif // sm_Player_h__