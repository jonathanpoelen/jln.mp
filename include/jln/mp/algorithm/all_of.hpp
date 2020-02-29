#pragma once

#include "../algorithm/transform.hpp"
#include "../number/operators.hpp"

namespace jln::mp
{
  template<class Pred, class C = identity>
  using all_of = transform<Pred, and_<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using all_of = unpack<L, mp::all_of<Pred, C>>;
  }
} // namespace jln::mp
