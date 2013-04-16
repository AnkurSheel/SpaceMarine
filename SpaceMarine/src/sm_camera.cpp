#include "includes.h"
#include "sm_camera.h"
#include "sm_entity.h"
#include "sm_game.h"
#include "sm_level.h"

using namespace  Base;
// *****************************************************************************
SMCamera::SMCamera()
	: m_pTarget(NULL)
{

}

// *****************************************************************************
SMCamera::~SMCamera()
{

}

// *****************************************************************************
void SMCamera::Update()
{
	if (m_pTarget != NULL)
	{
		m_Pos = m_pTarget->GetPos() + (m_pTarget->GetSize() * 0.5f) - (SMGame::GetScreenSize() * 0.5f);
		Clamp<float>(m_Pos.x, 0, (SMLevel::Level.GetLevelSize().x - SMGame::GetScreenSize().x));
		Clamp<float>(m_Pos.y, 0, (SMLevel::Level.GetLevelSize().y - SMGame::GetScreenSize().y));
	}
}
