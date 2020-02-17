#pragma once

#include "call.hpp"
#include "../list/front.hpp"

namespace jln::mp
{
  // fork_front<front<F, cfe<push_front, cfe<pop_front>>>, C>
  template<class F, class C>
  struct bind1st
  {
    template<class x, class... xs>
    using f = call<C,
      typename detail::dcall<sizeof...(xs) < 100000>::template f<F, x>, xs...>;
  };

  template<class F, class C>
  struct bind2nd
  {
    template<class x, class y, class... xs>
    using f = call<C, x,
      typename detail::dcall<sizeof...(xs) < 100000>::template f<F, y>, xs...>;
  };
} // namespace jln::mp
