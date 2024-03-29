#include "includes.h"
#include "sm_game.h"
#include "sm_surface.h"
#include "sm_entity_manager.h"
#include "Timer.hxx"
#include "sm_entity.h"
#include "sm_controls.h"
#include "ParamLoaders.hxx"
#include "sm_directories.h"
#include "sm_level.h"
#include "sm_camera.h"
#include "sdl_ttf.h"
#include <RandomGenerator.hxx>

using namespace Base;
using namespace Utilities;

cVector2 SMGame::m_ScreenSize;
SMCamera * SMGame::m_pCamera = NULL;
IRandomGenerator * SMGame::m_pRandom = NULL;
bool SMGame::m_bGameOver = false;

// *****************************************************************************
SMGame::SMGame()
	: m_Running(false)
	, m_pDisplaySurface(NULL)
	, m_pGameTimer(NULL)
	, m_pParamLoader(NULL)
	, m_pBGSurface(NULL)
	, m_pPlayer(NULL)
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
	if(TTF_Init() < 0 )
	{
		Log_Write(ILogger::LT_ERROR, 1, "Could not Initialize SDL TTF");
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

	m_pRandom = IRandomGenerator::CreateRandomGenerator();

	SMLevel::Level.Initialize("level1.xml");

	LoadBackGround();

	CreatePlayer();

	m_pCamera = DEBUG_NEW SMCamera();
	m_pCamera->SetTarget(m_pPlayer);
	
	m_Running = true;	
	return true;
}

// *****************************************************************************
void SMGame::Update()
{
	if (m_bGameOver)
	{
		return;
	}

	if (m_pGameTimer)
	{
		m_pGameTimer->VOnUpdate();
		SMLevel::Level.Update(m_pGameTimer->VGetDeltaTime());
		SMEntityManager::EntityManager.Update(m_pGameTimer->VGetDeltaTime());
	}
	if (m_pCamera)
	{
		m_pCamera->Update();
	}
}

// *****************************************************************************
void SMGame::Render()
{
	SDL_FillRect(m_pDisplaySurface, NULL, 0);
	if (m_pBGSurface != NULL)
	{
		SMSurface::OnDraw(m_pDisplaySurface, m_pBGSurface, 0, 0, static_cast<int>(m_pCamera->GetPos().x), static_cast<int>(m_pCamera->GetPos().y), static_cast<int>(m_ScreenSize.x), static_cast<int>(m_ScreenSize.y));
	}
	SMEntityManager::EntityManager.Render(m_pDisplaySurface);
	SDL_Flip(m_pDisplaySurface);
}

// *****************************************************************************
void SMGame::Cleanup()
{
	SafeDelete(&m_pGameTimer);
	SafeDelete(&m_pParamLoader);
	SafeDelete(&m_pCamera);
	SafeDelete(&m_pRandom);
	
	m_pPlayer = NULL;

	SMEntityManager::EntityManager.Cleanup();
	SafeFreeSurface(&m_pBGSurface);

	SafeFreeSurface(&m_pDisplaySurface);
	
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
	m_pDisplaySurface = SDL_SetVideoMode(static_cast<int>(m_ScreenSize.x), static_cast<int>(m_ScreenSize.y), 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

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
void SMGame::LoadBackGround()
{
	m_pBGSurface = SMSurface::OnLoad(SMDirectories::Directories.GetBackGroundSprites() + SMLevel::Level.GetBackground());
}

// *****************************************************************************
void SMGame::CreatePlayer()
{
	m_pPlayer = SMEntityManager::EntityManager.RegisterEntity("Player", "Player", "Player");
	m_pPlayer->VInitialize();
}

// *****************************************************************************
Base::cVector2 SMGame::GetCameraPosition()
{
	if (m_pCamera != NULL)
	{
		return m_pCamera->GetPos();
	}
	return cVector2::Zero();
}