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
    struct _fold_right;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Folds right over a list using a binary predicate.
  /// fold_right consideres the first element in the input pack as the state,
  /// use \c push_front<> to add state if needed.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   F::f<x[0], ..., F::f<x[n-2], F::f<xs[n-1], state>>>
  ///   \endcode
  /// \treturn \value
  /// \see fold_left, fold_tree, reverse_fold, fold_balanced_tree
  template<class F, class C = identity>
  struct fold_right
  {
    template<class... xs>
    using f = typename C::template f<
      typename detail::_fold_right<
        detail::sub_1_n_4_or_less_8_16_64_256(sizeof...(xs))
      >::template f<F::template f, xs...>
    >;
  };

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using fold_right = unpack<L,
      mp::push_front<state, mp::fold_right<F, C>>>;
  }
}


/// \cond
namespace jln::mp::detail
{
#define JLN_MP_FOLD_RIGHT_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                               \
  struct _fold_right<n>                                    \
  {                                                        \
    template<template<class...> class F, class state,      \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),              \
      class... xs>                                         \
    using f = mp_xs(F<, JLN_MP_COMMA, JLN_MP_NIL)          \
      typename _fold_right<                                \
        detail::n_4_or_less_8_16_64_256(sizeof...(xs))     \
      >::template f<F, state, xs...>                       \
    mp_dup(>, JLN_MP_NIL);                                 \
  };

  JLN_MP_GEN_XS_4_8_16_64_256(JLN_MP_FOLD_RIGHT_SELECT)

#undef JLN_MP_FOLD_RIGHT_SELECT

#define JLN_MP_FOLD_RIGHT_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                               \
  struct _fold_right<n>                                    \
  {                                                        \
    template<template<class...> class F, class state,      \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA)>              \
    using f = mp_xs(F<, JLN_MP_COMMA, JLN_MP_NIL)          \
      state mp_dup(>, JLN_MP_NIL);                         \
  };

  JLN_MP_GEN_XS_1_TO_4(JLN_MP_FOLD_RIGHT_SELECT)

#undef JLN_MP_FOLD_RIGHT_SELECT

  template<>
  struct _fold_right<0>
  {
    template<template<class...> class, class state>
    using f = state;
  };

  template<>
  struct _fold_right<-1>
  {};
}
/// \endcond
