#pragma once

#include <jln/mp/algorithm/drop_while_xs.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Remove the first elements of a \sequence that satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// Same as \c skip_while, but the \predicate takes all the elements of
  /// the current position until the end of the list.
  /// \treturn \sequence
  /// \see skip_while, partial_skip_while_xs, skip_inclusive_while_xs
  /// \see take_while_xs, take_until_xs
  /// \see drop_while_xs, drop_until_xs
  template<class Pred, class TC = listify, class FC = TC>
  using skip_while_xs = drop_while_xs<Pred, TC, clear<FC>>;

  /// Same as \c skip_while_xs, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see skip_while, skip_while_xs, skip_inclusive_while_xs
  /// \see take_while_xs, take_until_xs
  /// \see drop_while_xs, drop_until_xs
  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_while_xs_c = partial_drop_while_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_while_xs = partial_drop_while_xs<OffsetEnd, Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_while_xs = drop_inclusive_while_xs<Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_inclusive_while_xs_c
    = partial_drop_inclusive_while_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_inclusive_while_xs
    = partial_drop_inclusive_while_xs<OffsetEnd, Pred, TC, clear<FC>>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_while_extended_by_n_xs_c
    = drop_while_extended_by_n_xs_c<ExtendedByN, Pred, TC, clear<FC>>;

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_while_extended_by_n_xs
    = drop_while_extended_by_n_xs<ExtendedByN, Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_skip_while_extended_by_n_xs_c
    = partial_drop_while_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_skip_while_extended_by_n_xs
    = partial_drop_while_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_while_xs = unpack<L, mp::skip_while_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_while_xs = unpack<L,
      mp::partial_skip_while_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_while_xs_c = unpack<L,
      mp::partial_skip_while_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_inclusive_while_xs = unpack<L, mp::skip_inclusive_while_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_inclusive_while_xs = unpack<L,
      mp::partial_skip_inclusive_while_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_inclusive_while_xs_c = unpack<L,
      mp::partial_skip_inclusive_while_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_while_extended_by_n_xs_c = unpack<L,
      mp::drop_while_extended_by_n_xs_c<ExtendedByN, Pred, TC, clear<FC>>>;

    template<class L, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_while_extended_by_n_xs = unpack<L,
      mp::drop_while_extended_by_n_xs<ExtendedByN, Pred, TC, clear<FC>>>;

    template<class L, int_ OffsetEnd, std::size_t ExtendedByN,
             class Pred, class TC = listify, class FC = TC>
    using partial_skip_while_extended_by_n_xs_c = unpack<L,
      mp::partial_drop_while_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>>;

    template<class L, class OffsetEnd, class ExtendedByN,
             class Pred, class TC = listify, class FC = TC>
    using partial_skip_while_extended_by_n_xs = unpack<L,
      mp::partial_drop_while_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>>;
  }
}
