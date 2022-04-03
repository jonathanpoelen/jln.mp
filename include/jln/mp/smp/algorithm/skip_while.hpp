#pragma once

#include <jln/mp/smp/algorithm/drop_while.hpp>
#include <jln/mp/algorithm/skip_while.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = TC>
  using skip_while = drop_while<Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_while = drop_inclusive_while<Pred, TC, clear<FC>>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_while_extended_by_n_c = skip_while<
    Pred, contract<mp::drop_front_max_c<ExtendedByN, subcontract<TC>>>, subcontract<clear<FC>>>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(skip_while_extended_by_n,
  (ExtendedByN), (Pred), (TC, smp::listify), (FC, TC),
  smp::skip_while_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>)
