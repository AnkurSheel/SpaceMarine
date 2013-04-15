// *****************************************************************************
//  sm_directories   version:  1.0   Ankur Sheel  date: 2013/04/14
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_directories_h__
#define sm_directories_h__

#include <NonCopyable.h>

class SMDirectories
	: public Base::cNonCopyable
{
public:
	bool Initialize(const Base::cString & AssetsPath, const Base::cString & DirectoriesFileName);
	Base::cString GetBackGroundSprites() const { return m_BackGroundSprites; }
	Base::cString GetPlayerSprites() const { return m_PlayerSprites; }
	Base::cString GetLevels() const { return m_Levels; }
	Base::cString GetObjectSprites() const { return m_ObjectSprites; }

public:
	static SMDirectories Directories;

private:
	SMDirectories();
	~SMDirectories();

private:
	Base::cString	m_AssetsPath;
	Base::cString	m_BackGroundSprites;
	Base::cString	m_PlayerSprites;
	Base::cString	m_ObjectSprites;
	Base::cString	m_Levels;
};
#endif // sm_directories_h__