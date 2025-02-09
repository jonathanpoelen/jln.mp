// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// Makes a continuation from a \lazymetafunction.
  /// cfe means continuation from eager.
  /// \treturn \value
  /// \see cfe, cfl_v, cfl_v_c
  template<template<class...> class F, class C = identity>
  struct cfl
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_XS(xs, F, xs...)::type);
  };

  /// Makes a continuation from a \metafunction.
  /// cfl means continuation from lazy.
  /// \treturn \value
  /// \see cfl, cfe_v, cfe_v_c
  template<template<class...> class F, class C = identity>
  struct cfe
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_XS(xs, F, xs...));
  };

  /// \cond
  template<template<class...> class F>
  struct cfl<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_XS(xs, F, xs...)::type;
  };

  template<template<class...> class F>
  struct cfe<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_XS(xs, F, xs...);
  };
  /// \endcond


  /// Makes a \function from a \lazymetafunction.
  /// \treturn \value
  /// \see cfl
  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C = identity>
  struct cfl_v
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_C_XS(xs, F, xs::value...)::type);
  };

  /// Makes a \function from a \metafunction.
  /// \treturn \value
  /// \see cfe
  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C = identity>
  struct cfe_v
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_C_XS(xs, F, xs::value...));
  };

  /// \cond
  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct cfl_v<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs::value...)::type;
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct cfe_v<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs::value...);
  };
  /// \endcond


  /// Makes a \function from a \lazymetafunction.
  /// \treturn \value
  /// \see cfl
  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C = identity>
  struct cfl_v_c
  {
    template<JLN_MP_TPL_AUTO_OR_INT... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_C_XS(xs, F, xs...)::type);
  };

  /// Makes a \function from a \metafunction.
  /// \treturn \value
  /// \see cfe
  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C = identity>
  struct cfe_v_c
  {
    template<JLN_MP_TPL_AUTO_OR_INT... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_C_XS(xs, F, xs...));
  };

  /// \cond
  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct cfl_v_c<F, identity>
  {
    template<JLN_MP_TPL_AUTO_OR_INT... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs...)::type;
  };

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct cfe_v_c<F, identity>
  {
    template<JLN_MP_TPL_AUTO_OR_INT... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs...);
  };
  /// \endcond


#if JLN_MP_GCC
#  define JLN_MP_CF_WRAP_IMPL(fn, fn_t) ::jln::mp::cfl<fn>
#else
#  define JLN_MP_CF_WRAP_IMPL(fn, fn_t) ::jln::mp::cfe<fn_t>
#endif

#define JLN_MP_CF_WRAP(fn) JLN_MP_CF_WRAP_IMPL(fn, fn##_t)
} // namespace jln::mp
