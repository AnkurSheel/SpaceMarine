#include "includes.h"
#include "sm_Player.h"
#include "sm_controls.h"
#include "sm_surface.h"
#include "sm_level.h"
#include "sm_game.h"

using namespace Base;
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
}

// *****************************************************************************
void SMPlayer::VRender(SDL_Surface * pDisplaySurface)
{
	SMSurface::OnDraw(pDisplaySurface, m_pSurface, static_cast<int>(m_Pos.x - SMGame::GetCameraPosition().x), static_cast<int>(m_Pos.y - SMGame::GetCameraPosition().y), 0, 0, 64, 100);
}
