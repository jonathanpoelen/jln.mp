#pragma once

#include "../list/list.hpp"
#include "../../algorithm/group_n.hpp"

namespace jln::mp::smp
{
  template<class n, class C = listify>
  using group_n = valid_contract<mp::group_n<n, subcontract<C>>>;

  template<int_ n, class C = listify>
  using group_n_c = valid_contract<mp::group_n_c<n, subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class n, class C>
  struct _sfinae<sfinae, group_n<n, C>>
  {
    using type = smp::group_n<n, sfinae<C>>;
  };
}
