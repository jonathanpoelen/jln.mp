#pragma once

#include <jln/mp/algorithm/drop_while.hpp>
#include <jln/mp/list/is_empty.hpp>
#include <jln/mp/functional/not_fn.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a predicate holds for at least some element of a \sequence.
  /// \treturn \bool
  template<class Pred, class C = identity>
  using any_of = drop_while<not_fn<Pred>, is_empty<not_<C>>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using any_of = unpack<L, mp::any_of<Pred, C>>;
  }
} // namespace jln::mp
