// *****************************************************************************
//  sm_bullet   version:  1.0   Ankur Sheel  date: 2013/04/20
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_bullet_h__
#define sm_bullet_h__

#include "sm_entity.h"

class SMBullet
	: public SMEntity
{
public:
	SMBullet(const Base::cString & Type, const Base::cString & SubType,
		const Base::cString & Name);
	~SMBullet();
	bool VInitialize();
	void Initialize(const Base::cVector2 & ParentPosition, const Base::cVector2 & Direction);
	void VCheckCollisions(const Base::cVector2 & PredictedPos);
	void VOnCollided(SMEntity * const pEntity, const Base::cVector2 & PenentrationDistance);
	float GetFireDelay() const { return m_FireDelay; }
	void VUpdate(const float DeltaTime);
	int GetDamage() const { return m_Damage; }

private:
	float	m_FireDelay;
	int		m_Damage;
};
#endif // sm_bullet_h__