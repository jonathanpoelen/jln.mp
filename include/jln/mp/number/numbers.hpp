#pragma once

#include "number.hpp"
#include "../functional/when.hpp"
#include "../list/list.hpp"

namespace jln::mp
{
  template<class C = listify>
  struct numbers
  {
    template<int_... ns>
    using f = typename C::template f<number<ns>...>;
  };

  template<>
  struct numbers<listify>
  {
    template<int_... ns>
    using f = list<number<ns>...>;
  };

  namespace emp
  {
    template<int_... vs>
    using numbers = list<number<vs>...>;
  }

  namespace smp
  {
    template<class C = listify>
    // no checked
    using numbers = mp::when<
      mp::always<mp::true_>,
      mp::numbers<when_continuation<C>>>;
  }
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, numbers<C>>
  {
    using type = smp::numbers<sfinae<C>>;
  };
}
