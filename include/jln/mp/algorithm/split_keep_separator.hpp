// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/split.hpp>

namespace jln::mp
{
  /// \ingroup group

  /// Splits a \sequence into multiple \lists at every point that satisfy a predicate.
  /// The separator value is inserted in a new list.
  /// \semantics
  ///   \code
  ///   split_keep_separator_if<is<_0>>::f<_0, _1, _2, _0, _3>
  ///   == list<
  ///     list<>,
  ///     list<_0>,
  ///     list<_1, _2>,
  ///     list<_0>,
  ///     list<_3>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see split_if, split_before_if
  template<class Pred, class C = listify>
  struct split_keep_separator_if
  {
    template<class... xs>
    using f = typename detail::_split<sizeof...(xs) != 0>
      ::template f<detail::split_keep_sep, C, JLN_MP_TRACE_F(Pred), xs...>;
  };

  template<class x, class C = listify>
  using split_keep_separator = split_keep_separator_if<is<x>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using split_keep_separator_if = unpack<L, mp::split_keep_separator_if<Pred, C>>;

    template<class L, class x, class C = mp::listify>
    using split_keep_separator = unpack<L, mp::split_keep_separator<x, C>>;
  }
}
