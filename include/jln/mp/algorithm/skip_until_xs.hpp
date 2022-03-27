#pragma once

#include <jln/mp/algorithm/drop_until_xs.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Remove the first elements of a \sequence that does not satisfy a \predicate.
  /// \treturn \sequence
  /// \see skip_until, partial_skip_until_xs, skip_inclusive_until_xs
  /// \see take_until_xs, take_while_xs
  /// \see drop_until_xs, drop_while_xs
  template<class Pred, class C = listify>
  using skip_until_xs = drop_until_xs<Pred, C, clear<C>>;

  /// Same as \c drop_until_xs, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see skip_until, skip_until_xs, skip_inclusive_until_xs
  /// \see take_until_xs, take_while_xs
  /// \see drop_until_xs, drop_while_xs
  template<int_ OffsetEnd, class Pred, class C = listify>
  using partial_skip_until_xs_c = partial_drop_until_xs_c<OffsetEnd, Pred, C, clear<C>>;

  template<class OffsetEnd, class Pred, class C = listify>
  using partial_skip_until_xs = partial_drop_until_xs<OffsetEnd, Pred, C, clear<C>>;

  template<class Pred, class C = listify>
  using skip_inclusive_until_xs = drop_inclusive_until_xs<Pred, C, clear<C>>;

  template<int_ OffsetEnd, class Pred, class C = listify>
  using partial_skip_inclusive_until_xs_c
    = partial_drop_inclusive_until_xs_c<OffsetEnd, Pred, C, clear<C>>;

  template<class OffsetEnd, class Pred, class C = listify>
  using partial_skip_inclusive_until_xs
    = partial_drop_inclusive_until_xs<OffsetEnd, Pred, C, clear<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using skip_until_xs = unpack<L, mp::skip_until_xs<Pred, C>>;

    template<class L, class OffsetEnd, class state, class Pred, class C = mp::listify>
    using partial_skip_until_xs = unpack<L,
      mp::partial_skip_until_xs<OffsetEnd, Pred, C>>;

    template<class L, int_ OffsetEnd, class Pred, class C = mp::listify>
    using partial_skip_until_xs_c = unpack<L,
      mp::partial_skip_until_xs_c<OffsetEnd, Pred, C>>;

    template<class L, class Pred, class C = mp::listify>
    using skip_inclusive_until_xs = unpack<L, mp::skip_inclusive_until_xs<Pred, C>>;

    template<class L, class OffsetEnd, class state, class Pred, class C = mp::listify>
    using partial_skip_inclusive_until_xs = unpack<L,
      mp::partial_skip_inclusive_until_xs<OffsetEnd, Pred, C>>;

    template<class L, int_ OffsetEnd, class Pred, class C = mp::listify>
    using partial_skip_inclusive_until_xs_c = unpack<L,
      mp::partial_skip_inclusive_until_xs_c<OffsetEnd, Pred, C>>;
  }
}
