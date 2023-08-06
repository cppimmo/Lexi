/*******************************************************************************
 * @file   XWindowImpl.hpp
 * @author Brian Hoffpauir
 * @date   02.08.2023
 * @brief  Window system implementation for X11.
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
#ifndef LEXI_XWINDOWIMPL_HPP
#define LEXI_XWINDOWIMPL_HPP

namespace Lexi
{
	/**
	 * Window system implementation interface for X11.
	 */
	class XWindowImpl final : public IWindowImpl
	{
		::Display *m_pDisplay;
		::Window *m_window;
		::GC m_graphicsContext;
	public:
		XWindowImpl(void);
		~XWindowImpl(void);

		void VDrawLine(void) override { }
		void VDrawRect(void) override { }
		void VDrawPolygon(void) override { }
		void VDrawText(void) override { }

		void VFillRect(void) override { }
		void VFillPolygon(void) override { }
	private:
		
	};
} // End namespace (Lexi)

#endif /* !LEXI_XWINDOWIMPL_HPP */

