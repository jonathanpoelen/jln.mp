#pragma once

#include <jln/mp/smp/algorithm/transform.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/algorithm/any_of.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using any_of = transform<Pred, or_<C>>;
}
