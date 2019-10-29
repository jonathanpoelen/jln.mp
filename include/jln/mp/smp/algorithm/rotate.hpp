#pragma once

#include "../list/list.hpp"
#include "../../algorithm/rotate.hpp"

namespace jln::mp::smp
{
  template <class N, class C = listify>
  using rotate = valid_contract<mp::rotate<N, subcontract<C>>>;

  template <int_ n, class C = listify>
  using rotate_c = rotate<number<n>, C>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, rotate<N, C>>
  {
    using type = smp::rotate<N, sfinae<C>>;
  };
}
