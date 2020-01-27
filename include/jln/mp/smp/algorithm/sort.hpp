#pragma once

#include "../list/list.hpp"
#include "../number/operators.hpp"
#include "../../functional/contract.hpp"
#include "../../algorithm/sort.hpp"

namespace jln::mp::smp
{
  template<class Cmp = less<>, class C = listify>
  using sort = try_contract<sort<subcontract<Cmp>, subcontract<C>>>;

  template<class Cmp = less<>, class C = listify>
  using stable_sort = sort<Cmp, C>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, sort<Cmp, C>>
  {
    using type = smp::sort<sfinae<Cmp>, sfinae<C>>;
  };
}
