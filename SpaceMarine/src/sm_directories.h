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
	Base::cString GetBackGrounds() const { return m_BackGrounds; }
	Base::cString GetPlayer() const { return m_Player; }
	Base::cString GetLevels() const { return m_Levels; }

public:
	static SMDirectories Directories;

private:
	SMDirectories();
	~SMDirectories();

private:
	Base::cString	m_AssetsPath;
	Base::cString	m_BackGrounds;
	Base::cString	m_Player;
	Base::cString	m_Levels;
};
#endif // sm_directories_h__