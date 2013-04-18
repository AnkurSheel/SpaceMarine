// *****************************************************************************
//  sm_entity   version:  1.0   Ankur Sheel  date: 2013/04/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_entity_h__
#define sm_entity_h__

#include "Vector2.h"

class SMBounds;

class SMEntity
	: public Base::cNonCopyable
{
public:
	SMEntity(const int ID, const Base::cString & Name);
	SMEntity(const Base::cString & Name);
	virtual ~SMEntity();
	int GetID() const { return m_ID; }
	Base::cString GetName() const { return m_Name; }
	virtual bool VInitialize(const Base::cString & FilePath, const bool Collider);
	virtual bool VInitialize(const Base::cString & FilePath, const int Width,
		const int Height, const int MaxFrames, const bool Collider);
	virtual void VUpdate(const float DeltaTime);
	virtual void VRender(SDL_Surface * pDisplaySurface);
	virtual void VCleanup();
	Base::cVector2 GetPos() const { return m_Pos; }
	void SetPos(const Base::cVector2 & Pos);
	Base::cVector2 GetSize() const { return m_Size; }
	const SMBounds * const GetBounds() { return m_pBounds; }

protected:
	Base::cString	m_Name;
	Base::cVector2	m_Pos;
	Base::cVector2	m_Size;
	SDL_Surface *	m_pSurface;
	SMBounds *		m_pBounds;
	Base::cVector2	m_Speed;
	
private:
	void SetID(const int ID);
	void CreateCollider();

private:
	int				m_ID;
	static int		m_NextValidID;
};

#endif // sm_entity_h__