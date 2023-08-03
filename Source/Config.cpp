
#include "LexiStd.hpp"
#include "Config.hpp"

using Lexi::Config;
using namespace tinyxml2;
// Initialize static class instance:
Lexi::UniqueConfigPtr Config::s_pInstance;

Config::Config(void)
{
}

void Config::Load(XMLElement *pRoot)
{
	for (auto *pNode = pRoot->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
	{
		const std::string kName = pNode->Name();

		if (kName == "ProgramName")
		{
			m_programName = pNode->GetText();
		}
		else if (kName == "Description")
		{
			m_description = pNode->GetText();
		}
		else if (kName == "LongDescription")
		{
			m_longDesc = pNode->GetText();
		}
	}
}

Config &Config::Get(void)
{
	static bool c_bInitialized = false;
	
	if (!c_bInitialized)
	{
		s_pInstance = std::make_unique<Config>();
		c_bInitialized = true;
	}

	return *s_pInstance.get();
}

const std::string &Config::GetProgramName(void) const
{
	return m_programName;
}

const std::string &Config::GetDescription(void) const
{
	return m_description;
}

const std::string &Config::GetLongDescription(void) const
{
	return m_longDesc;
}

