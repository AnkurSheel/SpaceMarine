// *****************************************************************************
//  sm_level   version:  1.0   Ankur Sheel  date: 2013/04/14
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_level_h__
#define sm_level_h__

#include <NonCopyable.h>
#include <Vector2.h>

namespace Utilities
{
	class IXMLFileIO;
}

class SMLevel
	: public Base::cNonCopyable
{
public:
	bool Initialize(const Base::cString & LevelName);
	Base::cString GetBackground() const { return m_Background; }
	Base::cVector2 GetLevelSize() const { return m_LevelSize; }
	Base::cVector2 GetPlayerSpawnPoint() const { return m_PlayerSpawnPoint; }

public:
	static SMLevel Level;

private:
	SMLevel();
	~SMLevel();
	void LoadStaticObjects(Utilities::IXMLFileIO * const pXMLFile);

private:
	Base::cString	m_Background;
	Base::cVector2	m_LevelSize;
	Base::cVector2	m_PlayerSpawnPoint;
};
#endif // sm_level_h__