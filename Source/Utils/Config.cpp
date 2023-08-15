/*******************************************************************************
 * @file   Config.cpp
 * @author Brian Hoffpauir
 * @date   02.08.2023
 * @brief  Application configuration.
 *
 * Copyright (c) 2023, Brian Hoffpauir All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/
#include "LexiStd.hpp"
#include "Config.hpp"

using Lexi::Config;
using namespace tinyxml2;
// Declare/initialize static class members:
Lexi::UniqueConfigPtr Config::s_pInstance;
std::mutex Config::s_mutex;
std::unordered_map<std::string_view, Config::OperatingSystem> Config::s_systems = {
	{ "Linux", Config::OperatingSystem::kLinux },
	{ "Windows", Config::OperatingSystem::kWindows },
	{ "MacOS", Config::OperatingSystem::kMacOS },
	{ "FreeBSD", Config::OperatingSystem::kFreeBSD },
};

Config::Config(void)
{
}

void Config::Load(XMLElement *pRoot)
{
	// Parse application configuration:
	for (auto *pNode = pRoot->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
	{
		const std::string kName = pNode->Name();

		if (kName == "ProgramName")
		{
			m_app.programName = pNode->GetText();
		}
		else if (kName == "Description")
		{
			m_app.description = pNode->GetText();
		}
		else if (kName == "LongDescription")
		{
			m_app.longDesc = pNode->GetText();
		}
		else if (kName == "OperatingSystem")
		{
			m_app.OS = StringToOperatingSystem(pNode->GetText());
		}
	}
	// Parse user configuration:
	XMLElement *pUser = pRoot->FirstChildElement("User");
	for (auto *pNode = pUser->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
	{
		const std::string kName = pNode->Name();

		if (kName == "AutoSave")
		{
			m_user.bAutoSave = pNode->BoolAttribute("value");
		}
		else if (kName == "WordDict")
		{
			m_user.wordDictPath = pNode->GetText();
		}
	}
}

void Config::Save(XMLElement *pRoot)
{
}

Config &Config::Get(void)
{
	// Uses RAII to unlock after destruction.
	std::lock_guard<std::mutex> lockGuard(s_mutex);
	if (!s_pInstance)
	{
		s_pInstance = std::unique_ptr<Config>(LEXI_NEW Config);
	}

	return *s_pInstance.get();
}

const Config::App &Config::GetApp(void) const noexcept
{
	return m_app;
}

const Config::User &Config::GetUser(void) const noexcept
{
	return m_user;
}

Config::OperatingSystem Config::StringToOperatingSystem(std::string_view system)
{
	auto iter = s_systems.find(system);
	
	if (iter != s_systems.end())
	{
		return iter->second;
	}
	else
	{
		LEXI_THROW("Unsupported operating system!");
	}
}

