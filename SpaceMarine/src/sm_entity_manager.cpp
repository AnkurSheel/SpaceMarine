#include "includes.h"
#include "sm_entity_manager.h"
#include "sm_entity.h"

using namespace Utilities;
using namespace Base;

SMEntityManager::EntityMap	SMEntityManager::m_EntityMap;

// *****************************************************************************
SMEntityManager::SMEntityManager()
{
	m_EntityMap.clear();
}

// *****************************************************************************
SMEntityManager::~SMEntityManager()
{
}

// *****************************************************************************
void SMEntityManager::VRegisterEntity(SMEntity * const pEntity)
{
	Log_Write(ILogger::LT_DEBUG, 2, cString(100, "Registering Entity: %d ", pEntity->GetID()) + pEntity->GetName());
	m_EntityMap.insert(std::make_pair(pEntity->GetID(), pEntity));
}

// *****************************************************************************
SMEntity * const SMEntityManager::VGetEntityFromID(const int ID)
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
cString const SMEntityManager::VGetEntityNameFromID(const int ID)
{
	SMEntity * pEntity = VGetEntityFromID(ID);
	if (pEntity != NULL)
	{
		return pEntity->GetName();
	}
	return "";
}

// *****************************************************************************
void SMEntityManager::UnRegisterEntity(SMEntity * const pEntity )
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
