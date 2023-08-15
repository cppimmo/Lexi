/*******************************************************************************
 * @file   SpellCheckVisitor.hpp
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
#ifndef LEXI_SPELLCHECKVISITOR_HPP
#define LEXI_SPELLCHECKVISITOR_HPP

namespace Lexi
{
	class SpellCheckVisitor;
	LEXI_DECLARE_PTR(SpellCheckVisitor);
	
	//! Visitor for checking spelling of glyphs.
	class SpellCheckVisitor : public IVisitor
	{
	public:
		using Word = std::string;
		using WordVector = std::vector<Word>;
	private:
		Word m_currWord; //!< The current word
		WordVector m_misspellings; //!< Currently misspelled words
		WordVector m_words; //!< Dictionary (or word list)
	public:
		// TODO: Maintain reference to document structure?
		SpellCheckVisitor(void);
		// IVisitor overrides:
		void VVisitCharacter(char ch /* Character *pChar */) override;
		void VVisitRow(/* Row *pRow */) override;
		void VVisitImage(/* Image *pImage */) override;
		// Accessors:
		const WordVector &GetMisspellings(void) const;
		const WordVector &GetWords(void) const;
	protected:
		virtual bool VIsMisspelled(const Word &kWord);
	};
} // End namespace (Lexi)

#endif /* !LEXI_SPELLCHECKVISITOR_HPP */

