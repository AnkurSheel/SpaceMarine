#include "includes.h"
#include "sm_enemy.h"
#include "sm_directories.h"
#include "sm_entity_manager.h"
#include "sm_level.h"
#include "sm_Player.h"
#include "sm_config.h"
#include <XMLFileIO.hxx>
#include <RandomGenerator.hxx>
#include "sm_game.h"

using namespace Base;
using namespace Utilities;

// *****************************************************************************
SMEnemy::SMEnemy(const cString & Type, const cString & SubType, const cString & Name)
	: SMEntity(Type, SubType, Name)
	, m_ScoreGiven(0)
	, m_ChangeDirectionTimer(0.0f)
	, m_LastDirectionChangeTime(0.0f)
	, m_Damage(0)
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
	m_ChangeDirectionTimer = (SMConfig::GetConfigLoader()->VGetNodeAttributeAsInt(m_SubType, "DirectionTimer") / 1000.0f);
	m_Damage = SMConfig::GetConfigLoader()->VGetNodeAttributeAsInt(m_SubType, "Damage");
	GetNewDirection();

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
		GetNewDirection();
	}
	if (pEntity->GetType().CompareInsensitive("Player"))
	{
		VTakeDamage(m_Health);
		pEntity->VTakeDamage(m_Damage);
	}
}

// *****************************************************************************
void SMEnemy::VUpdate(const float DeltaTime)
{
	m_LastDirectionChangeTime -= DeltaTime;
	cVector2 Pos = m_LevelPosition - SMGame::GetCameraPosition();
	if (GetDead() || (Pos.x < -200 || Pos.x > SMGame::GetScreenSize().x 
		|| Pos.y < -200 || Pos.y > SMGame::GetScreenSize().y))
	{
		return;
	}

	if (m_LastDirectionChangeTime < 0.0f)
	{
		GetNewDirection();
	}
	else if (m_LevelPosition.x <= 0 || m_LevelPosition.y <= 0 
		|| m_LevelPosition.x >= (SMLevel::Level.GetLevelSize().x - m_Size.x)
		|| m_LevelPosition.y >= (SMLevel::Level.GetLevelSize().y - m_Size.y))
	{
		GetNewDirection();
	}

	SMEntity::VUpdate(DeltaTime);
}

// *****************************************************************************
void SMEnemy::VCheckCollisions(const Base::cVector2 & PredictedPos)
{
	SMEntity::VCheckCollisions(PredictedPos);
	CheckCollisionInternal("StaticObject");
	CheckCollisionInternal("Bullet");
	CheckCollisionInternal("Player");
}

// *****************************************************************************
bool SMEnemy::VTakeDamage(const int Amount)
{
	if(SMEntity::VTakeDamage(Amount))
	{
		SMLevel::Level.EnemyRemoved();
		SMPlayer::AddScore(m_ScoreGiven);
		return true;
	}
	return false;
}

// *****************************************************************************
void SMEnemy::GetNewDirection()
{
	if (SMGame::GetRandomGenerator() != NULL)
	{
		cVector2 Direction(SMGame::GetRandomGenerator()->Random(), SMGame::GetRandomGenerator()->Random());
		int iSpeedDirection = SMGame::GetRandomGenerator()->Random(2);
		if (iSpeedDirection == 1)
		{
			Direction.x = -Direction.x;
		}

		iSpeedDirection = SMGame::GetRandomGenerator()->Random(2);
		if (iSpeedDirection == 1)
		{
			Direction.y = -Direction.y;
		}
		m_LastDirectionChangeTime = m_ChangeDirectionTimer;
		m_Speed = Direction * m_MaxSpeed;
	}
}
