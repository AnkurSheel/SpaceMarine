// *****************************************************************************
//  sm_enemy   version:  1.0   Ankur Sheel  date: 2013/04/16
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_enemy_h__
#define sm_enemy_h__

#include "sm_entity.h"

class SMEnemy
	: public SMEntity
{
public:
	SMEnemy(const Base::cString & Type, const Base::cString & Name);
	~SMEnemy();
	bool VInitialize();
};
#endif // sm_enemy_h__