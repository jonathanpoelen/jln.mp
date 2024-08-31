// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/if.hpp>
#include <jln/mp/list/at.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// A conditional selection expression.
  /// This is the equivalent of the ternary `Pred::f<a, b>::value ? a : b`.
  /// \pre `sizeof...(xs) >= 2`
  /// \treturn \value
  /// \see if_, reverse_select
  template<class Pred, class TC = identity, class FC = TC>
  using select = if_<Pred, front<TC>, at1<FC>>;

  /// A conditional selection expression.
  /// This is the equivalent of the ternary `Pred::f<a, b>::value ? b : a`.
  /// \pre `sizeof...(xs) >= 2`
  /// \treturn \value
  /// \see if_, select
  template<class Pred, class TC = identity, class FC = TC>
  using reverse_select = if_<Pred, at1<TC>, front<FC>>;

  namespace emp
  {
    template<class Pred, class a, class b>
    using select = typename mp::if_<Pred, mp::front<>, mp::at1<>>::template f<a, b>;

    template<class Pred, class a, class b>
    using reverse_select = typename mp::if_<Pred, mp::at1<>, mp::front<>>::template f<a, b>;
  }
}
