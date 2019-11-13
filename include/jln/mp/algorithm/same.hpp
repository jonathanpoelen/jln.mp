#pragma once

#include "../functional/identity.hpp"
#include "../utility/eager.hpp"
#include "../number/number.hpp"
#include "../list/list.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<class... xs>
    struct _same;
  }

  template<class C = identity>
  struct same
  {
    template<class... xs>
    using f = typename C::template f<
      typename detail::_same<xs...>::type>;
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using same = eager<L, mp::same<C>>;
  }
}

namespace jln::mp::detail
{
  template<class... xs>
  struct _same_impl
  {
    using type = mp::false_;
  };

  template<template<class> class... _, class x>
  struct _same_impl<_<x>...>
  {
    using type = mp::true_;
  };

  template<class... xs>
  struct _same : _same_impl<list<xs>...>
  {};

  template<>
  struct _same<>
  {
    using type = mp::true_;
  };
}
