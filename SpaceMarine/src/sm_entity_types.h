// *****************************************************************************
//  sm_entity_type   version:  1.0   Ankur Sheel  date: 2013/04/22
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_entity_type_h__
#define sm_entity_type_h__

class SMEntityTypes
	: public Base::cNonCopyable
{
public:
	static const Base::cHashedString StaticObject;
	static const Base::cHashedString Player;
	static const Base::cHashedString Enemy;
	static const Base::cHashedString PlayerBullet;
	static const Base::cHashedString EnemyBullet;
private:
	SMEntityTypes();
	~SMEntityTypes();
public:
};
#endif // sm_entity_type_h__