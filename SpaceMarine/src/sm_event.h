// *****************************************************************************
//  sm_event   version:  1.0   Ankur Sheel  date: 2013/04/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_event_h__
#define sm_event_h__

class SMEvent
{
public:
	SMEvent();
	virtual ~SMEvent();
	virtual void OnEvent(const SDL_Event * const pEvent);
	virtual void VOnInputFocus();
	virtual void VOnInputBlur();
	virtual void VOnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);
	virtual void VOnKeyUp(SDLKey Sym, SDLMod Mod, Uint16 Unicode);
	virtual void VOnMinimize();
	virtual void VOnRestore();
	virtual void VOnResize(const int Width, const int Height);
	virtual void VOnExit();
};
#endif // sm_event_h__