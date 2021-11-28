#pragma once

#include <jln/mp/detail/compiler.hpp>

#ifndef JLN_MP_ENABLE_DEBUG
#  define JLN_MP_ENABLE_DEBUG 0
#endif

// useless with gcc and msvc since it displays all the transformations
#if (JLN_MP_GCC || JLN_MP_MSVC) && !defined(JLN_MP_FORCE_DEBUG)
#  undef JLN_MP_ENABLE_DEBUG
#  define JLN_MP_ENABLE_DEBUG 0
#endif
