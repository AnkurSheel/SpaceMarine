#include "includes.h"
#include "sm_game.h"

using namespace Utilities;

// *****************************************************************************
SMGame::SMGame()
	: m_Running(false)
	, m_pSurface(NULL)
{

}

// *****************************************************************************
SMGame::~SMGame()
{
	Cleanup();
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

	//Start SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Could not Initialize SDL");
		return false;
	}
	
	m_pSurface = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if(m_pSurface == NULL)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Could not Set the video mode");
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
	//Quit SDL
	SDL_Quit();
}
