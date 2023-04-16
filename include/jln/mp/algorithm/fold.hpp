#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/list/push_front.hpp>
#include <jln/mp/detail/enumerate.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct fold_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Folds left over a list using a binary predicate.
  /// The first element in the input pack as the state,
  /// use \c push_front<> to add state if needed.
  /// \semantics
  ///   \code
  ///   F::f<F::f<F::f<F::f<xs[0], xs[1]>, xs[2]>, ...>, xs[n-1]>
  ///   \endcode
  /// \pre `sizeof...(xs) >= 1`
  /// \treturn \value
  /// \see fold_right, fold_tree, reverse_fold, fold_balanced_tree
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

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using fold = unpack<L,
      mp::push_front<state, mp::fold<F, C>>>;

    template<class L, class F, class C = mp::identity>
    using reduce = unpack<L, mp::fold<F, C>>;
  }

  /// \cond
  template<class F>
  struct fold<F, identity>
  {
    template<class... xs>
    using f = typename detail::fold_impl<
      int(sizeof...(xs)) - 1
    >::template f<JLN_MP_TRACE_F(F)::template f, xs...>;
  };

  #if ! JLN_MP_ENABLE_DEBUG
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
  /// \endcond
}


/// \cond
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
