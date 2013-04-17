#include "includes.h"
#include "sm_bounds.h"

using namespace Base;

// *****************************************************************************
SMBounds::SMBounds(const cVector2 & Min, const cVector2 & Max)
{
	CalculateBounds(Min, Max);
}

// *****************************************************************************
SMBounds::~SMBounds()
{

}

// *****************************************************************************
SMBounds::SMBounds(const SMBounds & Other)
	: m_Center(Other.m_Center)
	, m_HalfExtents(Other.m_HalfExtents)
{

}

// *****************************************************************************
SMBounds & SMBounds::operator =(const SMBounds & Other)
{
	m_Center = Other.m_Center;
	m_HalfExtents = Other.m_HalfExtents;
	return *this;
}	

// *****************************************************************************
void SMBounds::CalculateBounds(const cVector2 & Min, const cVector2 & Max)
{
	m_Center = ((Min + Max) * 0.5f);
	m_HalfExtents = ((Max - Min) * 0.5f);
}

// *****************************************************************************
void SMBounds::Transalate(const Base::cVector2 & DeltaPos)
{
	m_Center += DeltaPos;
}

// *****************************************************************************
bool SMBounds::CheckCollision(const SMBounds * const pObjectA, const SMBounds * pObjectB, cVector2 & PenetrationDistance)
{
	PenetrationDistance = cVector2::Zero();
	if(pObjectA == NULL || pObjectB == NULL)
	{
		return false;
	}

	cVector2 CenterDelta = pObjectA->GetCenter() - pObjectB->GetCenter();
	cVector2 Overlap = CenterDelta;
	Overlap.AbsTo();

	cVector2 HalfExtentSum = pObjectA->GetHalfExtents() + pObjectB->GetHalfExtents();
	Overlap = HalfExtentSum - Overlap;

	bool Collides = Overlap.x > 0 && Overlap.y > 0;
	if(Collides)
	{
		cVector2 SmallestOverlap = Overlap.MinorAxis();
		cVector2 PlaneNormal = (CenterDelta * SmallestOverlap).MajorAxis();

		PenetrationDistance = Overlap * PlaneNormal;
	}
	return Collides;
}
