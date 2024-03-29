#include "includes.h"
#include "sm_entity.h"
#include "sm_surface.h"
#include "sm_game.h"
#include "sm_bounds.h"
#include "sm_config.h"
#include <XMLFileIO.hxx>
#include "sm_entity_manager.h"
#include "sm_level.h"

using namespace Utilities;
using namespace Base;

int SMEntity::m_NextValidID = 0;

// *****************************************************************************
SMEntity::SMEntity(const cString & Type, const cString & SubType, const cString & Name)
: m_Name(Name)
, m_Type(Type)
, m_SubType(SubType)
, m_pSurface(NULL)
, m_pBounds(NULL)
, m_Health(0)
, m_MaxSpeed(0)
{
	SetID(m_NextValidID);
}

// *****************************************************************************
SMEntity::~SMEntity()
{
	VCleanup();
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
	if (GetDead())
	{
		return;
	}

	if(!m_Speed.IsZero())
	{
		cVector2 PredictedPos = m_LevelPosition + m_Speed * DeltaTime;
		Clamp<float>(PredictedPos.x, 0, (SMLevel::Level.GetLevelSize().x - m_Size.x));
		Clamp<float>(PredictedPos.y, 0, (SMLevel::Level.GetLevelSize().y - m_Size.y));
		SetLevelPosition(PredictedPos);
	}
}

// *****************************************************************************
void SMEntity::VRender(SDL_Surface * pDisplaySurface)
{
	cVector2 Pos = m_LevelPosition - SMGame::GetCameraPosition();
	if (Pos.x < -200 || Pos.x > SMGame::GetScreenSize().x 
		|| Pos.y < -200 || Pos.y > SMGame::GetScreenSize().y)
	{
		return;
	}
	SMSurface::OnDraw(pDisplaySurface, m_pSurface, static_cast<int>(m_LevelPosition.x - SMGame::GetCameraPosition().x),
		static_cast<int>(m_LevelPosition.y - SMGame::GetCameraPosition().y), static_cast<int>(m_SpritePos.x), 
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
void SMEntity::SetLevelPosition(const cVector2 & Pos)
{
	if(m_pBounds != NULL)
	{
		m_pBounds->Transalate(Pos - m_LevelPosition);
	}
	m_LevelPosition = Pos;
	VCheckCollisions(m_LevelPosition);

}

// *****************************************************************************
bool SMEntity::Load(const cString & SpriteDirectory)
{
	cString Sprite = SMConfig::GetConfigLoader()->VGetNodeAttribute(m_SubType, "Sprite");
	if (Sprite.IsEmpty())
	{
		Log_Write(ILogger::LT_WARNING, 1, "No sprite file defined for " + m_SubType + ". Attribute - Sprite");
	}
	
	m_MaxSpeed = SMConfig::GetConfigLoader()->VGetNodeAttributeAsInt(m_SubType, "Speed");
	m_SpritePos.x = static_cast<float>(SMConfig::GetConfigLoader()->VGetNodeAttributeAsInt(m_SubType, "XPos"));
	m_SpritePos.y = static_cast<float>(SMConfig::GetConfigLoader()->VGetNodeAttributeAsInt(m_SubType, "YPos"));

	int Width = SMConfig::GetConfigLoader()->VGetNodeAttributeAsInt(m_SubType, "Width");
	int Height = SMConfig::GetConfigLoader()->VGetNodeAttributeAsInt(m_SubType, "Height");
	bool Collidable = SMConfig::GetConfigLoader()->VGetNodeAttributeAsBool(m_SubType, "Collidable");
	m_Health = SMConfig::GetConfigLoader()->VGetNodeAttributeAsInt(m_SubType, "Health");

	if (m_Health == 0)
	{
		m_Health = MaxInt;
	}

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

// *****************************************************************************
void SMEntity::CheckCollisionInternal(const cHashedString & Type)
{
	SMEntity * pEntity = NULL;
	SMEntityManager::EntityList List;
	Base::cVector2 PenentrationDistance;
	SMEntityManager::EntityManager.GetEntitiesOfType(Type, List);
	SMEntityManager::EntityList::const_iterator ListIter;
	for (ListIter = List.begin(); ListIter != List.end(); ListIter++)
	{
		pEntity = *ListIter;
		if(pEntity != NULL && this != pEntity && !pEntity->GetDead() &&
			SMBounds::CheckCollision(m_pBounds, pEntity->GetBounds(), PenentrationDistance))
		{
			VOnCollided(pEntity, PenentrationDistance);
			pEntity->VOnCollided(this, PenentrationDistance);
		}
		if(GetDead())
		{
			break;
		}

	}
}

// *****************************************************************************
void SMEntity::VOnCollided(SMEntity * const pEntity, const cVector2 & PenentrationDistance)
{

}

// *****************************************************************************
void SMEntity::VCheckCollisions(const Base::cVector2 & PredictedPos)
{

}

// *****************************************************************************
bool SMEntity::VTakeDamage(const int Amount)
{
	if (GetDead())
	{
		return false;
	}
	m_Health -= Amount;
	if (GetDead())
	{
		SMEntityManager::EntityManager.UnRegisterEntity(this);
	}
	return GetDead();
}
