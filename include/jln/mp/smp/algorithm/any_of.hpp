#pragma once

#include "transform.hpp"
#include "../number/operators.hpp"
#include "../../algorithm/any_of.hpp"

namespace jln::mp
{
  namespace smp
  {
    template<class Pred, class C = identity>
    using any_of = transform<Pred, or_<C>>;
  }
} // namespace jln::mp
