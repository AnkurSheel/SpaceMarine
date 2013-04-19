#include "includes.h"
#include "sm_Player.h"
#include "sm_controls.h"
#include "sm_level.h"
#include "sm_entity_manager.h"
#include "sm_bounds.h"
#include "sm_directories.h"

using namespace Base;
using namespace Utilities;

// *****************************************************************************
SMPlayer::SMPlayer(const Base::cString & Name) 
	: SMEntity(Name)
{
}

// *****************************************************************************
SMPlayer::~SMPlayer()
{

}

// *****************************************************************************
bool SMPlayer::VInitialize()
{
	return Load("Player", SMDirectories::Directories.GetPlayerSprites());
}

// *****************************************************************************
void SMPlayer::VUpdate(const float DeltaTime)
{
	m_Speed = cVector2::Zero();
	if (SMControls::Keys.IsKeyPressed(SDLK_DOWN))
	{
		m_Speed.y = static_cast<float>(m_MaxSpeed);
	}
	if (SMControls::Keys.IsKeyPressed(SDLK_UP))
	{
		m_Speed.y = static_cast<float>(-m_MaxSpeed);
	}
	if (SMControls::Keys.IsKeyPressed(SDLK_RIGHT))
	{
		m_Speed.x = static_cast<float>(m_MaxSpeed);
	}
	if (SMControls::Keys.IsKeyPressed(SDLK_LEFT))
	{
		m_Speed.x = static_cast<float>(-m_MaxSpeed);
	}
	if(!m_Speed.IsZero())
	{
		cVector2 PredictedPos = m_Pos + m_Speed * DeltaTime;
		Clamp<float>(PredictedPos.x, 0, (SMLevel::Level.GetLevelSize().x - m_Size.x));
		Clamp<float>(PredictedPos.y, 0, (SMLevel::Level.GetLevelSize().y - m_Size.y));
		SetPos(PredictedPos);

		CheckCollisions(PredictedPos);

	}
}

// *****************************************************************************
void SMPlayer::CheckCollisions(const cVector2 & PredictedPos)
{
	SMEntityManager::EntityMap::const_iterator Iter;
	cVector2 PenetrationDistance;

	for(Iter = SMEntityManager::EntityManager.GetEntityMap().begin(); Iter != SMEntityManager::EntityManager.GetEntityMap().end(); Iter++)
	{
		SMEntity * pEntity = (Iter->second);
		if(pEntity != NULL && this != pEntity && SMBounds::CheckCollision(m_pBounds, pEntity->GetBounds(), PenetrationDistance))
		{
			cVector2 PredictedPos = m_Pos + PenetrationDistance;
			SetPos(PredictedPos);
		}
	}
}
