// *****************************************************************************
//  sm_level   version:  1.0   Ankur Sheel  date: 2013/04/14
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_level_h__
#define sm_level_h__

#include <NonCopyable.h>
#include <Vector2.h>
#include <list>

namespace Utilities
{
	class IXMLFileIO;
	class ITimer;
}

class SMLevel
	: public Base::cNonCopyable
{
public:
	bool Initialize(const Base::cString & LevelName);
	Base::cString GetBackground() const { return m_Background; }
	Base::cVector2 GetLevelSize() const { return m_LevelSize; }
	Base::cVector2 GetPlayerSpawnPoint() const { return m_PlayerSpawnPoint; }
	void Update(const float DeltaTime);
	void AddEnemy();
	void EnemyRemoved();

public:
	static SMLevel Level;

private:
	struct SMEnemyData
	{
		int				m_Weight;
		Base::cString	m_Type;
	};
	typedef std::list<SMEnemyData> EnemydataList;

private:
	SMLevel();
	~SMLevel();
	void LoadStaticObjects(const Utilities::IXMLFileIO * const pXMLFile);

private:
	Base::cString					m_Background;
	Base::cVector2					m_LevelSize;
	Base::cVector2					m_PlayerSpawnPoint;
	int								m_MaxEnemies;
	int								m_EnemiesWeightRange;
	EnemydataList					m_EnemyDataList;
	bool							m_Initialized;
	float							m_LastSpawnTime;
	float							m_SpawnInterval;
	bool							m_MaxEnemiesSpawned;
};
#endif // sm_level_h__