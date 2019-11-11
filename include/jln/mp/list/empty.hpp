#pragma once

#include "size.hpp"
#include "../number/operators.hpp"

namespace jln::mp
{
  template<class C = identity>
  using empty = size<not_<C>>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using empty = eager<L, mp::empty<C>>;
  }
}
