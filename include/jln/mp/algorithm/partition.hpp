#pragma once

#include "remove.hpp"
#include "copy.hpp"
#include "../functional/fork.hpp"

namespace jln::mp
{
  /// \ingroup group

  /// Splits a \list in two according to a predicate.
  /// \treturn \sequence of two \values
  template<class Pred, class F = listify, class C = listify>
  using partition_with = fork<remove_if<Pred, F>, copy_if<Pred, F>, C>;

  /// Splits a \list in two according to a predicate.
  /// \treturn \sequence of two \lists
  template<class Pred, class C = listify>
  using partition = fork<remove_if<Pred>, copy_if<Pred>, C>;

  namespace emp
  {
    template<class L, class Pred, class F = mp::listify, class C = mp::listify>
    using partition_with = unpack<L, mp::partition_with<Pred, F, C>>;

    template<class L, class Pred, class C = mp::listify>
    using partition = unpack<L, mp::partition<Pred, C>>;
  }
}
