#include "includes.h"
#include "sm_entity_factory.h"
#include "sm_Player.h"
#include "sm_static_object.h"
#include "sm_enemy.h"
#include "sm_bullet.h"

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
SMEntity * SMEntityFactory::CreateEntity(const cString & Type, const cString & SubType,
	const cString & Name)
{
	if (SubType.CompareInsensitive("player"))
	{
		return DEBUG_NEW SMPlayer(Type, SubType, Name);
	}
	else if (SubType.CompareInsensitive("rock"))
	{
		return DEBUG_NEW SMStaticObject(Type, SubType, Name);
	}
	else if (SubType.CompareInsensitive("woods"))
	{
		return DEBUG_NEW SMStaticObject(Type, SubType, Name);
	}
	else if (SubType.CompareInsensitive("meleesoldier"))
	{
		return DEBUG_NEW SMEnemy(Type, SubType, Name);
	}
	else if (SubType.CompareInsensitive("rangedsoldier"))
	{
		return DEBUG_NEW SMEnemy(Type, SubType, Name);
	}
	else if (SubType.CompareInsensitive("bullet"))
	{
		return DEBUG_NEW SMBullet(Type, SubType, Name);
	}
	Log_Write(ILogger::LT_ERROR, 1, "Cannot create Entity of Type :" + Type + " SubType : " + SubType);
	return NULL;
}
