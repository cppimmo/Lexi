/*******************************************************************************
 * @file   ICommand.hpp
 * @author Brian Hoffpauir
 * @date   02.08.2023
 * @brief  Command interface for issuing requests.
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
#ifndef LEXI_ICOMMAND_HPP
#define LEXI_ICOMMAND_HPP

namespace Lexi
{
	class ICommand;
	LEXI_DECLARE_PTR(ICommand);
	//! Execution result enumeration.
	enum struct CommandResult
	{
		kSuccess = 0,
		kFailure
	};
	
	/**
	 * Command interface that encapsulates user requests.
	 */
	class ICommand
	{
	public:
		virtual ~ICommand(void) = default;
		//! Perform or redo a command.
		virtual CommandResult VExecute(void) = 0;
		//! Undo a previously executed command.
		virtual CommandResult VUnexecute(void) = 0;
		//! Determine whether or not a command can be undone.
		virtual bool VIsReversible(void) const = 0;
	};
} // End namespace (Lexi)

#endif /* !LEXI_ICOMMAND_HPP */
