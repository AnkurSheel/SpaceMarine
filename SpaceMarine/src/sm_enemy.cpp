#include "includes.h"
#include "sm_enemy.h"
#include "sm_directories.h"

using namespace Base;
using namespace Utilities;

// *****************************************************************************
SMEnemy::SMEnemy(const Base::cString & Type, const Base::cString & Name)
	: SMEntity(Type, Name)
{

}

// *****************************************************************************
SMEnemy::~SMEnemy()
{

}

// *****************************************************************************
bool SMEnemy::VInitialize()
{
	return Load(m_Type.GetString(), SMDirectories::Directories.GetEnemySprites());
}
