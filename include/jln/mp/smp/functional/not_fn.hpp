#pragma once

#include <jln/mp/smp/functional/tee.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/functional/not_fn.hpp>

namespace jln::mp::smp
{
  template <class F, class C = identity>
  using not_fn = tee<F, not_<C>>;
}
