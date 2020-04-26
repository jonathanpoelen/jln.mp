#pragma once

#include "size.hpp"
#include "../number/operators.hpp"

namespace jln::mp
{
  /// \ingroup list

  /// Checks whether a sequence has no elements.
  /// \treturn \number
  template<class C = identity>
  using is_empty = size<not_<C>>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using is_empty = unpack<L, mp::is_empty<C>>;
  }
}
