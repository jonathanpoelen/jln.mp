#pragma once

#include "../functional/each.hpp"
#include "../number/operators.hpp"

namespace jln::mp
{
  /// \ingroup functional

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