#pragma once

#include <jln/mp/smp/algorithm/drop_until.hpp>
#include <jln/mp/algorithm/skip_until.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using skip_until = drop_until<Pred, C, clear<C>>;

  template<class Pred, class C = listify>
  using skip_inclusive_until = drop_inclusive_until<Pred, C, clear<C>>;
}
