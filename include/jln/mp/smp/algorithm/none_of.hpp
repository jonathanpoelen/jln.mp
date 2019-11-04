#pragma once

#include "any_of.hpp"
#include "../../algorithm/none_of.hpp"

namespace jln::mp
{
  namespace smp
  {
    template<class Pred, class C = identity>
    using none_of = any_of<Pred, not_<C>>;
  }
} // namespace jln::mp
