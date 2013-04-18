// *****************************************************************************
//  sm_entity_manager   version:  1.0   Ankur Sheel  date: 2013/04/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_entity_manager_h__
#define sm_entity_manager_h__

#include <map>

class SMEntity;
class SMEntityFactory;

class SMEntityManager
	: public Base::cNonCopyable
{
public:
	typedef std::map<int, SMEntity * const > EntityMap;

public:
	SMEntity * RegisterEntity(const Base::cString & Type, const Base::cString & Name);
	void UnRegisterEntity(SMEntity * const pEntity);
	SMEntity * const GetEntityFromID(const int ID);
	void Update(const float DeltaTime);
	void Render(SDL_Surface * pDisplaySurface);
	void Cleanup();
	// return const reference to map to avoid overhead of copying the map
	const EntityMap & GetEntityMap() { return m_EntityMap; }

public:
	static SMEntityManager	EntityManager;

private:
	SMEntityManager();
	~SMEntityManager();

private:
	EntityMap			m_EntityMap;
	SMEntityFactory	*	m_pEntityFactory;
};

#endif // sm_entity_manager_h__
