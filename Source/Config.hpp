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
		static UniqueConfigPtr s_pInstance; //!< Singleton instance

		std::string m_programName;
		std::string m_description;
		std::string m_longDesc;
	public:
		Config(void);
		//! Load configuration from XML document.
		void Load(tinyxml2::XMLElement *pRoot);
		//! Save configuration changes to XML document.
		void Save(tinyxml2::XMLElement *pRoot);
		// Accessors:
		//! Retrieve singleton instance.
		static Config &Get(void);
		const std::string &GetProgramName(void) const;
		const std::string &GetDescription(void) const;
		const std::string &GetLongDescription(void) const;
	};
}

#endif /* !LEXI_CONFIG_HPP */
