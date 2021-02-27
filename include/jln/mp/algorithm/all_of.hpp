#pragma once

#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/number/operators.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a predicate holds for all elements of a \sequence.
  /// \treturn \bool
  template<class Pred, class C = identity>
  using all_of = transform<Pred, and_<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using all_of = unpack<L, mp::all_of<Pred, C>>;
  }
} // namespace jln::mp
