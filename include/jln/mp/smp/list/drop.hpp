#pragma once

#include "list.hpp"
#include "../../list/drop.hpp"

namespace jln::mp::smp
{
  template<class N, class C = listify>
  using drop = try_contract<mp::drop<N, subcontract<C>>>;

  template<int_ n, class C = listify>
  using drop_c = drop<number<n>, C>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, drop<N, C>>
  {
    using type = smp::drop<N, sfinae<C>>;
  };
}
