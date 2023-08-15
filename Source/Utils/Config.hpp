/*******************************************************************************
 * @file   Config.hpp
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
#ifndef LEXI_CONFIG_HPP
#define LEXI_CONFIG_HPP

namespace Lexi
{
	class Config;
	LEXI_DECLARE_PTR(Config);
	
	/**
	 * Configuration manager singleton.
	 */
	class Config final : public INonCopyable, public INonMoveable
	{
	public:
		enum struct OperatingSystem
		{
			kLinux,
			kWindows,
			kMacOS,
			kFreeBSD
		};
		//! Configuration options set by distributor.
		struct App
		{
			std::string programName;
			std::string description;
			std::string longDesc;
			OperatingSystem OS;
		};
		//! Configuration options set by user.
		struct User
		{
			bool bAutoSave;
			std::string wordDictPath;
		};
	private:
		static UniqueConfigPtr s_pInstance; //!< Singleton instance
		static std::mutex s_mutex;
		static std::unordered_map<std::string_view, OperatingSystem> s_systems;

		App m_app; //!< Application settings
		User m_user; //!< User settings
	public:
		//! Load configuration from XML document.
		void Load(tinyxml2::XMLElement *pRoot);
		//! Save configuration changes to XML document.
		void Save(tinyxml2::XMLElement *pRoot);
		// Accessors:
		//! Retrieve singleton instance.
		static Config &Get(void);
		const App &GetApp(void) const noexcept;
		const User &GetUser(void) const noexcept;
		static constexpr std::string_view OperatingSystemToString(OperatingSystem system) noexcept;
	private:
		// Hide constructor so instances cannot be created directly.
		Config(void);

		static OperatingSystem StringToOperatingSystem(std::string_view system);
	};

	inline constexpr std::string_view Config::OperatingSystemToString(OperatingSystem system) noexcept
	{
		using enum OperatingSystem;
		
		switch (system)
		{
		case kLinux:
			return "Linux";
		case kWindows:
			return "Windows";
		case kMacOS:
			return "MacOS";
		case kFreeBSD:
			return "FreeBSD";
		default:
			return "Unknown";
		}
	}
} // End namespace (Lexi)

#endif /* !LEXI_CONFIG_HPP */

