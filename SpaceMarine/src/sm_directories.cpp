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
		m_BackGroundSprites = m_AssetsPath + pXMLFile->VGetNodeValue("BackgroundSprites");
		m_PlayerSprites = m_AssetsPath + pXMLFile->VGetNodeValue("PlayerSprites");
		m_ObjectSprites = m_AssetsPath + pXMLFile->VGetNodeValue("ObjectsSprites");
		m_EnemySprites = m_AssetsPath + pXMLFile->VGetNodeValue("EnemySprites");
		m_Levels = m_AssetsPath + pXMLFile->VGetNodeValue("Levels");
		m_Fonts = m_AssetsPath + pXMLFile->VGetNodeValue("Fonts");
	}
	else
	{
		SafeDelete(&pXMLFile);
		return false;
	}
	SafeDelete(&pXMLFile);
	return true;
}
