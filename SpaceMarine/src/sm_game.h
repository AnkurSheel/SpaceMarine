// *****************************************************************************
//  game   version:  1.0   Ankur Sheel  date: 2013/04/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_game_h__
#define sm_game_h__

#include "NonCopyable.h"
#include "sm_event.h"
#include "vector2.h"

namespace Utilities
{
	class ITimer;
	class IParamLoader;
}

union SDL_Event;
struct SDL_Surface;
class SMEntityManager;
class SMPlayer;

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
	void LoadBackGround();
	void CreatePlayer();

private:
	bool						m_Running;
	Base::cVector2				m_ScreenSize;
	Base::cVector2				m_LevelSize;
	SDL_Surface *				m_pDisplaySurface;
	SDL_Surface *				m_pBGSurface;
	Utilities::ITimer *			m_pGameTimer;
	Utilities::IParamLoader *	m_pParamLoader;
	SMPlayer *					m_pPlayer;
};

#endif // sm_game_h__
