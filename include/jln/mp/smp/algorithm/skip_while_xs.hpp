#pragma once

#include <jln/mp/smp/algorithm/drop_while_xs.hpp>
#include <jln/mp/algorithm/skip_while_xs.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using skip_while_xs = drop_while_xs<Pred, C, clear<C>>;

  template<int_ OffsetEnd, class Pred, class C = listify>
  using partial_skip_while_xs_c = partial_drop_while_xs_c<OffsetEnd, Pred, C, clear<C>>;

  template<class Pred, class C = listify>
  using skip_inclusive_while_xs = drop_inclusive_while_xs<Pred, C, clear<C>>;

  template<int_ OffsetEnd, class Pred, class C = listify>
  using partial_skip_inclusive_while_xs_c
    = partial_drop_inclusive_while_xs_c<OffsetEnd, Pred, C, clear<C>>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(partial_skip_while_xs,
  (OffsetEnd), (Pred), (C, smp::listify),
  smp::partial_skip_while_xs_c<OffsetEnd::value, Pred, C>)

JLN_MP_MAKE_REGULAR_SMP3_P(partial_skip_inclusive_while_xs,
  (OffsetEnd), (Pred), (C, smp::listify),
  smp::partial_skip_inclusive_while_xs_c<OffsetEnd::value, Pred, C>)
