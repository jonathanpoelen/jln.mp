#pragma once

#include "identity.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<bool> struct dcallf;
#if __cplusplus >= 201703L
    template<bool> struct dcallv;
    template<bool> struct dcalltv;
#endif
  }

  template<template<class...> class F, class C = identity>
  struct cfl
  {
    template<class... xs>
    using f = typename C::template f<
      typename detail::dcallf<sizeof...(xs) < 1000000>
      ::template f<F, xs...>::type
    >;
  };

  template<template<class...> class F>
  struct cfl<F, identity>
  {
    template<class... xs>
    using f = typename detail::dcallf<sizeof...(xs) < 1000000>
      ::template f<F, xs...>::type;
  };

  template<template<class...> class F, class C = identity>
  struct cfe
  {
    template<class... xs>
    using f = typename C::template f<
      typename detail::dcallf<sizeof...(xs) < 1000000>
      ::template f<F, xs...>
    >;
  };

  template<template<class...> class F>
  struct cfe<F, identity>
  {
    template<class... xs>
    using f = typename detail::dcallf<sizeof...(xs) < 1000000>
      ::template f<F, xs...>;
  };

#if __cplusplus >= 201703L
  template<template<auto...> class F>
  struct cfv
  {
    template<class... xs>
    using f = typename detail::dcallv<(sizeof...(xs) < 1000000)>
      ::template f<F, xs::value...>;
  };

  template<template<auto...> class F>
  struct cftv
  {
    template<class x, class... xs>
    using f = typename detail::dcalltv<(sizeof...(xs) < 1000000)>
      ::template f<F, x, xs::value...>;
  };

  template<template<auto...> class F>
  struct cfv_v
  {
    template<auto... vs>
    using f = typename detail::dcallv<(sizeof...(vs) < 1000000)>
      ::template f<F, vs...>;
  };

  template<template<auto...> class F>
  struct cftv_v
  {
    template<class x, auto... vs>
    using f = typename detail::dcalltv<(sizeof...(vs) < 1000000)>
      ::template f<F, x, vs...>;
  };
#endif
} // namespace jln::mp

namespace jln::mp::detail
{
  template<>
  struct dcallf<true>
  {
    template<template<class...> class F, class...xs>
    using f = F<xs...>;
  };

#if __cplusplus >= 201703L
  template<>
  struct dcallv<true>
  {
    template<template<auto...> class F, auto...vs>
    using f = F<vs...>;
  };

  template<>
  struct dcalltv<true>
  {
    template<template<class, auto...> class F, class x, auto...vs>
    using f = F<x, vs...>;
  };
#endif
}
