#include "includes.h"
#include "sm_event.h"

// *****************************************************************************
SMEvent::SMEvent()
{

}

// *****************************************************************************
SMEvent::~SMEvent()
{

}

// *****************************************************************************
void SMEvent::OnEvent(const SDL_Event * const pEvent)
{
	if(pEvent->type == SDL_ACTIVEEVENT)
	{
		switch(pEvent->active.state) 
		{
		case SDL_APPINPUTFOCUS: 
			if (pEvent->active.gain)
			{
				VOnInputFocus();
			}
			else
			{
				VOnInputBlur();
			}

			break;
		}
	}
	else if (pEvent->type == SDL_APPACTIVE)
	{
		if(pEvent->active.gain)
		{
			VOnRestore();
		}
		else
		{
			VOnMinimize();
		}
	}
	else if(pEvent->type == SDL_KEYDOWN)
	{
		VOnKeyDown(pEvent->key.keysym.sym, pEvent->key.keysym.mod, pEvent->key.keysym.unicode);
	}
	else if (pEvent->type == SDL_KEYUP)
	{
		VOnKeyUp(pEvent->key.keysym.sym, pEvent->key.keysym.mod, pEvent->key.keysym.unicode);
	}
	else if(pEvent->type == SDL_QUIT)
	{
		VOnExit();
	}
	else if (pEvent->type == SDL_VIDEORESIZE)
	{
		VOnResize(pEvent->resize.w, pEvent->resize.h);
	}
}

// *****************************************************************************
void SMEvent::VOnInputFocus()
{

}

// *****************************************************************************
void SMEvent::VOnInputBlur()
{

}

// *****************************************************************************
void SMEvent::VOnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{

}

// *****************************************************************************
void SMEvent::VOnKeyUp(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{

}

// *****************************************************************************
void SMEvent::VOnMinimize()
{

}

// *****************************************************************************
void SMEvent::VOnRestore()
{

}

// *****************************************************************************
void SMEvent::VOnResize(const int Width, const int Height)
{

}

// *****************************************************************************
void SMEvent::VOnExit()
{

}
