#pragma once

#include "../list/list.hpp"
#include "../../functional/monadic.hpp"
#include "../../algorithm/remove_adjacent.hpp"

namespace jln::mp::smp
{
  template<class F, class C = listify>
  using remove_adjacent = valid_contract<mp::remove_adjacent<
    subcontract<F>, mp::monadic_xs<subcontract<C>>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, remove_adjacent<F, C>>
  {
    using type = smp::remove_adjacent<sfinae<F>, sfinae<C>>;
  };
}
