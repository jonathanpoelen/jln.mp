#pragma once

#include "../number/numbers.hpp"
#include "../../list/iota.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  using iota = try_contract<mp::iota<subcontract<C>>>;

  template<class C = numbers<>>
  using iota_v = try_contract<mp::iota_v<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, iota_v<C>>
  {
    using type = smp::iota_v<sfinae<C>>;
  };
}
