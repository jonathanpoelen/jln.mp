#pragma once

#include "../list/list.hpp"
#include "../../algorithm/erase.hpp"

namespace jln::mp::smp
{
  template<int_ start, int_ size = 1, class C = listify>
  using erase_c = try_contract<mp::erase<number<start>, number<size>, subcontract<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(erase, (start), (size, number<1>), (C, smp::listify),
  smp::erase_c<start::value, size::value, C>)

namespace jln::mp::detail
{
  template<template<class> class sfinae, class start, class size, class C>
  struct _sfinae<sfinae, erase<start, size, C>>
  {
    using type = smp::erase<start, size, sfinae<C>>;
  };
}
