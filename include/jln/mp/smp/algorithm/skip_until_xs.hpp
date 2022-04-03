#pragma once

#include <jln/mp/smp/algorithm/drop_until_xs.hpp>
#include <jln/mp/algorithm/skip_until_xs.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = TC>
  using skip_until_xs = drop_until_xs<Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_until_xs_c = partial_drop_until_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_until_xs = drop_inclusive_until_xs<Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_inclusive_until_xs_c
    = partial_drop_inclusive_until_xs_c<OffsetEnd, Pred, TC, clear<FC>>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(partial_skip_until_xs,
  (OffsetEnd), (Pred), (TC, smp::listify), (FC, TC),
  smp::partial_skip_until_xs_c<OffsetEnd::value, Pred, FC, TC>)

JLN_MP_MAKE_REGULAR_SMP4_P(partial_skip_inclusive_until_xs,
  (OffsetEnd), (Pred), (TC, smp::listify), (FC, TC),
  smp::partial_skip_inclusive_until_xs_c<OffsetEnd::value, Pred, FC, TC>)
