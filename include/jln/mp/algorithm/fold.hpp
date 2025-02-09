// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/if.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/list/push_front.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/detail/sequence.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct fold_impl;
  }
  /// \endcond

  /// \ingroup reduce

  /// Folds left over a list using a binary predicate.
  /// The first element in the input pack as the state,
  /// use \c push_front<> to add state if needed.
  /// \semantics
  ///   \code
  ///   F::f<F::f<F::f<F::f<xs[0], xs[1]>, xs[2]>, ...>, xs[n-1]>
  ///   \endcode
  /// \pre `sizeof...(xs) >= 1`
  /// \treturn \value
  /// \see fold_or_else, fold_right, fold_tree, reverse_fold, fold_balanced_tree
  template<class F, class C = identity>
  struct fold
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::fold_impl<
        int(sizeof...(xs)) - 1
      >::template f<JLN_MP_TRACE_F(F)::template f, xs...>
    );
  };

  /// Folds left over a list using a binary predicate.
  /// Like \c fold<>, but uses \c EmptyC when \c xs is empty.
  /// \treturn \value
  /// \see fold, fold_right, fold_tree, reverse_fold, fold_balanced_tree
  template<class F, class EmptyC, class C = identity>
  using fold_or_else = if_<size<>, fold<F, C>, EmptyC>;

  template<class F, class FallbackValue, class C = identity>
  using fold_or = if_<size<>, fold<F, C>, always<FallbackValue>>;

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using fold = typename detail::_unpack<mp::push_front<state, mp::fold<F, C>>, L>::type;

    template<class L, class F, class FallbackValue, class C = mp::identity>
    using fold_or = typename detail::_unpack<mp::fold_or_else<F, always<FallbackValue>, C>, L>::type;

    template<class L, class F, class EmptyC = F, class C = mp::identity>
    using fold_or_else = typename detail::_unpack<mp::fold_or_else<F, EmptyC, C>, L>::type;

    template<class L, class F, class C = mp::identity>
    using reduce = typename detail::_unpack<mp::fold<F, C>, L>::type;
  }
}


/// \cond
namespace jln::mp
{
  template<class F>
  struct fold<F, identity>
  {
    template<class... xs>
    using f = typename detail::fold_impl<
      int(sizeof...(xs)) - 1
    >::template f<JLN_MP_TRACE_F(F)::template f, xs...>;
  };

#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_DEBUG
  template<template<class...> class F, class C>
  struct fold<lift<F>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::fold_impl<
        int(sizeof...(xs)) - 1
      >::template f<F, xs...>
    );
  };

  template<template<class...> class F>
  struct fold<lift<F>, identity>
  {
    template<class... xs>
    using f = typename detail::fold_impl<
      int(sizeof...(xs)) - 1
    >::template f<F, xs...>;
  };
#endif
}

namespace jln::mp::detail
{
  template<int n>
  struct fold_impl : fold_impl<
      n < 8 ? 4
    : n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
  >
  {};

#define JLN_MP_FOLD_LEFT_SELECT(n, mp_xs, _, mp_dup)  \
  template<>                                          \
  struct fold_impl<n>                                 \
  {                                                   \
    template<template<class...> class F, class state, \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),         \
      class... xs>                                    \
    using f = typename fold_impl<                     \
      sizeof...(xs)                                   \
    >::template f<F,                                  \
      mp_dup(F<, JLN_MP_NIL) state,                   \
      mp_xs(JLN_MP_NIL, >, JLN_MP_COMMA), xs...       \
    >;                                                \
  };

  JLN_MP_GEN_XS_4_8_16_64_256(JLN_MP_FOLD_LEFT_SELECT)

#undef JLN_MP_FOLD_LEFT_SELECT

#define JLN_MP_FOLD_LEFT_SELECT(n, mp_xs, _, mp_dup)  \
  template<>                                          \
  struct fold_impl<n>                                 \
  {                                                   \
    template<template<class...> class F, class state, \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA)>         \
    using f = mp_dup(F<, JLN_MP_NIL) state,           \
      mp_xs(JLN_MP_NIL, >, JLN_MP_COMMA);             \
  };

  JLN_MP_GEN_XS_1_TO_4(JLN_MP_FOLD_LEFT_SELECT)

#undef JLN_MP_FOLD_LEFT_SELECT

  template<>
  struct fold_impl<0>
  {
    template<template<class...> class, class state>
    using f = state;
  };

  template<>
  struct fold_impl<-1>
  {};
}
/// \endcond
