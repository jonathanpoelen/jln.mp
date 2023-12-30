// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/detail/sequence.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<uint_>
    struct _fold_tree;

    template<uint_>
    struct _fold_balanced_tree;
  }
  /// \endcond

  /// \ingroup reduce

  /// Folds tree over a list using a binary predicate.
  /// recursively fold n/2 value to the left and the rest to the right.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   F::f<fold_tree::f<...xs[0..n/2]>, fold_tree::f<...xs[n/2..n]>>
  ///   \endcode
  /// \treturn \value
  /// \see fold, fold_right, fold_balanced_tree
  template<class F, class C = identity>
  struct fold_tree
  {
    template<class... xs>
    using f = typename detail::_fold_tree<
      sizeof...(xs) < 3 ? sizeof...(xs) : 3
    >::template f<C, JLN_MP_TRACE_F(F)::template f, xs...>;
  };

  /// Folds tree over a list using a binary predicate.
  /// recursively fold (n+1)/2 value to the left and the rest to the right.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   F::f<fold_tree::f<...xs[0..(n+1)/2]>, fold_tree::f<...xs[n-(n+1)/2..n]>>
  ///   \endcode
  /// \treturn \value
  /// \see fold, fold_right, fold_tree
  template<class F, class C = identity>
  struct fold_balanced_tree
  {
    template<class... xs>
    using f = typename detail::_fold_balanced_tree<
      sizeof...(xs) < 3 ? sizeof...(xs) : 3
    >::template f<C, JLN_MP_TRACE_F(F)::template f, xs...>;
  };

  namespace emp
  {
    template<class L, class F, class C = mp::identity>
    using fold_tree = unpack<L, mp::fold_tree<F, C>>;

    template<class L, class F, class C = mp::identity>
    using fold_balanced_tree = unpack<L, mp::fold_balanced_tree<F, C>>;
  }
}


#include <jln/mp/list/take_front.hpp>
#include <jln/mp/list/drop_front.hpp>

/// \cond
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
namespace jln::mp
{
  template<template<class...> class F, class C>
  struct fold_tree<lift<F>, C>
  {
    template<class... xs>
    using f = typename detail::_fold_tree<
      sizeof...(xs) < 3 ? sizeof...(xs) : 3
    >::template f<C, F, xs...>;
  };

  template<template<class...> class F, class C>
  struct fold_balanced_tree<lift<F>, C>
  {
    template<class... xs>
    using f = typename detail::_fold_balanced_tree<
      sizeof...(xs) < 3 ? sizeof...(xs) : 3
    >::template f<C, F, xs...>;
  };
}
#endif

namespace jln::mp::detail
{
  constexpr unsigned bit_ceil(unsigned n)
  {
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
  }

  template<>
  struct _fold_tree<0>
  {
    template<class C, template<class...> class F>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };

  template<>
  struct _fold_tree<1>
  {
    template<class C, template<class...> class F, class x>
    using f = JLN_MP_CALL_TRACE(C, x);
  };

  template<>
  struct _fold_tree<2>
  {
    template<class C, template<class...> class F, class x, class y>
    using f = JLN_MP_CALL_TRACE(C, F<x, y>);
  };

  template<template<class...> class F, unsigned>
  struct fold_tree_impl;

  template<template<class...> class F>
  struct fold_tree_impl<F, 0>
  {
    template<class x>
    using f = x;
  };

  template<template<class...> class F>
  struct fold_tree_impl<F, 1>
  {
    template<class x, class y>
    using f = F<x, y>;
  };

  template<template<class...> class F, unsigned n>
  struct fold_tree_impl
  {
    template<class... xs>
    using f = F<
      typename take_front_c<n, fold_tree_impl<F, n/2>>::template f<xs...>,
      typename drop_front_c<n, fold_tree_impl<F, bit_ceil(sizeof...(xs)-n)/2>>::template f<xs...>
    >;
  };

  template<>
  struct _fold_tree<3>
  {
    template<class C, template<class...> class F, class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename fold_tree_impl<F, bit_ceil(sizeof...(xs))/2>::template f<xs...>
    );
  };


  template<>
  struct _fold_balanced_tree<0>
  : _fold_tree<0>
  {};

  template<>
  struct _fold_balanced_tree<1>
  : _fold_tree<1>
  {};

  template<>
  struct _fold_balanced_tree<2>
  : _fold_tree<2>
  {};

  template<template<class...> class F, uint_>
  struct fold_balanced_tree_impl;

  template<template<class...> class F>
  struct fold_balanced_tree_impl<F, 1>
  {
    template<class x>
    using f = x;
  };

  template<template<class...> class F>
  struct fold_balanced_tree_impl<F, 2>
  {
    template<class x, class y>
    using f = F<x, y>;
  };

  template<template<class...> class F, uint_ n>
  struct fold_balanced_tree_impl
  {
    template<class... xs>
    using f = F<
      typename take_front_c<(n+1)/2, fold_balanced_tree_impl<F, (n+1)/2>>
        ::template f<xs...>,
      typename drop_front_c<(sizeof...(xs) & 0) + (n+1)/2, fold_balanced_tree_impl<F, n-(n+1)/2>>
        ::template f<xs...>
    >;
  };

  template<>
  struct _fold_balanced_tree<3>
  {
    template<class C, template<class...> class F, class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename fold_balanced_tree_impl<F, sizeof...(xs)>::template f<xs...>
    );
  };
}
/// \endcond
