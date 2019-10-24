#pragma once

#include "../functional/when.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<class x, class = void>
    struct _as_number;
  }

  template<class C = identity>
  struct as_number
  {
    template<class x>
    using f = mp::call<C, number<x::value>>;
  };

  namespace emp
  {
    template<class x>
    using as_number = number<x::value>;
  }

  namespace smp
  {
    template<class C = identity>
    using as_number = when<
      mp::if_<mp::size_of_1<>, mp::cfe<detail::_as_number>>,
      mp::as_number<when_continuation<C>>>;
  }
}

#include <type_traits>

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, as_number<C>>
  {
    using type = smp::as_number<sfinae<C>>;
  };

  template<class v, class>
  struct _as_number
  : false_
  {};

  template<class v>
  struct _as_number<v, std::void_t<decltype(int_{v::value})>>
  : true_
  {};
}
