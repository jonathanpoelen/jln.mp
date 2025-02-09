// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/rotate.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class... Fs>
    struct partial_transform0_xs_impl;

    template<int, class C, class... Fs>
    struct partial_transform_xs_select;

    template<class... Fs>
    using partial_transform_xs_impl = partial_transform_xs_select<2, Fs...>;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions each taking the parameter corresponding to its position,
  /// except the last one taking zero to all remaining parameters.
  /// \semantics
  ///   \code
  ///   partial_transform_xs<F,G,H,C>::f<a> == /* error */
  ///   partial_transform_xs<F,G,H,C>::f<a,b> == C::f<F::f<a>, G::f<b>, H::f<>>
  ///   partial_transform_xs<F,G,H,C>::f<a,b,c,d> == C::f<F::f<a>, G::f<b>, H::f<c,d>>
  ///   partial_transform_xs<C>::f<> == C::f<>
  ///   partial_transform_xs<C>::f<a> == /* error */
  ///   \endcode
  /// \treturn \sequence
  /// \see partial_transform0_xs, partial_transform, partial_tee, each, tee
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct partial_transform_xs
  {
    template<class... xs>
    using f;
  };
#else
  template<class... Fs>
  struct partial_transform_xs
    : detail::rotate_impl<sizeof...(Fs)-2>
    ::template f<sizeof...(Fs)-2, detail::partial_transform_xs_impl, Fs...>
  {};

  template<class C>
  struct partial_transform_xs<C>
  {
    template<class... xs>
    using f = typename conditional_c<JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs))>
      ::template f<C, void>
      ::template f<>;
  };
#endif

  /// Invokes multiple functions each taking the parameter corresponding to its position
  /// (or without parameter whether it does not exist),
  /// except the last one taking zero to all remaining parameters.
  /// \semantics
  ///   \code
  ///   partial_transform0_xs<F,G,H,C>::f<a> == C::f<F::f<a>, G::f<>, H::f<>>
  ///   partial_transform0_xs<F,G,H,C>::f<a,b> == C::f<F::f<a>, G::f<b>, H::f<>>
  ///   partial_transform0_xs<F,G,H,C>::f<a,b,c,d> == C::f<F::f<a>, G::f<b>, H::f<c,d>>
  ///   partial_transform0_xs<C>::f<> == C::f<>
  ///   partial_transform0_xs<C>::f<a> == /* error */
  ///   \endcode
  /// \treturn \sequence
  /// \see partial_transform_xs, partial_transform, partial_tee, each, tee
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct partial_transform0_xs
  {
    template<class... xs>
    using f;
  };
#else
  template<class... Fs>
  struct partial_transform0_xs
    : detail::rotate_impl<sizeof...(Fs)-2>
    ::template f<sizeof...(Fs)-2, detail::partial_transform0_xs_impl, Fs...>
  {};

  template<class C>
  struct partial_transform0_xs<C> : partial_transform_xs<C>
  {};
#endif
}


#include <jln/mp/functional/partial_transform.hpp>

/// \cond
namespace jln::mp::detail
{
  constexpr int partial_transform_xs_selector(std::size_t nf, std::size_t nx)
  {
    --nf;
    return nf == nx ? 0
         : nf == nx + 1 ? 1
         : nf < nx ? 2
         : 3;
  }

  // each (sizeof...(Fs) + 1 == sizeof...(xs))
  template<class F, class C, class... Fs>
  struct partial_transform_xs_select<0, F, C, Fs...>
  : _each<C, Fs..., F>
  {};

  // each (sizeof...(Fs) == sizeof...(xs))
  template<class F, class C, class... Fs>
  struct partial_transform_xs_select<1, F, C, Fs...>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      JLN_MP_CALL_TRACE(Fs, xs)...,
      JLN_MP_CALL_TRACE_0_ARG(F)
    );
  };

  template<class... Fs>
  struct partial_transform_xs_prefix
  {
    template<class C, class last, class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_CALL_TRACE(Fs, xs)..., last);
  };

  // sizeof...(Fs) + 1 < sizeof...(xs)
  template<class F, class C, class... Fs>
  struct partial_transform_xs_select<2, F, C, Fs...>
  {
    template<class... xs>
    using f = typename take_front_impl<sizeof...(Fs) + (sizeof...(xs) & 0) + 2>
      ::template f<
        sizeof...(Fs) + 2,
        partial_transform_xs_prefix<Fs...>::template f,
        C,
        typename drop_front_impl<(sizeof...(xs) & 0) + sizeof...(Fs)>
        ::template f<sizeof...(Fs), JLN_MP_TRACE_F(F)::template f, xs...>,
        xs...
      >;
  };

  #if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_DEBUG
  template<template<class...> class F, class C, class... Fs>
  struct partial_transform_xs_select<2, cfe<F>, C, Fs...>
  {
    template<class... xs>
    using f = typename take_front_impl<sizeof...(Fs) + (sizeof...(xs) & 0) + 2>
      ::template f<
        sizeof...(Fs) + 2,
        partial_transform_xs_prefix<Fs...>::template f,
        C,
        typename drop_front_impl<(sizeof...(xs) & 0) + sizeof...(Fs)>
        ::template f<sizeof...(Fs), F, xs...>,
        xs...
      >;
  };
  #endif

  // sizeof...(Fs) + 1 > sizeof...(xs)
  template<class F, class C, class... Fs>
  struct partial_transform_xs_select<3, F, C, Fs...>
    : partial_transform_select<2, C, Fs..., F>
  {};

  template<class... Fs>
  struct partial_transform0_xs_impl
  {
    template<class... xs>
    using f = typename partial_transform_xs_select<
      partial_transform_xs_selector(sizeof...(Fs), sizeof...(xs)),
      Fs...
    >::template f<xs...>;
  };
}
/// \endcond
