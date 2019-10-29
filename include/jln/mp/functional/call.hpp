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

  // TODO invoke -> try_invoke
  // TODO call -> invoke

#if jln_MP_ENABLE_DEBUG
  namespace detail
  {
    template<class C, class... xs>
    struct _call
    {
      using type = typename dcall<(sizeof...(xs) < 1000000)>::template f<C, xs...>;
    };
  }
  template<class C, class... xs>
  using call = typename detail::_call<C, xs...>::type;
#else
  template<class C, class... xs>
  using call = typename dcall<(sizeof...(xs) < 1000000)>::template f<C, xs...>;
#endif
}
