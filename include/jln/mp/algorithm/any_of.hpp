// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/none_of.hpp>
#include <jln/mp/number/not.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a predicate holds for at least some element of a \sequence.
  /// \c any_of is short-circuiting: if there is a template type
  /// argument `xs[i]` with `bool(xs[i]::value) == true`, then instantiating
  /// `any_of<C>::f<xs[0], ..., xs[n-1]>` does not require the
  /// instantiation of `Pred::f<xs[j]>::value` for `j > i`.
  /// If the predicate is fast, short-circuiting can slow down evaluation,
  /// and this form may be faster: `transform<Pred, any_of<is<true_>, C>>`
  /// because \c any_of is optimized with \c is.
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
