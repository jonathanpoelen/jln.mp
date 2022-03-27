#pragma once

#include <jln/mp/algorithm/index.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/functional/not_fn.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a predicate holds for all elements of a \sequence.
  /// \treturn \bool
  template<class Pred, class C = identity>
  using all_of = index_if<not_fn<Pred>, always<false_, C>, always<true_, C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using all_of = unpack<L, mp::all_of<Pred, C>>;
  }
} // namespace jln::mp
