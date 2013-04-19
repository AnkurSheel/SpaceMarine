#include "includes.h"
#include "sm_static_object.h"
#include "sm_directories.h"
#include <XMLFileIO.hxx>
#include "sm_config.h"

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
	cString ObjectSprite = SMConfig::GetConfigLoader()->VGetNodeAttribute(m_Name, "Sprite");
	if (ObjectSprite.IsEmpty())
	{
		Log_Write(ILogger::LT_ERROR, 1, "No sprite file defined for Static Object " 
			+ m_Name + " . Parameter : " + m_Name + "Sprite");
		return false;
	}

	bool Collidable = SMConfig::GetConfigLoader()->VGetNodeAttributeAsBool(m_Name, "Collidable");
	return Initialize(SMDirectories::Directories.GetObjectSprites() + ObjectSprite, Collidable);
}
