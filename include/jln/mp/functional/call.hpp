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
#else
  template<class C, class... xs>
  using call = typename detail::dcall<(sizeof...(xs) < 1000000)>
    ::template f<C, xs...>;
#endif
}
