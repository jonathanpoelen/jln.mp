#pragma once

#include "../functional/when.hpp"

namespace jln::mp
{
  template<class T, class C = listify>
  struct push_back
  {
    template<class... xs>
    using f = mp::call<C, xs..., T>;
  };

  namespace emp
  {
    template<class L, class T, class C = mp::listify>
    using push_back = eager<L, mp::push_back<T, C>>;
  }

  namespace smp
  {
    template<class T, class C = listify>
    using push_back = when<
      mp::always<mp::true_>,
      mp::push_back<T, when_continuation<C>>>;
  }
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class T, class C>
  struct _sfinae<sfinae, push_back<T, C>>
  {
    using type = smp::push_back<T, C>;
  };
}
