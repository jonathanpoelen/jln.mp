// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/drop_until_xs.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Remove the first elements of a \sequence that does not satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// \treturn \sequence
  /// \see skip_until, partial_skip_until_xs, skip_inclusive_until_xs
  /// \see take_until_xs, take_while_xs
  /// \see drop_until_xs, drop_while_xs
  template<class Pred, class TC = listify, class FC = TC>
  using skip_until_xs = drop_until_xs<Pred, TC, clear<FC>>;

  /// Same as \c drop_until_xs, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see skip_until, skip_until_xs, skip_inclusive_until_xs
  /// \see take_until_xs, take_while_xs
  /// \see drop_until_xs, drop_while_xs
  template<int_t OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_until_xs_c = partial_drop_until_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_until_xs = partial_drop_until_xs<OffsetEnd, Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_until_xs = drop_inclusive_until_xs<Pred, TC, clear<FC>>;

  template<int_t OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_inclusive_until_xs_c
    = partial_drop_inclusive_until_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_inclusive_until_xs
    = partial_drop_inclusive_until_xs<OffsetEnd, Pred, TC, clear<FC>>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_until_extended_by_n_xs_c
    = drop_until_extended_by_n_xs_c<ExtendedByN, Pred, TC, clear<FC>>;

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_until_extended_by_n_xs
    = drop_until_extended_by_n_xs<ExtendedByN, Pred, TC, clear<FC>>;

  template<int_t OffsetEnd, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_skip_until_extended_by_n_xs_c
    = partial_drop_until_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_skip_until_extended_by_n_xs
    = partial_drop_until_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_until_xs = typename detail::_unpack<mp::skip_until_xs<Pred, TC, FC>, L>::type;

    template<class L, class OffsetEnd, class state, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_until_xs = typename detail::_unpack<
      mp::partial_skip_until_xs<OffsetEnd, Pred, TC, FC>, L>::type;

    template<class L, int_t OffsetEnd, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_until_xs_c = typename detail::_unpack<
      mp::partial_skip_until_xs_c<OffsetEnd, Pred, TC, FC>, L>::type;

    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_inclusive_until_xs = typename detail::_unpack<
      mp::skip_inclusive_until_xs<Pred, TC, FC>, L>::type;

    template<class L, class OffsetEnd, class state, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_inclusive_until_xs = typename detail::_unpack<
      mp::partial_skip_inclusive_until_xs<OffsetEnd, Pred, TC, FC>, L>::type;

    template<class L, int_t OffsetEnd, class Pred, class TC = mp::listify, class FC = TC>
    using partial_skip_inclusive_until_xs_c = typename detail::_unpack<
      mp::partial_skip_inclusive_until_xs_c<OffsetEnd, Pred, TC, FC>, L>::type;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_until_extended_by_n_xs_c = typename detail::_unpack<
      mp::drop_until_extended_by_n_xs_c<ExtendedByN, Pred, TC, clear<FC>>, L>::type;

    template<class L, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_until_extended_by_n_xs = typename detail::_unpack<
      mp::drop_until_extended_by_n_xs<ExtendedByN, Pred, TC, clear<FC>>, L>::type;

    template<class L, int_t OffsetEnd, std::size_t ExtendedByN,
             class Pred, class TC = listify, class FC = TC>
    using partial_skip_until_extended_by_n_xs_c = typename detail::_unpack<
      mp::partial_drop_until_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>, L>::type;

    template<class L, class OffsetEnd, class ExtendedByN,
             class Pred, class TC = listify, class FC = TC>
    using partial_skip_until_extended_by_n_xs = typename detail::_unpack<
      mp::partial_drop_until_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>, L>::type;
  }
}
