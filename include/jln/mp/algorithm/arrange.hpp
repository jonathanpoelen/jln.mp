// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/lookup.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, int... ints>
    struct arrange_impl;

    template<class Ints>
    struct make_arrange
    {};
  }
  /// \endcond

  /// \ingroup algorithm

  /// Uses a list of indexes to reorder a sequence.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   arrange<numbers<0, 2, 0>>::f<a, b, c, d> == list<a, c, a>
  ///   \endcode
  /// \treturn \list
  template<class Ints, class C = listify>
  using arrange = typename detail::make_arrange<Ints>::template f<C>;

  template<int... ints>
  using arrange_c = detail::apply_indexed_v<detail::arrange_impl<listify, ints...>>;

  template<class C, int... ints>
  using arrange_c_with = detail::apply_indexed_v<detail::arrange_impl<C, ints...>>;

  namespace emp
  {
    template<class L, class Ints, class C = listify>
    using arrange = typename detail::_unpack<mp::arrange<Ints, C>, L>::type;

    template<class L, int... ints>
    using arrange_c = typename detail::_unpack<
      detail::apply_indexed_v<detail::arrange_impl<listify, ints...>>, L>::type;

    template<class L, class C, int... ints>
    using arrange_with_c = typename detail::_unpack<
      detail::apply_indexed_v<detail::arrange_impl<C, ints...>>, L>::type;
  }
}


#include <type_traits>
#include <jln/mp/number/number.hpp>  // JLN_MP_ENABLE_TPL_AUTO

/// \cond
namespace jln::mp::detail
{
  template<class C, int... ints>
  struct arrange_impl
  {
    template<class F>
    using f = typename std::enable_if_t<0 <= sizeof(F), JLN_MP_TRACE_F(C)>
      ::template f<typename F::template f<ints>...>;
  };

  template<int... ints>
  struct arrange_impl<listify, ints...>
  {
    template<class F>
    using f = list<typename F::template f<ints>...>;
  };


  template<template<class...> class Tpl, class... ints>
  struct make_arrange<Tpl<ints...>>
  {
    template<class C>
    using f = apply_indexed_v<arrange_impl<C, ints::value...>>;
  };

  template<template<class T, T...> class Tpl, class T, T... ints>
  struct make_arrange<Tpl<T, ints...>>
  {
    template<class C>
    using f = apply_indexed_v<arrange_impl<C, ints...>>;
  };

  template<template<int_...> class Tpl, int_... ints>
  struct make_arrange<Tpl<ints...>>
  {
    template<class C>
    using f = apply_indexed_v<arrange_impl<C, ints...>>;
  };

#if JLN_MP_ENABLE_TPL_AUTO
  template<template<auto...> class Tpl, auto... ints>
  struct make_arrange<Tpl<ints...>>
  {
    template<class C>
    using f = apply_indexed_v<arrange_impl<C, ints...>>;
  };
#endif
}
/// \endcond
