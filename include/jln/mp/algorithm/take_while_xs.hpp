// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/drop_while_xs.hpp>
#include <jln/mp/algorithm/take_while.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Extracts the first elements of a \sequence that satisfy a \predicate.
  /// \treturn \sequence
  /// \see take_front, take_back, take_while, partial_take_while_xs
  /// \see drop_while, drop_while_xs
  /// \see search
  template<class Pred, class TC = listify, class FC = TC>
  struct take_while_xs
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::_drop_while_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  /// Same as \c take_while_extended_by_n_c, but for \c take_while_xs.
  /// \treturn \sequence
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  struct take_while_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::take_while_extended_by_n_impl<
      typename detail::_drop_while_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using take_while_extended_by_n_xs = take_while_extended_by_n_xs_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_inclusive_while_xs = take_while_extended_by_n_xs_c<1, Pred, TC, FC>;

  /// Same as \c take_while_extended_by_n_xs_c, but stop searching at position \c OffsetEnd.
  /// \tparam OffsetEnd  a negative value start to end of sequence.
  /// \treturn \sequence
  /// \see drop_front, drop_back, drop_while, drop_while_xs
  /// \see take_while, take_while_xs
  /// \see search, partial_search
  template<int_ OffsetEnd, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  struct partial_take_while_extended_by_n_xs_c
  {
    template<class... xs>
    using f = typename detail::take_while_extended_by_n_impl<
      typename detail::drop_while_xs_call<
        detail::partial_drop_while_xs_size(OffsetEnd, sizeof...(xs)),
        JLN_MP_TRACE_F(Pred), xs...
      >
    >::template f<ExtendedByN, TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_while_xs =
    partial_take_while_extended_by_n_xs_c<OffsetEnd::value, 0, Pred, TC, FC>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_while_xs_c =
    partial_take_while_extended_by_n_xs_c<OffsetEnd, 0, Pred, TC, FC>;

  template<class OffsetEnd, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_take_while_extended_by_n_xs =
    partial_take_while_extended_by_n_xs_c<OffsetEnd::value, ExtendedByN::value, Pred, TC, FC>;

  template<std::size_t OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_inclusive_while_xs_c =
    partial_take_while_extended_by_n_xs_c<OffsetEnd, 1, Pred, TC, FC>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_inclusive_while_xs =
    partial_take_while_extended_by_n_xs_c<OffsetEnd::value, 1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using take_while_xs = unpack<L, mp::take_while_xs<Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred, class TC = mp::listify, class FC = TC>
    using take_while_extended_by_n_xs = unpack<L,
      mp::take_while_extended_by_n_xs<ExtendedByN, Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = mp::listify, class FC = TC>
    using take_while_extended_by_n_xs_c = unpack<L,
      mp::take_while_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred, class TC = mp::listify, class FC = TC>
    using partial_take_while_xs = unpack<L,
      mp::partial_take_while_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred, class TC = mp::listify, class FC = TC>
    using partial_take_while_xs_c = unpack<L,
      mp::partial_take_while_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using take_inclusive_while_xs = unpack<L, mp::take_inclusive_while_xs<Pred, TC, FC>>;

    template<class L, class OffsetEnd, class state, class Pred,
             class TC = mp::listify, class FC = TC>
    using partial_take_inclusive_while_xs = unpack<L,
      mp::partial_take_inclusive_while_xs<OffsetEnd, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, class Pred,
             class TC = mp::listify, class FC = TC>
    using partial_take_inclusive_while_xs_c = unpack<L,
      mp::partial_take_inclusive_while_xs_c<OffsetEnd, Pred, TC, FC>>;

    template<class L, class OffsetEnd, class ExtendedByN, class Pred,
             class TC = listify, class FC = TC>
    using partial_take_while_extended_by_n_xs = unpack<L,
      mp::partial_take_while_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, FC>>;

    template<class L, int_ OffsetEnd, std::size_t ExtendedByN, class Pred,
             class TC = listify, class FC = TC>
    using partial_take_while_extended_by_n_xs_c = unpack<L,
      mp::partial_take_while_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, FC>>;
  }
}
