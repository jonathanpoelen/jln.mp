#pragma once

#include "../functional/identity.hpp"
#include "../../utility/unpack_append.hpp"

namespace jln::mp::smp
{
  template<class C>
  using unpack_append = try_contract<mp::unpack_append<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unpack_append<C>>
  {
    using type = smp::unpack_append<sfinae<C>>;
  };
}
