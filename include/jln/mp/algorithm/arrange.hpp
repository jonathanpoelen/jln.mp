// SPDX-FileCopyrightText: 2026 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/lookup.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
#if ! JLN_MP_HAS_MEMOIZED_PACK_AT
    template<class C, int... ints>
    struct arrange_impl;
#endif

    template<class Ints>
    struct make_arrange
    {};
  }
  /// \endcond

  /// \ingroup algorithm

  /// Uses a list of indices to reorder a sequence.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   arrange<numbers<0, 2, 0>>::f<a, b, c, d> == list<a, c, a>
  ///   \endcode
  /// \treturn \list
  template<class Ints, class C = listify>
  using arrange = typename detail::make_arrange<Ints>::template f<C>;

#if JLN_MP_HAS_MEMOIZED_PACK_AT
  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_IGNORE_PACK_INDEXING_EXTENSION()
  template<class C, int... ints>
  struct arrange_c_with
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, JLN_MP_PACK_AT(xs, ints)...);
  };
  JLN_MP_DIAGNOSTIC_POP()
#else
  template<class C, int... ints>
  struct arrange_c_with : detail::apply_indexed_v<detail::arrange_impl<C, ints...>>
  {};
#endif

  template<int... ints>
  using arrange_c = arrange_c_with<listify, ints...>;

  namespace emp
  {
    template<class L, class Ints, class C = listify>
    using arrange = typename detail::_unpack<mp::arrange<Ints, C>, L>::type;

#if JLN_MP_HAS_MEMOIZED_PACK_AT
    template<class L, int... ints>
    using arrange_c = typename detail::_unpack<arrange_c_with<listify, ints...>, L>::type;

    template<class L, class C, int... ints>
    using arrange_with_c = typename detail::_unpack<arrange_c_with<C, ints...>, L>::type;
#else
    template<class L, int... ints>
    using arrange_c = typename detail::_unpack<
      detail::apply_indexed_v<detail::arrange_impl<listify, ints...>>, L>::type;

    template<class L, class C, int... ints>
    using arrange_with_c = typename detail::_unpack<
      detail::apply_indexed_v<detail::arrange_impl<C, ints...>>, L>::type;
#endif
  }
}


#include <jln/mp/utility/enable_if.hpp>
#include <jln/mp/number/number.hpp>  // JLN_MP_ENABLE_TPL_PARAM_AUTO

/// \cond
namespace jln::mp::detail
{
#if ! JLN_MP_HAS_MEMOIZED_PACK_AT
  template<class C, int... ints>
  struct arrange_impl
  {
    template<class F>
    using f = typename enable_if_t<0 <= sizeof(F), JLN_MP_TRACE_F(C)>
      ::template f<typename F::template f<ints>...>;
  };

  template<int... ints>
  struct arrange_impl<listify, ints...>
  {
    template<class F>
    using f = list<typename F::template f<ints>...>;
  };
#endif

  template<template<class...> class Tpl, class... ints>
  struct make_arrange<Tpl<ints...>>
  {
    template<class C>
    using f = arrange_c_with<C, ints::value...>;
  };

  template<template<class T, T...> class Tpl, class T, T... ints>
  struct make_arrange<Tpl<T, ints...>>
  {
    template<class C>
    using f = arrange_c_with<C, ints...>;
  };

  template<template<int_t...> class Tpl, int_t... ints>
  struct make_arrange<Tpl<ints...>>
  {
    template<class C>
    using f = arrange_c_with<C, ints...>;
  };

#if JLN_MP_ENABLE_TPL_PARAM_AUTO
  template<template<auto...> class Tpl, auto... ints>
  struct make_arrange<Tpl<ints...>>
  {
    template<class C>
    using f = arrange_c_with<C, ints...>;
  };
#endif
}
/// \endcond
