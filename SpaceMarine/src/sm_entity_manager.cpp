#include "includes.h"
#include "sm_entity_manager.h"
#include "sm_entity.h"
#include "sm_entity_factory.h"
#include <HashedString.h>

using namespace Utilities;
using namespace Base;

SMEntityManager SMEntityManager::EntityManager;

// *****************************************************************************
SMEntityManager::SMEntityManager()
	: m_pEntityFactory(DEBUG_NEW SMEntityFactory())
{
	m_EntityMap.clear();
}

// *****************************************************************************
SMEntityManager::~SMEntityManager()
{
	SafeDelete(&m_pEntityFactory);
}

// *****************************************************************************
SMEntity * SMEntityManager::RegisterEntity(const cString & Type, const cString & Name)
{
	SMEntity * pEntity = NULL;
	if (m_pEntityFactory != NULL)
	{
		pEntity = m_pEntityFactory->CreateEntity(Type, Name);
		if (pEntity != NULL)
		{
			Log_Write(ILogger::LT_DEBUG, 2, cString(100, "Registering Entity: %d ", pEntity->GetID()) + " Type : " + Type + " Name : " + Name);
			EntityMap::iterator iter = m_EntityMap.find(pEntity->GetTypeHash());
			if(iter == m_EntityMap.end())
			{
				EntityList list;
				list.push_back(pEntity);
				m_EntityMap.insert(std::make_pair(pEntity->GetTypeHash(), list));
			}
			else
			{
				EntityList & list = iter->second;
				list.push_back(pEntity);
			}
		}
	}
	return pEntity;


}

// *****************************************************************************
void SMEntityManager::UnRegisterEntity(SMEntity * const pEntity)
{
	EntityMap::iterator EntityIter = m_EntityMap.find(pEntity->GetTypeHash());
	
	EntityList & List = EntityIter->second;
	List.remove(pEntity);
	if(List.empty())
	{
		m_EntityMap.erase(pEntity->GetTypeHash());
	}
}

// *****************************************************************************
void SMEntityManager::Update(const float DeltaTime)
{
	SMEntityManager::EntityMap::iterator MapIter;
	SMEntity * pEntity;
	for (MapIter = m_EntityMap.begin(); MapIter != m_EntityMap.end(); MapIter++)
	{
		EntityList & List = (MapIter->second);
		SMEntityManager::EntityList ::iterator ListIter;
		for (ListIter = List.begin(); ListIter != List.end(); ListIter++)
		{
			pEntity = *ListIter;
			pEntity->VUpdate(DeltaTime);
		}
	}
}

// *****************************************************************************
void SMEntityManager::Render(SDL_Surface * pDisplaySurface)
{
	SMEntityManager::EntityMap::iterator MapIter;
	SMEntity * pEntity;
	for (MapIter = m_EntityMap.begin(); MapIter != m_EntityMap.end(); MapIter++)
	{
		EntityList & List = (MapIter->second);
		SMEntityManager::EntityList ::iterator ListIter;
		for (ListIter = List.begin(); ListIter != List.end(); ListIter++)
		{
			pEntity = *ListIter;
			pEntity->VRender(pDisplaySurface);
		}
	}
}

// *****************************************************************************
void SMEntityManager::Cleanup()
{
	SMEntityManager::EntityMap::iterator MapIter;
	EntityList List;
	SMEntity * pEntity;
	for (MapIter = m_EntityMap.begin(); MapIter != m_EntityMap.end(); MapIter++)
	{
		List = (MapIter->second);
		SMEntityManager::EntityList ::iterator ListIter;
		for (ListIter = List.begin(); ListIter != List.end(); ListIter++)
		{
			pEntity = *ListIter;
			pEntity->VCleanup();
			SafeDelete(&pEntity);
		}
	}
	m_EntityMap.clear();
}

// *****************************************************************************
void SMEntityManager::GetEntitiesOfType(const cString & Type, EntityList & Entities)
{
	unsigned long hash = cHashedString::CalculateHash(Type);
	EntityMap::iterator iter = m_EntityMap.find(hash);
	if(iter == m_EntityMap.end())
	{
		Log_Write(ILogger::LT_WARNING, 1, "No entity of type " + Type);
	}
	else
	{
		Entities = iter->second;
	}
}
