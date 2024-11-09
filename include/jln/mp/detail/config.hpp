// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/compiler.hpp>

#ifndef JLN_MP_MAX_CALL_ELEMENT
# define JLN_MP_MAX_CALL_ELEMENT 10000
#endif

#ifndef JLN_MP_ENABLE_DEBUG
# define JLN_MP_ENABLE_DEBUG 0
#endif

// useless with gcc and msvc since it displays all the transformations
#if JLN_MP_GCC || JLN_MP_MSVC || JLN_MP_MEMOIZED_ALIAS
# undef JLN_MP_ENABLE_DEBUG
# define JLN_MP_ENABLE_DEBUG 0
#endif

/// \defgroup list List
/// \defgroup algorithm Algorithm
/// \defgroup number Number
/// \defgroup value Value
/// \defgroup functional Functional
/// \defgroup utility Utility
/// \defgroup trait Trait
/// \defgroup search Search
/// \defgroup group Group
