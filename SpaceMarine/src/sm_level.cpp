#include "includes.h"
#include "sm_level.h"
#include "sm_directories.h"
#include <XMLFileIO.hxx>

using namespace Base;
using namespace Utilities;

SMLevel SMLevel::Level;

// *****************************************************************************
SMLevel::SMLevel()
{

}

// *****************************************************************************
SMLevel::~SMLevel()
{

}

// *****************************************************************************
bool SMLevel::Initialize(const cString & LevelName)
{
	if (LevelName.IsEmpty())
	{
		Log_Write(ILogger::LT_ERROR, 2, "Level Name is empty");
		return false;
	}
	IXMLFileIO * pXMLFile = IXMLFileIO::CreateXMLFile();
	if (pXMLFile == NULL)
	{
		return false;
	}
	if(pXMLFile->VLoad(SMDirectories::Directories.GetLevels() + LevelName))
	{
		m_Background = pXMLFile->VGetNodeValue("BackGround");
	}
	else
	{
		SafeDelete(&pXMLFile);
		return false;
	}
	SafeDelete(&pXMLFile);
	return true;
}
