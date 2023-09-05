#pragma once

#include <jln/mp/functional/partial_each.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Replace the third element of the \sequence.
  /// \treturn \list
  template<class F, class C = listify>
  using transform_third = partial_each<identity, identity, F, C>;

  namespace emp
  {
    template<class L, class F, class C = listify>
    using transform_third = unpack<L, mp::partial_each<mp::identity, mp::identity, F, C>>;
  }
}
