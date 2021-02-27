#pragma once

#include <jln/mp/smp/algorithm/transform.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/algorithm/all_of.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using all_of = transform<Pred, and_<C>>;
}
