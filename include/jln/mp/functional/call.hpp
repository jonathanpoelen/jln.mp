#pragma once

#include "../config/debug.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<bool> struct dcall;
    template<bool> struct dcallf;
    template<bool> struct dcall_c;
    template<bool> struct dcall_v;
#if __cplusplus >= 201703L
    template<bool> struct dcallf_c;
    template<bool> struct dcallf_tc;
#endif

    template<class F, class... xs>
    struct _memoizer;
  }

  template<class C, class... xs>
  using memoize_call = typename detail::_memoizer<C, xs...>::type;

#if JLN_MP_ENABLE_DEBUG
  template<class C, class... xs>
  using call = typename detail::_memoizer<C, xs...>::type;

  template<class C, class F, class... xs>
  using dispatch = typename detail::_memoizer<C,
    typename detail::_memoizer<F, xs>::type...
  >::type;

  template<class F, class C, class... xs>
  using indirect_call = typename detail::_memoizer<
    typename detail::_memoizer<F, xs...>::type,
    C, xs...
  >::type;

  template<class C, class F, class... xs>
  using unary_compose_call = typename detail::_memoizer<C,
    typename detail::_memoizer<F, xs...>::type
  >::type;

  template<class C, class F0, class F1, class... xs>
  using binary_compose_call = typename detail::_memoizer<C,
    typename detail::_memoizer<F0, xs...>::type,
    typename detail::_memoizer<F1, xs...>::type
  >::type;

  template<class C, class F0, class F1, class F2, class... xs>
  using ternary_compose_call = typename detail::_memoizer<C,
    typename detail::_memoizer<F0, xs...>::type,
    typename detail::_memoizer<F1, xs...>::type,
    typename detail::_memoizer<F2, xs...>::type
  >::type;
#else
  template<class C, class... xs>
  using call = typename detail::dcall<(sizeof...(xs) < 1000000)>
    ::template f<C, xs...>;

  template<class C, class... xs>
  using call_v = typename detail::dcall_v<(sizeof...(xs) < 1000000)>
    ::template f<C, xs...>;

  namespace detail
  {
    template<template<class...> class f, class C, class F, class... xs>
    using _indirect_call = f<f<F, xs...>, C, xs...>;
  }

  template<class F, class C, class... xs>
  using indirect_call = detail::_indirect_call<
    detail::dcall<(sizeof...(xs) < 1000000)>::template f,
    C, F, xs...>;

  namespace detail
  {
    template<template<class...> class f, class C, class F, class... xs>
    using _dispatch = f<C, f<F, xs>...>;
  }

  template<class C, class F, class... xs>
  using dispatch = detail::_dispatch<
    detail::dcall<(sizeof...(xs) < 1000000)>::template f,
    C, F, xs...>;

  namespace detail
  {
    template<template<class...> class f, class C, class F, class... xs>
    using _unary_compose_call = f<C, f<F, xs...>>;
  }

  template<class C, class F, class... xs>
  using unary_compose_call = detail::_unary_compose_call<
    detail::dcall<(sizeof...(xs) < 1000000)>::template f,
    C, F, xs...>;

  namespace detail
  {
    template<template<class...> class f, class C, class F0, class F1, class... xs>
    using _binary_compose_call = f<C, f<F0, xs...>, f<F1, xs...>>;
  }

  template<class C, class F0, class F1, class... xs>
  using binary_compose_call = detail::_binary_compose_call<
    detail::dcall<(sizeof...(xs) < 1000000)>::template f,
    C, F0, F1, xs...>;

  namespace detail
  {
    template<template<class...> class f, class C, class F0, class F1, class F2, class... xs>
    using _ternary_compose_call = f<C, f<F0, xs...>, f<F1, xs...>, f<F2, xs...>>;
  }

  template<class C, class F0, class F1, class F2, class... xs>
  using ternary_compose_call = detail::_ternary_compose_call<
    detail::dcall<(sizeof...(xs) < 1000000)>::template f,
    C, F0, F1, F2, xs...>;
#endif
}

namespace jln::mp::detail
{
  template<class F, class... xs>
  struct _memoizer
  {
    using type = typename F::template f<xs...>;
  };

  template<>
  struct dcall<true>
  {
      template<class C, typename...xs>
      using f = typename C::template f<xs...>;
  };

  template<>
  struct dcall_v<true>
  {
      template<class C, class...xs>
      using f = typename C::template f<xs::value...>;
  };

  template<>
  struct dcall_c<true>
  {
      template<class C, auto...xs>
      using f = typename C::template f<xs...>;
  };

  template<>
  struct dcallf<true>
  {
    template<template<class...> class F, class...xs>
    using f = F<xs...>;
  };

#if __cplusplus >= 201703L
  template<>
  struct dcallf_c<true>
  {
    template<template<auto...> class F, auto...vs>
    using f = F<vs...>;
  };

  template<>
  struct dcallf_tc<true>
  {
    template<template<class, auto...> class F, class x, auto...vs>
    using f = F<x, vs...>;
  };
#endif
}
