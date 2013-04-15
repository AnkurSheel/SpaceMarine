#include "includes.h"
#include "sm_Player.h"
#include "sm_controls.h"
#include "sm_surface.h"
#include "sm_level.h"

using namespace Base;
// *****************************************************************************
SMPlayer::SMPlayer(const cString & Name, const cVector2 & ScreenSize)
	: SMEntity(Name)
	, m_ScreenSize(ScreenSize)
{

}

// *****************************************************************************
SMPlayer::~SMPlayer()
{

}

// *****************************************************************************
void SMPlayer::VUpdate(const float DeltaTime)
{
	if (SMControls::Keys.IsKeyPressed(SDLK_DOWN))
	{
		m_Pos.y += (50 * DeltaTime);
	}
	if (SMControls::Keys.IsKeyPressed(SDLK_UP))
	{
		m_Pos.y -= (50 * DeltaTime);
	}
	if (SMControls::Keys.IsKeyPressed(SDLK_RIGHT))
	{
		m_Pos.x += (50 * DeltaTime);
	}
	if (SMControls::Keys.IsKeyPressed(SDLK_LEFT))
	{
		m_Pos.x -= (50 * DeltaTime);
	}

	Clamp<float>(m_Pos.x, 0, (SMLevel::Level.GetLevelSize().x - m_Size.x));
	Clamp<float>(m_Pos.y, 0, (SMLevel::Level.GetLevelSize().y - m_Size.y));
	
	m_PositionInLevel = m_Pos + (m_Size * 0.5f) - (m_ScreenSize * 0.5f);

	Clamp<float>(m_PositionInLevel.x, 0, (SMLevel::Level.GetLevelSize().x - m_ScreenSize.x));
	Clamp<float>(m_PositionInLevel.y, 0, (SMLevel::Level.GetLevelSize().y - m_ScreenSize.y));
}

// *****************************************************************************
void SMPlayer::VRender(SDL_Surface * pDisplaySurface)
{
	SMSurface::OnDraw(pDisplaySurface, m_pSurface, static_cast<int>(m_Pos.x - m_PositionInLevel.x), static_cast<int>(m_Pos.y - m_PositionInLevel.y), 0, 0, 64, 100);
}
