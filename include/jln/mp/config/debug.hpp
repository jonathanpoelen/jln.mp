#pragma once

#define jln_MP_ENABLE_DEBUG 1

#if jln_MP_ENABLE_DEBUG
#  define JLN_MP_DEBUG_A(...) , __VA_ARGS__
#  define JLN_MP_DEBUG_B(...) __VA_ARGS__,
#  define JLN_MP_DEBUG(...) __VA_ARGS__
#else
#  define JLN_MP_DEBUG_A(...)
#  define JLN_MP_DEBUG_B(...)
#  define JLN_MP_DEBUG(...)
#endif
