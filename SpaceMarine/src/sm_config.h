// *****************************************************************************
//  sm_config   version:  1.0   Ankur Sheel  date: 2013/04/18
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef sm_config_h__
#define sm_config_h__

namespace Utilities
{
	class IXMLFileIO;
}

class SMConfig
	: public Base::cNonCopyable
{
public:
	static const Utilities::IXMLFileIO * const GetConfigLoader();
	
private:
	SMConfig();
	~SMConfig();
	void Initialize();
	void Cleanup();

private:
	bool					m_FirstTime;
	Utilities::IXMLFileIO * m_pConfigFile;
};
#endif // sm_config_h__