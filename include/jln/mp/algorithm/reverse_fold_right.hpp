// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

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
    struct reverse_fold_right_impl;
  }
  /// \endcond

  /// \ingroup reduce

  /// Folds right over a list using a binary predicate.
  /// This is equivalent to `reverse<fold<flip<F>, C>>`.
  /// \semantics
  ///   \code
  ///   F::f<xs[n-1], F::f<..., F::f<xs[2], F::f<xs[1], xs[0]>>>>
  ///   \endcode
  /// \pre `sizeof...(xs) >= 1`
  /// \treturn \value
  /// \see reverse_fold_right_or_else, fold, fold_right, fold_tree, fold_balanced_tree
  template<class F, class C = identity>
  struct reverse_fold_right
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::reverse_fold_right_impl<int(sizeof...(xs)) - 1>
      ::template f<JLN_MP_TRACE_F(F)::template f, xs...>
    );
  };

  /// Folds right over a list using a binary predicate.
  /// Like \c reverse_fold_right<>, but uses \c EmptyC when \c xs is empty.
  /// \treturn \value
  /// \see reverse_fold_right, fold, fold_right, fold_tree, fold_balanced_tree
  template<class F, class EmptyC, class C = identity>
  using reverse_fold_right_or_else = if_<size<>, reverse_fold_right<F, C>, EmptyC>;

  template<class F, class FallbackValue, class C = identity>
  using reverse_fold_right_or = if_<size<>, reverse_fold_right<F, C>, always<FallbackValue>>;

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using reverse_fold_right = typename detail::_unpack<
      mp::push_front<state, mp::reverse_fold_right<F, C>>, L>::type;

    template<class L, class F, class FallbackValue, class C = mp::identity>
    using reverse_fold_right_or = typename detail::_unpack<
      mp::reverse_fold_right_or_else<F, always<FallbackValue>, C>, L>::type;

    template<class L, class F, class EmptyC = F, class C = mp::identity>
    using reverse_fold_right_or_else = typename detail::_unpack<
      mp::reverse_fold_right_or_else<F, EmptyC, C>, L>::type;

    template<class L, class F, class C = mp::identity>
    using reverse_reduce = typename detail::_unpack<mp::reverse_fold_right<F, C>, L>::type;
  }
}


/// \cond
namespace jln::mp
{
  template<class F>
  struct reverse_fold_right<F, identity>
  {
    template<class... xs>
    using f = typename detail::reverse_fold_right_impl<int(sizeof...(xs)) - 1>
      ::template f<JLN_MP_TRACE_F(F)::template f, xs...>;
  };

#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
  template<template<class...> class F, class C>
  struct reverse_fold_right<lift<F>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::reverse_fold_right_impl<int(sizeof...(xs)) - 1>
      ::template f<F, xs...>
    );
  };

  template<template<class...> class F>
  struct reverse_fold_right<lift<F>, identity>
  {
    template<class... xs>
    using f = typename detail::reverse_fold_right_impl<int(sizeof...(xs)) - 1>
      ::template f<F, xs...>;
  };
#endif
}

namespace jln::mp::detail
{
  template<int n>
  struct reverse_fold_right_impl : reverse_fold_right_impl<
      n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

  template<>
  struct reverse_fold_right_impl<-1>
  {};

  template<>
  struct reverse_fold_right_impl<0>
  {
    template<template<class...> class, class state>
    using f = state;
  };

#define JLN_MP_REVERSE_FOLD_RIGHT_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                                       \
  struct reverse_fold_right_impl<n>                                \
  {                                                                \
    template<template<class...> class F, class state,              \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),                      \
      class... xs>                                                 \
    using f = mp_rxs(F<, JLN_MP_COMMA, JLN_MP_NIL)                 \
      state mp_dup(>, JLN_MP_NIL);                                 \
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_REVERSE_FOLD_RIGHT_SELECT)

#undef JLN_MP_REVERSE_FOLD_RIGHT_SELECT

#define JLN_MP_REVERSE_FOLD_RIGHT_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                                       \
  struct reverse_fold_right_impl<n>                                \
  {                                                                \
    template<template<class...> class F, class state,              \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),                      \
      class... xs>                                                 \
    using f = typename reverse_fold_right_impl<sizeof...(xs)>      \
      ::template f<                                                \
        F,                                                         \
        mp_rxs(F<, JLN_MP_COMMA, JLN_MP_NIL)                       \
          state mp_dup(>, JLN_MP_NIL),                             \
        xs...                                                      \
      >;                                                           \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_REVERSE_FOLD_RIGHT_SELECT)

#undef JLN_MP_REVERSE_FOLD_RIGHT_SELECT
}
/// \endcond
