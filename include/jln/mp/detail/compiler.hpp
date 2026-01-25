// SPDX-FileCopyrightText: 2026 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

/// \ingroup config

/// Check that a builtin exists.
#if defined(__has_builtin)
#  define JLN_MP_HAS_BUILTIN(name) __has_builtin(name)
#else
#  define JLN_MP_HAS_BUILTIN(name) 0
#endif

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

#ifndef JLN_MP_FEATURE_NONTYPE_TEMPLATE_CLASS
// note: should be __cpp_nontype_template_args >= 201911,
// but clang does not have this value because it does not fully support NTTP
#  if __cplusplus >= 202002L \
    && defined(__cpp_nontype_template_parameter_auto) \
    && __cpp_nontype_template_parameter_auto >= 201606L
#    define JLN_MP_FEATURE_NONTYPE_TEMPLATE_CLASS 1
#  else
#    define JLN_MP_FEATURE_NONTYPE_TEMPLATE_CLASS 0
#  endif
#endif

#ifndef JLN_MP_FEATURE_PACK_INDEXING
#  ifdef __cpp_pack_indexing
#    if __cpp_pack_indexing >= 202311L
#      define JLN_MP_FEATURE_PACK_INDEXING 1
#    endif
#  endif
#  ifndef JLN_MP_FEATURE_PACK_INDEXING
#      define JLN_MP_FEATURE_PACK_INDEXING 0
#  endif
#endif

/// When 1, the builtin __type_pack_element can be used.
#ifndef JLN_MP_FEATURE_TYPE_PACK_ELEMENT
# if JLN_MP_HAS_BUILTIN(__type_pack_element)
#   define JLN_MP_FEATURE_TYPE_PACK_ELEMENT 1
# else
#   define JLN_MP_FEATURE_TYPE_PACK_ELEMENT 0
# endif
#endif
//@}


// Compiler type and properties
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
#  ifndef JLN_MP_HAS_MEMOIZED_ALIAS
#    define JLN_MP_HAS_MEMOIZED_ALIAS 1
#  endif
#  ifndef JLN_MP_FAST_ALIAS_ON_VARIABLE_TEMPLATE
#    define JLN_MP_FAST_ALIAS_ON_VARIABLE_TEMPLATE 1
#  endif

// gcc
#elif defined(__GNUC__)
#  ifndef JLN_MP_GCC
#    define JLN_MP_GCC (__GNUC__ * 100 + __GNUC_MINOR__)
#  endif
#  ifndef JLN_MP_OPTIMIZED_ALIAS
#    define JLN_MP_OPTIMIZED_ALIAS 1
#  endif
#  ifndef JLN_MP_HAS_MEMOIZED_ALIAS
#    define JLN_MP_HAS_MEMOIZED_ALIAS 1
#  endif
#  ifndef JLN_MP_FAST_ALIAS_ON_VARIABLE_TEMPLATE
#    define JLN_MP_FAST_ALIAS_ON_VARIABLE_TEMPLATE 1
#  endif
#  if JLN_MP_FEATURE_CONCEPTS
#    ifndef JLN_MP_REQUIRES_AS_FAST_SFINAE
#      define JLN_MP_REQUIRES_AS_FAST_SFINAE 1
#    endif
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

/// The compiler presents itself as a clang without necessarily being so.
#ifndef JLN_MP_CLANG_LIKE
#  define JLN_MP_CLANG_LIKE 0
#endif
/// Is clang on MacOS.
#ifndef JLN_MP_APPLE_CLANG
#  define JLN_MP_APPLE_CLANG 0
#endif
/// The compiler presents itself as a msvc without necessarily being so.
#ifndef JLN_MP_MSVC_LIKE
#  define JLN_MP_MSVC_LIKE 0
#endif
/// The compiler is clang-cl.
#ifndef JLN_MP_CLANG_CL
#  define JLN_MP_CLANG_CL 0
#endif
/// The compiler is clang.
#ifndef JLN_MP_CLANG
#  define JLN_MP_CLANG 0
#endif
/// The compiler is cl.
#ifndef JLN_MP_MSVC
#  define JLN_MP_MSVC 0
#endif
/// The compiler is gcc.
#ifndef JLN_MP_GCC
#  define JLN_MP_GCC 0
#endif
/// The compiler is nvcc.
#ifndef JLN_MP_CUDA
#  define JLN_MP_CUDA 0
#endif
/// The host compiler is clang (in the case of nvcc).
#ifndef JLN_MP_HOST_COMPILER_CLANG
#  define JLN_MP_HOST_COMPILER_CLANG 0
#endif
/// The host compiler is gcc (in the case of nvcc).
#ifndef JLN_MP_HOST_COMPILER_GCC
#  define JLN_MP_HOST_COMPILER_GCC 0
#endif

/// When 1, the compiler considers an alias that makes
/// `alias<xs...>` = `F<xs...>` is identical to `F`.
/// Therefore, `cfe<alias>` and `cfe<F>` will be the same.
#ifndef JLN_MP_OPTIMIZED_ALIAS
#  define JLN_MP_OPTIMIZED_ALIAS 0
#endif

/// When 1, aliases are memoized. This means that calling a "slow" alias
/// a second time and with the same parameters will be fast.
#ifndef JLN_MP_HAS_MEMOIZED_ALIAS
#  define JLN_MP_HAS_MEMOIZED_ALIAS 0
#endif

/// When 1, `number<f_v<xs...>>` is faster than `f<xs...>::type`.
#ifndef JLN_MP_FAST_ALIAS_ON_VARIABLE_TEMPLATE
#  define JLN_MP_FAST_ALIAS_ON_VARIABLE_TEMPLATE 0
#endif

/// When 1, `requires` keyword is faster than traditional use of SFINAE.
#ifndef JLN_MP_REQUIRES_AS_FAST_SFINAE
#  define JLN_MP_REQUIRES_AS_FAST_SFINAE 0
#endif
#if !JLN_MP_FEATURE_CONCEPTS
#  undef JLN_MP_REQUIRES_AS_FAST_SFINAE
#  define JLN_MP_REQUIRES_AS_FAST_SFINAE 0
#endif

/// When 0, aliases are not context dependent and are resolved as soon as
/// possible which generate errors in contexts that should be lazy.
#ifndef JLN_MP_LAZY_ALIAS
# if JLN_MP_CLANG_LIKE
#   define JLN_MP_LAZY_ALIAS 0
# else
#   define JLN_MP_LAZY_ALIAS 1
# endif
#endif
//@}


// Pragma
//@{
#define JLN_MP_PRAGMA(x) JLN_MP_PRAGMA_I(x)

#ifdef _MSC_VER
#  define JLN_MP_PRAGMA_I(x) __pragma(x)
#else
#  define JLN_MP_PRAGMA_I(x) _Pragma(#x)
#endif
//@}


// Diagnostic
//@{
#ifdef JLN_MP_DOXYGENATING
/// Save state of the diagnostics.
#  define JLN_MP_DIAGNOSTIC_PUSH()
/// Restore state of the diagnostics.
#  define JLN_MP_DIAGNOSTIC_POP()
/// Ignore a specific diagnostic.
/// `xxx` can be replaced by one of the compilers below:\n
/// - `GCC_ONLY` for GCC compiler.\n
/// - `GCC` for GCC and Clang compilers.\n
/// - `CLANG` for Clang compiler.\n
/// - `MSVC` for the Microsoft compiler (cl).\n
/// - `CUDA` for the NVIDIA/CUDA compiler (nvcc).
#  define JLN_MP_DIAGNOSTIC_xxx_IGNORE(X)
/// Treat a specific diagnostic as a warning.
/// `xxx` can be replaced by one of the compilers
/// listed by \c JLN_MP_DIAGNOSTIC_xxx_IGNORE.
#  define JLN_MP_DIAGNOSTIC_xxx_WARNING(X)
/// Treat a specific diagnostic as a error.
/// `xxx` can be replaced by one of the compilers
/// listed by \c JLN_MP_DIAGNOSTIC_xxx_IGNORE.
#  define JLN_MP_DIAGNOSTIC_xxx_ERROR(X)
#endif

#if JLN_MP_CLANG_LIKE || JLN_MP_GCC
#  define JLN_MP_DIAGNOSTIC_PUSH() _Pragma("GCC diagnostic push")
#  define JLN_MP_DIAGNOSTIC_POP() _Pragma("GCC diagnostic pop")
#elif JLN_MP_MSVC
#  define JLN_MP_DIAGNOSTIC_PUSH() __pragma(warning(push))
#  define JLN_MP_DIAGNOSTIC_POP() __pragma(warning(pop))
#elif JLN_MP_CUDA
#  if JLN_MP_HOST_COMPILER_CLANG || JLN_MP_HOST_COMPILER_GCC
#    define JLN_MP_DIAGNOSTIC_PUSH() _Pragma("nv_diagnostic push") \
                                     _Pragma("GCC diagnostic push")
#    define JLN_MP_DIAGNOSTIC_POP() _Pragma("GCC diagnostic pop") \
                                    _Pragma("nv_diagnostic pop")
#  else
#    define JLN_MP_DIAGNOSTIC_PUSH() _Pragma("nv_diagnostic push")
#    define JLN_MP_DIAGNOSTIC_POP() _Pragma("nv_diagnostic pop")
#  endif
#else
#  define JLN_MP_DIAGNOSTIC_PUSH()
#  define JLN_MP_DIAGNOSTIC_POP()
#endif

#if JLN_MP_CLANG_LIKE || JLN_MP_GCC || JLN_MP_HOST_COMPILER_CLANG || JLN_MP_HOST_COMPILER_GCC
#  define JLN_MP_DIAGNOSTIC_GCC_IGNORE(X) JLN_MP_PRAGMA_I(GCC diagnostic ignored X)
#  define JLN_MP_DIAGNOSTIC_GCC_WARNING(X) JLN_MP_PRAGMA_I(GCC diagnostic warning X)
#  define JLN_MP_DIAGNOSTIC_GCC_ERROR(X) JLN_MP_PRAGMA_I(GCC diagnostic error X)
#else
#  define JLN_MP_DIAGNOSTIC_GCC_IGNORE(X)
#  define JLN_MP_DIAGNOSTIC_GCC_WARNING(X)
#  define JLN_MP_DIAGNOSTIC_GCC_ERROR(X)
#endif

#if JLN_MP_MSVC
#  define JLN_MP_DIAGNOSTIC_MSVC_IGNORE(X) JLN_MP_PRAGMA_I(warning(disable:X))
#  define JLN_MP_DIAGNOSTIC_MSVC_WARNING(X) JLN_MP_PRAGMA_I(warning(4:X))
#  define JLN_MP_DIAGNOSTIC_MSVC_ERROR(X) JLN_MP_PRAGMA_I(error(X))
#else
#  define JLN_MP_DIAGNOSTIC_MSVC_IGNORE(X)
#  define JLN_MP_DIAGNOSTIC_MSVC_WARNING(X)
#  define JLN_MP_DIAGNOSTIC_MSVC_ERROR(X)
#endif

#if JLN_MP_CUDA
#  define JLN_MP_DIAGNOSTIC_CUDA_IGNORE(X) JLN_MP_PRAGMA_I(nv_diag_suppress X)
#  define JLN_MP_DIAGNOSTIC_CUDA_WARNING(X) JLN_MP_PRAGMA_I(nv_diag_warn X)
#  define JLN_MP_DIAGNOSTIC_CUDA_ERROR(X) JLN_MP_PRAGMA_I(nv_diag_error X)
#else
#  define JLN_MP_DIAGNOSTIC_CUDA_IGNORE(X)
#  define JLN_MP_DIAGNOSTIC_CUDA_WARNING(X)
#  define JLN_MP_DIAGNOSTIC_CUDA_ERROR(X)
#endif

#if JLN_MP_CLANG_LIKE || JLN_MP_HOST_COMPILER_CLANG
#  define JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE(X)
#  define JLN_MP_DIAGNOSTIC_CLANG_IGNORE JLN_MP_DIAGNOSTIC_GCC_IGNORE
#  define JLN_MP_DIAGNOSTIC_GCC_ONLY_WARNING(X)
#  define JLN_MP_DIAGNOSTIC_CLANG_WARNING JLN_MP_DIAGNOSTIC_GCC_WARNING
#  define JLN_MP_DIAGNOSTIC_GCC_ONLY_ERROR(X)
#  define JLN_MP_DIAGNOSTIC_CLANG_ERROR JLN_MP_DIAGNOSTIC_GCC_ERROR
#else
#  define JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE JLN_MP_DIAGNOSTIC_GCC_IGNORE
#  define JLN_MP_DIAGNOSTIC_CLANG_IGNORE(X)
#  define JLN_MP_DIAGNOSTIC_GCC_ONLY_WARNING JLN_MP_DIAGNOSTIC_GCC_WARNING
#  define JLN_MP_DIAGNOSTIC_CLANG_WARNING(X)
#  define JLN_MP_DIAGNOSTIC_GCC_ONLY_ERROR JLN_MP_DIAGNOSTIC_GCC_ERROR
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

#if JLN_MP_CLANG >= 2101
// clang bug:
// - https://stackoverflow.com/a/78746171
// - https://github.com/llvm/llvm-project/issues/95280
#  define JLN_MP_DIAGNOSTIC_IGNORE_BOGUS_WNRVO() \
  JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wnrvo")
#else
#  define JLN_MP_DIAGNOSTIC_IGNORE_BOGUS_WNRVO()
#endif

#if JLN_MP_FEATURE_PACK_INDEXING && JLN_MP_CLANG && __cplusplus < 202400L
#  define JLN_MP_DIAGNOSTIC_IGNORE_PACK_INDEXING_EXTENSION() \
  JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wc++26-extensions")
#else
#  define JLN_MP_DIAGNOSTIC_IGNORE_PACK_INDEXING_EXTENSION()
#endif
//@}


// keywords
//@{
#if defined(__cpp_consteval) && __cpp_consteval >= 201811L
#  define JLN_MP_CONSTEVAL_OR_CONSTEXPR consteval
#else
#  define JLN_MP_CONSTEVAL_OR_CONSTEXPR constexpr
#endif
//@}


// special wrapper for specialization of variable template or struct
//@{
#if JLN_MP_FAST_ALIAS_ON_VARIABLE_TEMPLATE
#  define JLN_MP_NUMBER_FROM_VARIABLE_TEMPLATE_OR_TYPE(expr_v, expr_impl, ...) \
  number<expr_v<__VA_ARGS__>>
#else
#  define JLN_MP_NUMBER_FROM_VARIABLE_TEMPLATE_OR_TYPE(expr_v, expr_impl, ...) \
  typename expr_impl<__VA_ARGS__>::type
#endif
#define JLN_MP_NUMBER_FROM_REGULAR_VARIABLE_TEMPLATE_OR_TYPE(name, ...) \
  JLN_MP_NUMBER_FROM_VARIABLE_TEMPLATE_OR_TYPE(emp::name##_v, detail::name##_impl, __VA_ARGS__)
//@}

// Pack indexing and __type_pack_element configuration
//@{
/// When 1, the builtin __type_pack_element can be used and is very fast.
/// With Clang, a non-memoized version takes longer on the second call than a memoized version.
#ifndef JLN_MP_HAS_MEMOIZED_TYPE_PACK_ELEMENT
# if JLN_MP_FEATURE_TYPE_PACK_ELEMENT && JLN_MP_GCC
#   define JLN_MP_HAS_MEMOIZED_TYPE_PACK_ELEMENT 1
# else
#   define JLN_MP_HAS_MEMOIZED_TYPE_PACK_ELEMENT 0
# endif
#endif

/// When 1, pack indexing (`xs...[i]`) can be used and is very fast.
/// With Clang, a non-memoized version takes longer on the fourth call than a memoized version.
#ifndef JLN_MP_HAS_MEMOIZED_PACK_INDEXING
# if JLN_MP_FEATURE_PACK_INDEXING && JLN_MP_GCC
#   define JLN_MP_HAS_MEMOIZED_PACK_INDEXING 1
# else
#   define JLN_MP_HAS_MEMOIZED_PACK_INDEXING 0
# endif
#endif

/// When 1, the builtin __type_pack_element can be used with chaining.
/// The gcc version of __type_pack_element is somewhat buggy and does
/// not support chaining: \c `__type_pack_element<i,a,b>::type` // error
#ifndef JLN_MP_CHANING_TYPE_PACK_ELEMENT
# if JLN_MP_FEATURE_TYPE_PACK_ELEMENT && !JLN_MP_GCC && !JLN_MP_HOST_COMPILER_GCC
#   define JLN_MP_CHANING_TYPE_PACK_ELEMENT 1
# else
#   define JLN_MP_CHANING_TYPE_PACK_ELEMENT 0
# endif
#endif

/// Call `__type_pack_element` or use pack indexing feature.
/// This macro is not defined if the features do not exist.
/// \attention The gcc version of `__type_pack_element` is somewhat
/// buggy and does not support chaining:\n
/// \c __type_pack_element<i,a,b>::type // error
/// \see JLN_MP_PACK_AT_SAFE
#if JLN_MP_FEATURE_PACK_INDEXING
# define JLN_MP_PACK_AT(xs, ...) xs...[__VA_ARGS__]
#elif JLN_MP_FEATURE_TYPE_PACK_ELEMENT
# define JLN_MP_PACK_AT(xs, ...) __type_pack_element<__VA_ARGS__, xs...>
#endif

/// When 1, \c JLN_MP_PACK_AT can be used and is very fast.
#if JLN_MP_HAS_MEMOIZED_PACK_INDEXING || JLN_MP_HAS_MEMOIZED_TYPE_PACK_ELEMENT
# define JLN_MP_HAS_MEMOIZED_PACK_AT 1
#elif JLN_MP_FEATURE_TYPE_PACK_ELEMENT
# define JLN_MP_HAS_MEMOIZED_PACK_AT 0
#endif

/// Version of \c JLN_MP_PACK_AT defined only if expression is "safe".
/// \see JLN_MP_PACK_AT
#if JLN_MP_FEATURE_PACK_INDEXING || JLN_MP_CHANING_TYPE_PACK_ELEMENT
# define JLN_MP_PACK_AT_SAFE(xs, ...) JLN_MP_PACK_AT(xs, __VA_ARGS__)
#endif
//@}


/// Checks that a value respects a condition and is different from 0.
/// ex: `JLN_MP_WORKAROUND(JLN_MP_GCC, < 1200)`.
#define JLN_MP_WORKAROUND(symbol, test) ((symbol) != 0 && ((symbol) test))

/// When 1, algorithms using friend injection its accessible
#ifndef JLN_MP_ENABLE_FRIEND_INJECTION
# define JLN_MP_ENABLE_FRIEND_INJECTION 1
#endif

/// Displays parameters. Useful in a macro to remove parentheses from a value.
#define JLN_MP_UNPACK(...) __VA_ARGS__
