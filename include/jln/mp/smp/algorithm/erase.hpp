#pragma once

#include "../list/list.hpp"
#include "../../algorithm/erase.hpp"

namespace jln::mp::smp
{
  template<class start, class size = number<1>, class C = listify>
  using erase = try_contract<mp::erase<start, size, subcontract<C>>>;

  template<int_ start, int_ size = 1, class C = listify>
  using erase_c = erase<number<start>, number<size>, C>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class start, class size, class C>
  struct _sfinae<sfinae, erase<start, size, C>>
  {
    using type = smp::erase<start, size, sfinae<C>>;
  };
}
