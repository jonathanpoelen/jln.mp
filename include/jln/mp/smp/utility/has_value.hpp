#pragma once

#include "../functional/identity.hpp"
#include "../../utility/has_value.hpp"

namespace jln::mp::smp
{
  template<class C = identity>
  using has_value = try_contract<mp::has_value<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, has_value<C>>
  {
    using type = smp::has_value<sfinae<C>>;
  };
}
