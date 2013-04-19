#include "includes.h"
#include "sm_entity.h"
#include "sm_surface.h"
#include "sm_game.h"
#include "sm_bounds.h"
#include "sm_config.h"
#include <XMLFileIO.hxx>

using namespace Utilities;
using namespace Base;

int SMEntity::m_NextValidID = 0;

// *****************************************************************************
SMEntity::SMEntity(const Base::cString & Type, const cString & Name)
: m_Name(Name)
, m_Type(Type)
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
bool SMEntity::Initialize(const cString & FilePath, const bool Collider)
{
	if(FilePath.IsEmpty())
	{
		Log_Write(ILogger::LT_ERROR, 1, "File Path is empty");
		return false;
	}

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
bool SMEntity::Initialize(const cString & FilePath, const int Width,
	const int Height, const bool Collider)
{
	if(Initialize(FilePath, Collider) == false)
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
	SMSurface::OnDraw(pDisplaySurface, m_pSurface, static_cast<int>(m_Pos.x - SMGame::GetCameraPosition().x),
		static_cast<int>(m_Pos.y - SMGame::GetCameraPosition().y), static_cast<int>(m_SpritePos.x), 
		static_cast<int>(m_SpritePos.y), static_cast<int>(m_Size.x), static_cast<int>(m_Size.y));
}

// *****************************************************************************
void SMEntity::VCleanup()
{
	SafeDelete(&m_pBounds);
	SafeFreeSurface(&m_pSurface);
}

// *****************************************************************************
void SMEntity::CreateCollider()
{
	SafeDelete(&m_pBounds);
	m_pBounds = DEBUG_NEW SMBounds(cVector2::Zero(), m_Size);
}

// *****************************************************************************
void SMEntity::SetPos(const cVector2 & Pos)
{
	if(m_pBounds != NULL)
	{
		m_pBounds->Transalate(Pos - m_Pos);
	}
	m_Pos = Pos;

}

// *****************************************************************************
bool SMEntity::Load(const cString & Name, const cString & SpriteDirectory)
{
	cString Sprite = SMConfig::GetConfigLoader()->VGetNodeAttribute(Name, "Sprite");
	if (Sprite.IsEmpty())
	{
		Log_Write(ILogger::LT_WARNING, 1, "No sprite file defined for " + Name + ". Attribute - Sprite");
	}
	
	m_MaxSpeed = SMConfig::GetConfigLoader()->VGetNodeAttributeAsInt(Name, "Speed");
	m_SpritePos.x = SMConfig::GetConfigLoader()->VGetNodeAttributeAsInt(Name, "XPos");
	m_SpritePos.y = SMConfig::GetConfigLoader()->VGetNodeAttributeAsInt(Name, "YPos");

	int Width = SMConfig::GetConfigLoader()->VGetNodeAttributeAsInt(Name, "Width");
	int Height = SMConfig::GetConfigLoader()->VGetNodeAttributeAsInt(Name, "Height");
	bool Collidable = SMConfig::GetConfigLoader()->VGetNodeAttributeAsBool(Name, "Collidable");

	if (Width == 0 || Height == 0)
	{
		return Initialize(SpriteDirectory + Sprite, Collidable);
	}
	else
	{
		return Initialize(SpriteDirectory + Sprite, Width, Height, Collidable);
	}

	return true;
}