#pragma once

#include "../list/list.hpp"
#include "../../algorithm/group_n.hpp"

namespace jln::mp::smp
{
  template<int_ n, class C = listify>
  using group_n_c = contract<mp::group_n_c<n, subcontract<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(group_n, (N), (C, smp::listify), smp::group_n_c<N::value, C>)

namespace jln::mp::detail
{
  template<template<class> class sfinae, class n, class C>
  struct _sfinae<sfinae, group_n<n, C>>
  {
    using type = smp::group_n<n, sfinae<C>>;
  };
}
