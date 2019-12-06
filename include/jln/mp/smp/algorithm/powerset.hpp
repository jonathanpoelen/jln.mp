#pragma once

#include "../list/list.hpp"
#include "../../algorithm/powerset.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  using powerset = valid_contract<mp::powerset<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, powerset<C>>
  {
    using type = smp::powerset<sfinae<C>>;
  };
}
