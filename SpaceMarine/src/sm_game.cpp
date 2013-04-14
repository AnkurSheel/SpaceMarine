#include "includes.h"
#include "sm_game.h"
#include "sm_surface.h"
#include "sm_entity_manager.h"
#include "Timer.hxx"
#include "sm_entity.h"
#include "sm_controls.h"
#include "sm_Player.h"
#include "ParamLoaders.hxx"

using namespace Base;
using namespace Utilities;

// *****************************************************************************
SMGame::SMGame()
	: m_Running(false)
	, m_pDisplaySurface(NULL)
	, m_pGameTimer(NULL)
	, m_pParamLoader(NULL)
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

	if(m_pParamLoader == NULL)
	{
		m_pParamLoader = IParamLoader::CreateParamLoader();
		m_pParamLoader->VLoadParametersFromFile("Options.ini");
	}

	SetLogOptions();

	if(CreateDisplaySurface() == false)
	{
		return false;
	}

	SetCaption();


	//Start SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Could not Initialize SDL");
		return false;
	}

	m_pGameTimer = ITimer::CreateTimer();
	m_pGameTimer->VStartTimer();

	SMEntity * pEntity1 = DEBUG_NEW SMPlayer("Player");
	pEntity1->VOnLoad("hero_spritesheet.png", 100, 100, 1);
	
	SMEntityManager::VRegisterEntity(pEntity1);

	m_Running = true;	
	return true;
}

// *****************************************************************************
void SMGame::Update()
{
	if (m_pGameTimer)
	{
		m_pGameTimer->VOnUpdate();
		SMEntityManager::Update(m_pGameTimer->VGetDeltaTime());
	}
	
}

// *****************************************************************************
void SMGame::Render()
{
	SDL_FillRect(m_pDisplaySurface, NULL, 0);

	SMEntityManager::Render(m_pDisplaySurface);
	SDL_Flip(m_pDisplaySurface);
}

// *****************************************************************************
void SMGame::Cleanup()
{
	SafeDelete(&m_pGameTimer);
	SMEntityManager::Cleanup();
	
	SDL_FreeSurface(m_pDisplaySurface);
	m_pDisplaySurface = NULL;

	//Quit SDL
	SDL_Quit();
	ILogger::Destroy();
}

// *****************************************************************************
void SMGame::VOnExit()
{
	m_Running = false;
}

// *****************************************************************************
void SMGame::VOnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
	SMControls::Keys.OnKeyDown(Sym);
}

// *****************************************************************************
void SMGame::VOnKeyUp(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
	SMControls::Keys.OnKeyUp(Sym);
}

// *****************************************************************************
void SMGame::SetLogOptions()
{
	bool ShowConsoleLog = m_pParamLoader->VGetParameterValueAsBool("-showconsolelog", false);
	bool LogToText = m_pParamLoader->VGetParameterValueAsBool("-logtotext", true);
	bool LogToXML = m_pParamLoader->VGetParameterValueAsBool("-logtoxml", false);
	unsigned int PriorityLevel = m_pParamLoader->VGetParameterValueAsInt("-loglevel", 1);
	ILogger::Instance()->VSetLogOptions(ShowConsoleLog, LogToText, LogToXML, PriorityLevel);
}

// *****************************************************************************
bool SMGame::CreateDisplaySurface()
{
	int Width = m_pParamLoader->VGetParameterValueAsInt("-WindowWidth", 800);
	int Height = m_pParamLoader->VGetParameterValueAsInt("-WindowHeight", 600);
	m_pDisplaySurface = SDL_SetVideoMode(Width, Height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if(m_pDisplaySurface == NULL)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Could not Set the video mode");
		return false;
	}
	return true;
}

// *****************************************************************************
void SMGame::SetCaption()
{
	cString strName = m_pParamLoader->VGetParameterValueAsString("-title", "Game");
	SDL_WM_SetCaption(strName.GetData(), NULL);
}
