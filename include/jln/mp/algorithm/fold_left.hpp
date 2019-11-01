#pragma once

#include "../functional/identity.hpp"

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
    template<class... xs>
    using f = typename C::template f<
      typename detail::_fold_left<sizeof...(xs)-1>
      ::template f<F::template f, xs...>
    >;
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using fold_left = eager<L, mp::fold_left<C>>;
  }
}

#include "../config/enumerate.hpp"

namespace jln::mp::detail
{
  template<int n>
  struct _fold_left
  : _fold_left<
    ( n >= 256 ? 256
    : n >= 64 ? 64
    : n >= 16 ? 16
    : n >= 8 ? 8
    : n >= 4 ? 4
    : n)>
  {};

#define JLN_MP_FOLD_LEFT_SELECT(n, mp_xs, mp_dup)   \
  template<>                                        \
  struct _fold_left<n>                              \
  {                                                 \
    template<template<class...> class F, class x,   \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),       \
      class... xs>                                  \
    using f = typename _fold_left<sizeof...(xs)>    \
      ::template f<F,                               \
        mp_dup(F<, JLN_MP_NIL) x,                   \
        mp_xs(JLN_MP_NIL, >, JLN_MP_COMMA), xs...>; \
  };

  JLN_MP_GEN_XS_4_8_16_64_256(JLN_MP_FOLD_LEFT_SELECT)

#undef JLN_MP_FOLD_LEFT_SELECT

#define JLN_MP_FOLD_LEFT_SELECT(n, mp_xs, mp_dup) \
  template<>                                      \
  struct _fold_left<n>                            \
  {                                               \
    template<template<class...> class F, class x, \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA)>     \
    using f = mp_dup(F<, JLN_MP_NIL) x,           \
      mp_xs(JLN_MP_NIL, >, JLN_MP_COMMA);         \
  };

  JLN_MP_GEN_XS_1_TO_4(JLN_MP_FOLD_LEFT_SELECT)

#undef JLN_MP_FOLD_LEFT_SELECT

  template<>
  struct _fold_left<0>
  {
    template<template<class...> class, class x>
    using f = x;
  };
}
