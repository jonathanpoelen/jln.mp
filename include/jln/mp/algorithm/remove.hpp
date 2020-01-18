#pragma once

#include "../list/join.hpp"
#include "../functional/call.hpp"
#include "../functional/fork.hpp"
#include "../number/operators.hpp"
#include "../utility/same_as.hpp"
#include "transform.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<template<class...> class Pred>
    struct _list_wrap_if;

    template<template<class...> class Pred>
    struct _list_wrap_if_not;
  }

  // TODO list_wrap_if.hpp
  // TODO list_wrap_if_c
  template<class Pred>
  struct list_wrap_if : detail::_list_wrap_if<Pred::template f>
  {
    // TODO
    // template<class x>
    // using f;
  };

  template<class Pred, class C = listify>
  using remove_if = transform<list_wrap_if<Pred>, join<C>>;
  template<class T, class C = listify>
  using remove = remove_if<same_as<T>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using remove_if = eager<L, mp::remove_if<Pred, C>>;

    template<class L, class T, class C = mp::listify>
    using remove = eager<L, mp::remove<T, C>>;
  }
}

namespace jln::mp
{
  template<class x, class C>
  struct list_wrap_if<same_as<x, not_<C>>>
  : detail::_list_wrap_if_not<same_as<x, C>::template f>
  {};

  template<class Pred>
  struct list_wrap_if<fork<Pred, not_<>>>
  : detail::_list_wrap_if_not<Pred::template f>
  {};

  template<class Pred>
  struct list_wrap_if<fork<fork<Pred, not_<>>, not_<>>>
  : list_wrap_if<Pred>
  {};
}

namespace jln::mp::detail
{
  template<bool>
  struct _wrap_if
  {
    template<class>
    using f = list<>;
  };

  template<>
  struct _wrap_if<true>
  {
    template<class x>
    using f = list<x>;
  };

  template<template<class...> class Pred>
  struct _list_wrap_if
  {
    // TODO class x, class... xs   Pred<x,xs...>
    template<class x>
    using f = typename _wrap_if<!Pred<x>::value>::template f<x>;
  };

  template<template<class...> class Pred>
  struct _list_wrap_if_not
  {
    // TODO class x, class... xs   Pred<x,xs...>
    template<class x>
    using f = typename _wrap_if<Pred<x>::value>::template f<x>;
  };
}
