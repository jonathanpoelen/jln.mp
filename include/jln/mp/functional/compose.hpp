// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/fold_right.hpp>
#include <jln/mp/functional/continuation.hpp>
#include <jln/mp/utility/conditional.hpp>
#include <jln/mp/list/at.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned> struct _compose_f;
    template<class, class> struct compose_impl;

    template<class x, class y>
    using compose_impl_t = typename compose_impl<x, y>::type;
  }
  /// \endcond

  /// \ingroup functional

  /// Composition of two \metafunctions or more.
  /// \semantics
  ///   \code
  ///   compose_f<foo, bar>::f<a, b> == bar<foo<a, b>>
  ///   \endcode
  /// \treturn \function
  template<template<class...> class F, template<class...> class... Fs>
  using compose_f = typename detail::_compose_f<sizeof...(Fs) < 8 ? sizeof...(Fs) : 8>
    ::template f<F, Fs...>;

  /// Composition of two \functions or more.
  /// \semantics
  ///   \code
  ///   compose<foo, bar>::f<a, b> == bar::f<foo::f<a, b>>
  ///   \endcode
  /// \treturn \function
  template<class F, class... Fs>
  using compose = typename conditional_c<sizeof...(Fs) == 0>
    ::template f<
      at1<F>,
      mp::fold_right<JLN_MP_CF_WRAP(detail::compose_impl)>
    >
    ::template f<identity, F, Fs...>;
}


#include <jln/mp/detail/sequence.hpp>
#include <jln/mp/functional/tee.hpp>

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
  struct compose_impl
  {
    using type = tee<F, C>;
  };

  template<template<class...> class F, class x>
  struct compose_impl<cfe<F>, x>
  {
    using type = cfe<F, x>;
  };

  template<template<class...> class F, class x>
  struct compose_impl<cfl<F>, x>
  {
    using type = cfl<F, x>;
  };

  template<class F>
  struct compose_impl<F, identity>
  {
    using type = F;
  };

  // fix ambiguity
  template<template<class...> class F>
  struct compose_impl<cfe<F>, identity>
  {
    using type = cfe<F>;
  };

  // fix ambiguity
  template<template<class...> class F>
  struct compose_impl<cfl<F>, identity>
  {
    using type = cfl<F>;
  };
}
/// \endcond
