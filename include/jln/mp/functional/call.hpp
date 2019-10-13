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
        template<class continuation, typename...xs>
        using f = typename continuation::template f<xs...>;
    };
  }

#if jln_MP_ENABLE_DEBUG
  namespace detail
  {
    template<class continuation, class... xs>
    struct _call
    {
      using type = typename dcall<(sizeof...(xs) < 1000000)>::template f<continuation, xs...>;
    };
  }
  template<class continuation, class... xs>
  using call = typename detail::_call<continuation, xs...>::type;
#else
  template<class continuation, class... xs>
  using call = typename dcall<(sizeof...(xs) < 1000000)>::template f<continuation, xs...>;
#endif
}
