#pragma once

#include <jln/mp/algorithm/fold_right.hpp>
#include <jln/mp/functional/lift.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/utility/conditional.hpp>
#include <jln/mp/list/at.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned> struct _compose_f;
    template<class, class> struct _compose;
  }
  /// \endcond

  /// \ingroup functional

  /// Composition of two \metafunctions or more.
  /// \treturn \function
  template<template<class...> class F, template<class...> class... Fs>
  using compose_f = typename detail::_compose_f<sizeof...(Fs)>
    ::template f<F, Fs...>;

  /// Composition of two \functions or more.
  /// \treturn \function
  template<class F, class... Fs>
  using compose = typename conditional_c<sizeof...(Fs) == 0>
    ::template f<
      at1<F>,
      mp::fold_right<lift_t<detail::_compose>>
    >
    ::template f<identity, F, Fs...>;
}


#include <jln/mp/detail/enumerate.hpp>
#include <jln/mp/functional/tee.hpp>
#include <jln/mp/functional/bind.hpp>

/// \cond
namespace jln::mp::detail
{
#define JLN_COMPOSE_IMPL(n, mp_xs, mp_rxs, mp_dup) \
  template<template<class...> class F              \
    mp_xs(JLN_MP_COMMA template<class...> class,   \
      JLN_MP_NIL, JLN_MP_NIL)>                     \
  struct _compose_f_impl##n                        \
  {                                                \
    template<class... xs>                          \
    using f = mp_rxs(JLN_MP_NIL, <, JLN_MP_NIL)    \
      JLN_MP_DCALLF_XS(xs, F, xs...)               \
    mp_dup(>, JLN_MP_NIL);                         \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_COMPOSE_IMPL)

#undef JLN_COMPOSE_IMPL

#define JLN_COMPOSE_IMPL(n, mp_xs, mp_rxs, mp_dup)  \
  template<>                                        \
  struct _compose_f<n>                              \
  {                                                 \
    template<template<class...> class F             \
      mp_xs(JLN_MP_COMMA template<class...> class,  \
        JLN_MP_NIL, JLN_MP_NIL)>                    \
    using f = _compose_f_impl##n<F                  \
      mp_xs(JLN_MP_COMMA, JLN_MP_NIL, JLN_MP_NIL)>; \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_COMPOSE_IMPL)

#undef JLN_COMPOSE_IMPL

  template<unsigned n>
  struct _compose_f
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
    using f = typename _compose_f<n-8>::template f<
      _compose_f_impl7<F0, F1, F2, F3, F4, F5, F6, F7>::template f,
      Fs...
    >;
  };

  template<class F, class C>
  struct _compose
  {
    using type = tee<F, C>;
  };

  template<template<class...> class F, class x>
  struct _compose<lift<F>, x>
  {
    using type = lift<F, x>;
  };

  template<template<class...> class F, class x>
  struct _compose<lift_t<F>, x>
  {
    using type = lift_t<F, x>;
  };
}
/// \endcond
