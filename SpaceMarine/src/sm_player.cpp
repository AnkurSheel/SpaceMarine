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

using namespace Base;
using namespace Utilities;

// *****************************************************************************
SMPlayer::SMPlayer(const cString & Type, const cString & SubType, const cString & Name) 
	: SMEntity(Type, SubType, Name)
	, m_Score(0)
	, m_pScoreSurface(NULL)
	, m_pFont(NULL)
	, m_pCrossHair(NULL)
	, m_Angle(0)
	, m_bDirty(false)
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

	m_pCrossHair = DEBUG_NEW SMCrosshair();
	m_pCrossHair->Initialize(SMDirectories::Directories.GetPlayerSprites() + "crosshairs.png",
		cVector2(100, 0));
	SetPos(SMLevel::Level.GetPlayerSpawnPoint());
	m_bDirty = true;
	return true;
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
	if(SMControls::Keys.IsKeyPressed(SDLK_q))
	{
		m_Angle -= DegtoRad(1);
		ClampToTwoPi(m_Angle);
		m_bDirty = true;
	}
	if(SMControls::Keys.IsKeyPressed(SDLK_a))
	{
		m_Angle += DegtoRad(1);
		ClampToTwoPi(m_Angle);
		m_bDirty = true;
	}
	if(!m_Speed.IsZero())
	{
		m_bDirty = true;
		cVector2 PredictedPos = m_LevelPosition + m_Speed * DeltaTime;
		Clamp<float>(PredictedPos.x, 0, (SMLevel::Level.GetLevelSize().x - m_Size.x));
		Clamp<float>(PredictedPos.y, 0, (SMLevel::Level.GetLevelSize().y - m_Size.y));
		SetPos(PredictedPos);
		CheckCollisions(PredictedPos);
	}
	if (m_bDirty)
	{
		m_bDirty = false;
		if (m_pCrossHair)
		{
			m_pCrossHair->UpdatePosition(m_LevelPosition, m_Angle);
		}
	}
}

// *****************************************************************************
void SMPlayer::VRender(SDL_Surface * pDisplaySurface)
{
	SMEntity::VRender(pDisplaySurface);
	if (m_pFont)
	{
		m_pScoreSurface = TTF_RenderText_Solid(m_pFont, m_ScoreText.GetData(), m_TextColor);
	}
	SMSurface::OnDraw(pDisplaySurface, m_pScoreSurface, 0, 0);
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
	SMEntity::VCleanup();
}

// *****************************************************************************
void SMPlayer::CheckCollisions(const cVector2 & PredictedPos)
{
	CheckCollisionInternal("StaticObject");
	CheckCollisionInternal("Enemy");
}

// *****************************************************************************
void SMPlayer::VOnCollided(const cString & Type, const cVector2 & PenentrationDistance)
{
	SMEntity::VOnCollided(Type, PenentrationDistance);
	if (Type.CompareInsensitive("StaticObjects"))
	{
		cVector2 PredictedPos = m_LevelPosition + PenentrationDistance;
		SetPos(PredictedPos);
	}
	if (Type.CompareInsensitive("Enemy"))
	{
	}
}