#pragma once

#include "../list/list.hpp"
#include "../../algorithm/erase.hpp"

namespace jln::mp::smp
{
  template<class i, class count = number<1>, class C = listify>
  using erase = try_contract<mp::erase<i, count, subcontract<C>>>;

  template<int_ i, int_ count = 1, class C = listify>
  using erase_c = erase<number<i>, number<count>, C>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class i, class count, class C>
  struct _sfinae<sfinae, erase<i, count, C>>
  {
    using type = smp::erase<i, count, sfinae<C>>;
  };
}
