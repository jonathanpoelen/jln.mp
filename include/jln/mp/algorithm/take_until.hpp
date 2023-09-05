// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/take_while.hpp>
#include <jln/mp/algorithm/drop_until.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Extract the first elements of a \sequence that does not satisfy a \predicate.
  /// When an element satisfy the predicate,
  /// call \c TC with it and those before it.
  /// Otherwise \c FC is called on the whole sequence.
  /// \treturn \sequence
  /// \see take_front, take_back, take_until_xs
  /// \see drop_until, drop_until_xs
  /// \see search, partial_search
  template<class Pred, class TC = listify, class FC = TC>
  struct take_until
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  /// Extract the first plus at most \c ExtendedByN elements of a \sequence that does not satisfy a \predicate.
  /// When an element satisfy the predicate,
  /// call \c TC with it and those before it plus at most \c ExtendedByN.
  /// Otherwise \c FC is called on the whole sequence.
  /// \semantics
  ///   \code
  ///   call<take_until_extended_by_n_c<2, is<number<2>>>,
  ///     number<0>, number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   //  predicate not satisfied ^ (+1)   ^ +2
  ///   ==
  ///   list<number<0>, number<1>, number<2>, number<3>>
  ///
  ///   call<take_until_extended_by_n_c<2, is<number<5>>>,
  ///     number<0>, number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   //                                   predicate not satisfied ^ (+1)
  ///   ==
  ///   list<number<0>, number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   \endcode
  /// \treturn \sequence
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  struct take_until_extended_by_n_c
  {
    template<class... xs>
    using f = typename detail::take_while_extended_by_n_impl<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<ExtendedByN, TC, FC, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using take_until_extended_by_n = take_until_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_inclusive_until = take_until_extended_by_n_c<1, Pred, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_until = unpack<L, mp::take_until<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_inclusive_until = unpack<L, mp::take_until_extended_by_n_c<1, Pred, TC, FC>>;

    template<class ExtendedByN, class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_until_extended_by_n
      = unpack<L, mp::take_until_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>>;

    template<std::size_t ExtendedByN,
             class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using take_until_extended_by_n_c
      = unpack<L, mp::take_until_extended_by_n_c<ExtendedByN, Pred, TC, FC>>;
  }
}
