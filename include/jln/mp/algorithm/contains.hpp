#pragma once

#include "any_of.hpp"
#include "../utility/same_as.hpp"

namespace jln::mp
{
  template<class x, class C = identity>
  using contains = any_of<same_as<x>, C>;
  // using contains = find<x, always<true_, C>, always<false_, C>>;

  namespace emp
  {
    template<class L, class x, class C = mp::identity>
    using contains = eager<L, mp::contains<x, C>>;
  }
}
