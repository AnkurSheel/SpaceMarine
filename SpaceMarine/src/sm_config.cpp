#include "includes.h"
#include "sm_config.h"
#include <XMLFileIO.hxx>
#include "sm_directories.h"

using namespace Base;
using namespace Utilities;

// *****************************************************************************
SMConfig::SMConfig()
	: m_FirstTime(true)
	, m_pConfigFile(NULL)
{

}

// *****************************************************************************
SMConfig::~SMConfig()
{
	Cleanup();
}

// *****************************************************************************
void SMConfig::Initialize()
{
	m_pConfigFile = IXMLFileIO::CreateXMLFile();
	m_pConfigFile->VLoad(SMDirectories::Directories.GetAssetsPath() + "config.xml");
}

// *****************************************************************************
void SMConfig::Cleanup()
{
	SafeDelete(&m_pConfigFile);
}

// *****************************************************************************
const Utilities::IXMLFileIO * const SMConfig::GetConfigLoader()
{
	static SMConfig instance;
	if (instance.m_FirstTime)
	{
		instance.m_FirstTime = false;
		instance.Initialize();
	}
	return instance.m_pConfigFile;
}
