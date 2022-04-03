#pragma once

#include <jln/mp/smp/algorithm/drop_until.hpp>
#include <jln/mp/algorithm/skip_until.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = TC>
  using skip_until = drop_until<Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_until = drop_inclusive_until<Pred, TC, clear<FC>>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_until_extended_by_n_c = skip_until<
    Pred, contract<mp::drop_front_max_c<ExtendedByN, subcontract<TC>>>, subcontract<clear<FC>>>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(skip_until_extended_by_n,
  (ExtendedByN), (Pred), (TC, smp::listify), (FC, TC),
  smp::skip_until_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>)
