#pragma once

#include "transform.hpp"
#include "../number/operators.hpp"
#include "../../algorithm/all_of.hpp"

namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using all_of = transform<Pred, and_<C>>;
}
