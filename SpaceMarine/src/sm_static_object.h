// *****************************************************************************
//  sm_static_object   version:  1.0   Ankur Sheel  date: 2013/04/16
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_static_object_h__
#define sm_static_object_h__

#include "sm_entity.h"

class SMStaticObject
	: public SMEntity
{
public:
	SMStaticObject(const Base::cString & Type, const Base::cString & SubType,
		const Base::cString & Name);
	~SMStaticObject();
	bool VInitialize();
};
#endif // sm_static_object_h__