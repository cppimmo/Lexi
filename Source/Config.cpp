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

void Config::Save(XMLElement *pRoot)
{
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

