#pragma once

#include "../list/list.hpp"
#include "../../functional/flip.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  using flip = try_contract<mp::flip<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, flip<C>>
  {
    using type = smp::flip<sfinae<C>>;
  };
}
