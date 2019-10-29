#pragma once

#include "../list/list.hpp"
#include "call.hpp"

namespace jln::mp
{
  template<class C = listify>
  struct flip
  {
    template<class x0, class x1, class... xs>
    using f = call<C, x1, x0, xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using flip = eager<L, C>;
  }
}
