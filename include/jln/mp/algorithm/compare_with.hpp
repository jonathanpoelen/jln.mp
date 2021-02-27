#pragma once

#include <jln/mp/functional/each.hpp>
#include <jln/mp/number/operators.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// comparison on the result of a function.
  /// \treturn \bool
  template<class F, class Cmp = less<>>
  using compare_with = each<F, F, Cmp>;

  namespace emp
  {
    template<class F, class x, class y>
    using compare_with = less<call<F, x>, call<F, y>>;
  }
}
