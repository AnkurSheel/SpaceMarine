#include "includes.h"
#include "sm_controls.h"

SMControls SMControls::Keys;

// *****************************************************************************
SMControls::SMControls()
{
	for(int i=0; i<SDLK_LAST; i++)
	{
		m_Keys[i] = false;
	}
}

// *****************************************************************************
SMControls::~SMControls()
{
}

// *****************************************************************************
void SMControls::OnKeyDown(const unsigned int CharID)
{
	m_Keys[CharID] = true;
}

// *****************************************************************************
void SMControls::OnKeyUp(const unsigned int CharID)
{
	m_Keys[CharID] = false;
}

// *****************************************************************************
bool SMControls::IsKeyPressed(const unsigned int CharID)
{
	return (m_Keys[CharID]);
}
