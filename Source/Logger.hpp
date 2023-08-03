/*******************************************************************************
 * @file   Logger.hpp
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
#ifndef LEXI_LOGGER_HPP
#define LEXI_LOGGER_HPP

namespace Lexi
{
	class Logger;
	LEXI_DECLARE_PTR(Logger);
	
	//! Logger singleton.
	class Logger final : public INonCopyable, public INonMoveable
	{
	public:
		enum struct Level
		{
			Msg,
			Log,
			Err
		};
	private:
		static constexpr std::size_t kDEFAULT_WRAP_COUNT = 80; //!< Default line wrap count
		
		static UniqueLoggerPtr s_pInstance; //!< Singleton instance

		bool m_bEnabled; //!< Whether or not log output is enabled
		bool m_bWrapLines; //!< Whether or not lines will be wrapped at m_wrapCount
		std::size_t m_wrapCount; //!< Number of columns before newline
		std::ostream m_msgStream; //!< Message output stream
		std::ostream m_logStream; //!< Logging output stream
		std::ostream m_errStream; //!< Error output stream
	public:
		Logger(void);
		//! Enable log output.
		bool Enable(void) noexcept;
		//! Disable log output.
		bool Disable(void) noexcept;
		//! Write output to stream at level.
		template <typename... Args>
		std::ostream &Write(Level level, std::string_view format, Args&&... args);
		//! Write output to stream at level with an appended newline.
		template <typename... Args>	
		std::ostream &Writeln(Level level, std::string_view format, Args&&... args);
		//! Flush output stream at level.
		void Flush(Level level);
		//! Redirect output stream at level to outStream.
		void RedirectLevelTo(Level level, std::ostream &outStream);
		// Accessors:
		//! Retrieve singleton instance.
		static Logger &Get(void);
		static std::optional<std::string> GetSystemTime(bool bUseUnderscores = false);
		std::size_t GetWrapCount(void) const noexcept;
		bool IsEnabled(void) const noexcept;
		bool ShouldWrapLines(void) const noexcept;

		void SetWrapLines(bool bWrapLines) noexcept;
		void SetWrapCount(std::size_t wrapCount) noexcept;
	private:
		static constexpr std::string_view GetLevelString(Level level) noexcept;

		std::ostream &GetLevelStream(Level level);
		void WrapLines(std::string_view input, std::ostringstream &outStrStream) const;
	};

	template <typename... Args>
	std::ostream &Logger::Write(Level level, std::string_view format, Args&&... args)
	{
		std::ostream &outStream = GetLevelStream(level);

		std::ostringstream outStrStream;
		if (m_bWrapLines)
		{
			WrapLines(format, outStrStream);
		}
		else
		{
			outStrStream << format;
		}
		
		auto timeStr = GetSystemTime();
		if (timeStr)
		{
			outStream << '[' << *timeStr << ']';
		}
		outStream << '[' << GetLevelString(level) << "]: " << std::vformat(outStrStream.str(), std::make_format_args(args...));
		return outStream;
	}
	
	template <typename... Args>	
	std::ostream &Logger::Writeln(Level level, std::string_view format, Args&&... args)
	{
		// std::forward<Args>(args...);
		return Write(level, format, args...) << '\n';
	}

	constexpr std::string_view Logger::GetLevelString(Level level) noexcept
	{
		switch (level)
		{
		case Level::Msg:
			return "MESSAGE";
		case Level::Log:
			return "LOG";
		case Level::Err:
			return "ERROR";
		}
		return "UNKNOWN";
	}
} // End namespace (Lexi)

#define LEXI_MSG(...) \
do \
{ \
	using Lexi::Logger; \
	Logger::Get().Writeln(Logger::Level::Msg, __VA_ARGS__); \
} \
while (0) \

#define LEXI_LOG(...) \
do \
{ \
	using Lexi::Logger; \
	Logger::Get().Writeln(Logger::Level::Log, __VA_ARGS__); \
} \
while (0) \

#define LEXI_ERR(...) \
do \
{ \
	using Lexi::Logger; \
	Logger::Get().Writeln(Logger::Level::Err, __VA_ARGS__); \
} \
while (0) \

#define LEXI_MSG_IF(COND, ...) \
do \
{ \
	if (COND) \
	{ \
		using Lexi::Logger; \
		Logger::Get().Writeln(Logger::Level::Msg, __VA_ARGS__); \
	} \
} \
while (0) \

#define LEXI_LOG_IF(COND, ...) \
do \
{ \
	if (COND) \
	{ \
		using Lexi::Logger; \
		Logger::Get().Writeln(Logger::Level::Log, __VA_ARGS__); \
	} \
} \
while (0) \

#define LEXI_ERR_IF(COND, ...) \
do \
{ \
	if (COND) \
	{ \
		using Lexi::Logger; \
		Logger::Get().Writeln(Logger::Level::Err, __VA_ARGS__); \
	} \
} \
while (0) \

#endif /* !LEXI_LOGGER_HPP */

