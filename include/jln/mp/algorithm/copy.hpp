#pragma once

#include "remove.hpp"
#include "../number/operators.hpp"

namespace jln::mp
{
  template<class Pred, class C = listify>
  using copy_if = remove_if<fork<Pred, not_<>>, C>;

  template<class x, class C = listify>
  using copy = remove_if<same_as<x, not_<>>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using copy_if = eager<L, mp::copy_if<Pred, C>>;

    template<class L, class x, class C = mp::listify>
    using copy = eager<L, mp::copy<x, C>>;
  }
}
