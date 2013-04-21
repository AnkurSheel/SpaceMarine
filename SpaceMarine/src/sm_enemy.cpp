#include "includes.h"
#include "sm_enemy.h"
#include "sm_directories.h"
#include "sm_entity_manager.h"
#include "sm_level.h"
#include "sm_Player.h"
#include "sm_config.h"
#include <XMLFileIO.hxx>

using namespace Base;
using namespace Utilities;

// *****************************************************************************
SMEnemy::SMEnemy(const cString & Type, const cString & SubType, const cString & Name)
	: SMEntity(Type, SubType, Name)
	, m_ScoreGiven(0)
{

}

// *****************************************************************************
SMEnemy::~SMEnemy()
{

}

// *****************************************************************************
bool SMEnemy::VInitialize()
{
	if(!Load(SMDirectories::Directories.GetEnemySprites()))
	{
		return false;
	}
	m_ScoreGiven = SMConfig::GetConfigLoader()->VGetNodeAttributeAsInt(m_SubType, "Score");
	return true;
}

// *****************************************************************************
void SMEnemy::VOnCollided(SMEntity * const pEntity, const Base::cVector2 & PenentrationDistance)
{
	SMEntity::VOnCollided(pEntity, PenentrationDistance);
	if (pEntity->GetType().CompareInsensitive("StaticObject"))
	{
		cVector2 PredictedPos = m_LevelPosition + PenentrationDistance;
		SetLevelPosition(PredictedPos);
	}
}

// *****************************************************************************
void SMEnemy::VCheckCollisions(const Base::cVector2 & PredictedPos)
{
	SMEntity::VCheckCollisions(PredictedPos);
	CheckCollisionInternal("StaticObject");
	CheckCollisionInternal("Bullet");
}

// *****************************************************************************
bool SMEnemy::VTakeDamage(const int Amount)
{
	if(SMEntity::VTakeDamage(Amount))
	{
		SMLevel::Level.AddEnemy();
		SMPlayer::AddScore(m_ScoreGiven);
		return true;
	}
	return false;
}
