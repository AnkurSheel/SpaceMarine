#include "includes.h"
#include "sm_controls.h"

SMControls SMControls::Keys;

// *****************************************************************************
SMControls::SMControls()
{

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
