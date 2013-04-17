#include "includes.h"
#include "sm_level.h"
#include "sm_directories.h"
#include <XMLFileIO.hxx>
#include "sm_entity.h"
#include "sm_entity_manager.h"

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
		m_Background = pXMLFile->VGetNodeAttribute("Level", "BackGround");
		m_LevelSize.x = static_cast<float>(pXMLFile->VGetNodeAttributeAsInt("Level", "Width"));
		m_LevelSize.y = static_cast<float>(pXMLFile->VGetNodeAttributeAsInt("Level", "Height"));

		m_PlayerSpawnPoint.x = static_cast<float>(pXMLFile->VGetNodeAttributeAsInt("Player", "SpawnPointX"));
		m_PlayerSpawnPoint.y = static_cast<float>(pXMLFile->VGetNodeAttributeAsInt("Player", "SpawnPointY"));

		LoadStaticObjects(pXMLFile);
	}
	else
	{
		SafeDelete(&pXMLFile);
		return false;
	}
	SafeDelete(&pXMLFile);
	return true;
}

void SMLevel::LoadStaticObjects(IXMLFileIO * const pXMLFile)
{
	std::vector<cString> StaticObjects;
	pXMLFile->VGetAllChildrenNames("StaticObjects", StaticObjects);
	
	std::vector<cString>::iterator iter;
	for(iter = StaticObjects.begin(); iter != StaticObjects.end(); iter++)
	{
		cString strStaticObjectID = (*iter);
		cString Type = pXMLFile->VGetNodeAttribute(strStaticObjectID, "Type");
		int XPos = pXMLFile->VGetNodeAttributeAsInt(strStaticObjectID, "XPos");
		int YPos = pXMLFile->VGetNodeAttributeAsInt(strStaticObjectID, "YPos");

		SMEntity * pEntity = SMEntityManager::EntityManager.RegisterEntity("SMStaticObject", strStaticObjectID);
		if (pEntity != NULL)
		{
			pEntity->VInitialize(SMDirectories::Directories.GetObjectSprites() + Type + ".png", true);
			pEntity->SetPos(cVector2(XPos, YPos));
		}
	}
}