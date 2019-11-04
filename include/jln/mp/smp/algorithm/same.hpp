#pragma once

#include "../functional/identity.hpp"
#include "../../algorithm/same.hpp"

namespace jln::mp::smp
{
  template<class C = identity>
  using same = valid_contract<mp::same<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, same<C>>
  {
    using type = smp::same<sfinae<C>>;
  };
}
