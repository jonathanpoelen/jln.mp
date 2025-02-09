// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/utility/unpack.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct transform_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Executes \c F on every element of a \sequence.
  /// \treturn \sequence
  template<class F, class C = listify>
  struct transform
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, JLN_MP_DCALL_TRACE_XS(xs, F, xs)...);
#else
    template<class... xs>
    using f = typename detail::transform_impl<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
      ::template f<JLN_MP_TRACE_F(C)::template f, JLN_MP_TRACE_F(F)::template f, xs...>;
#endif
  };

  namespace emp
  {
    template<class L, class F, class C = mp::listify>
    using transform = typename detail::_unpack<mp::transform<F, C>, L>::type;
  }

/// \cond
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_DEBUG
  template<class F, template<class...> class C>
  struct transform<F, cfe<C>>
  {
    template<class... xs>
    using f = typename detail::transform_impl<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
      ::template f<C, F::template f, xs...>;
  };

  template<template<class...> class F, class C>
  struct transform<cfe<F>, C>
  {
    template<class... xs>
    using f = typename detail::transform_impl<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
      ::template f<C::template f, F, xs...>;
  };

  template<template<class...> class F, template<class...> class C>
  struct transform<cfe<F>, cfe<C>>
  {
    template<class... xs>
    using f = typename detail::transform_impl<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
      ::template f<C, F, xs...>;
  };
#endif

#if ! JLN_MP_DEBUG
  namespace detail
  {
    template<bool>
    struct transform_impl_t;
  }

  template<template<class...> class F, class C>
  struct transform<cfl<F>, C>
  {
    template<class... xs>
    using f = typename detail::transform_impl_t<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
      ::template f<C::template f, F, xs...>;
  };

  template<template<class...> class F, template<class...> class C>
  struct transform<cfl<F>, cfe<C>>
  {
    template<class... xs>
    using f = typename detail::transform_impl_t<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
      ::template f<C, F, xs...>;
  };
#endif
/// \endcond
}


/// \cond
namespace jln::mp::detail
{
  template<>
  struct transform_impl<true>
  {
    template<template<class...> class C, template<class...> class F, class...xs>
    using f = C<F<xs>...>;
  };

  template<>
  struct transform_impl<false>
  {};

#if ! JLN_MP_DEBUG
  template<>
  struct transform_impl_t<true>
  {
    template<template<class...> class C, template<class...> class F, class...xs>
    using f = C<typename F<xs>::type...>;
  };

  template<>
  struct transform_impl_t<false>
  {};
#endif

  template<class T>
  struct optimize_useless_transform_unpack
  {
    using type = T;
  };

  template<class T>
  using optimize_useless_transform_unpack_t
    = typename optimize_useless_transform_unpack<T>::type;

  template<class F>
  struct optimize_useless_transform_unpack_impl
  {
    template<class C>
    using f = transform<F, C>;
  };

  template<>
  struct optimize_useless_transform_unpack_impl<identity>
  {
    template<class C>
    using f = optimize_useless_transform_unpack_t<C>;
  };

  template<class F, class C>
  struct optimize_useless_transform_unpack<transform<F, C>>
  {
    using type = typename optimize_useless_transform_unpack_impl<optimize_useless_unpack_t<F>>
      ::template f<C>;
  };
}
/// \endcond
