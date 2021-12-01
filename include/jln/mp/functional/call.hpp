#pragma once

#include <jln/mp/config/debug.hpp>
#include <jln/mp/config/config.hpp>
#include <jln/mp/detail/compiler.hpp>
#include <jln/mp/detail/call_trace.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/memoize.hpp>
#include <jln/mp/utility/conditional.hpp>

namespace jln::mp
{
  class to_many_argument_error {};

  /// \cond
  namespace detail
  {
    template<bool> struct dcall;
    template<bool> struct dcallf;
    template<bool> struct dcall_c;
    template<bool> struct dcallf_c;
  }
  /// \endcond

  /// \ingroup functional

// #define JLN_MP_MSVC_FIX_CALL(C, ...) raw_call<C, __VA_ARGS__>
#define JLN_MP_MSVC_FIX_CALL(C, ...) typename JLN_MP_IDENT C ::template f<__VA_ARGS__>

#define JLN_MP_DCALL_TRACE_XS(xs, C, ...) \
  JLN_MP_DCALL(sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT, JLN_MP_TRACE_F(C), __VA_ARGS__)

#define JLN_MP_DCALL_TRACE(cond, C, ...) JLN_MP_DCALL(cond, JLN_MP_TRACE_F(C), __VA_ARGS__)

#define JLN_MP_DCALL_XS(xs, ...) JLN_MP_DCALL(sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT, __VA_ARGS__)
#define JLN_MP_DCALL_XS_R(xs, ...) JLN_MP_DCALL_R(sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT, __VA_ARGS__)
#define JLN_MP_DCALL_V_XS(xs, ...) JLN_MP_DCALL_V(sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT, __VA_ARGS__)
#define JLN_MP_DCALLF_XS(xs, ...) JLN_MP_DCALLF(sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT, __VA_ARGS__)
#define JLN_MP_DCALLF_C_XS(xs, ...) JLN_MP_DCALLF_C(sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT, __VA_ARGS__)


#if JLN_MP_MSVC || JLN_MP_ENABLE_DEBUG || defined(JLN_MP_DOXYGENATING)

#ifdef JLN_MP_DOXYGENATING
  template<class C, class... xs>
  using call = C::f<xs...>;
  #define JLN_MP_DCALL(cond, ...) call<__VA_ARGS__>
  #define JLN_MP_DCALL_V(cond, ...) call<__VA_ARGS__>::value
  #define JLN_MP_DCALLF(cond, F, ...) F<__VA_ARGS__>
  #define JLN_MP_DCALL_C(cond, F, ...) F<__VA_ARGS__>
  #define JLN_MP_DCALLF_C(cond, F, ...) F<__VA_ARGS__>
#else
  template<class C, class... xs>
  using call = memoize_call<C, xs...>;
  #define JLN_MP_DCALL(cond, ...) typename detail::_memoizer<__VA_ARGS__>::type
  #define JLN_MP_DCALL_V(cond, ...) detail::_memoizer<__VA_ARGS__>::type::value
  #define JLN_MP_DCALLF(cond, ...) typename detail::dcallf<(cond)>::template f<__VA_ARGS__>
  #define JLN_MP_DCALL_C(cond, ...) typename detail::dcall_c<(cond)>::template f<__VA_ARGS__>
  #define JLN_MP_DCALLF_C(cond, ...) typename detail::dcallf_c<(cond)>::template f<__VA_ARGS__>
#endif

  template<class C, JLN_MP_TPL_AUTO_OR_INT... xs>
  using call_c = typename C::template f<xs...>;

#else
# define JLN_MP_DCALL(cond, C, ...) typename mp::conditional_c<(cond)>::template f<C,void>::template f<__VA_ARGS__>
# define JLN_MP_DCALL_R(cond, C, ...) mp::conditional_c<(cond)>::template f<C,void>::template f<__VA_ARGS__>
# define JLN_MP_DCALL_V(cond, C, ...) mp::conditional_c<(cond)>::template f<C,void>::template f<__VA_ARGS__>::value
# define JLN_MP_DCALLF(cond, ...) typename detail::dcallf<(cond)>::template f<__VA_ARGS__>
# define JLN_MP_DCALL_C(cond, ...) typename detail::dcall_c<(cond)>::template f<__VA_ARGS__>
# define JLN_MP_DCALLF_C(cond, ...) typename detail::dcallf_c<(cond)>::template f<__VA_ARGS__>

  template<class C, class... xs>
  using call = typename conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
    ::template f<C, to_many_argument_error>
    ::template f<xs...>;

  template<class C, JLN_MP_TPL_AUTO_OR_INT... xs>
  using call_c = typename detail::dcall_c<(sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT)>
    ::template f<C, xs...>;
#endif

  template<class C, class... xs>
  using call_t = typename call<C, xs...>::type;
}

/// \cond
namespace jln::mp::detail
{
  template<>
  struct dcall<true>
  {
      template<class C, class... xs>
      using f = typename C::template f<xs...>;
  };

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
