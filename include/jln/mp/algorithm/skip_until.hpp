#pragma once

#include <jln/mp/algorithm/drop_until.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Remove the first elements of a \sequence that does not satisfy a \predicate.
  /// \treturn \sequence
  /// \see skip_while, skip_until_xs
  /// \see drop_while, drop_until
  /// \see take_while, take_until
  template<class Pred, class C = listify>
  using skip_until = drop_until<Pred, C, clear<C>>;

  template<class Pred, class C = listify>
  using skip_inclusive_until = drop_inclusive_until<Pred, C, clear<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using skip_until = unpack<L, mp::skip_until<Pred, C>>;

    template<class L, class Pred, class C = mp::listify>
    using skip_inclusive_until = unpack<L, mp::skip_inclusive_until<Pred, C>>;
  }
}
