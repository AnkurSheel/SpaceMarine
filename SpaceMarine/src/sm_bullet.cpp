#include "includes.h"
#include "sm_bullet.h"
#include "sm_directories.h"
#include "sm_entity_manager.h"
#include <XMLFileIO.hxx>
#include "sm_config.h"
#include "sm_game.h"

using namespace Base;

// *****************************************************************************
SMBullet::SMBullet(const cString & Type, const cString & SubType, const cString & Name)
	: SMEntity(Type, SubType, Name)
	, m_FireDelay(0.0f)
{

}

// *****************************************************************************
SMBullet::~SMBullet()
{

}

// *****************************************************************************
bool SMBullet::VInitialize()
{
	if(!Load(SMDirectories::Directories.GetObjectSprites()))
	{
		return false;
	}
	m_FireDelay = (SMConfig::GetConfigLoader()->VGetNodeAttributeAsInt(m_SubType, "FireDelay") / 1000.0f);
	m_Damage = SMConfig::GetConfigLoader()->VGetNodeAttributeAsInt(m_SubType, "Damage");
	return true;
}

// *****************************************************************************
void SMBullet::Initialize(const Base::cVector2 & ParentPosition, const Base::cVector2 & Direction)
{
	VInitialize();
	SetLevelPosition(ParentPosition + Direction * 25);
	m_Speed = Direction * m_MaxSpeed;
}

// *****************************************************************************
void SMBullet::VCheckCollisions(const Base::cVector2 & PredictedPos)
{
	SMEntity::VCheckCollisions(PredictedPos);
	CheckCollisionInternal("StaticObject");
	CheckCollisionInternal("Enemy");
}

// *****************************************************************************
void SMBullet::VOnCollided(SMEntity * const pEntity, const Base::cVector2 & PenentrationDistance)
{
	SMEntity::VOnCollided(pEntity, PenentrationDistance);
	if (pEntity->GetType().CompareInsensitive("StaticObject"))
	{
		SMEntityManager::EntityManager.UnRegisterEntity(this);
	}
	else if (pEntity->GetType().CompareInsensitive("Enemy"))
	{
		SMEntityManager::EntityManager.UnRegisterEntity(this);
		pEntity->VTakeDamage(m_Damage);
	}
}

// *****************************************************************************
void SMBullet::VUpdate(const float DeltaTime)
{
	if (GetDead())
	{
		return;
	}
	cVector2 Pos = m_LevelPosition - SMGame::GetCameraPosition();
	if (Pos.x <= 0 || Pos.x >= SMGame::GetScreenSize().x 
		|| Pos.y <= 0 || Pos.y >= SMGame::GetScreenSize().y)
	{
		SMEntityManager::EntityManager.UnRegisterEntity(this);
	}
	SMEntity::VUpdate(DeltaTime);
}
