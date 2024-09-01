// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/list/push_front.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/detail/sequence.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct reverse_fold_impl;
  }
  /// \endcond

  /// \ingroup reduce

  /// Folds right over a list using a binary predicate.
  /// The first element in the input pack as the state,
  /// use \c push_front<> to add state if needed.
  /// \semantics
  ///   \code
  ///   F::f<F::f<F::f<F::f<xs[0], xs[n-1]>, x[n-2]>, ...>, x[1]>
  ///   \endcode
  /// \pre `sizeof...(xs) >= 1`
  /// \treturn \value
  /// \see reverse_fold_or_else, fold, reverse_fold_right, fold_tree, fold_balanced_tree
  template<class F, class C = identity>
  struct reverse_fold
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::reverse_fold_impl<
        int(sizeof...(xs)) - 1
      >::template f<JLN_MP_TRACE_F(F)::template f, xs...>
    );
  };

  /// Folds right over a list using a binary predicate.
  /// Like \c reverse_fold<>, but uses \c NoStateF when \c xs is empty.
  /// \treturn \value
  /// \see reverse_fold, fold, reverse_fold_right, fold_tree, fold_balanced_tree
  template<class F, class EmptyC, class C = identity>
  using reverse_fold_or_else = if_<size<>, rotate_c<-1, reverse_fold<F, C>>, EmptyC>;

  template<class F, class FallbackValue, class C = identity>
  using reverse_fold_or = reverse_fold_or_else<F, always<FallbackValue>, C>;

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using reverse_fold = unpack<L, mp::push_front<state, mp::reverse_fold<F, C>>>;

    template<class L, class F, class FallbackValue, class C = mp::identity>
    using reverse_fold_or = unpack<L, mp::reverse_fold_or_else<F, always<FallbackValue>, C>>;

    template<class L, class F, class NoStateF = F, class C = mp::identity>
    using reverse_fold_or_else = unpack<L, mp::reverse_fold_or_else<F, NoStateF, C>>;
  }
}


#include <jln/mp/algorithm/fold.hpp>

/// \cond
namespace jln::mp
{
  template<class F>
  struct reverse_fold<F, identity>
  {
    template<class... xs>
    using f = typename detail::reverse_fold_impl<
      int(sizeof...(xs)) - 1
    >::template f<JLN_MP_TRACE_F(F)::template f, xs...>;
  };

#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
  template<template<class...> class F, class C>
  struct reverse_fold<lift<F>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::reverse_fold_impl<
        int(sizeof...(xs)) - 1
      >::template f<F, xs...>
    );
  };

  template<template<class...> class F>
  struct reverse_fold<lift<F>, identity>
  {
    template<class... xs>
    using f = typename detail::reverse_fold_impl<
      int(sizeof...(xs)) - 1
    >::template f<F, xs...>;
  };
#endif
}

namespace jln::mp::detail
{
  template<int n>
  struct reverse_fold_impl : reverse_fold_impl<
      n < 8 ? 4
    : n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

#define JLN_MP_REVERSE_FOLD_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                                 \
  struct reverse_fold_impl<n>                                \
  {                                                          \
    template<template<class...> class F, class state,        \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),                \
      class... xs>                                           \
    using f = mp_dup(F<, JLN_MP_NIL)                         \
      typename reverse_fold_impl<                            \
        sizeof...(xs)                                        \
      >::template f<F, state, xs...>,                        \
    mp_rxs(JLN_MP_NIL, >, JLN_MP_COMMA);                     \
  };

  JLN_MP_GEN_XS_4_8_16_64_256(JLN_MP_REVERSE_FOLD_SELECT)

#undef JLN_MP_REVERSE_FOLD_SELECT

#define JLN_MP_REVERSE_FOLD_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                                 \
  struct reverse_fold_impl<n>                                \
  {                                                          \
    template<template<class...> class F, class state,        \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA)>                \
    using f = mp_dup(F<, JLN_MP_NIL)                         \
      state, mp_rxs(JLN_MP_NIL, >, JLN_MP_COMMA);            \
  };

  JLN_MP_GEN_XS_1_TO_4(JLN_MP_REVERSE_FOLD_SELECT)

#undef JLN_MP_REVERSE_FOLD_SELECT

  template<>
  struct reverse_fold_impl<0> : fold_impl<0>
  {};

  template<>
  struct reverse_fold_impl<-1>
  {};
}
/// \endcond
