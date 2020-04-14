#pragma once

#include "call.hpp"

namespace jln::mp
{
  template<class F, class... xs>
  struct bind
  {
    template<class... ys>
    using f = call<F, xs..., ys...>;
  };

  template<class F, class... xs>
  struct reverse_bind
  {
    template<class... ys>
    using f = call<F, ys..., xs...>;
  };

  // fork_front<front<F, cfe<push_front, cfe<pop_front>>>, C>
  template<class F, class C>
  struct bind1st
  {
    template<class x, class... xs>
    using f = call<C, JLN_MP_DCALL(sizeof...(xs) < 100000, F, x), xs...>;
  };

  template<class F, class C>
  struct bind2nd
  {
    template<class x, class y, class... xs>
    using f = call<C, x, JLN_MP_DCALL(sizeof...(xs) < 100000, F, y), xs...>;
  };
} // namespace jln::mp
