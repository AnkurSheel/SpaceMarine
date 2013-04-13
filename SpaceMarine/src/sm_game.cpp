#include "includes.h"
#include "sm_game.h"
#include "sm_surface.h"

using namespace Utilities;
using namespace Base;

// *****************************************************************************
SMGame::SMGame()
	: m_Running(false)
	, m_pDisplaySurface(NULL)
	, m_pTestSurface(NULL)
{

}

// *****************************************************************************
SMGame::~SMGame()
{
}

// *****************************************************************************
bool SMGame::OnExecute()
{
	if (Initialize() == false)
	{
		return false;
	}

	SDL_Event Event;
	while(m_Running)
	{
		while(SDL_PollEvent(&Event))
		{
			OnEvent(&Event);
		}
		Update();
		Render();
	}
	Cleanup();
	return true;
}

// *****************************************************************************
bool SMGame::Initialize()
{
	ILogger::Instance()->VInitialize();
	ILogger::Instance()->VSetLogOptions(true, true, false, 2);
	//Start SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Could not Initialize SDL");
		return false;
	}
	m_pDisplaySurface = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if(m_pDisplaySurface == NULL)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Could not Set the video mode");
		return false;
	}

	m_pTestSurface = SMSurface::OnLoad("myimage.bmp");
	if (m_pTestSurface == NULL)
	{
		return false;
	}

	m_Running = true;	
	return true;
}

// *****************************************************************************
void SMGame::Update()
{

}

// *****************************************************************************
void SMGame::Render()
{
	SMSurface::OnDraw(m_pDisplaySurface, m_pTestSurface, 0, 0);
	SMSurface::OnDraw(m_pDisplaySurface, m_pTestSurface, 200, 200, 0, 0, 50, 50);
	SDL_Flip(m_pDisplaySurface);
}

// *****************************************************************************
void SMGame::OnEvent(const SDL_Event * const pEvent)
{
	if (pEvent->type == SDL_QUIT)
	{
		m_Running = false;
	}
}

// *****************************************************************************
void SMGame::Cleanup()
{
	SDL_FreeSurface(m_pTestSurface);

	SDL_FreeSurface(m_pDisplaySurface);
	//Quit SDL
	SDL_Quit();
}
