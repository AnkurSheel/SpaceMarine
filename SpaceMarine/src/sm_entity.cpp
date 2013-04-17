#include "includes.h"
#include "sm_entity.h"
#include "sm_surface.h"
#include "sm_game.h"
#include "sm_bounds.h"

using namespace Utilities;
using namespace Base;

int SMEntity::m_NextValidID = 0;

// *****************************************************************************
SMEntity::SMEntity(const int ID, const Base::cString & Name)
: m_Name(Name)
, m_pSurface(NULL)
, m_pBounds(NULL)
{
	SetID(ID);
}

// *****************************************************************************
SMEntity::SMEntity(const Base::cString & Name)
: m_Name(Name)
, m_pSurface(NULL)
, m_pBounds(NULL)
{
	SetID(m_NextValidID);
}

// *****************************************************************************
SMEntity::~SMEntity()
{
}

// *****************************************************************************
void SMEntity::SetID(const int iID)
{
	if(iID >= m_NextValidID)
	{
		m_ID = iID;
	}
	else
	{
		Log_Write(ILogger::LT_ERROR, 2, cString(30, "%d is less than valid id. Setting ID to %d", m_ID, m_NextValidID));
		m_ID = m_NextValidID;
	}
	m_NextValidID = m_ID + 1;
}

// *****************************************************************************
bool SMEntity::VInitialize(const Base::cString & FilePath, const bool Collider)
{
	m_pSurface = SMSurface::OnLoad(FilePath);
	if (m_pSurface == NULL)
	{
		return false;
	}
	m_Size.x = static_cast<float>(m_pSurface->w);
	m_Size.y = static_cast<float>(m_pSurface->h);

	if(Collider)
	{
		CreateCollider();
	}
	return true;
}

// *****************************************************************************
bool SMEntity::VInitialize(const Base::cString & FilePath, const int Width,
	const int Height, const int MaxFrames, const bool Collider)
{
	if(VInitialize(FilePath, Collider) == false)
	{
		return false;
	}

	m_Size.x = static_cast<float>(Width);
	m_Size.y = static_cast<float>(Height);
	if(Collider)
	{
		CreateCollider();
	}
	return true;
}

// *****************************************************************************
void SMEntity::VUpdate(const float DeltaTime)
{
}

// *****************************************************************************
void SMEntity::VRender(SDL_Surface * pDisplaySurface)
{
	cVector2 Pos = m_Pos - SMGame::GetCameraPosition();
	if (Pos.x < -200 || Pos.x > SMGame::GetScreenSize().x 
		|| Pos.y < -200 || Pos.y > SMGame::GetScreenSize().y)
	{
		return;
	}
	SMSurface::OnDraw(pDisplaySurface, m_pSurface, static_cast<int>(Pos.x), static_cast<int>(Pos.y));
}

// *****************************************************************************
void SMEntity::VCleanup()
{
	SafeDelete(&m_pBounds);
	SafeFreeSurface(&m_pSurface);
}

void SMEntity::CreateCollider()
{
	SafeDelete(&m_pBounds);
	m_pBounds = DEBUG_NEW SMBounds(cVector2::Zero(), m_Size);
}

void SMEntity::SetPos(const Base::cVector2 & Pos)
{
	if(m_pBounds != NULL)
	{
		m_pBounds->Transalate(Pos - m_Pos);
	}
	m_Pos = Pos;

}