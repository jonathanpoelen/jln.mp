#pragma once

#include <jln/mp/smp/algorithm/drop_while.hpp>
#include <jln/mp/algorithm/skip_while.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = TC>
  using skip_while = drop_while<Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_while = drop_inclusive_while<Pred, TC, clear<FC>>;
}
