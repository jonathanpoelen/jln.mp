#pragma once

#include "../../number/is_number.hpp"
#include "../functional/identity.hpp"

namespace jln::mp::smp
{
  template<class C = identity>
  using is_number = try_contract<
    mp::is_number<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, is_number<C>>
  {
    using type = smp::is_number<sfinae<C>>;
  };
}
