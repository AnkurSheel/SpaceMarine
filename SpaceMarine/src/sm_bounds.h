// *****************************************************************************
//  sm_bounds  version:  1.0   Ankur Sheel  date: 2013/04/17
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "vector2.h"

class SMBounds
{
public:
	SMBounds(const Base::cVector2 & Min, const Base::cVector2 & Max);
	~SMBounds();
	SMBounds(const SMBounds & Other);
	SMBounds& operator =(const SMBounds & Other);
	void Transalate(const Base::cVector2 & DeltaPos);
	Base::cVector2 GetCenter() const { return m_Center; }
	Base::cVector2 GetHalfExtents() const { return m_HalfExtents; }
	static bool CheckCollision(const SMBounds * const pObjectA, 
		const SMBounds * pObjectB, Base::cVector2 & PenentrationDistance);

private:
	void CalculateBounds(const Base::cVector2 & Min, const Base::cVector2 & Max);

private:
	Base::cVector2	m_Center;
	Base::cVector2	m_HalfExtents;
};