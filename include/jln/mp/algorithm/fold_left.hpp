#pragma once

#include "../config/enumerate.hpp"
#include "../functional/when.hpp"
#include "../functional/monadic_invoke.hpp"

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

  namespace smp
  {
    template<class F, class C = identity>
    using fold_left = when<
      mp::size<>,
      mp::fold_left<
        mp::monadic_invoke<when_continuation<F>>,
        mp::monadic_invoke<when_continuation<C>>>>;
  }
}

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

#define JLN_MP_FOLD_LEFT_SELECT(n, mp_xs, mp_repeat)   \
  template<>                                           \
  struct _fold_left<n>                                 \
  {                                                    \
    template<template<class...> class F,               \
      class x, mp_xs(class, JLN_MP_NIL), class... xs>  \
    using f = typename _fold_left<sizeof...(xs)>       \
      ::template f<F,                                  \
        mp_repeat(F<) x, mp_xs(JLN_MP_NIL, >), xs...>; \
  };

  JLN_MP_GEN_XS_4_8_16_64_256(JLN_MP_FOLD_LEFT_SELECT)

#undef JLN_MP_FOLD_LEFT_SELECT

#define JLN_MP_FOLD_LEFT_SELECT(n, mp_xs, mp_repeat) \
  template<>                                         \
  struct _fold_left<n>                               \
  {                                                  \
    template<template<class...> class F,             \
      class x, mp_xs(class, JLN_MP_NIL)>             \
    using f = mp_repeat(F<) x, mp_xs(JLN_MP_NIL, >); \
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
