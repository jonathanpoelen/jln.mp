#pragma once

#include "../../number/as_number.hpp"
#include "../functional/identity.hpp"

namespace jln::mp::smp
{
  template<class C = identity>
  using as_number = try_contract<mp::as_number<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, as_number<C>>
  {
    using type = smp::as_number<sfinae<C>>;
  };
}
