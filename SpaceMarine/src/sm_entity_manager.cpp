#include "includes.h"
#include "sm_entity_manager.h"
#include "sm_entity.h"
#include "sm_entity_factory.h"

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
			m_EntityMap.insert(std::make_pair(pEntity->GetID(), pEntity));
		}
	}
	return pEntity;
}

// *****************************************************************************
SMEntity * const SMEntityManager::GetEntityFromID(const int ID)
{
	//find the entity
	EntityMap::const_iterator ent = m_EntityMap.find(ID);

	//assert that the entity is a member of the map
	if (ent !=  m_EntityMap.end())
	{
		return ent->second;
	}
	return NULL;
}

// *****************************************************************************
void SMEntityManager::UnRegisterEntity(SMEntity * const pEntity)
{
	m_EntityMap.erase(m_EntityMap.find(pEntity->GetID()));
}

// *****************************************************************************
void SMEntityManager::Update(const float DeltaTime)
{
	SMEntityManager::EntityMap::iterator Iter;
	SMEntity * pEntity;
	for (Iter = m_EntityMap.begin(); Iter != m_EntityMap.end(); Iter++)
	{
		pEntity = (Iter->second);
		pEntity->VUpdate(DeltaTime);
	}
}

// *****************************************************************************
void SMEntityManager::Render(SDL_Surface * pDisplaySurface)
{
	SMEntityManager::EntityMap::iterator Iter;
	SMEntity * pEntity;
	for (Iter = m_EntityMap.begin(); Iter != m_EntityMap.end(); Iter++)
	{
		pEntity = (Iter->second);
		pEntity->VRender(pDisplaySurface);
	}
}

// *****************************************************************************
void SMEntityManager::Cleanup()
{
	SMEntityManager::EntityMap::iterator Iter;
	SMEntity * pEntity;
	for (Iter = m_EntityMap.begin(); Iter != m_EntityMap.end(); Iter++)
	{
		pEntity = (Iter->second);
		pEntity->VCleanup();
		SafeDelete(&pEntity);
	}
	m_EntityMap.clear();
}
