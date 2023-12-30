// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/conjunction.hpp>
#include <jln/mp/algorithm/drop_until.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Perform a logical OR on the sequence of value and returns the first value converted to true.
  /// Disjunction is short-circuiting: if there is a template type
  /// argument `xs[i]` with `bool(xs[i]::value) == true`, then instantiating
  /// `disjunction<C>::f<xs[0], ..., xs[n-1]>` does not require the
  /// instantiation of `Pred::f<xs[j]>::value` for `j > i`
  /// \note If you just need a boolean, `any_of<Pred,C>` is more appropriate.
  /// \treturn \value
  /// \post If `sizeof...(xs) == 0`, `false_`
  /// \post If `sizeof...(xs) != 0`, the first type `xs[i]` for which `bool(Pred::f<xs[i]>::value) == true`, or last value if there is no such type.
  /// \see disjunction, drop_while, take_while
  template<class Pred, class C = identity>
  struct disjunction_with
  {
    template<class... xs>
    using f = typename detail::conjunction_impl<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<front<C>, sizeof...(xs)>
    ::template f<false_, xs...>;
  };

  /// Perform a logical OR on the sequence of value and returns the first value converted to true.
  /// Disjunction is short-circuiting: if there is a template type
  /// argument `xs[i]` with `bool(xs[i]::value) == true`, then instantiating
  /// `disjunction<C>::f<xs[0], ..., xs[n-1]>` does not require the
  /// instantiation of `xs[j]::value` for `j > i`.
  /// \note If you just need a boolean, `any_of<identity,C>` is more appropriate.
  /// \treturn \value convertible to \bool
  /// \post If `sizeof...(xs) == 0`, `false_`
  /// \post If `sizeof...(xs) != 0`, the first value for which `bool(xs[i]::value) == true`, or last value if there is no such type.
  /// \see disjunction, drop_while, take_while
  template<class C = identity>
  using disjunction = disjunction_with<identity, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using disjunction_with = unpack<L, mp::disjunction_with<Pred, C>>;

    template<class L, class C = mp::identity>
    using disjunction = unpack<L, mp::disjunction_with<mp::identity, C>>;
  }
}
