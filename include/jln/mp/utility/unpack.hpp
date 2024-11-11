// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/number.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, class L, class... xs> struct _unpack {};
    template<class C, class L, class... xs> struct _unpack_append {};
#if JLN_MP_ENABLE_TPL_AUTO
    template<class C, class L, class... xs> struct _unpack_v {};
    template<class C, class L, class... xs> struct _unpack_append_v {};
#endif
  }
  /// \endcond

  /// \ingroup utility

  /// Turns a \typelist into a \sequence of those types.
  /// \semantics
  ///   \code
  ///   unpack<F>::f<typelist<xs...>, ys...> == F::f<ys..., xs...>
  ///   \endcode
  /// \treturn \sequence
  template<class C>
  struct unpack
  {
    template<class seq, class... xs>
    using f = typename detail::_unpack<C, seq, xs...>::type;
  };

  /// Turns a \typelist into a \sequence of those types.
  /// \semantics
  ///   \code
  ///   unpack_append<F>::f<typelist<xs...>, ys...> == F::f<xs..., ys...>
  ///   \endcode
  /// \treturn \sequence
  template<class C>
  struct unpack_append
  {
    template<class seq, class... xs>
    using f = typename detail::_unpack_append<C, seq, xs...>::type;
  };

#if JLN_MP_ENABLE_TPL_AUTO
  /// Turns a \typelist into a \sequence of those types.
  /// \semantics
  ///   \code
  ///   unpack<F>::f<valuelist<xs...>, ys...> == F::f<ys..., xs...>
  ///   \endcode
  /// \treturn \sequence
  template<class C>
  struct unpack_v
  {
    template<class seq, class... xs>
    using f = typename detail::_unpack_v<C, seq, xs...>::type;
  };

  /// Turns a \typelist into a \sequence of those types.
  /// \semantics
  ///   \code
  ///   unpack_append<F>::f<valuelist<xs...>, ys...> == F::f<xs..., ys...>
  ///   \endcode
  /// \treturn \sequence
  template<class C>
  struct unpack_append_v
  {
    template<class seq, class... xs>
    using f = typename detail::_unpack_append_v<C, seq, xs...>::type;
  };
#endif

  namespace emp
  {
    template<class L, class C, class... xs>
    using unpack = typename detail::_unpack<C, L, xs...>::type;

    template<class L, class C, class... xs>
    using unpack_append = typename detail::_unpack_append<C, L, xs...>::type;

    template<class L, class C, int_... xs>
    using unpack_c = typename detail::_unpack<C, L, number<xs>...>::type;

    template<class L, class C, int_... xs>
    using unpack_append_c = typename detail::_unpack_append<C, L, number<xs>...>::type;

#if JLN_MP_ENABLE_TPL_AUTO
    template<class L, class C, class... xs>
    using unpack_v = typename detail::_unpack_v<C, L, xs...>::type;

    template<class L, class C, class... xs>
    using unpack_append_v = typename detail::_unpack_append_v<C, L, xs...>::type;

    template<class L, class C, int_... xs>
    using unpack_c_v = typename detail::_unpack_v<C, L, number<xs>...>::type;

    template<class L, class C, int_... xs>
    using unpack_append_c_v = typename detail::_unpack_append_v<C, L, number<xs>...>::type;
#endif
  }
} // namespace jln::mp


#include <jln/mp/list/listify.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class C, template<class...> class Seq, class... ys, class... xs>
  struct _unpack<C, Seq<ys...>, xs...>
  {
    using type = typename C::template f<xs..., ys...>;
  };

  template<class C, template<class...> class Seq, class... xs, class... ys>
  struct _unpack_append<C, Seq<xs...>, ys...>
  {
    using type = typename C::template f<xs..., ys...>;
  };

  template<template<class...> class F, template<class...> class Seq, class... ys, class... xs>
  struct _unpack<lift<F>, Seq<ys...>, xs...>
  {
    using type = F<xs..., ys...>;
  };

  template<template<class...> class F, template<class...> class Seq, class... xs, class... ys>
  struct _unpack_append<lift<F>, Seq<xs...>, ys...>
  {
    using type = F<xs..., ys...>;
  };

  template<template<class...> class F, template<class...> class Seq, class... ys, class... xs>
  struct _unpack<lift_t<F>, Seq<ys...>, xs...>
  {
    using type = typename F<xs..., ys...>::type;
  };

  template<template<class...> class F, template<class...> class Seq, class... xs, class... ys>
  struct _unpack_append<lift_t<F>, Seq<xs...>, ys...>
  {
    using type = typename F<xs..., ys...>::type;
  };

#if JLN_MP_ENABLE_TPL_AUTO
  template<class C, template<auto...> class Seq, auto... ys, class... xs>
  struct _unpack_v<C, Seq<ys...>, xs...>
  {
    using type = typename C::template f<xs..., ys...>;
  };

  template<class C, template<auto...> class Seq, auto... xs, class... ys>
  struct _unpack_append_v<C, Seq<xs...>, ys...>
  {
    using type = typename C::template f<xs..., ys...>;
  };
#endif

  template<class C>
  struct optimize_useless_unpack
  {
    using type = C;
  };

  template<>
  struct optimize_useless_unpack<unpack<listify>>
  {
    using type = identity;
  };

  template<>
  struct optimize_useless_unpack<unpack_append<listify>>
  {
    using type = identity;
  };

  template<class C>
  using optimize_useless_unpack_t = typename optimize_useless_unpack<C>::type;
}
/// \endcond
