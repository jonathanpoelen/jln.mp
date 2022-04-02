#pragma once

#include <jln/mp/algorithm/drop_while_xs.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Remove the first elements of a \sequence that satisfy a \predicate.
  /// Same as \c skip_while, but the \predicate takes all the elements of
  /// the current position until the end of the list.
  /// \treturn \sequence
  /// \see skip_while, partial_skip_while_xs, skip_inclusive_while_xs
  /// \see take_while_xs, take_until_xs
  /// \see drop_while_xs, drop_until_xs
  template<class Pred, class C = listify>
  using skip_while_xs = drop_while_xs<Pred, C, clear<C>>;

  /// Same as \c skip_while_xs, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see skip_while, skip_while_xs, skip_inclusive_while_xs
  /// \see take_while_xs, take_until_xs
  /// \see drop_while_xs, drop_until_xs
  template<int_ OffsetEnd, class Pred, class C = listify>
  using partial_skip_while_xs_c = partial_drop_while_xs_c<OffsetEnd, Pred, C, clear<C>>;

  template<class OffsetEnd, class Pred, class C = listify>
  using partial_skip_while_xs = partial_drop_while_xs<OffsetEnd, Pred, C, clear<C>>;

  template<class Pred, class C = listify>
  using skip_inclusive_while_xs = drop_inclusive_while_xs<Pred, C, clear<C>>;

  template<int_ OffsetEnd, class Pred, class C = listify>
  using partial_skip_inclusive_while_xs_c
    = partial_drop_inclusive_while_xs_c<OffsetEnd, Pred, C, clear<C>>;

  template<class OffsetEnd, class Pred, class C = listify>
  using partial_skip_inclusive_while_xs
    = partial_drop_inclusive_while_xs<OffsetEnd, Pred, C, clear<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using skip_while_xs = unpack<L, mp::skip_while_xs<Pred, C>>;

    template<class L, class OffsetEnd, class state, class Pred, class C = mp::listify>
    using partial_skip_while_xs = unpack<L,
      mp::partial_skip_while_xs<OffsetEnd, Pred, C>>;

    template<class L, int_ OffsetEnd, class Pred, class C = mp::listify>
    using partial_skip_while_xs_c = unpack<L,
      mp::partial_skip_while_xs_c<OffsetEnd, Pred, C>>;

    template<class L, class Pred, class C = mp::listify>
    using skip_inclusive_while_xs = unpack<L, mp::skip_inclusive_while_xs<Pred, C>>;

    template<class L, class OffsetEnd, class state, class Pred, class C = mp::listify>
    using partial_skip_inclusive_while_xs = unpack<L,
      mp::partial_skip_inclusive_while_xs<OffsetEnd, Pred, C>>;

    template<class L, int_ OffsetEnd, class Pred, class C = mp::listify>
    using partial_skip_inclusive_while_xs_c = unpack<L,
      mp::partial_skip_inclusive_while_xs_c<OffsetEnd, Pred, C>>;
  }
}