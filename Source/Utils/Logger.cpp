/*******************************************************************************
 * @file   Logger.cpp
 * @author Brian Hoffpauir
 * @date   02.08.2023
 * @brief  Logging facilities.
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
#include "Logger.hpp"

using Lexi::Logger;
// Initialize static class instance:
Lexi::UniqueLoggerPtr Logger::s_pInstance;
std::mutex Logger::s_mutex;

Logger::Logger(void)
	: m_bEnabled(true),
	  m_bWrapLines(true),
	  m_wrapCount(kDEFAULT_WRAP_COUNT),
	  m_msgStream(std::cout.rdbuf()),
	  m_logStream(std::clog.rdbuf()),
	  m_errStream(std::cerr.rdbuf())
{
}

void Logger::Init(tinyxml2::XMLElement *pRoot)
{
	for (auto *pNode = pRoot->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
	{
		const std::string kName = pNode->Name();

		if (kName == "Enabled")
		{
			m_bEnabled = pNode->BoolAttribute("value");
		}
		else if (kName == "WrapLines")
		{
			m_bWrapLines = pNode->BoolAttribute("value");
		}
		else if (kName == "WrapCount")
		{
			m_wrapCount = pNode->IntAttribute("value", kDEFAULT_WRAP_COUNT);
		}
		else if (kName == "Stream")
		{
			const std::string kLevelName = pNode->Attribute("level");
			const bool kbShowDate = pNode->BoolAttribute("showDate");
			bool bFilenameSet = true;
			const std::string kFilename = pNode->Attribute("filename");
			if (kFilename.empty())
			{
				bFilenameSet = false;
			}
			
			if (kLevelName == "Message")
			{
				//RedirectLevelTo(Level::Msg, kFilename);
			}
			else if (kLevelName == "Log")
			{
				//RedirectLevelTo(Level::Log, kFilename);
			}
			else if (kLevelName == "Error")
			{
				//RedirectLevelTo(Level::Err, kFilename);
			}
		}
		//const std::string kName = pElem->Attribute();
	}
}

bool Logger::Enable(void) noexcept
{
	bool bOld = m_bEnabled;
	m_bEnabled = true;
	return bOld;
}

bool Logger::Disable(void) noexcept
{
	bool bOld = m_bEnabled;
	m_bEnabled = false;
	return bOld;
}

void Logger::Flush(Level level)
{
	GetLevelStream(level).flush();
}

void Logger::RedirectLevelTo(Level level, std::ostream &outStream)
{
	GetLevelStream(level).rdbuf(outStream.rdbuf());
}

Logger &Logger::Get(void)
{
	// Uses RAII to unlock after destruction.
	std::lock_guard<std::mutex> lockGuard(s_mutex);
	if (!s_pInstance)
	{
		s_pInstance = std::unique_ptr<Logger>(LEXI_NEW Logger);
	}

	return *s_pInstance.get();
}

std::optional<std::string> Logger::GetSystemTime(bool bUseUnderscores)
{
	namespace ch = std::chrono;
	
	const auto kTime = ch::system_clock::to_time_t(ch::system_clock::now());
	std::tm *pNow = nullptr;
	pNow = std::localtime(&kTime); // localtime_s not available on Linux & GCC?
	if (!pNow)
	{
		return std::nullopt;
	}
	
	std::ostringstream outStrStream;
	outStrStream.fill('0');
	static constexpr int c_kSTARTING_YEAR = 1900;
	// Why must I set the width each time??
	outStrStream << std::setw(2) << (pNow->tm_mon + 1) << '-'
				  << std::setw(2) << pNow->tm_mday << '-'
				  << (pNow->tm_year + c_kSTARTING_YEAR) << ((bUseUnderscores) ? "_" : ", ")
				  << std::setw(2) << (pNow->tm_hour + 1) << ((bUseUnderscores) ? '-' : ':')
				  << std::setw(2) <<  pNow->tm_min << ((bUseUnderscores) ? '-' : ':')
				  << std::setw(2) << ((pNow->tm_sec == 60) ? 0 : pNow->tm_sec);
	return outStrStream.str();
}

std::size_t Logger::GetWrapCount(void) const noexcept
{
	return m_wrapCount;
}

bool Logger::IsEnabled(void) const noexcept
{
	return m_bEnabled;
}

bool Logger::ShouldWrapLines(void) const noexcept
{
	return m_bWrapLines;
}

void Logger::SetWrapLines(bool bWrapLines) noexcept
{
	m_bWrapLines = bWrapLines;
}

void Logger::SetWrapCount(std::size_t wrapCount) noexcept
{
	m_wrapCount = wrapCount;
}

std::ostream &Logger::GetLevelStream(Level level)
{
	switch (level)
	{
	case Level::kMessage:
		return m_msgStream;
	case Level::kLog:
		return m_logStream;
	case Level::kError:
		return m_errStream;
	default:
		LEXI_THROW("Invalid level.");
	}
}

void Logger::WrapLines(std::string_view input, std::ostringstream &outStrStream) const
{
	std::istringstream inStrStream(std::string{ input });
	std::string word;
	std::string::size_type currLineLen = 0;
	
	while (inStrStream >> word)
	{
		if ((currLineLen + word.size()) > m_wrapCount)
		{
			outStrStream << '\n';
			currLineLen = 0;
		}
		// TODO: Prevent trailing space.
		outStrStream << word << ' ';
		currLineLen += word.size();
	}
}

