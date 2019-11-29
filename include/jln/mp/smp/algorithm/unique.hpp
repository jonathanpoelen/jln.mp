#pragma once

#include "../list/list.hpp"
#include "../../algorithm/unique.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  using unique = valid_contract<mp::unique<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unique<C>>
  {
    using type = smp::unique<sfinae<C>>;
  };
}
