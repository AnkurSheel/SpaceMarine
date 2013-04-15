// *****************************************************************************
//  sm_entity   version:  1.0   Ankur Sheel  date: 2013/04/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_entity_h__
#define sm_entity_h__

#include "NonCopyable.h"
#include "Vector2.h"

class SMEntity
	: public Base::cNonCopyable
{
public:
	SMEntity(const int ID, const Base::cString & Name);
	SMEntity(const Base::cString & Name);
	virtual ~SMEntity();
	int GetID() const { return m_ID; }
	Base::cString GetName() const { return m_Name; }
	virtual bool VOnLoad(const Base::cString & FilePath);
	virtual bool VOnLoad(const Base::cString & FilePath, const int Width,
		const int Height, const int MaxFrames);
	virtual void VUpdate(const float DeltaTime);
	virtual void VRender(SDL_Surface * pDisplaySurface);
	virtual void VCleanup();
	Base::cVector2 GetPos() const { return m_Pos; }
	void SetPos(Base::cVector2 val) { m_Pos = val; }
	Base::cVector2 GetSize() const { return m_Size; }

protected:
	Base::cString	m_Name;
	Base::cVector2	m_Pos;
	Base::cVector2	m_Size;
	SDL_Surface *	m_pSurface;

private:
	void SetID(const int ID);

private:
	int				m_ID;
	static int		m_NextValidID;
};

#endif // sm_entity_h__