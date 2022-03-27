#pragma once

#include <jln/mp/smp/algorithm/drop_until_xs.hpp>
#include <jln/mp/algorithm/skip_until_xs.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using skip_until_xs = drop_until_xs<Pred, C, clear<C>>;

  template<int_ OffsetEnd, class Pred, class C = listify>
  using partial_skip_until_xs_c = partial_drop_until_xs_c<OffsetEnd, Pred, C, clear<C>>;

  template<class Pred, class C = listify>
  using skip_inclusive_until_xs = drop_inclusive_until_xs<Pred, C, clear<C>>;

  template<int_ OffsetEnd, class Pred, class C = listify>
  using partial_skip_inclusive_until_xs_c
    = partial_drop_inclusive_until_xs_c<OffsetEnd, Pred, C, clear<C>>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(partial_skip_until_xs,
  (OffsetEnd), (Pred), (C, smp::listify),
  smp::partial_skip_until_xs_c<OffsetEnd::value, Pred, C>)

JLN_MP_MAKE_REGULAR_SMP3_P(partial_skip_inclusive_until_xs,
  (OffsetEnd), (Pred), (C, smp::listify),
  smp::partial_skip_inclusive_until_xs_c<OffsetEnd::value, Pred, C>)
