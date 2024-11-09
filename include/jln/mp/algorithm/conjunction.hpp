// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/drop_while.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/front.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct conjunction_impl;
  }
  /// \endcond

  /// \ingroup search

  /// Perform a logical AND on the sequence of value and returns the first value converted to false.
  /// Conjunction is short-circuiting: if there is a template type
  /// argument `xs[i]` with `bool(Pred::f<xs[i]>::value) == false`,
  /// then instantiating `conjunction<C>::f<xs[0], ..., xs[n-1]>`
  /// does not require the instantiation of `Pred::f<xs[j]>::value` for `j > i`.
  /// \note If you just need a boolean, `all_of<Pred,C>` is more appropriate.
  /// \treturn \value
  /// \post If `sizeof...(xs) == 0`, `true_`
  /// \post If `sizeof...(xs) != 0`, the first type `xs[i]` for which `bool(Pred::f<xs[i]>::value) == false`, or last value if there is no such type.
  /// \see disjunction, drop_while, take_while
  template<class Pred, class C = identity>
  struct conjunction_with
  {
    template<class... xs>
    using f = typename detail::conjunction_impl<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<front<C>, sizeof...(xs)>
    ::template f<true_, xs...>;
  };

  /// Perform a logical AND on the sequence of value and returns the first value converted to false.
  /// Conjunction is short-circuiting: if there is a template type
  /// argument `xs[i]` with `bool(xs[i]::value) == false`, then instantiating
  /// `conjunction<C>::f<xs[0], ..., xs[n-1]>` does not require the
  /// instantiation of `xs[j]::value` for `j > i`.
  /// \note If you just need a boolean, `all_of<identity,C>` is more appropriate.
  /// \treturn \value convertible to \bool
  /// \post If `sizeof...(xs) == 0`, `true_`
  /// \post If `sizeof...(xs) != 0`, the first value for which `bool(xs[i]::value) == false`, or last value if there is no such type.
  /// \see disjunction, drop_while, take_while
  template<class C = identity>
  using conjunction = conjunction_with<identity, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using conjunction_with = unpack<L, mp::conjunction_with<Pred, C>>;

    template<class L, class C = mp::identity>
    using conjunction = unpack<L, mp::conjunction_with<mp::identity, C>>;

    template<class L, class Pred, class C = mp::identity>
    inline constexpr bool conjunction_with_v = unpack<L, mp::conjunction_with<Pred, C>>::value;

    template<class L, class C = mp::identity>
    inline constexpr bool conjunction_v = unpack<L, mp::conjunction_with<mp::identity, C>>::value;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<>
  struct conjunction_impl<_drop_while_continue>
  {
    template<class C, std::size_t n>
    using f = drop_front_c<n, C>;
  };

  template<std::size_t n>
  struct conjunction_impl<_drop_while_result<n>>
  {
    template<class C, std::size_t m>
    using f = drop_front_c<m-n, C>;
  };
}
/// \endcond
