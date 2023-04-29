#pragma once

#include <jln/mp/functional/partial_each.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// Replace the first element of the \sequence.
  /// \treturn \list
  template<class F, class C = listify>
  using transform_first = partial_each<F, C>;

  namespace emp
  {
    template<class L, class F, class C = listify>
    using transform_first = unpack<L, mp::partial_each<F, C>>;
  }
}
