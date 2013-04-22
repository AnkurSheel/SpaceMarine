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
	SMEnemy(const Base::cString & Type, const Base::cString & SubType,
		const Base::cString & Name);
	~SMEnemy();
	bool VInitialize();
	void VUpdate(const float DeltaTime);
	void VOnCollided(SMEntity * const pEntity, const Base::cVector2 & PenentrationDistance);
	void VCheckCollisions(const Base::cVector2 & PredictedPos);
	bool VTakeDamage(const int Amount);

protected:
	int				m_ScoreGiven;
	int				m_Damage;
	Base::cVector2	m_Direction;

private:
	void GetNewDirection();

private:
	float	m_ChangeDirectionTimer;
	float	m_LastDirectionChangeTime;
};
#endif // sm_enemy_h__