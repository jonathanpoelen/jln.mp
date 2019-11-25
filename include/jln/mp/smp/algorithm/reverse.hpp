#pragma once

#include "../list/list.hpp"
#include "../../algorithm/reverse.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  using reverse = valid_contract<mp::reverse<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, reverse<C>>
  {
    using type = smp::reverse<sfinae<C>>;
  };
}
