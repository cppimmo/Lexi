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

	// See: https://stackoverflow.com/a/52296294
	using OStreamDeleter = std::function<void (std::ostream *)>;
	using OStreamPtr = std::unique_ptr<std::ostream, OStreamDeleter>;
	/**
	 * Logger singleton.
	 */
	class Logger final : public INonCopyable, public INonMoveable
	{
	public:
		enum struct Level
		{
			kMessage, /**< Level for user messages */
			kLog, /**< Level for debug messages */
			kError /**< Level for error messages */
		};

		enum struct Redirection
		{
			kShared, /**< Maintain references to other redirections to a single level */
			kExclusive /**< Redirect exclusively to a single level */
		};
	private:
		static constexpr std::size_t kDEFAULT_WRAP_COUNT = 80; //!< Default line wrap count

		static UniqueLoggerPtr s_pInstance; //!< Singleton instance
		static std::mutex s_mutex;
		
		bool m_bEnabled; //!< Whether or not log output is enabled
		bool m_bWrapLines; //!< Whether or not lines will be wrapped at m_wrapCount
		std::size_t m_wrapCount; //!< Number of columns before newline
		std::ostream m_msgStream; //!< Message output stream
		std::ostream m_logStream; //!< Logging output stream
		std::ostream m_errStream; //!< Error output stream
		std::list<OStreamPtr> m_streamPtrs; //!< Shared stream pointers
	public:
		//! Initialize logger with the given XML configuration.
		void Init(tinyxml2::XMLElement *pRoot);
		//! Enable log output.
		bool Enable(void) noexcept;
		//! Disable log output.
		bool Disable(void) noexcept;
		//! Write output to stream at level.
		template <typename ...Args>
		std::ostream &Write(Level level, std::string_view format, Args &&...args);
		//! Write output to stream at level with an appended newline.
		template <typename ...Args>	
		std::ostream &Writeln(Level level, std::string_view format, Args &&...args);
		//! Flush output stream at level.
		void Flush(Level level);
		//! Redirect output stream at level to outStream.
		void RedirectLevelTo(Redirection redir, Level level, std::ostream &outStream);
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
		// Hide constructor so instances cannot be created directly.
		Logger(void);

		static constexpr std::string_view GetLevelString(Level level) noexcept;

		std::ostream &GetLevelStream(Level level);
		void WrapLines(std::string_view input, std::ostringstream &outStrStream) const;
	};

	template <typename ...Args>
	inline std::ostream &Logger::Write(Level level, std::string_view format, Args &&...args)
	{		
		std::ostream &outStream = GetLevelStream(level);
		if (!m_bEnabled)
		{
			return outStream;
		}
		
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
	
	template <typename ...Args>	
	inline std::ostream &Logger::Writeln(Level level, std::string_view format, Args &&...args)
	{
		// std::forward<Args>(args...);
		return Write(level, format, args...) << '\n';
	}

	inline constexpr std::string_view Logger::GetLevelString(Level level) noexcept
	{
		switch (level)
		{
		case Level::kMessage:
			return "MESSAGE";
		case Level::kLog:
			return "LOG";
		case Level::kError:
			return "ERROR";
		default:
			return "UNKNOWN";
		}
	}
} // End namespace (Lexi)

#define LEXI_MSG(...) \
do \
{ \
	using Lexi::Logger; \
	Logger::Get().Writeln(Logger::Level::kMessage, __VA_ARGS__); \
} \
while (0) \

#define LEXI_LOG(...) \
do \
{ \
	using Lexi::Logger; \
	Logger::Get().Writeln(Logger::Level::kLog, __VA_ARGS__); \
} \
while (0) \

#define LEXI_ERR(...) \
do \
{ \
	using Lexi::Logger; \
	Logger::Get().Writeln(Logger::Level::kError, __VA_ARGS__); \
} \
while (0) \

#define LEXI_MSG_IF(COND, ...) \
do \
{ \
	if (COND) \
	{ \
		using Lexi::Logger; \
		Logger::Get().Writeln(Logger::Level::kMessage, __VA_ARGS__); \
	} \
} \
while (0) \

#define LEXI_LOG_IF(COND, ...) \
do \
{ \
	if (COND) \
	{ \
		using Lexi::Logger; \
		Logger::Get().Writeln(Logger::Level::kLog, __VA_ARGS__); \
	} \
} \
while (0) \

#define LEXI_ERR_IF(COND, ...) \
do \
{ \
	if (COND) \
	{ \
		using Lexi::Logger; \
		Logger::Get().Writeln(Logger::Level::kError, __VA_ARGS__); \
	} \
} \
while (0) \

#endif /* !LEXI_LOGGER_HPP */

