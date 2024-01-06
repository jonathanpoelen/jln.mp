// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// Makes a \function from a \lazymetafunction.
  /// \treturn \value
  /// \see lift
  template<template<class...> class F, class C = identity>
  struct lift_t
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_XS(xs, F, xs...)::type);
  };

  /// Makes a \function from a \metafunction.
  /// \treturn \value
  /// \see lift_t
  template<template<class...> class F, class C = identity>
  struct lift
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_XS(xs, F, xs...));
  };

  /// \cond
  template<template<class...> class F>
  struct lift_t<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_XS(xs, F, xs...)::type;
  };

  template<template<class...> class F>
  struct lift<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_XS(xs, F, xs...);
  };
  /// \endcond


  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C = identity>
  struct lift_v_t
  {
    template<JLN_MP_TPL_AUTO_OR_INT... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_C_XS(xs, F, xs...)::type);
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C = identity>
  struct lift_v
  {
    template<JLN_MP_TPL_AUTO_OR_INT... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_C_XS(xs, F, xs...));
  };

  /// \cond
  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct lift_v_t<F, identity>
  {
    template<JLN_MP_TPL_AUTO_OR_INT... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs...)::type;
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct lift_v<F, identity>
  {
    template<JLN_MP_TPL_AUTO_OR_INT... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs...);
  };
  /// \endcond


  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C = identity>
  struct lift_a2v_t
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_C_XS(xs, F, xs::value...)::type);
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C = identity>
  struct lift_a2v
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_C_XS(xs, F, xs::value...));
  };

  /// \cond
  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct lift_a2v_t<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs::value...)::type;
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct lift_a2v<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs::value...);
  };

#if JLN_MP_GCC
#  define JLN_MP_LIFT_WRAP_IMPL(fn, fn_t) ::jln::mp::lift_t<fn>
#else
#  define JLN_MP_LIFT_WRAP_IMPL(fn, fn_t) ::jln::mp::lift<fn_t>
#endif

#define JLN_MP_LIFT_WRAP(fn) JLN_MP_LIFT_WRAP_IMPL(fn, fn##_t)
/// \endcond
} // namespace jln::mp
