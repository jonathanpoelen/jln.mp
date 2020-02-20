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

  // TODO polybind<Fs..., C>
  // polybind<f1, f2, f3, g>::f<a, b, c, d, e> = g<f1<a>, f2<b>, f3<c>, d, e>
} // namespace jln::mp
