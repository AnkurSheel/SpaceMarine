#include "includes.h"
#include "sm_directories.h"
#include "XMLFileIO.hxx"

using namespace Base;
using namespace Utilities;

SMDirectories SMDirectories::Directories;

// *****************************************************************************
SMDirectories::SMDirectories()
{

}

// *****************************************************************************
SMDirectories::~SMDirectories()
{

}

// *****************************************************************************
bool SMDirectories::Initialize(const Base::cString & AssetsPath,
	const Base::cString & DirectoriesFileName)
{
	m_AssetsPath = AssetsPath;
	IXMLFileIO * pXMLFile = IXMLFileIO::CreateXMLFile();

	if(pXMLFile == NULL)
	{
		return false;
	}
	if(pXMLFile->VLoad(AssetsPath + DirectoriesFileName))
	{
		m_BackGrounds = m_AssetsPath + pXMLFile->VGetNodeValue("BackgroundDirectory");
		m_Player = m_AssetsPath + pXMLFile->VGetNodeValue("PlayerDirectory");
		m_Levels = m_AssetsPath + pXMLFile->VGetNodeValue("LevelDirectory");
	}
	else
	{
		SafeDelete(&pXMLFile);
		return false;
	}
	SafeDelete(&pXMLFile);
	return true;
	
	


}
