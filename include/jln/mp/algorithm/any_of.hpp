// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/none_of.hpp>
#include <jln/mp/number/not.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a predicate holds for at least some element of a \sequence.
  /// \treturn \bool
  /// \see all_of, none_of
  template<class Pred, class C = identity>
  using any_of = none_of<Pred, not_<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using any_of = typename detail::_unpack<mp::any_of<Pred, C>, L>::type;

    template<class Pred, class... xs>
    using any_of_xs = typename mp::any_of<Pred>::template f<xs...>;

    template<class L, class Pred, class C = mp::identity>
    inline constexpr bool any_of_v = detail::_unpack<mp::any_of<Pred, C>, L>::type::value;

    template<class Pred, class... xs>
    inline constexpr bool any_of_xs_v = mp::any_of<Pred>::template f<xs...>::value;
  }
} // namespace jln::mp
