#pragma once

#include <jln/mp/smp/algorithm/drop_while_xs.hpp>
#include <jln/mp/algorithm/skip_while_xs.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = TC>
  using skip_while_xs = drop_while_xs<Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_while_xs_c = partial_drop_while_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_while_xs = drop_inclusive_while_xs<Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_inclusive_while_xs_c
    = partial_drop_inclusive_while_xs_c<OffsetEnd, Pred, TC, clear<FC>>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(partial_skip_while_xs,
  (OffsetEnd), (Pred), (TC, smp::listify), (FC, TC),
  smp::partial_skip_while_xs_c<OffsetEnd::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP4_P(partial_skip_inclusive_while_xs,
  (OffsetEnd), (Pred), (TC, smp::listify), (FC, TC),
  smp::partial_skip_inclusive_while_xs_c<OffsetEnd::value, Pred, TC, FC>)
