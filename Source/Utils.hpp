/*******************************************************************************
 * @file   Utils.hpp
 * @author Brian Hoffpauir
 * @date   02.08.2023
 * @brief  Utility types & functions.
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
#ifndef LEXI_UTILS_HPP
#define LEXI_UTILS_HPP

// Useful macros:
#if defined(_DEBUG) // Only on Windows IIRC
#define LEXI_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__) // Use overloaded debug new operator
#else
#define LEXI_NEW new
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(X) if (X) { delete X; X = nullptr; }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(X) if (X) { delete[] X; X = nullptr; }
#endif

#define LEXI_DECLARE_PTR(TYPE) \
	using Unique ## TYPE ## Ptr = std::unique_ptr<TYPE>; \
	using Strong ## TYPE ## Ptr = std::shared_ptr<TYPE>; \
	using Weak ## TYPE ## Ptr = std::weak_ptr<TYPE>; \

namespace Lexi
{
	//! Interface for non-copyable class types.
	class INonCopyable
	{
	public:
		INonCopyable(void) = default;
		INonCopyable(const INonCopyable &) = delete;
		INonCopyable &operator=(const INonCopyable &) = delete;
		virtual ~INonCopyable(void) = default;
	};
	//! Interface for non-moveable class types.
	class INonMoveable
	{
	public:
		INonMoveable(void) = default;
		INonMoveable(INonMoveable &&) = delete;
		INonMoveable &operator=(INonMoveable &&) = delete;
		virtual ~INonMoveable(void) = default;
	};
} // End namespace (Lexi)

#endif /* !LEXI_UTILS_HPP */
