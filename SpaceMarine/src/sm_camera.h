// *****************************************************************************
//  sm_camera   version:  1.0   Ankur Sheel  date: 2013/04/16
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "NonCopyable.h"
#include "Vector2.h"

class SMEntity;

class SMCamera
	: public Base::cNonCopyable
{
public:
	SMCamera();
	~SMCamera();
	void SetTarget(SMEntity * const pTarget) { m_pTarget = pTarget; }
	Base::cVector2 GetPos() const { return m_Pos; }
	void SetPos(const Base::cVector2 & Pos) { m_Pos = Pos; }
	void Update();

private:
	Base::cVector2	m_Pos;
	SMEntity *		m_pTarget;
};