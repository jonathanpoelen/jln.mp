#pragma once

#include <jln/mp/smp/algorithm/drop_until.hpp>
#include <jln/mp/algorithm/skip_until.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = TC>
  using skip_until = drop_until<Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_until = drop_inclusive_until<Pred, TC, clear<FC>>;
}
