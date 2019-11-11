#pragma once

#include "../config/debug.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<bool>
    struct dcall;

    template<>
    struct dcall<true>
    {
        template<class C, typename...xs>
        using f = typename C::template f<xs...>;
    };
  }

  namespace detail
  {
    template<class F, class... xs>
    struct _memoizer
    {
      using type = typename F::template f<xs...>;
    };
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
#else
  template<class C, class... xs>
  using call = typename detail::dcall<(sizeof...(xs) < 1000000)>
    ::template f<C, xs...>;

  namespace detail
  {
    template<template<class...> class f, class C, class F, class... xs>
    using _dispatch = f<C, f<F, xs>...>;
  }

  template<class C, class F, class... xs>
  using dispatch = detail::_dispatch<
    detail::dcall<(sizeof...(xs) < 1000000)>::template f,
    C, F, xs...>;
#endif
}
