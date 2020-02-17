#pragma once

#include "../algorithm/fold_right.hpp"
#include "../functional/function.hpp"
#include "../utility/always.hpp"
#include "../list/at.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<unsigned> struct _compose;
    template<class, class> struct _compose_f;
  }

  template<template<class...> class F, template<class...> class... Fs>
  using compose = typename detail::_compose<sizeof...(Fs)>
    ::template f<F, Fs...>;

  template<class F, class... Fs>
  using compose_f = typename conditional_c<sizeof...(Fs) == 0>
    ::template f<
      at1<F>,
      mp::fold_right<cfl<detail::_compose_f>>
    >
    ::template f<identity, F, Fs...>;

  // TODO compose_c<auto F, auto Fs>
  /*TODO template<auto F>
  struct eval
  {
    template<class... xs>
    using f = decltype(F.template operator()<xs...>());
  };*/
}


#include "../config/enumerate.hpp"
#include "bind.hpp"

namespace jln::mp::detail
{
#define JLN_COMPOSE_IMPL(n, mp_xs, mp_rxs, mp_dup)       \
  template<template<class...> class F                    \
    mp_xs(JLN_MP_COMMA template<class...> class,         \
      JLN_MP_NIL, JLN_MP_NIL)>                           \
  struct _compose_impl##n                                \
  {                                                      \
    template<class... xs>                                \
    using f = mp_rxs(JLN_MP_NIL, <, JLN_MP_NIL)          \
      typename detail::dcallf<(sizeof...(xs) < 1000000)> \
      ::template f<F, xs...>                             \
    mp_dup(>, JLN_MP_NIL);                               \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_COMPOSE_IMPL)

#undef JLN_COMPOSE_IMPL

#define JLN_COMPOSE_IMPL(n, mp_xs, mp_rxs, mp_dup)  \
  template<>                                        \
  struct _compose<n>                                \
  {                                                 \
    template<template<class...> class F             \
      mp_xs(JLN_MP_COMMA template<class...> class,  \
        JLN_MP_NIL, JLN_MP_NIL)>                    \
    using f = _compose_impl##n<F                    \
      mp_xs(JLN_MP_COMMA, JLN_MP_NIL, JLN_MP_NIL)>; \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_COMPOSE_IMPL)

#undef JLN_COMPOSE_IMPL

  template<unsigned n>
  struct _compose
  {
    template<
      template<class...> class F0,
      template<class...> class F1,
      template<class...> class F2,
      template<class...> class F3,
      template<class...> class F4,
      template<class...> class F5,
      template<class...> class F6,
      template<class...> class F7,
      template<class...> class... Fs>
    using f = typename _compose<n-8>::template f<
      _compose_impl7<F0, F1, F2, F3, F4, F5, F6, F7>::template f,
      Fs...
    >;
  };

  template<class F, class C>
  struct _compose_f
  {
    using type = fork<F, C>;
  };

  template<template<class...> class F, class x>
  struct _compose_f<cfe<F>, x>
  {
    using type = cfe<F, x>;
  };

  template<template<class...> class F, class x>
  struct _compose_f<cfl<F>, x>
  {
    using type = cfl<F, x>;
  };

  // TODO compose_f smp::cfe/cfl
}
