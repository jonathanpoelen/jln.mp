#pragma once

#include "../config/debug.hpp"

namespace jln::mp
{
#if jln_MP_ENABLE_DEBUG
  namespace detail
  {
    template<class continuation, class... xs>
    struct _call
    {
      using type = typename continuation::template f<xs...>;
    };
  }
  template<class continuation, class... xs>
  using call = typename detail::_call<continuation, xs...>::type;
#else
  template<class continuation, class... xs>
  using call = typename continuation::template f<xs...>;
#endif
}
