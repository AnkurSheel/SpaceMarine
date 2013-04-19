// *****************************************************************************
//  sm_entity   version:  1.0   Ankur Sheel  date: 2013/04/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_entity_h__
#define sm_entity_h__

#include "Vector2.h"
#include <HashedString.h>

class SMBounds;

class SMEntity
	: public Base::cNonCopyable
{
public:
	virtual ~SMEntity();
	virtual bool VInitialize() = 0;
	virtual void VUpdate(const float DeltaTime);
	virtual void VRender(SDL_Surface * pDisplaySurface);
	virtual void VCleanup();
	int GetID() const { return m_ID; }
	Base::cString GetName() const { return m_Name; }
	Base::cString GetType() const { return m_Type.GetString(); }
	unsigned long GetTypeHash() const { return m_Type.GetHash(); }
	Base::cVector2 GetPos() const { return m_Pos; }
	void SetPos(const Base::cVector2 & Pos);
	Base::cVector2 GetSize() const { return m_Size; }
	const SMBounds * const GetBounds() { return m_pBounds; }

protected:
	SMEntity(const Base::cString & Type, const Base::cString & SubType,
		const Base::cString & Name);
	bool Load(const Base::cString & SpriteDirectory);

protected:
	Base::cString			m_Name;
	Base::cHashedString		m_Type;
	Base::cString			m_SubType;
	Base::cVector2			m_Pos;
	Base::cVector2			m_Size;
	SDL_Surface *			m_pSurface;
	SMBounds *				m_pBounds;
	Base::cVector2			m_Speed;
	Base::cVector2			m_SpritePos;
	int						m_MaxSpeed;
	
private:
	void SetID(const int ID);
	void CreateCollider();
	bool Initialize(const Base::cString & FilePath, const bool Collider);
	bool Initialize(const Base::cString & FilePath, const int Width,
		const int Height, const bool Collider);

private:
	int				m_ID;
	static int		m_NextValidID;
};

#endif // sm_entity_h__