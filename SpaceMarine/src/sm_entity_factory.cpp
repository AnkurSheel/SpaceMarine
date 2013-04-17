#include "includes.h"
#include "sm_entity_factory.h"
#include "sm_Player.h"
#include "sm_static_object.h"

using namespace Base;
using namespace Utilities;

// *****************************************************************************
SMEntityFactory::SMEntityFactory()
{

}

// *****************************************************************************
SMEntityFactory::~SMEntityFactory()
{

}

// *****************************************************************************
SMEntity * SMEntityFactory::CreateEntity(const cString & Type, const cString & Name)
{
	if (Type.CompareInsensitive("SMPlayer"))
	{
		return DEBUG_NEW SMPlayer(Name);
	}
	else if (Type.CompareInsensitive("SMStaticObject"))
	{
		return DEBUG_NEW SMStaticObject(Name);
	}
	Log_Write(ILogger::LT_ERROR, 1, "Cannot create Entity of Type :" + Type);
	return NULL;
}
