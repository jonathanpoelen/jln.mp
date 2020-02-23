#pragma once

#include "../list/list.hpp"
#include "../../algorithm/repeat.hpp"

namespace jln::mp::smp
{
  template<int_ n, class C = listify>
  using repeat_c = repeat<mp::number<n>, subcontract<C>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(repeat, (N), (C, smp::listify), smp::repeat_c<N::value, C>)

namespace jln::mp::detail
{
  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, repeat<N, C>>
  {
    using type = smp::repeat<N, sfinae<C>>;
  };
}
