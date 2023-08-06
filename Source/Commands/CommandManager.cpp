/*******************************************************************************
 * @file   CommandManager.cpp
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
#include "LexiStd.hpp"
#include "CommandManager.hpp"

using Lexi::CommandManager, Lexi::CommandList, Lexi::CommandResult;

CommandManager::CommandManager(void)
	: m_commands{},
	  m_currIter{}
{
}

CommandResult CommandManager::Execute(ICommand &command)
{
	// If a command is irreversible, it should be executed but not placed in command list.
	CommandResult result = command.VExecute();

	if (command.VIsReversible())
	{
	}

	return result;
}

void CommandManager::Undo(void)
{
	// If a command is uncapable of being undone, it should be skipped.
}

void CommandManager::Redo(void)
{
}

void CommandManager::Clear(void)
{
	m_commands.clear();
	m_currIter = m_commands.end();
}

bool CommandManager::CanUndo(void) const
{
	if (m_currIter == m_commands.cend())
	{
		return false;
	}
	
	return (*m_currIter)->VIsReversible();
}

bool CommandManager::CanRedo(void) const
{
	return true;
}

