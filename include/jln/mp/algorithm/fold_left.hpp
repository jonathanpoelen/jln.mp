#pragma once

#include "../functional/identity.hpp"
#include "../utility/eager.hpp"
#include "../list/push_front.hpp"
#include "../config/enumerate.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<int>
    struct _fold_left;
  }

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
    using fold_left = eager<L,
      mp::push_front<state, mp::fold_left<C>>>;
  }
}


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
