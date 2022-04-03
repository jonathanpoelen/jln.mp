#pragma once

#include <jln/mp/algorithm/drop_while.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Remove the first elements of a \sequence that satisfy a \predicate.
  /// \treturn \sequence
  /// \see skip_until, skip_while_xs
  /// \see drop_while, drop_until
  /// \see take_while, take_until
  template<class Pred, class TC = listify, class FC = TC>
  using skip_while = drop_while<Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_while = drop_inclusive_while<Pred, TC, clear<FC>>;

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_while_extended_by_n = drop_while_extended_by_n_c<
    ExtendedByN::value, Pred, TC, clear<FC>>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_while_extended_by_n_c = drop_while_extended_by_n_c<
    ExtendedByN, Pred, TC, clear<FC>>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_while = unpack<L, mp::skip_while<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = TC>
    using skip_inclusive_while = unpack<L, mp::skip_inclusive_while<Pred, TC, FC>>;

    template<class L, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_while_extended_by_n_c = unpack<L,
      mp::skip_while_extended_by_n_c<ExtendedByN, Pred, TC, FC>>;

    template<class L, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
    using skip_while_extended_by_n = unpack<L,
      mp::skip_while_extended_by_n<ExtendedByN, Pred, TC, FC>>;
  }
}
