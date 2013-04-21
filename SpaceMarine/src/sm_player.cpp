#include "includes.h"
#include "sm_Player.h"
#include "sm_controls.h"
#include "sm_level.h"
#include "sm_entity_manager.h"
#include "sm_bounds.h"
#include "sm_directories.h"
#include <sdl_ttf.h>
#include "sm_surface.h"
#include "sm_crosshair.h"
#include "sm_bullet.h"
#include "sm_game.h"

using namespace Base;
using namespace Utilities;

SMPlayer * SMPlayer::m_pInstance = NULL;

// *****************************************************************************
SMPlayer::SMPlayer(const cString & Type, const cString & SubType, const cString & Name) 
	: SMEntity(Type, SubType, Name)
	, m_Score(0)
	, m_pScoreSurface(NULL)
	, m_pHealthSurface(NULL)
	, m_pFont(NULL)
	, m_pCrossHair(NULL)
	, m_Angle(0)
	, m_bDirty(false)
	, m_CanFire(false)
{
	m_TextColor.r = 255;
	m_TextColor.g = 255;
	m_TextColor.b = 255;
}

// *****************************************************************************
SMPlayer::~SMPlayer()
{

}

// *****************************************************************************
bool SMPlayer::VInitialize()
{
	if(Load(SMDirectories::Directories.GetPlayerSprites()) == false)
	{
		return false;
	}
	cString Path = SMDirectories::Directories.GetFonts() + "score.ttf";
	m_pFont = TTF_OpenFont(Path.GetData(), 18);
	m_ScoreText = cString(100, "Score : %d", m_Score);
	m_HealthText = cString(100, "Health : %d", m_Health);

	m_pCrossHair = DEBUG_NEW SMCrosshair();
	m_pCrossHair->Initialize(SMDirectories::Directories.GetPlayerSprites() + "crosshairs.png",
		cVector2(100, 0));
	SetLevelPosition(SMLevel::Level.GetPlayerSpawnPoint());
	m_Direction = cVector2::GetDirection(m_Angle);
	m_bDirty = true;
	m_CanFire = true;

	m_pInstance = this;
	return true;
}

// *****************************************************************************
void SMPlayer::VUpdate(const float DeltaTime)
{
	if (GetDead())
	{
		return;
	}

	m_Speed = cVector2::Zero();
	if (SMControls::Keys.IsKeyPressed(SDLK_DOWN))
	{
		m_Speed = m_Direction * m_MaxSpeed;
		m_Speed.NegTo();
		m_bDirty = true;
	}
	if (SMControls::Keys.IsKeyPressed(SDLK_UP))
	{
		m_Speed = m_Direction * m_MaxSpeed;
		m_bDirty = true;
	}
	if (SMControls::Keys.IsKeyPressed(SDLK_RIGHT))
	{
		m_Angle += DegtoRad(1);
		ClampToTwoPi(m_Angle);
		m_Direction = cVector2::GetDirection(m_Angle);
		m_bDirty = true;
	}
	if (SMControls::Keys.IsKeyPressed(SDLK_LEFT))
	{
		m_Angle -= DegtoRad(1);
		ClampToTwoPi(m_Angle);
		m_Direction = cVector2::GetDirection(m_Angle);
		m_bDirty = true;
	}
	if(m_CanFire && (SMControls::Keys.IsKeyPressed(SDLK_SPACE)))
	{
		m_CanFire = false;
		SMEntity * pEntity = SMEntityManager::EntityManager.RegisterEntity("Projectile", "Bullet", "Bullet");
		if (pEntity)
		{
			SMBullet * pBullet = dynamic_cast<SMBullet *>(pEntity);
			pBullet->Initialize(m_LevelPosition, m_Direction);
			m_LastFireTime = pBullet->GetFireDelay();
		}
	}

	if(m_LastFireTime > 0.0f)
	{
		m_LastFireTime -= DeltaTime;
		if(m_LastFireTime <= 0.0f)
		{
			m_CanFire = true;
		}
	}

	if (m_bDirty)
	{
		m_bDirty = false;
		if (m_pCrossHair)
		{
			m_pCrossHair->UpdatePosition(m_LevelPosition, m_Direction);
		}
	}

	SMEntity::VUpdate(DeltaTime);
}

// *****************************************************************************
void SMPlayer::VRender(SDL_Surface * pDisplaySurface)
{
	SMEntity::VRender(pDisplaySurface);
	if (m_pFont)
	{
		m_pScoreSurface = TTF_RenderText_Solid(m_pFont, m_ScoreText.GetData(), m_TextColor);
		m_pHealthSurface = TTF_RenderText_Solid(m_pFont, m_HealthText.GetData(), m_TextColor);

		SMSurface::OnDraw(pDisplaySurface, m_pScoreSurface, 0, 0);
		SMSurface::OnDraw(pDisplaySurface, m_pHealthSurface, SMGame::GetScreenSize().x - m_pHealthSurface->w, 0);
	}
	
	if (m_pCrossHair)
	{
		m_pCrossHair->Render(pDisplaySurface);
	}
}

// *****************************************************************************
void SMPlayer::VCleanup()
{
	if(m_pFont)
	{
		TTF_CloseFont(m_pFont);
		m_pFont = NULL;
	}
	SafeDelete(&m_pCrossHair);
	SafeFreeSurface(&m_pScoreSurface);
	SafeFreeSurface(&m_pHealthSurface);
	SMEntity::VCleanup();
}

// *****************************************************************************
void SMPlayer::VCheckCollisions(const cVector2 & PredictedPos)
{
	SMEntity::VCheckCollisions(PredictedPos);
	CheckCollisionInternal("StaticObject");
	CheckCollisionInternal("Enemy");
}

// *****************************************************************************
void SMPlayer::VOnCollided(SMEntity * const pEntity, const Base::cVector2 & PenentrationDistance)
{
	SMEntity::VOnCollided(pEntity, PenentrationDistance);
	if (pEntity->GetType().CompareInsensitive("StaticObject"))
	{
		cVector2 PredictedPos = m_LevelPosition + PenentrationDistance;
		SetLevelPosition(PredictedPos);
	}
	if (pEntity->GetType().CompareInsensitive("Enemy"))
	{
	}
}

// *****************************************************************************
void SMPlayer::AddScore(const int Score)
{
	if (m_pInstance != NULL)
	{
		m_pInstance->m_Score += Score;
		m_pInstance->m_ScoreText = cString(100, "Score : %d", m_pInstance->m_Score);
	}
}
