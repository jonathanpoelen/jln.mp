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
    struct _reverse_fold;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Folds right over a list using a binary predicate.
  /// reverse_fold consideres the first element in the input pack as the state,
  /// use \c push_front<> to add state if needed.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   F::f<... F::f<F::f<state, xs[n-1]>, x[n-2]>, ..., x[0]>
  ///   \endcode
  /// \treturn \value
  /// \see fold_left, fold_right, fold_tree, fold_balanced_tree
#ifdef JLN_MP_DOXYGENATING
  template<class F, class C = identity>
  using reverse_fold = reverse<fold_left<F, C>>;
#else
  template<class F, class C = identity>
  struct reverse_fold
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::_reverse_fold<
        detail::sub_1_n_4_or_less_8_16_64_256(sizeof...(xs))
      >::template f<JLN_MP_TRACE_F(F)::template f, xs...>
    );
  };
#endif

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using reverse_fold = unpack<L,
      mp::push_front<state, mp::reverse_fold<F, C>>>;
  }
}


/// \cond
namespace jln::mp::detail
{
#define JLN_MP_REVERSE_FOLD_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                                 \
  struct _reverse_fold<n>                                    \
  {                                                          \
    template<template<class...> class F, class state,        \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),                \
      class... xs>                                           \
    using f = mp_dup(F<, JLN_MP_NIL)                         \
      typename _reverse_fold<                                \
        detail::n_4_or_less_8_16_64_256(sizeof...(xs))       \
      >::template f<F, state, xs...>,                        \
    mp_rxs(JLN_MP_NIL, >, JLN_MP_COMMA);                     \
  };

  JLN_MP_GEN_XS_4_8_16_64_256(JLN_MP_REVERSE_FOLD_SELECT)

#undef JLN_MP_REVERSE_FOLD_SELECT

#define JLN_MP_REVERSE_FOLD_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                                 \
  struct _reverse_fold<n>                                    \
  {                                                          \
    template<template<class...> class F, class state,        \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA)>                \
    using f = mp_dup(F<, JLN_MP_NIL)                         \
      state, mp_rxs(JLN_MP_NIL, >, JLN_MP_COMMA);            \
  };

  JLN_MP_GEN_XS_1_TO_4(JLN_MP_REVERSE_FOLD_SELECT)

#undef JLN_MP_REVERSE_FOLD_SELECT

  template<>
  struct _reverse_fold<0>
  {
    template<template<class...> class, class state>
    using f = state;
  };

  template<>
  struct _reverse_fold<-1>
  {};
}
/// \endcond
