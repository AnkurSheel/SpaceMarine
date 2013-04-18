#include "includes.h"
#include "sm_static_object.h"
#include "sm_directories.h"
#include <ParamLoaders.hxx>
#include "sm_game.h"

using namespace Base;
using namespace Utilities;

// *****************************************************************************
SMStaticObject::SMStaticObject(const Base::cString & Name)
	: SMEntity(Name)
{

}

// *****************************************************************************
SMStaticObject::~SMStaticObject()
{

}

// *****************************************************************************
bool SMStaticObject::VInitialize()
{
	cString ObjectSprite = SMGame::GetConfig()->VGetParameterValueAsString("-" + m_Name + "Sprite", "");
	if (ObjectSprite.IsEmpty())
	{
		Log_Write(ILogger::LT_ERROR, 1, "No sprite file defined for Static Object " 
			+ m_Name + " . Parameter : " + m_Name + "Sprite");
		return false;
	}

	bool Collidable = SMGame::GetConfig()->VGetParameterValueAsBool("-" + m_Name + "Collider", false);
	return Initialize(SMDirectories::Directories.GetObjectSprites() + ObjectSprite, Collidable);
}
