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
    using f = typename C::template f<JLN_MP_DCALLF_XS(xs, F, xs...)::type>;
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
    using f = typename C::template f<JLN_MP_DCALLF_XS(xs, F, xs...)>;
  };

  /// \cond
  template<template<class...> class F>
  struct lift<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_XS(xs, F, xs...);
  };
  /// \endcond

#if __cplusplus >= 201703L
  template<template<auto...> class F>
  struct lift_c
  {
    template<auto... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs...);
  };

  template<template<auto...> class F>
  struct lift_v
#else
  template<template<int_...> class F>
  struct lift_c
  {
    template<int_... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs...);
  };

  template<template<int_...> class F>
  struct lift_v
#endif
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs::value...);
  };
} // namespace jln::mp
