#include "includes.h"
#include "sm_Player.h"
#include "sm_controls.h"
#include "sm_surface.h"

using namespace Base;
// *****************************************************************************
SMPlayer::SMPlayer(const cString & Name)
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
		m_Pos.y += (20 * DeltaTime);
	}
	if (SMControls::Keys.IsKeyPressed(SDLK_UP))
	{
		m_Pos.y -= (20 * DeltaTime);
	}
	if (SMControls::Keys.IsKeyPressed(SDLK_RIGHT))
	{
		m_Pos.x += (20 * DeltaTime);
	}
	if (SMControls::Keys.IsKeyPressed(SDLK_LEFT))
	{
		m_Pos.x -= (20 * DeltaTime);
	}
}

// *****************************************************************************
void SMPlayer::VRender(SDL_Surface * pDisplaySurface)
{
	SMSurface::OnDraw(pDisplaySurface, m_pSurface, static_cast<int>(m_Pos.x), static_cast<int>(m_Pos.y), 0, 0, 64, 100);
}
