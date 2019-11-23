#pragma once

#include "drop.hpp"
#include "../algorithm/rotate.hpp"
#include "../../list/take.hpp"

namespace jln::mp::smp
{
  template<class N, class C = listify>
  using take = try_contract<mp::take<N, subcontract<C>>>;

  template<int_ n, class C = listify>
  using take_c = take<number<n>, C>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, take<N, C>>
  {
    using type = smp::take<N, sfinae<C>>;
  };
}
