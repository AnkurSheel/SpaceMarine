// *****************************************************************************
//  game   version:  1.0   Ankur Sheel  date: 2013/04/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_game_h__
#define sm_game_h__

#include "NonCopyable.h"
#include "sm_event.h"

union SDL_Event;
struct SDL_Surface;

class SMGame
	: public Base::cNonCopyable
	, public SMEvent
{
public:
	SMGame();
	~SMGame();
	bool OnExecute();
	bool Initialize();
	void Update();
	void Render();
	void Cleanup();
	void VOnExit();

private:
	bool			m_Running;
	SDL_Surface *	m_pDisplaySurface;
	SDL_Surface *	m_pTestSurface;

};

#endif // sm_game_h__
