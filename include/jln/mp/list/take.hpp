#pragma once

#include "../algorithm/rotate.hpp"
#include "drop.hpp"

namespace jln::mp
{
  template<class N, class C = listify>
  struct take
  {
    template<class... xs>
    using f = call<
      rotate<N, drop<number<sizeof...(xs) - N::value>, C>>,
      xs...>;
  };

  template<int_ n, class C = listify>
  using take_c = take<number<n>, C>;

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using take = eager<L, mp::take<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using take_c = eager<L, mp::take<number<n>, C>>;
  }
}

