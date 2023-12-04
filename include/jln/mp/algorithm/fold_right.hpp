// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/list/push_front.hpp>
#include <jln/mp/detail/sequence.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct fold_right_impl;
  }
  /// \endcond

  /// \ingroup reduce

  /// Folds right over a list using a binary predicate.
  /// The first element in the input pack as the state,
  /// use \c push_front<> to add state if needed.
  /// \semantics
  ///   \code
  ///   F::f<xs[1], F::f<..., F::f<xs[n-2], F::f<xs[n-1], xs[0]>>>>
  ///   \endcode
  /// \pre `sizeof...(xs) >= 1`
  /// \treturn \value
  /// \see fold, fold_tree, reverse_fold_right, fold_balanced_tree
  template<class F, class C = identity>
  struct fold_right
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::fold_right_impl<
        int(sizeof...(xs)) - 1
      >::template f<JLN_MP_TRACE_F(F)::template f, xs...>
    );
  };

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using fold_right = unpack<L,
      mp::push_front<state, mp::fold_right<F, C>>>;
  }
}


/// \cond
namespace jln::mp
{
  template<class F>
  struct fold_right<F, identity>
  {
    template<class... xs>
    using f = typename detail::fold_right_impl<
      int(sizeof...(xs)) - 1
    >::template f<JLN_MP_TRACE_F(F)::template f, xs...>;
  };

#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
  template<template<class...> class F, class C>
  struct fold_right<lift<F>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::fold_right_impl<
        int(sizeof...(xs)) - 1
      >::template f<F, xs...>
    );
  };

  template<template<class...> class F>
  struct fold_right<lift<F>, identity>
  {
    template<class... xs>
    using f = typename detail::fold_right_impl<
      int(sizeof...(xs)) - 1
    >::template f<F, xs...>;
  };
#endif
}

namespace jln::mp::detail
{
  template<int n>
  struct fold_right_impl : fold_right_impl<
      n < 8 ? 4
    : n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

#define JLN_MP_FOLD_RIGHT_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                               \
  struct fold_right_impl<n>                                \
  {                                                        \
    template<template<class...> class F, class state,      \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),              \
      class... xs>                                         \
    using f = mp_xs(F<, JLN_MP_COMMA, JLN_MP_NIL)          \
      typename fold_right_impl<sizeof...(xs)>              \
      ::template f<F, state, xs...>                        \
    mp_dup(>, JLN_MP_NIL);                                 \
  };

  JLN_MP_GEN_XS_4_8_16_64_256(JLN_MP_FOLD_RIGHT_SELECT)

#undef JLN_MP_FOLD_RIGHT_SELECT

#define JLN_MP_FOLD_RIGHT_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                               \
  struct fold_right_impl<n>                                \
  {                                                        \
    template<template<class...> class F, class state,      \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA)>              \
    using f = mp_xs(F<, JLN_MP_COMMA, JLN_MP_NIL)          \
      state mp_dup(>, JLN_MP_NIL);                         \
  };

  JLN_MP_GEN_XS_1_TO_4(JLN_MP_FOLD_RIGHT_SELECT)

#undef JLN_MP_FOLD_RIGHT_SELECT

  template<>
  struct fold_right_impl<0>
  {
    template<template<class...> class, class state>
    using f = state;
  };

  template<>
  struct fold_right_impl<-1>
  {};
}
/// \endcond
