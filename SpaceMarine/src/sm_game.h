// *****************************************************************************
//  game   version:  1.0   Ankur Sheel  date: 2013/04/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_game_h__
#define sm_game_h__

#include "NonCopyable.h"

union SDL_Event;
struct SDL_Surface;

class SMGame
	: public Base::cNonCopyable
{
public:
	SMGame();
	~SMGame();
	bool OnExecute();
	bool Initialize();
	void Update();
	void Render();
	void OnEvent(const SDL_Event * const pEvent);
	void Cleanup();

private:
	bool			m_Running;
	SDL_Surface *	m_pDisplaySurface;
	SDL_Surface *	m_pTestSurface;

};

#endif // sm_game_h__
