#include "includes.h"
#include "sm_static_object.h"
#include "sm_directories.h"

using namespace Base;
using namespace Utilities;

// *****************************************************************************
SMStaticObject::SMStaticObject(const Base::cString & Type, const Base::cString & Name)
	: SMEntity(Type, Name)
{

}

// *****************************************************************************
SMStaticObject::~SMStaticObject()
{

}

// *****************************************************************************
bool SMStaticObject::VInitialize()
{
	return Load(m_Name, SMDirectories::Directories.GetObjectSprites());
}
