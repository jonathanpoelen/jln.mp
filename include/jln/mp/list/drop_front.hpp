#pragma once

#include "../list/list.hpp"
#include "../number/number.hpp"

namespace jln::mp
{
  // TODO drop_front
  template<class N, class C = listify>
  struct drop_front;

  template<class C>
  struct drop_front<number<1>, C>
  {
    template<class x0, class... xs>
    using f = typename C::template f<x0>;
  };

  template<class C>
  struct drop_front<number<2>, C>
  {
    template<class x0, class x1, class... xs>
    using f = typename C::template f<x1>;
  };

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using drop_front = eager<L, drop_front<N, C>>;
  }
}
