// *****************************************************************************
//  game   version:  1.0   Ankur Sheel  date: 2013/04/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_game_h__
#define sm_game_h__

#include "NonCopyable.h"
#include "sm_event.h"

namespace Utilities
{
	class ITimer;
	class IParamLoader;
}

union SDL_Event;
struct SDL_Surface;
class SMEntityManager;

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
	virtual void VOnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);
	virtual void VOnKeyUp(SDLKey Sym, SDLMod Mod, Uint16 Unicode);

private:
	void SetLogOptions();
	bool CreateDisplaySurface();
	void SetCaption();

private:
	bool						m_Running;
	SDL_Surface *				m_pDisplaySurface;
	Utilities::ITimer *			m_pGameTimer;
	Utilities::IParamLoader *	m_pParamLoader;
};

#endif // sm_game_h__
