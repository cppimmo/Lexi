/*******************************************************************************
 * @file   CommandManager.hpp
 * @author Brian Hoffpauir
 * @date   02.08.2023
 * @brief  Manager of requests.
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
#ifndef LEXI_COMMANDMANAGER_HPP
#define LEXI_COMMANDMANAGER_HPP

namespace Lexi
{
	class CommandManager;
	LEXI_DECLARE_PTR(CommandManager);

	using CommandList = std::list<ICommand *>;
	/**
	 * Manager of requests.
	 */
	class CommandManager
	{
		CommandList m_commands; //!< List of executed commands
		CommandList::iterator m_currIter; //!< Most recently executed command
	public:
		CommandManager(void);
		// TODO: How should a command object be placed in CommandList (ptr, ref, etc.)?
		CommandResult Execute(ICommand &command);
		void Undo(void);
		void Redo(void);
		//! Empty the command history.
		void Clear(void);
	private:
		//! Determine if the previous command is capable of being undone.
		bool CanUndo(void) const;
		//! Determine if the previous command is capable of being redone.
		bool CanRedo(void) const;
	};
} // End namespace (Lexi)

#endif /* !LEXI_COMMANDMANAGER_HPP */

