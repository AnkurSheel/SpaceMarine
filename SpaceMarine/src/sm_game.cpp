#include "includes.h"
#include "sm_game.h"
#include "sm_surface.h"
#include "sm_entity_manager.h"
#include "Timer.hxx"
#include "sm_entity.h"
#include "sm_controls.h"
#include "sm_Player.h"
#include "ParamLoaders.hxx"
#include "sm_directories.h"

using namespace Base;
using namespace Utilities;

// *****************************************************************************
SMGame::SMGame()
	: m_Running(false)
	, m_pDisplaySurface(NULL)
	, m_pGameTimer(NULL)
	, m_pParamLoader(NULL)
	, m_pBGSurface(NULL)
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
	// make sure our memory leak checker is working
#ifdef _DEBUG
	int * p = DEBUG_NEW int;
#endif // _DEBUG

	ILogger::Instance()->VInitialize();

	if(m_pParamLoader == NULL)
	{
		m_pParamLoader = IParamLoader::CreateParamLoader();
		m_pParamLoader->VLoadParametersFromFile("Options.ini");
	}

	SetLogOptions();

	//Start SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Could not Initialize SDL");
		return false;
	}

	if(CreateDisplaySurface() == false)
	{
		return false;
	}

	SetCaption();

	cString AssetsPath = m_pParamLoader->VGetParameterValueAsString("-AssetsPath", "");
	SMDirectories::Directories.Initialize(AssetsPath, "directories.xml");
	
	m_pGameTimer = ITimer::CreateTimer();
	m_pGameTimer->VStartTimer();

	m_pBGSurface = SMSurface::OnLoad(SMDirectories::Directories.GetBackGrounds() + "dirt.png");

	SetLevelSize();

	m_pPlayer  = DEBUG_NEW SMPlayer("Player", m_LevelSize, m_ScreenSize);
	m_pPlayer->VOnLoad(SMDirectories::Directories.GetPlayer() + "hero_spritesheet.png", 100, 100, 1);
	m_pPlayer->SetPos(cVector2(320.0f, 240.0f));
	SMEntityManager::VRegisterEntity(m_pPlayer);

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
	int XPos = 0;
	int YPos = 0;
	if (m_pPlayer != NULL)
	{
		XPos = m_pPlayer->GetCameraCenter().x;
		YPos = m_pPlayer->GetCameraCenter().y;
	}
	if (m_pBGSurface != NULL)
	{
		SMSurface::OnDraw(m_pDisplaySurface, m_pBGSurface, 0, 0, XPos, YPos, m_ScreenSize.x, m_ScreenSize.y);
	}
	SMEntityManager::Render(m_pDisplaySurface);
	SDL_Flip(m_pDisplaySurface);
}

// *****************************************************************************
void SMGame::Cleanup()
{
	SafeDelete(&m_pGameTimer);
	SafeDelete(&m_pParamLoader);
	SMEntityManager::Cleanup();
	
	if (m_pBGSurface != NULL)
	{
		SDL_FreeSurface(m_pBGSurface);
		m_pBGSurface = NULL;
	}

	if (m_pDisplaySurface != NULL)
	{
		SDL_FreeSurface(m_pDisplaySurface);
		m_pDisplaySurface = NULL;
	}

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
	m_ScreenSize.x = m_pParamLoader->VGetParameterValueAsFloat("-WindowWidth", 800);
	m_ScreenSize.y = m_pParamLoader->VGetParameterValueAsFloat("-WindowHeight", 600);
	m_pDisplaySurface = SDL_SetVideoMode(m_ScreenSize.x, m_ScreenSize.y, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

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

// *****************************************************************************
void SMGame::SetLevelSize()
{
	m_LevelSize = m_ScreenSize;
	if (m_pBGSurface != NULL)
	{
		m_LevelSize.x = m_pBGSurface->w;
		m_LevelSize.y = m_pBGSurface->h;
		Log_Write(ILogger::LT_DEBUG, 2, cString(100, "Level Size is (%d, %d) ", static_cast<int>(m_LevelSize.x), static_cast<int>(m_LevelSize.y)));
	}
}
