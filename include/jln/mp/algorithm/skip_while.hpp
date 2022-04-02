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
  template<class Pred, class C = listify>
  using skip_while = drop_while<Pred, C, clear<C>>;

  template<class Pred, class C = listify>
  using skip_inclusive_while = drop_inclusive_while<Pred, C, clear<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using skip_while = unpack<L, mp::skip_while<Pred, C>>;

    template<class L, class Pred, class C = mp::listify>
    using skip_inclusive_while = unpack<L, mp::skip_inclusive_while<Pred, C>>;
  }
}