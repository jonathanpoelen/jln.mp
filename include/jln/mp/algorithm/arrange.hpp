// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/make_int_sequence.hpp>
#include <jln/mp/list/lookup.hpp>


namespace jln::mp
{
  /// \ingroup algorithm

  /// Uses a list of indexes to reorder a sequence.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   arrange<numbers<0, 2, 0>>::f<a, b, c, d> == list<a, c, a>
  ///   \endcode
  /// \treturn \list
  template<class Ints, class C = listify>
  struct arrange
  {};

  template<unsigned... ints>
  using arrange_c = arrange<int_seq_v<ints...>>;

  template<int_... ints, class C>
  struct arrange<int_seq_v<ints...>, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, typename build_indexed_v<xs...>::template f<ints>...);
  };

  template<template<class...> class Tpl, class... ints, class C>
  struct arrange<Tpl<ints...>, C>
    : arrange<int_seq_v<ints::value...>, C>
  {};

  template<template<class T, T...> class Tpl, class T, T... ints, class C>
  struct arrange<Tpl<T, ints...>, C>
    : arrange<int_seq_v<ints...>, C>
  {};

  namespace emp
  {
    template<class L, class Ints, class C = listify>
    using arrange = unpack<L, mp::arrange<Ints, C>>;

    template<class L, unsigned... ints>
    using arrange_c = unpack<L, mp::arrange<int_seq_v<ints...>>>;
  }
}
