#pragma once

#include "../list/list.hpp"
#include "../../number/numbers.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  // no checked
  using numbers = valid_contract<mp::numbers<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, numbers<C>>
  {
    using type = smp::numbers<sfinae<C>>;
  };
}
