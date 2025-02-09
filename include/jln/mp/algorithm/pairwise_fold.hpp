// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/rotate.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct pairwise_fold_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Computes the differences between adjacent pair of elements.
  /// \semantics
  ///   \code
  ///   pairwise_fold_and_transform_front<F, G, C>::f<a, b, c> = C::f<G::f<a>, F::f<a, b>, F::f<b, c>>
  ///   pairwise_fold_and_transform_front<F, G, C>::f<a> = C::f<G::f<a>>
  ///   pairwise_fold_and_transform_front<F, G, C>::f<> = C::f<>
  ///   \endcode
  /// \treturn \sequence
  template<class F, class Front = identity, class C = listify>
  struct pairwise_fold_and_transform_front
  {
    template<class... xs>
    using f = typename detail::pairwise_fold_impl<
      typename detail::rotate_impl<sizeof...(xs) ? sizeof...(xs) - 1 : 0>
      ::template f<sizeof...(xs) ? sizeof...(xs) - 1 : 0, list, xs...>
    >::template f<C, Front, JLN_MP_SIMPLE_MEMOIZER(F)::template f, xs...>;
  };

  /// Computes the differences between adjacent pair of elements.
  /// \semantics
  ///   \code
  ///   pairwise_fold<F, C>::f<a, b, c> = C::f<a, F::f<a, b>, F::f<b, c>>
  ///   pairwise_fold<F, C>::f<a> = C::f<a>
  ///   pairwise_fold<F, C>::f<> = C::f<>
  ///   \endcode
  /// \treturn \sequence
  template<class F, class C = listify>
  using pairwise_fold = pairwise_fold_and_transform_front<F, identity, C>;

  namespace emp
  {
    template<class L, class F, class Front = mp::identity, class C = mp::listify>
    using pairwise_fold_and_transform_front = typename detail::_unpack<
      mp::pairwise_fold_and_transform_front<F, Front, C>, L>::type;

    template<class L, class F, class C = mp::listify>
    using pairwise_fold = typename detail::_unpack<
      mp::pairwise_fold_and_transform_front<F, mp::identity, C>, L>::type;
  }
}

/// \cond
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_DEBUG
namespace jln::mp
{
  template<template<class...> class F, class Front, class C>
  struct pairwise_fold_and_transform_front<cfe<F>, Front, C>
  {
    template<class... xs>
    using f = typename detail::pairwise_fold_impl<
      typename detail::rotate_impl<sizeof...(xs) ? sizeof...(xs) - 1 : 0>
      ::template f<sizeof...(xs) ? sizeof...(xs) - 1 : 0, list, xs...>
    >::template f<C, Front, F, xs...>;
  };
}
#endif

namespace jln::mp::detail
{
  template<class y, class... ys>
  struct pairwise_fold_impl<list<y, ys...>>
  {
    template<class C, class Front, template<class...> class F, class x, class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_CALL_TRACE(Front, x), F<ys, xs>...);
  };

  template<>
  struct pairwise_fold_impl<list<>>
  {
    template<class C, class Front, template<class...> class F, class...>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };
}
/// \endcond
