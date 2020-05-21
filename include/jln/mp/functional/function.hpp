#pragma once

#include "identity.hpp"
#include "call.hpp"

namespace jln::mp
{
  /// \ingroup functional

  /// Makes a \function from a \lazymetafunction.
  /// \treturn \value
  /// \see cfe
  template<template<class...> class F, class C = identity>
  struct cfl
  {
    template<class... xs>
    using f = typename C::template f<JLN_MP_DCALLF_XS(xs, F, xs...)::type>;
  };

  /// \cond
  template<template<class...> class F>
  struct cfl<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_XS(xs, F, xs...)::type;
  };
  /// \endcond

  /// Makes a \function from a \metafunction.
  /// \treturn \value
  /// \see cfl
  template<template<class...> class F, class C = identity>
  struct cfe
  {
    template<class... xs>
    using f = typename C::template f<JLN_MP_DCALLF_XS(xs, F, xs...)>;
  };

  /// \cond
  template<template<class...> class F>
  struct cfe<F, identity>
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_XS(xs, F, xs...);
  };
  /// \endcond

#if __cplusplus >= 201703L
  template<template<auto...> class F>
  struct cfe_v
  {
    template<class... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs::value...);
  };

  template<template<auto...> class F>
  struct cfe_c
  {
    template<auto... xs>
    using f = JLN_MP_DCALLF_C_XS(xs, F, xs...);
  };

  template<template<class, auto...> class F>
  struct cfe_tv
  {
    template<class x, class... xs>
    using f = JLN_MP_DCALLF_TC_XS(xs, F, x, xs::value...);
  };

  template<template<class, auto...> class F>
  struct cfe_tc
  {
    template<class x, auto... xs>
    using f = JLN_MP_DCALLF_TC_XS(xs, F, x, xs...);
  };
#endif
} // namespace jln::mp
