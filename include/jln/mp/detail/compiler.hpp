// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

// Compiler type
//@{
// cuda
#if defined(__CUDACC__)
#  ifndef JLN_MP_CUDA
#    define JLN_MP_CUDA (__CUDACC_VER_MAJOR__ * 100 + __CUDACC_VER_MINOR__)
#  endif
#  if defined(__clang__)
#    ifndef JLN_MP_HOST_COMPILER_CLANG
#      define JLN_MP_HOST_COMPILER_CLANG (__clang_major__ * 100 + __clang_minor__)
#    endif
#  elif defined(__GNUC__)
#    ifndef JLN_MP_HOST_COMPILER_GCC
#      define JLN_MP_HOST_COMPILER_GCC (__GNUC__ * 100 + __GNUC_MINOR__)
#    endif
#  endif

// clang-cl
#elif defined(_MSC_VER) && defined(__clang__)
#  ifndef JLN_MP_MSVC_LIKE
#    define JLN_MP_MSVC_LIKE _MSC_VER
#  endif
#  ifndef JLN_MP_CLANG_CL
#    define JLN_MP_CLANG_CL (__clang_major__ * 100 + __clang_minor__)
#  endif

// clang
#elif defined(__clang__)
#  ifndef JLN_MP_CLANG
#    define JLN_MP_CLANG (__clang_major__ * 100 + __clang_minor__)
#  endif

// msvc
#elif defined(_MSC_VER)
#  ifndef JLN_MP_MSVC_LIKE
#    define JLN_MP_MSVC_LIKE _MSC_VER
#  endif
#  ifndef JLN_MP_MSVC
#    define JLN_MP_MSVC _MSC_VER
#  endif
#  ifndef JLN_MP_MEMOIZED_ALIAS
#    define JLN_MP_MEMOIZED_ALIAS 1
#  endif

// gcc
#elif defined(__GNUC__)
#  ifndef JLN_MP_GCC
#    define JLN_MP_GCC (__GNUC__ * 100 + __GNUC_MINOR__)
#  endif
#  ifndef JLN_MP_OPTIMIZED_ALIAS
#    define JLN_MP_OPTIMIZED_ALIAS 1
#  endif
#  ifndef JLN_MP_MEMOIZED_ALIAS
#    define JLN_MP_MEMOIZED_ALIAS 1
#  endif
#endif

// clang like
#if defined(__clang__)
#  ifndef JLN_MP_CLANG_LIKE
#    define JLN_MP_CLANG_LIKE (__clang_major__ * 100 + __clang_minor__)
#  endif
#endif

// apple
#if defined(__APPLE__) && JLN_MP_CLANG
#  ifndef JLN_MP_APPLE_CLANG
#    define JLN_MP_APPLE_CLANG JLN_MP_CLANG
#  endif
#endif

#ifndef JLN_MP_CLANG_LIKE
#  define JLN_MP_CLANG_LIKE 0
#endif
#ifndef JLN_MP_APPLE_CLANG
#  define JLN_MP_APPLE_CLANG 0
#endif
#ifndef JLN_MP_MSVC_LIKE
#  define JLN_MP_MSVC_LIKE 0
#endif
#ifndef JLN_MP_CLANG_CL
#  define JLN_MP_CLANG_CL 0
#endif
#ifndef JLN_MP_CLANG
#  define JLN_MP_CLANG 0
#endif
#ifndef JLN_MP_MSVC
#  define JLN_MP_MSVC 0
#endif
#ifndef JLN_MP_GCC
#  define JLN_MP_GCC 0
#endif
#ifndef JLN_MP_CUDA
#  define JLN_MP_CUDA 0
#endif
#ifndef JLN_MP_HOST_COMPILER_CLANG
#  define JLN_MP_HOST_COMPILER_CLANG 0
#endif
#ifndef JLN_MP_HOST_COMPILER_GCC
#  define JLN_MP_HOST_COMPILER_GCC 0
#endif

#ifndef JLN_MP_OPTIMIZED_ALIAS
#  define JLN_MP_OPTIMIZED_ALIAS 0
#endif
#ifndef JLN_MP_MEMOIZED_ALIAS
#  define JLN_MP_MEMOIZED_ALIAS 0
#endif
//@}

#define JLN_MP_WORKAROUND(symbol, test) ((symbol) != 0 && ((symbol) test))

#if defined(__has_builtin)
#  define JLN_MP_HAS_BUILTIN(name) __has_builtin(name)
#else
#  define JLN_MP_HAS_BUILTIN(name) 0
#endif

// Pragma
//@{
#define JLN_MP_PRAGMA(x) JLN_MP_PRAGMA_I(x)

#ifdef _MSC_VER
#  define JLN_MP_PRAGMA_I(x) __pragma(x)
#else
#  define JLN_MP_PRAGMA_I(x) _Pragma(#x)
#endif
//@}

// Features
//@{
#ifndef JLN_MP_FEATURE_CONCEPTS
#  ifdef __cpp_concepts
#    if __cpp_concepts >= 201907L
#      define JLN_MP_FEATURE_CONCEPTS 1
#    endif
#  endif
#  ifndef JLN_MP_FEATURE_CONCEPTS
#      define JLN_MP_FEATURE_CONCEPTS 0
#  endif
#endif
//@}

// Diagnostic
//@{
#if JLN_MP_CLANG_LIKE || JLN_MP_GCC

#  define JLN_MP_DIAGNOSTIC_PUSH() _Pragma("GCC diagnostic push")
#  define JLN_MP_DIAGNOSTIC_POP() _Pragma("GCC diagnostic pop")

#  define JLN_MP_DIAGNOSTIC_MSVC_IGNORE(X)
#  define JLN_MP_DIAGNOSTIC_GCC_IGNORE(X) JLN_MP_PRAGMA_I(GCC diagnostic ignored X)
#  define JLN_MP_DIAGNOSTIC_MSVC_WARNING(X)
#  define JLN_MP_DIAGNOSTIC_GCC_WARNING(X) JLN_MP_PRAGMA_I(GCC diagnostic warning X)
#  define JLN_MP_DIAGNOSTIC_MSVC_ERROR(X)
#  define JLN_MP_DIAGNOSTIC_GCC_ERROR(X) JLN_MP_PRAGMA_I(GCC diagnostic error X)
#  ifdef __clang__
#    define JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE(X)
#    define JLN_MP_DIAGNOSTIC_CLANG_IGNORE JLN_MP_DIAGNOSTIC_GCC_IGNORE
#    define JLN_MP_DIAGNOSTIC_GCC_ONLY_WARNING(X)
#    define JLN_MP_DIAGNOSTIC_CLANG_WARNING JLN_MP_DIAGNOSTIC_GCC_WARNING
#    define JLN_MP_DIAGNOSTIC_GCC_ONLY_ERROR(X)
#    define JLN_MP_DIAGNOSTIC_CLANG_ERROR JLN_MP_DIAGNOSTIC_GCC_ERROR
#  else
#    define JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE JLN_MP_DIAGNOSTIC_GCC_IGNORE
#    define JLN_MP_DIAGNOSTIC_CLANG_IGNORE(X)
#    define JLN_MP_DIAGNOSTIC_GCC_ONLY_WARNING JLN_MP_DIAGNOSTIC_GCC_WARNING
#    define JLN_MP_DIAGNOSTIC_CLANG_WARNING(X)
#    define JLN_MP_DIAGNOSTIC_GCC_ONLY_ERROR JLN_MP_DIAGNOSTIC_GCC_ERROR
#    define JLN_MP_DIAGNOSTIC_CLANG_ERROR(X)
#  endif

#elif JLN_MP_MSVC

#  define JLN_MP_DIAGNOSTIC_PUSH() __pragma(warning(push))
#  define JLN_MP_DIAGNOSTIC_POP() __pragma(warning(pop))

#  define JLN_MP_DIAGNOSTIC_MSVC_IGNORE(X) JLN_MP_PRAGMA_I(warning(disable:X))
#  define JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE(X)
#  define JLN_MP_DIAGNOSTIC_GCC_IGNORE(X)

#  define JLN_MP_DIAGNOSTIC_MSVC_WARNING(X) JLN_MP_PRAGMA_I(warning(4:X))
#  define JLN_MP_DIAGNOSTIC_GCC_ONLY_WARNING(X)
#  define JLN_MP_DIAGNOSTIC_GCC_WARNING(X)

#  define JLN_MP_DIAGNOSTIC_MSVC_ERROR(X) JLN_MP_PRAGMA_I(error(X))
#  define JLN_MP_DIAGNOSTIC_GCC_ONLY_ERROR(X)
#  define JLN_MP_DIAGNOSTIC_GCC_ERROR(X)

#  if JLN_MP_CLANG_LIKE
#    define JLN_MP_DIAGNOSTIC_CLANG_IGNORE(X) JLN_MP_PRAGMA_I(GCC diagnostic ignored X)
#    define JLN_MP_DIAGNOSTIC_CLANG_WARNING(X) JLN_MP_PRAGMA_I(GCC diagnostic warning X)
#    define JLN_MP_DIAGNOSTIC_CLANG_ERROR(X) JLN_MP_PRAGMA_I(GCC diagnostic error X)
#  else
#    define JLN_MP_DIAGNOSTIC_CLANG_IGNORE(X)
#    define JLN_MP_DIAGNOSTIC_CLANG_WARNING(X)
#    define JLN_MP_DIAGNOSTIC_CLANG_ERROR(X)
#  endif

#else

#  define JLN_MP_DIAGNOSTIC_PUSH()
#  define JLN_MP_DIAGNOSTIC_POP()

#  define JLN_MP_DIAGNOSTIC_MSVC_IGNORE(X)
#  define JLN_MP_DIAGNOSTIC_GCC_IGNORE(X)
#  define JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE(X)
#  define JLN_MP_DIAGNOSTIC_CLANG_IGNORE(X)

#  define JLN_MP_DIAGNOSTIC_MSVC_WARNING(X)
#  define JLN_MP_DIAGNOSTIC_GCC_WARNING(X)
#  define JLN_MP_DIAGNOSTIC_GCC_ONLY_WARNING(X)
#  define JLN_MP_DIAGNOSTIC_CLANG_WARNING(X)

#  define JLN_MP_DIAGNOSTIC_MSVC_ERROR(X)
#  define JLN_MP_DIAGNOSTIC_GCC_ERROR(X)
#  define JLN_MP_DIAGNOSTIC_GCC_ONLY_ERROR(X)
#  define JLN_MP_DIAGNOSTIC_CLANG_ERROR(X)

#endif
//@}

// special diagnostic
//@{
#if JLN_MP_CLANG >= 1600
#  define JLN_MP_DIAGNOSTIC_IGNORE_UNSAFE_BUFFER_USAGE() \
  JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wunsafe-buffer-usage")
#else
#  define JLN_MP_DIAGNOSTIC_IGNORE_UNSAFE_BUFFER_USAGE()
#endif
//@}
