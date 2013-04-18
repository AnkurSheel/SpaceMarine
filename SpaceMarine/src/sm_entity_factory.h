// *****************************************************************************
//  sm_entity_factory   version:  1.0   Ankur Sheel  date: 2013/04/17
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_entity_factory_h__
#define sm_entity_factory_h__

class SMEntity;

class SMEntityFactory
	: public Base::cNonCopyable
{
public:
	SMEntityFactory();
	~SMEntityFactory();
	SMEntity * CreateEntity(const Base::cString & Type, const Base::cString & Name);
};
#endif // sm_entity_factory_h__