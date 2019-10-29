#pragma once

#include "identity.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<bool>
    struct dcallf;
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
} // namespace jln::mp

namespace jln::mp::detail
{
  template<bool>
  struct dcallf;

  template<>
  struct dcallf<true>
  {
    template<template<class...> class F, typename...xs>
    using f = F<xs...>;
  };
}
