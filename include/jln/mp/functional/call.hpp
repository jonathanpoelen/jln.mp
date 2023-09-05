// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/config/debug.hpp>
#include <jln/mp/config/config.hpp>
#include <jln/mp/detail/compiler.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/memoize.hpp>
#include <jln/mp/utility/conditional.hpp>

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

  #define JLN_MP_CALL_TRACE(C, ...) typename C ::template f<__VA_ARGS__>
  #define JLN_MP_CALL_TRACE_T(C, ...) typename C ::template f<__VA_ARGS__>
  #define JLN_MP_CALL_TRACE_0_ARG(...) typename __VA_ARGS__::template f<>
#else
  // does not compile with msvc...
  #define JLN_MP_TRACE_F(...) memoize<__VA_ARGS__>
  #define JLN_MP_TRACE_TYPENAME typename

  #define JLN_MP_CALL_TRACE(C, ...)            \
    typename ::jln::mp::detail::memoizer_impl< \
      C, ::jln::mp::list<__VA_ARGS__>          \
    >::type
  #define JLN_MP_CALL_TRACE_T(C, ...)          \
    typename ::jln::mp::detail::memoizer_impl< \
      typename C, ::jln::mp::list<__VA_ARGS__> \
    >::type
  #define JLN_MP_CALL_TRACE_0_ARG(...)         \
    typename ::jln::mp::detail::memoizer_impl< \
      __VA_ARGS__, ::jln::mp::list<>           \
    >::type
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
using call = typename detail::memoizer_impl<C, list<xs...>>::type;

#  define JLN_MP_DCALL_TRACE_XS(xs, C, ...) \
    typename ::jln::mp::detail::memoizer_impl<C, ::jln::mp::list<__VA_ARGS__>>::type

#  define JLN_MP_DCALL_TRACE_XS_0(xs, C) \
    typename ::jln::mp::detail::memoizer_impl<C, ::jln::mp::list<>>::type

#  define JLN_MP_DCALL_V_TRACE_XS(xs, C, ...) \
    ::jln::mp::detail::memoizer_impl<C, ::jln::mp::list<__VA_ARGS__>>::type

# else

template<class C, class... xs>
using call = typename conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
  ::template f<C, detail::too_many_arguments_error>
  ::template f<xs...>;

#  define JLN_MP_DCALL_TRACE_XS(xs, C, ...)                                        \
    typename ::jln::mp::conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>     \
      ::template f<JLN_MP_TRACE_F(C), ::jln::mp::detail::too_many_arguments_error> \
      ::template f<__VA_ARGS__>

#  define JLN_MP_DCALL_TRACE_XS_0(xs, C)                                           \
    typename ::jln::mp::conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>     \
      ::template f<JLN_MP_TRACE_F(C), ::jln::mp::detail::too_many_arguments_error> \
      ::template f<>

#  define JLN_MP_DCALL_V_TRACE_XS(xs, C, ...)                                      \
    ::jln::mp::conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>              \
      ::template f<JLN_MP_TRACE_F(C), ::jln::mp::detail::too_many_arguments_error> \
      ::template f<__VA_ARGS__>

# endif
#endif


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
}
/// \endcond
