#pragma once

#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/utility/is.hpp>
#include <jln/mp/number/operators.hpp>
#include <jln/mp/number/to_bool.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Counts all elements that satisfy a predicate.
  template<class Pred, class C = identity>
  using count_if = transform<Pred, add0<C>>;

  /// Counts all elements identical to a \value.
  template<class x, class C = identity>
  using count = transform<is<x>, add0<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using count_if = unpack<L, mp::count_if<Pred, C>>;

    template<class L, class x, class C = mp::identity>
    using count = unpack<L, mp::count<x, C>>;
  }
}
