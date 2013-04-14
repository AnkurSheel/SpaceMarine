// *****************************************************************************
//  sm_controls   version:  1.0   Ankur Sheel  date: 2013/04/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_controls_h__
#define sm_controls_h__

#include "NonCopyable.h"

class SMControls
	: public Base::cNonCopyable
{
public:
	void OnKeyDown(const unsigned int CharID);
	void OnKeyUp(const unsigned int CharID);
	bool IsKeyPressed(const unsigned int CharID);

public:
	static SMControls Keys;

private:
	SMControls();
	~SMControls();

private:
	bool	m_Keys[SDLK_LAST];
};

#endif // sm_controls_h__