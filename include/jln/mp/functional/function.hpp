#pragma once

#include "identity.hpp"
#include "call.hpp"

namespace jln::mp
{
  /// \ingroup functional

  /// Makes a \function from a \lazymetafunction.
  /// \return \value
  /// \see cfe
  template<template<class...> class F, class C = identity>
  struct cfl
  {
    template<class... xs>
    using f = typename C::template f<
      typename detail::dcallf<sizeof...(xs) < 1000000>
      ::template f<F, xs...>::type
    >;
  };

  /// \cond
  template<template<class...> class F>
  struct cfl<F, identity>
  {
    template<class... xs>
    using f = typename detail::dcallf<sizeof...(xs) < 1000000>
      ::template f<F, xs...>::type;
  };
  /// \endcond

  /// Makes a \function from a \metafunction.
  /// \return \value
  /// \see cfl
  template<template<class...> class F, class C = identity>
  struct cfe
  {
    template<class... xs>
    using f = typename C::template f<
      typename detail::dcallf<sizeof...(xs) < 1000000>
      ::template f<F, xs...>
    >;
  };

  /// \cond
  template<template<class...> class F>
  struct cfe<F, identity>
  {
    template<class... xs>
    using f = typename detail::dcallf<sizeof...(xs) < 1000000>
      ::template f<F, xs...>;
  };
  /// \endcond

#if __cplusplus >= 201703L
  template<template<auto...> class F>
  struct cfe_v
  {
    template<class... xs>
    using f = typename detail::dcallf_c<(sizeof...(xs) < 1000000)>
      ::template f<F, xs::value...>;
  };

  template<template<auto...> class F>
  struct cfe_c
  {
    template<auto... xs>
    using f = typename detail::dcallf_c<(sizeof...(xs) < 1000000)>
      ::template f<F, xs...>;
  };

  template<template<class, auto...> class F>
  struct cfe_tv
  {
    template<class x, class... xs>
    using f = typename detail::dcallf_tc<(sizeof...(xs) < 1000000)>
      ::template f<F, x, xs::value...>;
  };

  template<template<class, auto...> class F>
  struct cfe_tc
  {
    template<class x, auto... xs>
    using f = typename detail::dcallf_tc<(sizeof...(xs) < 1000000)>
      ::template f<F, x, xs...>;
  };
#endif
} // namespace jln::mp
