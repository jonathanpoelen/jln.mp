// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/drop_until_xs.hpp>
#include <jln/mp/algorithm/take_until_xs.hpp>
#include <jln/mp/detail/expr_conversion.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Search the first sub-\sequence that satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// Calls \c TC with all the elements from sub-\sequence found at the end.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search_before, partial_search, after, index_if
  /// \see search_before_extended_by_n
  /// \see partial_search_before, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using search = drop_until_xs<Pred, TC, FC>;

  /// Search elements before sub-\sequence that satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// Calls \c TC with the elements from the beginning to sub-\sequence found.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search, partial_search, after, index_if
  /// \see search_before_extended_by_n
  /// \see partial_search_before, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using search_before = take_until_xs<Pred, TC, FC>;

  /// Search elements before sub-\sequence that satisfy a \predicate.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// Calls \c TC with the elements from the beginning to sub-\sequence found + \c ExtendedByN.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search, search_before, partial_search, after, index_if
  /// \see partial_search_before, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using search_before_extended_by_n = take_until_extended_by_n_xs<ExtendedByN, Pred, TC, FC>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using search_before_extended_by_n_c = take_until_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>;

  /// Same \c search, but it stops when there is StopWhenAtLeast::value element or less.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// \treturn \sequence
  /// \see search, search_before, after, index_if
  /// \see search_before_extended_by_n
  /// \see partial_search_before, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<class StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search = partial_drop_until_xs_c<
    -JLN_MP_INTEGRAL_AS(int_t, StopWhenAtLeast::value)-1, Pred, TC, FC>;

  template<std::size_t StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_c = partial_drop_until_xs_c<
    -JLN_MP_INTEGRAL_AS(int_t, StopWhenAtLeast)-1, Pred, TC, FC>;

  /// Same \c search_before, but it stops when there is StopWhenAtLeast::value element or less.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// \treturn \sequence
  /// \see search, search_before, partial_search, after, index_if
  /// \see search_before_extended_by_n, partial_search_before_extended_by_n
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<class StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_before = partial_take_until_xs_c<
    -JLN_MP_INTEGRAL_AS(int_t, StopWhenAtLeast::value)-1, Pred, TC, FC>;

  template<std::size_t StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_before_c = partial_take_until_xs_c<
    -JLN_MP_INTEGRAL_AS(int_t, StopWhenAtLeast)-1, Pred, TC, FC>;

  /// Same \c search_before, but it stops when there is StopWhenAtLeast::value element or less.
  /// \pre \c Pred::f<ys...> must return a boolean, 1 or 0
  /// \treturn \sequence
  /// \see search, search_before, partial_search, after, index_if
  /// \see search_before_extended_by_n, partial_search_before
  /// \see drop_while, drop_while_xs, take_while, take_while_xs
  template<std::size_t StopWhenAtLeast, std::size_t ExtendedByN, class Pred,
           class TC = listify, class FC = clear<TC>>
  using partial_search_before_extended_by_n_c = partial_take_until_extended_by_n_xs_c<
    -JLN_MP_INTEGRAL_AS(int_t, StopWhenAtLeast)-1, ExtendedByN, Pred, TC, FC>;

  template<class StopWhenAtLeast, class ExtendedByN, class Pred,
           class TC = listify, class FC = clear<TC>>
  using partial_search_before_extended_by_n = partial_take_until_extended_by_n_xs_c<
    -JLN_MP_INTEGRAL_AS(int_t, StopWhenAtLeast::value)-1, ExtendedByN::value, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using search = typename detail::_unpack<mp::search<Pred, TC, FC>, L>::type;

    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using search_before = typename detail::_unpack<mp::search_before<Pred, TC, FC>, L>::type;

    template<class L, class ExtendedByN, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using search_before_extended_by_n = typename detail::_unpack<
      mp::search_before_extended_by_n<ExtendedByN, Pred, TC, FC>, L>::type;


    template<class L, class StopWhenAtLeast, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search = typename detail::_unpack<mp::partial_search<Pred, StopWhenAtLeast, TC, FC>, L>::type;

    template<class L, class StopWhenAtLeast, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_before = typename detail::_unpack<
      mp::partial_search_before<Pred, StopWhenAtLeast, TC, FC>, L>::type;

    template<class L, class StopWhenAtLeast, class ExtendedByN, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_before_extended_by_n = typename detail::_unpack<
      mp::partial_search_before_extended_by_n<StopWhenAtLeast, ExtendedByN, Pred, TC, FC>, L>::type;


    template<class L, std::size_t StopWhenAtLeast, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_c = typename detail::_unpack<mp::partial_search_c<StopWhenAtLeast, Pred, TC, FC>, L>::type;

    template<class L, std::size_t StopWhenAtLeast, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_before_c = typename detail::_unpack<
      mp::partial_search_before_c<StopWhenAtLeast, Pred, TC, FC>, L>::type;

    template<class L, std::size_t StopWhenAtLeast, std::size_t ExtendedByN, class Pred,
      class TC = mp::listify, class FC = mp::clear<TC>>
    using partial_search_before_extended_by_n_c = typename detail::_unpack<
      mp::partial_search_before_extended_by_n_c<StopWhenAtLeast, ExtendedByN, Pred, TC, FC>, L>::type;
  }
}
