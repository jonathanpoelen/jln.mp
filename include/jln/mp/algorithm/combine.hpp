#pragma once

#include "../config/enumerate.hpp"
#include "cartesian.hpp"
#include "repeat.hpp"

namespace jln::mp
{
  template<class C = listify>
  struct combine
  {
    template<class... xs>
    using f = typename repeat_c<sizeof...(xs), cartesian<C>>
      ::template f<list<xs...>>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using combine = eager<L, mp::combine<C>>;
  }
}
