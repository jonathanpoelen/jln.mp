#pragma once

#include "list.hpp"
#include "../utility/unpack.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<class seq>
    struct _as_list
    {};
  }

  template<class C = listify>
  struct as_list
  {
    template<class seq>
    using f = typename unpack<C>::template f<typename detail::_as_list<seq>::type>;
  };

  template<>
  struct as_list<listify>
  {
    template<class seq>
    using f = typename detail::_as_list<seq>::type;
  };

  namespace emp
  {
    template<class seq, class C = mp::listify>
    using as_list = typename as_list<C>::template f<seq>;
  }
}

#include "../number/number.hpp"

namespace jln::mp::detail
{
  template<template<class...> class seq, class... xs>
  struct _as_list<seq<xs...>>
  {
    using type = list<xs...>;
  };

  template<template<class T, T...> class seq, class T, T... ns>
  struct _as_list<seq<T, ns...>>
  {
    using type = list<number<ns>...>;
  };

  template<template<auto...> class seq, auto... ns>
  struct _as_list<seq<ns...>>
  {
    using type = list<number<ns>...>;
  };
}
