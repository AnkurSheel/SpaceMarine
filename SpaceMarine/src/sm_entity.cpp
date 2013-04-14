#include "includes.h"
#include "sm_entity.h"
#include "sm_surface.h"

using namespace Utilities;
using namespace Base;

int SMEntity::m_NextValidID = 0;

// *****************************************************************************
SMEntity::SMEntity(const int ID, const Base::cString & Name)
: m_Name(Name)
, m_pSurface(NULL)
{
	SetID(ID);
}

// *****************************************************************************
SMEntity::SMEntity(const Base::cString & Name)
: m_Name(Name)
, m_pSurface(NULL)
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
bool SMEntity::VOnLoad(const Base::cString & FilePath, const int Width,
	const int Height, const int MaxFrames)
{
	m_Size.x = Width;
	m_Size.y = Height;

	m_pSurface = SMSurface::OnLoad(FilePath);
	if (m_pSurface == NULL)
	{
		return false;
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
	SMSurface::OnDraw(pDisplaySurface, m_pSurface, static_cast<int>(m_Pos.x), static_cast<int>(m_Pos.y));
}

// *****************************************************************************
void SMEntity::VCleanup()
{
	if (m_pSurface != NULL)
	{
		SDL_FreeSurface(m_pSurface);
		m_pSurface = NULL;
	}
}
