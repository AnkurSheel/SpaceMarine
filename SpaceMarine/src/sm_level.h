// *****************************************************************************
//  sm_level   version:  1.0   Ankur Sheel  date: 2013/04/14
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_level_h__
#define sm_level_h__

#include <NonCopyable.h>
#include <Vector2.h>

class SMLevel
	: public Base::cNonCopyable
{
public:
	bool Initialize(const Base::cString & LevelName);
	Base::cString GetBackground() const { return m_Background; }

public:
	static SMLevel Level;

private:
	SMLevel();
	~SMLevel();

private:
	Base::cString	m_Background;
	Base::cVector2	m_PlayerSpawnPoint;
};
#endif // sm_level_h__