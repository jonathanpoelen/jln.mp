#pragma once

#include "transform.hpp"
#include "../utility/always.hpp"
#include "../utility/same_as.hpp"
#include "../number/operators.hpp"
#include "../number/to_bool.hpp"

namespace jln::mp
{
  template<class Pred, class C = identity>
  using count_if = transform<fork<Pred, mp::to_bool<>>, add0<C>>;

  template<class x, class C = identity>
  using count = transform<same_as<x>, add0<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using count_if = eager<L, mp::count_if<Pred, C>>;

    template<class L, class x, class C = mp::identity>
    using count = eager<L, mp::count<x, C>>;
  }
}
