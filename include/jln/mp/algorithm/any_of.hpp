#pragma once

#include "../algorithm/transform.hpp"
#include "../number/operators.hpp"

namespace jln::mp
{
  template<class Pred, class C = identity>
  using any_of = transform<Pred, or_<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using any_of = eager<L, mp::any_of<Pred, C>>;
  }
} // namespace jln::mp
