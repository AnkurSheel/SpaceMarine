#include "includes.h"
#include "sm_enemy.h"
#include "sm_directories.h"

using namespace Base;
using namespace Utilities;

// *****************************************************************************
SMEnemy::SMEnemy(const cString & Type, const cString & SubType, const cString & Name)
	: SMEntity(Type, SubType, Name)
{

}

// *****************************************************************************
SMEnemy::~SMEnemy()
{

}

// *****************************************************************************
bool SMEnemy::VInitialize()
{
	return Load(SMDirectories::Directories.GetEnemySprites());
}
