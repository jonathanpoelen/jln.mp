#pragma once

#include "../list/join.hpp"
#include "../functional/call.hpp"
#include "../functional/bind.hpp"
#include "../utility/eager.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<template<class...> class, class>
    struct _flatten;

    template<class S>
    struct wrapper;
  }

  template<class S = cfe<list>, class C = listify>
  struct flatten;

  template<template<class...> class S, class C>
  struct flatten<cfe<S, identity>, C>
  {
    template<class... xs>
    using f = mp::call<mp::join<C>,
      typename detail::_flatten<S, xs>::type...>;
  };

  template<class S>
  using wrapper = typename detail::wrapper<S>::type;

  namespace emp
  {
    template<class L, class S = wrapper<L>, class C = mp::listify>
    using flatten = eager<L, mp::flatten<S, C>>;
  }
}

namespace jln::mp::detail
{
  template<template<class...> class, class T>
  struct _flatten
  {
    using type = list<T>;
  };

  template<template<class...> class S, class... xs>
  struct _flatten<S, S<xs...>>
  : _join_select<sizeof...(xs)>
    ::template f<list, typename _flatten<S, xs>::type...>
  {};

  template<template<class...> class S, class... xs>
  struct wrapper<S<xs...>>
  {
    using type = cfe<S>;
  };
}
