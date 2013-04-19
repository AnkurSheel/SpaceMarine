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
	return Load(m_Name, SMDirectories::Directories.GetObjectSprites());
}
