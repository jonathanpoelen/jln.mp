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

  /// \cond
  template<template<class...> class F>
  struct lift_t<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_XS(xs, F, xs...)::type;
  };
  /// \endcond

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
  struct lift<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_XS(xs, F, xs...);
  };
  /// \endcond

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C = identity>
  struct lift_c
  {
    template<JLN_MP_TPL_AUTO_OR_INT... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_C_XS(xs, F, xs...));
  };

  /// \cond
  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct lift_c<F, identity>
  {
    template<JLN_MP_TPL_AUTO_OR_INT... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs...);
  };
  /// \endcond

  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F, class C = identity>
  struct lift_v
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_DCALLF_C_XS(xs, F, xs::value...));
  };

  /// \cond
  template<template<JLN_MP_TPL_AUTO_OR_INT...> class F>
  struct lift_v<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs::value...);
  };
  /// \endcond
} // namespace jln::mp
