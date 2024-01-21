// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
// Amalgamated version of https://github.com/jonathanpoelen/jln.mp

#pragma once

#ifndef JLN_MP_HPP
#define JLN_MP_HPP

#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <utility>


namespace jln::mp
{
  /// \ingroup functional

  /// \treturn \value
  struct identity
  {
    template<class x>
    using f = x;
  };

  namespace emp
  {
    template<class x>
    using identity = x;
  }
  /// \ingroup list

  template<class... xs>
  class list {};
} // namespace jln::mp
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

#ifndef JLN_MP_ENABLE_DEBUG
#  define JLN_MP_ENABLE_DEBUG 0
#endif

// useless with gcc and msvc since it displays all the transformations
#if JLN_MP_GCC || JLN_MP_MSVC || JLN_MP_MEMOIZED_ALIAS
#  undef JLN_MP_ENABLE_DEBUG
#  define JLN_MP_ENABLE_DEBUG 0
#endif
#ifndef JLN_MP_MAX_CALL_ELEMENT
# define JLN_MP_MAX_CALL_ELEMENT 10000
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

namespace jln::mp
{
  /// \ingroup utility

  template<bool>
  struct conditional_c;

  template<>
  struct conditional_c<true>
  {
    template<class true_value, class false_value>
    using f = true_value;
  };

  template<>
  struct conditional_c<false>
  {
    template<class true_value, class false_value>
    using f = false_value;
  };

  template<class bool_>
  using conditional = conditional_c<JLN_MP_RAW_EXPR_TO_BOOL(bool_::value)>;

  namespace emp
  {
    template<class bool_, class true_value, class false_value>
    using conditional = typename mp::conditional_c<JLN_MP_RAW_EXPR_TO_BOOL(bool_::value)>
      ::template f<true_value, false_value>;

    template<bool bool_, class true_value, class false_value>
    using conditional_c = typename mp::conditional_c<bool_>
      ::template f<true_value, false_value>;
  }
  /// Value that is not available.
  /// This type is used in `smp` for a contract that is not respected.
  struct na {};

#if !JLN_MP_MEMOIZED_ALIAS || JLN_MP_MSVC

# if !JLN_MP_CUDA
  /// \cond
  namespace detail
  {
    template<class F, class... Params>
    struct memoizer_impl;
  }
  /// \endcond

  /// \ingroup functional

  /// Memoization version of \link call.
  template<class C, class... xs>
  using memoize_call = typename detail::memoizer_impl<C, xs...>::type;

  /// Memoize a call to \c C::f<xs...>.
  template<class C>
  struct memoize
  {
    template<class... xs>
    using f = typename detail::memoizer_impl<C, xs...>::type;
  };

# else // if JLN_MP_CUDA

  /// \cond
  namespace detail
  {
    template<class dummy, class F, class... Params>
    struct memoizer_impl;
  }
  /// \endcond

  /// \ingroup functional

  /// Memoization version of \link call.
  template<class C, class... xs>
  using memoize_call = typename detail::memoizer_impl<void, C, xs...>::type;

  /// Memoize a call to \c C::f<xs...>.
  template<class C>
  struct memoize
  {
    template<class... xs>
    using f = typename detail::memoizer_impl<void, C, xs...>::type;
  };

# endif

# define JLN_MP_MEMOIZE(...) ::jln::mp::memoize<__VA_ARGS__>

#else // if JLN_MP_MEMOIZED_ALIAS && !JLN_MP_MSVC
  template<class C, class... xs>
  using memoize_call = typename conditional_c<!sizeof...(xs)>
    ::template f<C, C>
    ::template f<xs...>;

  template<class C>
  struct memoize
  {
    template<class... xs>
    using f = typename conditional_c<!sizeof...(xs)>
      ::template f<C, C>
      ::template f<xs...>;
  };

# define JLN_MP_MEMOIZE(...) __VA_ARGS__
#endif
}

/// \cond
// # if !JLN_MP_CUDA
// # endif

#if !JLN_MP_MEMOIZED_ALIAS || JLN_MP_MSVC

namespace jln::mp::detail
{
  struct uncallable_function
  {
    using try_type = na;
  };

  template<class T>
  struct memoize_result
  {
    using type = T;
    using try_type = T;
  };

# if !JLN_MP_CUDA
  template<class F, class... Params>
  memoize_result<
    typename conditional_c<!sizeof...(Params)>
    ::template f<F, F>
    ::template f<Params...>
  > memoized_call(list<Params...>*);

  template<class F>
  uncallable_function memoized_call(void*);

  template<class C, class... Params>
  struct memoizer_impl : decltype(memoized_call<C>(static_cast<list<Params...>*>(nullptr)))
  {};
#else // if JLN_MP_CUDA
  template<class dummy, class F, class... Params>
  struct memoizer_impl : uncallable_function
  {};

  template<class> using void_t = void;

  template<class F, class... Params>
  struct memoizer_impl<void_t<typename F::template f<Params...>>, F, Params...>
    : memoize_result<typename F::template f<Params...>>
  {};
# endif
}
#else // if JLN_MP_MEMOIZED_ALIAS && !JLN_MP_MSVC
namespace jln::mp::detail
{
  struct uncallable_function
  {};
}
#endif
/// \endcond

namespace jln::mp
{
  /// \ingroup number

  using int_ = std::intmax_t;
  using uint_ = std::uintmax_t;

  template<int_ v>
  struct number { static const int_ value = v; };

  using true_ = number<1>;
  using false_ = number<0>;

#ifndef JLN_MP_ENABLE_TPL_AUTO
# if defined( __cpp_nontype_template_parameter_auto)
#   if __cpp_nontype_template_parameter_auto >= 201606L
#     define JLN_MP_ENABLE_TPL_AUTO 1
#   endif
# endif
#endif

#ifndef JLN_MP_ENABLE_TPL_AUTO
# define JLN_MP_ENABLE_TPL_AUTO 0
#endif

#if JLN_MP_ENABLE_TPL_AUTO
# define JLN_MP_TPL_AUTO_OR_INT auto
# define JLN_MP_TPL_AUTO_OR(T) auto
#else
# define JLN_MP_TPL_AUTO_OR_INT ::jln::mp::int_
# define JLN_MP_TPL_AUTO_OR(T) T
#endif
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool> struct dcallf;
    template<bool> struct dcall_c;
    template<bool> struct dcallf_c;

    class too_many_arguments_error {};
  }
  /// \endcond

  /// \ingroup functional


#define JLN_MP_IDENT(...) __VA_ARGS__

#if ! JLN_MP_ENABLE_DEBUG
  #define JLN_MP_TRACE_F(...) __VA_ARGS__
  #define JLN_MP_TRACE_TYPENAME

  #define JLN_MP_CALL_TRACE(C, ...) typename C::template f<__VA_ARGS__>
  #define JLN_MP_CALL_TRACE_T(C, ...) typename C::template f<__VA_ARGS__>
  #define JLN_MP_CALL_TRACE_0_ARG(...) typename __VA_ARGS__::template f<>
#else
  // does not compile without memoize with msvc...
  #define JLN_MP_TRACE_F(...) memoize<__VA_ARGS__>
  #define JLN_MP_TRACE_TYPENAME typename

#if JLN_MP_CUDA
  #define JLN_MP_CALL_TRACE(C, ...) \
    typename ::jln::mp::detail::memoizer_impl<void, C, __VA_ARGS__>::type
  #define JLN_MP_CALL_TRACE_T(C, ...) \
    typename ::jln::mp::detail::memoizer_impl<void, typename C, __VA_ARGS__>::type
  #define JLN_MP_CALL_TRACE_0_ARG(...) \
    typename ::jln::mp::detail::memoizer_impl<void, __VA_ARGS__>::type
#else // if !JLN_MP_CUDA
  #define JLN_MP_CALL_TRACE(C, ...) \
    typename ::jln::mp::detail::memoizer_impl<C, __VA_ARGS__>::type
  #define JLN_MP_CALL_TRACE_T(C, ...) \
    typename ::jln::mp::detail::memoizer_impl<typename C, __VA_ARGS__>::type
  #define JLN_MP_CALL_TRACE_0_ARG(...) \
    typename ::jln::mp::detail::memoizer_impl<__VA_ARGS__>::type
#endif
#endif

#if JLN_MP_CLANG_LIKE
# define JLN_MP_MEMOIZE_CALL(C, ...) ::jln::mp::memoize_call<C, __VA_ARGS__>
# define JLN_MP_MEMOIZE_CALL_F(C, ...) ::jln::mp::memoize_call<C, __VA_ARGS__>
#else
# define JLN_MP_MEMOIZE_CALL(C, ...) typename JLN_MP_TRACE_F(C)::template f<__VA_ARGS__>
# define JLN_MP_MEMOIZE_CALL_F(C, ...) JLN_MP_TRACE_F(C)::template f<__VA_ARGS__>
#endif

#ifdef JLN_MP_DOXYGENATING

template<class C, class... xs>
using call = C::f<xs...>;

#define JLN_MP_DCALL_TRACE_XS(xs, C, ...) call<C, __VA_ARGS__>
#define JLN_MP_DCALL_TRACE_XS_0(xs, C) call<__VA_ARGS__>
#define JLN_MP_DCALL_V_TRACE_XS(xs, C, ...) call<C, __VA_ARGS__>
#define JLN_MP_FORCE_DCALL_TRACE_XS(xs, C, ...) call<C, __VA_ARGS__>
#define JLN_MP_FORCE_DCALL_V_TRACE_XS(xs, C, ...) call<C, __VA_ARGS__>
#define JLN_MP_DCALLF_XS(xs, F, ...) F<__VA_ARGS__>
#define JLN_MP_DCALLF_V_XS(xs, F, ...) F<__VA_ARGS__>
#define JLN_MP_DCALLF_C_XS(xs, F, ...) F<__VA_ARGS__>

#else

#define JLN_MP_DCALLF_XS(xs, C, ...)                               \
  typename detail::dcallf<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT> \
    ::template f<C, __VA_ARGS__>

#define JLN_MP_DCALLF_XS_0(xs, C)                                  \
  typename detail::dcallf<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT> \
    ::template f<C>

#define JLN_MP_DCALLF_V_XS(xs, C, ...)                    \
  detail::dcallf<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT> \
    ::template f<C, __VA_ARGS__>

#define JLN_MP_DCALLF_C_XS(xs, C, ...)                               \
  typename detail::dcallf_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT> \
    ::template f<C, __VA_ARGS__>

# if JLN_MP_MSVC

template<class C, class... xs>
using call = typename detail::memoizer_impl<C, xs...>::type;

#  define JLN_MP_DCALL_C(xs, C)                                              \
  typename ::jln::mp::conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT> \
    ::template f<C, C>

#  define JLN_MP_DCALL_TRACE_XS(xs, C, ...) \
    typename ::jln::mp::detail::memoizer_impl<C, __VA_ARGS__>::type

#  define JLN_MP_FORCE_DCALL_TRACE_XS(xs, C, ...) \
    typename ::jln::mp::detail::memoizer_impl<JLN_MP_DCALL_C(xs, C), __VA_ARGS__>::type

#  define JLN_MP_DCALL_TRACE_XS_0(xs, C) \
    typename ::jln::mp::detail::memoizer_impl<JLN_MP_DCALL_C(xs, C)>::type

#  define JLN_MP_DCALL_V_TRACE_XS(xs, C, ...) \
    ::jln::mp::detail::memoizer_impl<C, __VA_ARGS__>::type

#  define JLN_MP_FORCE_DCALL_V_TRACE_XS(xs, C, ...) \
    ::jln::mp::detail::memoizer_impl<JLN_MP_DCALL_C(xs, C), __VA_ARGS__>::type

# else

template<class C, class... xs>
using call = typename conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
  ::template f<C, detail::too_many_arguments_error>
  ::template f<xs...>;

#  define JLN_MP_DCALL_TRACE_XS(xs, C, ...)                                        \
    typename ::jln::mp::conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>     \
      ::template f<JLN_MP_TRACE_F(C), ::jln::mp::detail::too_many_arguments_error> \
      ::template f<__VA_ARGS__>

#  define JLN_MP_FORCE_DCALL_TRACE_XS JLN_MP_DCALL_TRACE_XS

#  define JLN_MP_DCALL_TRACE_XS_0(xs, C)                                           \
    typename ::jln::mp::conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>     \
      ::template f<JLN_MP_TRACE_F(C), ::jln::mp::detail::too_many_arguments_error> \
      ::template f<>

#  define JLN_MP_DCALL_V_TRACE_XS(xs, C, ...)                                      \
    ::jln::mp::conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>              \
      ::template f<JLN_MP_TRACE_F(C), ::jln::mp::detail::too_many_arguments_error> \
      ::template f<__VA_ARGS__>

#  define JLN_MP_FORCE_DCALL_V_TRACE_XS JLN_MP_DCALL_V_TRACE_XS

# endif
#endif

#define JLN_MP_CALLER_TRACE_XS(xs, ...)                             \
  ::jln::mp::conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT> \
    ::template f<__VA_ARGS__, ::jln::mp::detail::too_many_arguments_error>


#if JLN_MP_MSVC
# define JLN_MP_MSVC_FIX_CALL(C, ...) \
  ::jln::mp::detail::raw_call<typename JLN_MP_IDENT C, __VA_ARGS__>

# define JLN_MP_MSVC_FIX_CALL_T(C, ...) \
  ::jln::mp::detail::raw_call<JLN_MP_IDENT C, __VA_ARGS__>
#else
# define JLN_MP_MSVC_FIX_CALL(C, ...) typename JLN_MP_IDENT C::template f<__VA_ARGS__>
# define JLN_MP_MSVC_FIX_CALL_T(C, ...) typename JLN_MP_IDENT C::template f<__VA_ARGS__>
#endif


template<class C, JLN_MP_TPL_AUTO_OR_INT... xs>
using call_c = typename detail::dcall_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
  ::template f<C, xs...>;

template<class C, class... xs>
using call_t = typename call<C, xs...>::type;

}

/// \cond
namespace jln::mp::detail
{
  template<>
  struct dcall_c<true>
  {
      template<class C, JLN_MP_TPL_AUTO_OR_INT...xs>
      using f = typename C::template f<xs...>;
  };

  template<>
  struct dcallf<true>
  {
    template<template<class...> class F, class... xs>
    using f = F<xs...>;
  };

  template<>
  struct dcallf_c<true>
  {
      template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, JLN_MP_TPL_AUTO_OR_INT...xs>
      using f = F<xs...>;
  };

  // useful to work around msvc bugs
  template<class F, class... xs>
  using raw_call = typename F::template f<xs...>;


  template<class C>
  struct call_trace_xs_0
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS_0(xs, C);
  };

  template<class C>
  struct call_trace_xs
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };

  struct call_trace_c0_arg
  {
    template<class C, class...>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup functional

  /// Makes a \function from a \lazymetafunction.
  /// \treturn \value
  /// \see lift
  template<template<class...> class F, class C = identity>
  struct lift_t
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_XS(xs, F, xs...)::type);
  };

  /// Makes a \function from a \metafunction.
  /// \treturn \value
  /// \see lift_t
  template<template<class...> class F, class C = identity>
  struct lift
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_XS(xs, F, xs...));
  };

  /// \cond
  template<template<class...> class F>
  struct lift_t<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_XS(xs, F, xs...)::type;
  };

  template<template<class...> class F>
  struct lift<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_XS(xs, F, xs...);
  };
  /// \endcond


  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C = identity>
  struct lift_v_t
  {
    template<JLN_MP_TPL_AUTO_OR_INT... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_C_XS(xs, F, xs...)::type);
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C = identity>
  struct lift_v
  {
    template<JLN_MP_TPL_AUTO_OR_INT... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_C_XS(xs, F, xs...));
  };

  /// \cond
  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct lift_v_t<F, identity>
  {
    template<JLN_MP_TPL_AUTO_OR_INT... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs...)::type;
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct lift_v<F, identity>
  {
    template<JLN_MP_TPL_AUTO_OR_INT... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs...);
  };
  /// \endcond


  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C = identity>
  struct lift_a2v_t
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_C_XS(xs, F, xs::value...)::type);
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C = identity>
  struct lift_a2v
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_C_XS(xs, F, xs::value...));
  };

  /// \cond
  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct lift_a2v_t<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs::value...)::type;
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct lift_a2v<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs::value...);
  };

#if JLN_MP_GCC
#  define JLN_MP_LIFT_WRAP_IMPL(fn, fn_t) ::jln::mp::lift_t<fn>
#else
#  define JLN_MP_LIFT_WRAP_IMPL(fn, fn_t) ::jln::mp::lift<fn_t>
#endif

#define JLN_MP_LIFT_WRAP(fn) JLN_MP_LIFT_WRAP_IMPL(fn, fn##_t)
/// \endcond
  /// \ingroup list

  /// \treturn \link list
  using listify = lift<list>;

  /// \cond
  template<>
  struct lift<list, identity>
  {
    template<class... xs>
    using f = list<xs...>;
  };
  /// \endcond
  /// \cond
  namespace detail
  {
    template<class C, class L, class... xs> struct _unpack {};
    template<class C, class L, class... xs> struct _unpack_append {};
  }
  /// \endcond

  /// \ingroup utility

  /// Turns a \typelist into a \sequence of those types.
  /// \semantics
  ///   \code
  ///   unpack<F>::f<typelist<xs...>, ys...> == F::f<ys..., xs...>
  ///   \endcode
  /// \treturn \sequence
  template<class C>
  struct unpack
  {
    template<class seq, class... xs>
    using f = typename detail::_unpack<C, seq, xs...>::type;
  };

  /// Turns a \typelist into a \sequence of those types.
  /// \semantics
  ///   \code
  ///   unpack_append<F>::f<typelist<xs...>, ys...> == F::f<xs..., ys...>
  ///   \endcode
  /// \treturn \sequence
  template<class C>
  struct unpack_append
  {
    template<class seq, class... xs>
    using f = typename detail::_unpack_append<C, seq, xs...>::type;
  };

  namespace emp
  {
    template<class L, class C, class... xs>
    using unpack = typename detail::_unpack<C, L, xs...>::type;

    template<class L, class C, class... xs>
    using unpack_append = typename detail::_unpack_append<C, L, xs...>::type;
  }
} // namespace jln::mp



/// \cond
namespace jln::mp::detail
{
  template<class C, template<class...> class Seq, class... ys, class... xs>
  struct _unpack<C, Seq<ys...>, xs...>
  {
    using type = typename C::template f<xs..., ys...>;
  };

  template<class C, template<class...> class Seq, class... xs, class... ys>
  struct _unpack_append<C, Seq<xs...>, ys...>
  {
    using type = typename C::template f<xs..., ys...>;
  };

  template<template<class...> class F, template<class...> class Seq, class... ys, class... xs>
  struct _unpack<lift<F>, Seq<ys...>, xs...>
  {
    using type = F<xs..., ys...>;
  };

  template<template<class...> class F, template<class...> class Seq, class... xs, class... ys>
  struct _unpack_append<lift<F>, Seq<xs...>, ys...>
  {
    using type = F<xs..., ys...>;
  };

  template<template<class...> class F, template<class...> class Seq, class... ys, class... xs>
  struct _unpack<lift_t<F>, Seq<ys...>, xs...>
  {
    using type = typename F<xs..., ys...>::type;
  };

  template<template<class...> class F, template<class...> class Seq, class... xs, class... ys>
  struct _unpack_append<lift_t<F>, Seq<xs...>, ys...>
  {
    using type = typename F<xs..., ys...>::type;
  };

  template<class C>
  struct optimize_useless_unpack
  {
    using type = C;
  };

  template<>
  struct optimize_useless_unpack<unpack<listify>>
  {
    using type = identity;
  };

  template<>
  struct optimize_useless_unpack<unpack_append<listify>>
  {
    using type = identity;
  };

  template<class C>
  using optimize_useless_unpack_t = typename optimize_useless_unpack<C>::type;
}
/// \endcond

namespace jln::mp
{
  /// \ingroup list

  /// Appends \c x to the beginning of the sequence.
  /// \treturn \sequence
  template<class x, class C = listify>
  struct push_front
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, x, xs...);
  };

  namespace emp
  {
    template<class L, class T, class C = mp::listify>
    using push_front = unpack<L, mp::push_front<T, C>>;
  }

  /// \cond
  template<class x>
  struct push_front<x, listify>
  {
    template<class... xs>
    using f = list<x, xs...>;
  };
  /// \endcond
}

#define JLN_MP_NIL
#define JLN_MP_COMMA ,

#define JLN_MP_GEN_XS_16_64_256(func)                        \
  func(16,  JLN_MP_XS_16,  JLN_MP_RXS_16,  JLN_MP_REPEAT_16) \
  func(64,  JLN_MP_XS_64,  JLN_MP_RXS_64,  JLN_MP_REPEAT_64) \
  func(256, JLN_MP_XS_256, JLN_MP_RXS_256, JLN_MP_REPEAT_256)

#define JLN_MP_GEN_XS_8_16_64_256(func)                      \
  func(8,   JLN_MP_XS_8,   JLN_MP_RXS_8,   JLN_MP_REPEAT_8)  \
  func(16,  JLN_MP_XS_16,  JLN_MP_RXS_16,  JLN_MP_REPEAT_16) \
  func(64,  JLN_MP_XS_64,  JLN_MP_RXS_64,  JLN_MP_REPEAT_64) \
  func(256, JLN_MP_XS_256, JLN_MP_RXS_256, JLN_MP_REPEAT_256)

#define JLN_MP_GEN_XS_4_8_16_64_256(func)                    \
  func(4,   JLN_MP_XS_4,   JLN_MP_RXS_4,   JLN_MP_REPEAT_4)  \
  func(8,   JLN_MP_XS_8,   JLN_MP_RXS_8,   JLN_MP_REPEAT_8)  \
  func(16,  JLN_MP_XS_16,  JLN_MP_RXS_16,  JLN_MP_REPEAT_16) \
  func(64,  JLN_MP_XS_64,  JLN_MP_RXS_64,  JLN_MP_REPEAT_64) \
  func(256, JLN_MP_XS_256, JLN_MP_RXS_256, JLN_MP_REPEAT_256)

#define JLN_MP_GEN_XS_2_4_8_16_32_64_128_256(func)            \
  func(2,   JLN_MP_XS_2,   JLN_MP_RXS_2,   JLN_MP_REPEAT_2)   \
  func(4,   JLN_MP_XS_4,   JLN_MP_RXS_4,   JLN_MP_REPEAT_4)   \
  func(8,   JLN_MP_XS_8,   JLN_MP_RXS_8,   JLN_MP_REPEAT_8)   \
  func(16,  JLN_MP_XS_16,  JLN_MP_RXS_16,  JLN_MP_REPEAT_16)  \
  func(32,  JLN_MP_XS_32,  JLN_MP_RXS_32,  JLN_MP_REPEAT_32)  \
  func(64,  JLN_MP_XS_64,  JLN_MP_RXS_64,  JLN_MP_REPEAT_64)  \
  func(128, JLN_MP_XS_128, JLN_MP_RXS_128, JLN_MP_REPEAT_128) \
  func(256, JLN_MP_XS_256, JLN_MP_RXS_256, JLN_MP_REPEAT_256)

#define JLN_MP_GEN_XS_1_TO_16(func)                       \
  func(1, JLN_MP_XS_1, JLN_MP_RXS_1, JLN_MP_REPEAT_1)     \
  func(2, JLN_MP_XS_2, JLN_MP_RXS_2, JLN_MP_REPEAT_2)     \
  func(3, JLN_MP_XS_3, JLN_MP_RXS_3, JLN_MP_REPEAT_3)     \
  func(4, JLN_MP_XS_4, JLN_MP_RXS_4, JLN_MP_REPEAT_4)     \
  func(5, JLN_MP_XS_5, JLN_MP_RXS_5, JLN_MP_REPEAT_5)     \
  func(6, JLN_MP_XS_6, JLN_MP_RXS_6, JLN_MP_REPEAT_6)     \
  func(7, JLN_MP_XS_7, JLN_MP_RXS_7, JLN_MP_REPEAT_7)     \
  func(8, JLN_MP_XS_8, JLN_MP_RXS_8, JLN_MP_REPEAT_8)     \
  func(9, JLN_MP_XS_9, JLN_MP_RXS_9, JLN_MP_REPEAT_9)     \
  func(10, JLN_MP_XS_10, JLN_MP_RXS_10, JLN_MP_REPEAT_10) \
  func(11, JLN_MP_XS_11, JLN_MP_RXS_11, JLN_MP_REPEAT_11) \
  func(12, JLN_MP_XS_12, JLN_MP_RXS_12, JLN_MP_REPEAT_12) \
  func(13, JLN_MP_XS_13, JLN_MP_RXS_13, JLN_MP_REPEAT_13) \
  func(14, JLN_MP_XS_14, JLN_MP_RXS_14, JLN_MP_REPEAT_14) \
  func(15, JLN_MP_XS_15, JLN_MP_RXS_15, JLN_MP_REPEAT_15)

#define JLN_MP_GEN_XS_1_TO_16_INCLUDED(func)              \
  func(1, JLN_MP_XS_1, JLN_MP_RXS_1, JLN_MP_REPEAT_1)     \
  func(2, JLN_MP_XS_2, JLN_MP_RXS_2, JLN_MP_REPEAT_2)     \
  func(3, JLN_MP_XS_3, JLN_MP_RXS_3, JLN_MP_REPEAT_3)     \
  func(4, JLN_MP_XS_4, JLN_MP_RXS_4, JLN_MP_REPEAT_4)     \
  func(5, JLN_MP_XS_5, JLN_MP_RXS_5, JLN_MP_REPEAT_5)     \
  func(6, JLN_MP_XS_6, JLN_MP_RXS_6, JLN_MP_REPEAT_6)     \
  func(7, JLN_MP_XS_7, JLN_MP_RXS_7, JLN_MP_REPEAT_7)     \
  func(8, JLN_MP_XS_8, JLN_MP_RXS_8, JLN_MP_REPEAT_8)     \
  func(9, JLN_MP_XS_9, JLN_MP_RXS_9, JLN_MP_REPEAT_9)     \
  func(10, JLN_MP_XS_10, JLN_MP_RXS_10, JLN_MP_REPEAT_10) \
  func(11, JLN_MP_XS_11, JLN_MP_RXS_11, JLN_MP_REPEAT_11) \
  func(12, JLN_MP_XS_12, JLN_MP_RXS_12, JLN_MP_REPEAT_12) \
  func(13, JLN_MP_XS_13, JLN_MP_RXS_13, JLN_MP_REPEAT_13) \
  func(14, JLN_MP_XS_14, JLN_MP_RXS_14, JLN_MP_REPEAT_14) \
  func(15, JLN_MP_XS_15, JLN_MP_RXS_15, JLN_MP_REPEAT_15) \
  func(16, JLN_MP_XS_16, JLN_MP_RXS_16, JLN_MP_REPEAT_16)

#define JLN_MP_GEN_XS_0_TO_8(func)                    \
  func(0, JLN_MP_XS_0, JLN_MP_RXS_0, JLN_MP_REPEAT_0) \
  func(1, JLN_MP_XS_1, JLN_MP_RXS_1, JLN_MP_REPEAT_1) \
  func(2, JLN_MP_XS_2, JLN_MP_RXS_2, JLN_MP_REPEAT_2) \
  func(3, JLN_MP_XS_3, JLN_MP_RXS_3, JLN_MP_REPEAT_3) \
  func(4, JLN_MP_XS_4, JLN_MP_RXS_4, JLN_MP_REPEAT_4) \
  func(5, JLN_MP_XS_5, JLN_MP_RXS_5, JLN_MP_REPEAT_5) \
  func(6, JLN_MP_XS_6, JLN_MP_RXS_6, JLN_MP_REPEAT_6) \
  func(7, JLN_MP_XS_7, JLN_MP_RXS_7, JLN_MP_REPEAT_7)

#define JLN_MP_GEN_XS_1_TO_8_INCLUDED(func) \
  JLN_MP_GEN_XS_1_TO_8(func)                \
  func(8, JLN_MP_XS_8, JLN_MP_RXS_8, JLN_MP_REPEAT_8)

#define JLN_MP_GEN_XS_1_TO_8(func)                    \
  func(1, JLN_MP_XS_1, JLN_MP_RXS_1, JLN_MP_REPEAT_1) \
  func(2, JLN_MP_XS_2, JLN_MP_RXS_2, JLN_MP_REPEAT_2) \
  func(3, JLN_MP_XS_3, JLN_MP_RXS_3, JLN_MP_REPEAT_3) \
  func(4, JLN_MP_XS_4, JLN_MP_RXS_4, JLN_MP_REPEAT_4) \
  func(5, JLN_MP_XS_5, JLN_MP_RXS_5, JLN_MP_REPEAT_5) \
  func(6, JLN_MP_XS_6, JLN_MP_RXS_6, JLN_MP_REPEAT_6) \
  func(7, JLN_MP_XS_7, JLN_MP_RXS_7, JLN_MP_REPEAT_7)

#define JLN_MP_GEN_XS_1_TO_4(func)                    \
  func(1, JLN_MP_XS_1, JLN_MP_RXS_1, JLN_MP_REPEAT_1) \
  func(2, JLN_MP_XS_2, JLN_MP_RXS_2, JLN_MP_REPEAT_2) \
  func(3, JLN_MP_XS_3, JLN_MP_RXS_3, JLN_MP_REPEAT_3)


#define JLN_MP_REPEAT_0(x, sep)
#define JLN_MP_REPEAT_1(x, B) x
#define JLN_MP_REPEAT_2(x, B) x B x
#define JLN_MP_REPEAT_3(x, B) x B x B x
#define JLN_MP_REPEAT_4(x, B) x B x B x B x
#define JLN_MP_REPEAT_5(x, B) x B x B x B x B x
#define JLN_MP_REPEAT_6(x, B) x B x B x B x B x B x
#define JLN_MP_REPEAT_7(x, B) x B x B x B x B x B x B x
#define JLN_MP_REPEAT_8(x, B) x B x B x B x B x B x B x B x
#define JLN_MP_REPEAT_9(x, B) x B x B x B x B x B x B x B x B x
#define JLN_MP_REPEAT_10(x, B) x B x B x B x B x B x B x B x B x B x
#define JLN_MP_REPEAT_11(x, B) x B x B x B x B x B x B x B x B x B x B x
#define JLN_MP_REPEAT_12(x, B) \
  x B x B x B x B x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_13(x, B) \
  x B x B x B x B x B x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_14(x, B) \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_15(x, B) \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_16(x, B) \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_32(x, B)                                    \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_64(x, B)                                    \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_128(x, B)                                   \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_256(x, B)                                   \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x


#define JLN_MP_XS_0(before, after, sep)

#define JLN_MP_XS_1(before, after, sep) \
  before _1 after

#define JLN_MP_XS_2(before, after, sep) \
  before _1 after sep before _2 after

#define JLN_MP_XS_3(before, after, sep) \
  before _1 after sep before _2 after sep before _3 after

#define JLN_MP_XS_4(before, after, sep) \
  before _1 after sep before _2 after sep before _3 after sep before _4 after

#define JLN_MP_XS_5(before, after, sep)                                           \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep \
  before _5 after

#define JLN_MP_XS_6(before, after, sep)                                           \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep \
  before _5 after sep before _6 after

#define JLN_MP_XS_7(before, after, sep)                                           \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep \
  before _5 after sep before _6 after sep before _7 after

#define JLN_MP_XS_8(before, after, sep)                                           \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep \
  before _5 after sep before _6 after sep before _7 after sep before _8 after

#define JLN_MP_XS_9(before, after, sep)                                           \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep \
  before _5 after sep before _6 after sep before _7 after sep before _8 after sep \
  before _9 after

#define JLN_MP_XS_10(before, after, sep)                                          \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep \
  before _5 after sep before _6 after sep before _7 after sep before _8 after sep \
  before _9 after sep before _10 after

#define JLN_MP_XS_11(before, after, sep)                                          \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep \
  before _5 after sep before _6 after sep before _7 after sep before _8 after sep \
  before _9 after sep before _10 after sep before _11 after

#define JLN_MP_XS_12(before, after, sep)                                          \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep \
  before _5 after sep before _6 after sep before _7 after sep before _8 after sep \
  before _9 after sep before _10 after sep before _11 after sep before _12 after

#define JLN_MP_XS_13(before, after, sep)                                             \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep    \
  before _5 after sep before _6 after sep before _7 after sep before _8 after sep    \
  before _9 after sep before _10 after sep before _11 after sep before _12 after sep \
  before _13 after

#define JLN_MP_XS_14(before, after, sep)                                             \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep    \
  before _5 after sep before _6 after sep before _7 after sep before _8 after sep    \
  before _9 after sep before _10 after sep before _11 after sep before _12 after sep \
  before _13 after sep before _14 after

#define JLN_MP_XS_15(before, after, sep)                                             \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep    \
  before _5 after sep before _6 after sep before _7 after sep before _8 after sep    \
  before _9 after sep before _10 after sep before _11 after sep before _12 after sep \
  before _13 after sep before _14 after sep before _15 after

#define JLN_MP_XS_16(before, after, sep)                                             \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep    \
  before _5 after sep before _6 after sep before _7 after sep before _8 after sep    \
  before _9 after sep before _10 after sep before _11 after sep before _12 after sep \
  before _13 after sep before _14 after sep before _15 after sep before _16 after

#define JLN_MP_XS_32(before, after, sep)                                              \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep     \
  before _5 after sep before _6 after sep before _7 after sep before _8 after sep     \
  before _9 after sep before _10 after sep before _11 after sep before _12 after sep  \
  before _13 after sep before _14 after sep before _15 after sep before _16 after sep \
  before _17 after sep before _18 after sep before _19 after sep before _20 after sep \
  before _21 after sep before _22 after sep before _23 after sep before _24 after sep \
  before _25 after sep before _26 after sep before _27 after sep before _28 after sep \
  before _29 after sep before _30 after sep before _31 after sep before _32 after

#define JLN_MP_XS_64(before, after, sep)                                              \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep     \
  before _5 after sep before _6 after sep before _7 after sep before _8 after sep     \
  before _9 after sep before _10 after sep before _11 after sep before _12 after sep  \
  before _13 after sep before _14 after sep before _15 after sep before _16 after sep \
  before _17 after sep before _18 after sep before _19 after sep before _20 after sep \
  before _21 after sep before _22 after sep before _23 after sep before _24 after sep \
  before _25 after sep before _26 after sep before _27 after sep before _28 after sep \
  before _29 after sep before _30 after sep before _31 after sep before _32 after sep \
  before _33 after sep before _34 after sep before _35 after sep before _36 after sep \
  before _37 after sep before _38 after sep before _39 after sep before _40 after sep \
  before _41 after sep before _42 after sep before _43 after sep before _44 after sep \
  before _45 after sep before _46 after sep before _47 after sep before _48 after sep \
  before _49 after sep before _50 after sep before _51 after sep before _52 after sep \
  before _53 after sep before _54 after sep before _55 after sep before _56 after sep \
  before _57 after sep before _58 after sep before _59 after sep before _60 after sep \
  before _61 after sep before _62 after sep before _63 after sep before _64 after

#define JLN_MP_XS_128(before, after, sep)                                                 \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep         \
  before _5 after sep before _6 after sep before _7 after sep before _8 after sep         \
  before _9 after sep before _10 after sep before _11 after sep before _12 after sep      \
  before _13 after sep before _14 after sep before _15 after sep before _16 after sep     \
  before _17 after sep before _18 after sep before _19 after sep before _20 after sep     \
  before _21 after sep before _22 after sep before _23 after sep before _24 after sep     \
  before _25 after sep before _26 after sep before _27 after sep before _28 after sep     \
  before _29 after sep before _30 after sep before _31 after sep before _32 after sep     \
  before _33 after sep before _34 after sep before _35 after sep before _36 after sep     \
  before _37 after sep before _38 after sep before _39 after sep before _40 after sep     \
  before _41 after sep before _42 after sep before _43 after sep before _44 after sep     \
  before _45 after sep before _46 after sep before _47 after sep before _48 after sep     \
  before _49 after sep before _50 after sep before _51 after sep before _52 after sep     \
  before _53 after sep before _54 after sep before _55 after sep before _56 after sep     \
  before _57 after sep before _58 after sep before _59 after sep before _60 after sep     \
  before _61 after sep before _62 after sep before _63 after sep before _64 after sep     \
  before _65 after sep before _66 after sep before _67 after sep before _68 after sep     \
  before _69 after sep before _70 after sep before _71 after sep before _72 after sep     \
  before _73 after sep before _74 after sep before _75 after sep before _76 after sep     \
  before _77 after sep before _78 after sep before _79 after sep before _80 after sep     \
  before _81 after sep before _82 after sep before _83 after sep before _84 after sep     \
  before _85 after sep before _86 after sep before _87 after sep before _88 after sep     \
  before _89 after sep before _90 after sep before _91 after sep before _92 after sep     \
  before _93 after sep before _94 after sep before _95 after sep before _96 after sep     \
  before _97 after sep before _98 after sep before _99 after sep before _100 after sep    \
  before _101 after sep before _102 after sep before _103 after sep before _104 after sep \
  before _105 after sep before _106 after sep before _107 after sep before _108 after sep \
  before _109 after sep before _110 after sep before _111 after sep before _112 after sep \
  before _113 after sep before _114 after sep before _115 after sep before _116 after sep \
  before _117 after sep before _118 after sep before _119 after sep before _120 after sep \
  before _121 after sep before _122 after sep before _123 after sep before _124 after sep \
  before _125 after sep before _126 after sep before _127 after sep before _128 after

#define JLN_MP_XS_256(before, after, sep)                                                 \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep         \
  before _5 after sep before _6 after sep before _7 after sep before _8 after sep         \
  before _9 after sep before _10 after sep before _11 after sep before _12 after sep      \
  before _13 after sep before _14 after sep before _15 after sep before _16 after sep     \
  before _17 after sep before _18 after sep before _19 after sep before _20 after sep     \
  before _21 after sep before _22 after sep before _23 after sep before _24 after sep     \
  before _25 after sep before _26 after sep before _27 after sep before _28 after sep     \
  before _29 after sep before _30 after sep before _31 after sep before _32 after sep     \
  before _33 after sep before _34 after sep before _35 after sep before _36 after sep     \
  before _37 after sep before _38 after sep before _39 after sep before _40 after sep     \
  before _41 after sep before _42 after sep before _43 after sep before _44 after sep     \
  before _45 after sep before _46 after sep before _47 after sep before _48 after sep     \
  before _49 after sep before _50 after sep before _51 after sep before _52 after sep     \
  before _53 after sep before _54 after sep before _55 after sep before _56 after sep     \
  before _57 after sep before _58 after sep before _59 after sep before _60 after sep     \
  before _61 after sep before _62 after sep before _63 after sep before _64 after sep     \
  before _65 after sep before _66 after sep before _67 after sep before _68 after sep     \
  before _69 after sep before _70 after sep before _71 after sep before _72 after sep     \
  before _73 after sep before _74 after sep before _75 after sep before _76 after sep     \
  before _77 after sep before _78 after sep before _79 after sep before _80 after sep     \
  before _81 after sep before _82 after sep before _83 after sep before _84 after sep     \
  before _85 after sep before _86 after sep before _87 after sep before _88 after sep     \
  before _89 after sep before _90 after sep before _91 after sep before _92 after sep     \
  before _93 after sep before _94 after sep before _95 after sep before _96 after sep     \
  before _97 after sep before _98 after sep before _99 after sep before _100 after sep    \
  before _101 after sep before _102 after sep before _103 after sep before _104 after sep \
  before _105 after sep before _106 after sep before _107 after sep before _108 after sep \
  before _109 after sep before _110 after sep before _111 after sep before _112 after sep \
  before _113 after sep before _114 after sep before _115 after sep before _116 after sep \
  before _117 after sep before _118 after sep before _119 after sep before _120 after sep \
  before _121 after sep before _122 after sep before _123 after sep before _124 after sep \
  before _125 after sep before _126 after sep before _127 after sep before _128 after sep \
  before _129 after sep before _130 after sep before _131 after sep before _132 after sep \
  before _133 after sep before _134 after sep before _135 after sep before _136 after sep \
  before _137 after sep before _138 after sep before _139 after sep before _140 after sep \
  before _141 after sep before _142 after sep before _143 after sep before _144 after sep \
  before _145 after sep before _146 after sep before _147 after sep before _148 after sep \
  before _149 after sep before _150 after sep before _151 after sep before _152 after sep \
  before _153 after sep before _154 after sep before _155 after sep before _156 after sep \
  before _157 after sep before _158 after sep before _159 after sep before _160 after sep \
  before _161 after sep before _162 after sep before _163 after sep before _164 after sep \
  before _165 after sep before _166 after sep before _167 after sep before _168 after sep \
  before _169 after sep before _170 after sep before _171 after sep before _172 after sep \
  before _173 after sep before _174 after sep before _175 after sep before _176 after sep \
  before _177 after sep before _178 after sep before _179 after sep before _180 after sep \
  before _181 after sep before _182 after sep before _183 after sep before _184 after sep \
  before _185 after sep before _186 after sep before _187 after sep before _188 after sep \
  before _189 after sep before _190 after sep before _191 after sep before _192 after sep \
  before _193 after sep before _194 after sep before _195 after sep before _196 after sep \
  before _197 after sep before _198 after sep before _199 after sep before _200 after sep \
  before _201 after sep before _202 after sep before _203 after sep before _204 after sep \
  before _205 after sep before _206 after sep before _207 after sep before _208 after sep \
  before _209 after sep before _210 after sep before _211 after sep before _212 after sep \
  before _213 after sep before _214 after sep before _215 after sep before _216 after sep \
  before _217 after sep before _218 after sep before _219 after sep before _220 after sep \
  before _221 after sep before _222 after sep before _223 after sep before _224 after sep \
  before _225 after sep before _226 after sep before _227 after sep before _228 after sep \
  before _229 after sep before _230 after sep before _231 after sep before _232 after sep \
  before _233 after sep before _234 after sep before _235 after sep before _236 after sep \
  before _237 after sep before _238 after sep before _239 after sep before _240 after sep \
  before _241 after sep before _242 after sep before _243 after sep before _244 after sep \
  before _245 after sep before _246 after sep before _247 after sep before _248 after sep \
  before _249 after sep before _250 after sep before _251 after sep before _252 after sep \
  before _253 after sep before _254 after sep before _255 after sep before _256 after

#define JLN_MP_XS_512(before, after, sep)                                                 \
  before _1 after sep before _2 after sep before _3 after sep before _4 after sep         \
  before _5 after sep before _6 after sep before _7 after sep before _8 after sep         \
  before _9 after sep before _10 after sep before _11 after sep before _12 after sep      \
  before _13 after sep before _14 after sep before _15 after sep before _16 after sep     \
  before _17 after sep before _18 after sep before _19 after sep before _20 after sep     \
  before _21 after sep before _22 after sep before _23 after sep before _24 after sep     \
  before _25 after sep before _26 after sep before _27 after sep before _28 after sep     \
  before _29 after sep before _30 after sep before _31 after sep before _32 after sep     \
  before _33 after sep before _34 after sep before _35 after sep before _36 after sep     \
  before _37 after sep before _38 after sep before _39 after sep before _40 after sep     \
  before _41 after sep before _42 after sep before _43 after sep before _44 after sep     \
  before _45 after sep before _46 after sep before _47 after sep before _48 after sep     \
  before _49 after sep before _50 after sep before _51 after sep before _52 after sep     \
  before _53 after sep before _54 after sep before _55 after sep before _56 after sep     \
  before _57 after sep before _58 after sep before _59 after sep before _60 after sep     \
  before _61 after sep before _62 after sep before _63 after sep before _64 after sep     \
  before _65 after sep before _66 after sep before _67 after sep before _68 after sep     \
  before _69 after sep before _70 after sep before _71 after sep before _72 after sep     \
  before _73 after sep before _74 after sep before _75 after sep before _76 after sep     \
  before _77 after sep before _78 after sep before _79 after sep before _80 after sep     \
  before _81 after sep before _82 after sep before _83 after sep before _84 after sep     \
  before _85 after sep before _86 after sep before _87 after sep before _88 after sep     \
  before _89 after sep before _90 after sep before _91 after sep before _92 after sep     \
  before _93 after sep before _94 after sep before _95 after sep before _96 after sep     \
  before _97 after sep before _98 after sep before _99 after sep before _100 after sep    \
  before _101 after sep before _102 after sep before _103 after sep before _104 after sep \
  before _105 after sep before _106 after sep before _107 after sep before _108 after sep \
  before _109 after sep before _110 after sep before _111 after sep before _112 after sep \
  before _113 after sep before _114 after sep before _115 after sep before _116 after sep \
  before _117 after sep before _118 after sep before _119 after sep before _120 after sep \
  before _121 after sep before _122 after sep before _123 after sep before _124 after sep \
  before _125 after sep before _126 after sep before _127 after sep before _128 after sep \
  before _129 after sep before _130 after sep before _131 after sep before _132 after sep \
  before _133 after sep before _134 after sep before _135 after sep before _136 after sep \
  before _137 after sep before _138 after sep before _139 after sep before _140 after sep \
  before _141 after sep before _142 after sep before _143 after sep before _144 after sep \
  before _145 after sep before _146 after sep before _147 after sep before _148 after sep \
  before _149 after sep before _150 after sep before _151 after sep before _152 after sep \
  before _153 after sep before _154 after sep before _155 after sep before _156 after sep \
  before _157 after sep before _158 after sep before _159 after sep before _160 after sep \
  before _161 after sep before _162 after sep before _163 after sep before _164 after sep \
  before _165 after sep before _166 after sep before _167 after sep before _168 after sep \
  before _169 after sep before _170 after sep before _171 after sep before _172 after sep \
  before _173 after sep before _174 after sep before _175 after sep before _176 after sep \
  before _177 after sep before _178 after sep before _179 after sep before _180 after sep \
  before _181 after sep before _182 after sep before _183 after sep before _184 after sep \
  before _185 after sep before _186 after sep before _187 after sep before _188 after sep \
  before _189 after sep before _190 after sep before _191 after sep before _192 after sep \
  before _193 after sep before _194 after sep before _195 after sep before _196 after sep \
  before _197 after sep before _198 after sep before _199 after sep before _200 after sep \
  before _201 after sep before _202 after sep before _203 after sep before _204 after sep \
  before _205 after sep before _206 after sep before _207 after sep before _208 after sep \
  before _209 after sep before _210 after sep before _211 after sep before _212 after sep \
  before _213 after sep before _214 after sep before _215 after sep before _216 after sep \
  before _217 after sep before _218 after sep before _219 after sep before _220 after sep \
  before _221 after sep before _222 after sep before _223 after sep before _224 after sep \
  before _225 after sep before _226 after sep before _227 after sep before _228 after sep \
  before _229 after sep before _230 after sep before _231 after sep before _232 after sep \
  before _233 after sep before _234 after sep before _235 after sep before _236 after sep \
  before _237 after sep before _238 after sep before _239 after sep before _240 after sep \
  before _241 after sep before _242 after sep before _243 after sep before _244 after sep \
  before _245 after sep before _246 after sep before _247 after sep before _248 after sep \
  before _249 after sep before _250 after sep before _251 after sep before _252 after sep \
  before _253 after sep before _254 after sep before _255 after sep before _256 after sep \
  before _257 after sep before _258 after sep before _259 after sep before _260 after sep \
  before _261 after sep before _262 after sep before _263 after sep before _264 after sep \
  before _265 after sep before _266 after sep before _267 after sep before _268 after sep \
  before _269 after sep before _270 after sep before _271 after sep before _272 after sep \
  before _273 after sep before _274 after sep before _275 after sep before _276 after sep \
  before _277 after sep before _278 after sep before _279 after sep before _280 after sep \
  before _281 after sep before _282 after sep before _283 after sep before _284 after sep \
  before _285 after sep before _286 after sep before _287 after sep before _288 after sep \
  before _289 after sep before _290 after sep before _291 after sep before _292 after sep \
  before _293 after sep before _294 after sep before _295 after sep before _296 after sep \
  before _297 after sep before _298 after sep before _299 after sep before _300 after sep \
  before _301 after sep before _302 after sep before _303 after sep before _304 after sep \
  before _305 after sep before _306 after sep before _307 after sep before _308 after sep \
  before _309 after sep before _310 after sep before _311 after sep before _312 after sep \
  before _313 after sep before _314 after sep before _315 after sep before _316 after sep \
  before _317 after sep before _318 after sep before _319 after sep before _320 after sep \
  before _321 after sep before _322 after sep before _323 after sep before _324 after sep \
  before _325 after sep before _326 after sep before _327 after sep before _328 after sep \
  before _329 after sep before _330 after sep before _331 after sep before _332 after sep \
  before _333 after sep before _334 after sep before _335 after sep before _336 after sep \
  before _337 after sep before _338 after sep before _339 after sep before _340 after sep \
  before _341 after sep before _342 after sep before _343 after sep before _344 after sep \
  before _345 after sep before _346 after sep before _347 after sep before _348 after sep \
  before _349 after sep before _350 after sep before _351 after sep before _352 after sep \
  before _353 after sep before _354 after sep before _355 after sep before _356 after sep \
  before _357 after sep before _358 after sep before _359 after sep before _360 after sep \
  before _361 after sep before _362 after sep before _363 after sep before _364 after sep \
  before _365 after sep before _366 after sep before _367 after sep before _368 after sep \
  before _369 after sep before _370 after sep before _371 after sep before _372 after sep \
  before _373 after sep before _374 after sep before _375 after sep before _376 after sep \
  before _377 after sep before _378 after sep before _379 after sep before _380 after sep \
  before _381 after sep before _382 after sep before _383 after sep before _384 after sep \
  before _385 after sep before _386 after sep before _387 after sep before _388 after sep \
  before _389 after sep before _390 after sep before _391 after sep before _392 after sep \
  before _393 after sep before _394 after sep before _395 after sep before _396 after sep \
  before _397 after sep before _398 after sep before _399 after sep before _400 after sep \
  before _401 after sep before _402 after sep before _403 after sep before _404 after sep \
  before _405 after sep before _406 after sep before _407 after sep before _408 after sep \
  before _409 after sep before _410 after sep before _411 after sep before _412 after sep \
  before _413 after sep before _414 after sep before _415 after sep before _416 after sep \
  before _417 after sep before _418 after sep before _419 after sep before _420 after sep \
  before _421 after sep before _422 after sep before _423 after sep before _424 after sep \
  before _425 after sep before _426 after sep before _427 after sep before _428 after sep \
  before _429 after sep before _430 after sep before _431 after sep before _432 after sep \
  before _433 after sep before _434 after sep before _435 after sep before _436 after sep \
  before _437 after sep before _438 after sep before _439 after sep before _440 after sep \
  before _441 after sep before _442 after sep before _443 after sep before _444 after sep \
  before _445 after sep before _446 after sep before _447 after sep before _448 after sep \
  before _449 after sep before _450 after sep before _451 after sep before _452 after sep \
  before _453 after sep before _454 after sep before _455 after sep before _456 after sep \
  before _457 after sep before _458 after sep before _459 after sep before _460 after sep \
  before _461 after sep before _462 after sep before _463 after sep before _464 after sep \
  before _465 after sep before _466 after sep before _467 after sep before _468 after sep \
  before _469 after sep before _470 after sep before _471 after sep before _472 after sep \
  before _473 after sep before _474 after sep before _475 after sep before _476 after sep \
  before _477 after sep before _478 after sep before _479 after sep before _480 after sep \
  before _481 after sep before _482 after sep before _483 after sep before _484 after sep \
  before _485 after sep before _486 after sep before _487 after sep before _488 after sep \
  before _489 after sep before _490 after sep before _491 after sep before _492 after sep \
  before _493 after sep before _494 after sep before _495 after sep before _496 after sep \
  before _497 after sep before _498 after sep before _499 after sep before _500 after sep \
  before _501 after sep before _502 after sep before _503 after sep before _504 after sep \
  before _505 after sep before _506 after sep before _507 after sep before _508 after sep \
  before _509 after sep before _510 after sep before _511 after sep before _512 after

#define JLN_MP_RXS_0(before, after, sep)

#define JLN_MP_RXS_1(before, after, sep) \
  before _1 after

#define JLN_MP_RXS_2(before, after, sep) \
  before _2 after sep before _1 after

#define JLN_MP_RXS_3(before, after, sep) \
  before _3 after sep before _2 after sep before _1 after

#define JLN_MP_RXS_4(before, after, sep) \
  before _4 after sep before _3 after sep before _2 after sep before _1 after

#define JLN_MP_RXS_5(before, after, sep) \
  before _5 after sep before _4 after sep before _3 after sep before _2 after sep \
  before _1 after

#define JLN_MP_RXS_6(before, after, sep)                                          \
  before _6 after sep before _5 after sep before _4 after sep before _3 after sep \
  before _2 after sep before _1 after

#define JLN_MP_RXS_7(before, after, sep)                                          \
  before _7 after sep before _6 after sep before _5 after sep before _4 after sep \
  before _3 after sep before _2 after sep before _1 after

#define JLN_MP_RXS_8(before, after, sep)                                          \
  before _8 after sep before _7 after sep before _6 after sep before _5 after sep \
  before _4 after sep before _3 after sep before _2 after sep before _1 after

#define JLN_MP_RXS_9(before, after, sep)                                          \
  before _9 after sep before _8 after sep before _7 after sep before _6 after sep \
  before _5 after sep before _4 after sep before _3 after sep before _2 after sep \
  before _1 after

#define JLN_MP_RXS_10(before, after, sep)                                          \
  before _10 after sep before _9 after sep before _8 after sep before _7 after sep \
  before _6 after sep before _5 after sep before _4 after sep before _3 after sep  \
  before _2 after sep before _1 after

#define JLN_MP_RXS_11(before, after, sep)                                           \
  before _11 after sep before _10 after sep before _9 after sep before _8 after sep \
  before _7 after sep before _6 after sep before _5 after sep before _4 after sep   \
  before _3 after sep before _2 after sep before _1 after

#define JLN_MP_RXS_12(before, after, sep)                                             \
  before _12 after sep before _11 after sep before _10 after sep before _9 after sep  \
  before _8 after sep before _7 after sep before _6 after sep before _5 after sep     \
  before _4 after sep before _3 after sep before _2 after sep before _1 after

#define JLN_MP_RXS_13(before, after, sep)                                             \
  before _13 after sep before _12 after sep before _11 after sep before _10 after sep \
   before _9 after sep before _8 after sep before _7 after sep before _6 after sep    \
  before _5 after sep before _4 after sep before _3 after sep before _2 after sep     \
  before _1 after

#define JLN_MP_RXS_14(before, after, sep)                                             \
  before _14 after sep before _13 after sep before _12 after sep before _11 after sep \
  before _10 after sep before _9 after sep before _8 after sep before _7 after sep    \
  before _6 after sep before _5 after sep before _4 after sep before _3 after sep     \
  before _2 after sep before _1 after

#define JLN_MP_RXS_15(before, after, sep)                                             \
  before _15 after sep before _14 after sep before _13 after sep before _12 after sep \
  before _11 after sep before _10 after sep before _9 after sep before _8 after sep   \
  before _7 after sep before _6 after sep before _5 after sep before _4 after sep     \
  before _3 after sep before _2 after sep before _1 after

#define JLN_MP_RXS_16(before, after, sep)                                             \
  before _16 after sep before _15 after sep before _14 after sep before _13 after sep \
  before _12 after sep before _11 after sep before _10 after sep before _9 after sep  \
  before _8 after sep before _7 after sep before _6 after sep before _5 after sep     \
  before _4 after sep before _3 after sep before _2 after sep before _1 after

#define JLN_MP_RXS_32(before, after, sep)                                             \
  before _32 after sep before _31 after sep before _30 after sep before _29 after sep \
  before _28 after sep before _27 after sep before _26 after sep before _25 after sep \
  before _24 after sep before _23 after sep before _22 after sep before _21 after sep \
  before _20 after sep before _19 after sep before _18 after sep before _17 after sep \
  before _16 after sep before _15 after sep before _14 after sep before _13 after sep \
  before _12 after sep before _11 after sep before _10 after sep before _9 after sep  \
  before _8 after sep before _7 after sep before _6 after sep before _5 after sep     \
  before _4 after sep before _3 after sep before _2 after sep before _1 after

#define JLN_MP_RXS_64(before, after, sep)                                             \
  before _64 after sep before _63 after sep before _62 after sep before _61 after sep \
  before _60 after sep before _59 after sep before _58 after sep before _57 after sep \
  before _56 after sep before _55 after sep before _54 after sep before _53 after sep \
  before _52 after sep before _51 after sep before _50 after sep before _49 after sep \
  before _48 after sep before _47 after sep before _46 after sep before _45 after sep \
  before _44 after sep before _43 after sep before _42 after sep before _41 after sep \
  before _40 after sep before _39 after sep before _38 after sep before _37 after sep \
  before _36 after sep before _35 after sep before _34 after sep before _33 after sep \
  before _32 after sep before _31 after sep before _30 after sep before _29 after sep \
  before _28 after sep before _27 after sep before _26 after sep before _25 after sep \
  before _24 after sep before _23 after sep before _22 after sep before _21 after sep \
  before _20 after sep before _19 after sep before _18 after sep before _17 after sep \
  before _16 after sep before _15 after sep before _14 after sep before _13 after sep \
  before _12 after sep before _11 after sep before _10 after sep before _9 after sep  \
  before _8 after sep before _7 after sep before _6 after sep before _5 after sep     \
  before _4 after sep before _3 after sep before _2 after sep before _1 after

#define JLN_MP_RXS_128(before, after, sep)                                                \
  before _128 after sep before _127 after sep before _126 after sep before _125 after sep \
  before _124 after sep before _123 after sep before _122 after sep before _121 after sep \
  before _120 after sep before _119 after sep before _118 after sep before _117 after sep \
  before _116 after sep before _115 after sep before _114 after sep before _113 after sep \
  before _112 after sep before _111 after sep before _110 after sep before _109 after sep \
  before _108 after sep before _107 after sep before _106 after sep before _105 after sep \
  before _104 after sep before _103 after sep before _102 after sep before _101 after sep \
  before _100 after sep before _99 after sep before _98 after sep before _97 after sep    \
  before _96 after sep before _95 after sep before _94 after sep before _93 after sep     \
  before _92 after sep before _91 after sep before _90 after sep before _89 after sep     \
  before _88 after sep before _87 after sep before _86 after sep before _85 after sep     \
  before _84 after sep before _83 after sep before _82 after sep before _81 after sep     \
  before _80 after sep before _79 after sep before _78 after sep before _77 after sep     \
  before _76 after sep before _75 after sep before _74 after sep before _73 after sep     \
  before _72 after sep before _71 after sep before _70 after sep before _69 after sep     \
  before _68 after sep before _67 after sep before _66 after sep before _65 after sep     \
  before _64 after sep before _63 after sep before _62 after sep before _61 after sep     \
  before _60 after sep before _59 after sep before _58 after sep before _57 after sep     \
  before _56 after sep before _55 after sep before _54 after sep before _53 after sep     \
  before _52 after sep before _51 after sep before _50 after sep before _49 after sep     \
  before _48 after sep before _47 after sep before _46 after sep before _45 after sep     \
  before _44 after sep before _43 after sep before _42 after sep before _41 after sep     \
  before _40 after sep before _39 after sep before _38 after sep before _37 after sep     \
  before _36 after sep before _35 after sep before _34 after sep before _33 after sep     \
  before _32 after sep before _31 after sep before _30 after sep before _29 after sep     \
  before _28 after sep before _27 after sep before _26 after sep before _25 after sep     \
  before _24 after sep before _23 after sep before _22 after sep before _21 after sep     \
  before _20 after sep before _19 after sep before _18 after sep before _17 after sep     \
  before _16 after sep before _15 after sep before _14 after sep before _13 after sep     \
  before _12 after sep before _11 after sep before _10 after sep before _9 after sep      \
  before _8 after sep before _7 after sep before _6 after sep before _5 after sep         \
  before _4 after sep before _3 after sep before _2 after sep before _1 after

#define JLN_MP_RXS_256(before, after, sep)                                                \
  before _256 after sep before _255 after sep before _254 after sep before _253 after sep \
  before _252 after sep before _251 after sep before _250 after sep before _249 after sep \
  before _248 after sep before _247 after sep before _246 after sep before _245 after sep \
  before _244 after sep before _243 after sep before _242 after sep before _241 after sep \
  before _240 after sep before _239 after sep before _238 after sep before _237 after sep \
  before _236 after sep before _235 after sep before _234 after sep before _233 after sep \
  before _232 after sep before _231 after sep before _230 after sep before _229 after sep \
  before _228 after sep before _227 after sep before _226 after sep before _225 after sep \
  before _224 after sep before _223 after sep before _222 after sep before _221 after sep \
  before _220 after sep before _219 after sep before _218 after sep before _217 after sep \
  before _216 after sep before _215 after sep before _214 after sep before _213 after sep \
  before _212 after sep before _211 after sep before _210 after sep before _209 after sep \
  before _208 after sep before _207 after sep before _206 after sep before _205 after sep \
  before _204 after sep before _203 after sep before _202 after sep before _201 after sep \
  before _200 after sep before _199 after sep before _198 after sep before _197 after sep \
  before _196 after sep before _195 after sep before _194 after sep before _193 after sep \
  before _192 after sep before _191 after sep before _190 after sep before _189 after sep \
  before _188 after sep before _187 after sep before _186 after sep before _185 after sep \
  before _184 after sep before _183 after sep before _182 after sep before _181 after sep \
  before _180 after sep before _179 after sep before _178 after sep before _177 after sep \
  before _176 after sep before _175 after sep before _174 after sep before _173 after sep \
  before _172 after sep before _171 after sep before _170 after sep before _169 after sep \
  before _168 after sep before _167 after sep before _166 after sep before _165 after sep \
  before _164 after sep before _163 after sep before _162 after sep before _161 after sep \
  before _160 after sep before _159 after sep before _158 after sep before _157 after sep \
  before _156 after sep before _155 after sep before _154 after sep before _153 after sep \
  before _152 after sep before _151 after sep before _150 after sep before _149 after sep \
  before _148 after sep before _147 after sep before _146 after sep before _145 after sep \
  before _144 after sep before _143 after sep before _142 after sep before _141 after sep \
  before _140 after sep before _139 after sep before _138 after sep before _137 after sep \
  before _136 after sep before _135 after sep before _134 after sep before _133 after sep \
  before _132 after sep before _131 after sep before _130 after sep before _129 after sep \
  before _128 after sep before _127 after sep before _126 after sep before _125 after sep \
  before _124 after sep before _123 after sep before _122 after sep before _121 after sep \
  before _120 after sep before _119 after sep before _118 after sep before _117 after sep \
  before _116 after sep before _115 after sep before _114 after sep before _113 after sep \
  before _112 after sep before _111 after sep before _110 after sep before _109 after sep \
  before _108 after sep before _107 after sep before _106 after sep before _105 after sep \
  before _104 after sep before _103 after sep before _102 after sep before _101 after sep \
  before _100 after sep before _99 after sep before _98 after sep before _97 after sep    \
  before _96 after sep before _95 after sep before _94 after sep before _93 after sep     \
  before _92 after sep before _91 after sep before _90 after sep before _89 after sep     \
  before _88 after sep before _87 after sep before _86 after sep before _85 after sep     \
  before _84 after sep before _83 after sep before _82 after sep before _81 after sep     \
  before _80 after sep before _79 after sep before _78 after sep before _77 after sep     \
  before _76 after sep before _75 after sep before _74 after sep before _73 after sep     \
  before _72 after sep before _71 after sep before _70 after sep before _69 after sep     \
  before _68 after sep before _67 after sep before _66 after sep before _65 after sep     \
  before _64 after sep before _63 after sep before _62 after sep before _61 after sep     \
  before _60 after sep before _59 after sep before _58 after sep before _57 after sep     \
  before _56 after sep before _55 after sep before _54 after sep before _53 after sep     \
  before _52 after sep before _51 after sep before _50 after sep before _49 after sep     \
  before _48 after sep before _47 after sep before _46 after sep before _45 after sep     \
  before _44 after sep before _43 after sep before _42 after sep before _41 after sep     \
  before _40 after sep before _39 after sep before _38 after sep before _37 after sep     \
  before _36 after sep before _35 after sep before _34 after sep before _33 after sep     \
  before _32 after sep before _31 after sep before _30 after sep before _29 after sep     \
  before _28 after sep before _27 after sep before _26 after sep before _25 after sep     \
  before _24 after sep before _23 after sep before _22 after sep before _21 after sep     \
  before _20 after sep before _19 after sep before _18 after sep before _17 after sep     \
  before _16 after sep before _15 after sep before _14 after sep before _13 after sep     \
  before _12 after sep before _11 after sep before _10 after sep before _9 after sep      \
  before _8 after sep before _7 after sep before _6 after sep before _5 after sep         \
  before _4 after sep before _3 after sep before _2 after sep before _1 after

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct fold_impl;
  }
  /// \endcond

  /// \ingroup reduce

  /// Folds left over a list using a binary predicate.
  /// The first element in the input pack as the state,
  /// use \c push_front<> to add state if needed.
  /// \semantics
  ///   \code
  ///   F::f<F::f<F::f<F::f<xs[0], xs[1]>, xs[2]>, ...>, xs[n-1]>
  ///   \endcode
  /// \pre `sizeof...(xs) >= 1`
  /// \treturn \value
  /// \see fold_right, fold_tree, reverse_fold, fold_balanced_tree
  template<class F, class C = identity>
  struct fold
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::fold_impl<
        int(sizeof...(xs)) - 1
      >::template f<JLN_MP_TRACE_F(F)::template f, xs...>
    );
  };

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using fold = unpack<L,
      mp::push_front<state, mp::fold<F, C>>>;

    template<class L, class F, class C = mp::identity>
    using reduce = unpack<L, mp::fold<F, C>>;
  }
}


/// \cond
namespace jln::mp
{
  template<class F>
  struct fold<F, identity>
  {
    template<class... xs>
    using f = typename detail::fold_impl<
      int(sizeof...(xs)) - 1
    >::template f<JLN_MP_TRACE_F(F)::template f, xs...>;
  };

#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
  template<template<class...> class F, class C>
  struct fold<lift<F>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::fold_impl<
        int(sizeof...(xs)) - 1
      >::template f<F, xs...>
    );
  };

  template<template<class...> class F>
  struct fold<lift<F>, identity>
  {
    template<class... xs>
    using f = typename detail::fold_impl<
      int(sizeof...(xs)) - 1
    >::template f<F, xs...>;
  };
#endif
}

namespace jln::mp::detail
{
  template<int n>
  struct fold_impl : fold_impl<
      n < 8 ? 4
    : n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

#define JLN_MP_FOLD_LEFT_SELECT(n, mp_xs, _, mp_dup)  \
  template<>                                          \
  struct fold_impl<n>                                 \
  {                                                   \
    template<template<class...> class F, class state, \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),         \
      class... xs>                                    \
    using f = typename fold_impl<                     \
      sizeof...(xs)                                   \
    >::template f<F,                                  \
      mp_dup(F<, JLN_MP_NIL) state,                   \
      mp_xs(JLN_MP_NIL, >, JLN_MP_COMMA), xs...       \
    >;                                                \
  };

  JLN_MP_GEN_XS_4_8_16_64_256(JLN_MP_FOLD_LEFT_SELECT)

#undef JLN_MP_FOLD_LEFT_SELECT

#define JLN_MP_FOLD_LEFT_SELECT(n, mp_xs, _, mp_dup)  \
  template<>                                          \
  struct fold_impl<n>                                 \
  {                                                   \
    template<template<class...> class F, class state, \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA)>         \
    using f = mp_dup(F<, JLN_MP_NIL) state,           \
      mp_xs(JLN_MP_NIL, >, JLN_MP_COMMA);             \
  };

  JLN_MP_GEN_XS_1_TO_4(JLN_MP_FOLD_LEFT_SELECT)

#undef JLN_MP_FOLD_LEFT_SELECT

  template<>
  struct fold_impl<0>
  {
    template<template<class...> class, class state>
    using f = state;
  };

  template<>
  struct fold_impl<-1>
  {};
}
/// \endcond


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct transform_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Executes \c F on every element of a \sequence.
  /// \treturn \sequence
  template<class F, class C = listify>
  struct transform
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, JLN_MP_DCALL_TRACE_XS(xs, F, xs)...);
#else
    template<class... xs>
    using f = typename detail::transform_impl<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
      ::template f<JLN_MP_TRACE_F(C)::template f, JLN_MP_TRACE_F(F)::template f, xs...>;
#endif
  };

  namespace emp
  {
    template<class L, class F, class C = mp::listify>
    using transform = unpack<L, mp::transform<F, C>>;
  }

/// \cond
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
  template<class F, template<class...> class C>
  struct transform<F, lift<C>>
  {
    template<class... xs>
    using f = typename detail::transform_impl<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
      ::template f<C, F::template f, xs...>;
  };

  template<template<class...> class F, class C>
  struct transform<lift<F>, C>
  {
    template<class... xs>
    using f = typename detail::transform_impl<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
      ::template f<C::template f, F, xs...>;
  };

  template<template<class...> class F, template<class...> class C>
  struct transform<lift<F>, lift<C>>
  {
    template<class... xs>
    using f = typename detail::transform_impl<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
      ::template f<C, F, xs...>;
  };
#endif

#if ! JLN_MP_ENABLE_DEBUG
  namespace detail
  {
    template<bool>
    struct transform_impl_t;
  }

  template<template<class...> class F, class C>
  struct transform<lift_t<F>, C>
  {
    template<class... xs>
    using f = typename detail::transform_impl_t<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
      ::template f<C::template f, F, xs...>;
  };

  template<template<class...> class F, template<class...> class C>
  struct transform<lift_t<F>, lift<C>>
  {
    template<class... xs>
    using f = typename detail::transform_impl_t<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
      ::template f<C, F, xs...>;
  };
#endif
/// \endcond
}


/// \cond
namespace jln::mp::detail
{
  template<>
  struct transform_impl<true>
  {
    template<template<class...> class C, template<class...> class F, class...xs>
    using f = C<F<xs>...>;
  };

  template<>
  struct transform_impl<false>
  {};

#if ! JLN_MP_ENABLE_DEBUG
  template<>
  struct transform_impl_t<true>
  {
    template<template<class...> class C, template<class...> class F, class...xs>
    using f = C<typename F<xs>::type...>;
  };

  template<>
  struct transform_impl_t<false>
  {};
#endif

  template<class T>
  struct optimize_useless_transform_unpack
  {
    using type = T;
  };

  template<class T>
  using optimize_useless_transform_unpack_t
    = typename optimize_useless_transform_unpack<T>::type;

  template<class F>
  struct optimize_useless_transform_unpack_impl
  {
    template<class C>
    using f = transform<F, C>;
  };

  template<>
  struct optimize_useless_transform_unpack_impl<identity>
  {
    template<class C>
    using f = optimize_useless_transform_unpack_t<C>;
  };

  template<class F, class C>
  struct optimize_useless_transform_unpack<transform<F, C>>
  {
    using type = typename optimize_useless_transform_unpack_impl<optimize_useless_unpack_t<F>>
      ::template f<C>;
  };
}
/// \endcond


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<std::size_t n>
    struct _join_select;
  }
  /// \endcond

  /// \ingroup list

  /// Concatenates \lists.
  /// \pre \c seqs must be a \sequence of \list
  /// \treturn \sequence
  template<class C = listify>
  struct join
  {
    template<class... seqs>
    using f = typename detail::_join_select<sizeof...(seqs)>
      ::template f<JLN_MP_TRACE_F(C)::template f, seqs...>::type;
  };

  /// \cond
  #if ! JLN_MP_OPTIMIZED_ALIAS
  template<template<class...> class C>
  struct join<lift<C>>
  {
    template<class... seqs>
    using f = typename detail::_join_select<sizeof...(seqs)>
      ::template f<C, seqs...>::type;
  };
  #endif
  /// \endcond

  namespace emp
  {
    template<class... seqs>
    using join = typename mp::join<>::template f<seqs...>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<std::size_t n>
  struct _join_select : _join_select<
      n <= 2 ? 2
    : n <= 8 ? 8
    : n <= 16 ? 16
    : n <= 64 ? 64
    : n <= 256 ? 256
    : 512
  >
  {};

  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_MSVC_IGNORE(4348)

#define JLN_MP_JOIN_SELECT(n, mp_xs, mp_rxs, _)   \
  template<>                                      \
  struct _join_select<n>                          \
  {                                               \
    template<template<class...> class F,          \
      mp_xs(class, = list<>, JLN_MP_COMMA)>       \
    struct f;                                     \
                                                  \
    template<template<class...> class F,          \
      mp_xs(class..., JLN_MP_NIL, JLN_MP_COMMA)>  \
    struct f<F, mp_xs(list<, ...>, JLN_MP_COMMA)> \
    {                                             \
      using type = F<                             \
        mp_xs(JLN_MP_NIL, ..., JLN_MP_COMMA)>;    \
    };                                            \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_JOIN_SELECT)
  JLN_MP_JOIN_SELECT(2, JLN_MP_XS_2, _, _)

#undef JLN_MP_JOIN_SELECT

  template<>
  struct _join_select<512>
  {
    template<template<class...> class F,
      JLN_MP_XS_512(class, = list<>, JLN_MP_COMMA),
      class... tail>
    struct f;

    template<template<class...> class F,
      JLN_MP_XS_512(class..., JLN_MP_NIL, JLN_MP_COMMA),
      class... tail>
    struct f<F, JLN_MP_XS_512(list<, ...>, JLN_MP_COMMA), tail...>
    : _join_select<2>::f<F,
        list<JLN_MP_XS_512(JLN_MP_NIL, ..., JLN_MP_COMMA)>,
        typename _join_select<sizeof...(tail)>::template f<list, tail...>::type>
    {};
  };

  JLN_MP_DIAGNOSTIC_POP()

} // namespace jln::mp::detail
/// \endcond


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct _zip_dispatch;
  }
  /// \endcond

  /// \ingroup group

  /// Turns rows into columns, and columns into rows.
  /// This is similar to transposing a matrix.
  /// \pre all parameters must be \lists
  /// \pre all lists must be the same size
  /// \semantics
  ///   \code
  ///   zip<>::f<
  ///     list<_1, _2, _3>,
  ///     list<_a, _b, _c>
  ///   > = list<
  ///     list<_1, _a>,
  ///     list<_2, _b>,
  ///     list<_3, _c>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see zip_longest
  template<class F = listify, class C = listify>
  struct zip_with
  {
    template<class... seqs>
    using f = typename detail::_zip_dispatch<
      sizeof...(seqs) ? sizeof...(seqs) <= 8 ? 1 : 2 : 0
    >::template f<
      JLN_MP_TRACE_F(C)::template f,
      JLN_MP_TRACE_F(F)::template f,
      seqs...
    >;
  };

  template<class C = listify>
  using zip = zip_with<listify, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using zip = unpack<L, mp::zip<C>>;

    template<class L, class F = mp::listify, class C = mp::listify>
    using zip_with = unpack<L, mp::zip_with<F, C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class...>
  struct _zip_impl;

#define JLN_MP_TRANSPOSE_IMPL(n, mp_xs, mp_rxs, mp_rep)              \
  template<mp_xs(class..., JLN_MP_NIL, JLN_MP_COMMA)>                \
  struct _zip_impl<mp_xs(list<, ...>, JLN_MP_COMMA)>                 \
  {                                                                  \
    template<template<class...> class C, template<class...> class F> \
    using f = C<F<mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>...>;  \
  };

  JLN_MP_GEN_XS_1_TO_8_INCLUDED(JLN_MP_TRANSPOSE_IMPL)

#undef JLN_MP_TRANSPOSE_IMPL

  template<>
  struct _zip_dispatch<0>
  {
    template<template<class...> class C, template<class...> class F>
    // using f = JLN_MP_CALL_TRACE_0_ARG(C);
    using f = C<>;
  };

  template<>
  struct _zip_dispatch<1>
  {
    template<template<class...> class C, template<class...> class F, class... seqs>
    using f = typename _zip_impl<seqs...>::template f<C, F>;
  };

  template<int>
  struct _recursive_zip;

  template<>
  struct _recursive_zip<0>
  {
    template<int n, template<class...> class C, template<class...> class F, class... seqs>
    using f = typename detail::_zip_dispatch<
      sizeof...(seqs) <= 8 ? 1 : 2
    >::template f<C, F, seqs...>;
  };

#define JLN_MP_TRANSPOSE_IMPL(n, mp_xs, mp_rxs, mp_rep)                  \
  template<>                                                             \
  struct _recursive_zip<n>                                               \
  {                                                                      \
    template<int, template<class...> class C, template<class...> class F \
      mp_xs(JLN_MP_COMMA class, JLN_MP_NIL, JLN_MP_NIL),                 \
      class... seqs>                                                     \
    using f = typename detail::_zip_dispatch<                            \
      sizeof...(seqs) < 8 ? 1 : 2                                        \
    >::template f<C, join<lift<F>>::template f, seqs...,                 \
        typename _zip_impl<mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>  \
        ::template f<list, list>                                         \
      >;                                                                 \
  };

  template<>
  struct _recursive_zip<8>
  {
    template<int n, template<class...> class C, template<class...> class F,
      class _0, class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class... seqs>
    using f = typename _recursive_zip<n < 8 ? n : 8>
      ::template f<
        n-8, C, F, seqs..., typename _zip_impl<
          _0, _1, _2, _3, _4, _5, _6, _7
        >::template f<list, list>
      >;
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_TRANSPOSE_IMPL)

#undef JLN_MP_TRANSPOSE_IMPL

  template<>
  struct _zip_dispatch<2>
  {
    template<template<class...> class C, template<class...> class F, class... seqs>
    using f = typename _recursive_zip<!sizeof...(seqs) + 8>
      ::template f<sizeof...(seqs)-8, C, F, seqs...>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup functional

  /// Invokes a \function with its two first arguments reversed.
  /// \semantics
  ///   \code
  ///   C::f<xs[1], xs[0], ...xs[2:]>
  ///   \endcode
  /// \treturn \sequence
  template<class C = listify>
  struct flip
  {
    template<class x0, class x1, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, x1, x0, xs...);
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using flip = unpack<L, mp::flip<C>>;
  }

  /// \cond
  template<>
  struct flip<listify>
  {
    template<class x0, class x1, class... xs>
    using f = list<x1, x0, xs...>;
  };
  /// \endcond
}


namespace jln::mp
{
  /// \ingroup algorithm

  /// Computes the recursive invocation of \c F with the result of the previous
  /// invocation and each element of one or more \lists traversed in parallel
  /// from the beginning to the end.
  /// \pre all \c seqs must be the same size
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   C::f<fold<F>::f<
  ///     ...
  ///     fold<F>::f<fold<F>::f<state, ...seqs[:][0]>, ...seqs[:][1]>
  ///     ...,
  ///     ...seqs[:][n-1]>
  ///   >>
  ///   \endcode
  /// \treturn \value
  template<class F, class C = identity>
  struct accumulate
  {
    template<class state, class... seqs>
    using f = typename zip<push_front<state, fold<flip<unpack<F>>, C>>>
      ::template f<seqs...>;
  };

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using accumulate = unpack<L,
      mp::zip<mp::push_front<state, mp::fold<mp::flip<mp::unpack<F>>, C>>>>;
  }
}

namespace jln::mp
{
  /// \ingroup utility

  /// Always evaluate at an arbitrary value.
  /// \post result = x
  /// \treturn \value
  template<class x, class C = identity>
  struct always
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, x);
  };

  /// \cond
  template<class x>
  struct always<x, identity>
  {
    template<class... xs>
    using f = x;
  };
  /// \endcond
}

namespace jln::mp
{
  /// \ingroup list

  /// Removes all elements from the \sequence.
  /// \treturn \value
  template<class C = listify>
  struct clear
  {
    template<class... xs>
    using f = typename C::template f<>;
  };

  /// \cond
  template<>
  struct clear<listify>
    : always<list<>>
  {};
  /// \endcond
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct index;

    template<class...>
    struct indexed;

    template<int, bool = false>
    struct indexed_builder;

    template<int, class PrecomputedIndexes>
    struct build_indexed_v_impl;

#if JLN_MP_MEMOIZED_ALIAS
    template<int, class PrecomputedIndexes>
    struct build_indexed_impl;
#endif

    constexpr int build_indexed_state(std::size_t n);
  }
  /// \endcond

  /// \ingroup list

  /// Constructs an indexable sequence in O(1).
  /// \pre 0 <= i < sizeof...(xs)
  template<class... xs>
  struct build_indexed_v
  : detail::build_indexed_v_impl<
      detail::build_indexed_state(sizeof...(xs)),
      typename detail::indexed_builder<detail::build_indexed_state(sizeof...(xs))>
      ::template f<xs...>
    >
  {
#ifdef JLN_MP_DOXYGENATING
    template<int i>
    using f;
#endif
  };

  /// Constructs an indexable sequence in O(1).
  /// If possible prefer the use of build_indexed_v
  /// \pre 0 <= i::value < sizeof...(xs)
#if JLN_MP_MEMOIZED_ALIAS
  template<class... xs>
  struct build_indexed
  : detail::build_indexed_impl<
      detail::build_indexed_state(sizeof...(xs)),
      typename detail::indexed_builder<detail::build_indexed_state(sizeof...(xs))>
      ::template f<xs...>
    >
  {
#ifdef JLN_MP_DOXYGENATING
    template<class i>
    using f;
#endif
  };
#else
  template<class... xs>
  struct build_indexed
  {
  private:
    using BuildIndexedV = build_indexed_v<xs...>;

  public:
#if JLN_MP_MEMOIZED_ALIAS
    template<class i>
    using f = typename BuildIndexedV::template f<i::value>;
#else
    template<class i>
    using f = typename BuildIndexedV::template memoize_result_<i::value>::type;
#endif
  };
#endif

  namespace emp
  {
    template<class L>
    using build_indexed_v = unpack<L, lift<mp::build_indexed_v>>;

    template<class L>
    using build_indexed = unpack<L, lift<mp::build_indexed>>;

    template<class L, int i>
    using lookup_c = typename unpack<L, mp::lift<mp::build_indexed_v>>::template f<i>;

    template<class L, class I>
    using lookup = typename unpack<L, mp::lift<mp::build_indexed_v>>::template f<I::value>;

    template<class IndexedV, int i>
    using indexed_lookup_c = typename IndexedV::template f<i>;

    template<class IndexedV, class I>
    using indexed_lookup = typename IndexedV::template f<I::value>;
  }
}



namespace jln::mp::detail
{
  // fast propagation of lift<build_indexed_v, F> without dependency call
  template<class F>
  struct apply_indexed_v
  {
    template<class... xs>
    using f = typename F::template f<build_indexed_v<xs...>>;
  };


#define JLN_MP_INDEX(n, mp_xs, mp_rxs, mp_dup)      \
  template<>                                        \
  struct index<n-1>                                 \
  {                                                 \
    template<mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL) \
             class... xs>                           \
    using f = _##n;                                 \
  };

  JLN_MP_GEN_XS_1_TO_16_INCLUDED(JLN_MP_INDEX)

#undef JLN_MP_INDEX

  using index0 = index<0>;

  template<class Head, class Tail>
  struct rlist;

  class unindexed;

  using rlist_tail_of15 =
    rlist<unindexed,
      rlist<unindexed,
        rlist<unindexed,
          rlist<unindexed,
            rlist<unindexed,
              rlist<unindexed,
                rlist<unindexed,
                  rlist<unindexed,
                    rlist<unindexed,
                      rlist<unindexed,
                        rlist<unindexed,
                          rlist<unindexed,
                            rlist<unindexed,
                              rlist<unindexed,
                                rlist<unindexed, unindexed>>>>>>>>>>>>>>>;

  template<class... xs>
  struct indexed
  {
    template<class F>
    using f = typename F::template f<xs...>;
  };

  template<class x>
  struct rlist_to_indexed;

  template<
    class x0, class x1, class x2, class x3, class x4, class x5,
    class x6, class x7, class x8, class x9, class x10, class x11,
    class x12, class x13, class x14, class x15, class Tail>
  struct rlist_to_indexed<
    rlist<x0,
      rlist<x1,
        rlist<x2,
          rlist<x3,
            rlist<x4,
              rlist<x5,
                rlist<x6,
                  rlist<x7,
                    rlist<x8,
                      rlist<x9,
                        rlist<x10,
                          rlist<x11,
                            rlist<x12,
                              rlist<x13,
                                rlist<x14,
                                  rlist<x15, Tail>>>>>>>>>>>>>>>>>
  {
    template<template<class...> class F>
    using f = F<x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15>;
  };


  template<class x>
  struct rlist_to_indexed_rlist;

  template<
    class x0, class x1, class x2, class x3, class x4, class x5,
    class x6, class x7, class x8, class x9, class x10, class x11,
    class x12, class x13, class x14, class x15, class Tail>
  struct rlist_to_indexed_rlist<
    rlist<x0,
      rlist<x1,
        rlist<x2,
          rlist<x3,
            rlist<x4,
              rlist<x5,
                rlist<x6,
                  rlist<x7,
                    rlist<x8,
                      rlist<x9,
                        rlist<x10,
                          rlist<x11,
                            rlist<x12,
                              rlist<x13,
                                rlist<x14,
                                  rlist<x15, Tail>>>>>>>>>>>>>>>>>
  {
    using type = rlist<
      indexed<x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15>,
      typename rlist_to_indexed_rlist<Tail>::type
    >;
  };


  template<
    class x0, class x1, class x2, class x3, class x4, class x5,
    class x6, class x7, class x8, class x9, class x10, class x11,
    class x12, class x13, class x14, class x15, class Tail>
  struct rlist_to_indexed_rlist<
    rlist<x0,
      rlist<x1,
        rlist<x2,
          rlist<x3,
            rlist<x4,
              rlist<x5,
                rlist<x6,
                  rlist<x7,
                    rlist<x8,
                      rlist<x9,
                        rlist<x10,
                          rlist<x11,
                            rlist<x12,
                              rlist<x13,
                                rlist<x14,
                                  rlist<x15,
                                    rlist<unindexed, Tail>>>>>>>>>>>>>>>>>>
  {
    using type = rlist<
      indexed<x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15>,
      rlist_tail_of15
    >;
  };

  template<
    class x0, class x1, class x2, class x3, class x4, class x5,
    class x6, class x7, class x8, class x9, class x10, class x11,
    class x12, class x13, class x14, class x15>
  struct rlist_to_indexed_rlist<
    rlist<x0,
      rlist<x1,
        rlist<x2,
          rlist<x3,
            rlist<x4,
              rlist<x5,
                rlist<x6,
                  rlist<x7,
                    rlist<x8,
                      rlist<x9,
                        rlist<x10,
                          rlist<x11,
                            rlist<x12,
                              rlist<x13,
                                rlist<x14,
                                  rlist<x15, unindexed>>>>>>>>>>>>>>>>>
  {
    using type = rlist<
      indexed<x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15>,
      rlist_tail_of15
    >;
  };


  constexpr int build_indexed_state(std::size_t n)
  {
    return n <= 16 ? 0
         : n <= 256 ? 1
         : n <= 4096 ? 2
         : 3;
  }


  // 0 <= sizeof...(xs) <= 16
  template<>
  struct indexed_builder<0>
    : listify
  {};

  // 16 < sizeof...(xs) <= 256
  template<>
  struct indexed_builder<1>
  {
    template<JLN_MP_XS_256(class, = unindexed, JLN_MP_COMMA)>
    using f = indexed<
      indexed<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12,
              _13, _14, _15, _16>,
      indexed<_17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27,
              _28, _29, _30, _31, _32>,
      indexed<_33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43,
              _44, _45, _46, _47, _48>,
      indexed<_49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59,
              _60, _61, _62, _63, _64>,

      indexed<_65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75,
              _76, _77, _78, _79, _80>,
      indexed<_81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91,
              _92, _93, _94, _95, _96>,
      indexed<_97, _98, _99, _100, _101, _102, _103, _104, _105,
              _106, _107, _108, _109, _110, _111, _112>,
      indexed<_113, _114, _115, _116, _117, _118, _119, _120, _121,
              _122, _123, _124, _125, _126, _127, _128>,

      indexed<_129, _130, _131, _132, _133, _134, _135, _136, _137,
              _138, _139, _140, _141, _142, _143, _144>,
      indexed<_145, _146, _147, _148, _149, _150, _151, _152, _153,
              _154, _155, _156, _157, _158, _159, _160>,
      indexed<_161, _162, _163, _164, _165, _166, _167, _168, _169,
              _170, _171, _172, _173, _174, _175, _176>,
      indexed<_177, _178, _179, _180, _181, _182, _183, _184, _185,
              _186, _187, _188, _189, _190, _191, _192>,

      indexed<_193, _194, _195, _196, _197, _198, _199, _200, _201,
              _202, _203, _204, _205, _206, _207, _208>,
      indexed<_209, _210, _211, _212, _213, _214, _215, _216, _217,
              _218, _219, _220, _221, _222, _223, _224>,
      indexed<_225, _226, _227, _228, _229, _230, _231, _232, _233,
              _234, _235, _236, _237, _238, _239, _240>,
      indexed<_241, _242, _243, _244, _245, _246, _247, _248, _249,
              _250, _251, _252, _253, _254, _255, _256>
    >;
  };

  // 256 < sizeof...(xs) <= 4096
  template<>
  struct indexed_builder<2, false>
  {
    template<JLN_MP_XS_256(class, = unindexed, JLN_MP_COMMA), class... xs>
    using f = rlist<
      indexed<indexed<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12,
                      _13, _14, _15, _16>,
              indexed<_17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27,
                      _28, _29, _30, _31, _32>,
              indexed<_33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43,
                      _44, _45, _46, _47, _48>,
              indexed<_49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59,
                      _60, _61, _62, _63, _64>,

              indexed<_65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75,
                      _76, _77, _78, _79, _80>,
              indexed<_81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91,
                      _92, _93, _94, _95, _96>,
              indexed<_97, _98, _99, _100, _101, _102, _103, _104, _105,
                      _106, _107, _108, _109, _110, _111, _112>,
              indexed<_113, _114, _115, _116, _117, _118, _119, _120, _121,
                      _122, _123, _124, _125, _126, _127, _128>,

              indexed<_129, _130, _131, _132, _133, _134, _135, _136, _137,
                      _138, _139, _140, _141, _142, _143, _144>,
              indexed<_145, _146, _147, _148, _149, _150, _151, _152, _153,
                      _154, _155, _156, _157, _158, _159, _160>,
              indexed<_161, _162, _163, _164, _165, _166, _167, _168, _169,
                      _170, _171, _172, _173, _174, _175, _176>,
              indexed<_177, _178, _179, _180, _181, _182, _183, _184, _185,
                      _186, _187, _188, _189, _190, _191, _192>,

              indexed<_193, _194, _195, _196, _197, _198, _199, _200, _201,
                      _202, _203, _204, _205, _206, _207, _208>,
              indexed<_209, _210, _211, _212, _213, _214, _215, _216, _217,
                      _218, _219, _220, _221, _222, _223, _224>,
              indexed<_225, _226, _227, _228, _229, _230, _231, _232, _233,
                      _234, _235, _236, _237, _238, _239, _240>,
              indexed<_241, _242, _243, _244, _245, _246, _247, _248, _249,
                      _250, _251, _252, _253, _254, _255, _256>>,
      typename indexed_builder<2, sizeof...(xs) <= 16>::template f<xs...>
    >;
  };

  // 256 < sizeof...(xs) <= 4096
  template<>
  struct indexed_builder<2, true>
  {
    template<
      class x0 = unindexed, class x1 = unindexed, class x2 = unindexed, class x3 = unindexed,
      class x4 = unindexed, class x5 = unindexed, class x6 = unindexed, class x7 = unindexed,
      class x8 = unindexed, class x9 = unindexed, class x10 = unindexed, class x11 = unindexed,
      class x12 = unindexed, class x13 = unindexed, class x14 = unindexed, class x15 = unindexed>
    using f = rlist<
      indexed<indexed<x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15>>,
      rlist_tail_of15
    >;
  };

  // 4096 < sizeof...(xs)
  template<>
  struct indexed_builder<3> : indexed_builder<2>
  {};


#if JLN_MP_MEMOIZED_ALIAS
#  define JLN_MP_BUILD_INDEXED_IMPL(impl) template<int i> using f = impl
#  define JLN_MP_INDEXED_GET(i, ...) __VA_ARGS__::f<i>
#  define JLN_MP_D_INDEXED_GET(i, ...) __VA_ARGS__::template f<i>
#else
#  define JLN_MP_BUILD_INDEXED_IMPL(impl)                        \
  template<int i> struct memoize_result_ { using type = impl; }; \
  template<int i> using f = typename memoize_result_<i>::type
#  define JLN_MP_INDEXED_GET(i, ...) __VA_ARGS__::memoize_result_<i>::type
#  define JLN_MP_D_INDEXED_GET(i, ...) __VA_ARGS__::template memoize_result_<i>::type
#endif

  // 0 <= sizeof...(xs) <= 16
  template<class... xs>
  struct build_indexed_v_impl<0, list<xs...>>
  {
    JLN_MP_BUILD_INDEXED_IMPL(typename index<i>::template f<xs...>);
  };

  // 16 < sizeof...(xs) <= 256
  template<class PrecomputedIndexes>
  struct build_indexed_v_impl<1, PrecomputedIndexes>
  {
    JLN_MP_BUILD_INDEXED_IMPL(
      typename PrecomputedIndexes
      ::template f<index<(i >> 4)>>
      ::template f<index<i & 0xf>>
    );
  };

  // 256 < sizeof...(xs) <= 4096
  template<class PrecomputedIndexes>
  class build_indexed_v_impl<2, PrecomputedIndexes>
  {
    using _precomputed_indexes = typename rlist_to_indexed<PrecomputedIndexes>
      ::template f<indexed>;

  public:
    JLN_MP_BUILD_INDEXED_IMPL(
      typename _precomputed_indexes
      ::template f<index<(i >> 8)>>
      ::template f<index<(i >> 4) & 0xF>>
      ::template f<index<(i & 0xF)>>
    );
  };

  // 4096 < sizeof...(xs) <= 65536
  template<class PrecomputedIndexes>
  class build_indexed_v_impl<3, PrecomputedIndexes>
  {
    using _precomputed_indexes = typename rlist_to_indexed<
      typename rlist_to_indexed_rlist<PrecomputedIndexes>::type
    >::template f<indexed>;

  public:
    JLN_MP_BUILD_INDEXED_IMPL(
      typename _precomputed_indexes
      ::template f<index<(i >> 12)>>
      ::template f<index<(i >> 8) & 0xF>>
      ::template f<index<(i >> 4) & 0xF>>
      ::template f<index<(i & 0xF)>>
    );
  };

#undef JLN_MP_BUILD_INDEXED_IMPL

# if JLN_MP_MEMOIZED_ALIAS
  // 0 <= sizeof...(xs) <= 16
  template<class... xs>
  struct build_indexed_impl<0, list<xs...>>
  {
    template<class i>
    using f = typename index<i::value>::template f<xs...>;
  };

  // 16 < sizeof...(xs) <= 256
  template<class PrecomputedIndexes>
  struct build_indexed_impl<1, PrecomputedIndexes>
  {
    template<class i>
    using f = typename PrecomputedIndexes
      ::template f<index<(i::value >> 4)>>
      ::template f<index<i::value & 0xf>>;
  };

  // 256 < sizeof...(xs) <= 4096
  template<class PrecomputedIndexes>
  class build_indexed_impl<2, PrecomputedIndexes>
  {
    using _precomputed_indexes = typename rlist_to_indexed<PrecomputedIndexes>
      ::template f<indexed>;

  public:
    template<class i>
    using f = typename _precomputed_indexes
      ::template f<index<(i::value >> 8)>>
      ::template f<index<(i::value >> 4) & 0xF>>
      ::template f<index<i::value & 0xF>>;
  };

  // 4096 < sizeof...(xs) <= 65536
  template<class PrecomputedIndexes>
  class build_indexed_impl<3, PrecomputedIndexes>
  {
    using _precomputed_indexes = typename rlist_to_indexed<
      typename rlist_to_indexed_rlist<PrecomputedIndexes>::type
    >::template f<indexed>;

  public:
    template<class i>
    using f = typename _precomputed_indexes
      ::template f<index<(i::value >> 12)>>
      ::template f<index<(i::value >> 8) & 0xF>>
      ::template f<index<(i::value >> 4) & 0xF>>
      ::template f<index<i::value & 0xF>>;
  };
#endif

}

namespace jln::mp
{
  /// \ingroup list

  /// Retrieves the first element of a sequence.
  /// \treturn \value
  template<class C = identity>
  struct front
  {
    template<class x, class... xs>
    using f = JLN_MP_CALL_TRACE(C, x);
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using front = unpack<L, front<C>>;
  }
}

/// \cond

namespace jln::mp
{
  template<>
  struct front<identity> : detail::index<0>
  {};
}

// facilitates sfinae version for is_map_impl
namespace jln::mp::detail
{
  template<class C, template<class...> class Seq>
  struct _unpack<front<C>, Seq<>>
  {};
}
/// \endcond


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned>
    struct drop_front_impl;
  }
  /// \endcond

  /// \ingroup list

  /// Removes \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N <= sizeof...(xs)`
  /// \treturn \sequence
  /// \see drop_front_max, drop_back, take_front, take_back, drop_while
#ifdef JLN_MP_DOXYGENATING
  template<unsigned N, class C = listify>
  struct drop_front_c
  {
    template<class... xs>
    using f;
  };
#else
  template<unsigned N, class C = listify>
  struct drop_front_c;
#endif

  /// Removes at most \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N`
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_while
  template<unsigned N, class C = listify>
  struct drop_front_max_c
  {
    template<class... xs>
    using f = typename detail::drop_front_impl<
      sizeof...(xs) < N ? sizeof...(xs) : N
    >::template f<
      sizeof...(xs) < N ? sizeof...(xs) : N,
      JLN_MP_TRACE_F(C),
      xs...
    >;
  };

  template<class N, class C = listify>
  using drop_front = drop_front_c<N::value, C>;

  template<class N, class C = listify>
  using drop_front_max = drop_front_max_c<N::value, C>;

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using drop_front = unpack<L, mp::drop_front<N, C>>;

    template<class L, unsigned n, class C = mp::listify>
    using drop_front_c = unpack<L, mp::drop_front_c<n, C>>;

    template<class L, class N, class C = mp::listify>
    using drop_front_max = unpack<L, mp::drop_front_max<N, C>>;

    template<class L, unsigned n, class C = mp::listify>
    using drop_front_max_c = unpack<L, mp::drop_front_max_c<n, C>>;
  }

  /// \cond
  template<class C>
  struct drop_front_c<0, C>
    : detail::call_trace_xs<C>
  {};

  template<class C>
  struct drop_front_max_c<0, C>
    : detail::call_trace_xs<C>
  {};

  template<>
  struct drop_front_c<0, listify> : listify
  {};

  template<>
  struct drop_front_max_c<0, listify> : listify
  {};

  template<class C>
  struct drop_front_c<0, front<C>>
  {
    template<class x, class...>
    using f = JLN_MP_CALL_TRACE(C, x);
  };

  template<>
  struct drop_front_c<0, front<identity>> : detail::index<0>
  {};

  #define JLN_MP_DROP_FRONT(n, mp_xs, mp_rxs, mp_dup)             \
    template<class C>                                             \
    struct drop_front_c<n, C>                                     \
    {                                                             \
      template<mp_dup(class, JLN_MP_COMMA), class... xs>          \
      using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);              \
    };                                                            \
                                                                  \
    template<>                                                    \
    struct drop_front_c<n, listify>                               \
    {                                                             \
      template<mp_dup(class, JLN_MP_COMMA), class... xs>          \
      using f = list<xs...>;                                      \
    };                                                            \
                                                                  \
    template<class C>                                             \
    struct drop_front_c<n, front<C>>                              \
    {                                                             \
      template<mp_dup(class, JLN_MP_COMMA), class x, class... xs> \
      using f = JLN_MP_CALL_TRACE(C, x);                          \
    };                                                            \
                                                                  \
    template<>                                                    \
    struct drop_front_c<n, front<identity>> : detail::index<n>    \
    {};

  JLN_MP_GEN_XS_1_TO_8_INCLUDED(JLN_MP_DROP_FRONT)
  #undef JLN_MP_DROP_FRONT

  // N >= 9
  template<unsigned N, class C>
  struct drop_front_c
  {
    template<class, class, class, class,
             class, class, class, class,
             class, class... xs>
    using f = typename detail::drop_front_impl<
      (sizeof...(xs) & 0) + N-9
    >::template f<N-9, JLN_MP_TRACE_F(C), xs...>;
  };

#if JLN_MP_HAS_BUILTIN(__type_pack_element)
  template<unsigned N, class C>
  struct drop_front_c<N, front<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, __type_pack_element<N, xs...>);
  };

  template<unsigned N>
  struct drop_front_c<N, front<identity>>
  {
    template<class... xs>
    using f = __type_pack_element<N, xs...>;
  };

  template<unsigned N, class C>
  struct drop_front_max_c<N, front<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      __type_pack_element<sizeof...(xs) < N ? sizeof...(xs) : N, xs...>
    );
  };

  template<unsigned N>
  struct drop_front_max_c<N, front<identity>>
  {
    template<class... xs>
    using f = __type_pack_element<sizeof...(xs) < N ? sizeof...(xs) : N, xs...>;
  };
#endif
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template<unsigned n>
  struct drop_front_impl : drop_front_impl<
      n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

#define JLN_MP_DROP_IMPL(n, _, mp_rxs, mp_rep) \
  template<>                                   \
  struct drop_front_impl<n>                    \
  {                                            \
    template<unsigned size,                    \
      class C,                                 \
      mp_rep(class JLN_MP_COMMA, JLN_MP_NIL)   \
      class... xs>                             \
    using f = typename C::template f<xs...>;   \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_MP_DROP_IMPL)

#undef JLN_MP_DROP_IMPL

#define JLN_MP_DROP_IMPL(n, _, mp_rxs, mp_rep) \
  template<>                                   \
  struct drop_front_impl<n>                    \
  {                                            \
    template<unsigned size,                    \
      class C,                                 \
      mp_rep(class JLN_MP_COMMA, JLN_MP_NIL)   \
      class... xs>                             \
    using f = typename drop_front_impl<size-n> \
      ::template f<size-n, C, xs...>;          \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_DROP_IMPL)

#undef JLN_MP_DROP_IMPL
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int, bool found = false>
    struct _drop_while;

    template<class>
    struct to_drop_upto;

    template<class>
    struct drop_while_impl;

    template<class>
    struct drop_while_extended_by_n_impl;
  }
  /// \endcond

  /// \ingroup search

  /// Remove the first elements of a \sequence that satisfy a \predicate.
  /// When an element does not satisfy the predicate,
  /// call \c TC with it and all those that follow it.
  /// Otherwise \c FC is called on the whole sequence.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_while_xs
  /// \see take_while, take_while_xs
  /// \see search, partial_search
  template<class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_while
  {
    template<class... xs>
    using f = typename detail::drop_while_impl<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  /// Remove the first minus at most \c ExtendedByN elements of a \sequence that satisfy a \predicate.
  /// When an element does not satisfy the predicate,
  /// call \c TC with it and all those that follow it plus at most \c ExtendedByN.
  /// Otherwise \c FC is called on the whole sequence.
  /// \semantics
  ///   \code
  ///   call<drop_while_extended_by_n_c<2, is_not<number<4>>>,
  ///     number<0>, number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   //                         ^ 2        ^ 1       ^ found elem
  ///   ==
  ///   list<number<2>, number<3>, number<4>, number<5>>
  ///
  ///   call<drop_while_extended_by_n_c<2, is_not<number<1>>>,
  ///     number<0>, number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   //   ^ 1       ^ found elem
  ///   ==
  ///   list<number<0>, number<1>>
  ///   \endcode
  /// \treturn \sequence
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_while_extended_by_n_c
  {
    template<class... xs>
    using f = typename detail::drop_while_extended_by_n_impl<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using drop_while_extended_by_n = drop_while_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_inclusive_while = drop_while_extended_by_n_c<1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_while = unpack<L, mp::drop_while<Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
    using drop_while_extended_by_n_c = unpack<L,
      mp::drop_while_extended_by_n_c<ExtendedByN, Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
    using drop_while_extended_by_n = unpack<L,
      mp::drop_while_extended_by_n<ExtendedByN, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_inclusive_while = unpack<L, mp::drop_inclusive_while<Pred, TC, FC>>;
  }

  /// \cond
  template<class Pred, class TC, class FC>
  struct drop_while<Pred, drop_front_c<1, TC>, FC>
  : drop_while_extended_by_n_c<1, Pred, TC, FC>
  {};
  /// \endcond
}



/// \cond
namespace jln::mp::detail
{
  template<std::size_t n>
  struct _drop_while_result
  {
    template<class C, std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_result;
  };

  struct _drop_while_continue
  {
    template<class C, std::size_t consumed, class Pred, class... xs>
    using f = typename C::template f<consumed, Pred, xs...>;
  };


  template<class>
  struct is_drop_while_continue
  {
    using type = false_;
  };

  template<>
  struct is_drop_while_continue<_drop_while_continue>
  {
    using type = true_;
  };


  template<>
  struct drop_while_impl<_drop_while_continue>
  {
    template<class TC, class FC, std::size_t m>
    using f = JLN_MP_TRACE_F(FC);
  };

  template<std::size_t n>
  struct drop_while_impl<_drop_while_result<n>>
  {
    template<class TC, class FC, std::size_t m>
    using f = drop_front_c<m-n-1, TC>;
  };


  template<>
  struct drop_while_extended_by_n_impl<_drop_while_continue>
  {
    template<std::size_t ExtendedByN, class TC, class FC, std::size_t m>
    using f = JLN_MP_TRACE_F(FC);
  };

  template<std::size_t n>
  struct drop_while_extended_by_n_impl<_drop_while_result<n>>
  {
    template<std::size_t ExtendedByN, class TC, class FC, std::size_t m>
    using f = drop_front_c<
      m - (n >= ExtendedByN ? n - ExtendedByN + 1 : 0),
      TC
    >;
  };


  // _drop_while<n, b> = _drop_until<n, !b>

  template<int n>
  struct _drop_while<n, false> : _drop_while<
      n <= 16 ? 16
    : n <= 32 ? 32
    : n <= 64 ? 64
    : n <= 128 ? 128
    : 256,
    false
  >
  {};

  struct drop_while_impl_false
  {
    template<std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_result<consumed+sizeof...(xs)>;
  };

#define JLN_DROP_WHILE_IMPL(n, m)                                    \
  template<>                                                         \
  struct _drop_while<n, false>                                       \
  {                                                                  \
    template<std::size_t consumed, class Pred, class x, class... xs> \
    using f = typename _drop_while<                                  \
      m, JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred::template f<x>::value)     \
    >::template f<consumed, Pred, xs...>;                            \
  };                                                                 \
                                                                     \
  template<>                                                         \
  struct _drop_while<n, true> : drop_while_impl_false               \
  {}

  JLN_DROP_WHILE_IMPL(7, 6);
  JLN_DROP_WHILE_IMPL(6, 5);
  JLN_DROP_WHILE_IMPL(5, 4);
  JLN_DROP_WHILE_IMPL(4, 3);
  JLN_DROP_WHILE_IMPL(3, 2);
  JLN_DROP_WHILE_IMPL(2, 1);
  JLN_DROP_WHILE_IMPL(1, 0);

#undef JLN_DROP_WHILE_IMPL

  template<>
  struct _drop_while<0, false>
  {
    template<std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_continue;
  };

  template<>
  struct _drop_while<0, true>
  {
    template<std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_result<consumed+sizeof...(xs)>;
  };

  template<>
  struct _drop_while<8, false>
  {
    template<
      std::size_t consumed,
      class Pred,
      class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class _8,
      class... xs>
    using f = typename _drop_while<7, JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred::template f<_1>::value)>
      ::template f<
          consumed+sizeof...(xs), Pred,
          _2, _3, _4, _5, _6, _7, _8>;
  };

  template<>
  struct _drop_while<16, false>
  {
    template<
      std::size_t consumed,
      class Pred,
      class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class _8,
      class... xs>
    using f = typename _drop_while<7, JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred::template f<_1>::value)>
      ::template f<
          consumed+sizeof...(xs), Pred,
          _2, _3, _4, _5, _6, _7, _8>
      ::template f<
          _drop_while<sizeof...(xs), false>,
          consumed, Pred, xs...>;
  };

#define JLN_DROP_WHILE_IMPL(n, m, xs)               \
  template<>                                        \
  struct _drop_while<n, false>                      \
  {                                                 \
    template<                                       \
      std::size_t consumed,                         \
      class Pred,                                   \
      xs(class, JLN_MP_NIL, JLN_MP_COMMA),          \
      class... xs>                                  \
    using f = typename _drop_while<m, false>        \
      ::template f<                                 \
          consumed+sizeof...(xs), Pred,             \
          xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)> \
      ::template f<                                 \
          _drop_while<sizeof...(xs), false>,        \
          consumed, Pred, xs...>;                   \
  }

  JLN_DROP_WHILE_IMPL(32, 16, JLN_MP_XS_16);
  JLN_DROP_WHILE_IMPL(64, 32, JLN_MP_XS_32);
  JLN_DROP_WHILE_IMPL(128, 64, JLN_MP_XS_64);
  JLN_DROP_WHILE_IMPL(256, 128, JLN_MP_XS_128);

#undef JLN_DROP_WHILE_IMPL
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int, bool found = false>
    struct _drop_while_xs;

    constexpr int_ partial_drop_while_xs_size(int_ i, int_ size);

    template<int_ Size, class Pred, class... xs>
    using drop_while_xs_call = typename detail::_drop_while_xs<Size>
      ::template f<Size, Pred, xs...>;
  }
  /// \endcond

  /// \ingroup search

  /// Remove the first elements of a \sequence that satisfy a \predicate.
  /// Same as \c drop_while, but the \predicate takes all the elements of
  /// the current position until the end of the list.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_while, partial_drop_while_xs
  /// \see take_while, take_while_xs
  /// \see search
  template<class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_while_xs
  {
    template<class... xs>
    using f = typename detail::drop_while_impl<
      typename detail::_drop_while_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  /// Same as \c drop_while_extended_by_n_c, but for \c drop_while_xs.
  /// \treturn \sequence
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_while_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::drop_while_extended_by_n_impl<
      typename detail::_drop_while_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using drop_while_extended_by_n_xs = drop_while_extended_by_n_xs_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_inclusive_while_xs = drop_while_extended_by_n_xs_c<1, Pred, TC, FC>;

  /// Same as \c drop_while_extended_by_n_xs_c, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_while, drop_while_xs
  /// \see take_while, take_while_xs
  /// \see search, partial_search
  template<int_ OffsetEnd, std::size_t ExtendedByN,
           class Pred, class TC = listify, class FC = clear<TC>>
  struct partial_drop_while_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::drop_while_extended_by_n_impl<
      typename detail::drop_while_xs_call<
        detail::partial_drop_while_xs_size(OffsetEnd, sizeof...(xs)),
        JLN_MP_TRACE_F(Pred), xs...
      >
    >::template f<ExtendedByN, TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_while_xs =
    partial_drop_while_extended_by_n_xs_c<OffsetEnd::value, 0, Pred, TC, FC>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_while_xs_c =
    partial_drop_while_extended_by_n_xs_c<OffsetEnd, 0, Pred, TC, FC>;

  template<class OffsetEnd, class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_while_extended_by_n_xs =
    partial_drop_while_extended_by_n_xs_c<OffsetEnd::value, ExtendedByN::value, Pred, TC, FC>;

  template<std::size_t OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_inclusive_while_xs_c =
    partial_drop_while_extended_by_n_xs_c<OffsetEnd, 1, Pred, TC, FC>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_inclusive_while_xs =
    partial_drop_while_extended_by_n_xs_c<OffsetEnd::value, 1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_while_xs = unpack<L, mp::drop_while_xs<Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_while_extended_by_n_xs = unpack<L,
      mp::drop_while_extended_by_n_xs<ExtendedByN, Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_while_extended_by_n_xs_c = unpack<L,
      mp::drop_while_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_while_xs = unpack<L,
      mp::partial_drop_while_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_while_xs_c = unpack<L,
      mp::partial_drop_while_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_inclusive_while_xs = unpack<L, mp::drop_inclusive_while_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_inclusive_while_xs = unpack<L,
      mp::partial_drop_inclusive_while_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_inclusive_while_xs_c = unpack<L,
      mp::partial_drop_inclusive_while_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class OffsetEnd, class ExtendedByN, class Pred,
             class TC = listify, class FC = mp::clear<TC>>
    using partial_drop_while_extended_by_n_xs = unpack<L,
      mp::partial_drop_while_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, std::size_t ExtendedByN, class Pred,
             class TC = listify, class FC = mp::clear<TC>>
    using partial_drop_while_extended_by_n_xs_c = unpack<L,
      mp::partial_drop_while_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, FC>>;
  }

  /// \cond
  template<class Pred, class TC, class FC>
  struct drop_while_xs<Pred, drop_front_c<1, TC>, FC>
  : drop_while_extended_by_n_xs_c<1, Pred, TC, FC>
  {};
  /// \endcond
}


/// \cond
namespace jln::mp::detail
{
  constexpr int_ partial_drop_while_xs_size(int_ i, int_ size)
  {
    return (i >= size) ? size
         : (i >= 0) ? i
         : (i >= -size) ? size + i + 1
         : 0
         ;
  }

  template<int n>
  struct _drop_while_xs<n, false> : _drop_while_xs<
      n <= 16 ? 16
    : n <= 32 ? 32
    : n <= 64 ? 64
    : n <= 128 ? 128
    : 256,
    false
  >
  {};

  struct drop_while_xs_impl_false
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_result<sizeof...(xs)>;
  };

#define JLN_DROP_WHILE_IMPL(n, m)                                       \
  template<>                                                            \
  struct _drop_while_xs<n, false>                                       \
  {                                                                     \
    template<std::size_t remaining, class Pred, class x, class... xs>   \
    using f = typename _drop_while_xs<                                  \
      m, JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred::template f<x, xs...>::value) \
    >::template f<remaining-1, Pred, xs...>;                            \
  };                                                                    \
                                                                        \
  template<>                                                            \
  struct _drop_while_xs<n, true> : drop_while_xs_impl_false            \
  {}

  JLN_DROP_WHILE_IMPL(7, 6);
  JLN_DROP_WHILE_IMPL(6, 5);
  JLN_DROP_WHILE_IMPL(5, 4);
  JLN_DROP_WHILE_IMPL(4, 3);
  JLN_DROP_WHILE_IMPL(3, 2);
  JLN_DROP_WHILE_IMPL(2, 1);
  JLN_DROP_WHILE_IMPL(1, 0);

#undef JLN_DROP_WHILE_IMPL

  // _drop_while_xs<n, b> is a _search<n, !b>

  template<>
  struct _drop_while_xs<0, false>
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_continue;
  };

  template<>
  struct _drop_while_xs<0, true>
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_result<sizeof...(xs)>;
  };

  template<>
  struct _drop_while_xs<8, false>
  {
    template<std::size_t remaining, class Pred, class x, class... xs>
    using f = typename _drop_while_xs<
      7, JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred::template f<x, xs...>::value)
    >::template f<remaining-8, Pred, xs...>;
  };

  template<>
  struct _drop_while_xs<16, false>
  {
    template<
      std::size_t remaining,
      class Pred,
      class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class _8,
      class... xs>
    using f = typename _drop_while_xs<7, JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred::template f<
        _1, _2, _3, _4, _5, _6, _7, _8, xs...
      >::value)>
      ::template f<7, Pred, _2, _3, _4, _5, _6, _7, _8, xs...>
      ::template f<_drop_while_xs<remaining-8>, remaining-8, Pred, xs...>;
  };

#define JLN_DROP_WHILE_IMPL(n, m, xs)                                        \
  template<>                                                                 \
  struct _drop_while_xs<n, false>                                            \
  {                                                                          \
    template<                                                                \
      std::size_t remaining,                                                 \
      class Pred,                                                            \
      xs(class, JLN_MP_NIL, JLN_MP_COMMA),                                   \
      class... xs>                                                           \
    using f = typename _drop_while_xs<m, false>                              \
      ::template f<m, Pred, xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), xs...> \
      ::template f<_drop_while_xs<remaining-m>, remaining-m, Pred, xs...>;   \
  }

  JLN_DROP_WHILE_IMPL(32, 16, JLN_MP_XS_16);
  JLN_DROP_WHILE_IMPL(64, 32, JLN_MP_XS_32);
  JLN_DROP_WHILE_IMPL(128, 64, JLN_MP_XS_64);
  JLN_DROP_WHILE_IMPL(256, 128, JLN_MP_XS_128);

#undef JLN_DROP_WHILE_IMPL
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int, bool found = true>
    struct _drop_until_xs;

    template<int_ Size, class Pred, class... xs>
    using drop_until_xs_call = typename detail::_drop_until_xs<Size>
      ::template f<Size, Pred, xs...>;
  }
  /// \endcond

  /// \ingroup search

  /// Remove the first elements of a \sequence that does not satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// Same as \c drop_until, but the \predicate takes all the elements of
  /// the current position until the end of the list.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_until, partial_drop_until_xs
  /// \see take_until, take_until_xs
  /// \see search
  template<class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_until_xs
  {
    template<class... xs>
    using f = typename detail::drop_while_impl<
      typename detail::_drop_until_xs<sizeof...(xs)>
        ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  /// Same as \c drop_until_extended_by_n_c, but for \c drop_until_xs.
  /// \treturn \sequence
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_until_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::drop_while_extended_by_n_impl<
      typename detail::_drop_until_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using drop_until_extended_by_n_xs = drop_until_extended_by_n_xs_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_inclusive_until_xs = drop_until_extended_by_n_xs_c<1, Pred, TC, FC>;

  /// Same as \c drop_until_extended_by_n_xs_c, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_until, drop_until_xs
  /// \see take_until, take_until_xs
  /// \see search, partial_search
  template<int_ OffsetEnd, std::size_t ExtendedByN,
           class Pred, class TC = listify, class FC = clear<TC>>
  struct partial_drop_until_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::drop_while_extended_by_n_impl<
      detail::drop_until_xs_call<
        detail::partial_drop_while_xs_size(OffsetEnd, sizeof...(xs)),
        JLN_MP_TRACE_F(Pred), xs...
      >
    >::template f<ExtendedByN, TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_until_xs =
    partial_drop_until_extended_by_n_xs_c<OffsetEnd::value, 0, Pred, TC, FC>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_until_xs_c =
    partial_drop_until_extended_by_n_xs_c<OffsetEnd, 0, Pred, TC, FC>;

  template<class OffsetEnd, class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_until_extended_by_n_xs =
    partial_drop_until_extended_by_n_xs_c<OffsetEnd::value, ExtendedByN::value, Pred, TC, FC>;

  template<std::size_t OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_inclusive_until_xs_c =
    partial_drop_until_extended_by_n_xs_c<OffsetEnd, 1, Pred, TC, FC>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_inclusive_until_xs =
    partial_drop_until_extended_by_n_xs_c<OffsetEnd::value, 1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_until_xs = unpack<L, mp::drop_until_xs<Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_until_extended_by_n_xs = unpack<L,
      mp::drop_until_extended_by_n_xs<ExtendedByN, Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_until_extended_by_n_xs_c = unpack<L,
      mp::drop_until_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_until_xs = unpack<L,
      mp::partial_drop_until_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_until_xs_c = unpack<L,
      mp::partial_drop_until_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_inclusive_until_xs = unpack<L, mp::drop_inclusive_until_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_inclusive_until_xs = unpack<L,
      mp::partial_drop_inclusive_until_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_drop_inclusive_until_xs_c = unpack<L,
      mp::partial_drop_inclusive_until_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class OffsetEnd, class ExtendedByN, class Pred,
             class TC = listify, class FC = mp::clear<TC>>
    using partial_drop_until_extended_by_n_xs = unpack<L,
      mp::partial_drop_until_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, std::size_t ExtendedByN, class Pred,
             class TC = listify, class FC = mp::clear<TC>>
    using partial_drop_until_extended_by_n_xs_c = unpack<L,
      mp::partial_drop_until_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, FC>>;
  }

  /// \cond
  template<class Pred, class TC, class FC>
  struct drop_until_xs<Pred, drop_front_c<1, TC>, FC>
  : drop_until_extended_by_n_xs_c<1, Pred, TC, FC>
  {};
  /// \endcond
}


/// \cond
namespace jln::mp::detail
{
  template<int n>
  struct _drop_until_xs<n, true> : _drop_until_xs<
      n <= 16 ? 16
    : n <= 32 ? 32
    : n <= 64 ? 64
    : n <= 128 ? 128
    : 256,
    true
  >
  {};

  struct drop_until_xs_impl_true
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_result<sizeof...(xs)>;
  };

#define JLN_DROP_WHILE_IMPL(n, m)                                       \
  template<>                                                            \
  struct _drop_until_xs<n, true>                                        \
  {                                                                     \
    template<std::size_t remaining, class Pred, class x, class... xs>   \
    using f = typename _drop_until_xs<                                  \
      m, JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred::template f<x, xs...>::value) \
    >::template f<remaining-1, Pred, xs...>;                            \
  };                                                                    \
                                                                        \
  template<>                                                            \
  struct _drop_until_xs<n, false> : drop_until_xs_impl_true              \
  {}

  JLN_DROP_WHILE_IMPL(7, 6);
  JLN_DROP_WHILE_IMPL(6, 5);
  JLN_DROP_WHILE_IMPL(5, 4);
  JLN_DROP_WHILE_IMPL(4, 3);
  JLN_DROP_WHILE_IMPL(3, 2);
  JLN_DROP_WHILE_IMPL(2, 1);
  JLN_DROP_WHILE_IMPL(1, 0);

#undef JLN_DROP_WHILE_IMPL

  // _drop_until_xs<n, b> is a _search<n, !b>

  template<>
  struct _drop_until_xs<0, true>
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_continue;
  };

  template<>
  struct _drop_until_xs<0, false>
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_result<sizeof...(xs)>;
  };

  template<>
  struct _drop_until_xs<8, true>
  {
    template<std::size_t remaining, class Pred, class x, class... xs>
    using f = typename _drop_until_xs<
      7, JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred::template f<x, xs...>::value)
    >::template f<remaining-8, Pred, xs...>;
  };

  template<>
  struct _drop_until_xs<16, true>
  {
    template<
      std::size_t remaining,
      class Pred,
      class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class _8,
      class... xs>
    using f = typename _drop_until_xs<7, JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred::template f<
        _1, _2, _3, _4, _5, _6, _7, _8, xs...
      >::value)>
      ::template f<7, Pred, _2, _3, _4, _5, _6, _7, _8, xs...>
      ::template f<_drop_until_xs<remaining-8>, remaining-8, Pred, xs...>;
  };

#define JLN_DROP_WHILE_IMPL(n, m, xs)                                        \
  template<>                                                                 \
  struct _drop_until_xs<n, true>                                             \
  {                                                                          \
    template<                                                                \
      std::size_t remaining,                                                 \
      class Pred,                                                            \
      xs(class, JLN_MP_NIL, JLN_MP_COMMA),                                   \
      class... xs>                                                           \
    using f = typename _drop_until_xs<m, true>                               \
      ::template f<m, Pred, xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), xs...> \
      ::template f<_drop_until_xs<remaining-m>, remaining-m, Pred, xs...>;   \
  }

  JLN_DROP_WHILE_IMPL(32, 16, JLN_MP_XS_16);
  JLN_DROP_WHILE_IMPL(64, 32, JLN_MP_XS_32);
  JLN_DROP_WHILE_IMPL(128, 64, JLN_MP_XS_64);
  JLN_DROP_WHILE_IMPL(256, 128, JLN_MP_XS_128);

#undef JLN_DROP_WHILE_IMPL
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned>
    struct take_front_impl;
  }
  /// \endcond

  /// \ingroup list

  /// Extracts \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N <= sizeof...(xs)`
  /// \treturn \sequence
  /// \see take_front_max, take_back, drop_front, drop_back, take_while
  template<unsigned N, class C = listify>
  struct take_front_c
  {
    template<class... xs>
    using f = typename detail::take_front_impl<(sizeof...(xs) & 0) + N>
      ::template f<N, JLN_MP_TRACE_F(C)::template f, xs...>;
  };

  /// Extracts at most \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N`
  /// \treturn \sequence
  /// \see take_front, take_back, take_while
  template<unsigned N, class C = listify>
  struct take_front_max_c
  {
    template<class... xs>
    using f = typename conditional_c<sizeof...(xs) <= N>
      ::template f<JLN_MP_TRACE_F(C), take_front_c<N, C>>
      ::template f<xs...>;
  };

  template<class N, class C = listify>
  using take_front = take_front_c<N::value, C>;

  template<class N, class C = listify>
  using take_front_max = take_front_max_c<N::value, C>;

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using take_front = unpack<L, mp::take_front<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using take_front_c = unpack<L, mp::take_front_c<n, C>>;

    template<class L, class N, class C = mp::listify>
    using take_front_max = unpack<L, mp::take_front_max<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using take_front_max_c = unpack<L, mp::take_front_max_c<n, C>>;
  }


  /// \cond
  #if ! JLN_MP_OPTIMIZED_ALIAS
  template<unsigned N, template<class...> class C>
  struct take_front_c<N, lift<C>>
  {
    template<class... xs>
    using f = typename detail::take_front_impl<(sizeof...(xs) & 0) + N>
      ::template f<N, C, xs...>;
  };
  #endif
  /// \endcond
}


/// \cond
namespace jln::mp::detail
{
  template<unsigned n>
  struct take_front_impl : take_front_impl<
      n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

  template<>
  struct take_front_impl<0>
  {
    template<unsigned size, template<class...> class C, class... xs>
    using f = C<>;
  };

#define JLN_MP_TAKE_IMPL(n, mp_xs, mp_rxs, mp_rep)            \
  template<>                                                  \
  struct take_front_impl<n>                                   \
  {                                                           \
    template<unsigned size, template<class...> class C,       \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)                  \
      class... xs>                                            \
    using f = C<mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>; \
  };

  JLN_MP_GEN_XS_1_TO_16(JLN_MP_TAKE_IMPL)

#undef JLN_MP_TAKE_IMPL

#define JLN_MP_TAKE_IMPL(n, mp_xs, mp_rxs, mp_rep)                      \
  template<>                                                            \
  struct take_front_impl<n>                                             \
  {                                                                     \
    template<unsigned size, template<class...> class C,                 \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)                            \
      class... xs>                                                      \
    using f = typename _join_select<2>::f<C,                            \
      list<mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,                \
      typename take_front_impl<size-n>::template f<size-n, list, xs...> \
    >::type;                                                            \
  };

  JLN_MP_GEN_XS_16_64_256(JLN_MP_TAKE_IMPL)

#undef JLN_MP_TAKE_IMPL
}
/// \endcond

namespace jln::mp
{
  /// \ingroup algorithm

#if JLN_MP_HAS_BUILTIN(__is_same)
#  define JLN_MP_IS_SAME(...) __is_same(__VA_ARGS__)
#else
#  define JLN_MP_IS_SAME(...) ::jln::mp::emp::same_xs_v<__VA_ARGS__>
#endif

  namespace emp
  {
    template<class... xs>
    inline constexpr bool same_xs_v = true;

    template<class x>
    inline constexpr bool same_xs_v<x, x> = true;

    template<class x, class y>
    inline constexpr bool same_xs_v<x, y> = false;

    template<class x, class y, class z, class... xs>
    inline constexpr bool same_xs_v<x, y, z, xs...> =
#if JLN_MP_HAS_BUILTIN(__is_same)
      __is_same(list<x, y, z, xs...>, list<y, z, xs..., x>)
#else
      same_xs_v<list<x, y, z, xs...>, list<y, z, xs..., x>>
#endif
    ;
  }
}

namespace jln::mp
{
  /// \ingroup utility

  /// \treturn \bool
  template<class T, class C = identity>
  struct is
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_IS_SAME(T, x)>);
  };

  /// \cond
  template<class T>
  struct is<T, identity>
  {
    template<class x>
    using f = number<JLN_MP_IS_SAME(T, x)>;
  };
  /// \endcond
  /// \cond
  namespace detail
  {
    template<class>
    struct take_while_impl;

    template<class>
    struct take_while_extended_by_n_impl;
  }
  /// \endcond

  /// \ingroup search

  /// Extract the first elements of a \sequence that satisfy a \predicate.
  /// When an element does not satisfy the predicate,
  /// call \c TC with it and those before it.
  /// Otherwise \c FC is called on the whole sequence.
  /// \treturn \sequence
  /// \see take_front, take_back, take_while_xs
  /// \see drop_while, drop_while_xs
  /// \see search, partial_search
  template<class Pred, class TC = listify, class FC = TC>
  struct take_while
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  /// Extract the first plus at most \c ExtendedByN elements of a \sequence that satisfy a \predicate.
  /// When an element satisfy the predicate,
  /// call \c TC with it and those before it plus at most \c ExtendedByN.
  /// Otherwise \c FC is called on the whole sequence.
  /// \semantics
  ///   \code
  ///   call<take_while_extended_by_n_c<2, is_not<number<2>>>,
  ///     number<0>, number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   //  predicate not satisfied ^ (+1)   ^ +2
  ///   ==
  ///   list<number<0>, number<1>, number<2>, number<3>>
  ///
  ///   call<take_while_extended_by_n_c<2, is_not<number<5>>>,
  ///     number<0>, number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   //                                   predicate not satisfied ^ (+1)
  ///   ==
  ///   list<number<0>, number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   \endcode
  /// \treturn \sequence
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  struct take_while_extended_by_n_c
  {
    template<class... xs>
    using f = typename detail::take_while_extended_by_n_impl<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using take_while_extended_by_n = take_while_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_inclusive_while = take_while_extended_by_n_c<1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_while = unpack<L, mp::take_while<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_inclusive_while = unpack<L, mp::take_while_extended_by_n_c<1, Pred, TC, FC>>;

    template<class ExtendedByN, class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_while_extended_by_n
      = unpack<L, mp::take_while_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>>;

    template<std::size_t ExtendedByN,
             class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_while_extended_by_n_c
      = unpack<L, mp::take_while_extended_by_n_c<ExtendedByN, Pred, TC, FC>>;
  }
}



/// \cond
namespace jln::mp::detail
{
  template<>
  struct take_while_impl<_drop_while_continue>
    : drop_while_impl<_drop_while_continue>
  {};

  template<std::size_t n>
  struct take_while_impl<_drop_while_result<n>>
  {
    template<class TC, class FC, std::size_t m>
    using f = take_front_c<m-n-1, TC>;
  };


  template<>
  struct take_while_extended_by_n_impl<_drop_while_continue>
    : drop_while_extended_by_n_impl<_drop_while_continue>
  {};

  template<std::size_t n>
  struct take_while_extended_by_n_impl<_drop_while_result<n>>
  {
    template<std::size_t ExtendedByN, class TC, class FC, std::size_t m>
    using f = take_front_c<m - (n >= ExtendedByN ? n - ExtendedByN + 1 : 0), TC>;
  };
}
/// \encond

namespace jln::mp
{
  /// \ingroup search

  /// Extracts the first elements of a \sequence that satisfy a \predicate.
  /// \treturn \sequence
  /// \see take_front, take_back, take_while, partial_take_while_xs
  /// \see drop_while, drop_while_xs
  /// \see search
  template<class Pred, class TC = listify, class FC = TC>
  struct take_while_xs
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::_drop_while_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  /// Same as \c take_while_extended_by_n_c, but for \c take_while_xs.
  /// \treturn \sequence
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  struct take_while_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::take_while_extended_by_n_impl<
      typename detail::_drop_while_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using take_while_extended_by_n_xs = take_while_extended_by_n_xs_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_inclusive_while_xs = take_while_extended_by_n_xs_c<1, Pred, TC, FC>;

  /// Same as \c take_while_extended_by_n_xs_c, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_while, drop_while_xs
  /// \see take_while, take_while_xs
  /// \see search, partial_search
  template<int_ OffsetEnd, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  struct partial_take_while_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::take_while_extended_by_n_impl<
      typename detail::drop_while_xs_call<
        detail::partial_drop_while_xs_size(OffsetEnd, sizeof...(xs)),
        JLN_MP_TRACE_F(Pred), xs...
      >
    >::template f<ExtendedByN, TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_while_xs =
    partial_take_while_extended_by_n_xs_c<OffsetEnd::value, 0, Pred, TC, FC>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_while_xs_c =
    partial_take_while_extended_by_n_xs_c<OffsetEnd, 0, Pred, TC, FC>;

  template<class OffsetEnd, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_take_while_extended_by_n_xs =
    partial_take_while_extended_by_n_xs_c<OffsetEnd::value, ExtendedByN::value, Pred, TC, FC>;

  template<std::size_t OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_inclusive_while_xs_c =
    partial_take_while_extended_by_n_xs_c<OffsetEnd, 1, Pred, TC, FC>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_inclusive_while_xs =
    partial_take_while_extended_by_n_xs_c<OffsetEnd::value, 1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using take_while_xs = unpack<L, mp::take_while_xs<Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred, class TC = mp::listify, class FC = TC>
    using take_while_extended_by_n_xs = unpack<L,
      mp::take_while_extended_by_n_xs<ExtendedByN, Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = mp::listify, class FC = TC>
    using take_while_extended_by_n_xs_c = unpack<L,
      mp::take_while_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred, class TC = mp::listify, class FC = TC>
    using partial_take_while_xs = unpack<L,
      mp::partial_take_while_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred, class TC = mp::listify, class FC = TC>
    using partial_take_while_xs_c = unpack<L,
      mp::partial_take_while_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using take_inclusive_while_xs = unpack<L, mp::take_inclusive_while_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred,
             class TC = mp::listify, class FC = TC>
    using partial_take_inclusive_while_xs = unpack<L,
      mp::partial_take_inclusive_while_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred,
             class TC = mp::listify, class FC = TC>
    using partial_take_inclusive_while_xs_c = unpack<L,
      mp::partial_take_inclusive_while_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class OffsetEnd, class ExtendedByN, class Pred,
             class TC = listify, class FC = TC>
    using partial_take_while_extended_by_n_xs = unpack<L,
      mp::partial_take_while_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, std::size_t ExtendedByN, class Pred,
             class TC = listify, class FC = TC>
    using partial_take_while_extended_by_n_xs_c = unpack<L,
      mp::partial_take_while_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, FC>>;
  }
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int, bool not_found = true>
    struct _drop_until;
  }
  /// \endcond

  /// \ingroup search

  /// Remove the first elements of a \sequence that does not satisfy a \predicate.
  /// When an element satisfy the predicate,
  /// call \c TC with it and those that follow it.
  /// Otherwise \c FC is called on the whole sequence.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_until_xs
  /// \see take_until, take_until_xs
  /// \see search, partial_search
  template<class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_until
  {
    template<class... xs>
    using f = typename detail::drop_while_impl<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  /// Remove the first minus at most \c ExtendedByN elements of a \sequence that does not satisfy a \predicate.
  /// When an element satisfy the predicate,
  /// call \c TC with it and those that follow it plus at most \c ExtendedByN.
  /// Otherwise \c FC is called on the whole sequence.
  /// \semantics
  ///   \code
  ///   call<drop_while_extended_by_n_c<2, is<number<4>>>,
  ///     number<0>, number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   //                        ^ -2       ^ -1       ^ found elem
  ///   ==
  ///   list<number<2>, number<3>, number<4>, number<5>>
  ///
  ///   call<drop_while_extended_by_n_c<2, is<number<1>>>,
  ///     number<0>, number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   //  ^ -1       ^ found elem
  ///   ==
  ///   list<number<0>, number<1>>
  ///   \endcode
  /// \treturn \sequence
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  struct drop_until_extended_by_n_c
  {
    template<class... xs>
    using f = typename detail::drop_while_extended_by_n_impl<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using drop_until_extended_by_n = drop_until_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_inclusive_until = drop_until_extended_by_n_c<1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using drop_until = unpack<L, mp::drop_until<Pred, C>>;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
    using drop_until_extended_by_n_c = unpack<L,
      mp::drop_until_extended_by_n_c<ExtendedByN, Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
    using drop_until_extended_by_n = unpack<L,
      mp::drop_until_extended_by_n<ExtendedByN, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using drop_inclusive_until = unpack<L, mp::drop_inclusive_until<Pred, TC, FC>>;
  }

  /// \cond
  template<class Pred, class TC, class FC>
  struct drop_until<Pred, drop_front_c<1, TC>, FC>
  : drop_until_extended_by_n_c<1, Pred, TC, FC>
  {};
  /// \endcond
}



/// \cond
namespace jln::mp::detail
{
  // _drop_until<n, b> = _drop_while<n, !b>

  template<int n>
  struct _drop_until<n, true> : _drop_until<
      n <= 16 ? 16
    : n <= 32 ? 32
    : n <= 64 ? 64
    : n <= 128 ? 128
    : 256,
    true
  >
  {};

  struct drop_until_impl_true
  {
    template<std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_result<consumed+sizeof...(xs)>;
  };

#define JLN_DROP_WHILE_IMPL(n, m)                                    \
  template<>                                                         \
  struct _drop_until<n, true>                                        \
  {                                                                  \
    template<std::size_t consumed, class Pred, class x, class... xs> \
    using f = typename _drop_until<                                  \
      m, JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred::template f<x>::value)     \
    >::template f<consumed, Pred, xs...>;                            \
  };                                                                 \
                                                                     \
  template<>                                                         \
  struct _drop_until<n, false> : drop_until_impl_true                \
  {}

  JLN_DROP_WHILE_IMPL(7, 6);
  JLN_DROP_WHILE_IMPL(6, 5);
  JLN_DROP_WHILE_IMPL(5, 4);
  JLN_DROP_WHILE_IMPL(4, 3);
  JLN_DROP_WHILE_IMPL(3, 2);
  JLN_DROP_WHILE_IMPL(2, 1);
  JLN_DROP_WHILE_IMPL(1, 0);

#undef JLN_DROP_WHILE_IMPL

  template<>
  struct _drop_until<0, true>
  {
    template<std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_continue;
  };

  template<>
  struct _drop_until<0, false>
  {
    template<std::size_t consumed, class Pred, class... xs>
    using f = _drop_while_result<consumed+sizeof...(xs)>;
  };

  template<>
  struct _drop_until<8, true>
  {
    template<
      std::size_t consumed,
      class Pred,
      class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class _8,
      class... xs>
    using f = typename _drop_until<7, JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred::template f<_1>::value)>
      ::template f<
          consumed+sizeof...(xs), Pred,
          _2, _3, _4, _5, _6, _7, _8>;
  };

  template<>
  struct _drop_until<16, true>
  {
    template<
      std::size_t consumed,
      class Pred,
      class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class _8,
      class... xs>
    using f = typename _drop_until<7, JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred::template f<_1>::value)>
      ::template f<
          consumed+sizeof...(xs), Pred,
          _2, _3, _4, _5, _6, _7, _8>
      ::template f<
          _drop_until<sizeof...(xs), true>,
          consumed, Pred, xs...>;
  };

#define JLN_DROP_WHILE_IMPL(n, m, xs)               \
  template<>                                        \
  struct _drop_until<n, true>                       \
  {                                                 \
    template<                                       \
      std::size_t consumed,                         \
      class Pred,                                   \
      xs(class, JLN_MP_NIL, JLN_MP_COMMA),          \
      class... xs>                                  \
    using f = typename _drop_until<m, true>         \
      ::template f<                                 \
          consumed+sizeof...(xs), Pred,             \
          xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)> \
      ::template f<                                 \
          _drop_until<sizeof...(xs), true>,         \
          consumed, Pred, xs...>;                   \
  }

  JLN_DROP_WHILE_IMPL(32, 16, JLN_MP_XS_16);
  JLN_DROP_WHILE_IMPL(64, 32, JLN_MP_XS_32);
  JLN_DROP_WHILE_IMPL(128, 64, JLN_MP_XS_64);
  JLN_DROP_WHILE_IMPL(256, 128, JLN_MP_XS_128);

#undef JLN_DROP_WHILE_IMPL
}
/// \endcond

namespace jln::mp
{
  /// \ingroup list

  /// Returns the number of elements in a \c xs.
  /// \treturn \number
  template<class C = identity>
  struct size
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<sizeof...(xs)>);
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using size = unpack<L, mp::size<C>>;
  }

  /// \cond
  template<>
  struct size<identity>
  {
    template<class... xs>
    using f = number<sizeof...(xs)>;
  };

  template<int_ i>
  struct size<is<number<i>>>
  {
    template<class... xs>
    using f = number<sizeof...(xs) == i>;
  };

  template<int_ i, class C>
  struct size<is<number<i>, C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<sizeof...(xs) == i>);
  };
  /// \endcond
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct index_if_impl;
  }
  /// \endcond

  /// \ingroup search

  /// Finds the index of the first element of \sequence
  /// that satisfies the \predicate \c Pred.
  /// Calls \c TC with the index found or \c FC with the whole \sequence.
  /// \treturn \number
  template<class Pred, class TC = identity, class FC = size<>>
  struct index_if
  {
    template<class... xs>
    using f = typename detail::index_if_impl<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  /// Finds the index of the first element of \sequence that is a type \c T.
  /// Calls \c TC with the index found or \c FC with the whole \sequence.
  /// \treturn \number
  template<class T, class TC = identity, class FC = size<>>
  using index_of = index_if<is<T>, TC, FC>;

  /// Search the index of first sub-\sequence that satisfy a \predicate.
  /// \treturn \sequence
  template<class Pred, class TC = identity, class FC = size<>>
  struct index_if_xs
  {
    template<class... xs>
    using f = typename detail::index_if_impl<
      typename detail::_drop_until_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  /// Same as \c index_if_xs, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  template<int_ OffsetEnd, class Pred, class TC = identity, class FC = size<>>
  struct partial_index_if_xs_c
  {
    template<class... xs>
    using f = typename detail::index_if_impl<
      detail::drop_until_xs_call<
        detail::partial_drop_while_xs_size(OffsetEnd, sizeof...(xs)),
        JLN_MP_TRACE_F(Pred), xs...
      >
    >::template f<TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class OffsetEnd, class Pred, class TC = identity, class FC = size<>>
  using partial_index_if_xs = partial_index_if_xs_c<OffsetEnd::value, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::identity, class FC = mp::size<>>
    using index_if = unpack<L, mp::index_if<Pred, TC, FC>>;

    template<class L, class T, class TC = mp::identity, class FC = mp::size<>>
    using index_of = unpack<L, mp::index_of<T, TC, FC>>;

    template<class L, class Pred, class TC = mp::identity, class FC = mp::size<>>
    using index_if_xs = unpack<L, mp::index_if_xs<Pred, TC, FC>>;

    template<class OffsetEnd, class L, class Pred, class TC = mp::identity, class FC = mp::size<>>
    using partial_index_if_xs = unpack<L, mp::partial_index_if_xs<OffsetEnd, Pred, TC, FC>>;

    template<int_ OffsetEnd, class L, class Pred, class TC = mp::identity, class FC = mp::size<>>
    using partial_index_if_xs_c = unpack<L, mp::partial_index_if_xs_c<OffsetEnd, Pred, TC, FC>>;
  }
}



/// \cond
namespace jln::mp::detail
{
  template<>
  struct index_if_impl<_drop_while_continue>
    : drop_while_impl<_drop_while_continue>
  {};

  template<std::size_t n>
  struct index_if_impl<_drop_while_result<n>>
  {
    template<class TC, class FC, std::size_t m>
    using f = always<JLN_MP_CALL_TRACE(TC, number<m-n-1>)>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether all \values are identical.
  /// \treturn \bool
  template<class C = identity>
  struct same
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<emp::same_xs_v<xs...>>);
  };

  template<class C = identity>
  struct same_v
  {
    template<class... xs>
    using f = typename C::template f<emp::same_xs_v<xs...>>;
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using same = unpack<L, mp::same<C>>;

    template<class L, class C = mp::identity>
    inline constexpr bool same_v = unpack<L, mp::same<C>>::value;
  }
}


/// \cond
namespace jln::mp
{
  template<>
  struct same<identity>
  {
    template<class... xs>
    using f = number<emp::same_xs_v<xs...>>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup functional

  /// A conditional expression.
  /// \treturn \value
  template<class Pred, class TC, class FC = always<false_>>
  struct if_
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, xs...)::value)
    >
      ::template f<JLN_MP_TRACE_F(FC), JLN_MP_TRACE_F(TC)>
      ::template f<xs...>;
  };

  namespace emp
  {
    template<class Pred, class TC, class FC, class... xs>
    using if_ = typename mp::if_<Pred, TC, FC>::template f<xs...>;
  }
}

/// \cond

namespace jln::mp
{
  template<class TC, class FC>
  struct if_<size<>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs))>
      ::template f<JLN_MP_TRACE_F(FC), JLN_MP_TRACE_F(TC)>
      ::template f<xs...>;
  };

  template<int_ i, class TC, class FC>
  struct if_<size<is<number<i>>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<sizeof...(xs) == i>
      ::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
      ::template f<xs...>;
  };

  template<class TC, class FC>
  struct if_<same<>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<emp::same_xs_v<xs...>>
      ::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
      ::template f<xs...>;
  };

  template<class C, class TC, class FC>
  struct if_<same<C>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      JLN_MP_TRACE_F(C)::template f<number<emp::same_xs_v<xs...>>>::value
    >
      ::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
      ::template f<xs...>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct starts_with_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks if the \sequence begins with the given prefix.
  /// \treturn \bool
  /// \see ends_with
  template<class Seq, class C = identity>
  struct starts_with
  {};

  template<class... Ts, class C>
  struct starts_with<list<Ts...>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::starts_with_impl<sizeof...(Ts) <= sizeof...(xs)>
      ::template f<sizeof...(Ts), list<Ts...>, xs...>
    );
  };

  namespace emp
  {
    template<class L, class Seq, class C = mp::identity>
    using starts_with = unpack<starts_with<Seq, C>, L>;
  }

  /// \cond
  template<class... Ts>
  struct starts_with<list<Ts...>, identity>
  {
    template<class... xs>
    using f = typename detail::starts_with_impl<sizeof...(Ts) <= sizeof...(xs)>
      ::template f<sizeof...(Ts), list<Ts...>, xs...>;
  };

  namespace detail
  {
    class dummy;

    template<bool>
    struct starts_with1_impl;
  }

  template<class T, class C>
  struct starts_with<list<T>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::starts_with1_impl<1 <= sizeof...(xs)>
      ::template f<T, xs..., detail::dummy>
    );
  };

  template<class T>
  struct starts_with<list<T>, identity>
  {
    template<class... xs>
    using f = typename detail::starts_with1_impl<1 <= sizeof...(xs)>
      ::template f<T, xs..., detail::dummy>;
  };

  template<class C>
  struct starts_with<list<>, C>
  {
    template<class... xs>
    using f = JLN_MP_FORCE_DCALL_TRACE_XS(xs, C, true_);
  };

  template<>
  struct starts_with<list<>, identity> : always<true_>
  {};
  /// \endcond
}

/// \cond


namespace jln::mp::detail
{
  template<>
  struct starts_with_impl<true>
  {
    template<unsigned n, class L, class... xs>
    using f = number<JLN_MP_IS_SAME(
      typename take_front_c<n>::template f<xs...>,
      L
    )>;
  };

  template<>
  struct starts_with_impl<false>
  {
    template<unsigned n, class L, class... xs>
    using f = false_;
  };

  template<>
  struct starts_with1_impl<true>
  {
    template<class T, class x, class... xs>
    using f = number<JLN_MP_IS_SAME(T, x)>;
  };

  template<>
  struct starts_with1_impl<false> : always<false_>
  {};
}

namespace jln::mp::detail
{
  template<class C>
  struct optimized_starts_with_empty
  {
    using type = if_<size<>, always<true_, C>>;
  };

  template<>
  struct optimized_starts_with_empty<identity>
  {
    using type = size<>;
  };


  template<int_>
  struct optimized_index_if_xs_starts_with;

  template<>
  struct optimized_index_if_xs_starts_with<0>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = if_<typename optimized_starts_with_empty<C>::type, always<number<0>, TC>, FC>;
  };

  template<>
  struct optimized_index_if_xs_starts_with<1>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = index_if<is<Ts..., C>, TC, FC>;
  };

  template<>
  struct optimized_index_if_xs_starts_with<2>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = partial_index_if_xs_c<-int_(sizeof...(Ts)),
      starts_with<list<Ts...>, C>, TC, FC>;
  };
}

namespace jln::mp
{
  // optimize index_if_xs with starts_with
  template<class... Ts, class C, class TC, class FC>
  struct index_if_xs<starts_with<list<Ts...>, C>, TC, FC>
  : detail::optimized_index_if_xs_starts_with<sizeof...(Ts) < 2 ? sizeof...(Ts) : 2>
    ::template f<C, TC, FC, Ts...>
  {};
}

namespace jln::mp::detail
{
  template<int_>
  struct optimized_drop_while_starts_with;

  template<>
  struct optimized_drop_while_starts_with<0>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = if_<typename optimized_starts_with_empty<C>::type, clear<TC>, FC>;
  };

  template<>
  struct optimized_drop_while_starts_with<1>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = drop_while<is<Ts..., C>, TC, FC>;
  };

  template<>
  struct optimized_drop_while_starts_with<2>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = partial_drop_while_xs_c<-int_(sizeof...(Ts)),
      starts_with<list<Ts...>, C>, TC, FC>;
  };
}

namespace jln::mp
{
  template<class... Ts, class C, class TC, class FC>
  struct drop_while_xs<starts_with<list<Ts...>, C>, TC, FC>
  : detail::optimized_drop_while_starts_with<sizeof...(Ts) < 2 ? sizeof...(Ts) : 2>
    ::template f<C, TC, FC, Ts...>
  {};
}

namespace jln::mp::detail
{
  template<int_>
  struct optimized_take_while_starts_with;

  template<>
  struct optimized_take_while_starts_with<0>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = if_<typename optimized_starts_with_empty<C>::type, TC, FC>;
  };

  template<>
  struct optimized_take_while_starts_with<1>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = take_while<is<Ts..., C>, TC, FC>;
  };

  template<>
  struct optimized_take_while_starts_with<2>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = partial_take_while_xs_c<-int_(sizeof...(Ts)),
      starts_with<list<Ts...>, C>, TC, FC>;
  };
}

namespace jln::mp
{
  template<class... Ts, class C, class TC, class FC>
  struct take_while_xs<starts_with<list<Ts...>, C>, TC, FC>
  : detail::optimized_take_while_starts_with<sizeof...(Ts) < 2 ? sizeof...(Ts) : 2>
    ::template f<C, TC, FC, Ts...>
  {};
}

namespace jln::mp::detail
{
  template<int_>
  struct optimized_take_while_extended_by_n_starts_with;

  template<>
  struct optimized_take_while_extended_by_n_starts_with<0>
  {
    template<std::size_t ExtendedByN, class C, class TC, class FC, class... Ts>
    using f = if_<typename optimized_starts_with_empty<C>::type, TC, FC>;
  };

  template<>
  struct optimized_take_while_extended_by_n_starts_with<1>
  {
    template<std::size_t ExtendedByN, class C, class TC, class FC, class... Ts>
    using f = take_while_extended_by_n_c<ExtendedByN, is<Ts..., C>, TC, FC>;
  };

  template<>
  struct optimized_take_while_extended_by_n_starts_with<2>
  {
    template<std::size_t ExtendedByN, class C, class TC, class FC, class... Ts>
    using f = partial_take_while_extended_by_n_xs_c<
      -int_(sizeof...(Ts)), ExtendedByN, starts_with<list<Ts...>, C>, TC, FC
    >;
  };
}

namespace jln::mp
{
  template<std::size_t ExtendedByN, class... Ts, class C, class TC, class FC>
  struct take_while_extended_by_n_xs_c<ExtendedByN, starts_with<list<Ts...>, C>, TC, FC>
  : detail::optimized_take_while_extended_by_n_starts_with<sizeof...(Ts) < 2 ? sizeof...(Ts) : 2>
    ::template f<C, TC, FC, Ts...>
  {};
}
/// \endcond

namespace jln::mp
{
  /// \ingroup search

  /// Find the \sequence after a sub-\sequence.
  /// Calls \c TC with all the elements after the sub-\sequence found.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search, search_before
  template<class Seq, class TC = listify, class FC = clear<TC>>
  struct after
  {};

  template<class... Ts, class TC, class FC>
  struct after<list<Ts...>, TC, FC>
  : partial_drop_until_extended_by_n_xs_c<-int_(sizeof...(Ts)),
                                          sizeof...(Ts),
                                          starts_with<list<Ts...>>,
                                          TC, FC>
  {};

  namespace emp
  {
    template<class L, class Seq, class TC = mp::listify, class FC = mp::clear<TC>>
    using after = unpack<L, mp::after<Seq, TC, FC>>;
  }

  /// \cond
  template<class T, class TC, class FC>
  struct after<list<T>, TC, FC>
  : drop_until_extended_by_n_c<1, is<T>, TC, FC>
  {};

  template<class TC, class FC>
  struct after<list<>, TC, FC>
  : detail::call_trace_xs<TC>
  {};
  /// \endcond
}

// fix narrowing based on type:
//
// template<int>
// struct X {};
//
// template<class... T>
// struct A : X<int{sizeof...(T)}> // narrowing error with msvc 19.38
// {};

#if JLN_MP_MSVC
namespace jln::mp::detail
{
  template<bool is_neg>
  struct integral_as_impl;

  struct integral_conversion_error
  {};

  template<>
  struct integral_as_impl<true>
  {
    template<long long n>
    using as_bool = integral_conversion_error;

    template<long long n>
    struct as_int_ : number<n>
    {};

    template<long long n>
    using as_uint_ = integral_conversion_error;
  };

  template<>
  struct integral_as_impl<false>
  {
    template<unsigned long long n, bool = n <= 1>
    struct as_bool : number<n>
    {};

    template<unsigned long long n>
    struct as_bool<n, false>
    {};


    template<unsigned long long n, bool = n <= (~0ull >> 1)>
    struct as_int_ : number<n>
    {};

    template<unsigned long long n>
    struct as_int_<n, false>
    {};


    template<unsigned long long n>
    struct as_uint_ : number<n>
    {};
  };
}
#  define JLN_MP_INTEGRAL_AS(T, ...) \
  ::jln::mp::detail::integral_as_impl<__VA_ARGS__ < 0>::template as_##T<__VA_ARGS__>::value
#else
#  define JLN_MP_INTEGRAL_AS(T, ...) T{__VA_ARGS__}
#endif


namespace jln::mp
{
  /// \ingroup number

#if JLN_MP_CUDA
#  define JLN_MP_AS_BOOL(v) std::enable_if_t<std::size_t{v} <= 1, bool>{v}
#else
#  define JLN_MP_AS_BOOL(v) JLN_MP_INTEGRAL_AS(bool, v)
#endif

  /// Convertion without narrowing from \value to \bool.
  /// \treturn \bool
  template<class C = identity>
  struct as_bool
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_AS_BOOL(x::value)>);
  };

  namespace emp
  {
    template<class x>
    using as_bool = number<JLN_MP_AS_BOOL(x::value)>;
  }

  /// \cond
  template<>
  struct as_bool<identity>
  {
    template<class x>
    using f = number<JLN_MP_AS_BOOL(x::value)>;
  };
  /// \endcond

#undef JLN_MP_AS_BOOL
}

namespace jln::mp
{
  /// \ingroup number

  /// Converts a \value to a \bool.
  /// \treturn \bool
  template<class C = identity>
  struct to_bool
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_RAW_EXPR_TO_BOOL(x::value)>);
  };

  namespace emp
  {
    template<class x>
    using to_bool = number<JLN_MP_RAW_EXPR_TO_BOOL(x::value)>;
  }

  /// \cond
  template<>
  struct to_bool<identity>
  {
    template<class x>
    using f = number<JLN_MP_RAW_EXPR_TO_BOOL(x::value)>;
  };
  /// \endcond
}

namespace jln::mp
{
  /// \ingroup number

  template<class C = identity>
  struct not_
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_RAW_EXPR_TO_BOOL_NOT(x::value)>);
  };

  template<class C>
  struct not_<not_<C>>
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_RAW_EXPR_TO_BOOL(x::value)>);
  };

  namespace emp
  {
    template<class x, class C = mp::identity>
    using not_ = typename mp::not_<C>::template f<x>;
  }
}

/// \cond


namespace jln::mp
{
  template<>
  struct not_<identity>
  {
    template<class x>
    using f = number<JLN_MP_RAW_EXPR_TO_BOOL_NOT(x::value)>;
  };

  template<>
  struct not_<not_<identity>>
  {
    template<class x>
    using f = number<JLN_MP_RAW_EXPR_TO_BOOL(x::value)>;
  };

#if JLN_MP_CUDA
#  define JLN_MP_AS_BOOL(v) std::enable_if_t<std::size_t{v} <= 1, bool>{v}
#else
#  define JLN_MP_AS_BOOL(v) JLN_MP_INTEGRAL_AS(bool, v)
#endif

  template<>
  struct as_bool<not_<>>
  {
    template<class x>
    using f = number<!JLN_MP_AS_BOOL(x::value)>;
  };

  template<class C>
  struct as_bool<not_<C>>
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<!JLN_MP_AS_BOOL(x::value)>);
  };

#undef JLN_MP_AS_BOOL

  template<>
  struct to_bool<not_<>>
  {
    template<class x>
    using f = number<JLN_MP_RAW_EXPR_TO_BOOL_NOT(x::value)>;
  };

  template<class C>
  struct to_bool<not_<C>>
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_RAW_EXPR_TO_BOOL_NOT(x::value)>);
  };

  template<class T, class C>
  struct is<T, not_<C>>
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<!JLN_MP_IS_SAME(T, x)>);
  };

  template<class T>
  struct is<T, not_<>>
  {
    template<class x>
    using f = number<!JLN_MP_IS_SAME(T, x)>;
  };

  template<class C>
  struct same<not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      number<JLN_MP_RAW_EXPR_TO_BOOL_NOT(emp::same_xs_v<xs...>)>
    );
  };

  template<>
  struct same<not_<>>
  {
    template<class... xs>
    using f = number<JLN_MP_RAW_EXPR_TO_BOOL_NOT(emp::same_xs_v<xs...>)>;
  };

  template<class C>
  struct size<not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<!sizeof...(xs)>);
  };

  template<>
  struct size<not_<>>
  {
    template<class... xs>
    using f = number<!sizeof...(xs)>;
  };

  template<int_ i, class C>
  struct size<is<number<i>, not_<C>>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<sizeof...(xs) != i>);
  };

  template<int_ i>
  struct size<is<number<i>, not_<>>>
  {
    template<class... xs>
    using f = number<sizeof...(xs) != i>;
  };

  template<class TC, class FC>
  struct if_<size<not_<>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<!sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
      ::template f<xs...>;
  };

  template<int_ i, class TC, class FC>
  struct if_<size<is<number<i>, not_<>>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<sizeof...(xs) != i>
      ::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
      ::template f<xs...>;
  };

  template<class C, class TC, class FC>
  struct if_<same<not_<C>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      JLN_MP_TRACE_F(C)::template f<number<
        JLN_MP_RAW_EXPR_TO_BOOL_NOT(emp::same_xs_v<xs...>)
      >>::value
    >
      ::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
      ::template f<xs...>;
  };

  template<class TC, class FC>
  struct if_<same<not_<>>, TC, FC> : if_<same<>, FC, TC>
  {};

  template<class x, class TC, class FC>
  struct if_<is<x, not_<>>, TC, FC> : if_<is<x>, FC, TC>
  {};
}

/// \endcond

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a predicate holds for all elements of a \sequence.
  /// \treturn \bool
  /// \see any_of, none_of
  template<class Pred, class C = identity>
  struct all_of
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(
      C,
      typename detail::is_drop_while_continue<
        typename detail::_drop_while<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type
    );
  };

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using all_of = unpack<L, mp::all_of<Pred, C>>;
  }
} // namespace jln::mp


/// \cond
namespace jln::mp
{
  template<class Pred>
  struct all_of<Pred>
  {
    template<class... xs>
    using f = typename detail::is_drop_while_continue<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::type;
  };

  template<class Pred>
  struct all_of<Pred, not_<>>
  {
    template<class... xs>
    using f = number<!detail::is_drop_while_continue<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::type::value>;
  };

  template<class Pred, class C>
  struct all_of<Pred, not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(
      C,
      number<!detail::is_drop_while_continue<
        typename detail::_drop_while<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type::value>
    );
  };

  template<class Pred, class TC, class FC>
  struct if_<all_of<Pred>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      detail::is_drop_while_continue<
        typename detail::_drop_while<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type::value
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };

  template<class Pred, class TC, class FC>
  struct if_<all_of<Pred, not_<>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      !detail::is_drop_while_continue<
        typename detail::_drop_while<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type::value
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };
} // namespace jln::mp
/// \endcond

namespace jln::mp
{
  /// \ingroup number

  template<class C = listify>
  struct numbers
  {
    template<int_... ns>
    using f = JLN_MP_DCALL_TRACE_XS(ns, C, number<ns>...);
  };

  /// \cond
  template<>
  struct numbers<listify>
  {
    template<int_... ns>
    using f = list<number<ns>...>;
  };
  /// \endcond

  namespace emp
  {
    template<int_... vs>
    using numbers = list<number<vs>...>;
  }
}

#ifdef JLN_MP_DISABLE_INTEGER_SEQUENCE_OPTIMIZATION
#  define JLN_MP_USE_INTEGER_PACK 0
#  define JLN_MP_USE_MAKE_INTEGER_SEQ 0
#elif JLN_MP_HAS_BUILTIN(__make_integer_seq) || defined(_MSC_VER)
#  define JLN_MP_USE_INTEGER_PACK 0
#  define JLN_MP_USE_MAKE_INTEGER_SEQ 1
#elif JLN_MP_HAS_BUILTIN(__integer_pack) || JLN_MP_GCC >= 800
#  define JLN_MP_USE_INTEGER_PACK 1
#  define JLN_MP_USE_MAKE_INTEGER_SEQ 0
#else
#  define JLN_MP_USE_INTEGER_PACK 0
#  define JLN_MP_USE_MAKE_INTEGER_SEQ 0
#endif



namespace jln::mp
{
  /// \cond
  namespace detail
  {
#if JLN_MP_USE_MAKE_INTEGER_SEQ || JLN_MP_USE_INTEGER_PACK
    template<class>
    struct make_int_sequence_impl;
#elif ! defined(JLN_MP_FALLBACK_TO_STD_SEQUENCE)
    template<unsigned n>
    struct mk_int_seq;

    template<class C, class Ints>
    struct make_int_sequence_impl;

    template<template<class T, T...> class C, class Int, class Ints>
    struct make_int_pack_impl;

    template<template<class T, T...> class C, class Int, unsigned n>
    using make_int_pack_t = typename make_int_pack_impl<C, Int, typename mk_int_seq<n>::type>::type;
#else
    template<class C, class Ints>
    struct make_int_sequence_impl;

    template<template<class T, T...> class C, class Ints>
    struct make_int_pack_impl;

    template<template<class T, T...> class C, class Int, Int n>
    using make_int_pack_t = typename make_int_pack_impl<C, std::make_integer_sequence<Int, n>>::type;
#endif
  }
  /// \endcond

  /// \ingroup number

  /// Generates an incremental sequence of \c n \c int_.
  /// \treturn \sequence
  /// \see make_int_sequence, iota
  template<class C = numbers<>>
  struct make_int_sequence_v
  {
    template<class n>
#if JLN_MP_USE_MAKE_INTEGER_SEQ
    using f = typename __make_integer_seq<detail::make_int_sequence_impl<C>
      ::template f, int_, n::value>::type;
#elif JLN_MP_USE_INTEGER_PACK
    using f = typename detail::make_int_sequence_impl<C>
      ::template f<int_, __integer_pack(n::value)...>::type;
#elif ! defined(JLN_MP_FALLBACK_TO_STD_SEQUENCE)
    using f = typename detail::make_int_sequence_impl<
      C, typename detail::mk_int_seq<n::value>::type>::type;
#else
    using f = typename detail::make_int_sequence_impl<
      C, std::make_integer_sequence<int_, n::value>>::type;
#endif
  };

  template<class C = mp::listify>
  using make_int_sequence = make_int_sequence_v<mp::numbers<C>>;

  namespace emp
  {
#if JLN_MP_USE_INTEGER_PACK
    template<unsigned n, class C = mp::numbers<>>
    using make_int_sequence_v_c = typename mp::make_int_sequence_v<C>
      ::template f<number<n>>;

    template<unsigned n, class C = mp::listify>
    using make_int_sequence_c = typename mp::make_int_sequence_v<mp::numbers<C>>
      ::template f<number<n>>;

    template<class n, class C = mp::numbers<>>
    using make_int_sequence_v = typename mp::make_int_sequence_v<C>
      ::template f<n>;

    template<class n, class C = mp::listify>
    using make_int_sequence = typename mp::make_int_sequence_v<mp::numbers<C>>
      ::template f<n>;
#elif JLN_MP_USE_MAKE_INTEGER_SEQ
    template<unsigned n, class C = mp::numbers<>>
    using make_int_sequence_v_c = typename __make_integer_seq<
      detail::make_int_sequence_impl<C>::template f, int_, n>::type;

    template<unsigned n, class C = mp::listify>
    using make_int_sequence_c = typename __make_integer_seq<
      detail::make_int_sequence_impl<mp::numbers<C>>::template f, int_, n>::type;

    template<class n, class C = mp::numbers<>>
    using make_int_sequence_v = typename __make_integer_seq<
      detail::make_int_sequence_impl<C>::template f, int_, n::value>::type;

    template<class n, class C = mp::listify>
    using make_int_sequence = typename __make_integer_seq<
      detail::make_int_sequence_impl<mp::numbers<C>>::template f, int_, n::value>::type;
#else
# if ! defined(JLN_MP_FALLBACK_TO_STD_SEQUENCE)
#   define JLN_MK_INT_SEQ(n) typename detail::mk_int_seq<n>::type
# else
#   define JLN_MK_INT_SEQ(n) std::make_integer_sequence<int_, n>
# endif

    template<unsigned n, class C = mp::numbers<>>
    using make_int_sequence_v_c = typename detail::make_int_sequence_impl<
      C, JLN_MK_INT_SEQ(n)>::type;

    template<unsigned n, class C = mp::listify>
    using make_int_sequence_c = typename detail::make_int_sequence_impl<
      mp::numbers<C>, JLN_MK_INT_SEQ(n)>::type;

    template<class n, class C = mp::numbers<>>
    using make_int_sequence_v = typename detail::make_int_sequence_impl<
      C, JLN_MK_INT_SEQ(n::value)>::type;

    template<class n, class C = mp::listify>
    using make_int_sequence = typename detail::make_int_sequence_impl<
      mp::numbers<C>, JLN_MK_INT_SEQ(n::value)>::type;

# undef JLN_MK_INT_SEQ
#endif
  }

  /// Fast initialization of template of the shape `name<class T, T... ints>`.
  /// `n` should be a template parameter.
  /// \code
  /// template<class, int...>
  /// struct ints { ... };
  ///
  /// template<class n>
  /// using make_ints = JLN_MP_MAKE_INTEGER_SEQUENCE_T(int, n::value, ints);
  /// \endcode
  #if JLN_MP_USE_MAKE_INTEGER_SEQ
  #  define JLN_MP_MAKE_INTEGER_SEQUENCE_T(T, n, ...) __make_integer_seq<__VA_ARGS__, T, n>
  #  define JLN_MP_MAKE_INTEGER_SEQUENCE_TYPENAME
  #elif JLN_MP_USE_MAKE_INTEGER_SEQ || JLN_MP_USE_INTEGER_PACK
  #  define JLN_MP_MAKE_INTEGER_SEQUENCE_T(T, n, ...) __VA_ARGS__<T, __integer_pack(n)...>
  #  define JLN_MP_MAKE_INTEGER_SEQUENCE_TYPENAME typename
  #else
  #  define JLN_MP_MAKE_INTEGER_SEQUENCE_T(T, n, ...) \
      ::jln::mp::detail::make_int_pack_t<__VA_ARGS__, T, n>
  #  define JLN_MP_MAKE_INTEGER_SEQUENCE_TYPENAME typename
  #endif

  /// Fast initialization of template of the shape `name<class T, std::size_t... ints>`.
  /// `n` should be a template parameter.
  #define JLN_MP_MAKE_INDEX_SEQUENCE(n, ...) \
    JLN_MP_MAKE_INTEGER_SEQUENCE_T(std::size_t, n, __VA_ARGS__)

  /// Fast initialization of template of the shape `name<class T, int_... ints>`.
  /// `n` should be a template parameter.
  #define JLN_MP_MAKE_INTEGER_SEQUENCE(n, ...) \
    JLN_MP_MAKE_INTEGER_SEQUENCE_T(::jln::mp::int_, n, __VA_ARGS__)

  /// Fast initialization of template of the shape `name<class T, unsigned... ints>`.
  /// `n` should be a template parameter.
  #define JLN_MP_MAKE_UNSIGNED_SEQUENCE(n, ...) \
    JLN_MP_MAKE_INTEGER_SEQUENCE_T(unsigned, n, __VA_ARGS__)

  /// Template-dependent version of \c JLN_MP_MAKE_INTEGER_SEQUENCE_T ; add typename when needed.
  /// \code
  /// // typename impl<...>::template f<T, 0, 1, 2> ->
  /// JLN_MP_D_MAKE_INTEGER_SEQUENCE_T(T, n, impl<...>::template f)
  /// \endcode
  #define JLN_MP_D_MAKE_INTEGER_SEQUENCE_T(T, n, ...) \
    JLN_MP_MAKE_INTEGER_SEQUENCE_TYPENAME JLN_MP_MAKE_INTEGER_SEQUENCE_T(T, n, __VA_ARGS__)

  /// Template-dependent version of \c JLN_MP_MAKE_INDEX_SEQUENCE ; add typename when needed.
  /// \code
  /// // typename impl<...>::template f<T, 0, 1, 2> ->
  /// JLN_MP_MAKE_INDEX_SEQUENCE(n, impl<...>::template f)
  /// \endcode
  #define JLN_MP_D_MAKE_INDEX_SEQUENCE(n, ...) \
    JLN_MP_MAKE_INTEGER_SEQUENCE_TYPENAME JLN_MP_MAKE_INDEX_SEQUENCE(n, __VA_ARGS__)

  /// Template-dependent version of \c JLN_MP_MAKE_INTEGER_SEQUENCE ; add typename when needed.
  /// \code
  /// // typename impl<...>::template f<T, 0, 1, 2> ->
  /// JLN_MP_D_MAKE_INTEGER_SEQUENCE(n, impl<...>::template f)
  /// \endcode
  #define JLN_MP_D_MAKE_INTEGER_SEQUENCE(n, ...) \
    JLN_MP_MAKE_INTEGER_SEQUENCE_TYPENAME JLN_MP_MAKE_INTEGER_SEQUENCE(n, __VA_ARGS__)

  /// Template-dependent version of \c JLN_MP_MAKE_UNSIGNED_SEQUENCE ; add typename when needed.
  /// \code
  /// // typename impl<...>::template f<T, 0, 1, 2> ->
  /// JLN_MP_D_MAKE_UNSIGNED_SEQUENCE(n, impl<...>::template f)
  /// \endcode
  #define JLN_MP_D_MAKE_UNSIGNED_SEQUENCE(n, ...) \
    JLN_MP_MAKE_INTEGER_SEQUENCE_TYPENAME JLN_MP_MAKE_UNSIGNED_SEQUENCE(n, __VA_ARGS__)

  /// single list of int_
  template<int_... i>
  struct int_seq_v;
} // namespace jln::mp


/// \cond
#if JLN_MP_USE_MAKE_INTEGER_SEQ || JLN_MP_USE_INTEGER_PACK
namespace jln::mp::detail
{
  template<class C>
  struct make_int_sequence_impl
  {
    template<class, int_... ns>
    struct f
    {
      using type = typename C::template f<ns...>;
    };
  };

  template<>
  struct make_int_sequence_impl<numbers<>>
  {
    template<class, int_... ns>
    struct f
    {
      using type = list<number<ns>...>;
    };
  };

  template<class C>
  struct make_int_sequence_impl<numbers<C>>
  {
    template<class, int_... ns>
    struct f
    {
      using type = typename C::template f<number<ns>...>;
    };
  };

  template<template<class...> class F>
  struct make_int_sequence_impl<numbers<lift<F>>>
  {
    template<class, int_... ns>
    struct f
    {
      using type = F<number<ns>...>;
    };
  };

  template<template<class...> class F, class C>
  struct make_int_sequence_impl<numbers<lift<F, C>>>
  {
    template<class, int_... ns>
    struct f
    {
      using type = typename C::template f<F<number<ns>...>>;
    };
  };

  template<template<class...> class F>
  struct make_int_sequence_impl<numbers<lift_t<F>>>
  {
    template<class, int_... ns>
    struct f
    {
      using type = typename F<number<ns>...>::type;
    };
  };

  template<template<class...> class F, class C>
  struct make_int_sequence_impl<numbers<lift_t<F, C>>>
  {
    template<class, int_... ns>
    struct f
    {
      using type = typename C::template f<F<number<ns>...>>::type;
    };
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct make_int_sequence_impl<lift_v<F>>
  {
    template<class, int_... ns>
    struct f
    {
      using type = F<ns...>;
    };
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C>
  struct make_int_sequence_impl<lift_v<F, C>>
  {
    template<class, int_... ns>
    struct f
    {
      using type = typename C::template f<F<ns...>>;
    };
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct make_int_sequence_impl<lift_v_t<F>>
  {
    template<class, int_... ns>
    struct f
    {
      using type = typename F<ns...>::type;
    };
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C>
  struct make_int_sequence_impl<lift_v_t<F, C>>
  {
    template<class, int_... ns>
    struct f
    {
      using type = typename C::template f<F<ns...>>::type;
    };
  };
}
#elif ! defined(JLN_MP_FALLBACK_TO_STD_SEQUENCE)
namespace jln::mp::detail
{
  template<bool, int_ n, class ns>
  struct int_seq_expand;

  template<int_ n, int_... ns>
  struct int_seq_expand<false, n, int_seq_v<ns...>>
  {
    using type = int_seq_v<ns..., (n+ns)...>;
  };

  template<int_ n, int_... ns>
  struct int_seq_expand<true, n, int_seq_v<ns...>>
  {
    using type = int_seq_v<ns..., (n+ns)..., n * 2>;
  };

  template<unsigned n>
  struct mk_int_seq
  : int_seq_expand<n & 1, n / 2, typename mk_int_seq<n / 2>::type>
  {};

  template<> struct mk_int_seq<0> { using type = int_seq_v<>; };
  template<> struct mk_int_seq<1> { using type = int_seq_v<0>; };

  template<int_... ns>
  struct make_int_sequence_impl<numbers<>, int_seq_v<ns...>>
  {
    using type = list<number<ns>...>;
  };

  template<class C, int_... ns>
  struct make_int_sequence_impl<C, int_seq_v<ns...>>
  {
    using type = typename C::template f<ns...>;
  };

  template<class C, int_... ns>
  struct make_int_sequence_impl<numbers<C>, int_seq_v<ns...>>
  {
    using type = typename C::template f<number<ns>...>;
  };

  template<template<class T, T...> class C, class Int, int_... ns>
  struct make_int_pack_impl<C, Int, int_seq_v<ns...>>
  {
    using type = C<Int, ns...>;
  };
}
#else
namespace jln::mp::detail
{
  template<class C, int_... ns>
  struct make_int_sequence_impl<C, std::integer_sequence<int_, ns...>>
  {
    using type = typename C::template f<ns...>;
  };

  template<class C, int_... ns>
  struct make_int_sequence_impl<numbers<C>, std::integer_sequence<int_, ns...>>
  {
    using type = typename C::template f<number<ns>...>;
  };

  template<template<class T, T...> class C, class Int, Int... ns>
  struct make_int_pack_impl<C, std::integer_sequence<Int, ns...>>
  {
    using type = C<Int, ns...>;
  };
}
#endif
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned n>
    struct rotate_impl;

    constexpr unsigned rotate_size(int_ n, unsigned size);
  }
  /// \endcond

  /// \ingroup algorithm

  /// Rotates the elements of a \sequence around a pivot.
  /// \tparam N  a negative value start to end of sequence. The final offset is a modulo of `sizeof...(xs)`.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///     len = sizeof...(xs)
  ///     n = len ? (N < 0 ? len + N % len : N) % size : 0
  ///
  ///     C::f<...xs[n:], ...xs[:n]>
  ///   \endcode
  /// \treturn \sequence
  template<int_ N, class C = listify>
  struct rotate_c
  {
    template<class... xs>
    using f = typename detail::rotate_impl<
      detail::rotate_size(N, sizeof...(xs))
    >
    ::template f<
      detail::rotate_size(N, sizeof...(xs)),
      C, xs...
    >;
  };

  template<class N, class C = listify>
  using rotate = rotate_c<N::value, C>;

  namespace emp
  {
    template<class L, class n, class C = mp::listify>
    using rotate = unpack<L, mp::rotate<n, C>>;

    template<class L, int_ n, class C = mp::listify>
    using rotate_c = unpack<L, mp::rotate_c<n, C>>;
  }
}


/// \cond

namespace jln::mp
{
  template<int_ N1, int_ N2, class C>
  struct rotate_c<N1, rotate_c<N2, C>>
    : rotate_c<N1 + N2, C>
  {};

#if JLN_MP_HAS_BUILTIN(__type_pack_element)
  // back<C>
  template<int_ N, class C>
  struct rotate_c<N, front<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      __type_pack_element<detail::rotate_size(N, sizeof...(xs)), xs...>
    );
  };

  // back<>
  template<int_ N>
  struct rotate_c<N, front<>>
  {
    template<class... xs>
    using f = __type_pack_element<detail::rotate_size(N, sizeof...(xs)), xs...>;
  };
#endif
}

namespace jln::mp::detail
{
  constexpr unsigned rotate_size(int_ n, unsigned size)
  {
    return size ? static_cast<unsigned>(n < 0 ? size + n % size : n) % size : 0;
  }

  template<unsigned n>
  struct rotate_impl : rotate_impl<
      n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

#define JLN_MP_ROTATE_IMPL(n, mp_xs, mp_rxs, _)           \
  template<>                                              \
  struct rotate_impl<n>                                   \
  {                                                       \
    template<unsigned size, class C,                      \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)              \
      class... xs>                                        \
    using f = JLN_MP_CALL_TRACE(C,                        \
      xs... mp_xs(JLN_MP_COMMA, JLN_MP_NIL, JLN_MP_NIL)); \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_MP_ROTATE_IMPL)

#undef JLN_MP_ROTATE_IMPL

#define JLN_MP_ROTATE_IMPL(n, mp_xs, mp_rxs, _)           \
  template<>                                              \
  struct rotate_impl<n>                                   \
  {                                                       \
    template<unsigned size, class C,                      \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)              \
      class... xs>                                        \
    using f = typename rotate_impl<size-n>                \
      ::template f<size-n, C,                             \
        xs... mp_xs(JLN_MP_COMMA, JLN_MP_NIL, JLN_MP_NIL) \
      >;                                                  \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_ROTATE_IMPL)

#undef JLN_MP_ROTATE_IMPL
} // namespace jln::mp
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, class... Fs>
    struct _tee;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions passing all parameters to each.
  /// \treturn \value
  /// \see each, partial
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct tee
  {
    template<class... xs>
    using f = C::f<Fs::f<xs...>...>;
  };
#else
  template<class... Fs>
  struct tee
  : detail::rotate_impl<sizeof...(Fs)-1>
  ::template f<sizeof...(Fs)-1, lift<detail::_tee>, Fs...>
  {};
#endif

  /// \cond
  template<class C>
  struct tee<C> : detail::call_trace_xs_0<C>
  {};

  template<class F, class C>
  struct tee<F, C>
  {
    template<class... xs>
    using f = typename JLN_MP_TRACE_F(C)::template f<
      JLN_MP_DCALL_TRACE_XS(xs, F, xs...)
    >;
  };

  template<class F0, class F1, class C>
  struct tee<F0, F1, C>
  {
    template<class... xs>
    using f = typename JLN_MP_TRACE_F(C)::template f<
      JLN_MP_DCALL_TRACE_XS(xs, F0, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F1, xs...)
    >;
  };

  template<class F0, class F1, class F2, class C>
  struct tee<F0, F1, F2, C>
  {
    template<class... xs>
    using f = typename JLN_MP_TRACE_F(C)::template f<
      JLN_MP_DCALL_TRACE_XS(xs, F0, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F1, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F2, xs...)
    >;
  };
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template<class C, class... Fs>
  struct _tee
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, JLN_MP_DCALL_TRACE_XS(xs, Fs, xs...)...);
  };

  template<class C>
  struct optimize_tee
  {
    using type = C;
  };

  template<class C>
  struct optimize_tee<tee<C, identity>>
    : optimize_tee<C>
  {};

  template<class C>
  using optimize_tee_t = typename optimize_tee<C>::type;
} // namespace jln::mp
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, class F>
    struct anticirculant_matrix_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// square matrix in which all row vectors are composed of the
  /// same elements and each row vector is rotated one element to
  /// the left relative to the preceding row vector.
  /// \semantics
  ///   \code
  ///   anticirculant_matrix_with<>::f<a, b, c, d>
  ///   == list<
  ///     list<a, b, c, d>,
  ///     list<b, c, d, a>,
  ///     list<c, d, a, b>,
  ///     list<d, a, b, c>
  ///   >
  ///   \endcode
  /// \treturn \value
  /// \see circulant_matrix
  template<class F = listify, class C = listify>
  struct anticirculant_matrix_with
  {
    template<class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(
      sizeof...(xs), detail::anticirculant_matrix_impl<C, F>::template impl
    )::template f<xs...>;
  };

  template<class C = listify>
  using anticirculant_matrix = anticirculant_matrix_with<listify, C>;

  namespace emp
  {
    template<class L, class F, class C = mp::listify>
    using anticirculant_matrix_with = unpack<L, mp::anticirculant_matrix_with<F, C>>;

    template<class L, class C = mp::listify>
    using anticirculant_matrix = unpack<L, mp::anticirculant_matrix<C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class C, class F>
  struct anticirculant_matrix_impl
  {
    template<class, int_... i>
    struct impl : _tee<C, rotate_c<i, F>...>
    {};
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a predicate does not hold for any element of a \sequence.
  /// \treturn \bool
  /// \see all_of, any_of
  template<class Pred, class C = identity>
  struct none_of
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(
      C,
      typename detail::is_drop_while_continue<
        typename detail::_drop_until<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type
    );
  };

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using none_of = unpack<L, mp::none_of<Pred, C>>;
  }
} // namespace jln::mp


/// \cond
namespace jln::mp
{
  template<class Pred>
  struct none_of<Pred, identity>
  {
    template<class... xs>
    using f = typename detail::is_drop_while_continue<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::type;
  };

  template<class Pred>
  struct none_of<Pred, not_<>>
  {
    template<class... xs>
    using f = number<!detail::is_drop_while_continue<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::type::value>;
  };

  template<class Pred, class C>
  struct none_of<Pred, not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(
      C,
      number<!detail::is_drop_while_continue<
        typename detail::_drop_until<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type::value>
    );
  };

  template<class Pred, class TC, class FC>
  struct if_<none_of<Pred>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      detail::is_drop_while_continue<
        typename detail::_drop_until<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type::value
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };

  template<class Pred, class TC, class FC>
  struct if_<none_of<Pred, not_<>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      !detail::is_drop_while_continue<
        typename detail::_drop_until<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type::value
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };
} // namespace jln::mp
/// \endcond

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a predicate holds for at least some element of a \sequence.
  /// \treturn \bool
  /// \see all_of, none_of
  template<class Pred, class C = identity>
  using any_of = none_of<Pred, not_<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using any_of = unpack<L, mp::any_of<Pred, C>>;
  }
  /// \cond
  namespace detail
  {
    template<class C, int... ints>
    struct arrange_impl;

    template<class Ints>
    struct make_arrange
    {};
  }
  /// \endcond

  /// \ingroup algorithm

  /// Uses a list of indexes to reorder a sequence.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   arrange<numbers<0, 2, 0>>::f<a, b, c, d> == list<a, c, a>
  ///   \endcode
  /// \treturn \list
  template<class Ints, class C = listify>
  using arrange = typename detail::make_arrange<Ints>::template f<C>;

  template<int... ints>
  using arrange_c = detail::apply_indexed_v<detail::arrange_impl<listify, ints...>>;

  template<class C, int... ints>
  using arrange_c_with = detail::apply_indexed_v<detail::arrange_impl<C, ints...>>;

  namespace emp
  {
    template<class L, class Ints, class C = listify>
    using arrange = unpack<L, mp::arrange<Ints, C>>;

    template<class L, int... ints>
    using arrange_c = unpack<L, detail::apply_indexed_v<detail::arrange_impl<listify, ints...>>>;

    template<class L, class C, int... ints>
    using arrange_with_c = unpack<L, detail::apply_indexed_v<detail::arrange_impl<C, ints...>>>;
  }
}


/// \cond

namespace jln::mp::detail
{
  template<class C, int... ints>
  struct arrange_impl
  {
    template<class F>
    using f = typename std::enable_if_t<0 <= sizeof(F), JLN_MP_TRACE_F(C)>
      ::template f<typename F::template f<ints>...>;
  };

  template<int... ints>
  struct arrange_impl<listify, ints...>
  {
    template<class F>
    using f = list<typename F::template f<ints>...>;
  };


  template<template<class...> class Tpl, class... ints>
  struct make_arrange<Tpl<ints...>>
  {
    template<class C>
    using f = apply_indexed_v<arrange_impl<C, ints::value...>>;
  };

  template<template<class T, T...> class Tpl, class T, T... ints>
  struct make_arrange<Tpl<T, ints...>>
  {
    template<class C>
    using f = apply_indexed_v<arrange_impl<C, ints...>>;
  };

  template<template<int_...> class Tpl, int_... ints>
  struct make_arrange<Tpl<ints...>>
  {
    template<class C>
    using f = apply_indexed_v<arrange_impl<C, ints...>>;
  };

#if JLN_MP_ENABLE_TPL_AUTO
  template<template<auto...> class Tpl, auto... ints>
  struct make_arrange<Tpl<ints...>>
  {
    template<class C>
    using f = apply_indexed_v<arrange_impl<C, ints...>>;
  };
#endif
}
/// \endcond


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct pairwise_impl;
  }
  /// \endcond

  /// \ingroup group

  /// Returns successive overlapping pairs.
  /// \post If `sizeof...(xs) <= 1`, then the result sequence is empty
  /// \post If `sizeof...(xs) > 1`, then the number of 2-tuples is `sizeof...(xs) - 1`
  /// \semantics
  ///   \code
  ///   pairwise<>::f<a, b, c, d>
  ///   == list<
  ///     list<a, b>,
  ///     list<b, c>,
  ///     list<c, d>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see sliding, batched
  template<class F = listify, class C = listify>
  struct pairwise_with
  {
    template<class... xs>
    using f = typename detail::pairwise_impl<rotate_c<-1>::f<xs...>>
      ::template f<JLN_MP_TRACE_F(C)::template f, JLN_MP_TRACE_F(F)::template f, xs...>;
  };

  template<class C = listify>
  using pairwise = pairwise_with<listify, C>;

  namespace emp
  {
    template<class L, class F = mp::listify, class C = mp::listify>
    using pairwise_with = unpack<L, mp::pairwise_with<F, C>>;

    template<class L, class C = mp::listify>
    using pairwise = unpack<L, mp::pairwise<C>>;
  }

/// \cond
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
  template<class F, template<class...> class C>
  struct pairwise_with<F, lift<C>>
  {
    template<class... xs>
    using f = typename detail::pairwise_impl<rotate_c<-1>::f<xs...>>
      ::template f<C, JLN_MP_TRACE_F(F)::template f, xs...>;
  };

  template<template<class...> class F, class C>
  struct pairwise_with<lift<F>, C>
  {
    template<class... xs>
    using f = typename detail::pairwise_impl<rotate_c<-1>::f<xs...>>
      ::template f<JLN_MP_TRACE_F(C)::template f, F, xs...>;
  };

  template<template<class...> class F, template<class...> class C>
  struct pairwise_with<lift<F>, lift<C>>
  {
    template<class... xs>
    using f = typename detail::pairwise_impl<rotate_c<-1>::f<xs...>>
      ::template f<C, F, xs...>;
  };
#endif
/// \endcond
}

namespace jln::mp::detail
{
  template<class>
  struct pairwise_impl;

  template<class x, class... xs>
  struct pairwise_impl<list<x, xs...>>
  {
    template<template<class...> class C, template<class...> class F, class y, class... ys>
    using f = C<F<xs, ys>...>;
  };

  template<class x>
  struct pairwise_impl<list<x>>
  {
    template<template<class...> class C, template<class...> class F, class...>
    using f = C<>;
  };

  template<>
  struct pairwise_impl<list<>>
  {
    template<template<class...> class C, template<class...> class F>
    using f = C<>;
  };
}

namespace jln::mp
{
  /// \ingroup list

  /// Appends \c x to the end of the sequence.
  /// \treturn \sequence
  template<class x, class C = listify>
  struct push_back
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs..., x);
  };

  namespace emp
  {
    template<class L, class T, class C = mp::listify>
    using push_back = unpack<L, mp::push_back<T, C>>;
  }

  /// \cond
  template<class x>
  struct push_back<x, listify>
  {
    template<class... xs>
    using f = list<xs..., x>;
  };
  /// \endcond
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class F, class C>
    struct not_fn_impl;
  }
  /// \endcond

  /// \ingroup functional

  /// Returns the negation of \c F.
  /// \treturn \bool
  template<class F, class C = identity>
  using not_fn = typename detail::not_fn_impl<F, C>::type;

  namespace emp
  {
    template<class F, class... xs>
    using not_of = mp::number<!JLN_MP_DCALL_V_TRACE_XS(xs, F, xs...)::value>;

    template<class L, class F, class C = mp::identity>
    using not_fn = unpack<L, mp::not_fn<F, C>>;
  }
}



/// \cond
namespace jln::mp::detail
{
  template<class F>
  struct to_not_fn;

  template<class F>
  using to_not_fn_t = typename to_not_fn<F>::type;

  template<class Pred>
  struct to_not_fn
  {
    using type = tee<Pred, not_<>>;
  };

  template<>
  struct to_not_fn<not_<>>
  {
    using type = not_<not_<>>;
  };

  template<>
  struct to_not_fn<not_<not_<>>>
  {
    using type = not_<>;
  };

  template<class C>
  struct to_not_fn<not_<to_bool<C>>>
  : to_not_fn<not_<C>>
  {};

  template<class C>
  struct to_not_fn<not_<not_<not_<C>>>>
  : to_not_fn<not_<C>>
  {};

  template<>
  struct to_not_fn<identity>
  {
    using type = not_<>;
  };

  template<class PredNot>
  struct optimise_not_not;

  template<class PredNot>
  struct optimise_not_not<not_<not_<PredNot>>>
  {
    using type = PredNot;
  };

  template<class PredNot>
  struct optimise_not_not
  {
    using type = PredNot;
  };

  template<class C>
  struct to_not_fn<to_bool<C>>
  {
    using type = to_bool<typename optimise_not_not<to_not_fn_t<C>>::type>;
  };

  template<class x, class C>
  struct to_not_fn<is<x, C>>
  {
    using type = is<x, typename optimise_not_not<to_not_fn_t<C>>::type>;
  };

  template<class C>
  struct to_not_fn<same<C>>
  {
    using type = same<typename optimise_not_not<to_not_fn_t<C>>::type>;
  };

  template<class PredNot>
  struct to_not_fn_lift;

  template<template<class...> class F, class C, class Not>
  struct to_not_fn_lift<lift<F, tee<C, Not>>>
  {
    using type = tee<lift<F, C>, Not>;
  };

  template<class PredNot>
  struct to_not_fn_lift
  {
    using type = PredNot;
  };

  template<template<class...> class F, class C>
  struct to_not_fn<lift<F, C>>
  : to_not_fn_lift<lift<F, to_not_fn_t<C>>>
  {};

  template<class x, class C>
  struct to_not_fn<push_front<x, C>>
  {
    using type = push_front<x, to_not_fn_t<C>>;
  };

  template<class x, class C>
  struct to_not_fn<push_back<x, C>>
  {
    using type = push_back<x, to_not_fn_t<C>>;
  };

  template<class Pred>
  struct to_not_fn_tee;

  template<class Pred>
  struct to_not_fn_tee<tee<Pred, not_<>>>
  {
    using type = tee<Pred, not_<not_<>>>;
  };

  template<class Pred>
  struct to_not_fn_tee
  : to_not_fn<Pred>
  {};

  template<class Pred>
  struct to_not_fn<tee<Pred, not_<>>>
  : to_not_fn_tee<to_not_fn_t<Pred>>
  {};

  template<class PredNot>
  struct to_not_fn_tee2;

  template<class PredNot>
  struct to_not_fn_tee2<tee<PredNot, not_<>>>
  : to_not_fn<PredNot>
  {};

  template<class PredNot>
  struct to_not_fn_tee2<tee<PredNot, not_<not_<>>>>
  : to_not_fn<PredNot>
  {};

  template<class PredNot>
  struct to_not_fn_tee2
  {
    using type = PredNot;
  };

  template<class Pred, class C>
  struct to_not_fn<tee<Pred, C>>
  : to_not_fn_tee2<tee<Pred, to_not_fn_t<C>>>
  {};

  template<class F, class C>
  struct not_fn_impl
  : to_not_fn<tee<F, C>>
  {};

  template<class F>
  struct not_fn_impl<F, identity>
  : to_not_fn<F>
  {};
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class Pred>
    struct mk_wrap_in_list_if;

    template<class Pred>
    struct mk_wrap_in_list_if_not;
  }
  /// \endcond

  /// \ingroup list

  /// Returns a \list with the first element if the predicate is checked, otherwise returns a empty list.
  /// \pre \c Pred<xs...>::value must be narrowing convertible to bool
  /// \treturn \list
  template<class Pred>
  using wrap_in_list_if = typename detail::mk_wrap_in_list_if_not<
    detail::to_not_fn_t<Pred>
  >::type;

  /// Returns a \list with the first element if the predicate is not checked, otherwise returns a empty list.
  /// \pre \c Pred<xs...>::value must be narrowing convertible to bool
  /// \treturn \list
  template<class Pred>
  using wrap_in_list_if_not = typename detail::mk_wrap_in_list_if<
    detail::to_not_fn_t<Pred>
  >::type;

  template<bool b>
  struct wrap_in_list_c;

  template<>
  struct wrap_in_list_c<true>
  : listify
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f = list<xs...>;
#endif
  };

  template<>
  struct wrap_in_list_c<false>
  : always<list<>>
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f = list<>;
#endif
  };

  template<class b>
  using wrap_in_list = wrap_in_list_c<b::value>;

  namespace emp
  {
    template<class Pred, class... xs>
    using wrap_in_list_if = typename mp::wrap_in_list_if<Pred>::template f<xs...>;

    template<class Pred, class... xs>
    using wrap_in_list_if_not = typename mp::wrap_in_list_if_not<Pred>::template f<xs...>;

    template<class b, class... xs>
    using wrap_in_list = typename mp::wrap_in_list_c<b::value>::template f<xs...>;

    template<bool b, class... xs>
    using wrap_in_list_c = typename mp::wrap_in_list_c<b>::template f<xs...>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class Pred>
  struct _wrap_in_list_if
  {
    template<class x, class... xs>
    using f = JLN_MP_CALL_TRACE(wrap_in_list_c<
      JLN_MP_RAW_EXPR_TO_BOOL(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, x, xs...)::value)
    >, x);
  };

  template<class Pred>
  struct _wrap_in_list_if_not
  {
    template<class x, class... xs>
    using f = JLN_MP_CALL_TRACE(wrap_in_list_c<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, x, xs...)::value)
    >, x);
  };

  template<class T>
  struct _wrap_in_list_if<is<T>>
  {
    template<class x, class... xs>
    using f = typename std::enable_if_t<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs)),
      wrap_in_list_c<JLN_MP_IS_SAME(T, x)>
    >::template f<x>;
  };

  template<class C, class T>
  struct _wrap_in_list_if<is<T, C>>
  {
    template<class x, class... xs>
    using f = typename std::enable_if_t<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs)),
      wrap_in_list_c<JLN_MP_RAW_EXPR_TO_BOOL(
        JLN_MP_TRACE_F(C)::template f<number<JLN_MP_IS_SAME(T, x)>>::value
      )>
    >::template f<x>;
  };

  template<class C, class T>
  struct _wrap_in_list_if<is<T, not_<C>>>
  {
    template<class x, class... xs>
    using f = typename std::enable_if_t<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs)),
      wrap_in_list_c<JLN_MP_RAW_EXPR_TO_BOOL(
        JLN_MP_TRACE_F(C)::template f<number<
          !JLN_MP_IS_SAME(T, x)
        >>::value
      )>
    >::template f<x>;
  };

  template<class T>
  struct _wrap_in_list_if_not<is<T>>
  {
    template<class x, class... xs>
    using f = typename std::enable_if_t<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs)),
      wrap_in_list_c<!JLN_MP_IS_SAME(T, x)>
    >::template f<x>;
  };

  template<class C, class T>
  struct _wrap_in_list_if_not<is<T, C>>
  {
    template<class x, class... xs>
    using f = typename std::enable_if_t<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs)),
      wrap_in_list_c<JLN_MP_RAW_EXPR_TO_BOOL_NOT(
        JLN_MP_TRACE_F(C)::template f<number<JLN_MP_IS_SAME(T, x)>>::value
      )>
    >::template f<x>;
  };

  template<class C, class T>
  struct _wrap_in_list_if_not<is<T, not_<C>>>
  {
    template<class x, class... xs>
    using f = typename std::enable_if_t<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs)),
      wrap_in_list_c<JLN_MP_RAW_EXPR_TO_BOOL_NOT(
        JLN_MP_TRACE_F(C)::template f<number<!JLN_MP_IS_SAME(T, x)>>::value
      )>
    >::template f<x>;
  };

  template<>
  struct _wrap_in_list_if<same<>>
  {
    template<class x, class... xs>
    using f = typename wrap_in_list_c<emp::same_xs_v<x, xs...>>
      ::template f<x>;
  };

  template<class C>
  struct _wrap_in_list_if<same<C>>
  {
    template<class x, class... xs>
    using f = typename wrap_in_list_c<JLN_MP_RAW_EXPR_TO_BOOL(
      JLN_MP_TRACE_F(C)::template f<number<emp::same_xs_v<x, xs...>>>::value
    )>::template f<x>;
  };

  template<>
  struct _wrap_in_list_if_not<same<>>
  {
    template<class x, class... xs>
    using f = typename wrap_in_list_c<!emp::same_xs_v<x, xs...>>
      ::template f<x>;
  };

  template<class C>
  struct _wrap_in_list_if_not<same<C>>
  {
    template<class x, class... xs>
    using f = typename wrap_in_list_c<JLN_MP_RAW_EXPR_TO_BOOL(JLN_MP_TRACE_F(C)::template f<
      number<!emp::same_xs_v<x, xs...>>
    >::value)>::template f<x>;
  };

#if ! JLN_MP_ENABLE_DEBUG
  template<template<class...> class Pred>
  struct _wrap_in_list_if<lift<Pred>>
  {
    template<class x, class... xs>
    using f = JLN_MP_CALL_TRACE(wrap_in_list_c<
      JLN_MP_RAW_EXPR_TO_BOOL(JLN_MP_DCALLF_V_XS(xs, Pred, x, xs...)::value)
    >, x);
  };

  template<template<class...> class Pred>
  struct _wrap_in_list_if_not<lift<Pred>>
  {
    template<class x, class... xs>
    using f = JLN_MP_CALL_TRACE(wrap_in_list_c<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALLF_V_XS(xs, Pred, x, xs...)::value)
    >, x);
  };

  template<template<class...> class Pred>
  struct _wrap_in_list_if<lift_t<Pred>>
  {
    template<class x, class... xs>
    using f = JLN_MP_CALL_TRACE(wrap_in_list_c<
      JLN_MP_RAW_EXPR_TO_BOOL(JLN_MP_DCALLF_V_XS(xs, Pred, x, xs...)::type::value)
    >, x);
  };

  template<template<class...> class Pred>
  struct _wrap_in_list_if_not<lift_t<Pred>>
  {
    template<class x, class... xs>
    using f = JLN_MP_CALL_TRACE(wrap_in_list_c<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALLF_V_XS(xs, Pred, x, xs...)::type::value)
    >, x);
  };
#endif

  template<class Pred>
  struct mk_wrap_in_list_if
  {
    using type = _wrap_in_list_if<Pred>;
  };

  template<class Pred>
  struct mk_wrap_in_list_if_not
  {
    using type = _wrap_in_list_if_not<Pred>;
  };


  template<class x>
  struct mk_wrap_in_list_if<is<x, not_<>>>
  {
    using type = _wrap_in_list_if_not<is<x>>;
  };

  template<>
  struct mk_wrap_in_list_if<same<not_<>>>
  {
    using type = _wrap_in_list_if_not<same<>>;
  };

  template<template<class...> class F>
  struct mk_wrap_in_list_if<lift<F, not_<>>>
  {
    using type = _wrap_in_list_if_not<lift<F>>;
  };

  template<class Pred>
  struct mk_wrap_in_list_if<tee<Pred, not_<>>>
  {
    using type = _wrap_in_list_if_not<Pred>;
  };


  template<class x>
  struct mk_wrap_in_list_if_not<is<x, not_<>>>
  {
    using type = _wrap_in_list_if<is<x>>;
  };

  template<>
  struct mk_wrap_in_list_if_not<same<not_<>>>
  {
    using type = _wrap_in_list_if<same<>>;
  };

  template<template<class...> class F>
  struct mk_wrap_in_list_if_not<lift<F, not_<>>>
  {
    using type = _wrap_in_list_if<lift<F>>;
  };

  template<class Pred>
  struct mk_wrap_in_list_if_not<tee<Pred, not_<>>>
  {
    using type = _wrap_in_list_if<Pred>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<template<class...> class C, class... Selectors>
    struct compress_impl;

    template<class L, class C>
    struct make_compress;
  }
  /// \endcond

  /// \ingroup filter

  /// Removes elements that have a corresponding element in selectors to 0.
  /// \pre `emp::unpack<Selectors, listify> == Selectors`
  /// \pre all `Selectors::value` are `1`, `0` or a `bool` value
  /// \pre `sizeof...(xs) == emp::size<Selectors>`
  /// \semantics
  ///   \code
  ///   compress_c<1,0,1,0,1,1>
  ///          ::f<a,b,c,d,e,f>
  ///      == list<a,  c,  e,f>
  ///   \endcode
  /// \treturn \sequence
  template<class C, bool... selectors>
  struct compress_c_with
    : detail::compress_impl<C::template f, wrap_in_list_c<selectors>...>
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f;
#endif
  };

  template<bool... selectors>
  using compress_c = compress_c_with<listify, selectors...>;

  template<class... Selectors>
  using compress_for = compress_c_with<listify, Selectors::value...>;

  template<class Selectors, class C = listify>
  using compress = typename detail::make_compress<Selectors, C>::type;

  namespace emp
  {
    template<class L, class Selectors, class C = mp::listify>
    using compress = unpack<L, typename detail::make_compress<Selectors, C>::type>;

    template<class L, class... Selectors>
    using compress_for = unpack<L, mp::compress_c_with<listify, Selectors::value...>>;

    template<class L, bool... selectors>
    using compress_c = unpack<L, mp::compress_c_with<listify, selectors...>>;

    template<class L, class C, bool... selectors>
    using compress_c_with = unpack<L, mp::compress_c_with<C, selectors...>>;
  }
}


/// \cond
namespace jln::mp
{
  template<bool... selectors>
  struct compress_c_with<listify, selectors...>
    : detail::compress_impl<list, wrap_in_list_c<selectors>...>
  {};
}

namespace jln::mp::detail
{
  template<template<class...> class C, class... Selectors>
  struct compress_impl
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(Selectors)>
      ::template f<C, typename Selectors::template f<xs>...>
      ::type
      ;
  };

  template<template<class...> class Tpl, class... selectors, class C>
  struct make_compress<Tpl<selectors...>, C>
  {
    using type = compress_c_with<C, selectors::value...>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, class... Fs>
    struct _each;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions each taking the parameter corresponding to its position.
  /// \treturn \value
  /// \see tee, partial
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct each
  {
    template<class... xs>
    using f = C::f<Fs::f<xs>...>;
  };
#else
  template<class... Fs>
  struct each
  : detail::rotate_impl<sizeof...(Fs)-1>
  ::template f<sizeof...(Fs)-1, lift<detail::_each>, Fs...>
  {};
#endif
}

/// \cond
namespace jln::mp::detail
{
  template<class C, class... Fs>
  struct _each
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, typename JLN_MP_TRACE_F(Fs)::template f<xs>...);
  };
} // namespace jln::mp
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, int_ i, int_ ri>
    struct slice_impl;

    template<int_ i, int_ ri>
    struct strided_slice_impl;

    template<class C, int_ i, int_ ri>
    struct positive_slice_impl;

    template<int_ i, int_ ri>
    struct positive_strided_slice_impl;

    template<bool>
    struct negative_slice_select;

    template<bool>
    struct negative_strided_slice_select;

    // pre: start < 0
    // pre: count > 0
    // pre: step > 0
    // pre: n >= 0
    template<int_ start, int_ count, int_ step, int_ n,
      int_ i = n + start,
      int_ e = i + (count - 1) * step + 1,
      int_ ii
        = e <= 0
        ? -1
        : i < 0
        ? -i % step
        : i,
      int_ ri
        = e <= 0 || n <= ii
        ? -1
        : n - (n < e ? (n - 1 - ii) / step * step + ii + 1 : e)
    >
    using negative_strided_slice_dispatch = strided_slice_impl<
      ri == -1 ? -1 : ii,
      ri
    >;

    // pre: i >= 0
    // pre: count > 0
    // pre: step > 0
    template<int_ i, int_ count, int_ step,
      int_ e = i + (count - 1) * step + 1
    >
    using positive_strided_slice_dispatch = positive_strided_slice_impl<
      e <= 0 ? -1 : i < 0 ? -i % step : i,
      e <= 0 ? -1 : e
    >;

    // pre: start < 0
    // pre: count > 0
    // pre: n >= 0
    template<class C, int_ start, int_ count, int_ n,
      int_ e = n + start + count,
      int_ i
        = e <= 0
        ? -1
        : n < -start
        ? 0
        : n + start,
      int_ ri
        = e <= 0 || n <= i
        ? -1
        : n < e
        ? 0
        : n - e
    >
    using negative_slice_dispatch = slice_impl<
      C,
      ri == -1 ? -1 : i,
      ri
    >;

    // pre: i >= 0
    // pre: count > 0
    // pre: n >= 0
    template<class C, int_ i, int_ count, int_ e = i + count>
    using positive_slice_dispatch = positive_slice_impl<
      C,
      e <= 0 ? -1 : i < 0 ? 0 : i,
      e <= 0 ? -1 : e
    >;
  } // namespace jln::mp::detail
  /// \endcond


  /// \ingroup list

  /// Returns a subset of elements in a \c xs picked at regular intervals in range.
  /// A negative start represents an index starting from the end.
  /// \pre `0 < step || count == 0`
  /// \treturn \sequence
  template<int_ start, unsigned count, unsigned step = 1, class C = listify>
  struct strided_slice_c
    : detail::negative_strided_slice_select<start < 0>
    ::template impl<start, count, step, C>
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f;
#endif
  };

  template<class start, class count, class step = number<1>, class C = listify>
  using strided_slice = strided_slice_c<start::value, count::value, step::value, C>;

  template<int_ start, unsigned count, class C = listify>
  using slice_c = strided_slice_c<start, count, 1, C>;

  template<class start, class count, class C = listify>
  using slice = strided_slice_c<start::value, count::value, 1, C>;

  namespace emp
  {
    template<class L, class start, class count, class step = number<1>, class C = mp::listify>
    using strided_slice = unpack<L, strided_slice<start, count, step, C>>;

    template<class L, int_ start, unsigned count, unsigned step = 1, class C = mp::listify>
    using strided_slice_c = unpack<L, mp::strided_slice_c<start, count, step, C>>;

    template<class L, class start, class count, class C = mp::listify>
    using slice = unpack<L, mp::strided_slice_c<start::value, count::value, 1, C>>;

    template<class L, int_ start, unsigned count, class C = mp::listify>
    using slice_c = unpack<L, mp::strided_slice_c<start, count, 1, C>>;
  }
}



/// \cond
namespace jln::mp
{
  template<int_ start, unsigned count, class C>
  struct strided_slice_c<start, count, 1, C>
    : detail::negative_slice_select<start < 0>
    ::template impl<start, count, C>
  {};

  template<int_ start, unsigned step, class C>
  struct strided_slice_c<start, 0, step, C> : clear<C>
  {};

  // invalid
  template<int_ start, unsigned count, class C>
  struct strided_slice_c<start, count, 0, C>
  {};

  template<int_ start, class C>
  struct strided_slice_c<start, 0, 0, C> : clear<C>
  {};

  template<int_ start, class C>
  struct strided_slice_c<start, 0, 1, C> : clear<C>
  {};
}// namespace jln::mp

namespace jln::mp::detail
{
  template<>
  struct negative_slice_select<true>
  {
    template<int_ start, unsigned count, class C>
    struct impl
    {
      template<class... xs>
      using f = typename negative_slice_dispatch<C, start, count,
        static_cast<int_>(sizeof...(xs)) // cast is necessary for nvcc (tested with V12.3.52)
      >::template f<xs...>;
    };
  };

  template<>
  struct negative_slice_select<false>
  {
    template<int_ start, unsigned count, class C>
    struct impl
    {
      template<class... xs>
      using f = typename positive_slice_dispatch<C, start, count>
        ::template f<sizeof...(xs)>
        ::template f<xs...>;
    };
  };


  template<class C>
  struct positive_slice_impl<C, -1, -1>
  {
    template<int_ /*n*/>
    using f = clear<C>;
  };

  template<class C, int_ i, int_ e>
  struct positive_slice_impl
  {
    template<int_ n, int_ ri = n <= i ? -1 : n < e ? 0 : n - e>
    using f = slice_impl<C, ri == -1 ? -1 : i, ri>;
  };


  template<class C>
  struct slice_impl<C, -1, -1> : clear<C>
  {};

  template<class C, int_ i>
  struct slice_impl<C, i, 0> : drop_front_c<i, C>
  {};

  template<class C>
  struct slice_impl<C, 0, 0> : C
  {};

  template<class C, int_ i, int_ ri>
  struct slice_impl : rotate_c<-ri, drop_front_c<i + ri, C>>
  {};


  template<>
  struct negative_strided_slice_select<true>
  {
    template<int_ start, unsigned count, unsigned step, class C>
    struct impl
    {
      template<class... xs>
      using f = typename negative_strided_slice_dispatch<start, count, step,
        static_cast<int_>(sizeof...(xs)) // cast is necessary for nvcc (tested with V12.3.52)
      >
        ::template impl<C, step, sizeof...(xs)>
        ::template f<xs...>;
    };
  };

  template<>
  struct negative_strided_slice_select<false>
  {
    template<int_ start, unsigned count, unsigned step, class C>
    struct impl
    {
      template<class... xs>
      using f = typename positive_strided_slice_dispatch<start, count, step>
        ::template impl<C, step, sizeof...(xs)>
        ::template f<xs...>;
    };
  };


  template<>
  struct positive_strided_slice_impl<-1, -1>
  {
    // = 0 to be usable in range.hpp
    template<class C, unsigned /*step*/ = 0, int_ /*n*/ = 0>
    using impl = clear<C>;
  };

  template<int_ i, int_ e>
  struct positive_strided_slice_impl
  {
    template<class C, unsigned step, int_ n,
      int_ ri = n <= i ? -1 : n - (n < e ? (n - 1 - i) / step * step + i + 1 : e)>
    using impl = typename strided_slice_impl<ri == -1 ? -1 : i, ri>
      ::template impl<C, step, n>;
  };


  template<>
  struct strided_slice_impl<-1, -1> : positive_strided_slice_impl<-1, -1>
  {};

  template<class, unsigned... ints>
  struct slided_slice
  {
    template<class C, unsigned step>
    struct impl : compress_c_with<C, ints % step == 0 ...>
    {};
  };

  template<int_ i>
  struct strided_slice_impl<i, 0>
  {
    template<class C, unsigned step, std::size_t n>
    using impl = drop_front_c<i,
      typename JLN_MP_MAKE_UNSIGNED_SEQUENCE(n - i, slided_slice)
      ::template impl<C, step>
    >;
  };

  template<int_ i, int_ ri>
  struct strided_slice_impl
  {
    template<class C, unsigned step, std::size_t n>
    using impl = rotate_c<-ri, drop_front_c<i + ri,
      typename JLN_MP_MAKE_UNSIGNED_SEQUENCE(n - i - ri, slided_slice)
      ::template impl<C, step>
    >>;
  };
} // namespace jln::mp::detail
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    constexpr int_ sliding_stride(int_ size, int_ stride);

    template<int_ size, int_ stride>
    struct mk_sliding;
  }
  /// \endcond

  /// \ingroup list

  /// Returns sliding windows of width \c size.
  /// \pre `stride != 0`
  /// \pre `size >= 0`
  /// \treturn \sequence of \list
  /// Given a sequence and a count n, place a window over the first n elements of the underlying range.
  /// Return the contents of that window as the first element of the adapted range,
  /// then slide the window forward one element at a time until hitting the end of the underlying range.
  /// \semantics
  ///   If `stride < 0`, then `stride = stride + size`
  ///   If `sizeof...(xs) < size`, then `f = C::f<xs...>`
  ///   If `stride > 1`, the last window may be smaller than \c size
  ///   If `stride == 0 || size <= 0`, then the result sequence is empty
  ///   \code
  ///   strided_sliding_with_c<3, 1, F, C>::f<_0, _1, _2, _3, _4>
  ///   ==
  ///   C::f<F::f<_0, _1, _2>, F::f<_1, _2, _3>, F::f<_2, _3, _4>>
  ///
  ///   strided_sliding_with_c<3, 2, F, C>::f<_0, _1, _2, _3, _4>
  ///   ==
  ///   C::f<F::f<_0, _1, _2>, F::f<_2, _3, _4>>
  ///   \endcode
  template<int_ size, int_ stride = 1, class F = listify, class C = listify>
  using strided_sliding_with_c = typename detail::mk_sliding<size,
    detail::sliding_stride(size, stride)
  >::template f<C, F>;

  template<class size, class stride = number<1>, class F = listify, class C = listify>
  using strided_sliding_with = strided_sliding_with_c<size::value, stride::value, F, C>;

  template<class size, class stride = number<1>, class C = listify>
  using strided_sliding = strided_sliding_with_c<size::value, stride::value, listify, C>;

  template<int_ size, int_ stride = 1, class C = listify>
  using strided_sliding_c = strided_sliding_with_c<size, stride, listify, C>;

  template<class size, class F = listify, class C = listify>
  using sliding_with = strided_sliding_with_c<size::value, 1, F, C>;

  template<int_ size, class F = listify, class C = listify>
  using sliding_with_c = strided_sliding_with_c<size, 1, F, C>;

  template<class size, class C = listify>
  using sliding = strided_sliding_with_c<size::value, 1, listify, C>;

  template<int_ size, class C = listify>
  using sliding_c = strided_sliding_with_c<size, 1, listify, C>;


  namespace emp
  {
    template<class L, class size, class stride = number<1>, class F = listify, class C = mp::listify>
    using strided_sliding_with = unpack<L, mp::strided_sliding_with_c<size::value, stride::value, F, C>>;

    template<class L, int_ size, int_ stride = 1, class F = listify, class C = mp::listify>
    using strided_sliding_with_c = unpack<L, mp::strided_sliding_with_c<size, stride, F, C>>;

    template<class L, class size, class stride = number<1>, class C = mp::listify>
    using strided_sliding = unpack<L, mp::strided_sliding_with_c<size::value, stride::value, listify, C>>;

    template<class L, int_ size, int_ stride = 1, class C = mp::listify>
    using strided_sliding_c = unpack<L, mp::strided_sliding_with_c<size, stride, listify, C>>;

    template<class L, class size, class F = listify, class C = mp::listify>
    using sliding_with = unpack<L, mp::strided_sliding_with_c<size::value, 1, F, C>>;

    template<class L, int_ size, class F = listify, class C = mp::listify>
    using sliding_with_c = unpack<L, mp::strided_sliding_with_c<size, 1, F, C>>;

    template<class L, class size, class C = mp::listify>
    using sliding = unpack<L, mp::strided_sliding_with_c<size::value, 1, listify, C>>;

    template<class L, int_ size, class C = mp::listify>
    using sliding_c = unpack<L, mp::strided_sliding_with_c<size, 1, listify, C>>;
  }
}



/// \cond
namespace jln::mp::detail
{
  constexpr int_ sliding_stride(int_ size, int_ stride)
  {
    if (!stride || size < 1) {
      return -1;
    }

    if (stride < 0) {
      stride += size;
      if (stride <= 0) {
        return -1;
      }
    }

    return stride;
  }

  template<int>
  struct sliding_impl;

  constexpr int sliding_select(int n, int_ size, int_ stride);

  template<int_ size, int_ stride, class F, class C>
  struct sliding_
  {
    template<class... xs>
    using f = typename detail::sliding_impl<detail::sliding_select(
      sizeof...(xs), size, stride)
    >::template f<C, F, size, stride, xs...>;
  };

  // size == 1 ; stride != 1
  template<int_ stride, class F, class C>
  struct sliding_<1, stride, F, C>
  {
    template<class... xs>
    using f = typename detail::sliding_impl<sizeof...(xs) ? 3 : 0>
      ::template f<C, F, 1, stride, xs...>;
  };

  template<int_ size, int_ stride>
  struct mk_sliding
  {
    template<class C, class F>
    using f = sliding_<size, stride, F, C>;
  };

  template<class C>
  struct sliding_0
    : call_trace_xs_0<C>
  {};

  template<int_ size>
  struct mk_sliding<size, -1>
  {
    template<class C, class F>
    using f = sliding_0<C>;
  };

  template<>
  struct mk_sliding<1, 1>
  {
    template<class C, class F>
    using f = transform<F, C>;
  };

  constexpr int sliding_select(int n, int_ size, int_ stride)
  {
    return n <= size ? (n ? 1 : 0)         // C<list<xs...>>
      : stride > n ? 9                     // take_front_max
      : stride == 1 ? (size == 2 ? 4 : size < 9 ? 5 : 51)  // common case
      : stride == size ? (n % size ? 61 : 6)  // batched
      // slice<zip_longest> / slice<zip>
      : (stride >= size ? (n - 1) % stride >= size - 1 : (n - size) % stride == 0) ? 7 : 8;
  }


  // sizeof...(xs) == 0
  template<>
  struct sliding_impl<0>
  {
    template<class C, class F, int_, int_, class...>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };


  // sizeof...(xs) <= size
  template<>
  struct sliding_impl<1>
  {
    template<class C, class F, int_, int_, class... xs>
    using f = JLN_MP_CALL_TRACE(C, typename JLN_MP_TRACE_F(F)::template f<xs...>);
  };


  // size == 1 ; stride != 1
  template<>
  struct sliding_impl<3>
  {
    template<class C, class F, int_, int_ stride, class... xs>
    using f = typename strided_slice_impl<0, (sizeof...(xs) - 1) % stride>
      ::template impl<transform<F, C>, stride, sizeof...(xs)>
      ::template f<xs...>;
  };


  // stride > size  (take_front_max)
  template<>
  struct sliding_impl<9>
  {
    template<class C, class F, int_ size, int_ stride, class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename conditional_c<sizeof...(xs) <= size>
      ::template f<JLN_MP_TRACE_F(F), take_front_c<static_cast<unsigned>(size), F>>
      ::template f<xs...>
    );
  };


  // size == 2 ; stride == 1  (pairwise)
  template<>
  struct sliding_impl<4>
  {
    template<class C, class F, int_, int_, class... xs>
    using f = typename pairwise_with<F, C>::template f<xs...>;
  };


  // 2 < size < 9 ; stride == 1
  template<class, int_... i>
  struct sliding5_impl
  {
    template<class C, class F, int_ size, class drop_front>
    using impl = _tee<zip_with<F, C>,
      rotate_c<i-size, drop_front>...,
      drop_front
    >;
  };


  // size > 2 ; stride == 1
  template<>
  struct sliding_impl<5>
  {
    template<class C, class F, int_ size, int_, class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(size-1, sliding5_impl)
      ::template impl<C, F, size-1, drop_front_c<size-1>>
      ::template f<xs...>;
  };


  template<class, int... ns>
  struct sliding_inner
  {
    template<class C, class Indexed, int i>
    using f = typename C::template f<typename JLN_MP_D_INDEXED_GET(ns+i, Indexed)...>;
  };

  template<class, int... outer_index>
  struct sliding_outer
  {
      template<class F, class C, class InnerC, class Indexed>
      using f = typename C::template f<typename F::template f<InnerC, Indexed, outer_index>...>;
  };

  template<int_ n>
  using make_sliding_inner = JLN_MP_MAKE_INTEGER_SEQUENCE_T(int, n, sliding_inner);

  template<int_ n>
  using make_sliding_outer = JLN_MP_MAKE_INTEGER_SEQUENCE_T(int, n, sliding_outer);

  // size > 8 ; stride == 1
  template<>
  struct sliding_impl<51>
  {
    template<class C, class F, int_ size, int_ /*stride*/, class... xs>
    using f = typename make_sliding_outer<sizeof...(xs) - size + 1>
      ::template f<
        make_sliding_inner<size>,
        JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F),
        build_indexed_v<xs...>
      >;
  };


  template<class, int... outer_index>
  struct strided_sliding_outer
  {
    template<int d>
    struct strided
      : sliding_outer<int, outer_index * d...>
    {};
  };

  template<int_ n, int_ stride>
  using make_strided_sliding_outer
    = typename JLN_MP_MAKE_INTEGER_SEQUENCE_T(int, n, strided_sliding_outer)
      ::template strided<stride>;


  // stride == size  (batched) (all list == size)
  template<>
  struct sliding_impl<6>
  {
    template<class C, class F, int_ size, int_ /*stride*/, class... xs>
    using f = typename make_strided_sliding_outer<sizeof...(xs) / size, size>
      ::template f<
        make_sliding_inner<size>,
        JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F),
        build_indexed_v<xs...>
      >;
  };


  // stride == size  (batched) (last list < size)
  template<>
  struct sliding_impl<61>
  {
    template<class C, class F, int_ size, int_ n, class Indexed>
    using impl = typename join<C>::template f<
      typename make_strided_sliding_outer<n / size, size>
        ::template f<make_sliding_inner<size>, listify, F, Indexed>,
      list<typename make_sliding_inner<n % size>
        ::template f<F, Indexed, n / size * size>>
    >;

    template<class C, class F, int_ size, int_ /*stride*/, class... xs>
    using f = impl<
      JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F),
      size, sizeof...(xs), build_indexed_v<xs...>
    >;
  };


  // size > 1 ; stride > 1  (all list = size)
  template<>
  struct sliding_impl<7>
  {
    template<class C, class F, int_ size, int_ stride, class... xs>
    using f = typename make_strided_sliding_outer<(sizeof...(xs) - size) / stride + 1, stride>
      ::template f<
        make_sliding_inner<size>,
        JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F),
        build_indexed_v<xs...>
      >;
  };


  // size > 1 ; stride > 1  (last list < size)
  template<>
  struct sliding_impl<8>
  {
    template<class C, class F, int_ size, int_ stride, int_ ns, class Indexed,
      int_ n = (ns - size) / stride + 1>
    using impl = typename join<C>::template f<
      typename make_strided_sliding_outer<n, stride>
        ::template f<make_sliding_inner<size>, listify, F, Indexed>,
      list<typename make_sliding_inner<ns - n * stride>
        ::template f<F, Indexed, n * stride>>
    >;

    template<class C, class F, int_ size, int_ stride, class... xs>
    using f = impl<
      JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F),
      size, stride, sizeof...(xs), build_indexed_v<xs...>
    >;
  };
}
/// \endcond


namespace jln::mp
{
  /// \ingroup group

  /// Splits a sequence by arbitrary size group.
  /// \post If `size <= 0`, then the result sequence is empty
  /// \semantics
  ///   \code
  ///   batched_c<2>::f<
  ///     void, void, int, void, void
  ///   > = list<
  ///     list<void, void>,
  ///     list<int, void>,
  ///     list<void>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<int_ size, class F = listify, class C = listify>
  using batched_with_c = strided_sliding_with_c<size, size, F, C>;

  template<int_ size, class C = listify>
  using batched_c = strided_sliding_with_c<size, size, listify, C>;

  template<class size, class F = listify, class C = listify>
  using batched_with = strided_sliding_with_c<size::value, size::value, F, C>;

  template<class size, class C = listify>
  using batched = strided_sliding_with_c<size::value, size::value, listify, C>;

  namespace emp
  {
    template<class L, class size, class F = mp::listify, class C = mp::listify>
    using batched_with = unpack<L, mp::strided_sliding_with_c<size::value, size::value, F, C>>;

    template<class L, int_ size, class F = mp::listify, class C = mp::listify>
    using batched_with_c = unpack<L, mp::strided_sliding_with_c<size, size, F, C>>;

    template<class L, class size, class C = mp::listify>
    using batched = unpack<L, mp::strided_sliding_with_c<size::value, size::value, mp::listify, C>>;

    template<class L, int_ size, class C = mp::listify>
    using batched_c = unpack<L, mp::strided_sliding_with_c<size, size, mp::listify, C>>;
  }
}

namespace jln::mp
{
  /// \ingroup search

  /// Extract the first elements of a \sequence that does not satisfy a \predicate.
  /// When an element satisfy the predicate,
  /// call \c TC with it and those before it.
  /// Otherwise \c FC is called on the whole sequence.
  /// \treturn \sequence
  /// \see take_front, take_back, take_until_xs
  /// \see drop_until, drop_until_xs
  /// \see search, partial_search
  template<class Pred, class TC = listify, class FC = TC>
  struct take_until
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  /// Extract the first plus at most \c ExtendedByN elements of a \sequence that does not satisfy a \predicate.
  /// When an element satisfy the predicate,
  /// call \c TC with it and those before it plus at most \c ExtendedByN.
  /// Otherwise \c FC is called on the whole sequence.
  /// \semantics
  ///   \code
  ///   call<take_until_extended_by_n_c<2, is<number<2>>>,
  ///     number<0>, number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   //  predicate not satisfied ^ (+1)   ^ +2
  ///   ==
  ///   list<number<0>, number<1>, number<2>, number<3>>
  ///
  ///   call<take_until_extended_by_n_c<2, is<number<5>>>,
  ///     number<0>, number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   //                                   predicate not satisfied ^ (+1)
  ///   ==
  ///   list<number<0>, number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   \endcode
  /// \treturn \sequence
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  struct take_until_extended_by_n_c
  {
    template<class... xs>
    using f = typename detail::take_while_extended_by_n_impl<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using take_until_extended_by_n = take_until_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_inclusive_until = take_until_extended_by_n_c<1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_until = unpack<L, mp::take_until<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_inclusive_until = unpack<L, mp::take_until_extended_by_n_c<1, Pred, TC, FC>>;

    template<class ExtendedByN, class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_until_extended_by_n
      = unpack<L, mp::take_until_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>>;

    template<std::size_t ExtendedByN,
             class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_until_extended_by_n_c
      = unpack<L, mp::take_until_extended_by_n_c<ExtendedByN, Pred, TC, FC>>;
  }
}

namespace jln::mp
{
  /// \ingroup search

  /// Extracts the first elements of a \sequence that does not satisfy a \predicate.
  /// \treturn \sequence
  /// \see take_front, take_back, take_until, partial_take_until_xs
  /// \see drop_until, drop_until_xs
  /// \see search
  template<class Pred, class TC = listify, class FC = TC>
  struct take_until_xs
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::_drop_until_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  /// Same as \c take_until_extended_by_n_c, but for \c take_until_xs.
  /// \treturn \sequence
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  struct take_until_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::take_while_extended_by_n_impl<
      typename detail::_drop_until_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using take_until_extended_by_n_xs = take_until_extended_by_n_xs_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_inclusive_until_xs = take_until_extended_by_n_xs_c<1, Pred, TC, FC>;

  /// Same as \c take_until_extended_by_n_xs_c, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_until, drop_until_xs
  /// \see take_until, take_until_xs
  /// \see search, partial_search
  template<int_ OffsetEnd, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  struct partial_take_until_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::take_while_extended_by_n_impl<
      typename detail::drop_until_xs_call<
        detail::partial_drop_while_xs_size(OffsetEnd, sizeof...(xs)),
        JLN_MP_TRACE_F(Pred), xs...
      >
    >::template f<ExtendedByN, TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_until_xs =
    partial_take_until_extended_by_n_xs_c<OffsetEnd::value, 0, Pred, TC, FC>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_until_xs_c =
    partial_take_until_extended_by_n_xs_c<OffsetEnd, 0, Pred, TC, FC>;

  template<class OffsetEnd, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_take_until_extended_by_n_xs =
    partial_take_until_extended_by_n_xs_c<OffsetEnd::value, ExtendedByN::value, Pred, TC, FC>;

  template<std::size_t OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_inclusive_until_xs_c =
    partial_take_until_extended_by_n_xs_c<OffsetEnd, 1, Pred, TC, FC>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_inclusive_until_xs =
    partial_take_until_extended_by_n_xs_c<OffsetEnd::value, 1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using take_until_xs = unpack<L, mp::take_until_xs<Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred, class TC = mp::listify, class FC = TC>
    using take_until_extended_by_n_xs = unpack<L,
      mp::take_until_extended_by_n_xs<ExtendedByN, Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = mp::listify, class FC = TC>
    using take_until_extended_by_n_xs_c = unpack<L,
      mp::take_until_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred, class TC = mp::listify, class FC = TC>
    using partial_take_until_xs = unpack<L,
      mp::partial_take_until_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred, class TC = mp::listify, class FC = TC>
    using partial_take_until_xs_c = unpack<L,
      mp::partial_take_until_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using take_inclusive_until_xs = unpack<L, mp::take_inclusive_until_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred,
             class TC = mp::listify, class FC = TC>
    using partial_take_inclusive_until_xs = unpack<L,
      mp::partial_take_inclusive_until_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred,
             class TC = mp::listify, class FC = TC>
    using partial_take_inclusive_until_xs_c = unpack<L,
      mp::partial_take_inclusive_until_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class OffsetEnd, class ExtendedByN, class Pred,
             class TC = listify, class FC = TC>
    using partial_take_until_extended_by_n_xs = unpack<L,
      mp::partial_take_until_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, std::size_t ExtendedByN, class Pred,
             class TC = listify, class FC = TC>
    using partial_take_until_extended_by_n_xs_c = unpack<L,
      mp::partial_take_until_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, FC>>;
  }
}

namespace jln::mp
{
  /// \ingroup search

  /// Find the \sequence before a sub-\sequence.
  /// Calls \c TC with all the elements before the sub-\sequence found.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search, search_before
  template<class Seq, class TC = listify, class FC = clear<TC>>
  struct before
  {};

  template<class... Ts, class TC, class FC>
  struct before<list<Ts...>, TC, FC>
  : partial_take_until_xs_c<-int_(sizeof...(Ts)),
                            starts_with<list<Ts...>>,
                            TC, FC>
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f;
#endif
  };

  namespace emp
  {
    template<class L, class Seq, class TC = mp::listify, class FC = mp::clear<TC>>
    using before = unpack<L, mp::before<Seq, TC, FC>>;
  }

  /// \cond
  template<class T, class TC, class FC>
  struct before<list<T>, TC, FC>
  : take_until<is<T>, TC, FC>
  {};

  template<class TC, class FC>
  struct before<list<>, TC, FC>
  : detail::call_trace_xs_0<TC>
  {};
  /// \endcond
}

namespace jln::mp
{
  /// \ingroup functional

  /// Invokes twice.
  /// \treturn \value
  template<class F>
  struct invoke_twice
  {
    template<class... xs>
    using f = JLN_MP_TRACE_TYPENAME JLN_MP_TRACE_F(JLN_MP_DCALL_TRACE_XS(xs, F, xs...))
      ::template f<xs...>;
  };
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<std::size_t n, class SubC1, class SubC2, class C>
    struct before_after_defer_i;
  }
  /// \endcond

  /// \ingroup search

  /// Find the \sequences before and after a sub-\sequence.
  /// Calls \c TC with result of \c SubC1 and \c SubC2 called
  /// respectively with the sequences before and after the one found.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search, search_before
  template<
    class Seq,
    class SubC1 = listify, class SubC2 = SubC1,
    class TC = listify, class FC = clear<TC>>
  struct before_after_with
  {};

  template<class Seq, class TC = listify, class FC = clear<TC>>
  using before_after = before_after_with<Seq, listify, listify, TC, FC>;

  template<class... Ts, class SubC1, class SubC2, class TC, class FC>
  struct before_after_with<list<Ts...>, SubC1, SubC2, TC, FC>
  : invoke_twice<index_if_xs<starts_with<list<Ts...>>,
                             detail::before_after_defer_i<sizeof...(Ts), SubC1, SubC2, TC>,
                             mp::always<FC>>>
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f;
#endif
  };

  namespace emp
  {
    template<class L, class Seq, class TC = mp::listify, class FC = mp::clear<TC>>
    using before_after = unpack<L, mp::before_after<Seq, TC, FC>>;

    template<class L, class Seq,
             class SubC1 = mp::listify, class SubC2 = SubC1,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using before_after_with = unpack<L, mp::before_after_with<Seq, SubC1, SubC2, TC, FC>>;
  }

  /// \cond
  template<class T, class SubC1, class SubC2, class TC, class FC>
  struct before_after_with<list<T>, SubC1, SubC2, TC, FC>
  : invoke_twice<index_if<is<T>,
                          detail::before_after_defer_i<1, SubC1, SubC2, TC>,
                          mp::always<FC>>>
  {};

  template<class SubC1, class SubC2, class TC, class FC>
  struct before_after_with<list<>, SubC1, SubC2, TC, FC>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(TC,
      JLN_MP_DCALL_TRACE_XS_0(xs, SubC1),
      JLN_MP_DCALL_TRACE_XS(xs, SubC2, xs...)
    );
  };
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template<std::size_t n, class SubC1, class SubC2, class C>
  struct before_after_defer_i
  {
    template<class I>
    using f = tee<take_front<I, SubC1>, drop_front_c<I::value + n, SubC2>, C>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, class F>
    struct circulant_matrix_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// square matrix in which all row vectors are composed of the
  /// same elements and each row vector is rotated one element to
  /// the right relative to the preceding row vector.
  /// \semantics
  ///   \code
  ///   circulant_matrix_with<>::f<a, b, c, d>
  ///   == list<
  ///     list<a, b, c, d>,
  ///     list<d, a, b, c>,
  ///     list<c, d, a, b>,
  ///     list<b, c, d, a>
  ///   >
  ///   \endcode
  /// \treturn \value
  /// \see anticirculant_matrix
  template<class F = listify, class C = listify>
  struct circulant_matrix_with
  {
    template<class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(
      sizeof...(xs), detail::circulant_matrix_impl<C, F>::template impl
    )::template f<xs...>;
  };

  template<class C = listify>
  using circulant_matrix = circulant_matrix_with<listify, C>;

  namespace emp
  {
    template<class L, class F, class C = mp::listify>
    using circulant_matrix_with = unpack<L, mp::circulant_matrix_with<F, C>>;

    template<class L, class C = mp::listify>
    using circulant_matrix = unpack<L, mp::circulant_matrix<C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class C, class F>
  struct circulant_matrix_impl
  {
    template<class, int_... i>
    struct impl : _tee<C, rotate_c<-i, F>...>
    {};
  };
}
/// \endcond


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class MkIndexesInt2>
    struct array_int2_index_dispatcher;

    template<bool... bs>
    struct mk_split_indexes;
  }
  /// \endcond

  /// \ingroup group

  /// Splits a \sequence into multiple \lists at every point that satisfy a predicate.
  /// The separator value is removed.
  /// \semantics
  ///   \code
  ///   split_if<is<_0>>::f<_0, _1, _2, _0, _3>
  ///   == list<
  ///     list<>,
  ///     list<_1, _2>,
  ///     list<_3>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  /// \see split_before_if, split_after_if
  template<class Pred = identity, class F = listify, class C = listify>
  struct split_if_with
  {
    template<class... xs>
    using f = typename detail::array_int2_index_dispatcher<
      detail::mk_split_indexes<JLN_MP_RAW_EXPR_TO_BOOL(
        JLN_MP_TRACE_F(Pred)::template f<xs>::value
      )...>
    >::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F), build_indexed_v<xs...>>;
  };

  template<class Pred = identity, class C = listify>
  using split_if = split_if_with<Pred, listify, C>;

  template<class x, class F = listify, class C = listify>
  using split_with = split_if_with<is<x>, F, C>;

  template<class x, class C = listify>
  using split = split_if_with<is<x>, listify, C>;

  namespace emp
  {
    template<class L, class Pred = mp::identity, class F = listify, class C = listify>
    using split_if_with = unpack<L, mp::split_if_with<Pred, F, C>>;

    template<class L, class Pred = mp::identity, class C = listify>
    using split_if = unpack<L, mp::split_if_with<Pred, listify, C>>;

    template<class L, class x, class F = listify, class C = listify>
    using split_with = unpack<L, mp::split_if_with<is<x>, F, C>>;

    template<class L, class x, class C = listify>
    using split = unpack<L, mp::split_if_with<is<x>, listify, C>>;
  }
}


/// \cond

namespace jln::mp
{
  template<class T, class F, class C>
  struct split_if_with<is<T>, F, C>
  {
    template<class... xs>
    using f = typename detail::array_int2_index_dispatcher<
      detail::mk_split_indexes<JLN_MP_IS_SAME(T, xs)...>
    >::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F), build_indexed_v<xs...>>;
  };
}

namespace jln::mp::detail
{
  template<std::size_t N>
  struct array_int2
  {
    // index and size
    int elems[N][2];
  };

  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_IGNORE_UNSAFE_BUFFER_USAGE()
  template<bool... bs>
  struct mk_split_indexes
  {
    static constexpr std::size_t result_len = (1 + ... + bs);

    static constexpr auto make()
    {
      array_int2<result_len> a{};
      int i = 0;
      int n = 0;

      bool bools[] {bs...};
      for (bool b : bools)
      {
        ++i;
        if (b)
          a.elems[++n][0] = i;
        else
          ++a.elems[n][1];
      }

      return a;
    }
  };
  JLN_MP_DIAGNOSTIC_POP()

  template<>
  struct mk_split_indexes<>
  {
    static constexpr std::size_t result_len = 0;

    static constexpr int make()
    {
      return 0;
    }
  };

  template<class, class...>
  struct dispatch_group_index;

  template<int... outer_index, class... Inner>
  struct dispatch_group_index<sliding_outer<int, outer_index...>, Inner...>
  {
    template<class C, class InnerC, class Indexed>
    using f = typename C::template f<
      typename Inner::template f<InnerC, Indexed, outer_index>...
    >;
  };

#if __cplusplus >= 202002L && __cpp_nontype_template_args >= 201911L
  #define JLN_MP_INDEXES_TPL_PARAM() auto indexes_pairs
  #define JLN_MP_INDEXES_TPL_VALUE() MkIndexesInt2::make()
  #if JLN_MP_MSVC
    #define JLN_MP_INDEXES_GET_PAIR(i) indexes_pair_v<indexes_pairs, i>
    template<auto a, int i>
    inline constexpr auto indexes_pair_v = a.elems[i];
  #else
    #define JLN_MP_INDEXES_GET_PAIR(i) indexes_pairs.elems[i]
  #endif
#else
  template<class T>
  inline constexpr auto memoize_make_fn = T::make();
  #define JLN_MP_INDEXES_TPL_PARAM() class MkIndexesInt2
  #define JLN_MP_INDEXES_TPL_VALUE() MkIndexesInt2
  #if JLN_MP_MSVC
    #define JLN_MP_INDEXES_GET_PAIR(i) indexes_pair_v<MkIndexesInt2, i>
    template<class MkIndexesInt2, int i>
    inline constexpr auto indexes_pair_v = memoize_make_fn<MkIndexesInt2>.elems[i];
  #else
    #define JLN_MP_INDEXES_GET_PAIR(i) memoize_make_fn<MkIndexesInt2>.elems[i]
  #endif
#endif

  template<class, int... i>
  struct array_int2_index_dispatcher_impl
  {
    template<JLN_MP_INDEXES_TPL_PARAM()>
    using f = dispatch_group_index<
      sliding_outer<int, JLN_MP_INDEXES_GET_PAIR(i)[0]...>,
#if JLN_MP_MEMOIZED_ALIAS || (JLN_MP_CUDA && JLN_MP_HOST_COMPILER_GCC)
      make_sliding_inner<JLN_MP_INDEXES_GET_PAIR(i)[1]>...
#else
      JLN_MP_MAKE_INTEGER_SEQUENCE_T(int, JLN_MP_INDEXES_GET_PAIR(i)[1], sliding_inner)...
#endif
    >;
  };

  template<class MkIndexesInt2>
  struct array_int2_index_dispatcher
    : JLN_MP_MAKE_INTEGER_SEQUENCE_T(int,
        MkIndexesInt2::result_len,
        array_int2_index_dispatcher_impl
      )
      ::template f<JLN_MP_INDEXES_TPL_VALUE()>
  {};

#undef JLN_MP_INDEXES_GET_PAIR
#undef JLN_MP_INDEXES_TPL_PARAM
#undef JLN_MP_INDEXES_TPL_VALUE
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool... bs>
    struct mk_split_before_indexes;
  }
  /// \endcond

  /// \ingroup group

  /// Splits a \sequence into multiple \lists at every point that satisfy a predicate.
  /// The separator value is inserted at the beginning of the following list.
  /// \semantics
  ///   \code
  ///   split_before_if<is<_0>>::f<_0, _1, _2, _0, _3>
  ///   == list<
  ///     list<>,
  ///     list<_0, _1, _2>,
  ///     list<_0, _3>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  /// \see split_if, split_after_if
  template<class Pred, class F = listify, class C = listify>
  struct split_before_if_with
  {
    template<class... xs>
    using f = typename detail::array_int2_index_dispatcher<
      detail::mk_split_before_indexes<JLN_MP_RAW_EXPR_TO_BOOL(
        JLN_MP_TRACE_F(Pred)::template f<xs>::value
      )...>
    >::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F), build_indexed_v<xs...>>;
  };

  template<class Pred = identity, class C = listify>
  using split_before_if = split_before_if_with<Pred, listify, C>;

  template<class x, class F = listify, class C = listify>
  using split_before_with = split_before_if_with<is<x>, F, C>;

  template<class x, class C = listify>
  using split_before = split_before_if_with<is<x>, listify, C>;

  namespace emp
  {
    template<class L, class Pred = mp::identity, class F = listify, class C = listify>
    using split_before_if_with = unpack<L, mp::split_before_if_with<Pred, F, C>>;

    template<class L, class Pred = mp::identity, class C = listify>
    using split_before_if = unpack<L, mp::split_before_if_with<Pred, listify, C>>;

    template<class L, class x, class F = listify, class C = listify>
    using split_before_with = unpack<L, mp::split_before_if_with<is<x>, F, C>>;

    template<class L, class x, class C = listify>
    using split_before = unpack<L, mp::split_before_if_with<is<x>, listify, C>>;
  }
}


/// \cond
namespace jln::mp
{
  template<class T, class F, class C>
  struct split_before_if_with<is<T>, F, C>
  {
    template<class... xs>
    using f = typename detail::array_int2_index_dispatcher<
      detail::mk_split_before_indexes<JLN_MP_IS_SAME(T, xs)...>
    >::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F), build_indexed_v<xs...>>;
  };
}

namespace jln::mp::detail
{
  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_IGNORE_UNSAFE_BUFFER_USAGE()
  template<bool... bs>
  struct mk_split_before_indexes
  {
    static constexpr std::size_t result_len = (1 + ... + bs);

    static constexpr auto make()
    {
      array_int2<result_len> a{};
      int i = 0;
      int n = 0;

      bool bools[] {bs...};
      for (bool b : bools)
      {
        if (b)
          a.elems[++n][0] = i;
        ++i;
        ++a.elems[n][1];
      }

      return a;
    }
  };
  JLN_MP_DIAGNOSTIC_POP()

  template<>
  struct mk_split_before_indexes<> : mk_split_indexes<>
  {};
}
/// \endcond


namespace jln::mp
{
  using is_na = is<na>;
  using violation = always<na>;

  /// \cond
  namespace detail
  {
    template<class x>
    struct try_dispatch;

#if JLN_MP_MEMOIZED_ALIAS && !JLN_MP_MSVC
    template<class, class, class = void>
    struct _try_impl;

#   define JLN_MP_CALL_TRY_IMPL(F, params) detail::_try_impl<F, list<params>>::type
#elif JLN_MP_CUDA
#   define JLN_MP_CALL_TRY_IMPL(F, params) detail::memoizer_impl<void, F, params>::try_type
#else
#   define JLN_MP_CALL_TRY_IMPL(F, params) detail::memoizer_impl<F, params>::try_type
#endif
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes \c TC::f<result> whether \c FC::f<xs...> is a valid expression
  /// other than \c na, otherwhise invokes \c FC::f<xs...>.
  /// \pre \c F::f<xs...> must be a SFINAE compatible expression
  /// \treturn \value
  template<class F, class TC = identity, class FC = violation>
  struct try_
  {
    template<class... xs>
    using f = typename detail::try_dispatch<
      typename JLN_MP_CALL_TRY_IMPL(F, xs...)
    >::template f<TC, FC, xs...>;
  };

  template<class F, class FC = always<false_>>
  using try_or = try_<F, identity, FC>;

  /// Checks whether \c F::f<xs...> is invocable.
  /// \pre \c F::f<xs...> must be a SFINAE compatible expression
  /// \treturn \bool
  template<class F, class C = identity>
  using is_invocable = try_<F, always<true_, C>, always<false_, C>>;

  /// Checks whether \c F::f<xs...> is not invocable.
  /// \pre \c F::f<xs...> must be a SFINAE compatible expression
  /// \treturn \bool
  template<class F, class C = identity>
  using is_not_invocable = try_<F, always<false_, C>, always<true_, C>>;

  namespace emp
  {
    template<class F, class TC, class FC, class... xs>
    using try_ = typename mp::try_<F, TC, FC>::template f<xs...>;

    template<class F, class FC, class... xs>
    using try_or = typename mp::try_<F, mp::identity, FC>::template f<xs...>;

    template<class F, class... xs>
    constexpr bool is_invocable_v = JLN_MP_RAW_EXPR_TO_BOOL_NOT(
      JLN_MP_IS_SAME(na, typename JLN_MP_CALL_TRY_IMPL(F, xs...)));

    template<class F, class... xs>
    constexpr bool is_not_invocable_v = !is_invocable_v<F, xs...>;

    template<class F, class... xs>
    using is_invocable = number<is_invocable_v<F, xs...>>;

    template<class F, class... xs>
    using is_not_invocable = number<!is_invocable_v<F, xs...>>;
  }
}


/// \cond
namespace jln::mp
{
  template<class F>
  struct try_<F, always<true_>, always<false_>>
  {
    template<class... xs>
    using f = number<emp::is_invocable_v<F, xs...>>;
  };

  template<class F>
  struct try_<F, always<false_>, always<true_>>
  {
    template<class... xs>
    using f = number<!emp::is_invocable_v<F, xs...>>;
  };

  template<class F>
  struct try_<F, identity, violation>
  {
    template<class... xs>
    using f = typename JLN_MP_CALL_TRY_IMPL(F, xs...);
  };
}

namespace jln::mp::detail
{
  template<class x>
  struct try_dispatch
  {
    template<class TC, class FC, class...>
    using f = JLN_MP_CALL_TRACE(TC, x);
  };

  template<>
  struct try_dispatch<na>
  {
    template<class TC, class FC, class... xs>
    using f = JLN_MP_CALL_TRACE(FC, xs...);
  };
}

#if JLN_MP_MEMOIZED_ALIAS && !JLN_MP_MSVC

namespace jln::mp::detail
{
  template<class, class, class>
  struct _try_impl
  {
    using type = na;
  };

  template<class F, class... xs>
  struct _try_impl<F, list<xs...>, std::void_t<typename F::template f<xs...>>>
  {
    using type = typename F::template f<xs...>;
  };
}
#endif

#undef JLN_MP_CALL_TRY_IMPL
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool... bs>
    struct mk_group_indexes;

    template<bool>
    struct group_impl;
  }
  /// \endcond

  /// \ingroup group

  /// Groups adjacent elements that respect a predicate.
  /// \semantics
  ///   \code
  ///   group_by<same<>>::f<void, void, int, void>
  ///   == list<
  ///     list<void, void>,
  ///     list<int>,
  ///     list<void>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  template<class Cmp, class F = listify, class C = listify>
  struct group_by_with
  {
    template<class... xs>
    using f = typename detail::group_impl<!sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(Cmp), xs...>
      ::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F), build_indexed_v<xs...>>;
  };

  template<class F = listify, class C = listify>
  using group_with = group_by_with<same<>, F, C>;

  template<class Cmp, class C = listify>
  using group_by = group_by_with<Cmp, listify, C>;

  template<class C = listify>
  using group = group_by_with<same<>, listify, C>;

  namespace emp
  {
    template<class L, class Cmp, class F = listify, class C = listify>
    using group_by_with = unpack<L, mp::group_by_with<Cmp, F, C>>;

    template<class L, class F = listify, class C = listify>
    using group_with = unpack<L, mp::group_by_with<mp::same<>, F, C>>;

    template<class L, class Cmp, class C = listify>
    using group_by = unpack<L, mp::group_by_with<Cmp, listify, C>>;

    template<class L, class C = listify>
    using group = unpack<L, mp::group_by_with<mp::same<>, listify, C>>;
  }
}


/// \cond

namespace jln::mp::detail
{
  template<class Cmp, class x, class ys, class... xs>
  struct mk_pairs_indexes;

  template<class Cmp, class x, class... ys, class... xs>
  struct mk_pairs_indexes<Cmp, x, list<ys...>, xs...>
    : array_int2_index_dispatcher<
      mk_split_before_indexes<
        false,
        JLN_MP_RAW_EXPR_TO_BOOL_NOT(Cmp::template f<ys, xs>::value)...
      >
    >
  {};

  template<class x, class... ys, class... xs>
  struct mk_pairs_indexes<same<>, x, list<ys...>, xs...>
    : array_int2_index_dispatcher<
      mk_split_before_indexes<
        false,
        JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_IS_SAME(ys, xs))...
      >
    >
  {};

  template<class... ys>
  struct smp_mk_pairs_indexes
  {
    template<class Cmp, class x, class... xs>
    using f = array_int2_index_dispatcher<
      mk_split_before_indexes<
        false,
        JLN_MP_RAW_EXPR_TO_BOOL_NOT(Cmp::template f<ys, xs>::value)...
      >
    >;
  };

  template<class Cmp, class TC, class FC, class x, class... ys, class... xs>
  struct mk_pairs_indexes<try_<Cmp, TC, FC>, x, list<ys...>, xs...>
    : try_<smp_mk_pairs_indexes<ys...>>
    ::template f<try_<Cmp, TC, FC>, x, xs...>
  {};

  // needed when JLN_MP_ENABLE_DEBUG is enabled
  template<class Cmp, class x, class... ys, class... xs>
  struct mk_pairs_indexes<memoize<Cmp>, x, list<ys...>, xs...>
    : try_<smp_mk_pairs_indexes<ys...>>
    ::template f<memoize<Cmp>, x, xs...>
  {};

  template<>
  struct group_impl<false>
  {
    template<class Cmp, class x, class... xs>
    using f = mk_pairs_indexes<
      JLN_MP_TRACE_F(Cmp),
      x,
      typename take_front_c<sizeof...(xs)>::template f<x, xs...>,
      xs...
    >;
  };

  template<>
  struct group_impl<true>
  {
    template<class Cmp, class... xs>
    using f = call_trace_c0_arg;
  };
}
/// \endcond

namespace jln::mp
{
  namespace jln::mp::detail
  {
    template<class C, class F, class Dispatcher>
    struct collapse_impl;
  }

  /// \ingroup group

  /// Groups adjacent elements by adjacent keys.
  /// \pre `sizeof...(keys)` == `sizeof...(xs)`
  /// \semantics
  ///   \code
  ///   collapse_for< 1,  1,  0,  0,  0,  1,  2,  2>
  ///            ::f<_0, _1, _2, _3, _4, _5, _6, _7>
  ///   ==
  ///   list<
  ///     list<_0, _1>,
  ///     list<_2, _3, _4>,
  ///     list<_5>,
  ///     list<_6, _7>
  ///   >
  ///   \endcode
  /// \note \c collapse<list<xs...>>::f<xs...> == \c group<>::f<xs...>
  /// \treturn \sequence
  template<class C, class F, class... keys>
  struct collapse2_with
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f;
#endif
  };

  template<class C, class F, int_... keys>
  using collapse2_with_c = collapse2_with<C, F, number<keys>...>;

  template<class C, int_... keys>
  using collapse2_c = collapse2_with<C, listify, number<keys>...>;

  template<class C, class... keys>
  using collapse2 = collapse2_with<C, listify, keys...>;


  template<class keys, class F = listify, class C = listify>
  using collapse_with = typename detail::_unpack<lift<collapse2_with>, keys, C, F>::type;

  template<class keys, class C = listify>
  using collapse = typename detail::_unpack<lift<collapse2_with>, keys, C, listify>::type;


  template<class... keys>
  using collapse_for = collapse2_with<listify, listify, keys...>;

  template<int_... keys>
  using collapse_for_c = collapse2_with<listify, listify, number<keys>...>;


  namespace emp
  {
    template<class L, class keys, class F = listify, class C = listify>
    using collapse_with = unpack<L, mp::collapse_with<keys, F, C>>;

    template<class L, class keys, class C = listify>
    using collapse = unpack<L, mp::collapse_with<keys, listify, C>>;

    template<class L, class... keys>
    using collapse_for = unpack<L, collapse2_with<listify, listify, keys...>>;

    template<class L, int_... keys>
    using collapse_for_c = unpack<L, collapse2_with<listify, listify, number<keys>...>>;
  }
}


/// \cond

namespace jln::mp::detail
{
  template<class C, class F, std::size_t n, class Dispatcher>
  struct collapse_impl
  {
    template<class... xs>
    using f = typename Dispatcher::template f<
      std::enable_if_t<sizeof...(xs) == n, C>,
      F,
      build_indexed_v<xs...>
    >;
  };
}

namespace jln::mp
{
  template<class C, class F>
  struct collapse2_with<C, F>
  {
    template<class... xs>
    using f = typename conditional_c<!sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(C), detail::uncallable_function>
      ::template f<>;
  };

  template<class C, class F, class key, class... keys>
  struct collapse2_with<C, F, key, keys...> : detail::collapse_impl<
    C, F, sizeof...(keys) + 1,
    detail::mk_pairs_indexes<
      same<>,
      key,
      typename take_front_c<sizeof...(keys)>::template f<key, keys...>,
      keys...
    >
  >
  {};
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class, class>
    struct product_impl;

    template<class x, class y>
    using product_impl_t = typename product_impl<x, y>::type;

    template<class, class>
    struct _product;
  }
  /// \endcond

  /// \ingroup group

  /// Computes the cartesian product of \lists.
  /// \pre `emp::is_list<seqs> && ...`
  /// \post `sizeof...(result) == (emp::size<seqs> * ...)` if `sizeof...(xs) != 0` else `0`
  /// \semantics
  ///   \code
  ///   call<product<listify>,
  ///     list<_0, _1, _2>,
  ///     list<_3, _4>,
  ///     list<_5>
  ///   > = list<
  ///     list<_0, _3, _5>, list<_0, _4, _5>,
  ///     list<_1, _3, _5>, list<_1, _4, _5>,
  ///     list<_2, _3, _5>, list<_2, _4, _5>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class C = listify>
  struct product
  {
    template<class seq = list<>, class... seqs>
    using f = typename detail::_unpack<
      C,
      typename detail::fold_impl<sizeof...(seqs)>
      ::template f<
        detail::product_impl_t,
        typename detail::_product<list<>, seq>::type,
        seqs...
      >
    >::type;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using product = unpack<L, product<C>>;
  }

  /// \cond
  template<>
  struct product<listify>
  {
    template<class seq = list<>, class... seqs>
    using f = typename detail::fold_impl<sizeof...(seqs)>
      ::template f<
        detail::product_impl_t,
        typename detail::_product<list<>, seq>::type,
        seqs...
      >;
  };
  /// \endcond
}



/// \cond
namespace jln::mp::detail
{
  template<class... xs, class... ys>
  struct _product<list<xs...>, list<ys...>>
  {
    using type = list<list<xs..., ys>...>;
  };

  template<class... seqs, class seq>
  struct product_impl<list<seqs...>, seq>
  : detail::_join_select<sizeof...(seqs)>
    ::template f<list, typename _product<seqs, seq>::type...>
  {};
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int n>
    struct repeat_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Returns a \sequence that contains a \number of copies of the same \sequence.
  /// \pre `N >= 0`
  /// \treturn \sequence
  template<unsigned N, class C = listify>
  struct repeat_c
  {
    template<class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE_T(
      int, N,
      detail::repeat_impl<sizeof...(xs) < 2 ? sizeof...(xs) : 2>::template impl
    )::template f<C, xs...>;
  };

  template<class N, class C = listify>
  using repeat = repeat_c<N::value, C>;

  namespace emp
  {
    template<class L, class n, class C = mp::listify>
    using repeat = unpack<L, mp::repeat<n, C>>;

    template<class L, int_ n, class C = mp::listify>
    using repeat_c = unpack<L, mp::repeat_c<n, C>>;
  }
}



/// \cond
namespace jln::mp::detail
{
  template<>
  struct repeat_impl<0>
  {
    template<class, int...>
    struct impl : call_trace_c0_arg
    {};
  };

#if JLN_MP_CUDA && JLN_MP_HOST_COMPILER_GCC
  template<class x, class> using emp_index0 = x;
#  define JLN_MP_INDEX0 emp_index0
#else
#  define JLN_MP_INDEX0 index0::f
#endif

  template<>
  struct repeat_impl<1>
  {
    template<class, int... ns>
    struct impl
    {
#if JLN_MP_MSVC
      template<class C, class x, class... xs>
      using g = typename C::template f<index0::f<x, xs>...>;

      template<class C, class x>
      using f = g<C, x, decltype(ns)...>;
#else
      template<class C, class x>
      using f = JLN_MP_CALL_TRACE(C, JLN_MP_INDEX0<x, decltype(ns)>...);
#endif
    };
  };

  template<>
  struct repeat_impl<2>
  {
    template<class C, class L, class... xs>
    using g = typename join<C>::template f<JLN_MP_INDEX0<L, xs>...>;

    template<class, int... ns>
    struct impl
    {
      template<class C, class... xs>
      using f = g<C, list<xs...>, decltype(ns)...>;
    };
  };

#undef JLN_MP_INDEX0
}

namespace jln::mp
{
  template<class C>
  struct repeat_c<0, C>
    : detail::call_trace_xs_0<C>
  {};

  template<class C>
  struct repeat_c<1, C>
    : detail::call_trace_xs<C>
  {};
}
/// \endcond

namespace jln::mp
{
  /// \ingroup group

  /// Computes all possible combinations (with repetition) from the elements in a \sequence.
  /// \treturn \sequence of \list
  template<class C = listify>
  struct combine
  {
    template<class... xs>
    using f = typename repeat_c<sizeof...(xs), product<C>>
      ::template f<list<xs...>>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using combine = unpack<L, mp::combine<C>>;
  }
}



JLN_MP_DIAGNOSTIC_PUSH()
JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wlogical-op")

namespace jln::mp
{
  /// \ingroup number

  template<class C = identity>
  struct or_
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value || ... || false)>);
  };

  template<class C = identity>
  struct left_or
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(false || ... || xs::value)>);
  };


  template<class C = identity>
  struct and_
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value && ... && true)>);
  };

  template<class C = identity>
  struct left_and
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(true && ... && xs::value)>);
  };


  template<class C = identity>
  struct add
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value + ...)>);
  };

  template<class C = identity>
  using add0 = if_<size<>, add<C>, always<number<0>, C>>;

  template<class C = identity>
  struct left_add
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... + xs::value)>);
  };

  template<class C = identity>
  using left_add0 = if_<size<>, left_add<C>, always<number<0>, C>>;


  template<class C = identity>
  struct sub
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... - xs::value)>);
  };

  template<class C = identity>
  using sub0 = if_<size<>, sub<C>, always<number<0>, C>>;

  template<class C = identity>
  struct lshift
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... << xs::value)>);
  };

  template<class C = identity>
  using lshift0 = if_<size<>, lshift<C>, always<number<0>, C>>;

  template<class C = identity>
  struct rshift
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... >> xs::value)>);
  };

  template<class C = identity>
  using rshift0 = if_<size<>, rshift<C>, always<number<0>, C>>;


  template<class C = identity>
  struct mul
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value * ...)>);
  };

  template<class C = identity>
  using mul0 = if_<size<>, mul<C>, always<number<0>, C>>;

  template<class C = identity>
  using mul1 = if_<size<>, mul<C>, always<number<1>, C>>;

  template<class C = identity>
  struct left_mul
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... * xs::value)>);
  };

  template<class C = identity>
  using left_mul0 = if_<size<>, left_mul<C>, always<number<0>, C>>;

  template<class C = identity>
  using left_mul1 = if_<size<>, left_mul<C>, always<number<1>, C>>;


  template<class C = identity>
  struct div
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... / xs::value)>);
  };

  template<class C = identity>
  using div0 = if_<size<>, div<C>, always<number<0>, C>>;

  template<class C = identity>
  using div1 = if_<size<>, div<C>, always<number<1>, C>>;

  template<class C = identity>
  struct mod
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... % xs::value)>);
  };

  template<class C = identity>
  using mod0 = if_<size<>, mod<C>, always<number<0>, C>>;

  template<class C = identity>
  using mod1 = if_<size<>, mod<C>, always<number<1>, C>>;


  template<class C = identity>
  struct xor_
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value ^ ...)>);
  };

  template<class C = identity>
  using xor0 = if_<size<>, xor_<C>, always<number<0>, C>>;

  template<class C = identity>
  struct left_xor
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... ^ xs::value)>);
  };

  template<class C = identity>
  using left_xor0 = if_<size<>, left_xor<C>, always<number<0>, C>>;


  template<class C = identity>
  struct bit_and
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value & ...)>);
  };

  template<class C = identity>
  using bit_and0 = if_<size<>, bit_and<C>, always<number<0>, C>>;

  template<class C = identity>
  struct left_bit_and
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... & xs::value)>);
  };

  template<class C = identity>
  using left_bit_and0 = if_<size<>, left_bit_and<C>, always<number<0>, C>>;


  template<class C = identity>
  struct bit_or
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(xs::value | ...)>);
  };

  template<class C = identity>
  using bit_or0 = if_<size<>, bit_or<C>, always<number<0>, C>>;

  template<class C = identity>
  struct left_bit_or
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(... | xs::value)>);
  };

  template<class C = identity>
  using left_bit_or0 = if_<size<>, left_bit_or<C>, always<number<0>, C>>;


  template<class C = identity>
  struct neg
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(-x::value)>);
  };

  template<class C = identity>
  struct unary_plus
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(+x::value)>);
  };

  template<class C = identity>
  struct bit_not
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(~x::value)>);
  };

  template<class C = identity>
  struct inc
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value+1)>);
  };

  template<class C = identity>
  struct dec
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value-1)>);
  };

  template<class C = identity>
  struct equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value == y::value)>);
  };

  template<class C = identity>
  struct not_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value != y::value)>);
  };

  template<class C = identity>
  struct less
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value < y::value)>);
  };

  template<class C = identity>
  struct less_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value <= y::value)>);
  };

  template<class C = identity>
  struct greater
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value > y::value)>);
  };

  template<class C = identity>
  struct greater_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<(x::value >= y::value)>);
  };


  template<class N, class C = identity>
  using equal_to = push_front<N, equal<C>>;

  template<class N, class C = identity>
  using not_equal_to = push_front<N, not_equal<C>>;

  template<class N, class C = identity>
  using less_than = push_back<N, less<C>>;

  template<class N, class C = identity>
  using less_equal_than = push_back<N, less_equal<C>>;

  template<class N, class C = identity>
  using greater_than = push_back<N, greater<C>>;

  template<class N, class C = identity>
  using greater_equal_than = push_back<N, greater_equal<C>>;


  template<int_ n, class C = identity>
  using equal_to_c = equal_to<number<n>, C>;

  template<int_ n, class C = identity>
  using not_equal_to_c = not_equal_to<number<n>, C>;

  template<int_ n, class C = identity>
  using less_than_c = less_than<number<n>, C>;

  template<int_ n, class C = identity>
  using less_equal_than_c = less_equal_than<number<n>, C>;

  template<int_ n, class C = identity>
  using greater_than_c = greater_than<number<n>, C>;

  template<int_ n, class C = identity>
  using greater_equal_than_c = greater_equal_than<number<n>, C>;
}

namespace jln::mp::emp
{
  template<class L, class C = mp::identity>
  using or_seq = unpack<L, mp::or_<C>>;

  template<class L, class C = mp::identity>
  using and_seq = unpack<L, mp::and_<C>>;

  template<class L, class C = mp::identity>
  using or_left_seq = unpack<L, mp::left_or<C>>;

  template<class L, class C = mp::identity>
  using and_left_seq = unpack<L, mp::left_and<C>>;

  template<class L, class C = mp::identity>
  using add_seq = unpack<L, mp::add<C>>;

  template<class L, class C = mp::identity>
  using add0_seq = unpack<L, mp::add0<C>>;

  template<class L, class C = mp::identity>
  using left_add_seq = unpack<L, mp::left_add<C>>;

  template<class L, class C = mp::identity>
  using left_add0_seq = unpack<L, mp::left_add0<C>>;

  template<class L, class C = mp::identity>
  using sub_seq = unpack<L, mp::sub<C>>;

  template<class L, class C = mp::identity>
  using sub0_seq = unpack<L, mp::sub0<C>>;

  template<class L, class C = mp::identity>
  using lshift_seq = unpack<L, mp::lshift<C>>;

  template<class L, class C = mp::identity>
  using lshift0_seq = unpack<L, mp::lshift0<C>>;

  template<class L, class C = mp::identity>
  using rshift_seq = unpack<L, mp::rshift<C>>;

  template<class L, class C = mp::identity>
  using rshift0_seq = unpack<L, mp::rshift0<C>>;

  template<class L, class C = mp::identity>
  using mul_seq = unpack<L, mp::mul<C>>;

  template<class L, class C = mp::identity>
  using mul0_seq = unpack<L, mp::mul0<C>>;

  template<class L, class C = mp::identity>
  using mul1_seq = unpack<L, mp::mul1<C>>;

  template<class L, class C = mp::identity>
  using left_mul_seq = unpack<L, mp::left_mul<C>>;

  template<class L, class C = mp::identity>
  using left_mul0_seq = unpack<L, mp::left_mul0<C>>;

  template<class L, class C = mp::identity>
  using left_mul1_seq = unpack<L, mp::left_mul1<C>>;

  template<class L, class C = mp::identity>
  using div_seq = unpack<L, mp::div<C>>;

  template<class L, class C = mp::identity>
  using div0_seq = unpack<L, mp::div0<C>>;

  template<class L, class C = mp::identity>
  using div1_seq = unpack<L, mp::div1<C>>;

  template<class L, class C = mp::identity>
  using mod_seq = unpack<L, mp::mod<C>>;

  template<class L, class C = mp::identity>
  using mod0_seq = unpack<L, mp::mod0<C>>;

  template<class L, class C = mp::identity>
  using mod1_seq = unpack<L, mp::mod1<C>>;

  template<class L, class C = mp::identity>
  using xor_seq = unpack<L, mp::xor_<C>>;

  template<class L, class C = mp::identity>
  using xor0_seq = unpack<L, mp::xor0<C>>;

  template<class L, class C = mp::identity>
  using left_xor_seq = unpack<L, mp::left_xor<C>>;

  template<class L, class C = mp::identity>
  using left_xor0_seq = unpack<L, mp::left_xor0<C>>;

  template<class L, class C = mp::identity>
  using bit_and_seq = unpack<L, mp::bit_and<C>>;

  template<class L, class C = mp::identity>
  using bit_and0_seq = unpack<L, mp::bit_and0<C>>;

  template<class L, class C = mp::identity>
  using left_bit_and_seq = unpack<L, mp::left_bit_and<C>>;

  template<class L, class C = mp::identity>
  using left_bit_and0_seq = unpack<L, mp::left_bit_and0<C>>;

  template<class L, class C = mp::identity>
  using bit_or_seq = unpack<L, mp::bit_or<C>>;

  template<class L, class C = mp::identity>
  using bit_or0_seq = unpack<L, mp::bit_or0<C>>;

  template<class L, class C = mp::identity>
  using left_bit_or_seq = unpack<L, mp::left_bit_or<C>>;

  template<class L, class C = mp::identity>
  using left_bit_or0_seq = unpack<L, mp::left_bit_or0<C>>;


  template<int_... xs>
  using or_c = number<(xs || ... || false)>;

  template<int_... xs>
  using left_or_c = number<(false || ... || xs)>;

  template<int_... xs>
  using and_c = number<(xs && ... && true)>;

  template<int_... xs>
  using left_and_c = number<(true && ... && xs)>;

  template<int_... xs>
  using add_c = number<(xs + ...)>;

  template<int_... xs>
  using add0_c = add_c<xs..., 0>;

  template<int_... xs>
  using left_add_c = number<(... + xs)>;

  template<int_... xs>
  using left_add0_c = left_add_c<xs..., 0>;

  template<int_... xs>
  using sub_c = number<(... - xs)>;

  template<int_... xs>
  using sub0_c = sub_c<xs..., 0>;

  template<int_... xs>
  using lshift_c = number<(... << xs)>;

  template<int_... xs>
  using lshift0_c = lshift_c<xs..., 0>;

  template<int_... xs>
  using rshift_c = number<(... >> xs)>;

  template<int_... xs>
  using rshift0_c = rshift_c<xs..., 0>;

  template<int_... xs>
  using mul_c = number<(xs * ...)>;

  template<int_... xs>
  using mul0_c = mul_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<int_... xs>
  using mul1_c = mul_c<xs..., 1>;

  template<int_... xs>
  using left_mul_c = number<(... * xs)>;

  template<int_... xs>
  using left_mul0_c = left_mul_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<int_... xs>
  using left_mul1_c = left_mul_c<xs..., 1>;

  template<int_... xs>
  using div_c = number<(... / xs)>;

  template<int_... xs>
  using div0_c = div_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<int_... xs>
  using div1_c = div_c<xs..., 1>;

  template<int_... xs>
  using mod_c = number<(... % xs)>;

  template<int_... xs>
  using mod0_c = mod_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::min() : 0)>;

  template<int_... xs>
  using mod1_c = mod_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::min() : 1)>;

  template<int_... xs>
  using xor_c = number<(xs ^ ...)>;

  template<int_... xs>
  using xor0_c = xor_c<xs..., 0, 0>;

  template<int_... xs>
  using left_xor_c = number<(... ^ xs)>;

  template<int_... xs>
  using left_xor0_c = left_xor_c<xs..., 0, 0>;

  template<int_... xs>
  using bit_and_c = number<(xs & ...)>;

  template<int_... xs>
  using bit_and0_c = bit_and_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::max() : 0)>;

  template<int_... xs>
  using left_bit_and_c = number<(... & xs)>;

  template<int_... xs>
  using left_bit_and0_c = left_bit_and_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::max() : 0)>;

  template<int_... xs>
  using bit_or_c = number<(xs | ...)>;

  template<int_... xs>
  using bit_or0_c = bit_or_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::max() : 0)>;

  template<int_... xs>
  using left_bit_or_c = number<(... | xs)>;

  template<int_... xs>
  using left_bit_or0_c = left_bit_or_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::max() : 0)>;


  template<class... xs>
  using or_ = number<(xs::value || ... || false)>;

  template<class... xs>
  using and_ = number<(xs::value && ... && true)>;

  template<class... xs>
  using left_or = number<(false || ... || xs::value)>;

  template<class... xs>
  using left_and = number<(true && ... && xs::value)>;

  template<class... xs>
  using add = number<(xs::value + ...)>;

  template<class... xs>
  using add0 = typename mp::add0<>::template f<xs...>;

  template<class... xs>
  using left_add = number<(... + xs::value)>;

  template<class... xs>
  using left_add0 = typename mp::add0<>::template f<xs...>;

  template<class... xs>
  using sub = number<(... - xs::value)>;

  template<class... xs>
  using sub0 = typename mp::sub0<>::template f<xs...>;

  template<class... xs>
  using lshift = number<(... << xs::value)>;

  template<class... xs>
  using lshift0 = typename mp::lshift0<>::template f<xs...>;

  template<class... xs>
  using rshift = number<(... >> xs::value)>;

  template<class... xs>
  using rshift0 = typename mp::rshift0<>::template f<xs...>;

  template<class... xs>
  using mul = number<(xs::value * ...)>;

  template<class... xs>
  using mul0 = typename mp::mul0<>::template f<xs...>;

  template<class... xs>
  using mul1 = typename mp::mul1<>::template f<xs...>;

  template<class... xs>
  using left_mul = number<(... * xs::value)>;

  template<class... xs>
  using left_mul0 = typename mp::left_mul0<>::template f<xs...>;

  template<class... xs>
  using left_mul1 = typename mp::left_mul1<>::template f<xs...>;

  template<class... xs>
  using div = number<(... / xs::value)>;

  template<class... xs>
  using div0 = typename mp::div0<>::template f<xs...>;

  template<class... xs>
  using div1 = typename mp::div1<>::template f<xs...>;

  template<class... xs>
  using mod = number<(... % xs::value)>;

  template<class... xs>
  using mod0 = typename mp::mod0<>::template f<xs...>;

  template<class... xs>
  using mod1 = typename mp::mod1<>::template f<xs...>;

  template<class... xs>
  using xor_ = number<(xs::value ^ ...)>;

  template<class... xs>
  using xor0 = typename mp::xor0<>::template f<xs...>;

  template<class... xs>
  using left_xor = number<(... ^ xs::value)>;

  template<class... xs>
  using left_xor0 = typename mp::left_xor0<>::template f<xs...>;

  template<class... xs>
  using bit_and = number<(xs::value & ...)>;

  template<class... xs>
  using bit_and0 = typename mp::bit_and0<>::template f<xs...>;

  template<class... xs>
  using left_bit_and = number<(... & xs::value)>;

  template<class... xs>
  using left_bit_and0 = typename mp::left_bit_and0<>::template f<xs...>;

  template<class... xs>
  using bit_or = number<(xs::value | ...)>;

  template<class... xs>
  using bit_or0 = typename mp::bit_or0<>::template f<xs...>;

  template<class... xs>
  using left_bit_or = number<(... | xs::value)>;

  template<class... xs>
  using left_bit_or0 = typename mp::left_bit_or0<>::template f<xs...>;


  template<class x, class C = mp::identity>
  using neg = typename mp::neg<C>::template f<x>;

  template<class x, class C = mp::identity>
  using unary_plus = typename mp::unary_plus<C>::template f<x>;

  template<class x, class C = mp::identity>
  using bit_not = typename mp::bit_not<C>::template f<x>;

  template<class x, class C = mp::identity>
  using inc = typename mp::inc<C>::template f<x>;

  template<class x, class C = mp::identity>
  using dec = typename mp::dec<C>::template f<x>;

  template<class x, class y, class C = mp::identity>
  using equal = typename mp::equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using not_equal = typename mp::not_equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using less = typename mp::less<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using less_equal = typename mp::less_equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using greater = typename mp::greater<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using greater_equal = typename mp::greater_equal<C>::template f<x, y>;
}

JLN_MP_DIAGNOSTIC_POP()

/// \cond

namespace jln::mp
{
  template<>
  struct or_<identity>
  {
    template<class... xs>
    using f = number<(xs::value || ... || false)>;
  };

  template<>
  struct left_or<identity>
  {
    template<class... xs>
    using f = number<(false || ... || xs::value)>;
  };


  template<>
  struct and_<identity>
  {
    template<class... xs>
    using f = number<(xs::value && ... && true)>;
  };

  template<>
  struct left_and<identity>
  {
    template<class... xs>
    using f = number<(true && ... && xs::value)>;
  };


  template<>
  struct add<identity>
  {
    template<class... xs>
    using f = number<(xs::value + ...)>;
  };

  template<>
  struct left_add<identity>
  {
    template<class... xs>
    using f = number<(... + xs::value)>;
  };


  template<>
  struct equal<identity>
  {
    template<class x, class y>
    using f = number<(x::value == y::value)>;
  };

  template<>
  struct not_equal<identity>
  {
    template<class x, class y>
    using f = number<(x::value != y::value)>;
  };

  template<>
  struct less<identity>
  {
    template<class x, class y>
    using f = number<(x::value < y::value)>;
  };

  template<>
  struct less_equal<identity>
  {
    template<class x, class y>
    using f = number<(x::value <= y::value)>;
  };

  template<>
  struct greater<identity>
  {
    template<class x, class y>
    using f = number<(x::value > y::value)>;
  };

  template<>
  struct greater_equal<identity>
  {
    template<class x, class y>
    using f = number<(x::value >= y::value)>;
  };
}

/// \endcond

namespace jln::mp
{
  /// \ingroup algorithm

  /// comparison on the result of a function.
  /// \treturn \bool
  template<class F, class Cmp = less<>>
  using compare_with = each<F, F, Cmp>;

  namespace emp
  {
    template<class F, class x, class y, class Cmp = mp::less<>>
    using compare_with = typename Cmp::template f<
      typename F::template f<x>,
      typename F::template f<y>
    >;
  }
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct conjunction_impl;
  }
  /// \endcond

  /// \ingroup search

  /// Perform a logical AND on the sequence of value and returns the first value converted to false.
  /// Conjunction is short-circuiting: if there is a template type
  /// argument `xs[i]` with `bool(Pred::f<xs[i]>::value) == false`,
  /// then instantiating `conjunction<C>::f<xs[0], ..., xs[n-1]>`
  /// does not require the instantiation of `Pred::f<xs[j]>::value` for `j > i`.
  /// \note If you just need a boolean, `all_of<Pred,C>` is more appropriate.
  /// \treturn \value
  /// \post If `sizeof...(xs) == 0`, `true_`
  /// \post If `sizeof...(xs) != 0`, the first type `xs[i]` for which `bool(Pred::f<xs[i]>::value) == false`, or last value if there is no such type.
  /// \see disjunction, drop_while, take_while
  template<class Pred, class C = identity>
  struct conjunction_with
  {
    template<class... xs>
    using f = typename detail::conjunction_impl<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<front<C>, sizeof...(xs)>
    ::template f<true_, xs...>;
  };

  /// Perform a logical AND on the sequence of value and returns the first value converted to false.
  /// Conjunction is short-circuiting: if there is a template type
  /// argument `xs[i]` with `bool(xs[i]::value) == false`, then instantiating
  /// `conjunction<C>::f<xs[0], ..., xs[n-1]>` does not require the
  /// instantiation of `xs[j]::value` for `j > i`.
  /// \note If you just need a boolean, `all_of<identity,C>` is more appropriate.
  /// \treturn \value convertible to \bool
  /// \post If `sizeof...(xs) == 0`, `true_`
  /// \post If `sizeof...(xs) != 0`, the first value for which `bool(xs[i]::value) == false`, or last value if there is no such type.
  /// \see disjunction, drop_while, take_while
  template<class C = identity>
  using conjunction = conjunction_with<identity, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using conjunction_with = unpack<L, mp::conjunction_with<Pred, C>>;

    template<class L, class C = mp::identity>
    using conjunction = unpack<L, mp::conjunction_with<mp::identity, C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<>
  struct conjunction_impl<_drop_while_continue>
  {
    template<class C, std::size_t n>
    using f = drop_front_c<n, C>;
  };

  template<std::size_t n>
  struct conjunction_impl<_drop_while_result<n>>
  {
    template<class C, std::size_t m>
    using f = drop_front_c<m-n, C>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a \value is contained in a \list.
  /// \treturn \bool
  template<class x, class C = identity>
  using contains = any_of<is<x>, C>;

  namespace emp
  {
    template<class L, class x, class C = mp::identity>
    using contains = unpack<L, mp::contains<x, C>>;
  }
}

namespace jln::mp
{
  /// \ingroup filter

  /// Copies all elements that satisfy a predicate.
  /// \treturn \sequence
  template<class Pred, class C = listify>
  using copy_if = transform<wrap_in_list_if<Pred>, join<C>>;

  /// Copies all occurence of a \value.
  /// \treturn \sequence
  template<class x, class C = listify>
  using copy = copy_if<is<x>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using copy_if = unpack<L, mp::copy_if<Pred, C>>;

    template<class L, class x, class C = mp::listify>
    using copy = unpack<L, mp::copy<x, C>>;
  }
}

namespace jln::mp
{
  /// \ingroup list

  /// Remove the first element of sequence
  /// \pre `sizeof...(xs) > 0`
  /// \treturn \sequence
  template<class C = listify>
  using pop_front = drop_front_c<1, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using pop_front = drop_front_c<L, 1, C>;
  }
}

namespace jln::mp
{
  /// \ingroup utility

  /// \treturn \bool
  template<class T, class C = identity>
  using is_not = is<T, not_<C>>;
  /// \cond
  namespace detail
  {
    template<class x>
    struct basic_item
    {};

    template<class... xs>
    struct inherit : basic_item<xs>...
    {};
  }
#if JLN_MP_CLANG_LIKE || JLN_MP_GCC || JLN_MP_MSVC
# define JLN_MP_SET_CONTAINS_BASE(x, ...) __is_base_of(detail::basic_item<x>, __VA_ARGS__)
#else
# define JLN_MP_SET_CONTAINS_BASE(x, ...) std::is_base_of<detail::basic_item<x>, __VA_ARGS__>::value
#endif
#define JLN_MP_SET_CONTAINS(x, ...) JLN_MP_SET_CONTAINS_BASE(x, detail::inherit<__VA_ARGS__>)
  /// \endcond

  /// \ingroup set

  /// Checks if \c x is an element of the \set whose elements are \c xs.
  /// \treturn \bool
  /// \pre `emp::unique<xs...> == list<xs...>`
  template<class x, class C = identity>
  struct set_contains
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_SET_CONTAINS(x, xs...)>);
  };

  namespace emp
  {
    /// \c true if \c x is an element of the set \c xs, \c false otherwise.
    template<class x, class... xs>
    constexpr bool set_contains_xs_v = JLN_MP_SET_CONTAINS(x, xs...);

    /// \c true if \c x is an element of the set \c Set, \c false otherwise.
    template<class Set, class x>
    constexpr bool set_contains_v = JLN_MP_SET_CONTAINS_BASE(
      x, typename detail::_unpack<mp::lift<detail::inherit>, Set>::type
    );

    /// \c true if \c x is an element of all \set \c Sets, \c false otherwise.
    template<class x, class... Sets>
    constexpr bool set_all_contains_v = (JLN_MP_SET_CONTAINS_BASE(
      x, typename detail::_unpack<mp::lift<detail::inherit>, Sets>::type
    ) && ...);

    /// \c true if \c x is an element of any \set \c Sets, \c false otherwise.
    template<class x, class... Sets>
    constexpr bool set_any_contains_v = (JLN_MP_SET_CONTAINS_BASE(
      x, typename detail::_unpack<mp::lift<detail::inherit>, Sets>::type
    ) || ...);

    /// \c true if \c x is an element of none \set \c Sets, \c false otherwise.
    template<class x, class... Sets>
    constexpr bool set_none_contains_v = !set_any_contains_v<x, Sets...>;

    /// \c true_ if \c x is an element of the set \c Set, \c false_ otherwise.
    template<class Set, class x>
    using set_contains = number<set_contains_v<Set, x>>;

    /// \c true_ if \c x is an element of all \set \c Sets, \c false_ otherwise.
    template<class x, class... Sets>
    using set_all_contains = number<set_all_contains_v<x, Sets...>>;

    /// \c true_ if \c x is an element of any \set \c Sets, \c false_ otherwise.
    template<class x, class... Sets>
    using set_any_contains = number<set_any_contains_v<x, Sets...>>;

    /// \c true_ if \c x is an element of none \set \c Sets, \c false_ otherwise.
    template<class x, class... Sets>
    using set_none_contains = number<!set_any_contains_v<x, Sets...>>;
  }

  /// Checks if \c x is an element of all \set \c Sets.
  /// \treturn \bool
  /// \pre `emp::unique<Sets> && ...`
  template<class x, class C = identity>
  struct set_all_contains
  {
    template<class... Sets>
    using f = JLN_MP_CALL_TRACE(C, number<emp::set_all_contains_v<x, Sets...>>);
  };

  /// Checks if \c x is an element of any \set \c Sets.
  /// \treturn \bool
  /// \pre `emp::unique<Sets> && ...`
  template<class x, class C = identity>
  struct set_any_contains
  {
    template<class... Sets>
    using f = JLN_MP_CALL_TRACE(C, number<emp::set_any_contains_v<x, Sets...>>);
  };

  /// Checks if \c x is an element of none \set \c Sets.
  /// \treturn \bool
  /// \pre `emp::unique<Sets> && ...`
  template<class x, class C = identity>
  struct set_none_contains
  {
    template<class... Sets>
    using f = JLN_MP_CALL_TRACE(C, number<!emp::set_any_contains_v<x, Sets...>>);
  };
}

/// \cond
namespace jln::mp
{
  template<class x>
  struct set_contains<x, identity>
  {
    template<class... xs>
    using f = number<JLN_MP_SET_CONTAINS(x, xs...)>;
  };

  template<class x>
  struct set_all_contains<x, identity>
  {
    template<class... Sets>
    using f = number<emp::set_all_contains_v<x, Sets...>>;
  };

  template<class x>
  struct set_any_contains<x, identity>
  {
    template<class... Sets>
    using f = number<emp::set_any_contains_v<x, Sets...>>;
  };

  template<class x>
  struct set_none_contains<x, identity>
  {
    template<class... Sets>
    using f = number<!emp::set_any_contains_v<x, Sets...>>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether all \values are unique.
  /// \treturn \bool
  template<class Cmp = same<>, class C = identity>
  struct is_unique_if
#ifdef JLN_MP_DOXYGENATING
  {
    template<class... xs>
    using f;
  }
#endif
  ;

  /// Checks whether all \values are unique.
  /// \treturn \bool
  template<class C = identity>
  using is_unique = is_unique_if<same<>, C>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using is_unique = unpack<L, mp::is_unique_if<mp::same<>, C>>;

    template<class L, class Cmp = mp::same<>, class C = mp::identity>
    using is_unique_if = unpack<L, mp::is_unique_if<Cmp, C>>;
  }
}


/// \cond

namespace jln::mp::detail
{
  template<int_ i, class x>
  struct indexed_item : basic_item<x>
  {};

  template<class, int_... ints>
  struct indexed_inherit
  {
    template<class... xs>
    struct f : indexed_item<ints, xs>...
    {};
  };

#if JLN_MP_MSVC_LIKE
  template<class... xs>
  struct _is_set
  {
    template<class Pack>
    static auto is_set(Pack pack) -> decltype((
        static_cast<basic_item<xs>*>(pack),...
    ), number<1>());

    static number<0> is_set(...);

    using type = decltype(is_set(static_cast<
      typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), indexed_inherit)::template f<xs...>*
    >(nullptr)));
  };
#endif
}

namespace jln::mp
{
  template<class C>
  struct is_unique_if<same<>, C>
  {
    template<class... xs>
#if JLN_MP_MSVC_LIKE
    // workaround for MSVC which has a broken EBO
    using f = JLN_MP_CALL_TRACE(C, typename detail::_is_set<xs...>::type);
#else
    using f = JLN_MP_CALL_TRACE(C, number<sizeof(
      typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), detail::indexed_inherit)::template f<xs...>
    ) == 1>);
#endif
  };

  template<>
  struct is_unique_if<same<>, identity>
  {
    template<class... xs>
#if JLN_MP_MSVC_LIKE
    // workaround for MSVC which has a broken EBO
    using f = typename detail::_is_set<xs...>::type;
#else
    using f = number<sizeof(
      typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), detail::indexed_inherit)::template f<xs...>
    ) == 1>;
#endif
  };
}

namespace jln::mp::detail
{
  template<bool>
  struct is_unique_unpack_impl;

  template<>
  struct is_unique_unpack_impl<false>
  {
    template<class C, class seq, class... xs>
    using f = typename _unpack<C, seq, xs...>::type;
  };

  template<>
  struct is_unique_unpack_impl<true>
  {
    template<class C, class seq, class... xs>
    using f = void;
  };

  template<class C>
  struct is_unique_unpack
  {
    template<class seq, class... xs>
    using f = typename is_unique_unpack_impl<JLN_MP_IS_SAME(seq, void)>
      ::template f<C, seq, xs...>;
  };

  template<class Cmp>
  struct is_unique_set_cmp_push_back_or_void
  {
    template<class x, class... xs>
    using f = typename conditional_c<
      none_of<push_back<x, Cmp>>::template f<xs...>::value
    >::template f<list<xs..., x>, void>;
  };
}

namespace jln::mp
{
  template<class Cmp, class C>
  struct is_unique_if
    : push_front<
        list<>,
        fold<
          detail::is_unique_unpack<detail::is_unique_set_cmp_push_back_or_void<Cmp>>,
          is_not<void, C>
        >
      >
  {};
}
/// \endcond

// #if ! JLN_MP_GCC
// #endif


namespace jln::mp
{
  /// \cond
  namespace detail
  {
#if JLN_MP_GCC
    template<bool>
    struct _remove_unique;

    template<bool>
    struct _copy_unique;
#else
    template<class, int_... i>
    struct _remove_unique;

    template<class, int_... i>
    struct _copy_unique;
#endif

    template<class Cmp, class C>
    struct mk_remove_unique;

    template<class Cmp, class C>
    struct mk_copy_unique;
  }
  /// \endcond

  /// \ingroup filter

  /// Remove unique elements from a \sequence.
  /// \treturn \sequence
  /// \see remove_unique_if, copy_unique, copy_unique_if
  template<class C = listify>
  struct remove_unique
  {
    template<class... xs>
#if JLN_MP_GCC
    using f = typename detail::_remove_unique<sizeof...(xs) < 2>
#else
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), detail::_remove_unique)
#endif
      ::template f<C, xs...>;
  };

  /// Remove unique elements from a \sequence.
  /// \treturn \sequence
  /// \see remove_unique, copy_unique, copy_unique_if
  template<class Cmp = same<>, class C = listify>
  using remove_unique_if = typename detail::mk_remove_unique<Cmp, C>::type;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using remove_unique = unpack<L, remove_unique<C>>;

    template<class L, class Cmp = mp::same<>, class C = mp::listify>
    using remove_unique_if = unpack<L, remove_unique_if<Cmp, C>>;
  }

  /// Copy unique elements from a \sequence.
  /// \treturn \sequence
  /// \see copy_unique_if, remove_unique, remove_unique_if
  template<class C = listify>
  struct copy_unique
  {
    template<class... xs>
#if JLN_MP_GCC
    using f = typename detail::_copy_unique<sizeof...(xs) < 2>
#else
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), detail::_copy_unique)
#endif
      ::template f<C, xs...>;
  };

  /// Copy unique elements from a \sequence.
  /// \treturn \sequence
  /// \see copy_unique, remove_unique, remove_unique_if
  template<class Cmp = same<>, class C = listify>
  using copy_unique_if = typename detail::mk_copy_unique<Cmp, C>::type;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using copy_unique = unpack<L, copy_unique<C>>;

    template<class L, class Cmp = mp::same<>, class C = mp::listify>
    using copy_unique_if = unpack<L, copy_unique_if<Cmp, C>>;
  }
}



// #if JLN_MP_GCC
// #else
// #endif

/// \cond
namespace jln::mp::detail
{
#if JLN_MP_GCC
#if !JLN_MP_FEATURE_CONCEPTS
  template<class From, class To, class = decltype(To(From()))>
  constexpr bool is_convertible_to(From, To)
  {
    return true;
  }

  constexpr bool is_convertible_to(...)
  {
    return false;
  }
#endif

  template<class Inherit, class x>
  using remove_unique_elem_impl =
    typename wrap_in_list_c<
#if JLN_MP_FEATURE_CONCEPTS
      !requires{ static_cast<basic_item<x>*>(static_cast<Inherit*>(nullptr)); }
#else
      !is_convertible_to(
        static_cast<Inherit*>(nullptr),
        static_cast<basic_item<x>*>(nullptr)
      )
#endif
    >
    ::template f<x>;

  template<class C, class Inherit, class... xs>
  using remove_unique_impl = typename join<C>
    ::template f<remove_unique_elem_impl<Inherit, xs>...>;

  template<>
  struct _remove_unique<false>
  {
    template<class C, class... xs>
    using f = remove_unique_impl<
      C,
      typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), indexed_inherit)::template f<xs...>,
      xs...
    >;
  };

  template<>
  struct _remove_unique<true>
    : call_trace_c0_arg
  {};


  template<class Inherit, class x>
  using copy_unique_elem_impl =
    typename wrap_in_list_c<
#if JLN_MP_FEATURE_CONCEPTS
      requires{ static_cast<basic_item<x>*>(static_cast<Inherit*>(nullptr)); }
#else
      is_convertible_to(
        static_cast<Inherit*>(nullptr),
        static_cast<basic_item<x>*>(nullptr)
      )
#endif
    >
    ::template f<x>;

  template<class C, class Inherit, class... xs>
  using copy_unique_impl = typename join<C>
    ::template f<copy_unique_elem_impl<Inherit, xs>...>;

  template<>
  struct _copy_unique<false>
  {
    template<class C, class... xs>
    using f = copy_unique_impl<
      C,
      typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), indexed_inherit)::template f<xs...>,
      xs...
    >;
  };

  template<>
  struct _copy_unique<true>
  {
    template<class C, class... xs>
    using f = JLN_MP_CALL_TRACE(C, xs...);
  };
#else
  template<class C, class Inherit, Inherit* ptr, class... S>
  using remove_copy_unique_filter = typename join<C>
    ::template f<decltype(S::f(ptr))...>;


  template<class x>
  struct remove_unique_elem_impl
  {
    template<class i>
    static list<> f(basic_item<list<x, i>>*);

    static list<x> f(...);
  };

  template<class, int_... i>
  struct _remove_unique
  {
    template<class C, class... xs>
    using f = remove_copy_unique_filter<
      C, inherit<list<xs, number<i>>...>, nullptr, remove_unique_elem_impl<xs>...
    >;
  };


  template<class x>
  struct copy_unique_elem_impl
  {
    template<class i>
    static list<x> f(basic_item<list<x, i>>*);

    static list<> f(...);
  };

  template<class, int_... i>
  struct _copy_unique
  {
    template<class C, class... xs>
    using f = remove_copy_unique_filter<
      C, inherit<list<xs, number<i>>...>, nullptr, copy_unique_elem_impl<xs>...
    >;
  };
#endif


  template<class, int_... ints>
  struct remove_unique_if_impl
  {
    template<class C, class Cmp, class... xs>
    using f = typename join<C>::template f<
      JLN_MP_MSVC_FIX_CALL((
        rotate_impl<ints>::template f<
          ints,
          pop_front<any_of<
            push_back<xs, Cmp>,
            lift<wrap_in_list>
          >>,
          xs...
        >
      ), xs)...
    >;
  };

  template<>
  struct remove_unique_if_impl<int_>
    : call_trace_c0_arg
  {};

  template<int_ i>
  struct remove_unique_if_impl<int_, i>
  : remove_unique_if_impl<int_>
  {};

  template<class Cmp, class C>
  struct _remove_unique_if
  {
    template<class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), remove_unique_if_impl)
      ::template f<C, Cmp, xs...>;
  };

  template<class Cmp, class C>
  struct mk_remove_unique
  {
    using type = _remove_unique_if<Cmp, C>;
  };


  template<class, int_... ints>
  struct copy_unique_if_impl
  {
    template<class C, class Cmp, class... xs>
    using f = typename join<C>::template f<
      JLN_MP_MSVC_FIX_CALL((
        rotate_impl<ints>::template f<
          ints,
          pop_front<none_of<
            push_back<xs, Cmp>,
            lift<wrap_in_list>
          >>,
          xs...
        >
      ), xs)...
    >;
  };

  template<>
  struct copy_unique_if_impl<int_>
  : remove_unique_if_impl<int_>
  {};

  template<int_ i>
  struct copy_unique_if_impl<int_, i>
  {
    template<class C, class Cmp, class... xs>
    using f = JLN_MP_CALL_TRACE(C, xs...);
  };

  template<class Cmp, class C>
  struct _copy_unique_if
  {
    template<class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), copy_unique_if_impl)
      ::template f<C, Cmp, xs...>;
  };

  template<class Cmp, class C>
  struct mk_copy_unique
  {
    using type = _copy_unique_if<Cmp, C>;
  };


  template<class C>
  struct mk_remove_unique<same<>, C>
  {
    using type = mp::remove_unique<C>;
  };

  template<class C>
  struct mk_remove_unique<same<not_<>>, C>
  {
    using type = mp::copy_unique<C>;
  };

  template<class F, class C>
  struct mk_remove_unique<tee<F, not_<>>, C>
  : mk_copy_unique<F, C>
  {};

  template<class C>
  struct mk_copy_unique<same<>, C>
  {
    using type = mp::copy_unique<C>;
  };

  template<class C>
  struct mk_copy_unique<same<not_<>>, C>
  {
    using type = mp::remove_unique<C>;
  };

  template<class F, class C>
  struct mk_copy_unique<tee<F, not_<>>, C>
  : mk_remove_unique<F, C>
  {};
}
/// \endcond

namespace jln::mp
{
  /// \ingroup algorithm

  /// Counts all elements that satisfy a predicate.
  template<class Pred, class C = identity>
  using count_if = transform<Pred, add0<C>>;

  /// Counts all elements identical to a \value.
  template<class x, class C = identity>
  using count = transform<is<x>, add0<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using count_if = unpack<L, mp::count_if<Pred, C>>;

    template<class L, class x, class C = mp::identity>
    using count = unpack<L, mp::count<x, C>>;
  }
}


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct set_push_back_select;

    template<class Set, class x, class = number<0>>
    struct set_push_back_impl;
  }
  /// \endcond

  /// \ingroup set

  /// Appends \c x to the end of the \set whose elements are \c xs if not already in \c xs.
  /// \treturn \set
  /// \pre `emp::unique<xs...> == list<xs...>`
  /// \post \c emp::is_unique<result>
  /// \see set_push_front, set_push_back_elements
  template<class x, class C = listify>
  struct set_push_back
  {
    template<class... xs>
    using f = typename detail::set_push_back_select<JLN_MP_SET_CONTAINS(x, xs...)>
      ::template f<JLN_MP_TRACE_F(C), x, xs...>;
  };

  namespace emp
  {
    template<class Set, class x>
    using set_push_back = typename detail::set_push_back_impl<Set, x>::type;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<>
  struct set_push_back_select<false>
  {
    template<class C, class x, class... xs>
    using f = typename C::template f<xs..., x>;
  };

  template<>
  struct set_push_back_select<true>
  {
    template<class C, class, class... xs>
    using f = typename C::template f<xs...>;
  };

  template<class L, class x, class>
  struct set_push_back_impl
  {
    using type = L;
  };

  template<class... xs, class x>
  struct set_push_back_impl<list<xs...>, x, number<JLN_MP_SET_CONTAINS(x, xs...)>>
  {
    using type = list<xs..., x>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class Cmp, class C>
    struct mk_unique;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Returns a list with duplicate elements removed.
  /// \treturn \set
  template<class C = listify>
  using unique = typename detail::mk_unique<same<>, C>::type;

  /// Returns a list with duplicate elements removed.
  /// Only the first element found is kept.
  /// \treturn \sequence
  template<class Cmp = same<>, class C = listify>
  using unique_if = typename detail::mk_unique<Cmp, C>::type;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using unique = unpack<L, unique<C>>;

    template<class L, class Cmp = mp::same<>, class C = mp::listify>
    using unique_if = unpack<L, unique_if<Cmp, C>>;
  }
}


/// \cond

namespace jln::mp::detail
{
  template<class Cmp>
  struct _set_cmp_push_back
  {
    template<class x, class... xs>
    using f = typename conditional_c<
      none_of<push_back<x, Cmp>>::template f<xs...>::value
    >::template f<list<xs..., x>, list<xs...>>;
  };

  template<class Cmp, class C>
  struct mk_unique
  {
    using type = push_front<list<>, fold<
      unpack<_set_cmp_push_back<JLN_MP_TRACE_F(Cmp)>>,
      optimize_useless_unpack_t<unpack<C>>
    >>;
  };

  template<class C>
  struct mk_unique<same<>, C>
  {
    using type = push_front<list<>, fold<
      lift<emp::set_push_back>,
      optimize_useless_unpack_t<unpack<C>>
    >>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    struct mk_counter;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Counts all distinct elements and returns a list of pairs containing
  /// the type and the repeat count.
  /// Elements are sorted in order of first appearance.
  /// \semantics
  ///   \code
  ///   counter<F>::f<int, int, char, double, int, double>
  ///   == list<
  ///     F::f<int, number<3>>,
  ///     F::f<char, number<1>>,
  ///     F::f<double, number<2>>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list of type and \number
  template<class F, class C = listify>
  struct counter_wrapped_with
  {
    template<class... xs>
#if JLN_MP_GCC
    using f = typename decltype(
      unique<detail::mk_counter>::f<xs...>
      ::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F)::template f, xs...>()
    )::template f<>;
#else
    using f = typename unique<detail::mk_counter>::f<xs...>
      ::template counter<xs...>
      ::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F)::template f>;
#endif
  };

  /// Counts all distinct elements and returns a list of pairs containing
  /// the type and the repeat count.
  /// Elements are sorted in order of first appearance.
  /// \semantics
  ///   \code
  ///   counter<F>::f<int, int, char, double, int, double>
  ///   == list<
  ///     list<int, number<3>>,
  ///     list<char, number<1>>,
  ///     list<double, number<2>>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list of type and \number
  template<class C = listify>
  using counter = counter_wrapped_with<listify, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using counter = unpack<L, mp::counter<C>>;

    template<class L, class F = mp::listify, class C = mp::listify>
    using counter_wrapped_with = unpack<L, mp::counter_wrapped_with<F, C>>;
  }
}

/// \cond
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
namespace jln::mp
{
  template<template<class...> class F, class C>
  struct counter_wrapped_with<lift<F>, C>
  {
    template<class... xs>
#if JLN_MP_GCC
    using f = typename decltype(
      unique<detail::mk_counter>::f<xs...>
      ::template f<JLN_MP_TRACE_F(C), F, xs...>()
    )::template f<>;
#else
    using f = typename unique<detail::mk_counter>::f<xs...>
      ::template counter<xs...>
      ::template f<JLN_MP_TRACE_F(C), F>;
#endif
  };
}
#endif


namespace jln::mp::detail
{
  template<std::size_t N>
  struct array
  {
    int elems[N];
  };

  template<>
  struct array<0>
    : array<1>
  {};

  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_IGNORE_UNSAFE_BUFFER_USAGE()

#if JLN_MP_GCC || (!JLN_MP_MSVC && __cplusplus >= 202002L && __cpp_nontype_template_args >= 201911L)
  template<std::size_t N, int_... i>
  constexpr array<N> count_elems()
  {
    array<N> counter{};
    (..., ++counter.elems[i]);
    return counter;
  }
#else
  template<std::size_t N, int_... i>
  struct count_elems
  {
    static constexpr auto counters = []{
      array<N> counter {};
      (..., ++counter.elems[i]);
      return counter;
    }();
  };
#endif

#if JLN_MP_GCC

  template<class T, int_ i>
  constexpr int_ index_base(indexed_item<i, T>*)
  {
    return i;
  }

  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_GCC_IGNORE("-Wunused-but-set-variable")
  template<class, int_... ints>
  struct counter_impl
  {
    template<class... unique_xs>
    struct unique
    {
      template<class C, template<class...> class F, class... xs>
      static auto f()
      {
        constexpr typename indexed_inherit<int_, ints...>::template f<unique_xs...>*
          indexed = nullptr;

        constexpr auto counters = count_elems<
          sizeof...(ints),
          index_base<xs>(indexed)...
        >();

        return always<typename C::template f<
          F<unique_xs, number<counters.elems[ints]>>...
        >>();
      }
    };
  };
  JLN_MP_DIAGNOSTIC_POP()

#else

  template<class T, class i>
  constexpr int_ index_base(basic_item<list<i, T>>*)
  {
    return i::value;
  }

 template<class, int_... ints>
  struct counter_impl
  {
    template<class... unique_xs>
    struct unique
    {
      static constexpr detail::inherit<list<number<ints>, unique_xs>...>* indexed = nullptr;

#if !JLN_MP_MSVC && __cplusplus >= 202002L && __cpp_nontype_template_args >= 201911L
      template<auto counters>
      struct impl
      {
        template<class C, template<class...> class F>
        using f = typename C::template f<F<unique_xs, number<counters.elems[ints]>>...>;
      };

      template<class... xs>
      struct counter : impl<count_elems<sizeof...(ints), index_base2<xs>(indexed)...>()>
      {};
#else
      template<class S>
      struct impl
      {
        template<class C, template<class...> class F>
        using f = typename C::template f<F<unique_xs, number<S::counters.elems[ints]>>...>;
      };

      template<class... xs>
      struct counter : impl<count_elems<sizeof...(ints), index_base<xs>(indexed)...>>
      {};
#endif
    };
  };

#endif

  JLN_MP_DIAGNOSTIC_POP()

  struct mk_counter
  {
    template<class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), counter_impl)
      ::template unique<xs...>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup search

  /// Perform a logical OR on the sequence of value and returns the first value converted to true.
  /// Disjunction is short-circuiting: if there is a template type
  /// argument `xs[i]` with `bool(xs[i]::value) == true`, then instantiating
  /// `disjunction<C>::f<xs[0], ..., xs[n-1]>` does not require the
  /// instantiation of `Pred::f<xs[j]>::value` for `j > i`
  /// \note If you just need a boolean, `any_of<Pred,C>` is more appropriate.
  /// \treturn \value
  /// \post If `sizeof...(xs) == 0`, `false_`
  /// \post If `sizeof...(xs) != 0`, the first type `xs[i]` for which `bool(Pred::f<xs[i]>::value) == true`, or last value if there is no such type.
  /// \see disjunction, drop_while, take_while
  template<class Pred, class C = identity>
  struct disjunction_with
  {
    template<class... xs>
    using f = typename detail::conjunction_impl<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<front<C>, sizeof...(xs)>
    ::template f<false_, xs...>;
  };

  /// Perform a logical OR on the sequence of value and returns the first value converted to true.
  /// Disjunction is short-circuiting: if there is a template type
  /// argument `xs[i]` with `bool(xs[i]::value) == true`, then instantiating
  /// `disjunction<C>::f<xs[0], ..., xs[n-1]>` does not require the
  /// instantiation of `xs[j]::value` for `j > i`.
  /// \note If you just need a boolean, `any_of<identity,C>` is more appropriate.
  /// \treturn \value convertible to \bool
  /// \post If `sizeof...(xs) == 0`, `false_`
  /// \post If `sizeof...(xs) != 0`, the first value for which `bool(xs[i]::value) == true`, or last value if there is no such type.
  /// \see disjunction, drop_while, take_while
  template<class C = identity>
  using disjunction = disjunction_with<identity, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using disjunction_with = unpack<L, mp::disjunction_with<Pred, C>>;

    template<class L, class C = mp::identity>
    using disjunction = unpack<L, mp::disjunction_with<mp::identity, C>>;
  }
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct ends_with_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks if the \sequence ends with the given prefix.
  /// \treturn \bool
  /// \see ends_with
  template<class Seq, class C = identity>
  struct ends_with
  {};

  template<class... Ts, class C>
  struct ends_with<list<Ts...>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::ends_with_impl<sizeof...(Ts) <= sizeof...(xs)>
      ::template f<sizeof...(Ts), list<Ts...>, xs...>
    );
  };

  namespace emp
  {
    template<class L, class Seq, class C = mp::identity>
    using ends_with = unpack<ends_with<Seq, C>, L>;
  }

  /// \cond
  template<class... Ts>
  struct ends_with<list<Ts...>, identity>
  {
    template<class... xs>
    using f = typename detail::ends_with_impl<sizeof...(Ts) <= sizeof...(xs)>
      ::template f<sizeof...(Ts), list<Ts...>, xs...>;
  };

  template<class C>
  struct ends_with<list<>, C>
  {
    template<class... xs>
    using f = JLN_MP_FORCE_DCALL_TRACE_XS(xs, C, true_);
  };

  template<>
  struct ends_with<list<>, identity> : always<true_>
  {};
  /// \endcond
}

/// \cond

namespace jln::mp::detail
{
  template<>
  struct ends_with_impl<true>
  {
    template<unsigned n, class L, class... xs>
    using f = number<JLN_MP_IS_SAME(
      typename drop_front_c<sizeof...(xs) - n>::template f<xs...>,
      L
    )>;
  };

  template<>
  struct ends_with_impl<false> : starts_with_impl<false>
  {};
}
/// \endcond

namespace jln::mp
{
  /// \ingroup search

  /// Finds the first element that satisfy a \predicate.
  /// \pre \c Pred::f<x> must return a boolean, 1 or 0
  /// Calls \c TC with all the elements since the one found at the end.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see find_if_not, find, find_last_if, find_last
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_if = drop_until<Pred, TC, FC>;

  /// \see find_if, find, find_last_if, find_last
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_if_not = drop_while<Pred, TC, FC>;

  /// \see find_if, find_if_not, find_last_if, find_last
  template<class T, class TC = listify, class FC = clear<TC>>
  using find = find_if<is<T>, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using find_if = unpack<L, mp::find_if<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using find_if_not = unpack<L, mp::find_if_not<Pred, TC, FC>>;

    template<class L, class T, class TC = mp::listify, class FC = clear<TC>>
    using find = unpack<L, mp::find_if<mp::is<T>, TC, FC>>;
  }
}


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct _recursively;

    template<class>
    struct _recursively_as_much_as_possible;

    template<class x>
    struct _recursively_next;

    template<class x>
    struct _recursively_as_much_as_possible_next;

    template<class...>
    struct _recursion_result;

    template<class...>
    struct _next_recursion;
  }
  /// \endcond

  /// \ingroup functional

  /// Stop the recursion, the input values will be used as result.
  struct stop_recursion : always<stop_recursion>
  {
#ifdef JLN_MP_DOXYGENATING
    template<class...>
    using f = stop_recursion;
#endif
  };

  /// Specify result values and stop recursion.
  struct recursion_result
  {
    template<class... xs>
    using f = detail::_recursion_result<xs...>;
  };

  /// Specify values for the next iteration.
  struct next_recursion
  {
    template<class... xs>
    using f = detail::_next_recursion<xs...>;
  };

  /// \ingroup functional

  /// Recursively invokes \c F until \c stop_recursion or \c recursion_result.
  /// \treturn \value
  /// \see recursively_xs, recursively_as_much_as_possible
  /// \see stop_recursion, recursion_result, next_recursion
  template<class F, class C = identity>
  struct recursively
  {
    template<class... xs>
    using f = typename detail::_recursively<
      typename detail::_recursively_next<JLN_MP_DCALL_TRACE_XS(xs, F, xs...)>
      ::template g<xs...>
      ::template f<F>
      ::template f<F>
      ::template f<F>
    >::template f<F, C>;
  };

  /// Same than \c recursively, but with listify as default continuation.
  /// \treturn \sequence
  /// \see recursively
  template<class F, class C = listify>
  using recursively_xs = recursively<F, C>;

  /// Recursively invokes \c F until the result is \c stop_recursion, \c recursion_result or no longer changes.
  /// \treturn \value
  /// \see recursively_as_much_as_possible_xs
  /// \see recursively
  /// \see stop_recursion, recursion_result, next_recursion
  template<class F, class C = identity>
  struct recursively_as_much_as_possible
  {
    template<class... xs>
    using f = typename detail::_recursively_as_much_as_possible<
      typename detail::_recursively_as_much_as_possible_next<JLN_MP_DCALL_TRACE_XS(xs, F, xs...)>
        ::template g<xs...>
        ::template f<F>
        ::template f<F>
        ::template f<F>
    >::template f<F, C>;
  };

  /// Same than \c recursively_as_much_as_possible, but with listify as default continuation.
  /// \treturn \value
  /// \see recursively_as_much_as_possible
  template<class F, class C = listify>
  using recursively_as_much_as_possible_xs = recursively_as_much_as_possible<F, C>;

  namespace emp
  {
    template<class L, class F, class C = mp::identity>
    using recursively = unpack<L, mp::recursively<F, C>>;

    template<class L, class F, class C = mp::identity>
    using recursively_as_much_as_possible = unpack<L, mp::recursively_as_much_as_possible<F, C>>;

    template<class L, class F, class C = mp::listify>
    using recursively_xs = unpack<L, mp::recursively<F, C>>;

    template<class L, class F, class C = mp::listify>
    using recursively_as_much_as_possible_xs = unpack<L, mp::recursively_as_much_as_possible<F, C>>;
  }
}




/// \cond
namespace jln::mp::detail
{
  template<class x>
  struct _recursively_next
  {
    template<class>
    using f = _recursively_next;

    template<class...>
    using g = _recursively_next<_next_recursion<x>>;
  };

  template<>
  struct _recursively_next<stop_recursion>
  {
    template<class>
    using f = _recursively_next;

    template<class... xs>
    using g = _recursively_next<_recursion_result<xs...>>;
  };

  template<class... xs>
  struct _recursively_next<_recursion_result<xs...>>
  {
    template<class>
    using f = _recursively_next;

    template<class...>
    using g = _recursively_next;
  };

  template<class... xs>
  struct _recursively_next<_next_recursion<xs...>>
  {
    template<class F>
    using f = typename _recursively_next<JLN_MP_CALL_TRACE(F, xs...)>
              ::template g<xs...>;

    template<class...>
    using g = _recursively_next;
  };

  template<class... xs>
  struct _recursively<_recursively_next<_next_recursion<xs...>>>
  {
    template<class F, class C>
    using f = typename _recursively<
      typename _recursively_next<JLN_MP_CALL_TRACE(F, xs...)>
      ::template g<xs...>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
    >::template f<F, C>;
  };

  template<class... xs>
  struct _recursively<_recursively_next<_recursion_result<xs...>>>
  {
    template<class F, class C>
    using f = typename C::template f<xs...>;
  };

  template<bool>
  struct recursively_next_step;

  template<>
  struct recursively_next_step<true>
  {
    template<class x>
    using f = _recursively_as_much_as_possible_next<_recursion_result<x>>;
  };

  template<>
  struct recursively_next_step<false>
  {
    template<class x>
    using f = _recursively_as_much_as_possible_next<_next_recursion<x>>;
  };

  template<class x>
  struct _recursively_as_much_as_possible_next
  {
    template<class>
    using f = _recursively_as_much_as_possible_next;

    template<class... xs>
    using g = typename recursively_next_step<JLN_MP_IS_SAME(list<x>, list<xs...>)>
      ::template f<x>;
  };

  template<>
  struct _recursively_as_much_as_possible_next<stop_recursion>
  {
    template<class>
    using f = _recursively_as_much_as_possible_next;

    template<class... xs>
    using g = _recursively_as_much_as_possible_next<_recursion_result<xs...>>;
  };

  template<class... xs>
  struct _recursively_as_much_as_possible_next<_recursion_result<xs...>>
  {
    template<class>
    using f = _recursively_as_much_as_possible_next;

    template<class...>
    using g = _recursively_as_much_as_possible_next;
  };

  template<class... xs>
  struct _recursively_as_much_as_possible_next<_next_recursion<xs...>>
  {
    template<class F>
    using f = typename _recursively_as_much_as_possible_next<JLN_MP_CALL_TRACE(F, xs...)>
              ::template g<xs...>;

    template<class...>
    using g = _recursively_as_much_as_possible_next;
  };

  template<class... xs>
  struct _recursively_as_much_as_possible<_recursively_as_much_as_possible_next<_next_recursion<xs...>>>
  {
    template<class F, class C>
    using f = typename _recursively_as_much_as_possible<
      typename _recursively_as_much_as_possible_next<JLN_MP_CALL_TRACE(F, xs...)>
      ::template g<xs...>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
    >::template f<F, C>;
  };

  template<class... xs>
  struct _recursively_as_much_as_possible<_recursively_as_much_as_possible_next<_recursion_result<xs...>>>
  {
    template<class F, class C>
    using f = JLN_MP_CALL_TRACE(C, xs...);
  };
}
/// \endcond
#define JLN_MP_UNPACK(...) __VA_ARGS__

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct until_last_impl
    {};
  }
  /// \endcond

  /// \ingroup functional

  /// Uses a \c Searcher in a loop until the last result.
  /// Searcher must end with the continuations TC and FC.
  /// `until_last_t<find, is<x>, TC, FC>` is equivalent to \c find_last
  /// \treturn \sequence
  template<class Searcher>
  using until_last = typename detail::until_last_impl<Searcher>::type;

  template<template<class...> class Tpl, class Pred, class TC = listify, class FC = clear<TC>>
  using until_last_t = Tpl<Pred, recursively<
    pop_front<Tpl<Pred, next_recursion, stop_recursion>>,
    TC
  >, FC>;

  template<
    template<class...> class Tpl,
    class OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_until_last_t = Tpl<OffsetEnd, Pred, recursively<
    pop_front<Tpl<OffsetEnd, Pred, next_recursion, stop_recursion>>,
    TC
  >, FC>;

  template<
    template<int_, class...> class Tpl,
    int_ OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_until_last_t_c = Tpl<OffsetEnd, Pred, recursively<
    pop_front<Tpl<OffsetEnd, Pred, next_recursion, stop_recursion>>,
    TC
  >, FC>;

  namespace emp
  {
    template<class L, class Searcher>
    using until_last = unpack<L, mp::until_last<Searcher>>;

    template<
      class L, template<class...> class Tpl,
      class Pred, class TC = listify, class FC = clear<TC>>
    using until_last_t = unpack<L, mp::until_last_t<Tpl, Pred, TC, FC>>;

    template<
      class L, template<class...> class Tpl,
      class OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
    using partial_until_last_t = unpack<L, mp::partial_until_last_t<Tpl, OffsetEnd, Pred, TC, FC>>;

    template<
      class L, template<int_, class...> class Tpl,
      int_ OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
    using partial_until_last_t_c = unpack<L,
      mp::partial_until_last_t_c<Tpl, OffsetEnd, Pred, TC, FC>>;
  }
}

/// \cond

namespace jln::mp::detail
{
  template<class F, class TC, class FC>
  struct until_last_impl<try_<F, TC, FC>>
  {
    using type = try_<typename until_last_impl<F>::type, TC, FC>;
  };

  template<class Pred, class TC>
  struct until_last_impl<if_<Pred, TC, violation>>
  {
    using type = if_<Pred, typename until_last_impl<TC>::type, violation>;
  };

  template<template<class, class> class Tpl, class TC, class FC>
  struct until_last_impl<Tpl<TC, FC>>
  {
    using type = Tpl<recursively<
      pop_front<Tpl<next_recursion, stop_recursion>>,
      TC
    >, FC>;
  };

#define JLN_MP_MK_UNTIL_LAST_IMPL(tpl_params, arg_names)                       \
  template<                                                                    \
    template<JLN_MP_UNPACK tpl_params, class, class> class Tpl,                \
    JLN_MP_UNPACK tpl_params, class TC, class FC>                              \
  struct until_last_impl<Tpl<JLN_MP_UNPACK arg_names, TC, FC>>                 \
  {                                                                            \
    using type = Tpl<JLN_MP_UNPACK arg_names, recursively<                     \
      pop_front<Tpl<JLN_MP_UNPACK arg_names, next_recursion, stop_recursion>>, \
      TC                                                                       \
    >, FC>;                                                                    \
  }

  JLN_MP_MK_UNTIL_LAST_IMPL((class Pred), (Pred));

  JLN_MP_MK_UNTIL_LAST_IMPL((class Data1, class Pred), (Data1, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((class Data1, class Data2, class Pred),
                            (Data1, Data2, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((class Data1, class Data2, class Data3, class Pred),
                            (Data1, Data2, Data3, Pred));

  JLN_MP_MK_UNTIL_LAST_IMPL((int_ Data1, class Pred), (Data1, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((int_ Data1, class Data2, class Pred),
                            (Data1, Data2, Pred));

  JLN_MP_MK_UNTIL_LAST_IMPL((int_ Data1, int_ Data2, class Pred),
                            (Data1, Data2, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((int_ Data1, int_ Data2, class Data3, class Pred),
                            (Data1, Data2, Data3, Pred));

  JLN_MP_MK_UNTIL_LAST_IMPL((std::size_t Data1, class Pred), (Data1, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((std::size_t Data1, class Data2, class Pred),
                            (Data1, Data2, Pred));

  JLN_MP_MK_UNTIL_LAST_IMPL((std::size_t Data1, std::size_t Data2, class Pred),
                            (Data1, Data2, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((std::size_t Data1, std::size_t Data2, class Data3, class Pred),
                            (Data1, Data2, Data3, Pred));

  JLN_MP_MK_UNTIL_LAST_IMPL((int_ Data1, std::size_t Data2, class Pred),
                            (Data1, Data2, Pred));
  JLN_MP_MK_UNTIL_LAST_IMPL((int_ Data1, std::size_t Data2, class Data3, class Pred),
                            (Data1, Data2, Data3, Pred));

#undef JLN_MP_MK_UNTIL_LAST_IMPL
}
/// \endcond

namespace jln::mp
{
  /// \ingroup search

  /// Finds the last element that satisfy a \predicate.
  /// Calls \c TC with all the elements since the last found at the end.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see find_last_if_not, find_last, find
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_last_if = until_last_t<drop_until, Pred, TC, FC>;

  /// \see find_last_if, find_last, find
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_last_if_not = until_last_t<drop_while, Pred, TC, FC>;

  /// \see find_last_if, find_last_if_not, find_last, find
  template<class T, class TC = listify, class FC = clear<TC>>
  using find_last = find_last_if<is<T>, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using find_last_if = unpack<L, mp::find_last_if<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using find_last_if_not = unpack<L, mp::find_last_if_not<Pred, TC, FC>>;

    template<class L, class T, class TC = mp::listify, class FC = clear<TC>>
    using find_last = unpack<L, mp::find_last_if<mp::is<T>, TC, FC>>;
  }
}
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class S>
    struct wrapper;
  }
  /// \endcond

  /// \ingroup utility

  namespace emp
  {
    /// converts a \typelist to a \c lift<S>
    template<class L>
    using wrapper = typename detail::wrapper<L>::type;

    template<class L, class... xs>
    using rewrap = typename wrapper<L>::template f<xs...>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<template<class...> class S, class... xs>
  struct wrapper<S<xs...>>
  {
    using type = lift<S>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<template<class...> class, class>
    struct _flatten_once;

    template<template<class...> class, class>
    struct _flatten;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Remove 1 dimension level from a sequence.
  /// \semantics
  ///   \code
  ///   call<flatten_once<>, list<a, b>, c, list<list<d, e>, f>
  ///   ==
  ///   list<a, b, c, list<d, e>, f>
  ///   \endcode
  /// \treturn \sequence
  /// \see flatten
  template<class S = lift<list>, class C = listify>
  struct flatten_once
  {};

  template<template<class...> class S, class C>
  struct flatten_once<lift<S, identity>, C>
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(C)::template f, typename detail::_flatten_once<S, xs>::type...>
      ::type;
  };

  template<template<class...> class S, class C = listify>
  using flatten_once_f = flatten_once<lift<S>, C>;

  /// Recursive version of \c flatten_once.
  ///   \code
  ///   call<flatten<>, list<a, b>, c, list<list<d, e>, f>
  ///   ==
  ///   list<a, b, c, d, e, f>
  ///   \endcode
  /// \treturn \sequence
  /// \see flatten_once
  template<class S = lift<list>, class C = listify>
  struct flatten
  {};

  template<template<class...> class S, class C>
  struct flatten<lift<S, identity>, C>
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(C)::template f, typename detail::_flatten<S, xs>::type...>
      ::type;
  };

  template<template<class...> class S, class C = listify>
  using flatten_f = flatten<lift<S>, C>;

  namespace emp
  {
    template<class L, class S = wrapper<L>, class C = mp::listify>
    using flatten_once = unpack<L, mp::flatten_once<S, C>>;

    template<class L, class S = wrapper<L>, class C = mp::listify>
    using flatten = unpack<L, mp::flatten<S, C>>;

    template<class L, template<class...> class S, class C = mp::listify>
    using flatten_once_f = unpack<L, mp::flatten_once_f<S, C>>;

    template<class L, template<class...> class S, class C = mp::listify>
    using flatten_f = unpack<L, mp::flatten_f<S, C>>;
  }

/// \cond
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
  template<template<class...> class S, template<class...> class C>
  struct flatten_once<lift<S, identity>, lift<C>>
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<C, typename detail::_flatten_once<S, xs>::type...>
      ::type;
  };

  template<template<class...> class S, template<class...> class C>
  struct flatten<lift<S, identity>, lift<C>>
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<C, typename detail::_flatten<S, xs>::type...>
      ::type;
  };
#endif
/// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template<template<class...> class, class T>
  struct _flatten_once
  {
    using type = list<T>;
  };

  template<template<class...> class S, class... xs>
  struct _flatten_once<S, S<xs...>>
  {
    using type = list<xs...>;
  };

  template<template<class...> class, class T>
  struct _flatten
  {
    using type = list<T>;
  };

  template<template<class...> class S, class... xs>
  struct _flatten<S, S<xs...>>
  : _join_select<sizeof...(xs)>
    ::template f<list, typename _flatten<S, xs>::type...>
  {};
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct fold_right_impl;
  }
  /// \endcond

  /// \ingroup reduce

  /// Folds right over a list using a binary predicate.
  /// The first element in the input pack as the state,
  /// use \c push_front<> to add state if needed.
  /// \semantics
  ///   \code
  ///   F::f<xs[1], F::f<..., F::f<xs[n-2], F::f<xs[n-1], xs[0]>>>>
  ///   \endcode
  /// \pre `sizeof...(xs) >= 1`
  /// \treturn \value
  /// \see fold, fold_tree, reverse_fold_right, fold_balanced_tree
  template<class F, class C = identity>
  struct fold_right
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::fold_right_impl<
        int(sizeof...(xs)) - 1
      >::template f<JLN_MP_TRACE_F(F)::template f, xs...>
    );
  };

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using fold_right = unpack<L,
      mp::push_front<state, mp::fold_right<F, C>>>;
  }
}


/// \cond

namespace jln::mp
{
  template<class F>
  struct fold_right<F, identity>
  {
    template<class... xs>
    using f = typename detail::fold_right_impl<
      int(sizeof...(xs)) - 1
    >::template f<JLN_MP_TRACE_F(F)::template f, xs...>;
  };

#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
  template<template<class...> class F, class C>
  struct fold_right<lift<F>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::fold_right_impl<
        int(sizeof...(xs)) - 1
      >::template f<F, xs...>
    );
  };

  template<template<class...> class F>
  struct fold_right<lift<F>, identity>
  {
    template<class... xs>
    using f = typename detail::fold_right_impl<
      int(sizeof...(xs)) - 1
    >::template f<F, xs...>;
  };
#endif
}

namespace jln::mp::detail
{
  template<int n>
  struct fold_right_impl : fold_right_impl<
      n < 8 ? 4
    : n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

#define JLN_MP_FOLD_RIGHT_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                               \
  struct fold_right_impl<n>                                \
  {                                                        \
    template<template<class...> class F, class state,      \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),              \
      class... xs>                                         \
    using f = mp_xs(F<, JLN_MP_COMMA, JLN_MP_NIL)          \
      typename fold_right_impl<sizeof...(xs)>              \
      ::template f<F, state, xs...>                        \
    mp_dup(>, JLN_MP_NIL);                                 \
  };

  JLN_MP_GEN_XS_4_8_16_64_256(JLN_MP_FOLD_RIGHT_SELECT)

#undef JLN_MP_FOLD_RIGHT_SELECT

#define JLN_MP_FOLD_RIGHT_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                               \
  struct fold_right_impl<n>                                \
  {                                                        \
    template<template<class...> class F, class state,      \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA)>              \
    using f = mp_xs(F<, JLN_MP_COMMA, JLN_MP_NIL)          \
      state mp_dup(>, JLN_MP_NIL);                         \
  };

  JLN_MP_GEN_XS_1_TO_4(JLN_MP_FOLD_RIGHT_SELECT)

#undef JLN_MP_FOLD_RIGHT_SELECT

  template<>
  struct fold_right_impl<0> : fold_impl<0>
  {};

  template<>
  struct fold_right_impl<-1>
  {};
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<uint_>
    struct _fold_tree;

    template<uint_>
    struct _fold_balanced_tree;
  }
  /// \endcond

  /// \ingroup reduce

  /// Folds tree over a list using a binary predicate.
  /// recursively fold n/2 value to the left and the rest to the right.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   F::f<fold_tree::f<...xs[0..n/2]>, fold_tree::f<...xs[n/2..n]>>
  ///   \endcode
  /// \treturn \value
  /// \see fold, fold_right, fold_balanced_tree
  template<class F, class C = identity>
  struct fold_tree
  {
    template<class... xs>
    using f = typename detail::_fold_tree<
      sizeof...(xs) < 3 ? sizeof...(xs) : 3
    >::template f<C, JLN_MP_TRACE_F(F)::template f, xs...>;
  };

  /// Folds tree over a list using a binary predicate.
  /// recursively fold (n+1)/2 value to the left and the rest to the right.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   F::f<fold_tree::f<...xs[0..(n+1)/2]>, fold_tree::f<...xs[n-(n+1)/2..n]>>
  ///   \endcode
  /// \treturn \value
  /// \see fold, fold_right, fold_tree
  template<class F, class C = identity>
  struct fold_balanced_tree
  {
    template<class... xs>
    using f = typename detail::_fold_balanced_tree<
      sizeof...(xs) < 3 ? sizeof...(xs) : 3
    >::template f<C, JLN_MP_TRACE_F(F)::template f, xs...>;
  };

  namespace emp
  {
    template<class L, class F, class C = mp::identity>
    using fold_tree = unpack<L, mp::fold_tree<F, C>>;

    template<class L, class F, class C = mp::identity>
    using fold_balanced_tree = unpack<L, mp::fold_balanced_tree<F, C>>;
  }
}



/// \cond
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
namespace jln::mp
{
  template<template<class...> class F, class C>
  struct fold_tree<lift<F>, C>
  {
    template<class... xs>
    using f = typename detail::_fold_tree<
      sizeof...(xs) < 3 ? sizeof...(xs) : 3
    >::template f<C, F, xs...>;
  };

  template<template<class...> class F, class C>
  struct fold_balanced_tree<lift<F>, C>
  {
    template<class... xs>
    using f = typename detail::_fold_balanced_tree<
      sizeof...(xs) < 3 ? sizeof...(xs) : 3
    >::template f<C, F, xs...>;
  };
}
#endif

namespace jln::mp::detail
{
  constexpr unsigned bit_ceil(unsigned n)
  {
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
  }

  template<>
  struct _fold_tree<0>
  {
    template<class C, template<class...> class F>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };

  template<>
  struct _fold_tree<1>
  {
    template<class C, template<class...> class F, class x>
    using f = JLN_MP_CALL_TRACE(C, x);
  };

  template<>
  struct _fold_tree<2>
  {
    template<class C, template<class...> class F, class x, class y>
    using f = JLN_MP_CALL_TRACE(C, F<x, y>);
  };

  template<template<class...> class F, unsigned>
  struct fold_tree_impl;

  template<template<class...> class F>
  struct fold_tree_impl<F, 0>
  {
    template<class x>
    using f = x;
  };

  template<template<class...> class F>
  struct fold_tree_impl<F, 1>
  {
    template<class x, class y>
    using f = F<x, y>;
  };

  template<template<class...> class F, unsigned n>
  struct fold_tree_impl
  {
    template<class... xs>
    using f = F<
      typename take_front_c<n, fold_tree_impl<F, n/2>>::template f<xs...>,
      typename drop_front_c<n, fold_tree_impl<F, bit_ceil(sizeof...(xs)-n)/2>>::template f<xs...>
    >;
  };

  template<>
  struct _fold_tree<3>
  {
    template<class C, template<class...> class F, class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename fold_tree_impl<F, bit_ceil(sizeof...(xs))/2>::template f<xs...>
    );
  };


  template<>
  struct _fold_balanced_tree<0>
  : _fold_tree<0>
  {};

  template<>
  struct _fold_balanced_tree<1>
  : _fold_tree<1>
  {};

  template<>
  struct _fold_balanced_tree<2>
  : _fold_tree<2>
  {};

  template<template<class...> class F, uint_>
  struct fold_balanced_tree_impl;

  template<template<class...> class F>
  struct fold_balanced_tree_impl<F, 1>
  {
    template<class x>
    using f = x;
  };

  template<template<class...> class F>
  struct fold_balanced_tree_impl<F, 2>
  {
    template<class x, class y>
    using f = F<x, y>;
  };

  template<template<class...> class F, uint_ n>
  struct fold_balanced_tree_impl
  {
    template<class... xs>
    using f = F<
      typename take_front_c<(n+1)/2, fold_balanced_tree_impl<F, (n+1)/2>>
        ::template f<xs...>,
      typename drop_front_c<(sizeof...(xs) & 0) + (n+1)/2, fold_balanced_tree_impl<F, n-(n+1)/2>>
        ::template f<xs...>
    >;
  };

  template<>
  struct _fold_balanced_tree<3>
  {
    template<class C, template<class...> class F, class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename fold_balanced_tree_impl<F, sizeof...(xs)>::template f<xs...>
    );
  };
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct fold_xs_impl;

    constexpr int_ partial_fold_xs_size(int_ i, int_ size);

    template<template<class...> class F, int_ n, class... xs>
    using partial_fold_xs_select = typename detail::fold_xs_impl<n-1>
      ::template f<F, n-1, xs...>;
  }
  /// \endcond

  /// \ingroup reduce

  /// As \c fold_xs, but stop at position \c OffsetEnd.
  template<int_ OffsetEnd, class F, class C = identity>
  struct partial_fold_xs_c
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      detail::partial_fold_xs_select<
        JLN_MP_TRACE_F(F)::template f,
        detail::partial_fold_xs_size(OffsetEnd, sizeof...(xs)),
        xs...
      >
    );
  };

  template<class OffsetEnd, class F, class C = identity>
  using partial_fold_xs = partial_fold_xs_c<OffsetEnd::value, F, C>;

  /// Folds left over a list using a mulary predicate.
  /// The first element in the input pack as the state,
  /// use \c push_front<> to add state if needed.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   F::f<... F::f<xs[0], xs[1], ..., xs[n-1]>, xs[2], ..., xs[n-1]>, ..., xs[n-1]>, ...>
  ///   \endcode
  /// \treturn \value
  /// \see fold_right, fold_tree, reverse_fold, fold_balanced_tree
#ifdef JLN_MP_DOXYGENATING
  template<class F, class C = identity>
  using fold_xs = partial_fold_xs_c<-1, F, C>;
#else
  template<class F, class C = identity>
  struct fold_xs
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      detail::partial_fold_xs_select<JLN_MP_TRACE_F(F)::template f, sizeof...(xs), xs...>
    );
  };
#endif

  namespace emp
  {
    template<class L, class OffsetEnd, class state, class F, class C = mp::identity>
    using partial_fold_xs = unpack<L,
      mp::push_front<state, mp::partial_fold_xs<OffsetEnd, F, C>>>;

    template<class L, int_ OffsetEnd, class state, class F, class C = mp::identity>
    using partial_fold_xs_c = unpack<L,
      mp::push_front<state, mp::partial_fold_xs_c<OffsetEnd, F, C>>>;

    template<class L, class state, class F, class C = mp::identity>
    using fold_xs = unpack<L,
      mp::push_front<state, mp::fold_xs<F, C>>>;
  }
}


/// \cond
namespace jln::mp
{
  template<int_ OffsetEnd, class F>
  struct partial_fold_xs_c<OffsetEnd, F, identity>
  {
    template<class... xs>
    using f = detail::partial_fold_xs_select<
      JLN_MP_TRACE_F(F)::template f,
      detail::partial_fold_xs_size(OffsetEnd, sizeof...(xs)),
      xs...
    >;
  };

  template<class F>
  struct fold_xs<F, identity>
  {
    template<class... xs>
    using f = detail::partial_fold_xs_select<JLN_MP_TRACE_F(F)::template f, sizeof...(xs), xs...>;
  };

#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
  template<int_ OffsetEnd, template<class...> class F, class C>
  struct partial_fold_xs_c<OffsetEnd, lift<F>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      detail::partial_fold_xs_select<
        F,
        detail::partial_fold_xs_size(OffsetEnd, sizeof...(xs)),
        xs...
      >
    );
  };

  template<int_ OffsetEnd, template<class...> class F>
  struct partial_fold_xs_c<OffsetEnd, lift<F>, identity>
  {
    template<class... xs>
    using f = detail::partial_fold_xs_select<
      F,
      detail::partial_fold_xs_size(OffsetEnd, sizeof...(xs)),
      xs...
    >;
  };

  template<template<class...> class F, class C>
  struct fold_xs<lift<F>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      detail::partial_fold_xs_select<F, sizeof...(xs), xs...>
    );
  };
  template<template<class...> class F>
  struct fold_xs<lift<F>, identity>
  {
    template<class... xs>
    using f = detail::partial_fold_xs_select<F, sizeof...(xs), xs...>;
  };
#endif
}

namespace jln::mp::detail
{
  constexpr int_ partial_fold_xs_size(int_ i, int_ size)
  {
    // size contains state + xs...
    return (size == 0) ? 0
      : (i >= size) ? 1
      : (i >= 0) ? i + 1
      : (i >= -size) ? size + i + 1
      : 0
      ;
  }

  template<int n>
  struct fold_xs_impl : fold_xs_impl<
      n < 8 ? 4
    : n < 16 ? 8
    : n < 64 ? 16
    : 64
  >
  {};

  template<>
  struct fold_xs_impl<-1>
  {};

  template<>
  struct fold_xs_impl<0>
  {
    template<template<class...> class, int m, class state>
    using f = state;
  };

  template<>
  struct fold_xs_impl<1>
  {
    template<template<class...> class F, int m, class state, class... xs>
    using f = F<state, xs...>;
  };

  template<>
  struct fold_xs_impl<2>
  {
    template<template<class...> class F, int m, class state,
      class _1, class... xs>
    using f = F<F<state, _1, xs...>, xs...>;
  };

  template<>
  struct fold_xs_impl<3>
  {
    template<template<class...> class F, int m, class state,
      class _1, class _2, class... xs>
    using f = F<F<F<state, _1, _2, xs...>, _2, xs...>, xs...>;
  };

  // newline='\n'
  // for n in (4, 8, 16, 64):
  //   args = ', '.join(f'class _{i}' for i in range(1,n))
  //   ps = [f'_{i}, ' for i in range(1, n)]
  //   print(f'''
  //   template<>
  //   struct fold_xs_impl<{n}>
  //   {{
  //     template<template<class...> class F, int m, class state,
  //       {args}, class... xs>
  //     using f = typename fold_xs_impl<
  //       m-{n-1}
  //     >::template f<F, m-{n-1}, {'F<' * (n-1)}state{''.join(f',{newline}      {"".join(ps[i:])}xs...>' for i in range(n))};
  //   }};
  // ''', end='')

  template<>
  struct fold_xs_impl<4>
  {
    template<template<class...> class F, int m, class state,
      class _1, class _2, class _3, class... xs>
    using f = typename fold_xs_impl<
      m-3
    >::template f<F, m-3, F<F<F<state,
      _1, _2, _3, xs...>,
      _2, _3, xs...>,
      _3, xs...>,
      xs...>;
  };

  template<>
  struct fold_xs_impl<8>
  {
    template<template<class...> class F, int m, class state,
      class _1, class _2, class _3, class _4, class _5, class _6, class _7, class... xs>
    using f = typename fold_xs_impl<
      m-7
    >::template f<F, m-7, F<F<F<F<F<F<F<state,
      _1, _2, _3, _4, _5, _6, _7, xs...>,
      _2, _3, _4, _5, _6, _7, xs...>,
      _3, _4, _5, _6, _7, xs...>,
      _4, _5, _6, _7, xs...>,
      _5, _6, _7, xs...>,
      _6, _7, xs...>,
      _7, xs...>,
      xs...>;
  };

  template<>
  struct fold_xs_impl<16>
  {
    template<template<class...> class F, int m, class state,
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10, class _11, class _12, class _13, class _14,
      class _15, class... xs>
    using f = typename fold_xs_impl<
      m-15
    >::template f<F, m-15, F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<state,
      _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _7, _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _8, _9, _10, _11, _12, _13, _14, _15, xs...>,
      _9, _10, _11, _12, _13, _14, _15, xs...>,
      _10, _11, _12, _13, _14, _15, xs...>,
      _11, _12, _13, _14, _15, xs...>,
      _12, _13, _14, _15, xs...>,
      _13, _14, _15, xs...>,
      _14, _15, xs...>,
      _15, xs...>,
      xs...>;
  };

  template<>
  struct fold_xs_impl<64>
  {
    template<template<class...> class F, int m, class state,
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10, class _11, class _12, class _13,
      class _14, class _15, class _16, class _17, class _18, class _19,
      class _20, class _21, class _22, class _23, class _24, class _25,
      class _26, class _27, class _28, class _29, class _30, class _31,
      class _32, class _33, class _34, class _35, class _36, class _37,
      class _38, class _39, class _40, class _41, class _42, class _43,
      class _44, class _45, class _46, class _47, class _48, class _49,
      class _50, class _51, class _52, class _53, class _54, class _55,
      class _56, class _57, class _58, class _59, class _60, class _61,
      class _62, class _63,
      class... xs>
    using f = typename fold_xs_impl<
      m-63
    >::template f<F, m-63, F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<
                           F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<
                           F<F<F<F<F<F<F<F<F<F<F<
      state,
      _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16,
      _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31,
      _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46,
      _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61,
      _62, _63, xs...>,
      _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17,
      _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32,
      _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47,
      _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62,
      _63, xs...>,
      _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18,
      _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33,
      _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48,
      _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63,
      xs...>,
      _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19,
      _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34,
      _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49,
      _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,
      _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35,
      _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,
      _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,
      _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35,
      _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,
      _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21,
      _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36,
      _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51,
      _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22,
      _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37,
      _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52,
      _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23,
      _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38,
      _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53,
      _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24,
      _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39,
      _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54,
      _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25,
      _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40,
      _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55,
      _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26,
      _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41,
      _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
      _57, _58, _59, _60, _61, _62, _63, xs...>,
      _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27,
      _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42,
      _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57,
      _58, _59, _60, _61, _62, _63, xs...>,
      _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28,
      _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43,
      _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58,
      _59, _60, _61, _62, _63, xs...>,
      _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29,
      _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44,
      _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59,
      _60, _61, _62, _63, xs...>,
      _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,
      _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45,
      _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,
      _61, _62, _63, xs...>,
      _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31,
      _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46,
      _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61,
      _62, _63, xs...>,
      _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32,
      _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47,
      _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62,
      _63, xs...>,
      _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33,
      _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48,
      _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63,
      xs...>,
      _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34,
      _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49,
      _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35,
      _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,
      _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36,
      _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51,
      _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37,
      _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52,
      _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38,
      _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53,
      _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39,
      _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54,
      _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40,
      _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55,
      _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41,
      _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
      _57, _58, _59, _60, _61, _62, _63, xs...>,
      _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42,
      _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57,
      _58, _59, _60, _61, _62, _63, xs...>,
      _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43,
      _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58,
      _59, _60, _61, _62, _63, xs...>,
      _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44,
      _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59,
      _60, _61, _62, _63, xs...>,
      _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45,
      _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,
      _61, _62, _63, xs...>,
      _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46,
      _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61,
      _62, _63, xs...>,
      _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47,
      _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62,
      _63, xs...>,
      _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48,
      _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63,
      xs...>,
      _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49,
      _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,
      _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51,
      _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52,
      _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53,
      _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54,
      _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55,
      _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
      _57, _58, _59, _60, _61, _62, _63, xs...>,
      _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57,
      _58, _59, _60, _61, _62, _63, xs...>,
      _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58,
      _59, _60, _61, _62, _63, xs...>,
      _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59,
      _60, _61, _62, _63, xs...>,
      _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,
      _61, _62, _63, xs...>,
      _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61,
      _62, _63, xs...>,
      _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62,
      _63, xs...>,
      _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63,
      xs...>,
      _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _55, _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _56, _57, _58, _59, _60, _61, _62, _63, xs...>,
      _57, _58, _59, _60, _61, _62, _63, xs...>,
      _58, _59, _60, _61, _62, _63, xs...>,
      _59, _60, _61, _62, _63, xs...>,
      _60, _61, _62, _63, xs...>,
      _61, _62, _63, xs...>,
      _62, _63, xs...>,
      _63, xs...>,
      xs...>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct _intersperse;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Inserts a \value between each element of a \sequence.
  /// \treturn \list
  /// \see prefix, suffix
  template<class x, class C = listify>
  struct intersperse
  {
    template<class... xs>
    using f = typename detail::_intersperse<sizeof...(xs) ? 1 : 0>
      ::template f<C, x, xs...>;
  };

  namespace emp
  {
    template<class L, class x, class C = mp::listify>
    using intersperse = unpack<L, mp::intersperse<x, C>>;
  }
}



/// \cond
namespace jln::mp::detail
{
  template<>
  struct _intersperse<0>
    : call_trace_c0_arg
  {};

  template<>
  struct _intersperse<1>
  {
    template<class C, class x, class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<pop_front<C>::template f, list<x, xs>...>::type;
  };
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_ start, int_ count, int_ stride, bool is_neg = 0 < count>
    struct iota_v_c;
  }
  /// \endcond

  /// \ingroup number

  /// Generates a sequence of \int_.
  /// \treturn \sequence of \int_
  /// \see iota
  template<class C = numbers<>>
  struct iota_v
  {
    template<class start, class count, class stride = number<1>>
    using f = typename detail::iota_v_c<start::value, count::value, stride::value>
      ::template f<C>
      #if !JLN_MP_MEMOIZED_ALIAS
      ::type
      #endif
      ;
  };

  /// \ingroup number

  /// Generates a sequence of \number.
  /// \treturn \sequence of number
  template<class C = listify>
  using iota = iota_v<numbers<C>>;

  namespace emp
  {
    template<int_ start, int_ count, int_ stride = 1, class C = mp::numbers<>>
    using iota_v_c = typename detail::iota_v_c<start, count, stride>::template f<C>
      #if !JLN_MP_MEMOIZED_ALIAS
      ::type
      #endif
      ;

    template<class start, class count, class stride = number<1>, class C = mp::numbers<>>
    using iota_v = typename detail::iota_v_c<start::value, count::value, stride::value>
      ::template f<C>
      #if !JLN_MP_MEMOIZED_ALIAS
      ::type
      #endif
      ;

    template<int_ start, int_ count, int_ stride = 1, class C = mp::listify>
    using iota_c = typename detail::iota_v_c<start, count, stride>::template f<mp::numbers<C>>
      #if !JLN_MP_MEMOIZED_ALIAS
      ::type
      #endif
      ;

    template<class start, class count, class stride = number<1>, class C = mp::listify>
    using iota = typename detail::iota_v_c<start::value, count::value, stride::value>
      ::template f<mp::numbers<C>>
      #if !JLN_MP_MEMOIZED_ALIAS
      ::type
      #endif
      ;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<int_... i>
  struct iota_c_result;

  template<class, int_... i>
  struct iota_impl
  {
    template<int_ start, int_ stride>
    using strided = iota_c_result<start + i * stride...>;
  };

  template<int_ start, int_ count, int_ stride, bool is_neg>
  struct iota_v_c
    : JLN_MP_MAKE_INTEGER_SEQUENCE(count < 0 ? -count : count, iota_impl)
    ::template strided<start, count < 0 ? -stride : stride>
  {};

#if JLN_MP_MEMOIZED_ALIAS
  template<int_... i>
  struct iota_c_result
  {
    template<class C>
    using f = typename JLN_MP_CALLER_TRACE_XS(i, C)::template f<i...>;
  };

  template<int_ count>
  struct iota_v_c<0, count, 1, false>
  {
    template<class C>
    using f = emp::make_int_sequence_v_c<count, C>;
  };
#else
  template<int_... i>
  struct iota_c_result
  {
    template<class C>
    struct f
    {
      using type = typename JLN_MP_CALLER_TRACE_XS(i, C)::template f<i...>;
    };
  };

  template<int_ count>
  struct iota_v_c<0, count, 1, false>
  {
    template<class C>
    struct f
    {
      using type = emp::make_int_sequence_v_c<count, C>;
    };
  };
#endif
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<uint_>
    struct is_disjoint_select;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks whether \value in `seqs[0]` are disjoint from the \value in `seqs[1:]`.
  /// Returns `mp::true_` when `sizeof...(seqs) < 2`
  /// \treturn \bool
  /// \see is_disjoint, is_subset, is_subset_with
  template<class Cmp = same<>, class C = identity>
  struct is_disjoint_with
  {
    template<class... seqs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::is_disjoint_select<sizeof...(seqs) < 3 ? sizeof...(seqs) : 3>
      ::template f<JLN_MP_TRACE_F(Cmp), seqs...>);
  };

  /// Checks whether \value in `seqs[0]` are disjoint from the \value in `seqs[1:]`.
  /// Returns `mp::true_` when `sizeof...(seqs) < 2`
  /// \treturn \bool
  /// \see is_disjoint_with, is_subset, is_subset_with
  template<class C = identity>
  using is_disjoint = is_disjoint_with<same<>, C>;

  namespace emp
  {
#ifdef JLN_MP_DOXYGENATING
    template<class L1, class L2, class C = mp::identity>
    using is_disjoint = typename is_disjoint<C>::template f<L1, L2>;

    template<class L1, class L2, class Cmp = same<>, class C = mp::identity>
    using is_disjoint_with = typename is_disjoint_with<Cmp, C>::template f<L1, L2>;
#endif
  }

  /// \cond
  template<class Cmp>
  struct is_disjoint_with<Cmp, identity>
  {
    template<class... seqs>
    using f = typename detail::is_disjoint_select<sizeof...(seqs) < 3 ? sizeof...(seqs) : 3>
      ::template f<JLN_MP_TRACE_F(Cmp), seqs...>;
  };
  /// \endcond
}


/// \cond

namespace jln::mp::detail
{
  template<class Pred>
  struct is_disjoint_impl
  {
    template<class... xs>
    using f = typename is_drop_while_continue<
      typename _drop_while<sizeof...(xs)>::template f<0, Pred, xs...>
    >::type;
  };

  template<class Cmp, class... xs>
  struct is_disjoint_of
  {
    template<class x>
    using f = typename is_drop_while_continue<
      typename _drop_until<sizeof...(xs)>::template f<0, push_back<x, Cmp>, xs...>
    >::type;
  };

  template<>
  struct is_disjoint_select<0>
  {
    template<class Cmp, class... xs>
    using f = true_;
  };

  template<>
  struct is_disjoint_select<1> : is_disjoint_select<0>
  {};

  template<class Cmp, class seq0>
  using to_is_disjoint_impl = is_disjoint_impl<
    typename _unpack<lift<is_disjoint_of>, seq0, Cmp>::type
  >;

  template<>
  struct is_disjoint_select<2>
  {
    template<class Cmp, class seq0, class seq1>
    using f = typename _unpack<to_is_disjoint_impl<Cmp, seq0>, seq1>::type;
  };

  template<>
  struct is_disjoint_select<3>
  {
    template<class Cmp, class seq0, class... seqs>
    using f = typename is_drop_while_continue<
      typename _drop_while<sizeof...(seqs)>::template f<
        0,
        unpack<to_is_disjoint_impl<Cmp, seq0>>,
        seqs...
      >
    >::type;
  };
}

#ifndef JLN_MP_DOXYGENATING
namespace jln::mp::emp
{
  template<class L1, class L2, class C = mp::identity>
  using is_disjoint = typename C::template f<
    typename detail::is_disjoint_select<2>::f<mp::same<>, L1, L2>
  >;

  template<class L1, class L2, class Cmp = mp::same<>, class C = mp::identity>
  using is_disjoint_with = typename C::template f<
    typename detail::is_disjoint_select<2>::f<Cmp, L1, L2>
  >;
}
#endif
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_>
    struct is_sorted_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks whether a \sequence is sorted.
  /// \treturn \bool
  template<class Cmp = less<>, class C = identity>
  struct is_sorted
  {
    template<class... xs>
    using f = typename detail::is_sorted_impl<sizeof...(xs) < 3 ? sizeof...(xs) : 3>
      ::template f<C, Cmp, xs...>;
  };

  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using is_sorted = unpack<L, mp::is_sorted<Cmp, C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<>
  struct is_sorted_impl<0>
  {
    template<class C, class Cmp, class...>
    using f = JLN_MP_CALL_TRACE(C, true_);
  };

  template<>
  struct is_sorted_impl<1> : is_sorted_impl<0>
  {};

  template<>
  struct is_sorted_impl<2>
  {
    template<class C, class Cmp, class x, class y>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_RAW_EXPR_TO_BOOL(Cmp::template f<x, y>::value)>);
  };

  template<class F>
  struct bind_and_flip_2
  {
    template<class x, class y, class... xs>
    using f = typename F::template f<y, x>;
  };

  template<>
  struct is_sorted_impl<3>
  {
    template<class C, class Cmp, class... xs>
    using f = JLN_MP_CALL_TRACE(C, typename is_drop_while_continue<
      detail::drop_until_xs_call<
        sizeof...(xs)-1,
        bind_and_flip_2<JLN_MP_TRACE_F(Cmp)>, xs...
      >
    >::type);
  };
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<uint_>
    struct _is_subset;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks whether \value in `seqs[0]` are subset from the \value in `seqs[1:]`.
  /// Returns `mp::true_` when `sizeof...(seqs) < 2`
  /// \treturn \bool
  /// \see is_subset
  template<class Cmp = same<>, class C = identity>
  struct is_subset_with
  {
    template<class... seqs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::_is_subset<sizeof...(seqs) < 3 ? sizeof...(seqs) : 3>
      ::template f<JLN_MP_TRACE_F(Cmp), seqs...>
    );
  };

  /// Checks whether \value in `seqs[0]` are subset from the \value in `seqs[1:]`.
  /// Returns `mp::true_` when `sizeof...(seqs) < 2`
  /// \treturn \bool
  /// \see is_subset_with
  template<class C = identity>
  using is_subset = is_subset_with<same<>, C>;

  namespace emp
  {
#ifdef JLN_MP_DOXYGENATING
    template<class L1, class L2, class C = mp::identity>
    using is_subset = typename is_subset<C>::template f<L1, L2>;

    template<class L1, class L2, class Cmp = mp::same<>, class C = mp::identity>
    using is_subset_with = typename is_subset_with<Cmp, C>::template f<L1, L2>;
#endif
  }

  /// \cond
  template<class Cmp>
  struct is_subset_with<Cmp, identity>
  {
    template<class... seqs>
    using f = typename detail::_is_subset<sizeof...(seqs) < 3 ? sizeof...(seqs) : 3>
      ::template f<JLN_MP_TRACE_F(Cmp), seqs...>;
  };
  /// \endcond
}


/// \cond
namespace jln::mp::detail
{
  template<class Cmp, class... xs>
  struct _is_subset_of
  {
    template<class x>
    using f = number<!is_drop_while_continue<
      typename _drop_until<sizeof...(xs)>::template f<0, push_back<x, Cmp>, xs...>
    >::type::value>;
  };

  template<>
  struct _is_subset<0> : is_disjoint_select<0>
  {};

  template<>
  struct _is_subset<1> : is_disjoint_select<0>
  {};

  template<class Cmp, class seq0>
  using to_is_subset_impl = is_disjoint_impl<
    typename _unpack<lift<_is_subset_of>, seq0, Cmp>::type
  >;

  template<>
  struct _is_subset<2>
  {
    template<class Cmp, class seq0, class seq1>
    using f = typename _unpack<to_is_subset_impl<Cmp, seq0>, seq1>::type;
  };

  template<>
  struct _is_subset<3>
  {
    template<class Cmp, class seq0, class... seqs>
    using f = typename detail::is_drop_while_continue<
      typename _drop_while<sizeof...(seqs)>::template f<
        0,
        unpack<to_is_subset_impl<Cmp, seq0>>,
        seqs...
    >>::type;
  };
}

#ifndef JLN_MP_DOXYGENATING
namespace jln::mp::emp
{
  template<class L1, class L2, class C = mp::identity>
  using is_subset = typename C::template f<
    typename detail::_is_subset<2>::f<mp::same<>, L1, L2>
  >;

  template<class L1, class L2, class Cmp = mp::same<>, class C = mp::identity>
  using is_subset_with = typename C::template f<
    typename detail::_is_subset<2>::f<Cmp, L1, L2>
  >;
}
#endif
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class, class>
    struct _mismatch;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Returns mismatching info of elements from two sequences.
  /// Uses \c TC when a element mismatch and \c FC when one of
  /// the sequences equals the start of the other.
  /// \semantics
  ///   `FC::f<number<-1>, number<emp::size<seq1>>>` if \c seq1 == \c seq2.
  ///   `FC::f<number<i>, number<-1>>` if \c seq2 starts with \c seq1.
  ///   `FC::f<number<i>, number<1>>` if \c seq1 starts with \c seq2.
  ///   otherwise `TC::f<number<i>, number<0>>`.
  /// \treturn pair or \number
  template<class Cmp = equal<>, class TC = listify, class FC = TC>
  struct mismatch
  {
    template<class seq1, class seq2>
    using f = typename detail::_mismatch<seq1, seq2>::template f<JLN_MP_TRACE_F(Cmp), TC, FC>;
  };

  namespace emp
  {
    template<class seq1, class seq2, class Cmp = mp::equal<>, class TC = mp::listify, class FC = TC>
    using mismatch = typename mismatch<Cmp, TC, FC>::template f<seq1, seq2>;
  }
}



/// \cond
namespace jln::mp::detail
{
  template<class Cmp, int n>
  struct _mismatch_tree;

  template<class Cmp>
  struct _mismatch_tree<Cmp, 1>
  {
    struct type
    {
      template<class x, class y>
      using f = number<Cmp::template f<x, y>::value>;
    };
  };

  template<class Cmp>
  struct _mismatch_tree<Cmp, 2>
  {
    struct type
    {
      template<class x0, class x1, class y0, class y1>
      using f = number<
        !Cmp::template f<x0, y0>::value ? 0
      : !Cmp::template f<x1, y1>::value ? 1
      : 2
      >;
    };
  };

  template<class Cmp>
  struct _mismatch_tree<Cmp, 3>
  {
    struct type
    {
      template<class x0, class x1, class x2, class y0, class y1, class y2>
      using f = number<
        !Cmp::template f<x0, y0>::value ? 0
      : !Cmp::template f<x1, y1>::value ? 1
      : !Cmp::template f<x2, y2>::value ? 2
      : 3
      >;
    };
  };

  template<class Cmp>
  struct _mismatch_tree<Cmp, 4>
  {
    struct type
    {
      template<class x0, class x1, class x2, class x3, class y0, class y1, class y2, class y3>
      using f = number<
        !Cmp::template f<x0, y0>::value ? 0
      : !Cmp::template f<x1, y1>::value ? 1
      : !Cmp::template f<x2, y2>::value ? 2
      : !Cmp::template f<x3, y3>::value ? 3
      : 4
      >;
    };
  };

  constexpr int_ _mismatch_size(int n)
  {
    // is pow 2
    if ((-n ^ n) < -n) {
      return n/2;
    }

    if (n > 0xffff) {
      return 0x10000;
    }

    // std::bit_floor (c++20)
    int r = 1;

    if (n > 0xff) {
      r <<= 8;
      n >>= 8;
    }

    if (n > 0xf) {
      r <<= 4;
      n >>= 4;
    }

    if (n > 0b11) {
      r <<= 2;
      n >>= 2;
    }

    return (n > 0b1) ? (r << 1) : r;
  }

  template<class Cmp, int_ n, int_ size = _mismatch_size(n)>
  struct _mismatch_tree_next
  {
    template<class i, class = void>
    struct dispatch
    {
      template<unsigned, class...>
      using f = i;
    };

    template<class v>
    struct dispatch<number<size>, v>
    {
      template<unsigned dummy, class... xs>
      using f = number<size +
        drop_front_c<dummy+size,
          rotate_c<n-size,
            drop_front_c<size,
              typename _mismatch_tree<Cmp, n-size>::type
            >
          >
        >::template f<xs...>
      ::value>;
    };

    template<class... xs>
    using f = typename dispatch<
      typename rotate_impl<(sizeof...(xs) & 0) + size>::template f<
        size,
        drop_front_c<n-size,
          rotate_c<size,
            drop_front_c<n-size,
              typename _mismatch_tree<Cmp, size>::type
            >
          >
        >,
        xs...
      >
    >::template f<0u, xs...>;
  };

  template<class Cmp, int n>
  struct _mismatch_tree
  {
    using type = _mismatch_tree_next<Cmp, n>;
  };

  template<
    template<class...> class Txs, class... xs,
    template<class...> class Tys, class... ys>
  struct _mismatch<Txs<xs...>, Tys<ys...>>
  {
    template<class i, class n>
    struct apply_index
    {
      template<class C, class FC, class, class>
      using f = JLN_MP_CALL_TRACE(C, i, number<0>);
    };

    template<class n>
    struct apply_index<n, n>
    {
      template<class C, class FC, class i, class r>
      using f = JLN_MP_CALL_TRACE(FC, i, r);
    };

    // sizeof...(xs) == sizeof...(ys)
    template<bool, bool>
    struct impl
    {
      template<class Cmp, class C, class FC>
      using f = typename apply_index<
        typename _mismatch_tree<Cmp, sizeof...(xs)>::type
        ::template f<xs..., ys...>,
        number<sizeof...(xs)>
      >::template f<C, FC, number<-1>, number<sizeof...(xs)>>;
    };

    // sizeof...(xs) < sizeof...(ys)
    template<bool b>
    struct impl<true, b>
    {
      template<class Cmp, class C, class FC>
      using f = typename apply_index<
        typename take_front_c<sizeof...(xs) * 2,
          typename _mismatch_tree<Cmp, sizeof...(xs)>::type>
        ::template f<xs..., ys...>,
        number<sizeof...(xs)>
      >::template f<C, FC, number<sizeof...(xs)>, number<-1>>;
    };

    // sizeof...(xs) > sizeof...(ys)
    template<bool b>
    struct impl<b, true>
    {
      template<class Cmp, class C, class FC>
      using f = typename apply_index<
        typename take_front_c<sizeof...(ys) * 2,
          typename _mismatch_tree<Cmp, sizeof...(ys)>::type>
        ::template f<ys..., xs...>,
        number<sizeof...(ys)>
      >::template f<C, FC, number<sizeof...(ys)>, number<1>>;
    };

    template<class Cmp, class C, class FC>
    using f = typename impl<
      (sizeof...(xs) < sizeof...(ys)),
      (sizeof...(ys) < sizeof...(xs))
    >::template f<Cmp, C, FC>;
  };

  template<
    template<class...> class Txs,
    template<class...> class Tys, class... ys>
  struct _mismatch<Txs<>, Tys<ys...>>
  {
    template<class Cmp, class C, class FC>
    using f = JLN_MP_CALL_TRACE(FC, number<0>, number<-1>);
  };

  template<
    template<class...> class Txs, class... xs,
    template<class...> class Tys>
  struct _mismatch<Txs<xs...>, Tys<>>
  {
    template<class Cmp, class C, class FC>
    using f = JLN_MP_CALL_TRACE(FC, number<0>, number<1>);
  };

  template<template<class...> class Txs, template<class...> class Tys>
  struct _mismatch<Txs<>, Tys<>>
  {
    template<class Cmp, class C, class FC>
    using f = JLN_MP_CALL_TRACE(FC, number<-1>, number<0>);
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup list

  /// Retrieves an element of a sequence at an arbitrary position.
  /// \pre `0 <= N < sizeof...(xs)`
  /// \treturn \value
  template<class N, class C = identity>
  using at = drop_front<N, front<C>>;

  template<unsigned n, class C = identity>
  using at_c = drop_front_c<n, front<C>>;

  template<class C = identity>
  using at0 = front<C>;

  template<class C = identity>
  using at1 = drop_front_c<1, front<C>>;

  template<class C = identity>
  using at2 = drop_front_c<2, front<C>>;

  template<class C = identity>
  using at3 = drop_front_c<3, front<C>>;

  template<class C = identity>
  using at4 = drop_front_c<4, front<C>>;

  template<class C = identity>
  using at5 = drop_front_c<5, front<C>>;

  template<class C = identity>
  using at6 = drop_front_c<6, front<C>>;

  template<class C = identity>
  using at7 = drop_front_c<7, front<C>>;

  template<class C = identity>
  using at8 = drop_front_c<8, front<C>>;

  template<class C = identity>
  using at9 = drop_front_c<9, front<C>>;

  namespace emp
  {
    template<class L, class i, class C = mp::identity>
    using at = unpack<L, mp::drop_front_c<i::value, mp::front<C>>>;

    template<class L, unsigned i, class C = mp::identity>
    using at_c = unpack<L, mp::drop_front_c<i, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at0 = unpack<L, mp::front<C>>;

    template<class L, class C = mp::identity>
    using at1 = unpack<L, mp::drop_front_c<1, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at2 = unpack<L, mp::drop_front_c<2, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at3 = unpack<L, mp::drop_front_c<3, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at4 = unpack<L, mp::drop_front_c<4, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at5 = unpack<L, mp::drop_front_c<5, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at6 = unpack<L, mp::drop_front_c<6, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at7 = unpack<L, mp::drop_front_c<7, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at8 = unpack<L, mp::drop_front_c<8, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at9 = unpack<L, mp::drop_front_c<9, mp::front<C>>>;
  }
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class, class>
    struct _lexicographical_compare;

    template<class Cmp>
    struct _lexicographical_compare_equal;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks if \c seq1  is lexicographically less than \c seq2.
  /// \treturn \bool
  template<class Cmp = less<>, class C = identity>
  struct lexicographical_compare
  {
    template<class seq1, class seq2>
    using f = JLN_MP_CALL_TRACE(C,
      typename mismatch<
        detail::_lexicographical_compare_equal<JLN_MP_TRACE_F(Cmp)>,
        lift<detail::_lexicographical_compare>
      >
      ::template f<seq1, seq2>
      ::template f<JLN_MP_TRACE_F(Cmp), seq1, seq2>
    );
  };

  template<class CmpLess = less<>, class CmpEq = equal<>, class C = identity>
  struct lexicographical_compare2
  {
    template<class seq1, class seq2>
    using f = JLN_MP_CALL_TRACE(C,
      typename mismatch<JLN_MP_TRACE_F(CmpEq), lift<detail::_lexicographical_compare>>
      ::template f<seq1, seq2>
      ::template f<JLN_MP_TRACE_F(CmpLess), seq1, seq2>
    );
  };

  namespace emp
  {
    template<class seq1, class seq2, class Cmp = mp::less<>, class C = mp::identity>
    using lexicographical_compare = typename lexicographical_compare<Cmp, C>
      ::template f<seq1, seq2>;

    template<
      class seq1, class seq2,
      class CmpLess = mp::less<>, class CmpEq = mp::equal<>, class C = mp::identity>
    using lexicographical_compare2 = typename lexicographical_compare2<CmpLess, CmpEq, C>
      ::template f<seq1, seq2>;
  }

  /// \cond
  template<class Cmp>
  struct lexicographical_compare<Cmp, identity>
  {
    template<class seq1, class seq2>
    using f = typename mismatch<
      detail::_lexicographical_compare_equal<Cmp>,
      lift<detail::_lexicographical_compare>
    >
    ::template f<seq1, seq2>
    ::template f<Cmp, seq1, seq2>;
  };

  template<class CmpLess, class CmpEq>
  struct lexicographical_compare2<CmpLess, CmpEq, identity>
  {
    template<class seq1, class seq2>
    using f = typename mismatch<CmpEq, lift<detail::_lexicographical_compare>>
      ::template f<seq1, seq2>
      ::template f<CmpLess, seq1, seq2>;
  };
  /// \endcond
}



/// \cond
namespace jln::mp::detail
{
  template<class Cmp>
  struct _lexicographical_compare_equal
  {
    template<class x, class y>
    using f = number<!Cmp::template f<x, y>::value && !Cmp::template f<y, x>::value>;
  };

  template<class i, class n>
  struct _lexicographical_compare
  {
    template<class Cmp, class seq1, class seq2>
    using f = false_;
  };

  template<>
  struct _lexicographical_compare<number<-1>, number<0>>
  {
    template<class Cmp, class seq1, class seq2>
    using f = false_;
  };

  template<class i>
  struct _lexicographical_compare<i, number<0>>
  {
    template<class Cmp, class seq1, class seq2>
    using f = typename Cmp::template f<emp::at<seq1, i>, emp::at<seq2, i>>;
  };

  template<class i>
  struct _lexicographical_compare<i, number<-1>>
  {
    template<class Cmp, class seq1, class seq2>
    using f = true_;
  };
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct _lower_bound;

    constexpr int _lower_bound_select(unsigned n);

    template<class>
    struct optimize_cmp;
  }
  /// \endcond

  /// \ingroup search

  /// Finds first element that is not less than (i.e. greater or equal to) \c x.
  /// Calls \c TC with all the elements since the one found at the end.
  /// If no element is found, \c FC is used.
  /// \pre \c is_sorted<Cmp>::f<xs...>
  /// \treturn \sequence
  template<class x, class Cmp = less<>, class TC = listify, class FC = TC>
  struct lower_bound
  {
    template<class... xs>
    using f = typename detail::_lower_bound<
      detail::_lower_bound_select(sizeof...(xs))
    >::template f<
      sizeof...(xs),
      push_back<x, JLN_MP_TRACE_F(typename detail::optimize_cmp<Cmp>::type)>,
      TC, FC, xs...>;
  };

  template<int_ x, class Cmp = less<>, class TC = listify, class FC = TC>
  using lower_bound_c = lower_bound<number<x>, Cmp, TC, FC>;

  template<class x, class TC = listify, class FC = TC>
  using lower_bound_than = lower_bound<x, less<>, TC, FC>;

  template<int_ x, class TC = listify, class FC = TC>
  using lower_bound_than_c = lower_bound<number<x>, less<>, TC, FC>;

  namespace emp
  {
    template<class L, class x, class Cmp = mp::less<>, class TC = mp::listify, class FC = TC>
    using lower_bound = unpack<L, mp::lower_bound<x, Cmp, TC, FC>>;

    template<class L, int_ x, class Cmp = mp::less<>, class TC = mp::listify, class FC = TC>
    using lower_bound_c = unpack<L, mp::lower_bound<mp::number<x>, Cmp, TC, FC>>;

    template<class L, class x, class TC = mp::listify, class FC = TC>
    using lower_bound_than = unpack<L, mp::lower_bound<x, mp::less<>, TC, FC>>;

    template<class L, int_ x, class TC = mp::listify, class FC = TC>
    using lower_bound_than_c = unpack<L, mp::lower_bound<mp::number<x>, mp::less<>, TC, FC>>;
  }
}



/// \cond
namespace jln::mp::detail
{
  template<class Cmp>
  struct optimize_cmp
  {
    using type = Cmp;
  };

  template<class Cmp, class C>
  struct optimize_cmp<flip<tee<flip<Cmp>, C>>>
  : optimize_cmp<tee<Cmp, C>>
  {};

  template<class C>
  struct optimize_cmp<tee<less<>, C>>
  {
    using type = less<C>;
  };

  template<int>
  struct _smp_lower_bound;

  template<class Bool>
  struct _smp_conditional;

  template<>
  struct _smp_conditional<na>
  {
    template<class C, class FC>
    using f = violation;
  };

  template<>
  struct _smp_conditional<true_>
  {
    template<class C, class FC>
    using f = C;
  };

  template<>
  struct _smp_conditional<false_>
  {
    template<class C, class FC>
    using f = FC;
  };

  struct _lower_bound_violation2
  {
    template<unsigned, class...>
    using f = na;
  };

  template<class Bool>
  struct _smp_conditional2;

  template<>
  struct _smp_conditional2<na>
  {
    template<class C, class FC>
    using f = _lower_bound_violation2;
  };

  template<>
  struct _smp_conditional2<true_>
  {
    template<class C, class FC>
    using f = C;
  };

  template<>
  struct _smp_conditional2<false_>
  {
    template<class C, class FC>
    using f = FC;
  };

  constexpr int _lower_bound_select(unsigned n)
  {
    return
      n < 2 ? -int(n)
    : n < 4 ? 2
    : n < 8 ? 4
    : n < 16 ? 8
    : n < 32 ? 16
    : n < 64 ? 32
    : n < 128 ? 64
    : n < 256 ? 128
    : 256
    ;
  }

#define JLN_MP_LOWER_BOUND_IMPL(prefix, Cond)           \
  template<>                                            \
  struct prefix##lower_bound<0>                         \
  {                                                     \
    template<unsigned n, class Cmp, class C, class FC, \
      class... xs>                                      \
    using f = JLN_MP_CALL_TRACE_0_ARG(FC);              \
  };                                                    \
                                                        \
  /* original size == 1 */                              \
  template<>                                            \
  struct prefix##lower_bound<-1>                        \
  {                                                     \
    template<unsigned n, class Cmp, class C, class FC, \
      class x>                                          \
    using f = JLN_MP_CALL_TRACE_T(JLN_MP_IDENT(Cond(x)  \
      ::template f<clear<FC>, C>),                      \
      x);                                               \
  };                                                    \
                                                        \
  template<>                                            \
  struct prefix##lower_bound<1>                         \
  {                                                     \
    template<unsigned n, class Cmp, class C, class FC, \
      class x, class... xs>                             \
    using f = JLN_MP_CALL_TRACE_T(JLN_MP_IDENT(Cond(x)  \
      ::template f<pop_front<C>, C>),                   \
      x, xs...);                                        \
  };

#define JLN_MP_LOWER_BOUND_PRED_CALL(x) \
  conditional_c<JLN_MP_RAW_EXPR_TO_BOOL(Cmp::template f<x>::value)>

#define JLN_MP_LOWER_BOUND_SMP_PRED_CALL(x) \
  _smp_conditional<typename Cmp::template f<x>>

  JLN_MP_LOWER_BOUND_IMPL(_, JLN_MP_LOWER_BOUND_PRED_CALL)
  JLN_MP_LOWER_BOUND_IMPL(_smp_, JLN_MP_LOWER_BOUND_SMP_PRED_CALL)

#undef JLN_MP_LOWER_BOUND_IMPL

  template<unsigned> struct _lower_bound_drop_front;
  template<unsigned> struct _smp_lower_bound_drop_front;

#define JLN_MP_LOWER_BOUND_IMPL2(prefix, Cond, n, mp_xs) \
  template<>                                             \
  struct prefix##lower_bound_drop_front<n>               \
  {                                                      \
    template<int count, class Cmp, class C, class FC,   \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),            \
      class... xs>                                       \
    using f = typename detail::prefix##lower_bound<      \
      _lower_bound_select(count-n)                       \
    >::template f<count-n, Cmp, C, FC, xs...>;          \
  };                                                     \
                                                         \
  template<>                                             \
  struct prefix##lower_bound<n>                          \
  {                                                      \
    template<int count, class Cmp, class C, class FC,   \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),            \
      class... xs>                                       \
    using f = typename Cond(_##n)::template f<           \
      prefix##lower_bound_drop_front<n>,                 \
      prefix##lower_bound<n/2>                           \
    >::template f<count, Cmp, C, FC,                    \
      mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),       \
      xs...                                              \
    >;                                                   \
  };

#undef JLN_MP_LOWER_BOUND_SMP_PRED_CALL
#define JLN_MP_LOWER_BOUND_SMP_PRED_CALL(x) \
  _smp_conditional2<typename Cmp::template f<x>>

#define JLN_MP_LOWER_BOUND_IMPL(n, mp_xs, mp_rxs, mp_rep)             \
  JLN_MP_LOWER_BOUND_IMPL2(_, JLN_MP_LOWER_BOUND_PRED_CALL, n, mp_xs) \
  JLN_MP_LOWER_BOUND_IMPL2(_smp_, JLN_MP_LOWER_BOUND_SMP_PRED_CALL, n, mp_xs)

  JLN_MP_GEN_XS_2_4_8_16_32_64_128_256(JLN_MP_LOWER_BOUND_IMPL)

#undef JLN_MP_LOWER_BOUND_IMPL
#undef JLN_MP_LOWER_BOUND_PRED_CALL
#undef JLN_MP_LOWER_BOUND_SMP_PRED_CALL
}
/// \endcond


namespace jln::mp
{
  /// \ingroup value

#if JLN_MP_ENABLE_TPL_AUTO
# if !JLN_MP_ENABLE_DEBUG || JLN_MP_CLANG_LIKE
  template<auto v>
  struct val
  {
    static constexpr decltype(v) value = v;
  };

  template<class T, T v>
  using typed_value = val<v>;
# else
  template<class T, T v>
  struct typed_value
  {
    static constexpr T const value = v;
  };

  template<auto v>
  using val = typed_value<std::remove_const_t<decltype(v)>, v>;
# endif
#else
  template<class T, T v>
  struct typed_value
  {
    static constexpr T const value = v;
  };

  template<int_ v>
  using val = typed_value<int_, v>;
#endif
}

namespace jln::mp
{
  /// \ingroup functional

  /// Invoking \c F with its last parameters bound to bound to args.
  /// \semantics
  ///   \code
  ///   bind_back<F, c, d>::f<a, b> == F<a, b, c, d>
  ///   \endcode
  /// \treturn \sequence
  /// \see bind_front, capture_back, capture_front
  template<class F, class... BoundArgs>
  struct bind_back
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, F, xs..., BoundArgs...);
  };

  template<class F, int_... BoundArgs>
  using bind_back_c = bind_back<F, number<BoundArgs>...>;

#if JLN_MP_ENABLE_TPL_AUTO
  template<class F, auto... BoundArgs>
  using bind_back_v = bind_back<F, val<BoundArgs>...>;
#endif

  namespace emp
  {
    template<class L, class F, class... BoundArgs>
    using bind_back = unpack<L, mp::bind_back<F, BoundArgs...>>;

    template<class L, class F, int_... BoundArgs>
    using bind_back_c = unpack<L, mp::bind_back_c<F, BoundArgs...>>;

#if JLN_MP_ENABLE_TPL_AUTO
    template<class L, class F, auto... BoundArgs>
    using bind_back_v = unpack<L, mp::bind_back_v<F, BoundArgs...>>;
#endif
  }
  /// \cond
  namespace detail
  {
    template<class FillValue, class F, class EvenSizeF, class C, int_ max, class... ns>
    using matrix_longest_each_impl = _each<
      C,
      typename conditional_c<max != ns::value>
      ::template f<
        typename repeat_c<max - ns::value, F>::template f<FillValue>,
        EvenSizeF
      >
    ...>;

    constexpr int_ max_lengths();

    template<class... Ts>
    constexpr int_ max_lengths(int_ r, Ts... len);

    template<class FillValue, class F, class EvenSizeF, class C, class... ns>
    using matrix_longest_impl = matrix_longest_each_impl<
      FillValue, F, EvenSizeF, C, max_lengths(ns::value...), ns...>;
  }
  /// \endcond

  /// \ingroup group

  /// Fills a \sequence of \typelist to the longest size.
  /// \post `emp::size<result> == emp::max<emp::size<seqs>> && ...`
  /// \semantics
  ///   \code
  ///   left_matrix_longest_with<XX, listify>::f<
  ///     list<_1, _2>,
  ///     list<_1, _2, _3>,
  ///     list<_1, _2>,
  ///     list<_1, _2, _3, _4>
  ///   > = list<
  ///     list<XX, XX, _1, _2>,
  ///     list<XX, _1, _2, _3>,
  ///     list<XX, XX, _1, _2>,
  ///     list<_1, _2, _3, _4>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class FillValue, class F = listify, class C = listify>
  struct left_matrix_longest_with
  {
    template<class... seqs>
    using f = typename detail::matrix_longest_impl<
      FillValue,
      push_front<unpack<F>, lift<bind_back>>,
      typename detail::optimize_useless_unpack<unpack<F>>::type,
      C, unpack<size<>>::f<seqs>...
    >::template f<seqs...>;
  };

  template<class FillValue, class C = listify>
  using left_matrix_longest = left_matrix_longest_with<FillValue, listify, C>;

  /// Fills a \sequence of \typelist to the longest size.
  /// \post `emp::size<result> == emp::max<emp::size<seqs>> && ...`
  /// \semantics
  ///   \code
  ///   right_matrix_longest_with_matrix_longest_with<XX, listify>::f<
  ///     list<_1, _2>,
  ///     list<_1, _2, _3>,
  ///     list<_1, _2>,
  ///     list<_1, _2, _3, _4>
  ///   > = list<
  ///     list<_1, _2, XX, XX>,
  ///     list<_1, _2, _3, XX>,
  ///     list<_1, _2, XX, XX>,
  ///     list<_1, _2, _3, _4>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class FillValue, class F = listify, class C = listify>
  struct right_matrix_longest_with
  {
    template<class... seqs>
    using f = typename detail::matrix_longest_impl<
      FillValue,
      push_front<unpack_append<F>, lift<bind_back>>,
      typename detail::optimize_useless_unpack<unpack<F>>::type,
      C, unpack<size<>>::f<seqs>...
    >::template f<seqs...>;
  };

  template<class FillValue, class C = listify>
  using right_matrix_longest = right_matrix_longest_with<FillValue, listify, C>;

  namespace emp
  {
    template<class L, class FillValue, class F = mp::listify, class C = mp::listify>
    using left_matrix_longest_with = unpack<L, mp::left_matrix_longest_with<FillValue, F, C>>;

    template<class L, class FillValue, class C = mp::listify>
    using left_matrix_longest = unpack<L, mp::left_matrix_longest<FillValue, C>>;

    template<class L, class FillValue, class F = mp::listify, class C = mp::listify>
    using right_matrix_longest_with = unpack<L, mp::right_matrix_longest_with<FillValue, F, C>>;

    template<class L, class FillValue, class C = mp::listify>
    using right_matrix_longest = unpack<L, mp::right_matrix_longest<FillValue, C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  constexpr int_ max_lengths()
  {
    return 0;
  }

  template<class... Ts>
  constexpr int_ max_lengths(int_ r, Ts... len)
  {
    (..., ((len > r) ? void(r = len) : void()));
    return r;
  }
}
/// \endcond

namespace jln::mp
{
  /// \ingroup list

  /// Extracts \c N elements from the end of a \sequence.
  /// \pre `0 <= N <= sizeof...(xs)`
  /// \treturn \sequence
  /// \see take_back_max, take_front, drop_front, drop_back, take_while
  template<unsigned N, class C = listify>
  struct take_back_c
  {
    template<class... xs>
    using f = typename drop_front_c<sizeof...(xs) - N, C>
      ::template f<xs...>;
  };

  /// Extracts at most \c N elements from the end of a \sequence.
  /// \pre `0 <= N`
  /// \treturn \sequence
  /// \see take_front, take_back, take_while
  template<unsigned N, class C = listify>
  struct take_back_max_c
  {
    template<class... xs>
    using f = typename drop_front_c<sizeof...(xs) <= N ? 0 : sizeof...(xs) - N, C>
      ::template f<xs...>;
  };

  template<class N, class C = listify>
  using take_back = take_back_c<N::value, C>;

  template<class N, class C = listify>
  using take_back_max = take_back_max_c<N::value, C>;

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using take_back = unpack<L, mp::take_back<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using take_back_c = unpack<L, mp::take_back_c<n, C>>;

    template<class L, class N, class C = mp::listify>
    using take_back_max = unpack<L, mp::take_back_max<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using take_back_max_c = unpack<L, mp::take_back_max_c<n, C>>;
  }

  /// \cond
  template<class C>
  struct take_back_c<0, C>
    : detail::call_trace_xs_0<C>
  {};

  template<class C>
  struct take_back_max_c<0, C>
    : detail::call_trace_xs_0<C>
  {};

  template<>
  struct take_back_c<0, listify>
    : always<list<>>
  {};

  template<>
  struct take_back_max_c<0, listify>
    : always<list<>>
  {};
  /// \endcond
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<
      template<unsigned, class> class Take,
      class F, class EvenSizeF, class C, int_ min, class... ns>
    using matrix_shortest_each_impl = _each<
      C,
      typename conditional_c<min != ns::value>
      ::template f<unpack<Take<min, F>>, EvenSizeF>
    ...>;

    constexpr int_ min_lengths();

    template<class... Ts>
    constexpr int_ min_lengths(int_ r, Ts... len);

    template<
      template<unsigned, class> class Take,
      class F, class EvenSizeF, class C, class... ns>
    using matrix_shortest_impl = matrix_shortest_each_impl<
      Take, F, EvenSizeF, C, min_lengths(ns::value...), ns...>;
  }
  /// \endcond

  /// \ingroup group

  /// Truncates a \sequence of \typelist to the smallest size.
  /// \post `emp::size<result> == emp::min<emp::size<seqs>> && ...`
  /// \semantics
  ///   \code
  ///   left_matrix_shortest_with<listify>::f<
  ///     list<_1, _2>,
  ///     list<_1, _2, _3>,
  ///     list<_1, _2>,
  ///     list<_1, _2, _3, _4>
  ///   > = list<
  ///     list<_1, _2>,
  ///     list<_1, _2>,
  ///     list<_1, _2>,
  ///     list<_1, _2>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class F = listify, class C = listify>
  struct left_matrix_shortest_with
  {
    template<class... seqs>
    using f = typename detail::matrix_shortest_impl<
      take_front_c,
      F, typename detail::optimize_useless_unpack<unpack<F>>::type,
      C, unpack<size<>>::f<seqs>...
    >::template f<seqs...>;
  };

  template<class C = listify>
  using left_matrix_shortest = left_matrix_shortest_with<listify, C>;

  /// Truncates a \sequence of \typelist to the smallest size.
  /// \post `emp::size<result> == emp::min<emp::size<seqs>> && ...`
  /// \semantics
  ///   \code
  ///   right_matrix_shortest_with<listify>::f<
  ///     list<_1, _2>,
  ///     list<_1, _2, _3>,
  ///     list<_1, _2>,
  ///     list<_1, _2, _3, _4>
  ///   > = list<
  ///     list<_1, _2>,
  ///     list<_2, _3>,
  ///     list<_1, _2>,
  ///     list<_3, _4>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class F = listify, class C = listify>
  struct right_matrix_shortest_with
  {
    template<class... seqs>
    using f = typename detail::matrix_shortest_impl<
      take_back_c,
      F, typename detail::optimize_useless_unpack<unpack<F>>::type,
      C, unpack<size<>>::f<seqs>...
    >::template f<seqs...>;
  };

  template<class C = listify>
  using right_matrix_shortest = right_matrix_shortest_with<listify, C>;


  namespace emp
  {
    template<class L, class F = mp::listify, class C = mp::listify>
    using left_matrix_shortest_with = unpack<L, mp::left_matrix_shortest_with<F, C>>;

    template<class L, class C = mp::listify>
    using left_matrix_shortest = unpack<L, mp::left_matrix_shortest<C>>;

    template<class L, class F = mp::listify, class C = mp::listify>
    using right_matrix_shortest_with = unpack<L, mp::right_matrix_shortest_with<F, C>>;

    template<class L, class C = mp::listify>
    using right_matrix_shortest = unpack<L, mp::right_matrix_shortest<C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  constexpr int_ min_lengths()
  {
    return 0;
  }

  template<class... Ts>
  constexpr int_ min_lengths(int_ r, Ts... len)
  {
    (..., ((len < r) ? void(r = len) : void()));
    return r;
  }
}
/// \endcond



namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class L, class Seq1, class Seq2, class Cmp>
    struct merge_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Merges two \list into one sorted \sequence.
  /// \pre `emp::is_sorted<seq1, Cmp>`
  /// \pre `emp::is_sorted<seq2, Cmp>`
  /// \post \c emp::is_sorted<result...>
  /// \treturn \sequence
  template<class Cmp = less<>, class C = listify>
  struct merge
  {
    template<class seq1, class seq2>
    using f = typename detail::_unpack<
      C,
      typename detail::merge_impl<
        list<>, seq1, seq2, JLN_MP_TRACE_F(Cmp)
      >::type
    >::type;
  };

  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = listify>
    using merge = unpack<L, mp::merge<Cmp, C>>;
  }
}


/// \cond
namespace jln::mp
{
  template<class Cmp>
  struct merge<Cmp, listify>
  {
    template<class seq1, class seq2>
    using f = typename detail::merge_impl<
      list<>, seq1, seq2, JLN_MP_TRACE_F(Cmp)
    >::type;
  };
}

namespace jln::mp::detail
{
  template<bool, class L, class Seq1, class Seq2, class Cmp>
  struct merge_insert;

  template<class... R, class T0, class T1, class... Ts, class U, class... Us, class Cmp>
  struct merge_insert<true, list<R...>, list<T0, T1, Ts...>, list<U, Us...>, Cmp>
  : merge_insert<JLN_MP_RAW_EXPR_TO_BOOL_NOT(Cmp::template f<U, T1>::value),
                 list<R..., T0>, list<T1, Ts...>, list<U, Us...>, Cmp>
  {};

  template<class... R, class T, class U, class... Us, class Cmp>
  struct merge_insert<true, list<R...>, list<T>, list<U, Us...>, Cmp>
  {
    template<class... xs> using out   = list<xs..., R..., T>;
    template<class... xs> using left  = list<xs...>;
    template<class... xs> using right = list<U, Us..., xs...>;
  };

  template<class... R, class T, class... Ts, class U0, class U1, class... Us, class Cmp>
  struct merge_insert<false, list<R...>, list<T, Ts...>, list<U0, U1, Us...>, Cmp>
  : merge_insert<JLN_MP_RAW_EXPR_TO_BOOL_NOT(Cmp::template f<U1, T>::value),
                 list<R..., U0>, list<T, Ts...>, list<U1, Us...>, Cmp>
  {};

  template<class... R, class T, class... Ts, class U, class Cmp>
  struct merge_insert<false, list<R...>, list<T, Ts...>, list<U>, Cmp>
  {
    template<class... xs> using out   = list<xs..., R..., U>;
    template<class... xs> using left  = list<T, Ts..., xs...>;
    template<class... xs> using right = list<xs...>;
  };

  template<class... R, class T0, class T1, class T2, class T3, class T4, class T5,
            class T6, class T7, class T8, class T9, class... Ts, class U0, class U1,
            class U2, class U3, class U4, class U5, class U6, class U7, class U8,
            class U9, class... Us, class Cmp>
  struct merge_impl<list<R...>, list<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, Ts...>,
                    list<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9, Us...>, Cmp>
  {
    using sub = merge_insert<JLN_MP_RAW_EXPR_TO_BOOL_NOT(Cmp::template f<U0, T0>::value), list<>,
                             list<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>,
                             list<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>, Cmp>;
    using type = typename merge_impl<typename sub::template out<R...>,
                                     typename sub::template left<Ts...>,
                                     typename sub::template right<Us...>,
                                     Cmp>::type;
  };

  template<class... R, class T, class... Ts, class U, class... Us, class Cmp>
  struct merge_impl<list<R...>, list<T, Ts...>, list<U, Us...>, Cmp>
  : conditional_c<JLN_MP_RAW_EXPR_TO_BOOL_NOT(Cmp::template f<U, T>::value)>::template f<
      merge_impl<list<R..., T>, list<Ts...>, list<U, Us...>, Cmp>,
      merge_impl<list<R..., U>, list<T, Ts...>, list<Us...>, Cmp>
    >
  {};

  template<class... R, class... Ts, class Cmp>
  struct merge_impl<list<R...>, list<Ts...>, list<>, Cmp>
  {
    using type = list<R..., Ts...>;
  };

  template<class... R, class... Us, class Cmp>
  struct merge_impl<list<R...>, list<>, list<Us...>, Cmp>
  {
    using type = list<R..., Us...>;
  };

  template<class... R, class Cmp>
  struct merge_impl<list<R...>, list<>, list<>, Cmp>
  {
    using type = list<R...>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup algorithm

  /// Returns the first mismatching index of elements from two sequences, otherwise the size of the sequences.
  /// \treturn \number
  template<class Cmp = equal<>, class C = identity>
  using mismatch_index = mismatch<Cmp, at0<C>, if_<at0<is<number<-1>>>, at1<C>, at0<C>>>;

  namespace emp
  {
    template<class seq1, class seq2, class Cmp = mp::equal<>, class C = mp::identity>
    using mismatch_index = typename mismatch_index<Cmp, C>::template f<seq1, seq2>;
  }
}


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct pairwise_fold_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Computes the differences between adjacent pair of elements.
  /// \semantics
  ///   \code
  ///   pairwise_fold_and_transform_front<F, G, C>::f<a, b, c> = C::f<G::f<a>, F::f<a, b>, F::f<b, c>>
  ///   pairwise_fold_and_transform_front<F, G, C>::f<a> = C::f<G::f<a>>
  ///   pairwise_fold_and_transform_front<F, G, C>::f<> = C::f<>
  ///   \endcode
  /// \treturn \sequence
  template<class F, class Front = identity, class C = listify>
  struct pairwise_fold_and_transform_front
  {
    template<class... xs>
    using f = typename detail::pairwise_fold_impl<
      rotate_c<-1>::template f<xs...>
    >::template f<C, Front, JLN_MP_MEMOIZE(F)::template f, xs...>;
  };

  /// Computes the differences between adjacent pair of elements.
  /// \semantics
  ///   \code
  ///   pairwise_fold<F, C>::f<a, b, c> = C::f<a, F::f<a, b>, F::f<b, c>>
  ///   pairwise_fold<F, C>::f<a> = C::f<a>
  ///   pairwise_fold<F, C>::f<> = C::f<>
  ///   \endcode
  /// \treturn \sequence
  template<class F, class C = listify>
  using pairwise_fold = pairwise_fold_and_transform_front<F, identity, C>;

  namespace emp
  {
    template<class L, class F, class Front = mp::identity, class C = mp::listify>
    using pairwise_fold_and_transform_front = unpack<L,
      mp::pairwise_fold_and_transform_front<F, Front, C>
    >;

    template<class L, class F, class C = mp::listify>
    using pairwise_fold = unpack<L,
      mp::pairwise_fold_and_transform_front<F, mp::identity, C>
    >;
  }
}

/// \cond
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
namespace jln::mp
{
  template<template<class...> class F, class Front, class C>
  struct pairwise_fold_and_transform_front<lift<F>, Front, C>
  {
    template<class... xs>
    using f = typename detail::pairwise_fold_impl<
      rotate_c<-1>::template f<xs...>
    >::template f<C, Front, F, xs...>;
  };
}
#endif

namespace jln::mp::detail
{
  template<class y, class... ys>
  struct pairwise_fold_impl<list<y, ys...>>
  {
    template<class C, class Front, template<class...> class F, class x, class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_CALL_TRACE(Front, x), F<ys, xs>...);
  };

  template<>
  struct pairwise_fold_impl<list<>>
  {
    template<class C, class Front, template<class...> class F, class...>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class Left, class Right>
    struct partition_dispatch;

    template<class F, bool... bs>
    using make_partition = partition_dispatch<
      compress_c_with<F, bs...>,
      compress_c_with<F, !bs...>
    >;

    template<class F>
    struct partition_caller
    {
      template<class... xs>
      struct f : make_partition<F, xs::value...>
      {};
    };
  }
  /// \endcond

  /// \ingroup group

  /// Splits a \list in two according to a predicate.
  /// The first value contains all elements for which the predicate returns true,
  /// the second value contains all elements for which predicate returns false
  /// \treturn \sequence of two \values
  template<class Pred, class F = listify, class C = listify>
  struct partition_with
  {
    template<class... xs>
    using f = typename transform<Pred, detail::partition_caller<F>>
      ::template f<xs...>
      ::template g<JLN_MP_TRACE_F(C)::template f, identity::f, xs...>;
  };

  /// Splits a \list in two according to a predicate.
  /// The first value contains all elements for which the predicate returns true,
  /// the second value contains all elements for which predicate returns false
  /// \treturn \sequence of two \lists
  /// \see partition_with
  template<class Pred, class C = listify>
  using partition = partition_with<Pred, listify, C>;

  namespace emp
  {
    template<class L, class Pred, class F = mp::listify, class C = mp::listify>
    using partition_with = unpack<L, mp::partition_with<Pred, F, C>>;

    template<class L, class Pred, class C = mp::listify>
    using partition = unpack<L, mp::partition<Pred, C>>;
  }
}


/// \cond
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
namespace jln::mp
{
  template<class Pred, class F, template<class...> class C>
  struct partition_with<Pred, F, lift<C>>
  {
    template<class... xs>
    using f = typename transform<Pred, detail::partition_caller<F>>
      ::template f<xs...>
      ::template g<C, identity::f, xs...>;
  };
}
#endif

namespace jln::mp::detail
{
  template<class Left, class Right>
  struct partition_dispatch
  {
    template<template<class...> class C, template<class> class G, class... xs>
    using g = C<
      typename G<Left>::template f<xs...>,
      typename G<Right>::template f<xs...>
    >;
  };
}
/// \endcond


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct _permutations;

    constexpr int _permutations_select(int n);
  }
  /// \endcond

  /// \ingroup group

  /// Generates all permutations of \sequence.
  /// \post `sizeof...(result)` == `sizeof...(xs)!`
  /// \treturn \sequence of \list
  template<class C = listify>
  struct permutations
  {
    template<class... xs>
    using f = typename detail::_permutations<detail::_permutations_select(sizeof...(xs))>
      ::template f<C, xs...>;
  };

  namespace emp
  {
    template<class L, class C = listify>
    using permutations = unpack<L, mp::permutations<C>>;
  }
}



/// \cond
namespace jln::mp::detail
{
  constexpr int _permutations_select(int n)
  {
#ifdef JLN_MP_BIG_LIST_PERMUTATIONS
    // -1 with big list result (40320 elements)
    return n > 8 ? -1 : n;
#else
    // -1 with big list result (5040 elements)
    return n > 7 ? -1 : n;
#endif
  }

  template<>
  struct _permutations<-1>
  {};

  template<>
  struct _permutations<0>
    : call_trace_c0_arg
  {};

  template<>
  struct _permutations<1>
  {
    template<class C, class x>
    using f = JLN_MP_CALL_TRACE(C, list<x>);
  };

  template<>
  struct _permutations<2>
  {
    template<class C, class x0, class x1>
    using f = JLN_MP_CALL_TRACE(C,
      list<x0, x1>, list<x1, x0>
    );
  };

  template<>
  struct _permutations<3>
  {
    template<class C, class x0, class x1, class x2>
    using f = JLN_MP_CALL_TRACE(C,
      list<x0, x1, x2>, list<x0, x2, x1>,
      list<x1, x0, x2>, list<x1, x2, x0>,
      list<x2, x0, x1>, list<x2, x1, x0>
    );
  };

  template<>
  struct _permutations<4>
  {
    template<class C, class x0, class x1, class x2, class x3>
    using f = JLN_MP_CALL_TRACE(C,
      list<x0, x1, x2, x3>, list<x0, x1, x3, x2>,
      list<x0, x2, x1, x3>, list<x0, x2, x3, x1>,
      list<x0, x3, x1, x2>, list<x0, x3, x2, x1>,

      list<x1, x0, x2, x3>, list<x1, x0, x3, x2>,
      list<x1, x2, x0, x3>, list<x1, x2, x3, x0>,
      list<x1, x3, x0, x2>, list<x1, x3, x2, x0>,

      list<x2, x0, x1, x3>, list<x2, x0, x3, x1>,
      list<x2, x1, x0, x3>, list<x2, x1, x3, x0>,
      list<x2, x3, x0, x1>, list<x2, x3, x1, x0>,

      list<x3, x0, x1, x2>, list<x3, x0, x2, x1>,
      list<x3, x1, x0, x2>, list<x3, x1, x2, x0>,
      list<x3, x2, x0, x1>, list<x3, x2, x1, x0>
    );
  };

  struct _insert_permutations4
  {
    template<class x, class x0, class x1, class x2, class x3>
    using f = list<
      list<x, x0, x1, x2, x3>, list<x, x0, x1, x3, x2>,
      list<x, x0, x2, x1, x3>, list<x, x0, x2, x3, x1>,
      list<x, x0, x3, x1, x2>, list<x, x0, x3, x2, x1>,

      list<x, x1, x0, x2, x3>, list<x, x1, x0, x3, x2>,
      list<x, x1, x2, x0, x3>, list<x, x1, x2, x3, x0>,
      list<x, x1, x3, x0, x2>, list<x, x1, x3, x2, x0>,

      list<x, x2, x0, x1, x3>, list<x, x2, x0, x3, x1>,
      list<x, x2, x1, x0, x3>, list<x, x2, x1, x3, x0>,
      list<x, x2, x3, x0, x1>, list<x, x2, x3, x1, x0>,

      list<x, x3, x0, x1, x2>, list<x, x3, x0, x2, x1>,
      list<x, x3, x1, x0, x2>, list<x, x3, x1, x2, x0>,
      list<x, x3, x2, x0, x1>, list<x, x3, x2, x1, x0>
    >;
  };

  template<>
  struct _permutations<5>
  {
    template<class C, class x0, class x1, class x2, class x3, class x4>
    using f = typename join<C>::template f<
      _insert_permutations4::f<x0, x1, x2, x3, x4>,
      _insert_permutations4::f<x1, x2, x3, x4, x0>,
      _insert_permutations4::f<x2, x3, x4, x0, x1>,
      _insert_permutations4::f<x3, x4, x0, x1, x2>,
      _insert_permutations4::f<x4, x0, x1, x2, x3>
    >;
  };

  struct _push_permutations4
  {
    template<class F, class x, class x0, class x1, class x2, class x3>
    using f = list<
      typename F::template f<x, x0, x1, x2, x3>, typename F::template f<x, x0, x1, x3, x2>,
      typename F::template f<x, x0, x2, x1, x3>, typename F::template f<x, x0, x2, x3, x1>,
      typename F::template f<x, x0, x3, x1, x2>, typename F::template f<x, x0, x3, x2, x1>,

      typename F::template f<x, x1, x0, x2, x3>, typename F::template f<x, x1, x0, x3, x2>,
      typename F::template f<x, x1, x2, x0, x3>, typename F::template f<x, x1, x2, x3, x0>,
      typename F::template f<x, x1, x3, x0, x2>, typename F::template f<x, x1, x3, x2, x0>,

      typename F::template f<x, x2, x0, x1, x3>, typename F::template f<x, x2, x0, x3, x1>,
      typename F::template f<x, x2, x1, x0, x3>, typename F::template f<x, x2, x1, x3, x0>,
      typename F::template f<x, x2, x3, x0, x1>, typename F::template f<x, x2, x3, x1, x0>,

      typename F::template f<x, x3, x0, x1, x2>, typename F::template f<x, x3, x0, x2, x1>,
      typename F::template f<x, x3, x1, x0, x2>, typename F::template f<x, x3, x1, x2, x0>,
      typename F::template f<x, x3, x2, x0, x1>, typename F::template f<x, x3, x2, x1, x0>
    >;
  };

  template<class C>
  struct _permutations5
  {
    template<class F, class x0, class x1, class x2, class x3, class x4>
    using f = typename join<C>::template f<
      _push_permutations4::f<F, x0, x1, x2, x3, x4>,
      _push_permutations4::f<F, x1, x2, x3, x4, x0>,
      _push_permutations4::f<F, x2, x3, x4, x0, x1>,
      _push_permutations4::f<F, x3, x4, x0, x1, x2>,
      _push_permutations4::f<F, x4, x0, x1, x2, x3>
    >;
  };

  template<class C>
  struct _permutations6
  {
    template<class F, class x0, class x1, class x2, class x3, class x4, class x5>
    using f = typename join<C>::template f<
      _permutations5<listify>::f<push_front<x0, F>, x1, x2, x3, x4, x5>,
      _permutations5<listify>::f<push_front<x1, F>, x2, x3, x4, x5, x0>,
      _permutations5<listify>::f<push_front<x2, F>, x3, x4, x5, x0, x1>,
      _permutations5<listify>::f<push_front<x3, F>, x4, x5, x0, x1, x2>,
      _permutations5<listify>::f<push_front<x4, F>, x5, x0, x1, x2, x3>,
      _permutations5<listify>::f<push_front<x5, F>, x0, x1, x2, x3, x4>
    >;
  };

  template<>
  struct _permutations<6>
  {
    template<class C, class x0, class x1, class x2, class x3, class x4, class x5>
    using f = typename _permutations6<C>::template f<listify, x0, x1, x2, x3, x4, x5>;
  };

  template<class C>
  struct _permutations7
  {
    template<class F, class x0, class x1, class x2, class x3, class x4, class x5, class x6>
    using f = typename join<C>::template f<
      _permutations6<listify>::f<push_front<x0, F>, x1, x2, x3, x4, x5, x6>,
      _permutations6<listify>::f<push_front<x1, F>, x2, x3, x4, x5, x6, x0>,
      _permutations6<listify>::f<push_front<x2, F>, x3, x4, x5, x6, x0, x1>,
      _permutations6<listify>::f<push_front<x3, F>, x4, x5, x6, x0, x1, x2>,
      _permutations6<listify>::f<push_front<x4, F>, x5, x6, x0, x1, x2, x3>,
      _permutations6<listify>::f<push_front<x5, F>, x6, x0, x1, x2, x3, x4>,
      _permutations6<listify>::f<push_front<x6, F>, x0, x1, x2, x3, x4, x5>
    >;
  };

  template<>
  struct _permutations<7>
  {
    template<class C, class x0, class x1, class x2, class x3, class x4, class x5, class x6>
    using f = typename _permutations7<C>::template f<listify, x0, x1, x2, x3, x4, x5, x6>;
  };

#ifdef JLN_MP_BIG_LIST_PERMUTATIONS
  template<class C>
  struct _permutations8
  {
    template<class F, class x0, class x1, class x2, class x3, class x4, class x5, class x6, class x7>
    using f = typename join<C>::template f<
      _permutations7<listify>::f<push_front<x0, F>, x1, x2, x3, x4, x5, x6, x7>,
      _permutations7<listify>::f<push_front<x1, F>, x2, x3, x4, x5, x6, x7, x0>,
      _permutations7<listify>::f<push_front<x2, F>, x3, x4, x5, x6, x7, x0, x1>,
      _permutations7<listify>::f<push_front<x3, F>, x4, x5, x6, x7, x0, x1, x2>,
      _permutations7<listify>::f<push_front<x4, F>, x5, x6, x7, x0, x1, x2, x3>,
      _permutations7<listify>::f<push_front<x5, F>, x6, x7, x0, x1, x2, x3, x4>,
      _permutations7<listify>::f<push_front<x6, F>, x7, x0, x1, x2, x3, x4, x5>,
      _permutations7<listify>::f<push_front<x7, F>, x0, x1, x2, x3, x4, x5, x6>
    >;
  };

  template<>
  struct _permutations<8>
  {
    template<class C, class x0, class x1, class x2, class x3, class x4, class x5, class x6, class x7>
    using f = typename _permutations8<C>::template f<listify, x0, x1, x2, x3, x4, x5, x6, x7>;
  };
#endif
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, bool>
    struct _powerset;
  }
  /// \endcond

  /// \ingroup group

  /// Computes the powerset of a \sequence.
  /// \semantics
  ///   \code
  ///   powerset<>::f<a, b, c> == list<
  ///     list<>,
  ///     list<a>, list<b>, list<a, b>, list<c>,
  ///     list<a, c>, list<b, c>,
  ///     list<a, b, c>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  template<class C = listify>
  struct powerset
  {
    template<class... xs>
    using f = typename detail::_powerset<C, JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs))>
      ::type::template f<list<list<>>, xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using powerset = unpack<L, mp::powerset<C>>;
  }
}



/// \cond
namespace jln::mp::detail
{
  template<class, class>
  struct _power;

  template<class... xs, class y>
  struct _power<list<xs...>, y>
  {
    using type = list<list<xs...>, list<y, xs...>>;
  };

  template<class, class>
  struct powerset_impl;

  template<class... seqs, class y>
  struct powerset_impl<y, list<seqs...>>
  {
    using type = join<>::f<typename _power<seqs, y>::type...>;
  };

  template<class x, class y>
  using powerset_impl_t = typename powerset_impl<x, y>::type;

  template<class C>
  struct _powerset<C, false>
  {
    using type = fold_right<JLN_MP_LIFT_WRAP(powerset_impl), unpack<C>>;
  };

  template<>
  struct _powerset<listify, false>
  {
    using type = fold_right<JLN_MP_LIFT_WRAP(powerset_impl)>;
  };

  template<class C>
  struct _powerset<C, true>
  {
    using type = clear<C>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup algorithm

  /// Inserts a \value before each element of a \sequence.
  /// \treturn \list
  /// \see intersperse, suffix
  template<class x, class C = listify>
  struct prefix
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(C)::template f, list<x, xs>...>::type;
  };

  namespace emp
  {
    template<class L, class x, class C = mp::listify>
    using prefix = unpack<L, mp::prefix<x, C>>;
  }
}

/// \cond
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
namespace jln::mp
{
  template<class x, template<class...> class C>
  struct prefix<x, lift<C>>
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<C, list<x, xs>...>::type;
  };
}
#endif
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C>
    struct counter_to_repeat;

    template<class... xs>
    struct regroup_by_impl;
  }
  /// \endcond

  /// \ingroup group

  /// Group identical type together.
  /// Elements are sorted in order of first appearance.
  /// \semantics
  ///   \code
  ///   regroup_with<listify>::f<int, int, char, double, int, double>
  ///   == list<
  ///     list<int, int, int>,
  ///     list<char>,
  ///     list<double, double>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list of type and \number
  template<class F, class C = listify>
  using regroup_with = counter_wrapped_with<detail::counter_to_repeat<F>, C>;

  template<class C = listify>
  using regroup = regroup_with<listify, C>;

  template<class Cmp = same<>, class F = listify, class C = listify>
  struct regroup_by_with
  {
    template<class... xs>
    using f = typename unique_if<Cmp, lift<detail::regroup_by_impl>>
      ::template f<xs...>
      ::template f<C, F, Cmp, xs...>;
  };

  template<class Cmp = same<>, class C = listify>
  using regroup_by = regroup_by_with<Cmp, listify, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using regroup = unpack<L, mp::regroup<C>>;

    template<class L, class F = mp::listify, class C = mp::listify>
    using regroup_with = unpack<L, mp::regroup_with<F, C>>;

    template<class L, class Cmp = mp::same<>, class C = mp::listify>
    using regroup_by = unpack<L, mp::regroup_by<Cmp, C>>;

    template<class L, class Cmp = mp::same<>, class F = mp::listify, class C = mp::listify>
    using regroup_by_with = unpack<L, mp::regroup_by_with<Cmp, F, C>>;
  }

  /// \cond
  template<class F, class C>
  struct regroup_by_with<same<>, F, C> : regroup_with<F, C>
  {};
  /// \endcond
}



/// \cond
namespace jln::mp::detail
{
  template<class C>
  struct counter_to_repeat
  {
    template<class x, class n>
    using f = typename repeat<n, C>::template f<x>;
  };

  template<class... xs>
  struct regroup_by_impl
  {
    template<class C, class F, class Cmp, class... ys>
    using f = JLN_MP_CALL_TRACE(C,
      typename copy_if<push_front<xs, Cmp>, F>::template f<ys...>...
    );
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup filter

  /// Removes all elements that satisfy a predicate.
  /// \treturn \sequence
  template<class Pred, class C = listify>
  using remove_if = transform<wrap_in_list_if_not<Pred>, join<C>>;

  /// Removes all occurence of a \value.
  /// \treturn \sequence
  template<class T, class C = listify>
  using remove = remove_if<is<T>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using remove_if = unpack<L, mp::remove_if<Pred, C>>;

    template<class L, class T, class C = mp::listify>
    using remove = unpack<L, mp::remove<T, C>>;
  }
}


namespace jln::mp
{
  /// \ingroup filter

  /// Removes each element in a \sequence which respect a predicate with privious element.
  /// \treturn \sequence
  template<class BinaryPred, class C = listify>
  using remove_adjacent_if = pairwise_fold_and_transform_front<
    if_<BinaryPred, always<list<>>, pop_front<>>,
    listify,
    join<C>
  >;

  /// Removes each element in a \sequence which is the same type as the privious element.
  /// \treturn \sequence
  template<class C = listify>
  using remove_adjacent = remove_adjacent_if<same<>, C>;

  namespace emp
  {
    template<class L, class BinaryPred, class C = mp::listify>
    using remove_adjacent_if = unpack<L, mp::remove_adjacent_if<BinaryPred, C>>;

    template<class L, class C = mp::listify>
    using remove_adjacent = unpack<L, mp::remove_adjacent<C>>;
  }
}

namespace jln::mp
{
  /// \endcond
  namespace detail
  {
    template<class Pred, class Replacement>
    struct substitute_if;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Replaces every occurrence that satisfy a predicate by some \value.
  /// \treturn \sequence
  template<class Pred, class T, class C = listify>
  using replace_if = transform<detail::substitute_if<Pred, T>, C>;

  /// Replaces every occurrence of a \value by another \value.
  /// \treturn \sequence
  template<class T, class U, class C = listify>
  using replace = replace_if<is<T>, U, C>;

  namespace emp
  {
    template<class L, class T, class U, class C = mp::listify>
    using replace = unpack<L, mp::replace<T, U, C>>;

    template<class L, class Pred, class T, class C = mp::listify>
    using replace_if = unpack<L, mp::replace_if<Pred, T, C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class Pred, class Replacement>
  struct substitute_if
  {
    template<class x>
    using f = typename conditional_c<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_TRACE_F(Pred)::template f<x>::value)
    >::template f<x, Replacement>;
  };

  template<class T, class Replacement>
  struct substitute_if<is<T>, Replacement>
  {
    template<class x>
    using f = typename conditional_c<JLN_MP_IS_SAME(T, x)>
      ::template f<Replacement, x>;
  };

  template<class T, class Replacement>
  struct substitute_if<is_not<T>, Replacement>
  {
    template<class x>
    using f = typename conditional_c<JLN_MP_IS_SAME(T, x)>
      ::template f<x, Replacement>;
  };

#if ! JLN_MP_ENABLE_DEBUG
  template<template<class...> class Pred, class Replacement>
  struct substitute_if<lift<Pred>, Replacement>
  {
    template<class x>
    using f = typename conditional_c<JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred<x>::value)>
      ::template f<x, Replacement>;
  };

  template<template<class...> class Pred, class Replacement>
  struct substitute_if<lift_t<Pred>, Replacement>
  {
    template<class x>
    using f = typename conditional_c<JLN_MP_RAW_EXPR_TO_BOOL_NOT(Pred<x>::type::value)>
      ::template f<x, Replacement>;
  };
#endif
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned>
    struct reverse_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Reverses the order of the elements of a \sequence.
  /// \treturn \sequence
  template<class C = listify>
  struct reverse
  {
    template<class... xs>
    using f = typename detail::reverse_impl<sizeof...(xs)>
      ::template f<C, sizeof...(xs), xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using reverse = unpack<L, mp::reverse<C>>;
  }
}


/// \cond

namespace jln::mp::detail
{
  template<unsigned n>
  struct reverse_impl2 : reverse_impl2<
      n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

  template<unsigned n>
  struct reverse_impl : reverse_impl2<n>
  {};

  template<>
  struct reverse_impl2<0>
  {
    template<class C, std::size_t count, class... xs>
    using f = typename reverse<join<C>>::template f<xs...>;
  };

  template<>
  struct reverse_impl<0>
  {
    template<class C, std::size_t count, class... xs>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };

#define JLN_MP_REVERSE_IMPL(n, mp_xs, mp_rxs, mp_rep)    \
  template<>                                             \
  struct reverse_impl2<n>                                \
  {                                                      \
    template<class C, std::size_t count                  \
      mp_xs(JLN_MP_COMMA class, JLN_MP_NIL, JLN_MP_NIL), \
      class... xs>                                       \
    using f = typename reverse<join<C>>                  \
      ::template f<xs..., list<                          \
        mp_rxs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>>;  \
  };                                                     \
  template<>                                             \
  struct reverse_impl<n>                                 \
  {                                                      \
    template<class C, std::size_t count                  \
      mp_xs(JLN_MP_COMMA class, JLN_MP_NIL, JLN_MP_NIL), \
      class... xs>                                       \
    using f = JLN_MP_CALL_TRACE(C,                       \
      mp_rxs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA));     \
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_REVERSE_IMPL)

#undef JLN_MP_REVERSE_IMPL

#define JLN_MP_REVERSE_IMPL(n, mp_xs, mp_rxs, mp_rep) \
  template<>                                          \
  struct reverse_impl2<n>                             \
  {                                                   \
    template<class C, std::size_t count,              \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),         \
      class... xs>                                    \
    using f = typename reverse_impl2<                 \
      count-n                                         \
    >::template f<C, count-n, xs..., list<            \
      mp_rxs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>>; \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_REVERSE_IMPL)

#undef JLN_MP_REVERSE_IMPL
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct reverse_fold_impl;
  }
  /// \endcond

  /// \ingroup reduce

  /// Folds right over a list using a binary predicate.
  /// The first element in the input pack as the state,
  /// use \c push_front<> to add state if needed.
  /// \semantics
  ///   \code
  ///   F::f<F::f<F::f<F::f<xs[0], xs[n-1]>, x[n-2]>, ...>, x[1]>
  ///   \endcode
  /// \pre `sizeof...(xs) >= 1`
  /// \treturn \value
  /// \see fold, reverse_fold, fold_tree, fold_balanced_tree
  template<class F, class C = identity>
  struct reverse_fold
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::reverse_fold_impl<
        int(sizeof...(xs)) - 1
      >::template f<JLN_MP_TRACE_F(F)::template f, xs...>
    );
  };

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using reverse_fold = unpack<L,
      mp::push_front<state, mp::reverse_fold<F, C>>>;
  }
}


/// \cond

namespace jln::mp
{
  template<class F>
  struct reverse_fold<F, identity>
  {
    template<class... xs>
    using f = typename detail::reverse_fold_impl<
      int(sizeof...(xs)) - 1
    >::template f<JLN_MP_TRACE_F(F)::template f, xs...>;
  };

#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
  template<template<class...> class F, class C>
  struct reverse_fold<lift<F>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::reverse_fold_impl<
        int(sizeof...(xs)) - 1
      >::template f<F, xs...>
    );
  };

  template<template<class...> class F>
  struct reverse_fold<lift<F>, identity>
  {
    template<class... xs>
    using f = typename detail::reverse_fold_impl<
      int(sizeof...(xs)) - 1
    >::template f<F, xs...>;
  };
#endif
}

namespace jln::mp::detail
{
  template<int n>
  struct reverse_fold_impl : reverse_fold_impl<
      n < 8 ? 4
    : n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

#define JLN_MP_REVERSE_FOLD_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                                 \
  struct reverse_fold_impl<n>                                \
  {                                                          \
    template<template<class...> class F, class state,        \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),                \
      class... xs>                                           \
    using f = mp_dup(F<, JLN_MP_NIL)                         \
      typename reverse_fold_impl<                            \
        sizeof...(xs)                                        \
      >::template f<F, state, xs...>,                        \
    mp_rxs(JLN_MP_NIL, >, JLN_MP_COMMA);                     \
  };

  JLN_MP_GEN_XS_4_8_16_64_256(JLN_MP_REVERSE_FOLD_SELECT)

#undef JLN_MP_REVERSE_FOLD_SELECT

#define JLN_MP_REVERSE_FOLD_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                                 \
  struct reverse_fold_impl<n>                                \
  {                                                          \
    template<template<class...> class F, class state,        \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA)>                \
    using f = mp_dup(F<, JLN_MP_NIL)                         \
      state, mp_rxs(JLN_MP_NIL, >, JLN_MP_COMMA);            \
  };

  JLN_MP_GEN_XS_1_TO_4(JLN_MP_REVERSE_FOLD_SELECT)

#undef JLN_MP_REVERSE_FOLD_SELECT

  template<>
  struct reverse_fold_impl<0> : fold_impl<0>
  {};

  template<>
  struct reverse_fold_impl<-1>
  {};
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct reverse_fold_right_impl;
  }
  /// \endcond

  /// \ingroup reduce

  /// Folds right over a list using a binary predicate.
  /// This is equivalent to `reverse<fold<flip<F>, C>>`.
  /// \semantics
  ///   \code
  ///   F::f<xs[n-1], F::f<..., F::f<xs[2], F::f<xs[1], xs[0]>>>>
  ///   \endcode
  /// \pre `sizeof...(xs) >= 1`
  /// \treturn \value
  /// \see fold, fold_right, fold_tree, fold_balanced_tree
  template<class F, class C = identity>
  struct reverse_fold_right
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::reverse_fold_right_impl<int(sizeof...(xs)) - 1>
      ::template f<JLN_MP_TRACE_F(F)::template f, xs...>
    );
  };

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using reverse_fold_right = unpack<L,
      mp::push_front<state, mp::reverse_fold_right<F, C>>>;

    template<class L, class F, class C = mp::identity>
    using reverse_reduce = unpack<L, mp::reverse_fold_right<F, C>>;
  }
}


/// \cond
namespace jln::mp
{
  template<class F>
  struct reverse_fold_right<F, identity>
  {
    template<class... xs>
    using f = typename detail::reverse_fold_right_impl<int(sizeof...(xs)) - 1>
      ::template f<JLN_MP_TRACE_F(F)::template f, xs...>;
  };

#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
  template<template<class...> class F, class C>
  struct reverse_fold_right<lift<F>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::reverse_fold_right_impl<int(sizeof...(xs)) - 1>
      ::template f<F, xs...>
    );
  };

  template<template<class...> class F>
  struct reverse_fold_right<lift<F>, identity>
  {
    template<class... xs>
    using f = typename detail::reverse_fold_right_impl<int(sizeof...(xs)) - 1>
      ::template f<F, xs...>;
  };
#endif
}

namespace jln::mp::detail
{
  template<int n>
  struct reverse_fold_right_impl : reverse_fold_right_impl<
      n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

  template<>
  struct reverse_fold_right_impl<-1>
  {};

  template<>
  struct reverse_fold_right_impl<0>
  {
    template<template<class...> class, class state>
    using f = state;
  };

#define JLN_MP_REVERSE_FOLD_RIGHT_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                                       \
  struct reverse_fold_right_impl<n>                                \
  {                                                                \
    template<template<class...> class F, class state,              \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),                      \
      class... xs>                                                 \
    using f = mp_rxs(F<, JLN_MP_COMMA, JLN_MP_NIL)                 \
      state mp_dup(>, JLN_MP_NIL);                                 \
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_REVERSE_FOLD_RIGHT_SELECT)

#undef JLN_MP_REVERSE_FOLD_RIGHT_SELECT

#define JLN_MP_REVERSE_FOLD_RIGHT_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                                       \
  struct reverse_fold_right_impl<n>                                \
  {                                                                \
    template<template<class...> class F, class state,              \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),                      \
      class... xs>                                                 \
    using f = typename reverse_fold_right_impl<sizeof...(xs)>      \
      ::template f<                                                \
        F,                                                         \
        mp_rxs(F<, JLN_MP_COMMA, JLN_MP_NIL)                       \
          state mp_dup(>, JLN_MP_NIL),                             \
        xs...                                                      \
      >;                                                           \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_REVERSE_FOLD_RIGHT_SELECT)

#undef JLN_MP_REVERSE_FOLD_RIGHT_SELECT
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned>
    struct _scan;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Fold a \sequence to the left and return a list containing the successive reduction states.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   C::f<
  ///     xs[0],
  ///     F::f<xs[0], xs[1]>,
  ///     F::f<F::f<xs[0], xs[1]>, xs[2]>,
  ///     ...
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class F, class C = listify>
  struct scan
  {
    template<class... xs>
    using f = typename detail::_scan<sizeof...(xs)>
      ::template f<sizeof...(xs), C, JLN_MP_TRACE_F(F)::template f, xs...>;
  };

  namespace emp
  {
    template<class L, class F, class C = mp::listify>
    using scan = unpack<L, mp::scan<F, C>>;
  }
}



/// \cond
namespace jln::mp::detail
{
  template<unsigned n>
  struct _scan : _scan<
      n <= 16 ? 16
    : n <= 32 ? 32
    : n <= 64 ? 64
    : n <= 128 ? 128
    : 256
  >
  {};

  template<>
  struct _scan<0>
  {
    template<unsigned remaining, class C, template<class...> class F,
      class... xs>
    using f = typename join<C>::template f<xs...>;
  };

  template<>
  struct _scan<1>
  {
    template<unsigned remaining, class C, template<class...> class F,
      class _0, class... xs>
    using f = typename join<C>::template f<xs..., list<_0>>;
  };

  template<>
  struct _scan<2>
  {
    template<unsigned remaining, class C, template<class...> class F,
      class _0, class _1, class... xs>
    using f = typename join<C>::template f<xs..., list<_0, F<_0, _1>>>;
  };

  // for n in range(3,9):
  //   args=', '.join(f'class _{i}' for i in range(1,n))
  //   ps=', '.join(f'_{i}' for i in range(n))
  //   rs=', '.join(f'class r{i} = F<r{i-1}, _{i}>' for i in range(1, n-1))
  //   l=', '.join(f'r{i}' for i in range(n-1))
  //   sep=', ' if n > 2 else ''
  //   print(f'''
  //   template<>
  //   struct _scan<{n}>
  //   {{
  //     template<template<class...> class F,
  //       class r0, {args}{sep}{rs}>
  //     using g = list<{l}, F<r{n-2}, _{n-1}>>;
  //
  //     template<unsigned remaining, class C, template<class...> class F,
  //       class _0, {args}, class... xs>
  //     using f = typename join<C>::template f<xs..., g<F, {ps}>>;
  //   }};''')

  template<>
  struct _scan<3>
  {
    template<template<class...> class F,
      class r0, class _1, class _2, class r1 = F<r0, _1>>
    using g = list<r0, r1, F<r1, _2>>;

    template<unsigned remaining, class C, template<class...> class F,
      class _0, class _1, class _2, class... xs>
    using f = typename join<C>::template f<xs..., g<F, _0, _1, _2>>;
  };

  template<>
  struct _scan<4>
  {
    template<template<class...> class F,
      class r0, class _1, class _2, class _3,
      class r1 = F<r0, _1>, class r2 = F<r1, _2>>
    using g = list<r0, r1, r2, F<r2, _3>>;

    template<unsigned remaining, class C, template<class...> class F,
      class _0, class _1, class _2, class _3, class... xs>
    using f = typename join<C>::template f<xs..., g<F, _0, _1, _2, _3>>;
  };

  template<>
  struct _scan<5>
  {
    template<template<class...> class F,
      class r0, class _1, class _2, class _3, class _4,
      class r1 = F<r0, _1>, class r2 = F<r1, _2>, class r3 = F<r2, _3>>
    using g = list<r0, r1, r2, r3, F<r3, _4>>;

    template<unsigned remaining, class C, template<class...> class F,
      class _0, class _1, class _2, class _3, class _4, class... xs>
    using f = typename join<C>::template f<xs..., g<F, _0, _1, _2, _3, _4>>;
  };

  template<>
  struct _scan<6>
  {
    template<template<class...> class F,
      class r0, class _1, class _2, class _3, class _4, class _5,
      class r1 = F<r0, _1>, class r2 = F<r1, _2>, class r3 = F<r2, _3>,
      class r4 = F<r3, _4>>
    using g = list<r0, r1, r2, r3, r4, F<r4, _5>>;

    template<unsigned remaining, class C, template<class...> class F,
      class _0, class _1, class _2, class _3, class _4, class _5,
      class... xs>
    using f = typename join<C>
      ::template f<xs..., g<F, _0, _1, _2, _3, _4, _5>>;
  };

  template<>
  struct _scan<7>
  {
    template<template<class...> class F,
      class r0, class _1, class _2, class _3, class _4, class _5, class _6,
      class r1 = F<r0, _1>, class r2 = F<r1, _2>, class r3 = F<r2, _3>,
      class r4 = F<r3, _4>, class r5 = F<r4, _5>>
    using g = list<r0, r1, r2, r3, r4, r5, F<r5, _6>>;

    template<unsigned remaining, class C, template<class...> class F,
      class _0, class _1, class _2, class _3, class _4, class _5, class _6,
      class... xs>
    using f = typename join<C>
      ::template f<xs..., g<F, _0, _1, _2, _3, _4, _5, _6>>;
  };

  template<>
  struct _scan<8>
  {
    template<template<class...> class F,
      class r0, class _1, class _2, class _3, class _4, class _5, class _6,
      class _7, class r1 = F<r0, _1>, class r2 = F<r1, _2>,
      class r3 = F<r2, _3>, class r4 = F<r3, _4>, class r5 = F<r4, _5>,
      class r6 = F<r5, _6>>
    using g = list<r0, r1, r2, r3, r4, r5, r6, F<r6, _7>>;

    template<unsigned remaining, class C, template<class...> class F,
      class _0, class _1, class _2, class _3, class _4, class _5, class _6,
      class _7, class... xs>
    using f = typename join<C>::template f<xs..., g<F, _0, _1, _2, _3, _4, _5, _6, _7>>;
  };

  template<class state, class l>
  struct scan_continuation
  {
    template<
      unsigned remaining, class Next, class C,
      template<class...> class F, class... xs>
    using f = typename Next::template f<remaining, C, F, state, xs..., l>;
  };

  // for n in [8,16,32,64,128]:
  //   args=', '.join(f'class _{i}' for i in range(1, n))
  //   ps=', '.join(f'_{i}' for i in range(n))
  //   rs=', '.join(f'class r{i} = F<r{i-1}, _{i}>' for i in range(1, n-1))
  //   l=', '.join(f'r{i}' for i in range(n-1))
  //   print(f'''
  //   template<>
  //   struct _scan<{n*2}>
  //   {{
  //     template<template<class...> class F,
  //       class r0, {args},
  //       {rs},
  //     using g = scan_continuation<F<r{n-2}, _{n-1}>, list<{l}>>;
  //
  //     template<unsigned remaining, class C, template<class...> class F,
  //       class _0, {args},
  //       class... xs>
  //     using f = typename g<F, {ps}>
  //       ::template f<remaining-{n-1}, _scan<remaining-{n-1}>, C, F, xs...>;
  //   }};''')

  template<>
  struct _scan<16>
  {
    template<
      template<class...> class F, class r0, class _1, class _2, class _3,
      class _4, class _5, class _6, class _7, class r1 = F<r0, _1>,
      class r2 = F<r1, _2>, class r3 = F<r2, _3>, class r4 = F<r3, _4>,
      class r5 = F<r4, _5>, class r6 = F<r5, _6>>
    using g = scan_continuation<F<r6, _7>, list<r0, r1, r2, r3, r4, r5, r6>>;

    template<
      unsigned remaining, class C, template<class...> class F, class _0,
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class... xs>
    using f = typename g<F, _0, _1, _2, _3, _4, _5, _6, _7>::template f<
      remaining - 7, _scan<remaining - 7>, C, F, xs...>;
  };

  template<>
  struct _scan<32>
  {
    template<
      template<class...> class F, class r0, class _1, class _2, class _3,
      class _4, class _5, class _6, class _7, class _8, class _9, class _10,
      class _11, class _12, class _13, class _14, class _15, class r1 = F<r0, _1>,
      class r2 = F<r1, _2>, class r3 = F<r2, _3>, class r4 = F<r3, _4>,
      class r5 = F<r4, _5>, class r6 = F<r5, _6>, class r7 = F<r6, _7>,
      class r8 = F<r7, _8>, class r9 = F<r8, _9>, class r10 = F<r9, _10>,
      class r11 = F<r10, _11>, class r12 = F<r11, _12>, class r13 = F<r12, _13>,
      class r14 = F<r13, _14>>
    using g = scan_continuation<F<r14, _15>, list<
      r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12,
      r13, r14>>;

    template<
      unsigned remaining, class C, template<class...> class F, class _0,
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10, class _11, class _12, class _13,
      class _14, class _15,
      class... xs>
    using f = typename g<
      F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15
    >::template f<remaining - 15, _scan<remaining - 15>, C, F, xs...>;
  };

  template<>
  struct _scan<64>
  {
    template<
      template<class...> class F, class r0, class _1, class _2, class _3,
      class _4, class _5, class _6, class _7, class _8, class _9, class _10,
      class _11, class _12, class _13, class _14, class _15, class _16,
      class _17, class _18, class _19, class _20, class _21, class _22,
      class _23, class _24, class _25, class _26, class _27, class _28,
      class _29, class _30, class _31, class r1 = F<r0, _1>,
      class r2 = F<r1, _2>, class r3 = F<r2, _3>, class r4 = F<r3, _4>,
      class r5 = F<r4, _5>, class r6 = F<r5, _6>, class r7 = F<r6, _7>,
      class r8 = F<r7, _8>, class r9 = F<r8, _9>, class r10 = F<r9, _10>,
      class r11 = F<r10, _11>, class r12 = F<r11, _12>, class r13 = F<r12, _13>,
      class r14 = F<r13, _14>, class r15 = F<r14, _15>, class r16 = F<r15, _16>,
      class r17 = F<r16, _17>, class r18 = F<r17, _18>, class r19 = F<r18, _19>,
      class r20 = F<r19, _20>, class r21 = F<r20, _21>, class r22 = F<r21, _22>,
      class r23 = F<r22, _23>, class r24 = F<r23, _24>, class r25 = F<r24, _25>,
      class r26 = F<r25, _26>, class r27 = F<r26, _27>, class r28 = F<r27, _28>,
      class r29 = F<r28, _29>, class r30 = F<r29, _30>>
    using g = scan_continuation<F<r30, _31>, list<
      r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12,
      r13, r14, r15, r16, r17, r18, r19, r20, r21, r22, r23,
      r24, r25, r26, r27, r28, r29, r30>>;

    template<
      unsigned remaining, class C, template<class...> class F, class _0,
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10, class _11, class _12, class _13,
      class _14, class _15, class _16, class _17, class _18, class _19,
      class _20, class _21, class _22, class _23, class _24, class _25,
      class _26, class _27, class _28, class _29, class _30, class _31,
      class... xs>
    using f = typename g<
      F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15,
      _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,
      _31
    >::template f<remaining - 31, _scan<remaining - 31>, C, F, xs...>;
  };

  template<>
  struct _scan<128>
  {
    template<
      template<class...> class F, class r0, class _1, class _2, class _3,
      class _4, class _5, class _6, class _7, class _8, class _9, class _10,
      class _11, class _12, class _13, class _14, class _15, class _16,
      class _17, class _18, class _19, class _20, class _21, class _22,
      class _23, class _24, class _25, class _26, class _27, class _28,
      class _29, class _30, class _31, class _32, class _33, class _34,
      class _35, class _36, class _37, class _38, class _39, class _40,
      class _41, class _42, class _43, class _44, class _45, class _46,
      class _47, class _48, class _49, class _50, class _51, class _52,
      class _53, class _54, class _55, class _56, class _57, class _58,
      class _59, class _60, class _61, class _62, class _63,
      class r1 = F<r0, _1>, class r2 = F<r1, _2>, class r3 = F<r2, _3>,
      class r4 = F<r3, _4>, class r5 = F<r4, _5>, class r6 = F<r5, _6>,
      class r7 = F<r6, _7>, class r8 = F<r7, _8>, class r9 = F<r8, _9>,
      class r10 = F<r9, _10>, class r11 = F<r10, _11>, class r12 = F<r11, _12>,
      class r13 = F<r12, _13>, class r14 = F<r13, _14>, class r15 = F<r14, _15>,
      class r16 = F<r15, _16>, class r17 = F<r16, _17>, class r18 = F<r17, _18>,
      class r19 = F<r18, _19>, class r20 = F<r19, _20>, class r21 = F<r20, _21>,
      class r22 = F<r21, _22>, class r23 = F<r22, _23>, class r24 = F<r23, _24>,
      class r25 = F<r24, _25>, class r26 = F<r25, _26>, class r27 = F<r26, _27>,
      class r28 = F<r27, _28>, class r29 = F<r28, _29>, class r30 = F<r29, _30>,
      class r31 = F<r30, _31>, class r32 = F<r31, _32>, class r33 = F<r32, _33>,
      class r34 = F<r33, _34>, class r35 = F<r34, _35>, class r36 = F<r35, _36>,
      class r37 = F<r36, _37>, class r38 = F<r37, _38>, class r39 = F<r38, _39>,
      class r40 = F<r39, _40>, class r41 = F<r40, _41>, class r42 = F<r41, _42>,
      class r43 = F<r42, _43>, class r44 = F<r43, _44>, class r45 = F<r44, _45>,
      class r46 = F<r45, _46>, class r47 = F<r46, _47>, class r48 = F<r47, _48>,
      class r49 = F<r48, _49>, class r50 = F<r49, _50>, class r51 = F<r50, _51>,
      class r52 = F<r51, _52>, class r53 = F<r52, _53>, class r54 = F<r53, _54>,
      class r55 = F<r54, _55>, class r56 = F<r55, _56>, class r57 = F<r56, _57>,
      class r58 = F<r57, _58>, class r59 = F<r58, _59>, class r60 = F<r59, _60>,
      class r61 = F<r60, _61>, class r62 = F<r61, _62>>
    using g = scan_continuation<F<r62, _63>, list<
      r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15,
      r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29,
      r30, r31, r32, r33, r34, r35, r36, r37, r38, r39, r40, r41, r42, r43,
      r44, r45, r46, r47, r48, r49, r50, r51, r52, r53, r54, r55, r56, r57,
      r58, r59, r60, r61, r62>>;

    template<
      unsigned remaining, class C, template<class...> class F, class _0,
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10, class _11, class _12, class _13,
      class _14, class _15, class _16, class _17, class _18, class _19,
      class _20, class _21, class _22, class _23, class _24, class _25,
      class _26, class _27, class _28, class _29, class _30, class _31,
      class _32, class _33, class _34, class _35, class _36, class _37,
      class _38, class _39, class _40, class _41, class _42, class _43,
      class _44, class _45, class _46, class _47, class _48, class _49,
      class _50, class _51, class _52, class _53, class _54, class _55,
      class _56, class _57, class _58, class _59, class _60, class _61,
      class _62, class _63, class... xs>
    using f = typename g<
      F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15,
      _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,
      _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45,
      _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,
      _61, _62,
      _63>::template f<remaining - 63, _scan<remaining - 63>, C, F, xs...>;
  };

  template<>
  struct _scan<256>
  {
    template<
      template<class...> class F, class r0, class _1, class _2, class _3,
      class _4, class _5, class _6, class _7, class _8, class _9, class _10,
      class _11, class _12, class _13, class _14, class _15, class _16,
      class _17, class _18, class _19, class _20, class _21, class _22,
      class _23, class _24, class _25, class _26, class _27, class _28,
      class _29, class _30, class _31, class _32, class _33, class _34,
      class _35, class _36, class _37, class _38, class _39, class _40,
      class _41, class _42, class _43, class _44, class _45, class _46,
      class _47, class _48, class _49, class _50, class _51, class _52,
      class _53, class _54, class _55, class _56, class _57, class _58,
      class _59, class _60, class _61, class _62, class _63, class _64,
      class _65, class _66, class _67, class _68, class _69, class _70,
      class _71, class _72, class _73, class _74, class _75, class _76,
      class _77, class _78, class _79, class _80, class _81, class _82,
      class _83, class _84, class _85, class _86, class _87, class _88,
      class _89, class _90, class _91, class _92, class _93, class _94,
      class _95, class _96, class _97, class _98, class _99, class _100,
      class _101, class _102, class _103, class _104, class _105, class _106,
      class _107, class _108, class _109, class _110, class _111, class _112,
      class _113, class _114, class _115, class _116, class _117, class _118,
      class _119, class _120, class _121, class _122, class _123, class _124,
      class _125, class _126, class _127, class r1 = F<r0, _1>,
      class r2 = F<r1, _2>, class r3 = F<r2, _3>, class r4 = F<r3, _4>,
      class r5 = F<r4, _5>, class r6 = F<r5, _6>, class r7 = F<r6, _7>,
      class r8 = F<r7, _8>, class r9 = F<r8, _9>, class r10 = F<r9, _10>,
      class r11 = F<r10, _11>, class r12 = F<r11, _12>, class r13 = F<r12, _13>,
      class r14 = F<r13, _14>, class r15 = F<r14, _15>, class r16 = F<r15, _16>,
      class r17 = F<r16, _17>, class r18 = F<r17, _18>, class r19 = F<r18, _19>,
      class r20 = F<r19, _20>, class r21 = F<r20, _21>, class r22 = F<r21, _22>,
      class r23 = F<r22, _23>, class r24 = F<r23, _24>, class r25 = F<r24, _25>,
      class r26 = F<r25, _26>, class r27 = F<r26, _27>, class r28 = F<r27, _28>,
      class r29 = F<r28, _29>, class r30 = F<r29, _30>, class r31 = F<r30, _31>,
      class r32 = F<r31, _32>, class r33 = F<r32, _33>, class r34 = F<r33, _34>,
      class r35 = F<r34, _35>, class r36 = F<r35, _36>, class r37 = F<r36, _37>,
      class r38 = F<r37, _38>, class r39 = F<r38, _39>, class r40 = F<r39, _40>,
      class r41 = F<r40, _41>, class r42 = F<r41, _42>, class r43 = F<r42, _43>,
      class r44 = F<r43, _44>, class r45 = F<r44, _45>, class r46 = F<r45, _46>,
      class r47 = F<r46, _47>, class r48 = F<r47, _48>, class r49 = F<r48, _49>,
      class r50 = F<r49, _50>, class r51 = F<r50, _51>, class r52 = F<r51, _52>,
      class r53 = F<r52, _53>, class r54 = F<r53, _54>, class r55 = F<r54, _55>,
      class r56 = F<r55, _56>, class r57 = F<r56, _57>, class r58 = F<r57, _58>,
      class r59 = F<r58, _59>, class r60 = F<r59, _60>, class r61 = F<r60, _61>,
      class r62 = F<r61, _62>, class r63 = F<r62, _63>, class r64 = F<r63, _64>,
      class r65 = F<r64, _65>, class r66 = F<r65, _66>, class r67 = F<r66, _67>,
      class r68 = F<r67, _68>, class r69 = F<r68, _69>, class r70 = F<r69, _70>,
      class r71 = F<r70, _71>, class r72 = F<r71, _72>, class r73 = F<r72, _73>,
      class r74 = F<r73, _74>, class r75 = F<r74, _75>, class r76 = F<r75, _76>,
      class r77 = F<r76, _77>, class r78 = F<r77, _78>, class r79 = F<r78, _79>,
      class r80 = F<r79, _80>, class r81 = F<r80, _81>, class r82 = F<r81, _82>,
      class r83 = F<r82, _83>, class r84 = F<r83, _84>, class r85 = F<r84, _85>,
      class r86 = F<r85, _86>, class r87 = F<r86, _87>, class r88 = F<r87, _88>,
      class r89 = F<r88, _89>, class r90 = F<r89, _90>, class r91 = F<r90, _91>,
      class r92 = F<r91, _92>, class r93 = F<r92, _93>, class r94 = F<r93, _94>,
      class r95 = F<r94, _95>, class r96 = F<r95, _96>, class r97 = F<r96, _97>,
      class r98 = F<r97, _98>, class r99 = F<r98, _99>,
      class r100 = F<r99, _100>, class r101 = F<r100, _101>,
      class r102 = F<r101, _102>, class r103 = F<r102, _103>,
      class r104 = F<r103, _104>, class r105 = F<r104, _105>,
      class r106 = F<r105, _106>, class r107 = F<r106, _107>,
      class r108 = F<r107, _108>, class r109 = F<r108, _109>,
      class r110 = F<r109, _110>, class r111 = F<r110, _111>,
      class r112 = F<r111, _112>, class r113 = F<r112, _113>,
      class r114 = F<r113, _114>, class r115 = F<r114, _115>,
      class r116 = F<r115, _116>, class r117 = F<r116, _117>,
      class r118 = F<r117, _118>, class r119 = F<r118, _119>,
      class r120 = F<r119, _120>, class r121 = F<r120, _121>,
      class r122 = F<r121, _122>, class r123 = F<r122, _123>,
      class r124 = F<r123, _124>, class r125 = F<r124, _125>,
      class r126 = F<r125, _126>>
    using g = scan_continuation<F<r126, _127>, list<
      r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15,
      r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29,
      r30, r31, r32, r33, r34, r35, r36, r37, r38, r39, r40, r41, r42, r43,
      r44, r45, r46, r47, r48, r49, r50, r51, r52, r53, r54, r55, r56, r57,
      r58, r59, r60, r61, r62, r63, r64, r65, r66, r67, r68, r69, r70, r71,
      r72, r73, r74, r75, r76, r77, r78, r79, r80, r81, r82, r83, r84, r85,
      r86, r87, r88, r89, r90, r91, r92, r93, r94, r95, r96, r97, r98, r99,
      r100, r101, r102, r103, r104, r105, r106, r107, r108, r109, r110,
      r111, r112, r113, r114, r115, r116, r117, r118, r119, r120, r121,
      r122, r123, r124, r125, r126>>;

    template<
      unsigned remaining, class C, template<class...> class F, class _0,
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10, class _11, class _12, class _13,
      class _14, class _15, class _16, class _17, class _18, class _19,
      class _20, class _21, class _22, class _23, class _24, class _25,
      class _26, class _27, class _28, class _29, class _30, class _31,
      class _32, class _33, class _34, class _35, class _36, class _37,
      class _38, class _39, class _40, class _41, class _42, class _43,
      class _44, class _45, class _46, class _47, class _48, class _49,
      class _50, class _51, class _52, class _53, class _54, class _55,
      class _56, class _57, class _58, class _59, class _60, class _61,
      class _62, class _63, class _64, class _65, class _66, class _67,
      class _68, class _69, class _70, class _71, class _72, class _73,
      class _74, class _75, class _76, class _77, class _78, class _79,
      class _80, class _81, class _82, class _83, class _84, class _85,
      class _86, class _87, class _88, class _89, class _90, class _91,
      class _92, class _93, class _94, class _95, class _96, class _97,
      class _98, class _99, class _100, class _101, class _102, class _103,
      class _104, class _105, class _106, class _107, class _108, class _109,
      class _110, class _111, class _112, class _113, class _114, class _115,
      class _116, class _117, class _118, class _119, class _120, class _121,
      class _122, class _123, class _124, class _125, class _126, class _127,
      class... xs>
    using f = typename g<
      F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15,
      _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,
      _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45,
      _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,
      _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75,
      _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90,
      _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104,
      _105, _106, _107, _108, _109, _110, _111, _112, _113, _114, _115, _116,
      _117, _118, _119, _120, _121, _122, _123, _124, _125, _126, _127>::
      template f<remaining - 127, _scan<remaining - 127>, C, F, xs...>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class F, class C>
    struct scan_right_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Fold a \sequence to the right and return a list containing the successive reduction states.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   C::f<
  ///     ...
  ///     F::f<xs[n-3], F::f<xs[n-2], xs[n-1]>>,
  ///     F::f<xs[n-2], xs[n-1]>,
  ///     xs[n-1],
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class F, class C = listify>
  using scan_right = reverse<detail::scan_right_impl<F, C>>;

  namespace emp
  {
    template<class L, class F, class C = mp::listify>
    using scan_right = unpack<L, mp::scan_right<F, C>>;
  }
}



/// \cond
namespace jln::mp::detail
{
  template<unsigned n>
  struct _scan_right : _scan_right<
      n <= 16 ? 16
    : n <= 32 ? 32
    : n <= 64 ? 64
    : n <= 128 ? 128
    : 256
  >
  {};

  template<unsigned>
  struct _scan_right;

  template<class F, class C>
  struct scan_right_impl
  {
    template<class... xs>
    using f = typename _scan_right<sizeof...(xs)>
    ::template f<sizeof...(xs), C, JLN_MP_TRACE_F(F)::template f, xs...>;
  };

  template<>
  struct _scan_right<0>
  {
    template<unsigned remaining, class C, template<class...> class F,
      class... xs>
    using f = typename join<C>::template f<xs...>;
  };

  template<>
  struct _scan_right<1>
  {
    template<unsigned remaining, class C, template<class...> class F,
      class _0, class... xs>
    using f = typename join<C>::template f<list<_0>, xs...>;
  };

  template<>
  struct _scan_right<2>
  {
    template<unsigned remaining, class C, template<class...> class F,
      class _0, class _1, class... xs>
    using f = typename join<C>::template f<list<F<_1, _0>, _0>, xs...>;
  };

  // for n in range(3,9):
  //   args=', '.join(f'class _{i}' for i in range(1,n))
  //   ps=', '.join(f'_{i}' for i in range(n))
  //   rs=', '.join(f'class r{i} = F<_{i}, r{i-1}>' for i in range(1, n-1))
  //   l=', '.join(f'r{i}' for i in range(n-2, -1, -1))
  //   sep=', ' if n > 2 else ''
  //   print(f'''
  //   template<>
  //   struct _scan_right<{n}>
  //   {{
  //     template<template<class...> class F,
  //       class r0, {args}{sep}{rs}>
  //     using g = list<F<_{n-1}, r{n-2}>, {l}>;
  //
  //     template<unsigned remaining, class C, template<class...> class F,
  //       class _0, {args}, class... xs>
  //     using f = typename join<C>::template f<g<F, {ps}>, xs...>;
  //   }};''')

  template<>
  struct _scan_right<3>
  {
    template<template<class...> class F, class r0, class _1, class _2,
             class r1 = F<_1, r0>>
    using g = list<F<_2, r1>, r1, r0>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class... xs>
    using f = typename join<C>::template f<xs..., g<F, _0, _1, _2>>;
  };

  template<>
  struct _scan_right<4>
  {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
              class r1 = F<_1, r0>, class r2 = F<_2, r1>>
    using g = list<F<_3, r2>, r2, r1, r0>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class... xs>
    using f = typename join<C>::template f<g<F, _0, _1, _2, _3>, xs...>;
  };

  template<>
  struct _scan_right<5>
  {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
             class _4, class r1 = F<_1, r0>, class r2 = F<_2, r1>,
             class r3 = F<_3, r2>>
    using g = list<F<_4, r3>, r3, r2, r1, r0>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class... xs>
    using f = typename join<C>::template f<g<F, _0, _1, _2, _3, _4>, xs...>;
  };

  template<>
  struct _scan_right<6>
  {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
             class _4, class _5, class r1 = F<_1, r0>, class r2 = F<_2, r1>,
             class r3 = F<_3, r2>, class r4 = F<_4, r3>>
    using g = list<F<_5, r4>, r4, r3, r2, r1, r0>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
              class _1, class _2, class _3, class _4, class _5, class... xs>
    using f = typename join<C>::template f<g<F, _0, _1, _2, _3, _4, _5>, xs...>;
  };

  template<>
  struct _scan_right<7>
  {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
             class _4, class _5, class _6, class r1 = F<_1, r0>,
             class r2 = F<_2, r1>, class r3 = F<_3, r2>, class r4 = F<_4, r3>,
             class r5 = F<_5, r4>>
    using g = list<F<_6, r5>, r5, r4, r3, r2, r1, r0>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class _5, class _6,
             class... xs>
    using f = typename join<C>::template f<g<F, _0, _1, _2, _3, _4, _5, _6>, xs...>;
  };

  template<>
  struct _scan_right<8>
  {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
             class _4, class _5, class _6, class _7, class r1 = F<_1, r0>,
             class r2 = F<_2, r1>, class r3 = F<_3, r2>, class r4 = F<_4, r3>,
             class r5 = F<_5, r4>, class r6 = F<_6, r5>>
    using g = list<F<_7, r6>, r6, r5, r4, r3, r2, r1, r0>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class _5, class _6,
             class _7, class... xs>
    using f = typename join<C>::template f<g<F, _0, _1, _2, _3, _4, _5, _6, _7>, xs...>;
  };

  // for n in [8,16,32,64,128]:
  //   args=', '.join(f'class _{i}' for i in range(1, n))
  //   ps=', '.join(f'_{i}' for i in range(n))
  //   rs=', '.join(f'class r{i} = F<_{i}, r{i-1}>' for i in range(1, n-1))
  //   l=', '.join(f'r{i}' for i in range(n-2,-1,-1))
  //   print(f'''
  //   template<>
  //   struct _scan_right<{n*2}>
  //   {{
  //     template<template<class...> class F,
  //       class r0, {args},
  //       {rs}>
  //     using g = scan_continuation<F<_{n-1}, r{n-2}>, list<{l}>>;
  //
  //     template<unsigned remaining, class C, template<class...> class F,
  //       class _0, {args},
  //       class... xs>
  //     using f = typename g<F, {ps}>
  //       ::template f<remaining-{n-1}, _scan_right<remaining-{n-1}>, C, F, xs..
  // .>;
  //   }};''')

  template<> struct _scan_right<16>
  {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
             class _4, class _5, class _6, class _7, class r1 = F<_1, r0>,
             class r2 = F<_2, r1>, class r3 = F<_3, r2>, class r4 = F<_4, r3>,
             class r5 = F<_5, r4>, class r6 = F<_6, r5>>
    using g = scan_continuation<F<_7, r6>, list<r6, r5, r4, r3, r2, r1, r0>>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class _5, class _6,
             class _7, class... xs>
    using f = typename g<F, _0, _1, _2, _3, _4, _5, _6, _7>::template f<
        remaining - 7, _scan_right<remaining - 7>, C, F, xs...>;
  };

  template<> struct _scan_right<32> {
    template<template<class...> class F, class r0, class _1, class _2, class _3,
             class _4, class _5, class _6, class _7, class _8, class _9,
             class _10, class _11, class _12, class _13, class _14, class _15,
             class r1 = F<_1, r0>, class r2 = F<_2, r1>, class r3 = F<_3, r2>,
             class r4 = F<_4, r3>, class r5 = F<_5, r4>, class r6 = F<_6, r5>,
             class r7 = F<_7, r6>, class r8 = F<_8, r7>, class r9 = F<_9, r8>,
             class r10 = F<_10, r9>, class r11 = F<_11, r10>,
             class r12 = F<_12, r11>, class r13 = F<_13, r12>,
             class r14 = F<_14, r13>>
    using g =
        scan_continuation<F<_15, r14>, list<r14, r13, r12, r11, r10, r9, r8, r7,
                                            r6, r5, r4, r3, r2, r1, r0>>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class _5, class _6,
             class _7, class _8, class _9, class _10, class _11, class _12,
             class _13, class _14, class _15, class... xs>
    using f = typename g<F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12,
                         _13, _14, _15>::
        template f<remaining - 15, _scan_right<remaining - 15>, C, F, xs...>;
  };

  template<> struct _scan_right<64> {
    template<
        template<class...> class F, class r0, class _1, class _2, class _3,
        class _4, class _5, class _6, class _7, class _8, class _9, class _10,
        class _11, class _12, class _13, class _14, class _15, class _16,
        class _17, class _18, class _19, class _20, class _21, class _22,
        class _23, class _24, class _25, class _26, class _27, class _28,
        class _29, class _30, class _31, class r1 = F<_1, r0>,
        class r2 = F<_2, r1>, class r3 = F<_3, r2>, class r4 = F<_4, r3>,
        class r5 = F<_5, r4>, class r6 = F<_6, r5>, class r7 = F<_7, r6>,
        class r8 = F<_8, r7>, class r9 = F<_9, r8>, class r10 = F<_10, r9>,
        class r11 = F<_11, r10>, class r12 = F<_12, r11>, class r13 = F<_13, r12>,
        class r14 = F<_14, r13>, class r15 = F<_15, r14>, class r16 = F<_16, r15>,
        class r17 = F<_17, r16>, class r18 = F<_18, r17>, class r19 = F<_19, r18>,
        class r20 = F<_20, r19>, class r21 = F<_21, r20>, class r22 = F<_22, r21>,
        class r23 = F<_23, r22>, class r24 = F<_24, r23>, class r25 = F<_25, r24>,
        class r26 = F<_26, r25>, class r27 = F<_27, r26>, class r28 = F<_28, r27>,
        class r29 = F<_29, r28>, class r30 = F<_30, r29>>
    using g =
        scan_continuation<F<_31, r30>,
                          list<r30, r29, r28, r27, r26, r25, r24, r23, r22, r21,
                               r20, r19, r18, r17, r16, r15, r14, r13, r12, r11,
                               r10, r9, r8, r7, r6, r5, r4, r3, r2, r1, r0>>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class _5, class _6,
             class _7, class _8, class _9, class _10, class _11, class _12,
             class _13, class _14, class _15, class _16, class _17, class _18,
             class _19, class _20, class _21, class _22, class _23, class _24,
             class _25, class _26, class _27, class _28, class _29, class _30,
             class _31, class... xs>
    using f = typename g<F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12,
                         _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23,
                         _24, _25, _26, _27, _28, _29, _30, _31>::
        template f<remaining - 31, _scan_right<remaining - 31>, C, F, xs...>;
  };

  template<> struct _scan_right<128> {
    template<
        template<class...> class F, class r0, class _1, class _2, class _3,
        class _4, class _5, class _6, class _7, class _8, class _9, class _10,
        class _11, class _12, class _13, class _14, class _15, class _16,
        class _17, class _18, class _19, class _20, class _21, class _22,
        class _23, class _24, class _25, class _26, class _27, class _28,
        class _29, class _30, class _31, class _32, class _33, class _34,
        class _35, class _36, class _37, class _38, class _39, class _40,
        class _41, class _42, class _43, class _44, class _45, class _46,
        class _47, class _48, class _49, class _50, class _51, class _52,
        class _53, class _54, class _55, class _56, class _57, class _58,
        class _59, class _60, class _61, class _62, class _63,
        class r1 = F<_1, r0>, class r2 = F<_2, r1>, class r3 = F<_3, r2>,
        class r4 = F<_4, r3>, class r5 = F<_5, r4>, class r6 = F<_6, r5>,
        class r7 = F<_7, r6>, class r8 = F<_8, r7>, class r9 = F<_9, r8>,
        class r10 = F<_10, r9>, class r11 = F<_11, r10>, class r12 = F<_12, r11>,
        class r13 = F<_13, r12>, class r14 = F<_14, r13>, class r15 = F<_15, r14>,
        class r16 = F<_16, r15>, class r17 = F<_17, r16>, class r18 = F<_18, r17>,
        class r19 = F<_19, r18>, class r20 = F<_20, r19>, class r21 = F<_21, r20>,
        class r22 = F<_22, r21>, class r23 = F<_23, r22>, class r24 = F<_24, r23>,
        class r25 = F<_25, r24>, class r26 = F<_26, r25>, class r27 = F<_27, r26>,
        class r28 = F<_28, r27>, class r29 = F<_29, r28>, class r30 = F<_30, r29>,
        class r31 = F<_31, r30>, class r32 = F<_32, r31>, class r33 = F<_33, r32>,
        class r34 = F<_34, r33>, class r35 = F<_35, r34>, class r36 = F<_36, r35>,
        class r37 = F<_37, r36>, class r38 = F<_38, r37>, class r39 = F<_39, r38>,
        class r40 = F<_40, r39>, class r41 = F<_41, r40>, class r42 = F<_42, r41>,
        class r43 = F<_43, r42>, class r44 = F<_44, r43>, class r45 = F<_45, r44>,
        class r46 = F<_46, r45>, class r47 = F<_47, r46>, class r48 = F<_48, r47>,
        class r49 = F<_49, r48>, class r50 = F<_50, r49>, class r51 = F<_51, r50>,
        class r52 = F<_52, r51>, class r53 = F<_53, r52>, class r54 = F<_54, r53>,
        class r55 = F<_55, r54>, class r56 = F<_56, r55>, class r57 = F<_57, r56>,
        class r58 = F<_58, r57>, class r59 = F<_59, r58>, class r60 = F<_60, r59>,
        class r61 = F<_61, r60>, class r62 = F<_62, r61>>
    using g = scan_continuation<
        F<_63, r62>,
        list<r62, r61, r60, r59, r58, r57, r56, r55, r54, r53, r52, r51, r50, r49,
             r48, r47, r46, r45, r44, r43, r42, r41, r40, r39, r38, r37, r36, r35,
             r34, r33, r32, r31, r30, r29, r28, r27, r26, r25, r24, r23, r22, r21,
             r20, r19, r18, r17, r16, r15, r14, r13, r12, r11, r10, r9, r8, r7,
             r6, r5, r4, r3, r2, r1, r0>>;

    template<unsigned remaining, class C, template<class...> class F, class _0,
             class _1, class _2, class _3, class _4, class _5, class _6,
             class _7, class _8, class _9, class _10, class _11, class _12,
             class _13, class _14, class _15, class _16, class _17, class _18,
             class _19, class _20, class _21, class _22, class _23, class _24,
             class _25, class _26, class _27, class _28, class _29, class _30,
             class _31, class _32, class _33, class _34, class _35, class _36,
             class _37, class _38, class _39, class _40, class _41, class _42,
             class _43, class _44, class _45, class _46, class _47, class _48,
             class _49, class _50, class _51, class _52, class _53, class _54,
             class _55, class _56, class _57, class _58, class _59, class _60,
             class _61, class _62, class _63, class... xs>
    using f = typename g<F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12,
                         _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23,
                         _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34,
                         _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45,
                         _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56,
                         _57, _58, _59, _60, _61, _62, _63>::
        template f<remaining - 63, _scan_right<remaining - 63>, C, F, xs...>;
  };

  template<> struct _scan_right<256> {
    template<
        template<class...> class F, class r0, class _1, class _2, class _3,
        class _4, class _5, class _6, class _7, class _8, class _9, class _10,
        class _11, class _12, class _13, class _14, class _15, class _16,
        class _17, class _18, class _19, class _20, class _21, class _22,
        class _23, class _24, class _25, class _26, class _27, class _28,
        class _29, class _30, class _31, class _32, class _33, class _34,
        class _35, class _36, class _37, class _38, class _39, class _40,
        class _41, class _42, class _43, class _44, class _45, class _46,
        class _47, class _48, class _49, class _50, class _51, class _52,
        class _53, class _54, class _55, class _56, class _57, class _58,
        class _59, class _60, class _61, class _62, class _63, class _64,
        class _65, class _66, class _67, class _68, class _69, class _70,
        class _71, class _72, class _73, class _74, class _75, class _76,
        class _77, class _78, class _79, class _80, class _81, class _82,
        class _83, class _84, class _85, class _86, class _87, class _88,
        class _89, class _90, class _91, class _92, class _93, class _94,
        class _95, class _96, class _97, class _98, class _99, class _100,
        class _101, class _102, class _103, class _104, class _105, class _106,
        class _107, class _108, class _109, class _110, class _111, class _112,
        class _113, class _114, class _115, class _116, class _117, class _118,
        class _119, class _120, class _121, class _122, class _123, class _124,
        class _125, class _126, class _127, class r1 = F<_1, r0>,
        class r2 = F<_2, r1>, class r3 = F<_3, r2>, class r4 = F<_4, r3>,
        class r5 = F<_5, r4>, class r6 = F<_6, r5>, class r7 = F<_7, r6>,
        class r8 = F<_8, r7>, class r9 = F<_9, r8>, class r10 = F<_10, r9>,
        class r11 = F<_11, r10>, class r12 = F<_12, r11>, class r13 = F<_13, r12>,
        class r14 = F<_14, r13>, class r15 = F<_15, r14>, class r16 = F<_16, r15>,
        class r17 = F<_17, r16>, class r18 = F<_18, r17>, class r19 = F<_19, r18>,
        class r20 = F<_20, r19>, class r21 = F<_21, r20>, class r22 = F<_22, r21>,
        class r23 = F<_23, r22>, class r24 = F<_24, r23>, class r25 = F<_25, r24>,
        class r26 = F<_26, r25>, class r27 = F<_27, r26>, class r28 = F<_28, r27>,
        class r29 = F<_29, r28>, class r30 = F<_30, r29>, class r31 = F<_31, r30>,
        class r32 = F<_32, r31>, class r33 = F<_33, r32>, class r34 = F<_34, r33>,
        class r35 = F<_35, r34>, class r36 = F<_36, r35>, class r37 = F<_37, r36>,
        class r38 = F<_38, r37>, class r39 = F<_39, r38>, class r40 = F<_40, r39>,
        class r41 = F<_41, r40>, class r42 = F<_42, r41>, class r43 = F<_43, r42>,
        class r44 = F<_44, r43>, class r45 = F<_45, r44>, class r46 = F<_46, r45>,
        class r47 = F<_47, r46>, class r48 = F<_48, r47>, class r49 = F<_49, r48>,
        class r50 = F<_50, r49>, class r51 = F<_51, r50>, class r52 = F<_52, r51>,
        class r53 = F<_53, r52>, class r54 = F<_54, r53>, class r55 = F<_55, r54>,
        class r56 = F<_56, r55>, class r57 = F<_57, r56>, class r58 = F<_58, r57>,
        class r59 = F<_59, r58>, class r60 = F<_60, r59>, class r61 = F<_61, r60>,
        class r62 = F<_62, r61>, class r63 = F<_63, r62>, class r64 = F<_64, r63>,
        class r65 = F<_65, r64>, class r66 = F<_66, r65>, class r67 = F<_67, r66>,
        class r68 = F<_68, r67>, class r69 = F<_69, r68>, class r70 = F<_70, r69>,
        class r71 = F<_71, r70>, class r72 = F<_72, r71>, class r73 = F<_73, r72>,
        class r74 = F<_74, r73>, class r75 = F<_75, r74>, class r76 = F<_76, r75>,
        class r77 = F<_77, r76>, class r78 = F<_78, r77>, class r79 = F<_79, r78>,
        class r80 = F<_80, r79>, class r81 = F<_81, r80>, class r82 = F<_82, r81>,
        class r83 = F<_83, r82>, class r84 = F<_84, r83>, class r85 = F<_85, r84>,
        class r86 = F<_86, r85>, class r87 = F<_87, r86>, class r88 = F<_88, r87>,
        class r89 = F<_89, r88>, class r90 = F<_90, r89>, class r91 = F<_91, r90>,
        class r92 = F<_92, r91>, class r93 = F<_93, r92>, class r94 = F<_94, r93>,
        class r95 = F<_95, r94>, class r96 = F<_96, r95>, class r97 = F<_97, r96>,
        class r98 = F<_98, r97>, class r99 = F<_99, r98>,
        class r100 = F<_100, r99>, class r101 = F<_101, r100>,
        class r102 = F<_102, r101>, class r103 = F<_103, r102>,
        class r104 = F<_104, r103>, class r105 = F<_105, r104>,
        class r106 = F<_106, r105>, class r107 = F<_107, r106>,
        class r108 = F<_108, r107>, class r109 = F<_109, r108>,
        class r110 = F<_110, r109>, class r111 = F<_111, r110>,
        class r112 = F<_112, r111>, class r113 = F<_113, r112>,
        class r114 = F<_114, r113>, class r115 = F<_115, r114>,
        class r116 = F<_116, r115>, class r117 = F<_117, r116>,
        class r118 = F<_118, r117>, class r119 = F<_119, r118>,
        class r120 = F<_120, r119>, class r121 = F<_121, r120>,
        class r122 = F<_122, r121>, class r123 = F<_123, r122>,
        class r124 = F<_124, r123>, class r125 = F<_125, r124>,
        class r126 = F<_126, r125>>
    using g = scan_continuation<
        F<_127, r126>,
        list<r126, r125, r124, r123, r122, r121, r120, r119, r118, r117, r116,
             r115, r114, r113, r112, r111, r110, r109, r108, r107, r106, r105,
             r104, r103, r102, r101, r100, r99, r98, r97, r96, r95, r94, r93, r92,
             r91, r90, r89, r88, r87, r86, r85, r84, r83, r82, r81, r80, r79, r78,
             r77, r76, r75, r74, r73, r72, r71, r70, r69, r68, r67, r66, r65, r64,
             r63, r62, r61, r60, r59, r58, r57, r56, r55, r54, r53, r52, r51, r50,
             r49, r48, r47, r46, r45, r44, r43, r42, r41, r40, r39, r38, r37, r36,
             r35, r34, r33, r32, r31, r30, r29, r28, r27, r26, r25, r24, r23, r22,
             r21, r20, r19, r18, r17, r16, r15, r14, r13, r12, r11, r10, r9, r8,
             r7, r6, r5, r4, r3, r2, r1, r0>>;

    template<
        unsigned remaining, class C, template<class...> class F, class _0,
        class _1, class _2, class _3, class _4, class _5, class _6, class _7,
        class _8, class _9, class _10, class _11, class _12, class _13, class _14,
        class _15, class _16, class _17, class _18, class _19, class _20,
        class _21, class _22, class _23, class _24, class _25, class _26,
        class _27, class _28, class _29, class _30, class _31, class _32,
        class _33, class _34, class _35, class _36, class _37, class _38,
        class _39, class _40, class _41, class _42, class _43, class _44,
        class _45, class _46, class _47, class _48, class _49, class _50,
        class _51, class _52, class _53, class _54, class _55, class _56,
        class _57, class _58, class _59, class _60, class _61, class _62,
        class _63, class _64, class _65, class _66, class _67, class _68,
        class _69, class _70, class _71, class _72, class _73, class _74,
        class _75, class _76, class _77, class _78, class _79, class _80,
        class _81, class _82, class _83, class _84, class _85, class _86,
        class _87, class _88, class _89, class _90, class _91, class _92,
        class _93, class _94, class _95, class _96, class _97, class _98,
        class _99, class _100, class _101, class _102, class _103, class _104,
        class _105, class _106, class _107, class _108, class _109, class _110,
        class _111, class _112, class _113, class _114, class _115, class _116,
        class _117, class _118, class _119, class _120, class _121, class _122,
        class _123, class _124, class _125, class _126, class _127, class... xs>
    using f = typename g<
        F, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15,
        _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,
        _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45,
        _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,
        _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75,
        _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90,
        _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104,
        _105, _106, _107, _108, _109, _110, _111, _112, _113, _114, _115, _116,
        _117, _118, _119, _120, _121, _122, _123, _124, _125, _126, _127>::
        template f<remaining - 127, _scan_right<remaining - 127>, C, F, xs...>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup search

  /// Search the first sub-\sequence that satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// Calls \c TC with all the elements from sub-\sequence found at the end.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search_before, partial_search, after, index_if
  /// \see search_before_extended_by_n
  /// \see partial_search_before, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using search = drop_until_xs<Pred, TC, FC>;

  /// Search elements before sub-\sequence that satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// Calls \c TC with the elements from the beginning to sub-\sequence found.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search, partial_search, after, index_if
  /// \see search_before_extended_by_n
  /// \see partial_search_before, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using search_before = take_until_xs<Pred, TC, FC>;

  /// Search elements before sub-\sequence that satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// Calls \c TC with the elements from the beginning to sub-\sequence found + \c ExtendedByN.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search, search_before, partial_search, after, index_if
  /// \see partial_search_before, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using search_before_extended_by_n = take_until_extended_by_n_xs<ExtendedByN, Pred, TC, FC>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using search_before_extended_by_n_c = take_until_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>;

  /// Same \c search, but it stops when there is StopWhenAtLeast::value element or less.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// \treturn \sequence
  /// \see search, search_before, after, index_if
  /// \see search_before_extended_by_n
  /// \see partial_search_before, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<class StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search = partial_drop_until_xs_c<
    -JLN_MP_INTEGRAL_AS(int_, StopWhenAtLeast::value)-1, Pred, TC, FC>;

  template<std::size_t StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_c = partial_drop_until_xs_c<
    -JLN_MP_INTEGRAL_AS(int_, StopWhenAtLeast)-1, Pred, TC, FC>;

  /// Same \c search_before, but it stops when there is StopWhenAtLeast::value element or less.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// \treturn \sequence
  /// \see search, search_before, partial_search, after, index_if
  /// \see search_before_extended_by_n, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<class StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_before = partial_take_until_xs_c<
    -JLN_MP_INTEGRAL_AS(int_, StopWhenAtLeast::value)-1, Pred, TC, FC>;

  template<std::size_t StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_before_c = partial_take_until_xs_c<
    -JLN_MP_INTEGRAL_AS(int_, StopWhenAtLeast)-1, Pred, TC, FC>;

  /// Same \c search_before, but it stops when there is StopWhenAtLeast::value element or less.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// \treturn \sequence
  /// \see search, search_before, partial_search, after, index_if
  /// \see search_before_extended_by_n, partial_search_before
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<std::size_t StopWhenAtLeast, std::size_t ExtendedByN, class Pred,
           class TC = listify, class FC = clear<TC>>
  using partial_search_before_extended_by_n_c = partial_take_until_extended_by_n_xs_c<
    -JLN_MP_INTEGRAL_AS(int_, StopWhenAtLeast)-1, ExtendedByN, Pred, TC, FC>;

  template<class StopWhenAtLeast, class ExtendedByN, class Pred,
           class TC = listify, class FC = clear<TC>>
  using partial_search_before_extended_by_n = partial_take_until_extended_by_n_xs_c<
    -JLN_MP_INTEGRAL_AS(int_, StopWhenAtLeast::value)-1, ExtendedByN::value, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using search = unpack<L, mp::search<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using search_before = unpack<L, mp::search_before<Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using search_before_extended_by_n = unpack<L,
      mp::search_before_extended_by_n<ExtendedByN, Pred, TC, FC>>;


    template<class L, class StopWhenAtLeast, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search = unpack<L, mp::partial_search<Pred, StopWhenAtLeast, TC, FC>>;

    template<class L, class StopWhenAtLeast, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_before = unpack<L,
      mp::partial_search_before<Pred, StopWhenAtLeast, TC, FC>>;

    template<class L, class StopWhenAtLeast, class ExtendedByN, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_before_extended_by_n = unpack<L,
      mp::partial_search_before_extended_by_n<StopWhenAtLeast, ExtendedByN, Pred, TC, FC>>;


    template<class L, std::size_t StopWhenAtLeast, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_c = unpack<L, mp::partial_search_c<StopWhenAtLeast, Pred, TC, FC>>;

    template<class L, std::size_t StopWhenAtLeast, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_before_c = unpack<L,
      mp::partial_search_before_c<StopWhenAtLeast, Pred, TC, FC>>;

    template<class L, std::size_t StopWhenAtLeast, std::size_t ExtendedByN, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_before_extended_by_n_c = unpack<L,
      mp::partial_search_before_extended_by_n_c<StopWhenAtLeast, ExtendedByN, Pred, TC, FC>>;
  }
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
#if JLN_MP_GCC && JLN_MP_FEATURE_CONCEPTS
#  define JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT(name, TplType, Tpl, ...) \
     requires requires{ static_cast<TplType<Tpl>*>(nullptr); }                \
     struct name<Tpl<__VA_ARGS__>>
#  define JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT_CUDA(name, TplType, Tpl, ...) \
     struct name<Tpl<__VA_ARGS__>>

    template<class>
#elif JLN_MP_CUDA
#  define JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT(name, TplType, Tpl, ...) \
     struct name<Tpl<__VA_ARGS__>, decltype(static_cast<void(*)(TplType<Tpl>*)>(nullptr)(nullptr))>
#  define JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT_CUDA JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT

    template<class, class = void>
#elif JLN_MP_CLANG
#  define JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT(name, TplType, Tpl, ...) \
     struct name<Tpl<__VA_ARGS__>>
#  define JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT_CUDA JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT

    template<class, class = void>
#else
#  define JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT(name, TplType, Tpl, ...) \
     struct name<Tpl<__VA_ARGS__>, std::void_t<TplType<Tpl>>>
#  define JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT_CUDA(name, TplType, Tpl, ...) \
     struct name<Tpl<__VA_ARGS__>>

    template<class, class = void>
#endif
    struct normalize_similar;
  }
  /// \endcond

  /// \ingroup algorithm

  namespace emp
  {
    template<class... xs>
    inline constexpr bool similar_xs_v
      = same_xs_v<typename detail::normalize_similar<xs>::type...>;
  }

  /// Checks whether all types are the same or instantiations of the same class template.
  /// The list of supported class templates are:
  ///   - `template<class...>`
  ///   - `template<class T, T...>`
  ///   - `template<class, std::size_t>`
  ///   - `template<std::size_t, class...>`
  ///   - `template<class, auto...>` (when supported)
  ///   - `template<auto, class...>` (when supported)
  ///   - `template<auto...>` (when supported)
  /// \treturn \bool
  template<class C = identity>
  struct similar
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<emp::similar_xs_v<xs...>>);
  };

  template<class C = identity>
  struct similar_v
  {
    template<class... xs>
    using f = typename C::template f<emp::similar_xs_v<xs...>>;
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using similar = unpack<L, mp::similar<C>>;

    template<class L, class C = mp::identity>
    inline constexpr bool similar_v = unpack<L, mp::similar<C>>::value;
  }
}


/// \cond
namespace jln::mp
{
  template<>
  struct similar<identity>
  {
    template<class... xs>
    using f = number<emp::same_xs_v<typename detail::normalize_similar<xs>::type...>>;
  };

  template<class C>
  struct similar<not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_RAW_EXPR_TO_BOOL_NOT(
      emp::same_xs_v<typename detail::normalize_similar<xs>::type...>
    )>);
  };

  template<>
  struct similar<not_<>>
  {
    template<class... xs>
    using f = number<JLN_MP_RAW_EXPR_TO_BOOL_NOT(
      emp::same_xs_v<typename detail::normalize_similar<xs>::type...>
    )>;
  };
}

namespace jln::mp::detail
{
  template<template<class...> class Tpl>
  struct tpl_type1 {};

  template<template<class T, JLN_MP_TPL_AUTO_OR(T)...> class Tpl>
  struct tpl_type2 {};

#if JLN_MP_ENABLE_TPL_AUTO
  template<template<auto...> class Tpl>
#else
  template<template<class, std::size_t...> class Tpl>
#endif
  struct tpl_type3;

  template<template<JLN_MP_TPL_AUTO_OR(std::size_t), class...> class Tpl>
  struct tpl_type4;


#if JLN_MP_GCC && JLN_MP_FEATURE_CONCEPTS
#  define JLN_MP_NORMALIZE_SIMILAR2 normalize_similar
#  define JLN_MP_NORMALIZE_SIMILAR3 normalize_similar
#  define JLN_MP_NORMALIZE_SIMILAR4 normalize_similar
  template<class T>
  struct normalize_similar
#else
#  if JLN_MP_CUDA
#    define JLN_MP_NORMALIZE_SIMILAR2 normalize_similar2
#    define JLN_MP_NORMALIZE_SIMILAR3 normalize_similar3
#    define JLN_MP_NORMALIZE_SIMILAR4 normalize_similar4
#  else
#    define JLN_MP_NORMALIZE_SIMILAR2 normalize_similar2
#    define JLN_MP_NORMALIZE_SIMILAR3 normalize_similar2
#    define JLN_MP_NORMALIZE_SIMILAR4 normalize_similar2
#  endif
  template<class T, class = void>
  struct JLN_MP_NORMALIZE_SIMILAR4
#endif
  {
    using type = T;
  };

#if JLN_MP_CUDA
  template<class T, class = void>
  struct normalize_similar3 : normalize_similar4<T>
  {};

  template<class T, class = void>
  struct normalize_similar2 : normalize_similar3<T>
  {};
#elif JLN_MP_ENABLE_TPL_AUTO
  // fix ambiguous
  template<template<auto> class Tpl, auto x>
  JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT(
    JLN_MP_NORMALIZE_SIMILAR2, tpl_type3, Tpl, x)
  {
    using type = tpl_type3<Tpl>;
  };
#endif

  template<class T,
           template<class, JLN_MP_TPL_AUTO_OR(T)...>
           class Tpl, JLN_MP_TPL_AUTO_OR(T)... xs>
  JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT_CUDA(
    JLN_MP_NORMALIZE_SIMILAR2, tpl_type2, Tpl, T, xs...)
  {
    using type = tpl_type2<Tpl>;
  };

#if JLN_MP_ENABLE_TPL_AUTO
  template<template<auto...> class Tpl, auto v, auto... vs>
  JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT(
    JLN_MP_NORMALIZE_SIMILAR3, tpl_type3, Tpl, v, vs...)
#else
  template<template<class, std::size_t...> class Tpl, class T, std::size_t... N>
  JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT_CUDA(
    JLN_MP_NORMALIZE_SIMILAR3, tpl_type3, Tpl, T, N...)
#endif
  {
    using type = tpl_type3<Tpl>;
  };

  template<template<JLN_MP_TPL_AUTO_OR(std::size_t), class...> class Tpl,
    JLN_MP_TPL_AUTO_OR(std::size_t) N, class... T>
  JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT_CUDA(
    JLN_MP_NORMALIZE_SIMILAR4, tpl_type4, Tpl, N, T...)
  {
    using type = tpl_type4<Tpl>;
  };

#if JLN_MP_GCC && JLN_MP_FEATURE_CONCEPTS
  // fix ambiguous
  template<template<class> class Tpl, class x>
  JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT(normalize_similar, tpl_type1, Tpl, x)
  {
    using type = tpl_type1<Tpl>;
  };

  template<template<class...> class Tpl, class... xs>
  struct normalize_similar<Tpl<xs...>>
#else
  template<class T, class>
  struct normalize_similar : normalize_similar2<T>
  {};

  template<template<class...> class Tpl, class... xs>
  JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT(normalize_similar, tpl_type1, Tpl, xs...)
#endif
  {
    using type = tpl_type1<Tpl>;
  };

#undef JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT
#undef JLN_MP_NORMALIZE_SIMILAR_SPECIALIZE_STRUCT_CUDA
}
/// \endcond

namespace jln::mp
{
  /// \ingroup search

  /// Remove the first elements of a \sequence that does not satisfy a \predicate.
  /// \pre \c Pred::f<x> must return a boolean, 1 or 0
  /// \treturn \sequence
  /// \see skip_while, skip_until_xs
  /// \see drop_while, drop_until
  /// \see take_while, take_until
  template<class Pred, class TC = listify, class FC = TC>
  using skip_until = drop_until<Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_until = drop_inclusive_until<Pred, TC, clear<FC>>;

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_until_extended_by_n = drop_until_extended_by_n_c<
    ExtendedByN::value, Pred, TC, clear<FC>>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_until_extended_by_n_c = drop_until_extended_by_n_c<
    ExtendedByN, Pred, TC, clear<FC>>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_until = unpack<L, mp::skip_until<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_inclusive_until = unpack<L, mp::skip_inclusive_until<Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_until_extended_by_n_c = unpack<L,
      mp::skip_until_extended_by_n_c<ExtendedByN, Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_until_extended_by_n = unpack<L,
      mp::skip_until_extended_by_n<ExtendedByN, Pred, TC, FC>>;
  }
}

namespace jln::mp
{
  /// \ingroup search

  /// Remove the first elements of a \sequence that does not satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// \treturn \sequence
  /// \see skip_until, partial_skip_until_xs, skip_inclusive_until_xs
  /// \see take_until_xs, take_while_xs
  /// \see drop_until_xs, drop_while_xs
  template<class Pred, class TC = listify, class FC = TC>
  using skip_until_xs = drop_until_xs<Pred, TC, clear<FC>>;

  /// Same as \c drop_until_xs, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see skip_until, skip_until_xs, skip_inclusive_until_xs
  /// \see take_until_xs, take_while_xs
  /// \see drop_until_xs, drop_while_xs
  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_until_xs_c = partial_drop_until_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_until_xs = partial_drop_until_xs<OffsetEnd, Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_until_xs = drop_inclusive_until_xs<Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_inclusive_until_xs_c
    = partial_drop_inclusive_until_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_inclusive_until_xs
    = partial_drop_inclusive_until_xs<OffsetEnd, Pred, TC, clear<FC>>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_until_extended_by_n_xs_c
    = drop_until_extended_by_n_xs_c<ExtendedByN, Pred, TC, clear<FC>>;

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_until_extended_by_n_xs
    = drop_until_extended_by_n_xs<ExtendedByN, Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_skip_until_extended_by_n_xs_c
    = partial_drop_until_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_skip_until_extended_by_n_xs
    = partial_drop_until_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_until_xs = unpack<L, mp::skip_until_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_until_xs = unpack<L,
      mp::partial_skip_until_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_until_xs_c = unpack<L,
      mp::partial_skip_until_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_inclusive_until_xs = unpack<L, mp::skip_inclusive_until_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_inclusive_until_xs = unpack<L,
      mp::partial_skip_inclusive_until_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_inclusive_until_xs_c = unpack<L,
      mp::partial_skip_inclusive_until_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_until_extended_by_n_xs_c = unpack<L,
      mp::drop_until_extended_by_n_xs_c<ExtendedByN, Pred, TC, clear<FC>>>;

    template<class L, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_until_extended_by_n_xs = unpack<L,
      mp::drop_until_extended_by_n_xs<ExtendedByN, Pred, TC, clear<FC>>>;

    template<class L, int_ OffsetEnd, std::size_t ExtendedByN,
             class Pred, class TC = listify, class FC = TC>
    using partial_skip_until_extended_by_n_xs_c = unpack<L,
      mp::partial_drop_until_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>>;

    template<class L, class OffsetEnd, class ExtendedByN,
             class Pred, class TC = listify, class FC = TC>
    using partial_skip_until_extended_by_n_xs = unpack<L,
      mp::partial_drop_until_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>>;
  }
}

namespace jln::mp
{
  /// \ingroup search

  /// Remove the first elements of a \sequence that satisfy a \predicate.
  /// \pre \c Pred::f<x> must return a boolean, 1 or 0
  /// \treturn \sequence
  /// \see skip_until, skip_while_xs
  /// \see drop_while, drop_until
  /// \see take_while, take_until
  template<class Pred, class TC = listify, class FC = TC>
  using skip_while = drop_while<Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_while = drop_inclusive_while<Pred, TC, clear<FC>>;

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_while_extended_by_n = drop_while_extended_by_n_c<
    ExtendedByN::value, Pred, TC, clear<FC>>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_while_extended_by_n_c = drop_while_extended_by_n_c<
    ExtendedByN, Pred, TC, clear<FC>>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_while = unpack<L, mp::skip_while<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_inclusive_while = unpack<L, mp::skip_inclusive_while<Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_while_extended_by_n_c = unpack<L,
      mp::skip_while_extended_by_n_c<ExtendedByN, Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_while_extended_by_n = unpack<L,
      mp::skip_while_extended_by_n<ExtendedByN, Pred, TC, FC>>;
  }
}

namespace jln::mp
{
  /// \ingroup search

  /// Remove the first elements of a \sequence that satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// Same as \c skip_while, but the \predicate takes all the elements of
  /// the current position until the end of the list.
  /// \treturn \sequence
  /// \see skip_while, partial_skip_while_xs, skip_inclusive_while_xs
  /// \see take_while_xs, take_until_xs
  /// \see drop_while_xs, drop_until_xs
  template<class Pred, class TC = listify, class FC = TC>
  using skip_while_xs = drop_while_xs<Pred, TC, clear<FC>>;

  /// Same as \c skip_while_xs, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see skip_while, skip_while_xs, skip_inclusive_while_xs
  /// \see take_while_xs, take_until_xs
  /// \see drop_while_xs, drop_until_xs
  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_while_xs_c = partial_drop_while_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_while_xs = partial_drop_while_xs<OffsetEnd, Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_while_xs = drop_inclusive_while_xs<Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_inclusive_while_xs_c
    = partial_drop_inclusive_while_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_inclusive_while_xs
    = partial_drop_inclusive_while_xs<OffsetEnd, Pred, TC, clear<FC>>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_while_extended_by_n_xs_c
    = drop_while_extended_by_n_xs_c<ExtendedByN, Pred, TC, clear<FC>>;

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_while_extended_by_n_xs
    = drop_while_extended_by_n_xs<ExtendedByN, Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_skip_while_extended_by_n_xs_c
    = partial_drop_while_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_skip_while_extended_by_n_xs
    = partial_drop_while_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_while_xs = unpack<L, mp::skip_while_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_while_xs = unpack<L,
      mp::partial_skip_while_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_while_xs_c = unpack<L,
      mp::partial_skip_while_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_inclusive_while_xs = unpack<L, mp::skip_inclusive_while_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_inclusive_while_xs = unpack<L,
      mp::partial_skip_inclusive_while_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_inclusive_while_xs_c = unpack<L,
      mp::partial_skip_inclusive_while_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_while_extended_by_n_xs_c = unpack<L,
      mp::drop_while_extended_by_n_xs_c<ExtendedByN, Pred, TC, clear<FC>>>;

    template<class L, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_while_extended_by_n_xs = unpack<L,
      mp::drop_while_extended_by_n_xs<ExtendedByN, Pred, TC, clear<FC>>>;

    template<class L, int_ OffsetEnd, std::size_t ExtendedByN,
             class Pred, class TC = listify, class FC = TC>
    using partial_skip_while_extended_by_n_xs_c = unpack<L,
      mp::partial_drop_while_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>>;

    template<class L, class OffsetEnd, class ExtendedByN,
             class Pred, class TC = listify, class FC = TC>
    using partial_skip_while_extended_by_n_xs = unpack<L,
      mp::partial_drop_while_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>>;
  }
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int n>
    struct sort_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Sorts the elements of a \sequence according to an ordering relation.
  /// Sorting is stable.
  /// \post \c is_sorted<result...>
  /// \treturn \sequence
  template<class Cmp = less<>, class C = listify>
  struct sort
  {
    template<class... xs>
    using f = typename detail::_unpack<
      C,
      typename detail::sort_impl<sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(Cmp), xs...>
    >::type;
  };

  template<class Cmp = less<>, class C = listify>
  using stable_sort = sort<Cmp, C>;

  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = listify>
    using sort = unpack<L, mp::sort<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = listify>
    using stable_sort = unpack<L, mp::sort<Cmp, C>>;
  }

  /// \cond
  template<class Cmp>
  struct sort<Cmp, listify>
  {
    template<class... xs>
    using f = typename detail::sort_impl<sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(Cmp), xs...>;
  };
  /// \endcond
}



/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct mk_list2;

  template<>
  struct mk_list2<true>
    : listify
  {};

  template<>
  struct mk_list2<false>
  {
    template<class x, class y>
    using f = list<y, x>;
  };


  template<int n>
  struct sort_impl : sort_impl<
      n <= 8 ? 8
    : n <= 16 ? 16
    : n <= 32 ? 32
    : n <= 64 ? 64
    : 128
  >
  {};

  template<>
  struct sort_impl<0>
    : always<list<>>
  {};

  template<>
  struct sort_impl<1>
  {
    template<class Cmp, class x>
    using f = list<x>;
  };

  template<class Cmp, class x, class y>
  using sort_pair = typename mk_list2<JLN_MP_RAW_EXPR_TO_BOOL_NOT(Cmp::template f<y, x>::value)>
    ::template f<x, y>;

  template<>
  struct sort_impl<2>
  {
    template<class Cmp, class x, class y>
    using f = sort_pair<Cmp, x, y>;
  };

  template<>
  struct sort_impl<3>
  {
    template<class Cmp, class x1, class x2, class x3>
    using f = typename merge_impl<
      list<>,
      sort_pair<Cmp, x1, x2>,
      list<x3>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<4>
  {
    template<class Cmp, class x1, class x2, class x3, class x4>
    using f = typename merge_impl<
      list<>,
      sort_pair<Cmp, x1, x2>,
      sort_pair<Cmp, x3, x4>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<5>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5>
    using f = typename merge_impl<
      list<>,
      sort_pair<Cmp, x1, x2>,
      typename sort_impl<3>::template f<Cmp, x3, x4, x5>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<6>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5,
             class x6>
    using f = typename merge_impl<
      list<>,
      typename sort_impl<3>::template f<Cmp, x1, x2, x3>,
      typename sort_impl<3>::template f<Cmp, x4, x5, x6>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<7>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5,
             class x6, class x7>
    using f = typename merge_impl<
      list<>,
      typename sort_impl<4>::template f<Cmp, x1, x2, x3, x4>,
      typename sort_impl<3>::template f<Cmp, x5, x6, x7>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<8>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5,
             class x6, class x7, class x8>
    using f = typename merge_impl<
      list<>,
      typename sort_impl<4>::template f<Cmp, x1, x2, x3, x4>,
      typename sort_impl<4>::template f<Cmp, x5, x6, x7, x8>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<16>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5,
             class x6, class x7, class x8, class... xs>
    using f = typename merge_impl<
      list<>,
      typename sort_impl<8>::template f<Cmp, x1, x2, x3, x4, x5, x6, x7, x8>,
      typename sort_impl<sizeof...(xs)>::template f<Cmp, xs...>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<32>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5,
             class x6, class x7, class x8, class x9, class x10, class x11,
             class x12, class x13, class x14, class x15, class x16, class... xs>
    using f = typename merge_impl<
      list<>,
      typename sort_impl<16>::template f<
        Cmp, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16>,
      typename sort_impl<sizeof...(xs)>::template f<Cmp, xs...>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<64>
  {
    template<class Cmp, class x1, class x2, class x3, class x4, class x5,
             class x6, class x7, class x8, class x9, class x10, class x11,
             class x12, class x13, class x14, class x15, class x16, class x17,
             class x18, class x19, class x20, class x21, class x22, class x23,
             class x24, class x25, class x26, class x27, class x28, class x29,
             class x30, class x31, class x32, class... xs>
    using f = typename merge_impl<
      list<>,
      typename sort_impl<32>::template f<
        Cmp, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15,
        x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29,
        x30, x31, x32>,
      typename sort_impl<sizeof...(xs)>::template f<Cmp, xs...>,
      Cmp
    >::type;
  };

  template<>
  struct sort_impl<128>
  {
    template<class Cmp, JLN_MP_XS_32(class, JLN_MP_NIL, JLN_MP_COMMA), class... xs>
    using f = typename merge_impl<
      list<>,
      typename take_front_impl<(sizeof...(xs) + 32) / 2>
        ::template f<(sizeof...(xs) + 32) / 2, sort<Cmp>::template f,
          JLN_MP_XS_32(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), xs...>,
      typename drop_front_impl<(sizeof...(xs) + 32) / 2 - 32>
        ::template f<(sizeof...(xs) + 32) / 2 - 32, sort<Cmp>, xs...>,
      Cmp
    >::type;
  };
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool... bs>
    struct mk_split_after_indexes;
  }
  /// \endcond

  /// \ingroup group

  /// Splits a \sequence into multiple \lists at every point that satisfy a predicate.
  /// The separator value is inserted at the end of the previous list.
  /// \semantics
  ///   \code
  ///   split_after_if<is<_0>>::f<_0, _1, _2, _0, _3>
  ///   == list<
  ///     list<_0>,
  ///     list<_1, _2, _0>,
  ///     list<_3>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  /// \see split_if, split_before_if
  template<class Pred, class F = listify, class C = listify>
  struct split_after_if_with
  {
    template<class... xs>
    using f = typename detail::array_int2_index_dispatcher<
      detail::mk_split_after_indexes<JLN_MP_RAW_EXPR_TO_BOOL(
        JLN_MP_TRACE_F(Pred)::template f<xs>::value
      )...>
    >::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F), build_indexed_v<xs...>>;
  };

  template<class Pred = identity, class C = listify>
  using split_after_if = split_after_if_with<Pred, listify, C>;

  template<class x, class F = listify, class C = listify>
  using split_after_with = split_after_if_with<is<x>, F, C>;

  template<class x, class C = listify>
  using split_after = split_after_if_with<is<x>, listify, C>;

  namespace emp
  {
    template<class L, class Pred = mp::identity, class F = listify, class C = listify>
    using split_after_if_with = unpack<L, mp::split_after_if_with<Pred, F, C>>;

    template<class L, class Pred = mp::identity, class C = listify>
    using split_after_if = unpack<L, mp::split_after_if_with<Pred, listify, C>>;

    template<class L, class x, class F = listify, class C = listify>
    using split_after_with = unpack<L, mp::split_after_if_with<is<x>, F, C>>;

    template<class L, class x, class C = listify>
    using split_after = unpack<L, mp::split_after_if_with<is<x>, listify, C>>;
  }
}


/// \cond
namespace jln::mp
{
  template<class T, class F, class C>
  struct split_after_if_with<is<T>, F, C>
  {
    template<class... xs>
    using f = typename detail::array_int2_index_dispatcher<
      detail::mk_split_after_indexes<JLN_MP_IS_SAME(T, xs)...>
    >::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F), build_indexed_v<xs...>>;
  };
}

namespace jln::mp::detail
{
  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_IGNORE_UNSAFE_BUFFER_USAGE()
  template<bool... bs>
  struct mk_split_after_indexes
  {
    static constexpr std::size_t result_len = (1 + ... + bs);

    static constexpr auto make()
    {
      array_int2<result_len> a{};
      int i = 0;
      int n = 0;

      bool bools[] {bs...};
      for (bool b : bools)
      {
        ++a.elems[n][1];
        ++i;
        if (b)
          a.elems[++n][0] = i;
      }

      return a;
    }
  };
  JLN_MP_DIAGNOSTIC_POP()

  template<>
  struct mk_split_after_indexes<> : mk_split_indexes<>
  {};
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned n>
    struct split_at_impl;

    template<class C, class C1, class C2, class L>
    struct split_at_with_impl;
  }
  /// \endcond


  /// \ingroup group

  /// Splits a sequence at an arbitrary position.
  /// \pre `i >= 0 && i <= sizeof...(xs)`
  /// \treturn \sequence of two \values
  template<unsigned i, class SubC1 = listify, class SubC2 = SubC1, class C = listify>
  struct split_at2_with_c
  {
    template<class... xs>
    using f = typename detail::split_at_with_impl<C, SubC1, SubC2,
      typename JLN_MP_CALLER_TRACE_XS(xs, detail::split_at_impl<i>)
      ::template f<i, list<>, xs...>
    >::type;
  };

  template<class i, class SubC1 = listify, class SubC2 = SubC1, class C = listify>
  using split_at2_with = split_at2_with_c<i::value, SubC1, SubC2, C>;

  template<unsigned i, class F = listify, class C = listify>
  using split_at_with_c = split_at2_with_c<i, F, F, C>;

  template<class i, class F = listify, class C = listify>
  using split_at_with = split_at2_with_c<i::value, F, F, C>;

  /// Splits a sequence at an arbitrary position.
  /// \pre `i >= 0 && i <= sizeof...(xs)`
  /// \treturn \sequence of two \lists
  template<unsigned i, class C = listify>
  using split_at_c = split_at2_with_c<i, listify, listify, C>;

  template<class i, class C = listify>
  using split_at = split_at2_with_c<i::value, listify, listify, C>;

  namespace emp
  {
    template<class L, class i, class SubC1 = mp::listify, class SubC2 = mp::listify,
             class C = mp::listify>
    using split_at2_with = unpack<L, mp::split_at2_with_c<i::value, SubC1, SubC2, C>>;

    template<class L, unsigned i, class SubC1 = mp::listify, class SubC2 = mp::listify,
             class C = mp::listify>
    using split_at2_with_c = unpack<L, mp::split_at2_with_c<i, SubC1, SubC2, C>>;

    template<class L, class i, class F = mp::listify, class C = mp::listify>
    using split_at_with = unpack<L, mp::split_at2_with_c<i::value, F, F, C>>;

    template<class L, unsigned i, class F = mp::listify, class C = mp::listify>
    using split_at_with_c = unpack<L, mp::split_at2_with_c<i, F, F, C>>;

    template<class L, class i, class C = mp::listify>
    using split_at = unpack<L, mp::split_at2_with_c<i::value, listify, listify, C>>;

    template<class L, unsigned i, class C = mp::listify>
    using split_at_c = unpack<L, mp::split_at2_with_c<i, listify, listify, C>>;
  }
}

/// \cond
namespace jln::mp
{
  template<unsigned i>
  struct split_at2_with_c<i, listify, listify, listify>
  {
    template<class... xs>
    using f = typename JLN_MP_CALLER_TRACE_XS(xs, detail::split_at_impl<i>)
      ::template f<i, list<>, xs...>;
  };
}


namespace jln::mp::detail
{
  template<unsigned n>
  struct split_at_impl : split_at_impl<
      n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

  template<>
  struct split_at_impl<0>
  {
    template<unsigned size, class L, class... xs>
    using f = list<L, list<xs...>>;
  };

#define JLN_MP_SPLIT_AT_IMPL(n, mp_xs, mp_rxs, mp_rep)  \
  template<>                                            \
  struct split_at_impl<n>                               \
  {                                                     \
    template<unsigned size,                             \
      class L,                                          \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)            \
      class... xs>                                      \
    using f = list<typename _join_select<2>::f<list, L, \
      list<mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)> \
    >::type, list<xs...>>;                              \
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_SPLIT_AT_IMPL)

#undef JLN_MP_SPLIT_AT_IMPL

#define JLN_MP_SPLIT_AT_IMPL(n, mp_xs, mp_rxs, mp_rep)      \
  template<>                                                \
  struct split_at_impl<n>                                   \
  {                                                         \
    template<unsigned size,                                 \
      class L,                                              \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)                \
      class... xs>                                          \
    using f = typename split_at_impl<size-n>                \
      ::template f<size-n,                                  \
        typename _join_select<2>::f<list, L,                \
          list<mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)> \
        >::type,                                            \
        xs...                                               \
      >;                                                    \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_SPLIT_AT_IMPL)

#undef JLN_MP_SPLIT_AT_IMPL

  template<class C, class C1, class C2, class... xs, class... ys>
  struct split_at_with_impl<C, C1, C2, list<list<xs...>, list<ys...>>>
  {
    using type = typename C::template f<
      typename C1::template f<xs...>,
      typename C2::template f<ys...>
    >;
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup group

  /// Splits a sequence at an arbitrary position returns by \c GetIndex.
  /// \pre `GetIndex::f<xs...>::value >= 0 && GetIndex::f<xs...>::value <= sizeof...(xs)`
  /// \treturn \sequence of two \values
  template<class GetIndex, class SubC1 = listify, class SubC2 = SubC1, class C = listify>
  struct split_from2
  {
    template<class... xs>
    using f = typename split_at2_with_c<
      JLN_MP_DCALL_V_TRACE_XS(xs, GetIndex, xs...)::value, SubC1, SubC2, C
    >::template f<xs...>;
  };

  template<class GetIndex, class C = listify>
  using split_from = split_from2<GetIndex, listify, listify, C>;

  namespace emp
  {
    template<class L, class GetIndex,
      class SubC1 = mp::listify, class SubC2 = SubC1, class C = mp::listify>
    using split_from2 = unpack<L, mp::split_from2<GetIndex, SubC1, SubC2, C>>;

    template<class L, class GetIndex, class C = mp::listify>
    using split_from = unpack<L, mp::split_from2<GetIndex, mp::listify, mp::listify, C>>;
  }
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool... bs>
    struct mk_split_keep_separator_indexes;
  }
  /// \endcond

  /// \ingroup group

  /// Splits a \sequence into multiple \lists at every point that satisfy a predicate.
  /// The separator value is inserted in a new list.
  /// \semantics
  ///   \code
  ///   split_keep_separator_if<is<_0>>::f<_0, _1, _2, _0, _3>
  ///   == list<
  ///     list<>,
  ///     list<_0>,
  ///     list<_1, _2>,
  ///     list<_0>,
  ///     list<_3>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see split_if, split_before_if
  template<class Pred = identity, class F = listify, class C = listify>
  struct split_keep_separator_if_with
  {
    template<class... xs>
    using f = typename detail::array_int2_index_dispatcher<
      detail::mk_split_keep_separator_indexes<JLN_MP_RAW_EXPR_TO_BOOL(
        JLN_MP_TRACE_F(Pred)::template f<xs>::value
      )...>
    >::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F), build_indexed_v<xs...>>;
  };

  template<class Pred = identity, class C = listify>
  using split_keep_separator_if = split_keep_separator_if_with<Pred, listify, C>;

  template<class x, class F = listify, class C = listify>
  using split_keep_separator_with = split_keep_separator_if_with<is<x>, F, C>;

  template<class x, class C = listify>
  using split_keep_separator = split_keep_separator_if_with<is<x>, listify, C>;

  namespace emp
  {
    template<class L, class Pred = mp::identity, class F = listify, class C = listify>
    using split_keep_separator_if_with = unpack<L, mp::split_keep_separator_if_with<Pred, F, C>>;

    template<class L, class Pred = mp::identity, class C = listify>
    using split_keep_separator_if = unpack<L, mp::split_keep_separator_if_with<Pred, listify, C>>;

    template<class L, class x, class F = listify, class C = listify>
    using split_keep_separator_with = unpack<L, mp::split_keep_separator_if_with<is<x>, F, C>>;

    template<class L, class x, class C = listify>
    using split_keep_separator = unpack<L, mp::split_keep_separator_if_with<is<x>, listify, C>>;
  }
}

/// \cond
namespace jln::mp
{
  template<class T, class F, class C>
  struct split_keep_separator_if_with<is<T>, F, C>
  {
    template<class... xs>
    using f = typename detail::array_int2_index_dispatcher<
      detail::mk_split_keep_separator_indexes<JLN_MP_IS_SAME(T, xs)...>
    >::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F), build_indexed_v<xs...>>;
  };
}

namespace jln::mp::detail
{
  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_IGNORE_UNSAFE_BUFFER_USAGE()
  template<bool... bs>
  struct mk_split_keep_separator_indexes
  {
    static constexpr std::size_t result_len = (0 + ... + bs) * 2 + 1;

    static constexpr auto make()
    {
      array_int2<result_len> a{};

      bool bools[] {bs...};
      int i = 0;
      int n = 0;

      for (bool b : bools)
      {
        if (b)
        {
          a.elems[++n][0] = i;
          ++a.elems[n][1] = 1;
          a.elems[++n][0] = i + 1;
        }
        else
          ++a.elems[n][1];
        ++i;
      }

      return a;
    }
  };
  JLN_MP_DIAGNOSTIC_POP()

  template<>
  struct mk_split_keep_separator_indexes<> : mk_split_indexes<>
  {};
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class i>
    struct split_once_select;
  }
  /// \endcond
  /// \ingroup group

  /// Splits a \sequence at the first position that satisfy a predicate.
  /// \treturn \sequence of two or zero \sequence
  template<class Pred, class TC = listify, class FC = clear<>>
  struct split_once_if
  {
    template<class... xs>
    using f = typename detail::split_once_select<
      typename index_if<Pred, identity, always<number<-1>>>::template f<xs...>
    >
      ::template f<TC, FC>
      ::template f<xs...>;
  };

  template<class x, class TC = listify, class FC = clear<>>
  using split_once = split_once_if<is<x>, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = listify, class FC = clear<>>
    using split_once_if = unpack<L, mp::split_once_if<Pred, TC, FC>>;

    template<class L, class x, class TC = listify, class FC = clear<>>
    using split_once = unpack<L, mp::split_once_if<is<x>, TC, FC>>;
  }
}



namespace jln::mp::detail
{
  template<int_ i>
  struct split_once_select<number<i>>
  {
    template<class TC, class FC>
    using f = split_at2_with_c<i, listify, pop_front<>, TC>;
  };

  template<>
  struct split_once_select<number<-1>>
  {
    template<class TC, class FC>
    using f = JLN_MP_TRACE_F(FC);
  };
}

namespace jln::mp
{
  /// \ingroup algorithm

  /// Inserts a \value after each element of a \sequence.
  /// \treturn \list
  /// \see intersperse, prefix
  template<class x, class C = listify>
  struct suffix
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(C)::template f, list<xs, x>...>::type;
  };

  namespace emp
  {
    template<class L, class x, class C = mp::listify>
    using suffix = unpack<L, mp::suffix<x, C>>;
  }
}

/// \cond
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
namespace jln::mp
{
  template<class x, template<class...> class C>
  struct suffix<x, lift<C>>
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<C, list<xs, x>...>::type;
  };
}
#endif
/// \endcond

namespace jln::mp
{
  /// \ingroup functional

  /// Invoking \c F with its first parameters bound to bound to args.
  /// \semantics
  ///   \code
  ///   bind_front<F, a, b>::f<c, d> == F<a, b, c, d>
  ///   \endcode
  /// \treturn \sequence
  /// \see bind_back, capture_front, capture_back
  template<class F, class... BoundArgs>
  struct bind_front
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, F, BoundArgs..., xs...);
  };

  template<class F, int_... BoundArgs>
  using bind_front_c = bind_front<F, number<BoundArgs>...>;

#if JLN_MP_ENABLE_TPL_AUTO
  template<class F, auto... BoundArgs>
  using bind_front_v = bind_front<F, val<BoundArgs>...>;
#endif

  namespace emp
  {
    template<class L, class F, class... BoundArgs>
    using bind_front = unpack<L, mp::bind_front<F, BoundArgs...>>;

    template<class L, class F, int_... BoundArgs>
    using bind_front_c = unpack<L, mp::bind_front_c<F, BoundArgs...>>;

#if JLN_MP_ENABLE_TPL_AUTO
    template<class L, class F, auto... BoundArgs>
    using bind_front_v = unpack<L, mp::bind_front_v<F, BoundArgs...>>;
#endif
  }
  /// \cond
  namespace detail
  {
    template<class C, class... Fs>
    struct _partial;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions each taking the parameter corresponding to its position
  /// (or without parameter whether it does not exist),
  /// then calls \c C with the results and the rest of the parameters.
  /// \semantics
  ///   \code
  ///   partial<F,G,C>::f<a> == C::f<F::f<a>, G::f<>>
  ///   partial<F,G,C>::f<a,b,c,d> == C::f<F::f<a>, G::f<b>, c, d>
  ///   \endcode
  /// \treturn \value
  /// \see partial_each, partial_tee, partial_xs, each, tee
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct partial
  {
    template<class... xs>
    using f;
  };
#else
  template<class... Fs>
  struct partial
  : detail::rotate_impl<sizeof...(Fs)-1>
  ::template f<sizeof...(Fs)-1, lift<detail::_partial>, Fs...>
  {};
#endif
}


/// \cond
namespace jln::mp::detail
{
  constexpr int on_select(std::size_t nf, std::size_t nx)
  {
    return nf < nx ? 1 : nf > nx ? 2 : 0;
  }

  template<int, class C, class... Fs>
  struct _partial_select;

  // each (sizeof...(Fs) == sizeof...(xs))
  template<class C, class... Fs>
  struct _partial_select<0, C, Fs...>
  : _each<C, Fs...>
  {};

  template<class... Fs>
  struct partial_prefix
  {
    template<class C, class... xs>
    using f = bind_front<C, typename JLN_MP_TRACE_F(Fs)::template f<xs>...>;
  };

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class... Fs>
  struct _partial_select<1, C, Fs...>
  {
    template<class... xs>
    using f = typename drop_front_impl<
      (sizeof...(xs) & 0) + sizeof...(Fs)
    >::template f<
      sizeof...(Fs),
      typename take_front_c<sizeof...(Fs) + 1, partial_prefix<Fs...>>
      ::template f<C, xs...>,
      xs...
    >;
  };

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class F0, class F1, class F2, class F3>
  struct _partial_select<1, C, F0, F1, F2, F3>
  {
    template<class x0, class x1, class x2, class x3,
             class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0),
      JLN_MP_DCALL_TRACE_XS(xs, F1, x1),
      JLN_MP_DCALL_TRACE_XS(xs, F2, x2),
      JLN_MP_DCALL_TRACE_XS(xs, F3, x3),
      xs...
    );
  };

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class F3>
  struct _partial_select<1, C, identity, identity, identity, F3>
  {
    template<class x0, class x1, class x2, class x3,
             class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      x0,
      x1,
      x2,
      JLN_MP_DCALL_TRACE_XS(xs, F3, x3),
      xs...
    );
  };

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class F0, class F1, class F2>
  struct _partial_select<1, C, F0, F1, F2>
  {
    template<class x0, class x1, class x2, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0),
      JLN_MP_DCALL_TRACE_XS(xs, F1, x1),
      JLN_MP_DCALL_TRACE_XS(xs, F2, x2),
      xs...
    );
  };

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class F2>
  struct _partial_select<1, C, identity, identity, F2>
  {
    template<class x0, class x1, class x2, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      x0,
      x1,
      JLN_MP_DCALL_TRACE_XS(xs, F2, x2),
      xs...
    );
  };

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class F0, class F1>
  struct _partial_select<1, C, F0, F1>
  {
    template<class x0, class x1, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0),
      JLN_MP_DCALL_TRACE_XS(xs, F1, x1),
      xs...
    );
  };

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class F1>
  struct _partial_select<1, C, identity, F1>
  {
    template<class x0, class x1, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      x0,
      JLN_MP_DCALL_TRACE_XS(xs, F1, x1),
      xs...
    );
  };

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class F0>
  struct _partial_select<1, C, F0>
  {
    template<class x0, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0),
      xs...
    );
  };

  // sizeof...(Fs) < sizeof...(xs)
  template<class C>
  struct _partial_select<1, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };

  template<class... Fs>
  struct partial_suffix
  {
    template<class C>
    using f = typename C::template f<typename JLN_MP_TRACE_F(Fs)::template f<>...>;
  };

  // sizeof...(Fs) > sizeof...(xs)
  template<class C, class... Fs>
  struct _partial_select<2, C, Fs...>
  {
    template<class... xs>
    using f = typename drop_front_c<sizeof...(xs), lift<partial_suffix>>
      ::template f<Fs...>
      ::template f<
        typename take_front_c<sizeof...(xs), lift<partial_prefix>>
        ::template f<Fs...>
        ::template f<C, xs...>
      >;
  };

  template<class C, class... Fs>
  struct _partial
  {
    template<class... xs>
    using f = typename _partial_select<on_select(sizeof...(Fs), sizeof...(xs)), C, Fs...>
      ::template f<xs...>;
  };
} // namespace jln::mp
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    struct partial_each_impl;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions each taking the parameter corresponding to its position,
  /// then calls \c C with the results and the rest of the parameters.
  /// \semantics
  ///   \code
  ///   partial_each<F,G,C>::f<a> == /* error */
  ///   partial_each<F,G,C>::f<a,b,c,d> == C::f<F::f<a>, G::f<b>, c, d>
  ///   \endcode
  /// \treturn \value
  /// \see partial_tee, partial, each, tee
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct partial_each
  {
    template<class... xs>
    using f;
  };
#else
  template<class... Fs>
  struct partial_each
  : detail::rotate_impl<sizeof...(Fs)-1>
  ::template f<sizeof...(Fs)-1, detail::partial_each_impl, Fs...>
  {};
#endif
}


/// \cond
namespace jln::mp::detail
{
  struct partial_each_impl
  {
    template<class... Fs>
    using f = _partial_select<1, Fs...>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup algorithm

  /// Replace the first element of the \sequence.
  /// \treturn \list
  template<class F, class C = listify>
  using transform_first = partial_each<F, C>;

  namespace emp
  {
    template<class L, class F, class C = listify>
    using transform_first = unpack<L, mp::partial_each<F, C>>;
  }
}

namespace jln::mp
{
  /// \ingroup algorithm

  /// Replace the second element of the \sequence.
  /// \treturn \list
  template<class F, class C = listify>
  using transform_second = partial_each<identity, F, C>;

  namespace emp
  {
    template<class L, class F, class C = listify>
    using transform_second = unpack<L, mp::partial_each<mp::identity, F, C>>;
  }
}

namespace jln::mp
{
  /// \ingroup algorithm

  /// Replace the third element of the \sequence.
  /// \treturn \list
  template<class F, class C = listify>
  using transform_third = partial_each<identity, identity, F, C>;

  namespace emp
  {
    template<class L, class F, class C = listify>
    using transform_third = unpack<L, mp::partial_each<mp::identity, mp::identity, F, C>>;
  }
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class F>
    struct unfold_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  template<class value, class next = value>
  using Some = mp::list<value, next>;

  using None = mp::stop_recursion;

  /// Unfold \c F until returning \c None.
  /// When \c F returns `Some<value,next>`, \c value is added to the
  /// results list and \c next is used for the next iteration.
  /// \semantics
  ///   \code
  ///   unfold<
  ///     if_<
  ///       less_than_c<5>,
  ///       inc<lift<Some>>,
  ///       None
  ///     >
  ///   >::f<
  ///     number<0>
  ///   >
  ///   == list<number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   \endcode
  /// \treturn \list
  /// \see fold, fold_right, recursively
  template<class F, class C = listify>
  using unfold = mp::recursively<detail::unfold_impl<F>, mp::pop_front<C>>;

  namespace emp
  {
    template<class state, class F, class C = mp::listify>
    using unfold = JLN_MP_CALL_TRACE(JLN_MP_IDENT(mp::unfold<F, C>), state);
  }
}

/// \cond
namespace jln::mp::detail
{
  template<class>
  struct unfold_next
  {};

  template<>
  struct unfold_next<stop_recursion> : always<stop_recursion>
  {};

  template<class x, class next>
  struct unfold_next<list<x, next>>
  {
    template<class... xs>
    using f = _next_recursion<next, xs..., x>;
  };

  template<class F>
  struct unfold_impl
  {
    template<class state, class... xs>
    using f = typename unfold_next<JLN_MP_CALL_TRACE(F, state)>::template f<xs...>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup search

  /// Finds first element that is greater that \c x.
  /// Invokes \c TC with all the elements since the one found at the end.
  /// If no element is found, \c FC is used.
  /// \pre \c is_sorted<Cmp>::f<xs...>
  /// \treturn \sequence
  template<class x, class Cmp = less<>, class TC = listify, class FC = TC>
  using upper_bound = lower_bound<x, flip<tee<Cmp, not_<>>>, TC, FC>;

  template<int_ x, class Cmp = less<>, class TC = listify, class FC = TC>
  using upper_bound_c = upper_bound<number<x>, Cmp, TC, FC>;

  template<class x, class TC = listify, class FC = TC>
  using upper_bound_than = upper_bound<x, less<>, TC, FC>;

  template<int_ x, class TC = listify, class FC = TC>
  using upper_bound_than_c = upper_bound<number<x>, less<>, TC, FC>;

  namespace emp
  {
    template<class L, class x, class Cmp = mp::less<>, class TC = mp::listify, class FC = TC>
    using upper_bound = unpack<L, mp::upper_bound<x, Cmp, TC, FC>>;

    template<class L, int_ x, class Cmp = mp::less<>, class TC = mp::listify, class FC = TC>
    using upper_bound_c = unpack<L, mp::upper_bound<mp::number<x>, Cmp, TC, FC>>;

    template<class L, class x, class TC = mp::listify, class FC = TC>
    using upper_bound_than = unpack<L, mp::upper_bound<x, mp::less<>, TC, FC>>;

    template<class L, int_ x, class TC = mp::listify, class FC = TC>
    using upper_bound_than_c = unpack<L, mp::upper_bound<mp::number<x>, mp::less<>, TC, FC>>;
  }
}

namespace jln::mp
{
  /// \ingroup group

  /// Turns rows into columns, and columns into rows.
  /// Missing values are filled-in with fillvalue.
  /// This is similar to transposing a matrix.
  /// \semantics
  ///   \code
  ///   zip_longest<_0>::f<
  ///     list<_1, _2, _3>,
  ///     list<_a, _b, _c, _d>
  ///   > = list<
  ///     list<_1, _a>,
  ///     list<_2, _b>,
  ///     list<_3, _c>
  ///     list<_0, _d>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see zip
  template<class FillValue, class C = listify>
  using zip_longest = right_matrix_longest<FillValue, zip<C>>;

  template<class FillValue, class F = listify, class C = listify>
  using zip_longest_with = right_matrix_longest<FillValue, zip_with<F, C>>;

  namespace emp
  {
    template<class L, class FillValue, class C = mp::listify>
    using zip_longest = unpack<L, mp::zip_longest<FillValue, C>>;

    template<class L, class FillValue, class F = mp::listify, class C = mp::listify>
    using zip_longest_with = unpack<L, mp::zip_longest_with<FillValue, F, C>>;
  }
}

namespace jln::mp
{
  /// \ingroup functional

  /// Return \p TC::f<x> if \p Pred::f<x>, otherwise returns \p x.
  /// \treturn \value
  template<class Pred, class TC>
  using apply_or_identity = if_<Pred, TC, identity>;

  namespace emp
  {
    template<class Pred, class TC, class x>
    using apply_or_identity = typename mp::if_<Pred, TC, mp::identity>::template f<x>;
  }
}

namespace jln::mp
{
  /// \ingroup functional

  /// Invoking \c F with its last parameters bound to args.
  /// \semantics
  ///   \code
  ///   capture_back<c, d>::f<F, a, b> == F<a, b, c, d>
  ///   \endcode
  /// \treturn \sequence
  /// \see capture_front, bind_back, bind_front
  template<class... BoundArgs>
  struct capture_back
  {
    template<class F, class... xs>
    using f = JLN_MP_CALL_TRACE(F, xs..., BoundArgs...);
  };

#if __cplusplus >= 201703L
  template<JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  using capture_back_c = capture_back<val<BoundArgs>...>;
#else
  template<int_... BoundArgs>
  using capture_back_c = capture_back<typed_value<int_, BoundArgs>...>;
#endif

  template<JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  struct capture_back_v_c
  {
    template<class F, class... xs>
    using f = typename F::template f<xs::value..., BoundArgs...>;
  };

  template<class... BoundArgs>
  using capture_back_v = capture_back_v_c<BoundArgs::value...>;

  namespace emp
  {
    template<class L, class... BoundArgs>
    using capture_back = unpack<L, mp::capture_back<BoundArgs...>>;

    template<class L, class... BoundArgs>
    using capture_back_v = unpack<L, mp::capture_back_v<BoundArgs...>>;

    template<class L, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
    using capture_back_v_c = unpack<L, mp::capture_back_v_c<BoundArgs...>>;
  }
}

namespace jln::mp
{
  /// \ingroup functional

  /// Invoking \c F with its first parameters bound to args.
  /// \semantics
  ///   \code
  ///   capture_front<a, b>::f<F, c, d> == F<a, b, c, d>
  ///   \endcode
  /// \treturn \sequence
  /// \see capture_back, bind_front, bind_back
  template<class... BoundArgs>
  struct capture_front
  {
    template<class F, class... xs>
    using f = JLN_MP_CALL_TRACE(F, BoundArgs..., xs...);
  };

#if __cplusplus >= 201703L
  template<JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  using capture_front_c = capture_front<val<BoundArgs>...>;
#else
  template<int_... BoundArgs>
  using capture_front_c = capture_front<typed_value<int_, BoundArgs>...>;
#endif

  template<JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  struct capture_front_v_c
  {
    template<class F, class... xs>
    using f = typename F::template f<BoundArgs..., xs::value...>;
  };

  template<class... BoundArgs>
  using capture_front_v = capture_front_v_c<BoundArgs::value...>;

  namespace emp
  {
    template<class L, class... BoundArgs>
    using capture_front = unpack<L, mp::capture_front<BoundArgs...>>;

    template<class L, class... BoundArgs>
    using capture_front_v = unpack<L, mp::capture_front_v<BoundArgs...>>;

    template<class L, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
    using capture_front_v_c = unpack<L, mp::capture_front_v_c<BoundArgs...>>;
  }
}
namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class, class...>
    struct _cascade;
  }
  /// \endcond

  /// \ingroup functional

  /// Recursively invokes \functions to nested \typelist of \typelists.
  /// \semantics
  ///   \code
  ///     cascade<F0> = transform<F0>
  ///     cascade<F0,F1,F2> = transform<unpack<transform<unpack<F0>, F1>>, F2>
  ///   \endcode
  template<class F, class... Fs>
  using cascade = typename detail::_cascade<F, Fs...>::type;
}



/// \cond
namespace jln::mp::detail
{
  template<class F0, class F1, class... Fs>
  struct _cascade<F0, F1, Fs...>
    : _cascade<transform<unpack<F0>, F1>, Fs...>
  {};

  template<class F0, class F1>
  struct _cascade<F0, F1>
  {
    using type = transform<unpack<F0>, F1>;
  };

  template<class F>
  struct _cascade<F>
  {
    using type = transform<F>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned> struct _compose_f;
    template<class, class> struct compose_impl;

    template<class x, class y>
    using compose_impl_t = typename compose_impl<x, y>::type;
  }
  /// \endcond

  /// \ingroup functional

  /// Composition of two \metafunctions or more.
  /// \semantics
  ///   \code
  ///   compose_f<foo, bar>::f<a, b> == bar<foo<a, b>>
  ///   \endcode
  /// \treturn \function
  template<template<class...> class F, template<class...> class... Fs>
  using compose_f = typename detail::_compose_f<sizeof...(Fs) < 8 ? sizeof...(Fs) : 8>
    ::template f<F, Fs...>;

  /// Composition of two \functions or more.
  /// \semantics
  ///   \code
  ///   compose<foo, bar>::f<a, b> == bar::f<foo::f<a, b>>
  ///   \endcode
  /// \treturn \function
  template<class F, class... Fs>
  using compose = typename conditional_c<sizeof...(Fs) == 0>
    ::template f<
      at1<F>,
      mp::fold_right<JLN_MP_LIFT_WRAP(detail::compose_impl)>
    >
    ::template f<identity, F, Fs...>;
}



/// \cond
namespace jln::mp::detail
{
#define JLN_COMPOSE_IMPL(n, mp_xs, mp_rxs, mp_dup) \
  template<template<class...> class F              \
    mp_xs(JLN_MP_COMMA template<class...> class,   \
      JLN_MP_NIL, JLN_MP_NIL)>                     \
  struct _compose_f_impl##n                        \
  {                                                \
    template<class... xs>                          \
    using f = mp_rxs(JLN_MP_NIL, <, JLN_MP_NIL)    \
      JLN_MP_DCALLF_XS(xs, F, xs...)               \
    mp_dup(>, JLN_MP_NIL);                         \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_COMPOSE_IMPL)

#undef JLN_COMPOSE_IMPL

#define JLN_COMPOSE_IMPL(n, mp_xs, mp_rxs, mp_dup)  \
  template<>                                        \
  struct _compose_f<n>                              \
  {                                                 \
    template<template<class...> class F             \
      mp_xs(JLN_MP_COMMA template<class...> class,  \
        JLN_MP_NIL, JLN_MP_NIL)>                    \
    using f = _compose_f_impl##n<F                  \
      mp_xs(JLN_MP_COMMA, JLN_MP_NIL, JLN_MP_NIL)>; \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_COMPOSE_IMPL)

#undef JLN_COMPOSE_IMPL

  template<unsigned n>
  struct _compose_f
  {
    template<
      template<class...> class F0,
      template<class...> class F1,
      template<class...> class F2,
      template<class...> class F3,
      template<class...> class F4,
      template<class...> class F5,
      template<class...> class F6,
      template<class...> class F7,
      template<class...> class... Fs>
    using f = typename _compose_f<n-8>::template f<
      _compose_f_impl7<F0, F1, F2, F3, F4, F5, F6, F7>::template f,
      Fs...
    >;
  };

  template<class F, class C>
  struct compose_impl
  {
    using type = tee<F, C>;
  };

  template<template<class...> class F, class x>
  struct compose_impl<lift<F>, x>
  {
    using type = lift<F, x>;
  };

  template<template<class...> class F, class x>
  struct compose_impl<lift_t<F>, x>
  {
    using type = lift_t<F, x>;
  };

  template<class F>
  struct compose_impl<F, identity>
  {
    using type = F;
  };

  // fix ambiguity
  template<template<class...> class F>
  struct compose_impl<lift<F>, identity>
  {
    using type = lift<F>;
  };

  // fix ambiguity
  template<template<class...> class F>
  struct compose_impl<lift_t<F>, identity>
  {
    using type = lift_t<F>;
  };
}
/// \endcond

#ifdef __cpp_nontype_template_parameter_class
#if __cpp_nontype_template_parameter_class >= 201806L
namespace jln::mp
{
  /// \ingroup functional

  /// Invokes a lambda function.
  /// \treturn \value
  template<auto F, class C = identity>
  struct eval
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, decltype(F.template operator()<xs...>()));
  };

  namespace emp
  {
    template<auto F, class... xs>
    using eval = decltype(F.template operator()<xs...>());
  }

  /// \cond
  template<auto F>
  struct eval<F, identity>
  {
    template<class... xs>
    using f = decltype(F.template operator()<xs...>());
  };
  /// \endcond
}
#endif
#endif

namespace jln::mp
{
  /// \ingroup functional

  /// Invokes a function computing the fixed point of a function.
  /// \treturn \value
  /// \see recursively
  template<class C>
  struct fix
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, fix<C>, xs...);
  };

  namespace emp
  {
    template<class F, class... xs>
    using fix = typename fix<F>::template f<xs...>;
  }
}

#ifdef __cpp_generic_lambdas
#if __cpp_generic_lambdas >= 201707L

# ifdef __cpp_consteval
#   if __cpp_consteval >= 201811L
#     define JLN_MP_CONSTEVAL_OR_CONSTEXPR consteval
#   endif
# endif
# ifndef JLN_MP_CONSTEVAL_OR_CONSTEXPR
#   define JLN_MP_CONSTEVAL_OR_CONSTEXPR constexpr
# endif

namespace jln::mp
{
  /// \ingroup functional

  class default_make_id_tag {};

  /// \cond
  namespace detail::mkid
  {
    JLN_MP_DIAGNOSTIC_PUSH()
    JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wnon-template-friend")
    JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wunused-function")
    template<class T, int X>
    struct flag
    {
      friend JLN_MP_CONSTEVAL_OR_CONSTEXPR auto f(flag<T, X>);
    };
    JLN_MP_DIAGNOSTIC_POP()

    template<class T, int X>
    struct injecter
    {
      friend JLN_MP_CONSTEVAL_OR_CONSTEXPR auto f(flag<T, X>) { return X; }
    };

    template<class T = default_make_id_tag, int X = 0, auto v = []{}>
    JLN_MP_CONSTEVAL_OR_CONSTEXPR auto next_id()
    {
      if constexpr (requires { f(flag<T, X+10>{}); }) {
        if constexpr (requires { f(flag<T, X+100>{}); }) {
          if constexpr (requires { f(flag<T, X+1000>{}); }) {
            if constexpr (requires { f(flag<T, X+10000>{}); }) {
              return next_id<T, X+10001, v>();
            }
            else if constexpr (requires { f(flag<T, X+3000>{}); }) {
              return next_id<T, X+3001, v>();
            }
            else {
              return next_id<T, X+1001, v>();
            }
          }
          else if constexpr (requires { f(flag<T, X+300>{}); }) {
            return next_id<T, X+301, v>();
          }
          else {
            return next_id<T, X+101, v>();
          }
        }
        else if constexpr (requires { f(flag<T, X+30>{}); }) {
          return next_id<T, X+31, v>();
        }
        else {
          return next_id<T, X+11, v>();
        }
      }
      else if constexpr (requires { f(flag<T, X>{}); }) {
        if constexpr (requires { f(flag<T, X+2>{}); }) {
          if constexpr (requires { f(flag<T, X+4>{}); }) {
            return next_id<T, X+5, v>();
          }
          else if constexpr (requires { f(flag<T, X+3>{}); }) {
            return next_id<T, X+4, v>();
          }
          else {
            return next_id<T, X+3, v>();
          }
        }
        else if constexpr (requires { f(flag<T, X+1>{}); }) {
            return next_id<T, X+2, v>();
        }
        else {
            return next_id<T, X+1, v>();
        }
      }
      else {
        void(injecter<T, X>{});
        return f(flag<T, X>{});
      }
    }
  }
  /// \endcond

  /// Generates a unique id per call for a specified tag.
  /// Signature: `int next_id<class Tag = default_make_id_tag, start_id = 0, auto = []{}>()`
  using detail::mkid::next_id;

  /// Generates a unique id per type.
  /// \treturn int
  template<class T>
  struct id_of
  {
    static constexpr int value = next_id<default_make_id_tag, 0, []{}>();
  };

  template<class T>
  static constexpr int id_of_v = id_of<T>::value;

  template<class T>
  using id_of_t = number<id_of<T>::value>;


  /// Generates a unique id per type for a specified tag.
  /// \treturn int
  template<class Tag, class T>
  struct tagged_id_of
  {
    static constexpr int value = next_id<Tag, 0, []{}>();
  };

  template<class Tag, class T>
  static constexpr int tagged_id_of_v = tagged_id_of<Tag, T>::value;

  template<class Tag, class T>
  using tagged_id_of_t = number<tagged_id_of<Tag, T>::value>;


  /// Generates a unique id per type.
  /// \treturn \number
  template<class Tag, class C = identity>
  struct make_id_for
  {
    template<class T>
    using f = JLN_MP_CALL_TRACE(C, tagged_id_of_t<Tag, T>);
  };

  template<class C = identity>
  using make_id = make_id_for<default_make_id_tag, C>;

  /// \cond
  template<class T>
  struct tagged_id_of<default_make_id_tag, T>
  : id_of<T>
  {};

  template<>
  struct make_id_for<default_make_id_tag, identity>
  {
    template<class T>
    using f = id_of_t<T>;
  };

  template<class Tag>
  struct make_id_for<Tag, identity>
  {
    template<class T>
    using f = tagged_id_of_t<Tag, T>;
  };

  template<class C>
  struct make_id_for<default_make_id_tag, C>
  {
    template<class T>
    using f = JLN_MP_CALL_TRACE(C, id_of_t<T>);
  };
  /// \endcond
}

#endif
#endif



namespace jln::mp
{
  /// \ingroup functional

  /// Invokes \c FC whether `na`, otherwise \c TC.
  /// \treturn \value
  template<class TC, class FC = violation>
  using monadic = if_<is<na>, FC, TC>;

  /// Invokes \c FC whether first value is `na`, otherwise \c TC.
  /// \treturn \value
  template<class TC, class FC = violation>
  using monadic0 = if_<front<is<na>>, FC, TC>;

  /// Invokes \c FC whether any value is `na`, otherwise \c TC.
  /// \treturn \value
  template<class TC, class FC = violation>
  using monadic_xs = if_<none_of<is<na>>, TC, FC>;

  /// Monadify only if \c x is \c na.
  /// \treturn \value
  template<class x, template<class...> class M, class TC, class FC = violation>
  using monadic_if_na = typename conditional_c<JLN_MP_IS_SAME(na, x)>
    ::template f<M<TC, FC>, TC>;
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, class... Fs>
    struct partial_xs_impl;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions passing all parameters to each
  /// (or without parameter whether it does not exist),
  /// then calls \c C with the results and the rest of the parameters.
  /// \semantics
  ///   \code
  ///   partial_xs<F,G,C>::f<a> == C::f<F::f<a>, G::f<>>
  ///   partial_xs<F,G,C>::f<a,b,c,d> == C::f<F::f<a,b,c,d>, G::f<a,b,c,d>, c, d>
  ///   \endcode
  /// \treturn \value
  /// \see partial_each, partial_tee, each, tee
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct partial_xs
  {
    template<class... xs>
    using f;
  };
#else
  template<class... Fs>
  struct partial_xs
  : detail::rotate_impl<sizeof...(Fs)-1>
  ::template f<sizeof...(Fs)-1, lift<detail::partial_xs_impl>, Fs...>
  {};
#endif
}


/// \cond
namespace jln::mp::detail
{
  template<int, class C, class... Fs>
  struct partial_xs_select;

  // tee (sizeof...(Fs) == sizeof...(xs))
  template<class C, class... Fs>
  struct partial_xs_select<0, C, Fs...>
  : _tee<C, Fs...>
  {};

  // sizeof...(Fs) < sizeof...(xs)
  template<class C, class... Fs>
  struct partial_xs_select<1, C, Fs...>
  {
    template<class... xs>
    using f = typename drop_front_impl<
      (sizeof...(xs) & 0) + sizeof...(Fs)
    >::template f<
      sizeof...(Fs),
      bind_front<C, JLN_MP_DCALL_TRACE_XS(xs, Fs, xs...)...>,
      xs...
    >;
  };

  template<class C, class F0, class F1, class F2, class F3>
  struct partial_xs_select<1, C, F0, F1, F2, F3>
  {
    template<class x0, class x1, class x2, class x3,
             class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0, x1, x2, x3, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F1, x0, x1, x2, x3, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F2, x0, x1, x2, x3, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F3, x0, x1, x2, x3, xs...),
      xs...
    );
  };

  template<class C, class F0, class F1, class F2>
  struct partial_xs_select<1, C, F0, F1, F2>
  {
    template<class x0, class x1, class x2, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0, x1, x2, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F1, x0, x1, x2, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F2, x0, x1, x2, xs...),
      xs...
    );
  };

  template<class C, class F0, class F1>
  struct partial_xs_select<1, C, F0, F1>
  {
    template<class x0, class x1, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0, x1, xs...),
      JLN_MP_DCALL_TRACE_XS(xs, F1, x0, x1, xs...),
      xs...
    );
  };

  template<class C, class F0>
  struct partial_xs_select<1, C, F0>
  {
    template<class x0, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_DCALL_TRACE_XS(xs, F0, x0, xs...),
      xs...
    );
  };

  template<class C>
  struct partial_xs_select<1, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };

  template<class... Fs>
  struct partial_xs_prefix
  {
    template<class C, class... xs>
    using f = bind_front<C, JLN_MP_DCALL_TRACE_XS(xs, Fs, xs...)...>;
  };

  // sizeof...(Fs) > sizeof...(xs)
  template<class C, class... Fs>
  struct partial_xs_select<2, C, Fs...>
  {
    template<class... xs>
    using f = typename drop_front_c<sizeof...(xs), lift<partial_suffix>>
      ::template f<Fs...>
      ::template f<
        typename take_front_c<sizeof...(xs), lift<partial_xs_prefix>>
        ::template f<Fs...>
        ::template f<C, xs...>
      >;
  };

  template<class C, class... Fs>
  struct partial_xs_impl
  {
    template<class... xs>
    using f = typename partial_xs_select<on_select(sizeof...(Fs), sizeof...(xs)), C, Fs...>
      ::template f<xs...>;
  };
} // namespace jln::mp
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    struct partial_tee_impl;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions passing all parameters to each
  /// then calls \c C with the results and the rest of the parameters.
  /// \semantics
  ///   \code
  ///   partial_tee<F,G,C>::f<a> == /* error */
  ///   partial_tee<F,G,C>::f<a,b,c,d> == C::f<F::f<a,b,c,d>, G::f<a,b,c,d>, c, d>
  ///   \endcode
  /// \treturn \value
  /// \see partial_each, partial, each, tee
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct partial_tee
  {
    template<class... xs>
    using f;
  };
#else
  template<class... Fs>
  struct partial_tee
  : detail::rotate_impl<sizeof...(Fs)-1>
  ::template f<sizeof...(Fs)-1, detail::partial_tee_impl, Fs...>
  {};
#endif
}


/// \cond
namespace jln::mp::detail
{
  struct partial_tee_impl
  {
    template<class... Fs>
    using f = partial_xs_select<1, Fs...>;
  };
} // namespace jln::mp
/// \endcond

#ifdef __cpp_generic_lambdas
#if __cpp_generic_lambdas >= 201707L


namespace jln::mp
{
  /// \ingroup functional

  /// \cond
  namespace detail::rand
  {
    JLN_MP_DIAGNOSTIC_PUSH()
    JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wnon-template-friend")
    template<int X>
    struct flag
    {
      friend JLN_MP_CONSTEVAL_OR_CONSTEXPR auto f(flag<X>);
    };
    JLN_MP_DIAGNOSTIC_POP()

    struct random_data
    {
      unsigned z;
      unsigned w;
    };

    template<int X, unsigned z, unsigned w>
    struct injecter
    {
      friend JLN_MP_CONSTEVAL_OR_CONSTEXPR auto f(flag<X>) { return random_data{z,w}; }
    };

    #ifndef JLN_MP_RANDOM_SEED_Z
    #   define JLN_MP_RANDOM_SEED_Z 0
    #endif
    #ifndef JLN_MP_RANDOM_SEED_W
    #   define JLN_MP_RANDOM_SEED_W 0
    #endif
    // -1 -> do not use __TIME__
    // 0 -> use __TIME__
    // >= 0 -> use value as __TIME__
    #ifndef JLN_MP_RANDOM_SEED_TIME
    #   define JLN_MP_RANDOM_SEED_TIME -1
    #endif

    #if JLN_MP_RANDOM_SEED_TIME >= 0
    #  if JLN_MP_RANDOM_SEED_TIME == 0
    JLN_MP_DIAGNOSTIC_PUSH()
    JLN_MP_DIAGNOSTIC_GCC_IGNORE("-Wdate-time")
    constexpr unsigned t = unsigned((__TIME__[0] * 10 + __TIME__[1]) * 3600
                                  + (__TIME__[3] * 10 + __TIME__[4]) * 60
                                  + (__TIME__[6] * 10 + __TIME__[7]));
    JLN_MP_DIAGNOSTIC_POP()
    #    undef JLN_MP_RANDOM_SEED_TIME
    #    define JLN_MP_RANDOM_SEED_TIME t
    #  endif
    #  if JLN_MP_RANDOM_SEED_Z == 0
    #    define JLN_MP_RANDOM_SEED_Z \
           (JLN_MP_RANDOM_SEED_TIME >> 16) ? (JLN_MP_RANDOM_SEED_TIME >> 16) : 362436069
    #  endif
    #  if JLN_MP_RANDOM_SEED_W == 0
    #    define JLN_MP_RANDOM_SEED_W \
           (JLN_MP_RANDOM_SEED_TIME % 4294967296) ? (JLN_MP_RANDOM_SEED_TIME % 4294967296) : 521288629
    #  endif
    #else
    #  if JLN_MP_RANDOM_SEED_Z == 0
    #    undef JLN_MP_RANDOM_SEED_Z
    #    define JLN_MP_RANDOM_SEED_Z 362436069
    #  endif
    #  if JLN_MP_RANDOM_SEED_W == 0
    #    undef JLN_MP_RANDOM_SEED_W
    #    define JLN_MP_RANDOM_SEED_W 521288629
    #  endif
    #endif

    inline JLN_MP_CONSTEVAL_OR_CONSTEXPR auto f(flag<0>)
    {
      return random_data{JLN_MP_RANDOM_SEED_Z, JLN_MP_RANDOM_SEED_W};
    }

    #undef JLN_MP_RANDOM_SEED_Z
    #undef JLN_MP_RANDOM_SEED_W
    #undef JLN_MP_RANDOM_SEED_TIME

    /// \pre id >= 1
    /// \pre random_for_id<id-1>() must have been called
    template<int id>
    JLN_MP_CONSTEVAL_OR_CONSTEXPR unsigned random_for_id()
    {
      constexpr auto data = f(flag<id-1>{});
      // algorithm found on https://www.codeproject.com/Articles/25172/Simple-Random-Number-Generation
      constexpr unsigned z = 36969 * (data.z & 65535) + (data.z >> 16);
      constexpr unsigned w = 18000 * (data.w & 65535) + (data.w >> 16);
      void(injecter<id, z, w>{});
      return (z << 16) + w;
    }

    template<auto v = []{}>
    JLN_MP_CONSTEVAL_OR_CONSTEXPR unsigned next_random()
    {
      return random_for_id<next_id<random_data, 1, v>()>();
    }
  }
  /// \endcond

  /// Generates a unique id per call for a specified tag.
  /// Signature: `unsigned next_random<auto = []{}>()`
  using detail::rand::next_random;

  namespace emp
  {
    template<auto v = []{}>
    using random = number<next_random<v>()>;

    template<auto v = []{}>
    static constexpr unsigned random_v = next_random<v>();
  }

  /// Generate a random number.
  /// The seed can be configured with `JLN_MP_RANDOM_SEED_TIME`
  /// or `JLN_MP_RANDOM_SEED_W` and `JLN_MP_RANDOM_SEED_Z`
  /// \treturn \number
  template<class C = identity, auto = []{}>
  struct random
  #ifdef JLN_MP_DOXYGENATING
  {
    template<class... xs>
    using f;
  }
  #endif
  ;

/// \cond
#if JLN_MP_CLANG
  namespace detail
  {
    template<std::size_t, auto v = []{}>
    using random_impl = number<next_random<v>()>;
  }

  template<class C, auto>
  struct random
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, detail::random_impl<sizeof...(xs)>);
  };

  template<auto v>
  struct random<identity, v>
  {
    template<class... xs>
    using f = detail::random_impl<sizeof...(xs)>;
  };
#else
  template<class C, auto>
  struct random
  {
    template<class...>
    using f = JLN_MP_CALL_TRACE(C, number<next_random<[]{}>()>);
  };

  template<auto v>
  struct random<identity, v>
  {
    template<class...>
    using f = number<next_random<[]{}>()>;
  };
#endif
/// \endcond
}

#endif
#endif

namespace jln::mp
{
  /// \ingroup functional

  /// Apply a function until some \predicate is satisfied.
  /// \treturn \value
  /// \see until_xs
  template<class Pred, class F, class C = identity>
  using until = recursively<if_<Pred, stop_recursion, F>, C>;

  /// Apply a function until some \predicate is satisfied.
  /// \treturn \value
  /// \see until
  template<class Pred, class F, class C = listify>
  using until_xs = recursively<if_<Pred, stop_recursion, F>, C>;

  namespace emp
  {
    template<class L, class Pred, class F, class C = mp::identity>
    using until = unpack<L, mp::until<Pred, F, C>>;

    template<class L, class Pred, class F, class C = mp::listify>
    using until_xs = unpack<L, mp::until<Pred, F, C>>;
  }
}

namespace jln::mp
{
  /// \ingroup functional

  /// Apply a function while some \predicate is satisfied.
  /// \treturn \value
  /// \see while_xs
  template<class Pred, class F, class C = identity>
  using while_ = recursively<if_<Pred, F, stop_recursion>, C>;

  /// Apply a function while some \predicate is satisfied.
  /// \treturn \value
  /// \see while_
  template<class Pred, class F, class C = listify>
  using while_xs = recursively<if_<Pred, F, stop_recursion>, C>;

  namespace emp
  {
    template<class L, class Pred, class F, class C = mp::identity>
    using while_ = unpack<L, mp::while_<Pred, F, C>>;

    template<class L, class Pred, class F, class C = mp::listify>
    using while_xs = unpack<L, mp::while_<Pred, F, C>>;
  }
}

namespace jln::mp
{
  /// \ingroup list

  /// Inserts elements at the end of \c L list.
  /// \treturn \sequence
  template<class L, class C = listify>
  using append = push_front<L, unpack_append<C>>;

  namespace emp
  {
    template<class L, class... xs>
    using append = unpack_append<L, listify, xs...>;
  }
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class seq>
    struct _as_list
    {};
  }
  /// \endcond

  /// \ingroup list

  /// Extracts type paramaters of a template class or union, then constructs a \list.
  /// \pre \c seq must be compatible with \typelist or \c detail::_as_list<seq>::type.
  /// \treturn \list
  template<class C = identity>
  struct as_list
  {
    template<class seq>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_as_list<seq>::type);
  };

  namespace emp
  {
    template<class seq, class C = mp::identity>
    using as_list = typename as_list<C>::template f<seq>;
  }
}


/// \cond
namespace jln::mp
{
  template<>
  struct as_list<identity>
  {
    template<class seq>
    using f = typename detail::_as_list<seq>::type;
  };
}

namespace jln::mp::detail
{
  template<template<class...> class seq, class... xs>
  struct _as_list<seq<xs...>>
  {
    using type = list<xs...>;
  };

  template<template<class T, T...> class seq, class T, T... ns>
  struct _as_list<seq<T, ns...>>
  {
    using type = list<number<ns>...>;
  };

  template<template<auto...> class seq, auto... ns>
  struct _as_list<seq<ns...>>
  {
    using type = list<number<ns>...>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup list

  /// Retrieves the last element of a sequence.
  /// \treturn \value
  template<class C = identity>
  using back = rotate_c<-1, front<C>>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using back = unpack<L, mp::back<C>>;
  }
}

namespace jln::mp
{
  /// \ingroup list

  /// Removes \c N elements from the end of a \sequence.
  /// \pre `0 <= N <= sizeof...(xs)`
  /// \treturn \sequence
  /// \see drop_back_max, drop_front, take_front, take_back, drop_while
  template<unsigned N, class C = listify>
  struct drop_back_c
  {
    template<class... xs>
    using f = typename detail::take_front_impl<sizeof...(xs) - N>
      ::template f<sizeof...(xs) - N, JLN_MP_TRACE_F(C)::template f, xs...>;
  };

  /// Removes at most \c N elements from the end of a \sequence.
  /// \pre `0 <= N`
  /// \treturn \sequence
  /// \see drop_back, drop_front, drop_while
  template<unsigned N, class C = listify>
  struct drop_back_max_c
  {
    template<class... xs>
    using f = typename take_front_c<sizeof...(xs) <= N ? 0 : sizeof...(xs) - N, C>
      ::template f<xs...>;
  };

  template<class N, class C = listify>
  using drop_back = drop_back_c<N::value, C>;

  template<class N, class C = listify>
  using drop_back_max = drop_back_max_c<N::value, C>;

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using drop_back = unpack<L, mp::drop_back<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using drop_back_c = unpack<L, mp::drop_back_c<n, C>>;

    template<class L, class N, class C = mp::listify>
    using drop_back_max = unpack<L, mp::drop_back_max<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using drop_back_max_c = unpack<L, mp::drop_back_max_c<n, C>>;
  }

  /// \cond
  #if ! JLN_MP_OPTIMIZED_ALIAS
  template<unsigned N, template<class...> class C>
  struct drop_back_c<N, lift<C>>
  {
    template<class... xs>
    using f = typename detail::take_front_impl<sizeof...(xs) - N>
      ::template f<sizeof...(xs) - N, C, xs...>;
  };

  template<template<class...> class C>
  struct drop_back_c<0, lift<C>>
    : detail::call_trace_xs<lift<C>>
  {};
  #endif

  template<class C>
  struct drop_back_c<0, C>
    : detail::call_trace_xs<C>
  {};

  template<class C>
  struct drop_back_max_c<0, C>
    : detail::call_trace_xs<C>
  {};
  /// \endcond
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct enumerate_impl;

    template<class, int_...>
    struct enumerate_v_impl;
  }
  /// \endcond


  /// \ingroup list

  /// Returns pairs containing a numeric index of type \c int_ and a value.
  /// \semantics
  ///   \code
  ///   C::f<F::f<0, xs[0]>, ..., F::f<n, xs[n]>>
  ///   \endcode
  /// \treturn \sequence
  template<class F, class C = listify>
  struct enumerate_v_with
  {
    template<class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), detail::enumerate_v_impl)
      ::template f<F, JLN_MP_TRACE_F(C), xs...>;
  };

  /// Returns pairs containing an index and a value.
  /// \semantics
  ///   \code
  ///   C::f<F::f<number<0>, xs[0]>, ..., F::f<number<n>, xs[n]>>
  ///   \endcode
  /// \treturn \sequence
  template<class F = listify, class C = listify>
  struct enumerate_with
  {
    template<class... xs>
    using f = typename detail::enumerate_impl<emp::make_int_sequence_c<sizeof...(xs)>>
      ::template f<JLN_MP_TRACE_F(F)::template f, JLN_MP_TRACE_F(C), xs...>;
  };

  template<class C = listify>
  using enumerate = enumerate_with<listify, C>;

  namespace emp
  {
    template<class L, class F, class C = mp::listify>
    using enumerate_v_with = unpack<L, mp::enumerate_v_with<F, C>>;

    template<class L, class F = mp::listify, class C = mp::listify>
    using enumerate_with = unpack<L, mp::enumerate_with<F, C>>;

    template<class L, class C = mp::listify>
    using enumerate = unpack<L, mp::enumerate_with<mp::listify, C>>;
  }
} // namespace jln::mp


/// \cond
#if ! JLN_MP_OPTIMIZED_ALIAS
namespace jln::mp
{
  template<template<class...> class F, class C>
  struct enumerate_with<lift<F>, C>
  {
    template<class... xs>
    using f = typename detail::enumerate_impl<emp::make_int_sequence_c<sizeof...(xs)>>
      ::template f<F, JLN_MP_TRACE_F(C), xs...>;
  };
}
#endif

namespace jln::mp::detail
{
  template<class... ns>
  struct enumerate_impl<list<ns...>>
  {
    template<template<class...> class F, class C, class... xs>
    using f = typename C::template f<F<ns, xs>...>;
  };

  template<class, int_... i>
  struct enumerate_v_impl
  {
    template<class F, class C, class... xs>
    using f = typename C::template f<typename F::template f<i, xs>...>;
  };
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool, bool>
    struct erase_values;

    template<class C, int_ start, int_ size, int_ n,
      int_ index = start < 0 ? n+start : start,
      class s = erase_values<index >= n, index < 0>,
      int_ index2 = s::template start<index>,
      int_ dropped = s::template dropped<index, size, n>>
    using erase_impl = rotate_c<
      index2,
      drop_front_c<
        dropped,
        rotate_c<n - index2 - dropped, C>
      >
    >;
  }
  /// \endcond

  /// \ingroup list

  /// Removes at most \c size elements from index \c start.
  /// A negative value represents an index starting from the end.
  /// \treturn \sequence
  template<int_ start, unsigned size = 1, class C = listify>
  struct erase_c
  {
    template<class... xs>
    using f = typename detail::erase_impl<C, start, size, int_(sizeof...(xs))>
      ::template f<xs...>;
  };

  template<class start, class size = number<1>, class C = listify>
  using erase = erase_c<start::value, size::value, C>;

  namespace emp
  {
    template<class L, class start, class size = mp::number<1>, class C = mp::listify>
    using erase = unpack<L, mp::erase<start, size, C>>;

    template<class L, int_ start, unsigned size = 1, class C = mp::listify>
    using erase_c = unpack<L, mp::erase_c<start, size, C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<>
  struct erase_values<true, false>
  {
    template<int_ index>
    static constexpr int_ start = 0;

    template<int_ index, int_ size, int_ n>
    static constexpr int_ dropped = 0;
  };

  template<>
  struct erase_values<false, true>
  {
    template<int_ index>
    static constexpr int_ start = 0;

    template<int_ index, int_ size, int_ n>
    static constexpr int_ dropped = index + size <= 0 ? 0 : index + size <= n ? index + size : n;
  };

  template<>
  struct erase_values<false, false>
  {
    template<int_ index>
    static constexpr int_ start = index;

    template<int_ index, int_ size, int_ n>
    static constexpr int_ dropped = index + size <= n ? size : n - index;
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup number

  /// Replaces each element of a \sequence by its corresponding index.
  /// \treturn \sequence
  template<class C = listify>
  using indices = size<make_int_sequence<C>>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using indices = unpack<L, mp::indices<C>>;
  }
  /// \cond
  namespace detail
  {
    template<bool>
    struct insert_sequence_index;

    template<int_ index, class C, class... xs>
    using insert_sequence_impl = rotate_c<index, bind_front<rotate_c<-index, C>, xs...>>;
  }
  /// \endcond

  /// \ingroup list

  /// Inserts all elements of \c seq at an arbitrary position.
  /// A negative value represents an index starting from the end.
  /// \treturn \sequence
  template<int_ index, class seq, class C = listify>
  struct insert_sequence_c
  {};

  template<int_ index, template<class...> class List, class... xs, class C>
  struct insert_sequence_c<index, List<xs...>, C>
  {
    template<class... ys>
    using f = typename detail::insert_sequence_impl<
      detail::insert_sequence_index<index < 0>::template index<index, sizeof...(ys)>, C, xs...
    >::template f<ys...>;
  };

  /// \cond
  template<class... xs, template<class...> class List, class C>
  struct insert_sequence_c<0, List<xs...>, C> : bind_front<C, xs...>
  {};
  /// \endcond

  template<class index, class seq, class C = listify>
  using insert_sequence = insert_sequence_c<index::value, seq, C>;

  namespace emp
  {
    template<class L, class index, class seq, class C = mp::listify>
    using insert_sequence = unpack<L, mp::insert_sequence<index, seq, C>>;

    template<class L, int_ index, class seq, class C = mp::listify>
    using insert_sequence_c = unpack<L, mp::insert_sequence_c<index, seq, C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<>
  struct insert_sequence_index<true>
  {
    template<int_ i, int_ n>
    static constexpr int_ index = -i < n ? n+i : 0;
  };

  template<>
  struct insert_sequence_index<false>
  {
    template<int_ i, int_ n>
    static constexpr int_ index = i < n ? i : n;
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup list

  /// Inserts an elements at an arbitrary position.
  /// \treturn \sequence
  template<int_ index, class x, class C = listify>
  using insert_c = insert_sequence_c<index, list<x>, C>;

  template<class index, class x, class C = listify>
  using insert = insert_sequence_c<index::value, list<x>, C>;

  namespace emp
  {
    template<class L, class index, class x, class C = mp::listify>
    using insert = unpack<L, mp::insert<index, x, C>>;

    template<class L, int_ index, class x, class C = mp::listify>
    using insert_c = unpack<L, mp::insert_c<index, x, C>>;
  }
}

namespace jln::mp
{
  /// \ingroup list

  /// Checks whether a sequence has no elements.
  /// \treturn \bool
  template<class C = identity>
  using is_empty = size<not_<C>>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using is_empty = unpack<L, mp::is_empty<C>>;
  }
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class x>
    struct _is_list;
  }
  /// \endcond

  /// \ingroup list

  /// Checks whether \c x is a \list.
  /// \treturn \bool
  template<class C = identity>
  struct is_list
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_is_list<x>::type);
  };

  namespace emp
  {
    template<class x, class C = mp::identity>
    using is_list = JLN_MP_CALL_TRACE(C, typename detail::_is_list<x>::type);
  }

  /// \cond
  template<>
  struct is_list<identity>
  {
    template<class x>
    using f = typename detail::_is_list<x>::type;
  };
  /// \endcond
} // namespace jln::mp



/// \cond
namespace jln::mp::detail
{
  template<class x>
  struct _is_list
  {
    using type = false_;
  };

  template<class... xs>
  struct _is_list<list<xs...>>
  {
    using type = true_;
  };
} // namespace jln::mp::detail
/// \endcond

namespace jln::mp
{
  /// \ingroup list

  /// Checks whether a sequence has elements.
  /// \treturn \bool
  template<class C = identity>
  using is_not_empty = size<is<number<0>, not_<C>>>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using is_not_empty = unpack<L, mp::is_not_empty<C>>;
  }
}

namespace jln::mp
{
  /// \ingroup list

  template<class N, class C = identity>
  using is_size_of = size<is<N, C>>;

  template<int_ n, class C = identity>
  using is_size_of_c = size<is<number<n>, C>>;

  namespace emp
  {
    template<class L, class N, class C = mp::identity>
    using is_size_of = unpack<L, mp::is_size_of<N, C>>;

    template<class L, int_ n, class C = mp::identity>
    using is_size_of_c = unpack<L, mp::is_size_of_c<n, C>>;
  }
}

namespace jln::mp
{
  /// \ingroup list

  /// Difference between the number of parameter \c xs and \c I::value.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   size<push_front<I, sub<C>>>
  ///   \endcode
  /// \treturn \number
  template<int_ I, class C = identity>
  struct offset_c
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<I - int_(sizeof...(xs))>);
  };

  /// \cond
  template<int_ I>
  struct offset_c<I, identity>
  {
    template<class... xs>
    using f = number<I - int_(sizeof...(xs))>;
  };
  /// \endcond

  template<class I, class C = identity>
  using offset = offset_c<I::value, C>;

  namespace emp
  {
    template<class L, class I, class C = mp::identity>
    using offset = unpack<L, mp::offset<I, C>>;

    template<class L, int_ i, class C = mp::identity>
    using offset_c = unpack<L, mp::offset_c<i, C>>;
  }
}

namespace jln::mp
{
  /// \ingroup list

  /// Removes the last element of sequence.
  /// \pre `sizeof...(xs) > 0`
  /// \treturn \sequence
  template<class C = listify>
  using pop_back = rotate_c<-1, pop_front<C>>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using pop_back = unpack<L, mp::pop_back<C>>;
  }
}

namespace jln::mp
{
  /// \ingroup list

  /// Inserts elements at the start of \c L list.
  /// \treturn \sequence
  template<class L, class C = listify>
  using prepend = push_front<L, unpack<C>>;

  namespace emp
  {
    template<class L, class... xs>
    using prepend = unpack<L, listify, xs...>;
  }
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_ beg, int_ end,
      bool = beg < 0,
      bool = end < 0,
      bool = beg >= end>
    struct _range;
  }
  /// \endcond

  /// \ingroup list

  /// Returns a contiguous subsequence of a \sequence.
  /// A negative value represents an index starting from the end.
  /// All indices available in the range are returned, indices outside the bounds are ignored.
  /// \treturn \sequence
  template<int_ beg, int_ end, class C = listify>
  struct range_c : detail::_range<beg, end>::template impl<C>
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f;
#endif
  };

  template<class beg, class end, class C = listify>
  using range = range_c<beg::value, end::value, C>;

  namespace emp
  {
    template<class L, class beg, class end, class C = mp::listify>
    using range = unpack<L, mp::range<beg, end, C>>;

    template<class L, int_ beg, int_ end, class C = mp::listify>
    using range_c = unpack<L, mp::range_c<beg, end, C>>;
  }
}



/// \cond
namespace jln::mp::detail
{
  // beg < 0 && end < 0 && beg >= end
  template<int_ beg, int_ end>
  struct _range<beg, end, true, true, true>
    : positive_strided_slice_impl<-1, -1>
  {};

  // beg < 0 && end < 0 && beg < end
  template<int_ beg, int_ end>
  struct _range<beg, end, true, true, false>
  {
    template<class C>
    using impl = negative_slice_select<true>::impl<beg, end - beg, C>;
  };

  // pre: beg >= 0
  // pre: end < 0
  template<class C, int_ beg, int_ end, int_ n,
    bool b = n + end <= beg>
  using negative_end_range_dispatch = slice_impl<
    C,
    b ? -1 : beg,
    b ? -1 : -end
  >;

  // beg >= 0 && end < 0
  template<int_ beg, int_ end>
  struct _range<beg, end, false, true, true>
  {
    template<class C>
    struct impl
    {
      template<class... xs>
      using f = typename negative_end_range_dispatch<C, beg, end,
        static_cast<int_>(sizeof...(xs)) // cast is necessary for nvcc (tested with V12.3.52)
      >::template f<xs...>;
    };
  };

  // pre: beg < 0
  // pre: end >= 0
  template<class C, int_ beg, int_ end, int_ n,
    bool b = end <= n + beg>
  using negative_beg_range_dispatch = slice_impl<
    C,
    b ? -1 : n < -beg ? 0 : n + beg,
    b ? -1 : n < end ? 0 : n - end
  >;

  // beg < 0 && end >= 0
  template<int_ beg, int_ end>
  struct _range<beg, end, true, false, false>
  {
    template<class C>
    struct impl
    {
      template<class... xs>
      using f = typename negative_beg_range_dispatch<C, beg, end,
        static_cast<int_>(sizeof...(xs)) // cast is necessary for nvcc (tested with V12.3.52)
      >::template f<xs...>;
    };
  };

  // beg >= 0 && end >= 0 && beg < end
  template<int_ beg, int_ end>
  struct _range<beg, end, false, false, false>
  {
    template<class C>
    using impl = negative_slice_select<false>::impl<beg, end - beg, C>;
  };

  // beg >= 0 && end >= 0 && beg >= end
  template<int_ beg, int_ end>
  struct _range<beg, end, false, false, true>
    : positive_strided_slice_impl<-1, -1>
  {};
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool, bool>
    struct _select_swap_index;
  }
  /// \endcond

  /// \ingroup list

  /// Swap elements at indexes \c i and \c j of a \sequence.
  /// \pre `0 < i < sizeof...(xs)`
  /// \pre `0 < j < sizeof...(xs)`
  /// \treturn \sequence
  /// \note `swap_index<I, J>` == `swap_index<J, I>`
  template<unsigned i, unsigned j, class C = listify>
  using swap_index_c = typename detail::_select_swap_index<i < j, i == j>
    ::template f<i, j, C>;

  template<class I, class J, class C = listify>
  using swap_index = swap_index_c<I::value, J::value, C>;

  namespace emp
  {
    template<class L, class I, class J, class C = mp::listify>
    using swap_index = unpack<L, swap_index<I, J, C>>;

    template<class L, unsigned i, unsigned j, class C = mp::listify>
    using swap_index_c = unpack<L, swap_index_c<i, j, C>>;
  }
}



/// \cond
namespace jln::mp::detail
{
  //                     |        i     j
  //                     |        <--n-->
  //                     |    aaa X bbb Y ccc
  //                     |
  // rotate i            |    X bbb Y ccc aaa
  // get X ; prepend C,i |  C i bbb Y ccc aaa
  // rotate n+1          |    Y ccc aaa C i bbb
  // get Y ; append X    |      ccc aaa C i bbb X
  // rotate -n-1         |    C i bbb X ccc aaa
  // rm C,i ; append Y   |        bbb X ccc aaa Y
  //                     |
  // rotate -i           |    aaa Y bbb X ccc

  template<class y>
  struct swap_elem_push_Y
  {
    template<class C, class i, class... xs>
    using f = typename rotate_impl<sizeof...(xs) - i::value>
      ::template f<sizeof...(xs) - i::value, C, xs..., y>;
  };

  template<class x, unsigned n>
  struct swap_elem_get_Y_push_X
  {
    template<class y, class... xs>
    using f = typename rotate_impl<sizeof...(xs) - n - 1>
      ::template f<sizeof...(xs) - n - 1, swap_elem_push_Y<y>, xs..., x>;
  };

  template<unsigned n, class i, class C>
  struct swap_elem_get_X
  {
    template<class x, class... xs>
    using f = typename rotate_impl<(sizeof...(xs) & 0) + n + 1>
      ::template f<n + 1, swap_elem_get_Y_push_X<x, n>, C, i, xs...>;
  };

  template<unsigned i, unsigned j, class C>
  struct swap_elem
  {
    template<class... xs>
    using f = typename rotate_impl<(sizeof...(xs) & 0) + i>
      ::template f<i, swap_elem_get_X<j-i, number<i>, C>, xs...>;
  };

  template<bool, bool>
  struct _select_swap_index
  {
    template<unsigned i, unsigned j, class C>
    using f = swap_elem<i, j, C>;
  };

  template<>
  struct _select_swap_index<false, false>
  {
    template<unsigned i, unsigned j, class C>
    using f = swap_elem<j, i, C>;
  };

  template<unsigned i, class C>
  struct if_valid_index
    : detail::call_trace_xs<C>
  {};

  template<unsigned i>
  struct if_valid_index<i, listify>
    : listify
  {};

  template<>
  struct _select_swap_index<false, true>
  {
    template<unsigned i, unsigned j, class C>
    using f = if_valid_index<i, C>;
  };
}
/// \endcond


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    struct is_map_impl;
  }
  /// \endcond

  /// \ingroup map

  /// Checks whether \c xs is a map.
  /// A map is a sequence of lists having at least one element (the key).
  /// The keys of the map must be unique.
  /// \treturn \bool
  template<class C = identity>
  using is_map = try_<detail::is_map_impl, C, always<false_, C>>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using is_map = unpack<L, mp::is_map<C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  struct is_map_impl
  {
    template<class... xs>
    using f = typename is_unique_if<same<>, identity>
      ::template f<typename _unpack<front<>, xs>::type...>;
  };
}
/// \endcond


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class key>
    struct map_find_select;

    template<class key, class... kvs>
    using map_find_impl = decltype(detail::map_find_select<key>::f(
      static_cast<detail::inherit<kvs...>*>(nullptr)
    ));
  }
  /// \endcond

  /// \ingroup map

  /// Finds the element of the \map with a key \c key.
  /// Calls \c TC with element found.
  /// If no element is found, \c FC is used with the whole \map.
  /// \pre \c is_map<>::f<kvs...>
  /// \treturn \sequence
  template<class key, class TC = identity, class FC = always<void>>
  struct map_find
  {
    template<class... kvs>
    using f = typename detail::map_find_impl<key, kvs...>
      ::template f<TC, FC, kvs...>;
  };

  namespace emp
  {
    template<class L, class key, class TC = mp::identity, class FC = mp::always<void>>
    using map_find = unpack<L, mp::map_find<key, TC, FC>>;
  }
}

/// \cond
namespace jln::mp
{
  template<class key, class T>
  struct map_find<key, identity, always<T>>
  {
    template<class... kvs>
    using f = typename detail::map_find_impl<key, kvs...>
      ::template f<identity, always<T>>;
  };

  // map_contains
  template<class key, class T, class U, class C>
  struct map_find<key, always<T, C>, always<U, C>>
  {
    template<class... kvs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::map_find_impl<key, kvs...>
      ::template f<always<T>, always<U>>
    );
  };

  // map_contains
  template<class key, class T, class U>
  struct map_find<key, always<T>, always<U>>
  {
    template<class... kvs>
    using f = typename detail::map_find_impl<key, kvs...>
      ::template f<always<T>, always<U>>;
  };
}

namespace jln::mp::detail
{
  template<class x>
  struct map_find_elem
  {
    template<class TC, class FC, class...>
    using f = JLN_MP_CALL_TRACE(TC, x);
  };

  template<>
  struct map_find_elem<void>
  {
    template<class TC, class FC, class... kvs>
    using f = JLN_MP_CALL_TRACE(FC, kvs...);
  };

  template<class key>
  struct map_find_select
  {
    template<template<class...> class Tpl, class... xs>
    static map_find_elem<Tpl<key, xs...>> f(basic_item<Tpl<key, xs...>>*);

    static map_find_elem<void> f(...);
  };
}
/// \endcond

namespace jln::mp
{
  /// \ingroup map

  /// Checks if a key exists in a \map.
  /// \treturn \bool
  /// \pre \c is_map<>
  template<class key, class C = identity>
  using map_contains = map_find<key, always<true_, C>, always<false_, C>>;

  namespace emp
  {
    template<class L, class key, class C = mp::identity>
    using map_contains = unpack<L, mp::map_contains<key, C>>;
  }
}

namespace jln::mp
{
  /// \ingroup map

  /// If the \map contains an element with a key \c Key, removes it.
  /// \pre \c is_map<>
  /// \treturn \map
  template<class Key, class C = listify>
  using map_erase = transform<map_find<Key, always<list<>>, listify>, join<C>>;

  namespace emp
  {
    template<class L, class Key, class C = mp::listify>
    using map_erase = unpack<L, mp::map_erase<Key, C>>;
  }
}

namespace jln::mp
{
  /// \ingroup map

  /// Inserts the element \c KV into the map, if the key \c emp::front<KV> does not exist.
  /// \pre \c is_map<>
  /// \treturn \map
  template<class KV, class C = listify>
  using map_insert = if_<map_contains<unpack<front<>>::f<KV>>, C, push_back<KV, C>>;

  namespace emp
  {
    template<class L, class KV, class C = mp::listify>
    using map_insert = unpack<L, mp::map_insert<KV, C>>;
  }
}

namespace jln::mp
{
  /// \ingroup map

  /// Returns a list of the keys of \map.
  /// When is a valid map, the keys are unique, so the result is a \set.
  /// \treturn \sequence
  template<class C = listify>
  using map_keys = transform<unpack<front<>>, C>;

  /// Returns a list of the keys of \map transformed with \c F.
  /// When is a valid map, the keys are unique.
  /// \treturn \sequence
  template<class F = mp::identity, class C = listify>
  using map_keys_with = transform<unpack<front<F>>, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using map_keys = unpack<L, mp::map_keys<C>>;

    template<class L, class F = mp::identity, class C = mp::listify>
    using map_keys_with = unpack<L, mp::map_keys_with<F, C>>;
  }
}

namespace jln::mp
{
  /// \ingroup map

  /// If the \map contain the key \c Key, replaces the existing element `L<k, v...>` with `F<k, v...>`.
  /// \pre \c is_map<>
  /// \treturn \sequence
  template<class Key, class F, class C = listify>
  using map_update = transform<map_find<Key, F, front<>>, C>;

  /// Update an element `L<k, v...>` with `L<k, F<k, v...>>`.
  /// \pre `unpack<size<>>::f<x> >= 1`
  template<class F>
  struct map_element_value_update
  {
    template<class x>
    using f = typename unpack<tee<front<>, F, emp::wrapper<x>>>
      ::template f<x>;
  };

  /// Update an element `L<k, v...>` with `L<F<k, v...>, v...>`.
  /// \pre `unpack<size<>>::f<x> >= 1`
  template<class F>
  struct map_element_key_update
  {
    template<class x>
    using f = typename unpack<partial_tee<F, emp::wrapper<x>>>
      ::template f<x>;
  };

  /// If the \map contain the key \c Key, replaces the existing element `L<k, v...>` with `L<F<k, v...>, v...>`.
  /// \pre \c is_map<>
  /// \treturn \sequence
  template<class Key, class F, class C = listify>
  using map_update_key = map_update<Key, map_element_key_update<F>, C>;

  /// If the \map contain the key \c Key, replaces the existing element `L<k, v...>` with `L<k, F<k, v...>>`.
  /// \pre \c is_map<>
  /// \treturn \map
  template<class Key, class F, class C = listify>
  using map_update_value = map_update<Key, map_element_value_update<F>, C>;

  /// If the \map contain a key \c emp::front<KV>, replaces the existing element `L<k, v...>` with `F<k, v...>`; otherwise, inserts it using \c push_back<KV>.
  /// \pre \c is_map<>
  /// \treturn \sequence
  template<class KV, class F, class C = listify>
  using map_update_or_insert = if_<
    map_contains<unpack<front<>>::f<KV>>,
    map_update<unpack<front<>>::f<KV>, F, C>,
    push_back<KV, C>
  >;

  /// If the \map contain a key \c emp::front<KV>, replaces the existing element `L<k, v...>` with `L<k, F<k, v...>>`; otherwise, inserts it using \c push_back<KV>.
  /// \pre \c is_map<>
  /// \treturn \map
  template<class KV, class F, class C = listify>
  using map_update_value_or_insert = map_update_or_insert<KV, map_element_value_update<F>, C>;


  namespace emp
  {
    template<class L, class Key, class F, class C = mp::listify>
    using map_update = unpack<L, mp::map_update<Key, F, C>>;

    template<class KV, class F>
    using map_element_key_update = typename mp::map_element_key_update<F>
      ::template f<KV>;

    template<class KV, class F>
    using map_element_value_update = typename mp::map_element_value_update<F>
      ::template f<KV>;

    template<class L, class Key, class F, class C = mp::listify>
    using map_update_key = unpack<L, mp::map_update_key<Key, F, C>>;

    template<class L, class Key, class F, class C = mp::listify>
    using map_update_value = unpack<L, mp::map_update_value<Key, F, C>>;

    template<class L, class KV, class F, class C = mp::listify>
    using map_update_or_insert = unpack<L, mp::map_update_or_insert<KV, F, C>>;

    template<class L, class KV, class F, class C = mp::listify>
    using map_update_value_or_insert = unpack<L, mp::map_update_value_or_insert<KV, F, C>>;
  }
}

namespace jln::mp
{
  /// \ingroup map

  /// If the \map contain the key \c emp::front<KV>, replaces the existing element with \c KV.
  /// \pre \c is_map<>
  /// \treturn \map
  template<class KV, class C = listify>
  using map_replace = map_update<unpack<front<>>::f<KV>, always<KV>, C>;

  /// If the \map contain the key \c emp::front<KV>, replaces the existing element with \c KV; otherwise, inserts it using \c push_back<KV>.
  /// \pre \c is_map<>
  /// \treturn \map
  template<class KV, class C = listify>
  using map_replace_or_insert = map_update_or_insert<KV, always<KV>, C>;

  namespace emp
  {
    template<class L, class KV, class C = mp::listify>
    using map_replace = unpack<L, mp::map_replace<KV, C>>;

    template<class L, class KV, class C = mp::listify>
    using map_replace_or_insert = unpack<L, mp::map_replace_or_insert<KV, C>>;
  }
}


namespace jln::mp
{
  /// \ingroup number

#if JLN_MP_CUDA
#  define JLN_MP_AS_MP_INT(v) std::enable_if_t<v < 0 || std::size_t{v} <= (~0ull >> 1), int_>{v}
#else
#  define JLN_MP_AS_MP_INT(v) JLN_MP_INTEGRAL_AS(int_, v)
#endif

  /// Convertion without narrowing from \value to \number.
  /// \treturn \number
  template<class C = identity>
  struct as_number
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_AS_MP_INT(x::value)>);
  };

  namespace emp
  {
    template<class x>
    using as_number = number<JLN_MP_AS_MP_INT(x::value)>;
  }

  /// \cond
  template<>
  struct as_number<identity>
  {
    template<class x>
    using f = number<JLN_MP_AS_MP_INT(x::value)>;
  };
  /// \endcond
}

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class x>
    struct _is_number;
  }
  /// \endcond

  /// \ingroup number

  /// Checks whether a \value is a \number.
  /// \treturn \bool
  template<class C = identity>
  struct is_number
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_is_number<x>::type);
  };

  namespace emp
  {
    template<class x>
    using is_number = typename detail::_is_number<x>::type;
  }

  /// \cond
  template<>
  struct is_number<identity>
  {
    template<class x>
    using f = typename detail::_is_number<x>::type;
  };
  /// \endcond
}



/// \cond
namespace jln::mp::detail
{
  template<class x>
  struct _is_number
  {
    using type = false_;
  };

  template<int_ x>
  struct _is_number<number<x>>
  {
    using type = true_;
  };
}
/// \endcond

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_ b, int_ e, int_ r = 1>
    struct _ipow;

    template<class base, class exponent>
    using _pow = typename _ipow<base::value, exponent::value, 1>::type;
  }
  /// \endcond

  /// \ingroup number

  template<class Cmp = less<>, class C = identity>
  using min = fold<if_<flip<Cmp>, at1<>, at0<>>, C>;

  template<class Cmp = less<>, class C = identity>
  using min0 = if_<size<>, min<Cmp, C>, always<number<0>, C>>;


  template<class Cmp = less<>, class C = identity>
  using max = fold<if_<Cmp, at1<>, at0<>>, C>;

  template<class Cmp = less<>, class C = identity>
  using max0 = if_<size<>, max<Cmp, C>, always<number<0>, C>>;


  template<class Min, class Max, class Cmp = less<>, class C = identity>
  using clamp = if_<push_back<Min, Cmp>, always<Min>,
    detail::substitute_if<push_front<Max, Cmp>, Max>>;

  template<int_ min, int_ max, class Cmp = less<>, class C = identity>
  using clamp_c = clamp<number<min>, number<max>, Cmp, C>;


  template<class Cmp = less<>, class C = identity>
  using abs = tee<identity, neg<>, if_<Cmp, at1<C>, at0<C>>>;


  template<class C = identity>
  using pow = fold<lift<detail::_pow>, C>;

  template<class C = identity>
  using pow0 = if_<size<>, pow<C>, always<number<0>, C>>;

  template<class C = identity>
  using pow1 = if_<size<>, pow<C>, always<number<1>, C>>;


  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using min = unpack<L, mp::min<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using min0 = unpack<L, mp::min0<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using max = unpack<L, mp::max<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using max0 = unpack<L, mp::max0<Cmp, C>>;

    template<class I, class Min, class Max, class Cmp = mp::less<>, class C = mp::identity>
    using clamp = typename mp::clamp<Min, Max, Cmp, C>::template f<I>;

    template<int_ I, int_ min, int_ max, class Cmp = mp::less<>, class C = mp::identity>
    using clamp_c = typename mp::clamp_c<min, max, Cmp, C>::template f<number<I>>;

    template<class I, class Cmp = mp::less<>, class C = mp::identity>
    using abs = typename mp::abs<Cmp, C>::template f<I>;

    template<int_ I, class Cmp = mp::less<>, class C = mp::identity>
    using abs_c = typename mp::abs<Cmp, C>::template f<number<I>>;

    template<class L, class C = mp::identity>
    using pow = unpack<L, mp::pow<C>>;

    template<class L, class C = mp::identity>
    using pow0 = unpack<L, mp::pow0<C>>;

    template<class L, class C = mp::identity>
    using pow1 = unpack<L, mp::pow1<C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<int_ b, int_ e, int_ r>
  struct _ipow
  : _ipow<(b * b), (e / 2), (e % 2 ? b * r : r)>
  {};

  template<int_ b, int_ r>
  struct _ipow<b, 0, r>
  {
    using type = number<1>;
  };

  template<int_ b, int_ r>
  struct _ipow<b, 1, r>
  {
    using type = number<b * r>;
  };

  template<int_ b, int_ r>
  struct _ipow<b, -1, r>
  {
    using type = number<1 / (b * r)>;
  };

  template<int_ r>
  struct _ipow<0, -1, r>
  {};
}
/// \endcond


namespace jln::mp
{
  /// \cont
  namespace detail
  {
    template<class L, class C = listify>
    struct set_difference_impl
    {};
  }
  /// \endcont

  /// \ingroup set

  /// Removes the elements of the list \c L that appear in any of the sets \c Sets.
  /// \treturn \set
  /// \pre `emp::is_unique<Sets> && ...`
  /// \post \c emp::is_unique<result>
  template<class C = listify>
  struct set_difference
  {
    template<class L, class... Sets>
    using f = typename detail::set_difference_impl<L>::template f<C, Sets...>;
  };

  namespace emp
  {
    template<class L, class... Sets>
    using set_difference = typename detail::set_difference_impl<L>::template f<listify, Sets...>;
  }
}

/// \cont
namespace jln::mp::detail
{
  template<template<class...> class List, class... xs>
  struct set_difference_impl<List<xs...>>
  {
    template<class C, class... Sets>
    using f = typename join<C>::template f<
      typename wrap_in_list_c<!emp::set_any_contains_v<xs, Sets...>>
      ::template f<xs>...
    >;
  };
}
/// \endcont


namespace jln::mp
{
  /// \cont
  namespace detail
  {
    template<class L, class C = listify>
    struct set_intersection_impl
    {};
  }
  /// \endcont

  /// \ingroup set

  /// Returns a \set that contains the elements that occur in all of the sets \c Sets.
  /// \pre `emp::is_unique<Sets> && ...`
  /// \post \c emp::is_unique<result>
  /// \treturn \set
  template<class C = listify>
  struct set_intersection
  {
    template<class L, class... Sets>
    using f = typename detail::set_intersection_impl<L>::template f<C, Sets...>;
  };

  namespace emp
  {
    template<class L, class... Sets>
    using set_intersection = typename detail::set_intersection_impl<L>::template f<listify, Sets...>;
  }
}

/// \cont
namespace jln::mp::detail
{
  template<template<class...> class List, class... xs>
  struct set_intersection_impl<List<xs...>>
  {
    template<class C, class... Sets>
    using f = typename join<C>::template f<
      typename wrap_in_list_c<emp::set_all_contains_v<xs, Sets...>>
      ::template f<xs>...
    >;
  };
}
/// \endcont


namespace jln::mp
{
  /// \ingroup set

  /// Appends to the end of the \set \c Set the elements of \c xs which are not already in \c Set.
  /// \treturn \set
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   fold<lift<emp::set_push_back>>::f<xs...>
  ///   \endcode
  /// \pre \c emp::is_unique<Set>
  /// \post \c emp::is_unique<result>
  /// \see set_push_back, set_push_front_elements
#ifdef JLN_MP_DOXYGENATING
  template<class C = listify>
  struct set_push_back_elements
  {
    template<class Set, class... xs>
    using f;
  };
#else
  template<class C = listify>
  using set_push_back_elements = fold<
    lift<emp::set_push_back>,
    detail::optimize_useless_unpack_t<unpack<C>>
  >;
#endif

  namespace emp
  {
    template<class Set, class... xs>
    using set_push_back_elements = typename mp::set_push_back_elements<>::template f<Set, xs...>;
  }
}


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct set_push_front_select;

    template<class S, class x, class = number<0>>
    struct set_push_front_impl;
  }
  /// \endcond

  /// \ingroup set

  /// Appends \c x to the beginning of the \set whose elements are \c xs if not already in \c xs.
  /// \treturn \set
  /// \pre `emp::unique<xs...> == list<xs...>`
  /// \post \c emp::is_unique<result>
  /// \see set_push_back, set_push_front_elements
  template<class x, class C = listify>
  struct set_push_front
  {
    template<class... xs>
    using f = typename detail::set_push_front_select<JLN_MP_SET_CONTAINS(x, xs...)>
      ::template f<JLN_MP_TRACE_F(C), x, xs...>;
  };

  namespace emp
  {
    template<class Set, class x>
    using set_push_front = typename detail::set_push_front_impl<Set, x>::type;
  }
}


/// \cond

namespace jln::mp::detail
{
  template<>
  struct set_push_front_select<false>
  {
    template<class C, class... xs>
    using f = typename C::template f<xs...>;
  };

  template<>
  struct set_push_front_select<true> : set_push_back_select<true>
  {};

  template<class L, class x, class>
  struct set_push_front_impl
  {
    using type = L;
  };

  template<class... xs, class x>
  struct set_push_front_impl<list<xs...>, x, number<JLN_MP_SET_CONTAINS(x, xs...)>>
  {
    using type = list<x, xs...>;
  };
}
/// \endcond


namespace jln::mp
{
  /// \ingroup set

  /// Appends to the beginning of the \set \c Set the elements of \c xs which are not already in \c Set.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   fold<lift<emp::set_push_front>>::f<xs...>
  ///   \endcode
  /// \treturn \set
  /// \pre \c emp::is_unique<Set>
  /// \post \c emp::is_unique<result>
  /// \see set_push_front, set_push_back_elements
#ifdef JLN_MP_DOXYGENATING
  template<class C = listify>
  struct set_push_front_elements
  {
    template<class Set, class... xs>
    using f;
  };
#else
  template<class C = listify>
  using set_push_front_elements = fold<
    lift<emp::set_push_front>,
    detail::optimize_useless_unpack_t<unpack<C>>
  >;
#endif

  namespace emp
  {
    template<class Set, class... xs>
    using set_push_front_elements = typename mp::set_push_front_elements<>::template f<Set, xs...>;
  }
}


namespace jln::mp
{
  /// \ingroup set

  /// Appends to the end of the \set \c Set the elements of \c Ls which are not already in \c Set.
  /// \treturn \set
  /// \pre \c emp::is_unique<Set>
  /// \post \c emp::is_unique<result>
  template<class C = listify>
  struct set_union
  {
    template<class Set, class... Ls>
    using f = typename unpack<set_push_back_elements<C>>::template f<emp::join<Ls...>, Set>;
  };

  namespace emp
  {
    template<class Set, class... Ls>
    using set_union = mp::set_union<>::f<Set, Ls...>;
  }
}

namespace jln::mp
{
  /// \ingroup trait

  /// Wrapper for alignof keyword
  /// \treturn \number
  template<class C = identity>
  struct alignof_
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<alignof(x)>);
  };

  namespace emp
  {
    template<class x>
    using alignof_ = number<alignof(x)>;
  }

  /// \cond
  template<>
  struct alignof_<identity>
  {
    template<class x>
    using f = number<alignof(x)>;
  };
  /// \endcond
}

namespace jln::mp
{
  /// \ingroup trait

#if !JLN_MP_FEATURE_CONCEPTS || !JLN_MP_GCC
  /// \cond
  namespace detail
  {
    template<class x, class = void>
    struct _has_type;
  }
  /// \endcond

  /// Checks whether \c x has a type member.
  /// \treturn \bool
  template<class C = identity>
  struct has_type
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_has_type<x>::type);
  };

  namespace emp
  {
    template<class x>
    using has_type = typename detail::_has_type<x>::type;

    template<class x>
    inline constexpr bool has_type_v = detail::_has_type<x>::type::value;
  }

  /// \cond
  template<>
  struct has_type<identity>
  {
    template<class x>
    using f = typename detail::_has_type<x>::type;
  };
  /// \endcond

#else

  template<class C = identity>
  struct has_type
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<requires{ typename x::type; }>);
  };

  namespace emp
  {
    template<class x>
    using has_type = number<requires{ typename x::type; }>;

    template<class x>
    inline constexpr bool has_type_v = requires{ typename x::type; };
  }

  /// \cond
  template<>
  struct has_type<identity>
  {
    template<class x>
    using f = number<requires{ typename x::type; }>;
  };
  /// \endcond

#undef JLN_MP_HAS_TYPE

#endif
}

#if !JLN_MP_FEATURE_CONCEPTS || !JLN_MP_GCC

/// \cond
namespace jln::mp::detail
{
  template<class x, class>
  struct _has_type
  {
    using type = false_;
  };

  template<class x>
  struct _has_type<x, std::void_t<typename x::type>>
  {
    using type = true_;
  };
}
/// \endcond
#endif

namespace jln::mp
{
  /// \ingroup trait

#if !JLN_MP_FEATURE_CONCEPTS || !JLN_MP_GCC
  /// \cond
  namespace detail
  {
    template<class x, class = void>
    struct _has_value_type;
  }
  /// \endcond

  /// Checks whether \c x has a type member.
  /// \treturn \bool
  template<class C = identity>
  struct has_value_type
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_has_value_type<x>::type);
  };

  namespace emp
  {
    template<class x>
    using has_value_type = typename detail::_has_value_type<x>::type;

    template<class x>
    inline constexpr bool has_value_type_v = detail::_has_value_type<x>::type::value;
  }

  /// \cond
  template<>
  struct has_value_type<identity>
  {
    template<class x>
    using f = typename detail::_has_value_type<x>::type;
  };
  /// \endcond

#else

  template<class C = identity>
  struct has_value_type
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<requires{ typename x::value_type; }>);
  };

  namespace emp
  {
    template<class x>
    using has_value_type = number<requires{ typename x::value_type; }>;

    template<class x>
    inline constexpr bool has_value_type_v = requires{ typename x::value_type; };
  }

  /// \cond
  template<>
  struct has_value_type<identity>
  {
    template<class x>
    using f = number<requires{ typename x::value_type; }>;
  };
  /// \endcond

#undef JLN_MP_HAS_TYPE

#endif
}

#if !JLN_MP_FEATURE_CONCEPTS || !JLN_MP_GCC

/// \cond
namespace jln::mp::detail
{
  template<class x, class>
  struct _has_value_type
  {
    using type = false_;
  };

  template<class x>
  struct _has_value_type<x, std::void_t<typename x::value_type>>
  {
    using type = true_;
  };
}
/// \endcond
#endif

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<template<class...> class Tpl, class T>
    struct _is_specialization_of;
  }
  /// \endcond

  /// \ingroup trait

  /// Checks whether \c x is \c Tpl<xs...>
  /// \treturn \bool
  template<template<class...> class Tpl, class C = identity>
  struct is_specialization_of
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::_is_specialization_of<Tpl, x>::type);
  };

  namespace emp
  {
    template<template<class...> class Tpl, class x>
    using is_specialization_of = typename detail::_is_specialization_of<Tpl, x>::type;
  }

  /// \cond
  template<template<class...> class Tpl>
  struct is_specialization_of<Tpl, identity>
  {
    template<class x>
    using f = typename detail::_is_specialization_of<Tpl, x>::type;
  };
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template<template<class...> class Tpl, class T>
  struct _is_specialization_of
  {
    using type = false_;
  };

  template<template<class...> class Tpl, class... Ts>
  struct _is_specialization_of<Tpl, Tpl<Ts...>>
  {
    using type = true_;
  };
}
/// \endcond


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<uint_>
    struct iterate_impl;
  }
  /// \endcond

  /// \ingroup utility

  /// Apply a function \c n times to its argument.
  /// \treturn \value
  template<uint_ n, class F, class C = identity>
  struct iterate_c
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::iterate_impl<n>::template f<n, JLN_MP_TRACE_F(F), x>
    );
  };

  /// Apply a function \c n times to its argument.
  /// \treturn \value
  template<class n, class F, class C = identity>
  using iterate = iterate_c<n::value, F, C>;

  namespace emp
  {
    template<class L, class n, class F, class C = mp::identity>
    using iterate = unpack<L, mp::iterate<n, F, C>>;

    template<class L, uint_ n, class F, class C = mp::identity>
    using iterate_c = unpack<L, mp::iterate_c<n, F, C>>;
  }

  /// \cond
  template<uint_ n, class F>
  struct iterate_c<n, F, identity>
  {
    template<class x>
    using f = typename detail::iterate_impl<n>
      ::template f<n, JLN_MP_TRACE_F(F), x>;
  };
  /// \endcond
} // namespace jln::mp


/// \cond
namespace jln::mp::detail
{
  template<uint_ n>
  struct iterate_impl : iterate_impl<
      n <= 16 ? 8
    : n <= 32 ? 16
    : n <= 64 ? 32
    : n <= 128 ? 64
    : 128
  >
  {
  };

  template<>
  struct iterate_impl<0>
  {
    template<uint_ i, class F, class x>
    using f = x;
  };

#define JLN_MP_ITERATE(n, mp_xs, mp_rsx, mp_rep)  \
  template<>                                      \
  struct iterate_impl<n>                          \
  {                                               \
    template<uint_ i, class F, class x>           \
    using f =                                     \
      mp_rep(typename F::template f<, JLN_MP_NIL) \
      x                                           \
      mp_rep(>, JLN_MP_NIL)                       \
    ;                                             \
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_ITERATE)

#undef JLN_MP_ITERATE

  template<class F, class x>
  struct iterate8_impl
  {
    using type =
      typename F::template f<
        typename F::template f<
          typename F::template f<
            typename F::template f<
              typename F::template f<
                typename F::template f<
                  typename F::template f<
                    typename F::template f<
                      x>>>>>>>>;
  };

  template<>
  struct iterate_impl<8>
  {
    template<uint_ i, class F, class x>
    using f = typename iterate_impl<i-8>
      ::template f<i-8, F, typename iterate8_impl<F, x>::type>;
  };

  template<>
  struct iterate_impl<16>
  {
    template<uint_ i, class F, class x>
    using f = typename iterate_impl<i-16>
      ::template f<i-16, F, typename iterate8_impl<
        F, typename iterate8_impl<F, x>::type
      >::type>;
  };

#define JLN_MP_ITERATE(n)                                   \
  template<>                                                \
  struct iterate_impl<n>                                    \
  {                                                         \
    template<uint_ i, class F, class x>                     \
    using f = typename iterate_impl<i-n>                    \
      ::template f<i-n, F,                                  \
        typename iterate_impl<n/2>::template f<n/2, F,      \
          typename iterate_impl<n/2>::template f<n/2, F, x> \
        >                                                   \
      >;                                                    \
  }

  JLN_MP_ITERATE(32);
  JLN_MP_ITERATE(64);
  JLN_MP_ITERATE(128);

#undef JLN_MP_ITERATE
}
/// \endcond

namespace jln::mp
{
  /// \ingroup utility

  /// Rewrap result of \c unpack<C> in the same type as \c L.
  /// \semantics
  ///   \code
  ///   rewrap_unpack<C>::f<L, xs...>
  ///   ==
  ///   unpack<emp::wraper<L>>::f<unpack<C>::f<L, xs...>>
  ///
  ///   rewrap_unpack<remove<b>>::f<std::tuple<a, b, c>, d, e>
  ///   ==
  ///   std::tuple<d, e, a, c>
  ///   \endcode
  /// \treturn \sequence
  template<class C>
  struct rewrap_unpack
  {
    template<class L, class... xs>
    using f = typename detail::_unpack<
      typename detail::wrapper<L>::type,
      typename detail::_unpack<C, L, xs...>::type
    >::type;
  };

  /// Rewrap result of \c unpack_append<C> in the same type as \c L.
  /// \semantics
  ///   \code
  ///   rewrap_unpack_append<C>::f<L, xs...>
  ///   ==
  ///   unpack<emp::wraper<L>>::f<unpack_append<C>::f<L, xs...>>
  ///
  ///   rewrap_unpack<remove<b>>::f<std::tuple<a, b, c>, d, e>
  ///   ==
  ///   std::tuple<a, c, d, e>
  ///   \endcode
  /// \treturn \sequence
  template<class C>
  struct rewrap_unpack_append
  {
    template<class L, class... xs>
    using f = typename detail::_unpack<
      typename detail::wrapper<L>::type,
      typename detail::_unpack_append<C, L, xs...>::type
    >::type;
  };

  namespace emp
  {
    template<class L, class C, class... xs>
    using rewrap_unpack = typename detail::_unpack<
      wrapper<L>,
      typename detail::_unpack<C, L, xs...>::type
    >::type;

    template<class L, class C, class... xs>
    using rewrap_unpack_append = typename detail::_unpack<
      wrapper<L>,
      typename detail::_unpack_append<C, L, xs...>::type
    >::type;
  }
  /// \ingroup trait

  /// Wrapper for sizeof keyword
  /// \treturn \number
  template<class C = identity>
  struct sizeof_
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<sizeof(x)>);
  };

  namespace emp
  {
    template<class x>
    using sizeof_ = number<sizeof(x)>;
  }

  /// \cond
  template<>
  struct sizeof_<identity>
  {
    template<class x>
    using f = number<sizeof(x)>;
  };
  /// \endcond
}


namespace jln::mp::traits
{
  /// \ingroup trait

#define JLN_MP_MAKE_TRAIT(Name)                   \
  template<class C = identity>                    \
  struct Name                                     \
  {                                               \
    template<class... xs>                         \
    using f = JLN_MP_CALL_TRACE(C,                \
      typename std::Name<xs...>::type);           \
  };                                              \
                                                  \
  namespace emp                                   \
  {                                               \
    template<class... xs>                         \
    using Name = typename std::Name<xs...>::type; \
  }                                               \
                                                  \
  template<>                                      \
  struct Name<identity>                           \
  {                                               \
    template<class... xs>                         \
    using f = typename std::Name<xs...>::type;    \
  }


#if defined(_GLIBCXX_RELEASE)
#  define JLN_MP_LIBSTDCXX _GLIBCXX_RELEASE
#else
#  define JLN_MP_LIBSTDCXX 0
#endif

#if defined(_LIBCPP_VERSION)
#  define JLN_MP_LIBCXX _LIBCPP_VERSION
#else
#  define JLN_MP_LIBCXX 0
#endif

#if defined(_MSVC_STL_UPDATE)
#  define JLN_MP_LIBMS _MSVC_STL_UPDATE
#else
#  define JLN_MP_LIBMS 0
#endif


  // primary type categories:
#if __cplusplus >= 201703L
  JLN_MP_MAKE_TRAIT(is_void);
#endif
#if __cplusplus >= 201402L
  JLN_MP_MAKE_TRAIT(is_null_pointer);
#endif
  JLN_MP_MAKE_TRAIT(is_integral);
  JLN_MP_MAKE_TRAIT(is_floating_point);
  JLN_MP_MAKE_TRAIT(is_array);
  JLN_MP_MAKE_TRAIT(is_pointer);
  JLN_MP_MAKE_TRAIT(is_lvalue_reference);
  JLN_MP_MAKE_TRAIT(is_rvalue_reference);
  JLN_MP_MAKE_TRAIT(is_member_object_pointer);
  JLN_MP_MAKE_TRAIT(is_member_function_pointer);
  JLN_MP_MAKE_TRAIT(is_enum);
  JLN_MP_MAKE_TRAIT(is_union);
  JLN_MP_MAKE_TRAIT(is_class);
  JLN_MP_MAKE_TRAIT(is_function);

  // composite type categories:
  JLN_MP_MAKE_TRAIT(is_reference);
  JLN_MP_MAKE_TRAIT(is_arithmetic);
  JLN_MP_MAKE_TRAIT(is_fundamental);
  JLN_MP_MAKE_TRAIT(is_object);
  JLN_MP_MAKE_TRAIT(is_scalar);
  JLN_MP_MAKE_TRAIT(is_compound);
  JLN_MP_MAKE_TRAIT(is_member_pointer);

  // type properties:
  JLN_MP_MAKE_TRAIT(is_const);
  JLN_MP_MAKE_TRAIT(is_volatile);
  JLN_MP_MAKE_TRAIT(is_trivial);
  JLN_MP_MAKE_TRAIT(is_trivially_copyable);
  JLN_MP_MAKE_TRAIT(is_standard_layout);
#if __cplusplus <= 201703L
  JLN_MP_MAKE_TRAIT(is_pod);
#endif
  JLN_MP_MAKE_TRAIT(is_empty);
  JLN_MP_MAKE_TRAIT(is_polymorphic);
  JLN_MP_MAKE_TRAIT(is_abstract);
#if __cplusplus >= 201402L
  JLN_MP_MAKE_TRAIT(is_final);
#endif
#if __cplusplus >= 201703L
  JLN_MP_MAKE_TRAIT(is_aggregate);
#endif
  JLN_MP_MAKE_TRAIT(is_signed);
  JLN_MP_MAKE_TRAIT(is_unsigned);
#if defined(__cpp_lib_bounded_array_traits) && __cpp_lib_bounded_array_traits
  JLN_MP_MAKE_TRAIT(is_bounded_array);
  JLN_MP_MAKE_TRAIT(is_unbounded_array);
#endif
  JLN_MP_MAKE_TRAIT(is_constructible);
  JLN_MP_MAKE_TRAIT(is_default_constructible);
  JLN_MP_MAKE_TRAIT(is_copy_constructible);
  JLN_MP_MAKE_TRAIT(is_move_constructible);
  JLN_MP_MAKE_TRAIT(is_assignable);
  JLN_MP_MAKE_TRAIT(is_copy_assignable);
  JLN_MP_MAKE_TRAIT(is_move_assignable);
#if __cplusplus >= 201703L
  JLN_MP_MAKE_TRAIT(is_swappable_with);
  JLN_MP_MAKE_TRAIT(is_swappable);
  JLN_MP_MAKE_TRAIT(is_nothrow_swappable_with);
  JLN_MP_MAKE_TRAIT(is_nothrow_swappable);
#endif
  JLN_MP_MAKE_TRAIT(is_destructible);
  JLN_MP_MAKE_TRAIT(is_trivially_constructible);
  JLN_MP_MAKE_TRAIT(is_trivially_default_constructible);
  JLN_MP_MAKE_TRAIT(is_trivially_copy_constructible);
  JLN_MP_MAKE_TRAIT(is_trivially_move_constructible);
  JLN_MP_MAKE_TRAIT(is_trivially_assignable);
  JLN_MP_MAKE_TRAIT(is_trivially_copy_assignable);
  JLN_MP_MAKE_TRAIT(is_trivially_move_assignable);
  JLN_MP_MAKE_TRAIT(is_trivially_destructible);
  JLN_MP_MAKE_TRAIT(is_nothrow_constructible);
  JLN_MP_MAKE_TRAIT(is_nothrow_default_constructible);
  JLN_MP_MAKE_TRAIT(is_nothrow_copy_constructible);
  JLN_MP_MAKE_TRAIT(is_nothrow_move_constructible);
  JLN_MP_MAKE_TRAIT(is_nothrow_assignable);
  JLN_MP_MAKE_TRAIT(is_nothrow_copy_assignable);
  JLN_MP_MAKE_TRAIT(is_nothrow_move_assignable);
  JLN_MP_MAKE_TRAIT(is_nothrow_destructible);
  JLN_MP_MAKE_TRAIT(has_virtual_destructor);
#if __cplusplus >= 201703L
  JLN_MP_MAKE_TRAIT(has_unique_object_representations);
#endif

  // type property queries:
  JLN_MP_MAKE_TRAIT(alignment_of);
  JLN_MP_MAKE_TRAIT(rank);

  template<class C = identity>
  struct extent
  {
    template<class x, class i>
    using f = JLN_MP_CALL_TRACE(C, typename std::extent<x, i::value>::type);
  };

  namespace emp
  {
    template<class x, class i = number<0>>
    using extent = typename std::extent<x, i::value>::type;
  }

  /// \cond
  template<>
  struct extent<identity>
  {
    template<class x, class i = number<0>>
    using f = typename std::extent<x, i::value>::type;
  };
  /// \endcond

  // type relations:
  JLN_MP_MAKE_TRAIT(is_same);
  JLN_MP_MAKE_TRAIT(is_base_of);
  JLN_MP_MAKE_TRAIT(is_convertible);
#if defined(__cpp_lib_is_nothrow_convertible) && __cpp_lib_is_nothrow_convertible
// is_nothrow_convertible is an alias, not a class: https://github.com/microsoft/STL/issues/4317
# if JLN_MP_WORKAROUND(JLN_MP_LIBMS, <= 202401)
  template<class C = identity>
  struct is_nothrow_convertible
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      std::bool_constant<std::is_nothrow_convertible_v<xs...>>);
  };

  namespace emp
  {
    template<class... xs>
    using is_nothrow_convertible = std::bool_constant<std::is_nothrow_convertible_v<xs...>>;
  }

  template<>
  struct is_nothrow_convertible<identity>
  {
    template<class... xs>
    using f = std::bool_constant<std::is_nothrow_convertible_v<xs...>>;
  };
# else
  JLN_MP_MAKE_TRAIT(is_nothrow_convertible);
# endif
#endif
#if defined(__cpp_lib_is_layout_compatible) && __cpp_lib_is_layout_compatible
  JLN_MP_MAKE_TRAIT(is_layout_compatible);
#endif
#if defined(__cpp_lib_is_pointer_interconvertible) && __cpp_lib_is_pointer_interconvertible
  JLN_MP_MAKE_TRAIT(is_pointer_interconvertible_base_of);
#endif
#if __cplusplus >= 201703L
  JLN_MP_MAKE_TRAIT(is_invocable);
  JLN_MP_MAKE_TRAIT(is_invocable_r);
  JLN_MP_MAKE_TRAIT(is_nothrow_invocable);
  JLN_MP_MAKE_TRAIT(is_nothrow_invocable_r);
#endif

  // const-volatile modifications:
  JLN_MP_MAKE_TRAIT(remove_const);
  JLN_MP_MAKE_TRAIT(remove_volatile);
  JLN_MP_MAKE_TRAIT(remove_cv);
  JLN_MP_MAKE_TRAIT(add_const);
  JLN_MP_MAKE_TRAIT(add_volatile);
  JLN_MP_MAKE_TRAIT(add_cv);

  // reference modifications:
  JLN_MP_MAKE_TRAIT(remove_reference);
  JLN_MP_MAKE_TRAIT(add_lvalue_reference);
  JLN_MP_MAKE_TRAIT(add_rvalue_reference);

  // sign modifications:
  JLN_MP_MAKE_TRAIT(make_signed);
  JLN_MP_MAKE_TRAIT(make_unsigned);

  // array modifications:
  JLN_MP_MAKE_TRAIT(remove_extent);
  JLN_MP_MAKE_TRAIT(remove_all_extents);

  // pointer modifications:
  JLN_MP_MAKE_TRAIT(remove_pointer);
  JLN_MP_MAKE_TRAIT(add_pointer);

  // other transformations:
  JLN_MP_MAKE_TRAIT(decay);
#if defined(__cpp_lib_unwrap_ref) && __cpp_lib_unwrap_ref \
  /* unwrap_reference is missing from <type_traits> with libc++-15 */ \
  && (!JLN_MP_LIBCXX || JLN_MP_LIBCXX >= 16000)
  JLN_MP_MAKE_TRAIT(unwrap_ref_decay);
  JLN_MP_MAKE_TRAIT(unwrap_reference);
#endif
#if defined(__cpp_lib_remove_cvref) && __cpp_lib_remove_cvref
  JLN_MP_MAKE_TRAIT(remove_cvref);
#endif
#if __cplusplus >= 202002L
  JLN_MP_MAKE_TRAIT(common_reference);
  JLN_MP_MAKE_TRAIT(basic_common_reference);
#else
  JLN_MP_MAKE_TRAIT(result_of);
#endif
  JLN_MP_MAKE_TRAIT(underlying_type);
  JLN_MP_MAKE_TRAIT(common_type);
#if __cplusplus >= 201703L
  JLN_MP_MAKE_TRAIT(invoke_result);
#endif

  template<class C = identity>
  struct aligned_storage
  {
    template<class Len, class... Alignment>
    using f = JLN_MP_CALL_TRACE(C,
      typename std::aligned_storage<Len::value, Alignment::value...>::type
    );
  };

  namespace emp
  {
    template<class Len, class... Alignment>
    using aligned_storage = typename std::aligned_storage<
      Len::value, Alignment::value...>::type;
  }

  /// \cond
  template<>
  struct aligned_storage<identity>
  {
    template<class Len, class... Alignment>
    using f = typename std::aligned_storage<Len::value, Alignment::value...>::type;
  };
  /// \endcond

  template<class C = identity>
  struct aligned_union
  {
    template<class len, class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename std::aligned_union<len::value, xs...>::type
    );
  };

  namespace emp
  {
    template<class len, class... xs>
    using aligned_union = typename std::aligned_union<len::value, xs...>::type;
  }

  /// \cond
  template<>
  struct aligned_union<identity>
  {
    template<class len, class... xs>
    using f = typename std::aligned_union<len::value, xs...>::type;
  };
  /// \endcond

#undef JLN_MP_MAKE_TRAIT
}

namespace jln::mp
{
  /// \ingroup trait

  /// Function for \c x::type.
  /// \treturn \value
  template<class C = identity>
  struct type_
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename x::type);
  };

  namespace emp
  {
    template<class x>
    using type_ = typename x::type;
  }

  /// \cond
  template<>
  struct type_<identity>
  {
    template<class x>
    using f = typename x::type;
  };
  /// \endcond
}

namespace jln::mp
{
  /// \ingroup trait

  /// Function for \c x::value_type.
  /// \treturn \value
  template<class C = identity>
  struct value_type
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename x::value_type);
  };

  template<>
  struct value_type<identity>
  {
    template<class x>
    using f = typename x::value_type;
  };

  namespace emp
  {
    template<class x>
    using value_type = typename x::value_type;
  }
}

namespace jln::mp
{
  /// \ingroup value

  /// Converts \c x to \val.
  /// \pre \c emp::has_value<x> == \c true
  /// \treturn \bool
  template<class C = identity>
  struct as_val
  {
#if JLN_MP_ENABLE_TPL_AUTO
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, val<x::value>);
#else
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typed_value<decltype(x::value), x::value>);
#endif
  };

  /// \cond
  template<>
  struct as_val<identity>
  {
#if JLN_MP_ENABLE_TPL_AUTO
    template<class x>
    using f = val<x::value>;
#else
    template<class x>
    using f = typed_value<decltype(x::value), x::value>;
#endif
  };
  /// \endcond

  namespace emp
  {
    template<class x, class C = mp::identity>
    using as_val = typename mp::as_val<C>::template f<x>;
  }
}

namespace jln::mp
{
  /// \ingroup value

#if !JLN_MP_FEATURE_CONCEPTS || !JLN_MP_GCC
  /// \cond
  namespace detail
  {
    template<class x, class = void>
    struct _has_value;
  }
  /// \endcond

  /// Checks whether \c x has a value member.
  /// \treturn \bool
  template<class C = identity>
  struct has_value
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_has_value<x>::type);
  };

  namespace emp
  {
    template<class x>
    using has_value = typename detail::_has_value<x>::type;

    template<class x>
    inline constexpr bool has_value_v = detail::_has_value<x>::type::value;
  }

  /// \cond
  template<>
  struct has_value<identity>
  {
    template<class x>
    using f = typename detail::_has_value<x>::type;
  };
  /// \endcond

#else

  template<class C = identity>
  struct has_value
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<requires{ x::value; }>);
  };

  namespace emp
  {
    template<class x>
    using has_value = number<requires{ x::value; }>;

    template<class x>
    inline constexpr bool has_value_v = requires{ x::value; };
  }

  /// \cond
  template<>
  struct has_value<identity>
  {
    template<class x>
    using f = number<requires{ x::value; }>;
  };
  /// \endcond

#undef JLN_MP_HAS_TYPE

#endif
}

#if !JLN_MP_FEATURE_CONCEPTS || !JLN_MP_GCC

/// \cond
namespace jln::mp::detail
{
  template<class x, class>
  struct _has_value
  {
    using type = false_;
  };

  template<class x>
  struct _has_value<x, decltype(void(x::value))>
  {
    using type = true_;
  };
}
/// \endcond
#endif

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class x>
    struct _is_val;
  }
  /// \endcond

  /// \ingroup value

  /// Checks whether \c x is a \val.
  /// \treturn \bool
  template<class C = identity>
  struct is_val
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_is_val<x>::type);
  };

  namespace emp
  {
    template<class x>
    using is_val = typename detail::_is_val<x>::type;
  }

  /// \cond
  template<>
  struct is_val<identity>
  {
    template<class x>
    using f = typename detail::_is_val<x>::type;
  };
  /// \endcond
}



/// \cond
namespace jln::mp::detail
{
  template<class x>
  struct _is_val
  {
    using type = false_;
  };

#if JLN_MP_ENABLE_TPL_AUTO && (!JLN_MP_ENABLE_DEBUG || JLN_MP_CLANG_LIKE)
  template<auto x>
  struct _is_val<val<x>>
#else
  template<class T, T x>
  struct _is_val<typed_value<T, x>>
#endif
  {
    using type = true_;
  };
}
/// \endcond


JLN_MP_DIAGNOSTIC_PUSH()
JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wlogical-op")

namespace jln::mp
{
  /// \ingroup value

  template<class C = identity>
  struct val_or
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(xs::value || ... || false)>);
  };

  template<class C = identity>
  struct val_left_or
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(false || ... || xs::value)>);
  };


  template<class C = identity>
  struct val_and
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(xs::value && ... && true)>);
  };

  template<class C = identity>
  struct val_left_and
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(true && ... && xs::value)>);
  };


  template<class C = identity>
  struct val_add
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(xs::value + ...)>);
  };

  template<class C = identity>
  using val_add0 = if_<size<>, val_add<C>, always<val<0>, C>>;

  template<class C = identity>
  struct val_left_add
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... + xs::value)>);
  };

  template<class C = identity>
  using val_left_add0 = if_<size<>, val_left_add<C>, always<val<0>, C>>;


  template<class C = identity>
  struct val_sub
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... - xs::value)>);
  };

  template<class C = identity>
  using val_sub0 = if_<size<>, val_sub<C>, always<val<0>, C>>;

  template<class C = identity>
  struct val_lshift
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... << xs::value)>);
  };

  template<class C = identity>
  using val_lshift0 = if_<size<>, val_lshift<C>, always<val<0>, C>>;

  template<class C = identity>
  struct val_rshift
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... >> xs::value)>);
  };

  template<class C = identity>
  using val_rshift0 = if_<size<>, val_rshift<C>, always<val<0>, C>>;


  template<class C = identity>
  struct val_mul
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(xs::value * ...)>);
  };

  template<class C = identity>
  using val_mul0 = if_<size<>, val_mul<C>, always<val<0>, C>>;

  template<class C = identity>
  using val_mul1 = if_<size<>, val_mul<C>, always<val<1>, C>>;

  template<class C = identity>
  struct val_left_mul
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... * xs::value)>);
  };

  template<class C = identity>
  using val_left_mul0 = if_<size<>, val_left_mul<C>, always<val<0>, C>>;

  template<class C = identity>
  using val_left_mul1 = if_<size<>, val_left_mul<C>, always<val<1>, C>>;


  template<class C = identity>
  struct val_div
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... / xs::value)>);
  };

  template<class C = identity>
  using val_div0 = if_<size<>, val_div<C>, always<val<0>, C>>;

  template<class C = identity>
  using val_div1 = if_<size<>, val_div<C>, always<val<1>, C>>;

  template<class C = identity>
  struct val_mod
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... % xs::value)>);
  };

  template<class C = identity>
  using val_mod0 = if_<size<>, val_mod<C>, always<val<0>, C>>;

  template<class C = identity>
  using val_mod1 = if_<size<>, val_mod<C>, always<val<1>, C>>;


  template<class C = identity>
  struct val_xor
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(xs::value ^ ...)>);
  };

  template<class C = identity>
  using val_xor0 = if_<size<>, val_xor<C>, always<val<0>, C>>;

  template<class C = identity>
  struct val_left_xor
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... ^ xs::value)>);
  };

  template<class C = identity>
  using val_left_xor0 = if_<size<>, val_left_xor<C>, always<val<0>, C>>;


  template<class C = identity>
  struct val_bit_and
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(xs::value & ...)>);
  };

  template<class C = identity>
  using val_bit_and0 = if_<size<>, val_bit_and<C>, always<val<0>, C>>;

  template<class C = identity>
  struct val_left_bit_and
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... & xs::value)>);
  };

  template<class C = identity>
  using val_left_bit_and0 = if_<size<>, val_bit_and<C>, always<val<0>, C>>;


  template<class C = identity>
  struct val_bit_or
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(xs::value | ...)>);
  };

  template<class C = identity>
  using val_bit_or0 = if_<size<>, val_bit_or<C>, always<val<0>, C>>;

  template<class C = identity>
  struct val_left_bit_or
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, val<(... | xs::value)>);
  };

  template<class C = identity>
  using val_left_bit_or0 = if_<size<>, val_left_bit_or<C>, always<val<0>, C>>;


  template<class C = identity>
  struct val_neg
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, val<(-x::value)>);
  };

  template<class C = identity>
  struct val_unary_plus
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, val<(+x::value)>);
  };

  template<class C = identity>
  struct val_not
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, val<(!x::value)>);
  };

  template<class C = identity>
  struct val_bit_not
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, val<(~x::value)>);
  };

  template<class C = identity>
  struct val_inc
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, val<(x::value+1)>);
  };

  template<class C = identity>
  struct val_dec
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, val<(x::value-1)>);
  };

  template<class C = identity>
  struct val_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, val<(x::value == y::value)>);
  };

  template<class C = identity>
  struct val_not_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, val<(x::value != y::value)>);
  };

  template<class C = identity>
  struct val_less
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, val<(x::value < y::value)>);
  };

  template<class C = identity>
  struct val_less_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, val<(x::value <= y::value)>);
  };

  template<class C = identity>
  struct val_greater
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, val<(x::value > y::value)>);
  };

  template<class C = identity>
  struct val_greater_equal
  {
    template<class x, class y>
    using f = JLN_MP_CALL_TRACE(C, val<(x::value >= y::value)>);
  };


  template<class N, class C = identity>
  using val_equal_to = push_back<N, val_equal<C>>;

  template<class N, class C = identity>
  using val_not_equal_to = push_back<N, val_not_equal<C>>;

  template<class N, class C = identity>
  using val_less_than = push_back<N, val_less<C>>;

  template<class N, class C = identity>
  using val_less_equal_than = push_back<N, val_less_equal<C>>;

  template<class N, class C = identity>
  using val_greater_than = push_back<N, val_greater<C>>;

  template<class N, class C = identity>
  using val_greater_equal_than = push_back<N, val_greater_equal<C>>;


  template<auto x, class C = identity>
  using val_equal_to_c = val_equal_to<val<x>, C>;

  template<auto x, class C = identity>
  using val_not_equal_to_c = val_not_equal_to<val<x>, C>;

  template<auto x, class C = identity>
  using val_less_than_c = val_less_than<val<x>, C>;

  template<auto x, class C = identity>
  using val_less_equal_than_c = val_less_equal_than<val<x>, C>;

  template<auto x, class C = identity>
  using val_greater_than_c = val_greater_than<val<x>, C>;

  template<auto x, class C = identity>
  using val_greater_equal_than_c = val_greater_equal_than<val<x>, C>;
}

namespace jln::mp::emp
{
  template<class L, class C = mp::identity>
  using val_or_seq = unpack<L, mp::val_or<C>>;

  template<class L, class C = mp::identity>
  using val_and_seq = unpack<L, mp::val_and<C>>;

  template<class L, class C = mp::identity>
  using val_left_or_seq = unpack<L, mp::val_left_or<C>>;

  template<class L, class C = mp::identity>
  using val_left_and_seq = unpack<L, mp::val_left_and<C>>;

  template<class L, class C = mp::identity>
  using val_add_seq = unpack<L, mp::val_add<C>>;

  template<class L, class C = mp::identity>
  using val_add0_seq = unpack<L, mp::val_add0<C>>;

  template<class L, class C = mp::identity>
  using val_left_add_seq = unpack<L, mp::val_left_add<C>>;

  template<class L, class C = mp::identity>
  using val_left_add0_seq = unpack<L, mp::val_left_add0<C>>;

  template<class L, class C = mp::identity>
  using val_sub_seq = unpack<L, mp::val_sub<C>>;

  template<class L, class C = mp::identity>
  using val_sub0_seq = unpack<L, mp::val_sub0<C>>;

  template<class L, class C = mp::identity>
  using val_lshift_seq = unpack<L, mp::val_lshift<C>>;

  template<class L, class C = mp::identity>
  using val_lshift0_seq = unpack<L, mp::val_lshift0<C>>;

  template<class L, class C = mp::identity>
  using val_rshift_seq = unpack<L, mp::val_rshift<C>>;

  template<class L, class C = mp::identity>
  using val_rshift0_seq = unpack<L, mp::val_rshift0<C>>;

  template<class L, class C = mp::identity>
  using val_mul_seq = unpack<L, mp::val_mul<C>>;

  template<class L, class C = mp::identity>
  using val_mul0_seq = unpack<L, mp::val_mul0<C>>;

  template<class L, class C = mp::identity>
  using val_mul1_seq = unpack<L, mp::val_mul1<C>>;

  template<class L, class C = mp::identity>
  using val_left_mul_seq = unpack<L, mp::val_left_mul<C>>;

  template<class L, class C = mp::identity>
  using val_left_mul0_seq = unpack<L, mp::val_left_mul0<C>>;

  template<class L, class C = mp::identity>
  using val_left_mul1_seq = unpack<L, mp::val_left_mul1<C>>;

  template<class L, class C = mp::identity>
  using val_div_seq = unpack<L, mp::val_div<C>>;

  template<class L, class C = mp::identity>
  using val_div0_seq = unpack<L, mp::val_div0<C>>;

  template<class L, class C = mp::identity>
  using val_div1_seq = unpack<L, mp::val_div1<C>>;

  template<class L, class C = mp::identity>
  using val_mod_seq = unpack<L, mp::val_mod<C>>;

  template<class L, class C = mp::identity>
  using val_mod0_seq = unpack<L, mp::val_mod0<C>>;

  template<class L, class C = mp::identity>
  using val_mod1_seq = unpack<L, mp::val_mod1<C>>;

  template<class L, class C = mp::identity>
  using val_xor_seq = unpack<L, mp::val_xor<C>>;

  template<class L, class C = mp::identity>
  using val_xor0_seq = unpack<L, mp::val_xor0<C>>;

  template<class L, class C = mp::identity>
  using val_left_xor_seq = unpack<L, mp::val_left_xor<C>>;

  template<class L, class C = mp::identity>
  using val_left_xor0_seq = unpack<L, mp::val_left_xor0<C>>;

  template<class L, class C = mp::identity>
  using val_bit_and_seq = unpack<L, mp::val_bit_and<C>>;

  template<class L, class C = mp::identity>
  using val_bit_and0_seq = unpack<L, mp::val_bit_and0<C>>;

  template<class L, class C = mp::identity>
  using val_left_bit_and_seq = unpack<L, mp::val_left_bit_and<C>>;

  template<class L, class C = mp::identity>
  using val_left_bit_and0_seq = unpack<L, mp::val_left_bit_and0<C>>;

  template<class L, class C = mp::identity>
  using val_bit_or_seq = unpack<L, mp::val_bit_or<C>>;

  template<class L, class C = mp::identity>
  using val_bit_or0_seq = unpack<L, mp::val_bit_or0<C>>;

  template<class L, class C = mp::identity>
  using val_left_bit_or_seq = unpack<L, mp::val_left_bit_or<C>>;

  template<class L, class C = mp::identity>
  using val_left_bit_or0_seq = unpack<L, mp::val_left_bit_or0<C>>;


  template<auto... xs>
  using val_or_c = val<(xs || ... || false)>;

  template<auto... xs>
  using val_and_c = val<(xs && ... && true)>;

  template<auto... xs>
  using val_left_or_c = val<(false || ... || xs)>;

  template<auto... xs>
  using val_left_and_c = val<(true && ... && xs)>;

  template<auto... xs>
  using val_add_c = val<(xs + ...)>;

  template<auto... xs>
  using val_add0_c = val_add_c<xs..., 0>;

  template<auto... xs>
  using val_left_add_c = val<(... + xs)>;

  template<auto... xs>
  using val_left_add0_c = val_left_add_c<xs..., 0>;

  template<auto... xs>
  using val_sub_c = val<(... - xs)>;

  template<auto... xs>
  using val_sub0_c = val_sub_c<xs..., 0>;

  template<auto... xs>
  using val_lshift_c = val<(... << xs)>;

  template<auto... xs>
  using val_lshift0_c = val_lshift_c<xs..., 0>;

  template<auto... xs>
  using val_rshift_c = val<(... >> xs)>;

  template<auto... xs>
  using val_rshift0_c = val_rshift_c<xs..., 0>;

  template<auto... xs>
  using val_mul_c = val<(xs * ...)>;

  template<auto... xs>
  using val_mul0_c = val_mul_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<auto... xs>
  using val_mul1_c = val_mul_c<xs..., 1>;

  template<auto... xs>
  using val_left_mul_c = val<(... * xs)>;

  template<auto... xs>
  using val_left_mul0_c = val_left_mul_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<auto... xs>
  using val_left_mul1_c = val_left_mul_c<xs..., 1>;

  template<auto... xs>
  using val_div_c = val<(... / xs)>;

  template<auto... xs>
  using val_div0_c = val_div_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<auto... xs>
  using val_div1_c = val_div_c<xs..., 1>;

  template<auto... xs>
  using val_mod_c = val<(... % xs)>;


  template<class... xs>
  using val_or = val<(xs::value || ... || false)>;

  template<class... xs>
  using val_and = val<(xs::value && ... && true)>;

  template<class... xs>
  using val_left_or = val<(false || ... || xs::value)>;

  template<class... xs>
  using val_left_and = val<(true && ... && xs::value)>;

  template<class... xs>
  using val_add = val<(xs::value + ...)>;

  template<class... xs>
  using val_add0 = typename mp::val_add0<>::template f<xs...>;

  template<class... xs>
  using val_left_add = val<(... + xs::value)>;

  template<class... xs>
  using val_left_add0 = typename mp::val_add0<>::template f<xs...>;

  template<class... xs>
  using val_sub = val<(... - xs::value)>;

  template<class... xs>
  using val_sub0 = typename mp::val_sub0<>::template f<xs...>;

  template<class... xs>
  using val_lshift = val<(... << xs::value)>;

  template<class... xs>
  using val_lshift0 = typename mp::val_lshift0<>::template f<xs...>;

  template<class... xs>
  using val_rshift = val<(... >> xs::value)>;

  template<class... xs>
  using val_rshift0 = typename mp::val_rshift0<>::template f<xs...>;

  template<class... xs>
  using val_mul = val<(xs::value * ...)>;

  template<class... xs>
  using val_mul0 = typename mp::val_mul0<>::template f<xs...>;

  template<class... xs>
  using val_mul1 = typename mp::val_mul1<>::template f<xs...>;

  template<class... xs>
  using val_left_mul = val<(... * xs::value)>;

  template<class... xs>
  using val_left_mul0 = typename mp::val_left_mul0<>::template f<xs...>;

  template<class... xs>
  using val_left_mul1 = typename mp::val_left_mul1<>::template f<xs...>;

  template<class... xs>
  using val_div = val<(... / xs::value)>;

  template<class... xs>
  using val_div0 = typename mp::val_div0<>::template f<xs...>;

  template<class... xs>
  using val_div1 = typename mp::val_div1<>::template f<xs...>;

  template<class... xs>
  using val_mod = val<(... % xs::value)>;

  template<class... xs>
  using val_mod0 = typename mp::val_mod0<>::template f<xs...>;

  template<class... xs>
  using val_mod1 = typename mp::val_mod1<>::template f<xs...>;

  template<class... xs>
  using val_xor_ = val<(xs::value ^ ...)>;

  template<class... xs>
  using val_xor0 = typename mp::val_xor0<>::template f<xs...>;

  template<class... xs>
  using val_left_xor = val<(... ^ xs::value)>;

  template<class... xs>
  using val_left_xor0 = typename mp::val_left_xor0<>::template f<xs...>;

  template<class... xs>
  using val_bit_and = val<(xs::value & ...)>;

  template<class... xs>
  using val_bit_and0 = typename mp::val_bit_and0<>::template f<xs...>;

  template<class... xs>
  using val_left_bit_and = val<(... & xs::value)>;

  template<class... xs>
  using val_left_bit_and0 = typename mp::val_left_bit_and0<>::template f<xs...>;

  template<class... xs>
  using val_bit_or = val<(xs::value | ...)>;

  template<class... xs>
  using val_bit_or0 = typename mp::val_bit_or0<>::template f<xs...>;

  template<class... xs>
  using val_left_bit_or = val<(... | xs::value)>;

  template<class... xs>
  using val_left_bit_or0 = typename mp::val_left_bit_or0<>::template f<xs...>;


  template<class x, class C = mp::identity>
  using val_neg = typename mp::val_neg<C>::template f<x>;

  template<class x, class C = mp::identity>
  using val_unary_plus = typename mp::val_unary_plus<C>::template f<x>;

  template<class x, class C = mp::identity>
  using val_not = typename mp::val_not<C>::template f<x>;

  template<class x, class C = mp::identity>
  using val_bit_not = typename mp::val_bit_not<C>::template f<x>;

  template<class x, class C = mp::identity>
  using val_inc = typename mp::val_inc<C>::template f<x>;

  template<class x, class C = mp::identity>
  using val_dec = typename mp::val_dec<C>::template f<x>;

  template<class x, class y, class C = mp::identity>
  using val_equal = typename mp::val_equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using val_not_equal = typename mp::val_not_equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using val_less = typename mp::val_less<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using val_less_equal = typename mp::val_less_equal<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using val_greater = typename mp::val_greater<C>::template f<x, y>;

  template<class x, class y, class C = mp::identity>
  using val_greater_equal = typename mp::val_greater_equal<C>::template f<x, y>;
}

/// \cond
namespace jln::mp::detail
{
  template<bool, template<auto...> class f, int_ d>
  struct val_emp_op;

  template<template<auto...> class F, int_ d>
  struct val_emp_op<true, F, d>
  {
    template<auto... xs>
    using f = F<xs...>;
  };

  template<template<auto...> class F, int_ d>
  struct val_emp_op<false, F, d>
  {
    template<auto...>
    using f = val<d>;
  };
}
/// \endcond

namespace jln::mp::emp
{
  template<auto... xs>
  using val_mod0_c = typename detail::val_emp_op<sizeof...(xs) != 0, val_mod_c, 0>
    ::template f<xs...>;

  template<auto... xs>
  using val_mod1_c = typename detail::val_emp_op<sizeof...(xs) != 0, val_mod_c, 1>
    ::template f<xs...>;

  template<auto... xs>
  using val_xor_c = val<(xs ^ ...)>;

  template<auto... xs>
  using val_xor0_c = val_xor_c<xs..., 0, 0>;

  template<auto... xs>
  using val_left_xor_c = val<(... ^ xs)>;

  template<auto... xs>
  using val_left_xor0_c = val_left_xor_c<xs..., 0, 0>;

  template<auto... xs>
  using val_bit_and_c = val<(xs & ...)>;

  template<auto... xs>
  using val_bit_and0_c = typename detail::val_emp_op<sizeof...(xs) != 0, val_bit_and_c, 0>
    ::template f<xs...>;

  template<auto... xs>
  using val_left_bit_and_c = val<(... & xs)>;

  template<auto... xs>
  using val_left_bit_and0_c = typename detail::val_emp_op<sizeof...(xs) != 0, val_left_bit_and_c, 0>
    ::template f<xs...>;

  template<auto... xs>
  using val_bit_or_c = val<(xs | ...)>;

  template<auto... xs>
  using val_bit_or0_c = typename detail::val_emp_op<sizeof...(xs) != 0, val_bit_or_c, 0>
    ::template f<xs...>;

  template<auto... xs>
  using val_left_bit_or_c = val<(... | xs)>;

  template<auto... xs>
  using val_left_bit_or0_c = typename detail::val_emp_op<sizeof...(xs) != 0, val_left_bit_or_c, 0>
    ::template f<xs...>;
}

JLN_MP_DIAGNOSTIC_POP()

/// \cond
namespace jln::mp
{
  template<>
  struct val_or<identity>
  {
    template<class... xs>
    using f = val<(xs::value || ... || false)>;
  };

  template<>
  struct val_left_or<identity>
  {
    template<class... xs>
    using f = val<(false || ... || xs::value)>;
  };


  template<>
  struct val_and<identity>
  {
    template<class... xs>
    using f = val<(xs::value && ... && true)>;
  };

  template<>
  struct val_left_and<identity>
  {
    template<class... xs>
    using f = val<(true && ... && xs::value)>;
  };


  template<>
  struct val_add<identity>
  {
    template<class... xs>
    using f = val<(xs::value + ...)>;
  };


  template<>
  struct val_not<identity>
  {
    template<class x>
    using f = val<(!x::value)>;
  };


  template<>
  struct val_equal<identity>
  {
    template<class x, class y>
    using f = val<(x::value == y::value)>;
  };

  template<>
  struct val_not_equal<identity>
  {
    template<class x, class y>
    using f = val<(x::value != y::value)>;
  };

  template<>
  struct val_less<identity>
  {
    template<class x, class y>
    using f = val<(x::value < y::value)>;
  };

  template<>
  struct val_less_equal<identity>
  {
    template<class x, class y>
    using f = val<(x::value <= y::value)>;
  };

  template<>
  struct val_greater<identity>
  {
    template<class x, class y>
    using f = val<(x::value > y::value)>;
  };

  template<>
  struct val_greater_equal<identity>
  {
    template<class x, class y>
    using f = val<(x::value >= y::value)>;
  };
}
/// \endcond

#if JLN_MP_ENABLE_TPL_AUTO && (!JLN_MP_ENABLE_DEBUG || JLN_MP_CLANG_LIKE)
namespace jln::mp
{
  /// \ingroup value

  template<class C = listify>
  struct values
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, val<xs::value>...);
  };

  template<class C = listify>
  struct typed_values
  {
    template<class T, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, val<T(xs::value)>...);
  };

  namespace emp
  {
    template<auto... xs>
    using values = list<val<xs>...>;

    template<class T, T... xs>
    using typed_values = list<val<T(xs)>...>;
  }
} // namespace jln::mp
#else
namespace jln::mp
{
  template<class C>
  struct values
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, typed_value<decltype(xs::value), xs::value>...);
  };

  template<class C>
  struct typed_values
  {
    template<class T, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, typed_value<T, xs::value>...);
  };

  namespace emp
  {
    template<class T, T... xs>
    using typed_values = list<typed_value<T, xs>...>;
  }
}
#endif

#endif
