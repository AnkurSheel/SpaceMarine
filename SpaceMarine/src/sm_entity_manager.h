// *****************************************************************************
//  sm_entity_manager   version:  1.0   Ankur Sheel  date: 2013/04/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_entity_manager_h__
#define sm_entity_manager_h__

#include <map>
#include <list>

class SMEntity;
class SMEntityFactory;

class SMEntityManager
	: public Base::cNonCopyable
{
public:
	typedef std::list<SMEntity * const > EntityList;
	typedef std::map<unsigned long, EntityList> EntityMap;

public:
	SMEntity * RegisterEntity(const Base::cString & Type, const Base::cString & SubType,
		const Base::cString & Name);
	void UnRegisterEntity(SMEntity * const pEntity);
	void Update(const float DeltaTime);
	void Render(SDL_Surface * pDisplaySurface);
	void Cleanup();
	void GetEntitiesOfType(const Base::cString & strType, EntityList & entities);

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
