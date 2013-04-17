#include "includes.h"
#include "sm_Player.h"
#include "sm_controls.h"
#include "sm_surface.h"
#include "sm_level.h"
#include "sm_game.h"
#include "sm_entity_manager.h"
#include "sm_bounds.h"

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
void SMPlayer::VUpdate(const float DeltaTime)
{
	m_Speed = cVector2::Zero();
	if (SMControls::Keys.IsKeyPressed(SDLK_DOWN))
	{
		m_Speed.y = 50;
	}
	if (SMControls::Keys.IsKeyPressed(SDLK_UP))
	{
		m_Speed.y = -50;
	}
	if (SMControls::Keys.IsKeyPressed(SDLK_RIGHT))
	{
		m_Speed.x = 50;
	}
	if (SMControls::Keys.IsKeyPressed(SDLK_LEFT))
	{
		m_Speed.x = -50;
	}
	if(!m_Speed.IsZero())
	{
		cVector2 PredictedPos = m_Pos + m_Speed * DeltaTime;
		Clamp<float>(PredictedPos.x, 0, (SMLevel::Level.GetLevelSize().x - m_Size.x));
		Clamp<float>(PredictedPos.y, 0, (SMLevel::Level.GetLevelSize().y - m_Size.y));
		SetPos(PredictedPos);

		SMEntityManager::EntityMap::const_iterator Iter;
		cVector2 PenetrationDistance;
		for(Iter = SMEntityManager::m_EntityMap.begin(); Iter != SMEntityManager::m_EntityMap.end(); Iter++)
		{
			SMEntity * pEntity = (Iter->second);
			if(pEntity != NULL && this != pEntity && SMBounds::CheckCollision(m_pBounds, pEntity->GetBounds(), PenetrationDistance))
			{
				Log_Write(ILogger::LT_DEBUG, 2, pEntity->GetName() + cString(100, "Collision Distance (%f, %f)", PenetrationDistance.x, PenetrationDistance.y));
				PredictedPos += PenetrationDistance;
				SetPos(PredictedPos);
			}
		}
	}
}

// *****************************************************************************
void SMPlayer::VRender(SDL_Surface * pDisplaySurface)
{
	SMSurface::OnDraw(pDisplaySurface, m_pSurface, static_cast<int>(m_Pos.x - SMGame::GetCameraPosition().x), static_cast<int>(m_Pos.y - SMGame::GetCameraPosition().y), 0, 0, 64, 100);
}