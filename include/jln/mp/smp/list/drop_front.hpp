#pragma once

#include "../list/list.hpp"
#include "../../list/drop_front.hpp"
#include "../../number/operators.hpp"

namespace jln::mp::smp
{
  template<class N, class C = listify>
  using drop_front = contract<
    mp::size<mp::greater_equal_than<N>>,
    mp::drop_front<N, subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, drop_front<N, C>>
  {
    using type = smp::drop_front<N, sfinae<C>>;
  };
}
