#pragma once

#include <jln/mp/detail/compiler.hpp>

#ifndef JLN_MP_ENABLE_DEBUG
#  define JLN_MP_ENABLE_DEBUG 0
#endif

// useless with gcc since it displays all the transformations
#if JLN_MP_GCC && !defined(JLN_MP_ENABLE_GCC_DEBUG)
#  undef JLN_MP_ENABLE_DEBUG
#  define JLN_MP_ENABLE_DEBUG 0
#endif
