// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/compiler.hpp>

// Fast convertion to bool.
// If the value is more likely to be a bool, preferred bool(expr)

#if JLN_MP_GCC
#  define JLN_MP_RAW_EXPR_TO_BOOL(...) __VA_ARGS__ ? true : false
#  define JLN_MP_RAW_EXPR_TO_BOOL_NOT(...) __VA_ARGS__ ? false : true
#  define JLN_MP_EXPR_TO_BOOL(...) __VA_ARGS__ ? true : false
#  define JLN_MP_EXPR_TO_BOOL_NOT(...) __VA_ARGS__ ? false : true
#elif JLN_MP_CLANG
#  define JLN_MP_RAW_EXPR_TO_BOOL(...) !!__VA_ARGS__
#  define JLN_MP_RAW_EXPR_TO_BOOL_NOT(...) !__VA_ARGS__
#  define JLN_MP_EXPR_TO_BOOL(...) !!(__VA_ARGS__)
#  define JLN_MP_EXPR_TO_BOOL_NOT(...) !(__VA_ARGS__)
#else
#  define JLN_MP_RAW_EXPR_TO_BOOL(...) bool(__VA_ARGS__)
#  define JLN_MP_RAW_EXPR_TO_BOOL_NOT(...) !__VA_ARGS__
#  define JLN_MP_EXPR_TO_BOOL(...) bool(__VA_ARGS__)
#  define JLN_MP_EXPR_TO_BOOL_NOT(...) !(__VA_ARGS__)
#endif
