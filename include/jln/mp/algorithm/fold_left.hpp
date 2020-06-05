#pragma once

#include "../functional/identity.hpp"
#include "../utility/unpack.hpp"
#include "../list/push_front.hpp"
#include "../detail/enumerate.hpp"

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct _fold_left;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Folds left over a list using a binary predicate.
  /// fold left consideres the first element in the input pack the state,
  /// use \c push_front<> to add state if needed.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   F::f<... F::f<state, xs[0]>, x[1]>, ..., x[n-1]>, ...>
  ///   \endcode
  /// \treturn \value
  template<class F, class C = identity>
  struct fold_left
  {
    template<class state, class... xs>
    using f = typename C::template f<
      typename detail::_fold_left<
        detail::n_4_or_less_8_16_64_256(sizeof...(xs))
      >::template f<F::template f, state, xs...>
    >;
  };

  namespace emp
  {
    template<class L, class state, class C = mp::identity>
    using fold_left = unpack<L,
      mp::push_front<state, mp::fold_left<C>>>;
  }
}


/// \cond
namespace jln::mp::detail
{
#define JLN_MP_FOLD_LEFT_SELECT(n, mp_xs, _, mp_dup)  \
  template<>                                          \
  struct _fold_left<n>                                \
  {                                                   \
    template<template<class...> class F, class state, \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),         \
      class... xs>                                    \
    using f = typename _fold_left<                    \
      detail::n_4_or_less_8_16_64_256(sizeof...(xs))  \
    >::template f<F,                                  \
      mp_dup(F<, JLN_MP_NIL) state,                   \
      mp_xs(JLN_MP_NIL, >, JLN_MP_COMMA), xs...       \
    >;                                                \
  };

  JLN_MP_GEN_XS_4_8_16_64_256(JLN_MP_FOLD_LEFT_SELECT)

#undef JLN_MP_FOLD_LEFT_SELECT

#define JLN_MP_FOLD_LEFT_SELECT(n, mp_xs, _, mp_dup)  \
  template<>                                          \
  struct _fold_left<n>                                \
  {                                                   \
    template<template<class...> class F, class state, \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA)>         \
    using f = mp_dup(F<, JLN_MP_NIL) state,           \
      mp_xs(JLN_MP_NIL, >, JLN_MP_COMMA);             \
  };

  JLN_MP_GEN_XS_1_TO_4(JLN_MP_FOLD_LEFT_SELECT)

#undef JLN_MP_FOLD_LEFT_SELECT

  template<>
  struct _fold_left<0>
  {
    template<template<class...> class, class state>
    using f = state;
  };
}
/// \endcond
