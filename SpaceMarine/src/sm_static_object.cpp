#include "includes.h"
#include "sm_static_object.h"
#include "sm_directories.h"

using namespace Base;
using namespace Utilities;

// *****************************************************************************
SMStaticObject::SMStaticObject(const cString & Type, const cString & SubType,
	const cString & Name)
	: SMEntity(Type, SubType, Name)
{

}

// *****************************************************************************
SMStaticObject::~SMStaticObject()
{

}

// *****************************************************************************
bool SMStaticObject::VInitialize()
{
	return Load(SMDirectories::Directories.GetObjectSprites());
}
