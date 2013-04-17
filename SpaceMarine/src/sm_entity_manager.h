// *****************************************************************************
//  sm_entity_manager   version:  1.0   Ankur Sheel  date: 2013/04/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_entity_manager_h__
#define sm_entity_manager_h__

#include "NonCopyable.h"
#include <map>

class SMEntity;

class SMEntityManager
	: public Base::cNonCopyable
{
public:
	typedef std::map<int, SMEntity * const > EntityMap;

public:
	static void VRegisterEntity(SMEntity * const pEntity);
	static void UnRegisterEntity(SMEntity * const pEntity);
	static SMEntity * const VGetEntityFromID(const int ID);
	static Base::cString const VGetEntityNameFromID(const int ID);
	static void Update(const float DeltaTime);
	static void Render(SDL_Surface * pDisplaySurface);
	static void Cleanup();

private:
	SMEntityManager();
	~SMEntityManager();

public:
	static  EntityMap		m_EntityMap;
};

#endif // sm_entity_manager_h__
