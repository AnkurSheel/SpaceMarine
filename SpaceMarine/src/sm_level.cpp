#include "includes.h"
#include "sm_level.h"
#include "sm_directories.h"
#include <XMLFileIO.hxx>
#include "sm_entity.h"
#include "sm_entity_manager.h"
#include "sm_game.h"
#include <RandomGenerator.hxx>
#include "sm_entity_types.h"

using namespace Base;
using namespace Utilities;

SMLevel SMLevel::Level;

// *****************************************************************************
SMLevel::SMLevel()
	: m_MaxEnemies(0)
	, m_EnemiesWeightRange(0)
	, m_Initialized(false)
	, m_LastSpawnTime(0.0f)
	, m_SpawnInterval(0.0f)
	, m_MaxEnemiesSpawned(false)
{
	m_EnemyDataList.clear();
}

// *****************************************************************************
SMLevel::~SMLevel()
{
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
	
	int InitialEnemies = 0;
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

		m_MaxEnemies = pXMLFile->VGetNodeAttributeAsInt("Enemies", "Max");
		InitialEnemies = pXMLFile->VGetNodeAttributeAsInt("Enemies", "Initial");
		m_SpawnInterval = (pXMLFile->VGetNodeAttributeAsInt("Enemies", "SpawnInterval") / 1000.0f);
	}
	else
	{
		SafeDelete(&pXMLFile);
		return false;
	}
	SafeDelete(&pXMLFile);
	for(int Idx = 0; Idx < InitialEnemies; Idx++)
	{
		AddEnemy();
	}
	m_Initialized = true;
	return true;
}

// *****************************************************************************
void SMLevel::Update(const float DeltaTime)
{
	if(m_Initialized && !m_MaxEnemiesSpawned)
	{
		m_LastSpawnTime += DeltaTime;
		if(m_LastSpawnTime >= m_SpawnInterval)
		{
			m_LastSpawnTime = 0.0f;
			AddEnemy();
		}
	}
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

		SMEntity * pEntity = SMEntityManager::EntityManager.RegisterEntity("StaticObject", Type, strStaticObjectID);
		if (pEntity != NULL)
		{
			pEntity->VInitialize();
			pEntity->SetLevelPosition(cVector2(static_cast<float>(XPos), static_cast<float>(YPos)));
		}
	}
}

// *****************************************************************************
void SMLevel::AddEnemy()
{
	SMEntityManager::EntityList EnemiesList;
	if(!m_MaxEnemiesSpawned)
	{
		SMEntityManager::EntityManager.GetEntitiesOfType(SMEntityTypes::Enemy, EnemiesList);
		if(EnemiesList.size() >= static_cast<unsigned int>(m_MaxEnemies))
		{
			Log_Write(ILogger::LT_COMMENT, 1, "Max Enemies Spawned");
			m_MaxEnemiesSpawned = true;
			return;
		}
	}
	SMEntity * pEntity = NULL; 
	int Val = 0;
	int Random = 0;
	if (SMGame::GetRandomGenerator() != NULL)
	{
		Random = SMGame::GetRandomGenerator()->Random(m_EnemiesWeightRange);
	}

	EnemydataList::const_iterator ListIter;
	for(ListIter = m_EnemyDataList.begin(); ListIter != m_EnemyDataList.end(); ListIter++)
	{
		SMEnemyData EnemyData = (*ListIter);
		Val += EnemyData.m_Weight;
		if(Random <= Val)
		{
			pEntity = SMEntityManager::EntityManager.RegisterEntity("Enemy", EnemyData.m_Type, "Soldier");
			break;
		}
	}
	
	if (pEntity != NULL)
	{
		pEntity->VInitialize();
		if(SMGame::GetRandomGenerator() != NULL)
		{
			float XPos = static_cast<float>(SMGame::GetRandomGenerator()->Random(static_cast<int>(m_LevelSize.x)));
			float YPos = static_cast<float>(SMGame::GetRandomGenerator()->Random(static_cast<int>(m_LevelSize.y)));
			pEntity->SetLevelPosition(cVector2(XPos, YPos));
		}
	}
	else
	{
		Log_Write(ILogger::LT_WARNING, 1, cString(200, "Could not find entity Type. Random value : %d", Random));
	}
}

// *****************************************************************************
void SMLevel::EnemyRemoved()
{
	m_MaxEnemiesSpawned = false;
}
