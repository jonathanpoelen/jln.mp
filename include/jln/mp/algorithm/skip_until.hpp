// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/drop_until.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Remove the first elements of a \sequence that does not satisfy a \predicate.
  /// \pre \c Pred::f<x> must return a boolean, 1 or 0
  /// \treturn \sequence
  /// \see skip_while, skip_until_xs
  /// \see drop_while, drop_until
  /// \see take_while, take_until
  template<class Pred, class TC = listify, class FC = TC>
  using skip_until = drop_until<Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_until = drop_inclusive_until<Pred, TC, clear<FC>>;

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_until_extended_by_n = drop_until_extended_by_n_c<
    ExtendedByN::value, Pred, TC, clear<FC>>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_until_extended_by_n_c = drop_until_extended_by_n_c<
    ExtendedByN, Pred, TC, clear<FC>>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_until = typename detail::_unpack<mp::skip_until<Pred, TC, FC>, L>::type;

    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_inclusive_until = typename detail::_unpack<mp::skip_inclusive_until<Pred, TC, FC>, L>::type;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_until_extended_by_n_c = typename detail::_unpack<
      mp::skip_until_extended_by_n_c<ExtendedByN, Pred, TC, FC>, L>::type;

    template<class L, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_until_extended_by_n = typename detail::_unpack<
      mp::skip_until_extended_by_n<ExtendedByN, Pred, TC, FC>, L>::type;
  }
}
