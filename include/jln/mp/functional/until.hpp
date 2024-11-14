// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/recursively.hpp>
#include <jln/mp/functional/if.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// Apply a function until some \predicate is satisfied.
  /// \treturn \value
  /// \see until_xs
  template<class Pred, class F, class C = identity>
  using until = recursively<if_<Pred, stop_recursion, F>, C>;

  /// Apply a function until some \predicate is satisfied.
  /// \treturn \value
  /// \see until
  template<class Pred, class F, class C = listify>
  using until_xs = recursively<if_<Pred, stop_recursion, F>, C>;

  namespace emp
  {
    template<class L, class Pred, class F, class C = mp::identity>
    using until = typename detail::_unpack<mp::until<Pred, F, C>, L>::type;

    template<class L, class Pred, class F, class C = mp::listify>
    using until_xs = typename detail::_unpack<mp::until<Pred, F, C>, L>::type;
  }
}
