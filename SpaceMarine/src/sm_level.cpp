#include "includes.h"
#include "sm_level.h"
#include "sm_directories.h"
#include <XMLFileIO.hxx>
#include <RandomGenerator.hxx>
#include "sm_entity.h"
#include "sm_entity_manager.h"

using namespace Base;
using namespace Utilities;

SMLevel SMLevel::Level;

// *****************************************************************************
SMLevel::SMLevel()
	: m_pRandom(NULL)
	, m_EnemiesWeightRange(0)
{

}

// *****************************************************************************
SMLevel::~SMLevel()
{
	SafeDelete(&m_pRandom);
	m_EnemyDataList.clear();
}

// *****************************************************************************
bool SMLevel::Initialize(const cString & LevelName)
{
	if (LevelName.IsEmpty())
	{
		Log_Write(ILogger::LT_ERROR, 2, "Level Name is empty");
		return false;
	}
	m_pRandom = IRandomGenerator::CreateRandomGenerator();

	IXMLFileIO * pXMLFile = IXMLFileIO::CreateXMLFile();
	if(pXMLFile->VLoad(SMDirectories::Directories.GetLevels() + LevelName))
	{
		m_Background = pXMLFile->VGetNodeAttribute("Level", "BackGround");
		m_LevelSize.x = static_cast<float>(pXMLFile->VGetNodeAttributeAsInt("Level", "Width"));
		m_LevelSize.y = static_cast<float>(pXMLFile->VGetNodeAttributeAsInt("Level", "Height"));

		m_PlayerSpawnPoint.x = static_cast<float>(pXMLFile->VGetNodeAttributeAsInt("Player", "SpawnPointX"));
		m_PlayerSpawnPoint.y = static_cast<float>(pXMLFile->VGetNodeAttributeAsInt("Player", "SpawnPointY"));

		LoadStaticObjects(pXMLFile);
		
		m_EnemiesWeightRange = 0;
		m_EnemyDataList.clear();

		std::vector<cString> EnemyTypes;
		pXMLFile->VGetAllChildrenNames("Enemies", EnemyTypes);
	
		std::vector<cString>::iterator iter;
		for(iter = EnemyTypes.begin(); iter != EnemyTypes.end(); iter++)
		{
			cString strEnemyID = (*iter);

			SMEnemyData Enemydata;
			Enemydata.m_Type = pXMLFile->VGetNodeAttribute(strEnemyID, "Type");
			Enemydata.m_Weight = pXMLFile->VGetNodeAttributeAsInt(strEnemyID, "Weight");

			m_EnemyDataList.push_back(Enemydata);

			m_EnemiesWeightRange += Enemydata.m_Weight;
		}

		int MaxEnemies = pXMLFile->VGetNodeAttributeAsInt("Enemies", "Max");
		for(int Idx = 0; Idx < MaxEnemies; Idx++)
		{
			AddEnemy(pXMLFile);
		}
	}
	else
	{
		SafeDelete(&pXMLFile);
		return false;
	}
	SafeDelete(&pXMLFile);
	return true;
}

// *****************************************************************************
void SMLevel::LoadStaticObjects(const IXMLFileIO * const pXMLFile)
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

		SMEntity * pEntity = SMEntityManager::EntityManager.RegisterEntity(Type, Type);
		if (pEntity != NULL)
		{
			pEntity->VInitialize();
			pEntity->SetPos(cVector2(XPos, YPos));
		}
	}
}

// *****************************************************************************
void SMLevel::AddEnemy(const Utilities::IXMLFileIO * const pXMLFile)
{
	SMEntity * pEntity = NULL; 
	int Val = 0;

	int Random = m_pRandom->Random(m_EnemiesWeightRange);

	EnemydataList::const_iterator ListIter;
	for(ListIter = m_EnemyDataList.begin(); ListIter != m_EnemyDataList.end(); ListIter++)
	{
		SMEnemyData EnemyData = (*ListIter);
		Val += EnemyData.m_Weight;
		if(Random <= Val)
		{
			pEntity = SMEntityManager::EntityManager.RegisterEntity(EnemyData.m_Type, "Soldier");
			break;
		}
	}
	
	if (pEntity != NULL)
	{
		pEntity->VInitialize();
		if(m_pRandom != NULL)
		{
			pEntity->SetPos(cVector2(m_pRandom->Random(m_LevelSize.x), m_pRandom->Random(m_LevelSize.y)));
		}
	}
	else
	{
		Log_Write(ILogger::LT_WARNING, 1, cString(200, "Could not find entity Type. Random value : %d", Random));
	}
}