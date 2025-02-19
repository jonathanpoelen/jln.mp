// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

/// \ingroup config

#include <jln/mp/detail/compiler.hpp>


/// Maximum pack size that can be passed to the call function.
/// If the pack is larger, there will be a compilation error.
#ifndef JLN_MP_MAX_CALL_ELEMENT
# define JLN_MP_MAX_CALL_ELEMENT 10000
#endif

/// When 1, ignore the value of JLN_MP_LAZY_ALIAS in the implementations.
/// This allows the code to compile in an emptier way, but will fail when
/// the compiler can resolve an alias leading to a compilation error
/// (which is actually quite rare).
#ifndef JLN_MP_FORCE_LAZY_ALIAS
# define JLN_MP_FORCE_LAZY_ALIAS 1
#endif

#if JLN_MP_LAZY_ALIAS
# undef JLN_MP_FORCE_LAZY_ALIAS
# define JLN_MP_FORCE_LAZY_ALIAS 1
#endif

/// When 1, uses a memoization version of call to keep better track of calls
/// in the case of compilation error. This is especially useful with clang,
/// which doesn't display aliases.
#ifndef JLN_MP_DEBUG
# define JLN_MP_DEBUG 0
#endif

#if JLN_MP_DEBUG
# define JLN_MP_DEBUG_ORIGINAL 1
#else
# define JLN_MP_DEBUG_ORIGINAL 0
#endif

// Useless with gcc and msvc since it displays all the transformations.
#if JLN_MP_GCC || JLN_MP_MSVC || JLN_MP_MEMOIZED_ALIAS
# undef JLN_MP_DEBUG
# define JLN_MP_DEBUG 0
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
