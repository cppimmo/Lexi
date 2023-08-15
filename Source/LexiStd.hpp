/*******************************************************************************
 * @file   LexiStd.hpp
 * @author Brian Hoffpauir
 * @date   02.08.2023
 * @brief  Standard project items.
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
#ifndef LEXI_LEXISTD_HPP
#define LEXI_LEXISTD_HPP

// Common library headers:
#include <tinyxml2.h>
// Common standard library headers:
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <format>
#include <memory>
#include <new>
#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <span>
#include <type_traits>
#include <concepts>
#include <numeric>
#include <numbers>
#include <limits>
#include <algorithm>
#include <compare>
#include <chrono>
#include <ratio>
#include <exception>
#include <source_location>
#include <mutex>
#include <filesystem>
#include <functional>
#include <ranges>
// Common project headers:
#include "Utils/Types.hpp"
#include "Utils/Interfaces.hpp"
#include "Utils/Templates.hpp"
#include "Utils/Utils.hpp"
#include "Utils/Exception.hpp"
#include "Utils/Logger.hpp"
#include "Utils/Config.hpp"
// All project headers:
#include "Commands/ICommand.hpp"
#include "Commands/QuitCommand.hpp"
#include "Visitors/IVisitor.hpp"
#include "Visitors/SpellCheckVisitor.hpp"

//! Primary namespace.
namespace Lexi
{
} // End namespace (Lexi)

#endif /* !LEXI_LEXISTD_HPP */
