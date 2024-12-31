// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/each.hpp>
#include <jln/mp/number/operators.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// comparison on the result of a function.
  /// \treturn \bool
  template<class F, class Cmp = less<>>
  using compare_with = each<F, F, Cmp>;

  namespace emp
  {
    template<class F, class x, class y, class Cmp = mp::less<>>
    using compare_with = typename Cmp::template f<
      typename F::template f<x>,
      typename F::template f<y>
    >;

    template<class F, class x, class y, class Cmp = mp::less<>>
    inline constexpr bool compare_with_v = Cmp::template f<
      typename F::template f<x>,
      typename F::template f<y>
    >::value;
  }
}
