// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/join.hpp>
#include <jln/mp/list/wrap_in_list.hpp>
#include <jln/mp/number/number.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<template<class...> class C, class... Selectors>
    struct compress_impl;

    template<class L, class C>
    struct make_compress;
  }
  /// \endcond

  /// \ingroup filter

  /// Removes elements that have a corresponding element in selectors to 0.
  /// \pre `emp::unpack<Selectors, listify> == Selectors`
  /// \pre all `Selectors::value` are `1`, `0` or a `bool` value
  /// \pre `sizeof...(xs) == emp::size<Selectors>`
  /// \semantics
  ///   \code
  ///   compress_c<1,0,1,0,1,1>
  ///          ::f<a,b,c,d,e,f>
  ///      == list<a,  c,  e,f>
  ///   \endcode
  /// \treturn \sequence
  template<class C, bool... selectors>
  struct compress_c_with
    : detail::compress_impl<C::template f, wrap_in_list_c<selectors>...>
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f;
#endif
  };

  template<bool... selectors>
  using compress_c = compress_c_with<listify, selectors...>;

  template<class... Selectors>
  using compress_for = compress_c_with<listify, Selectors::value...>;

  template<class Selectors, class C = listify>
  using compress = typename detail::make_compress<Selectors, C>::type;

  namespace emp
  {
    template<class L, class Selectors, class C = mp::listify>
    using compress = unpack<L, typename detail::make_compress<Selectors, C>::type>;

    template<class L, class... Selectors>
    using compress_for = unpack<L, mp::compress_c_with<listify, Selectors::value...>>;

    template<class L, bool... selectors>
    using compress_c = unpack<L, mp::compress_c_with<listify, selectors...>>;

    template<class L, class C, bool... selectors>
    using compress_c_with = unpack<L, mp::compress_c_with<C, selectors...>>;
  }
}


/// \cond
namespace jln::mp
{
  template<bool... selectors>
  struct compress_c_with<listify, selectors...>
    : detail::compress_impl<list, wrap_in_list_c<selectors>...>
  {};
}

namespace jln::mp::detail
{
  template<template<class...> class C, class... Selectors>
  struct compress_impl
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(Selectors)>
      ::template f<C, typename Selectors::template f<xs>...>
      ::type
      ;
  };

  template<template<class...> class Tpl, class... selectors, class C>
  struct make_compress<Tpl<selectors...>, C>
  {
    using type = compress_c_with<C, selectors::value...>;
  };
}
/// \endcond
