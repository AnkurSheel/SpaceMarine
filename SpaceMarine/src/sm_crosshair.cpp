#include "includes.h"
#include "sm_crosshair.h"
#include "sm_surface.h"
#include "sm_game.h"

using namespace Base;

// *****************************************************************************
SMCrosshair::SMCrosshair()
	: m_pSurface(NULL)
{

}

// *****************************************************************************
SMCrosshair::~SMCrosshair()
{
	SafeFreeSurface(&m_pSurface);
}

// *****************************************************************************
bool SMCrosshair::Initialize(const cString & FilePath, const cVector2 & Offset)
{
	m_pSurface = SMSurface::OnLoad(FilePath);
	if (m_pSurface == NULL)
	{
		return false;
	}
	return true;
}

// *****************************************************************************
void SMCrosshair::Render(SDL_Surface * pDisplaySurface)
{
	if (m_pSurface)
	{
		SMSurface::OnDraw(pDisplaySurface, m_pSurface, m_Position.x - SMGame::GetCameraPosition().x, 
			m_Position.y - SMGame::GetCameraPosition().y, 320, 192, 64, 64);
	}
}

// *****************************************************************************
void SMCrosshair::UpdatePosition(const Base::cVector2 & ParentPosition, const Base::cVector2 & Direction)
{
	//float s = sin(Angle);
	//float c = cos(Angle);

	//m_Position = m_Offset;

	//// rotate point
	//float Xnew = m_Position.x * c - m_Position.y * s;
	//float Ynew = -m_Position.y * c + m_Position.x * s;

	//m_Position.x = Xnew + ParentPosition.x;
	//m_Position.y = Ynew + ParentPosition.y;
	m_Position = ParentPosition - cVector2(16, 16) + Direction * 125;
}
