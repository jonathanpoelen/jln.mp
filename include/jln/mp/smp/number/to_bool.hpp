#pragma once

#include "../../number/to_bool.hpp"
#include "../functional/identity.hpp"

namespace jln::mp::smp
{
  // TODO C, NC = violation ?
  template<class C = identity>
  using to_bool = try_contract<mp::to_bool<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, to_bool<C>>
  {
    using type = smp::to_bool<sfinae<C>>;
  };
}
