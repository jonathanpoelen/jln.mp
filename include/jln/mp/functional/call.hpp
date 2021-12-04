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

#ifdef JLN_MP_DOXYGENATING

template<class C, class... xs>
using call = C::f<xs...>;

#define JLN_MP_DCALL_TRACE_XS(xs, ...) call<__VA_ARGS__>
#define JLN_MP_DCALL_V_TRACE_XS(xs, ...) call<__VA_ARGS__>::value
#define JLN_MP_DCALLF_XS(xs, F, ...) F<__VA_ARGS__>
#define JLN_MP_DCALLF_C_XS(xs, F, ...) F<__VA_ARGS__>

#else

#define JLN_MP_DCALLF_XS(xs, C, ...)                               \
  typename detail::dcallf<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT> \
    ::template f<C, __VA_ARGS__>

#define JLN_MP_DCALLF_C_XS(xs, C, ...)                               \
  typename detail::dcallf_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT> \
    ::template f<C, __VA_ARGS__>

# if JLN_MP_MSVC

template<class C, class... xs>
using call = memoize_call<C, xs...>;

#  define JLN_MP_DCALL_TRACE_XS(xs, C, ...) \
    typename ::jln::detail::_memoizer<C, __VA_ARGS__>::type

#  define JLN_MP_DCALL_V_TRACE_XS(xs, C, ...) \
    ::jln::detail::_memoizer<C, __VA_ARGS__>::type::value

# else

template<class C, class... xs>
using call = typename conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
  ::template f<C, detail::too_many_arguments_error>
  ::template f<xs...>;

#  define JLN_MP_DCALL_TRACE_XS(xs, C, ...)                                        \
    typename ::jln::mp::conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>     \
      ::template f<JLN_MP_TRACE_F(C), ::jln::mp::detail::too_many_arguments_error> \
      ::template f<__VA_ARGS__>

#  define JLN_MP_DCALL_V_TRACE_XS(xs, C, ...)                                      \
    ::jln::mp::conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>              \
      ::template f<JLN_MP_TRACE_F(C), ::jln::mp::detail::too_many_arguments_error> \
      ::template f<__VA_ARGS__>                                                    \
      ::value

# endif
#endif


#if JLN_MP_MSVC
# define JLN_MP_MSVC_FIX_CALL(C, ...) ::jln::mp::detail::raw_call<C, __VA_ARGS__>
#else
# define JLN_MP_MSVC_FIX_CALL(C, ...) typename JLN_MP_IDENT C::template f<__VA_ARGS__>
#endif


template<class C, JLN_MP_TPL_AUTO_OR_INT... xs>
using call_c = typename detail::dcall_c<(sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT)>
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
