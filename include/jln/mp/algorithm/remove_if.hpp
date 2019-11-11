#pragma once

#include "../list/join.hpp"
#include "../functional/call.hpp"
#include "../functional/fork.hpp"
#include "../number/operators.hpp"
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
  template<class Pred>
  struct list_wrap_if : detail::_list_wrap_if<Pred::template f>
  {
    // TODO
    // template<class x>
    // using f;
  };

  template<class Pred, class C = listify>
  using remove_if = transform<list_wrap_if<Pred>, join<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using remove_if = eager<L, mp::remove_if<Pred, C>>;
  }
}

namespace jln::mp
{
  template<class Pred>
  struct list_wrap_if<fork<Pred, not_<>>>
  : detail::_list_wrap_if_not<Pred::template f>
  {
    // TODO
    // template<class x>
    // using f;
  };

  template<class Pred>
  struct list_wrap_if<fork<fork<Pred, not_<>>, not_<>>>
  : list_wrap_if<Pred>
  {
    // TODO
    // template<class x>
    // using f;
  };
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
    template<class x>
    using f = typename _wrap_if<!Pred<x>::value>::template f<x>;
  };

  template<template<class...> class Pred>
  struct _list_wrap_if_not
  {
    template<class x>
    using f = typename _wrap_if<Pred<x>::value>::template f<x>;
  };
}
