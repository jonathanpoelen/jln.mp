#pragma once

#include "remove.hpp"
#include "../number/operators.hpp"

namespace jln::mp
{
  /// \ingroup algorithm

  /// Copies all elements that satisfy a predicate.
  /// \treturn \sequence
  template<class Pred, class C = listify>
  using copy_if = remove_if<tee<Pred, not_<>>, C>;

  /// Copies all occurence of a \value.
  /// \treturn \sequence
  template<class x, class C = listify>
  using copy = remove_if<same_as<x, not_<>>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using copy_if = unpack<L, mp::copy_if<Pred, C>>;

    template<class L, class x, class C = mp::listify>
    using copy = unpack<L, mp::copy<x, C>>;
  }
}
