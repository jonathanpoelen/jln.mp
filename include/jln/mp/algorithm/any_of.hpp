#pragma once

#include <jln/mp/algorithm/index.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/functional/not_fn.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a predicate holds for at least some element of a \sequence.
  /// \treturn \bool
  template<class Pred, class C = identity>
  using any_of = index_if<not_fn<not_fn<Pred>>, always<true_, C>, always<false_, C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using any_of = unpack<L, mp::any_of<Pred, C>>;
  }
} // namespace jln::mp
