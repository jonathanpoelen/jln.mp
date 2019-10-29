#pragma once

#include "../functional/when.hpp"

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
    using f = typename detail::dcall<sizeof...(xs)>
      ::template f<C, typename detail::_same<always<xs>...>::type>;
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using same = eager<L, mp::same<C>>;
  }

  namespace smp
  {
    template<class C = identity>
    using same = when<mp::always<true_>,
      mp::same<when_continuation<C>>>;
  }
}

namespace jln::mp::detail
{
  template<class... xs>
  struct _same
  {
    using type = mp::false_;
  };

  template<template<class> class... _, class x>
  struct _same<_<x>...>
  {
    using type = mp::true_;
  };

  // TODO optional ?
  template<>
  struct _same<>
  {
    using type = mp::true_;
  };
}
