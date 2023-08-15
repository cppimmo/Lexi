/*******************************************************************************
 * @file   SpellCheckVisitor.cpp
 * @author Brian Hoffpauir
 * @date   14.08.2023
 * @brief  Visitor for checking spelling of glyphs.
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
#include "SpellCheckVisitor.hpp"

using Lexi::SpellCheckVisitor;

SpellCheckVisitor::SpellCheckVisitor(void)
	: m_currWord{},
	  m_misspellings{},
	  m_words{}
{
	Config &config = Config::Get();

	std::ifstream inFile;
	inFile.exceptions(std::ios::badbit);
	inFile.open(config.GetUser().wordDictPath);
	LEXI_LOG("Word dict path: {}", config.GetUser().wordDictPath);

	for (std::string line; std::getline(inFile, line); )
	{
		std::istringstream inStrStream(line);
		Word word;
		inStrStream >> word;

		m_words.push_back(word);
	}
}

void SpellCheckVisitor::VVisitCharacter(char ch)
{
	if (std::isalpha(ch))
	{
		// Append alphabetic character to current word
		m_currWord += ch;
	}
	else
	{
		// Non alphabetic character encountered
		// Check spelling of current word
		bool bEmpty = m_currWord.empty();
		bool bMoreThanOneChar = (m_currWord.size() > 1);
		bool bAllAlpha = IsStringAlpha(m_currWord);
		
		if (!bEmpty && bMoreThanOneChar && bAllAlpha && VIsMisspelled(StringToLower(m_currWord)))
		{
			// Add the current word to the misspelled word list
			m_misspellings.push_back(m_currWord);
		}
		// Reset the current word
		m_currWord.clear();
	}
}

void SpellCheckVisitor::VVisitRow(void)
{
}

void SpellCheckVisitor::VVisitImage(void)
{
}

const SpellCheckVisitor::WordVector &SpellCheckVisitor::GetMisspellings(void) const
{
	return m_misspellings;
}

const SpellCheckVisitor::WordVector &SpellCheckVisitor::GetWords(void) const
{
	return m_words;
}

bool SpellCheckVisitor::VIsMisspelled(const Word &kWord)
{
	return (std::ranges::find(m_words, kWord) == m_words.end());
}

